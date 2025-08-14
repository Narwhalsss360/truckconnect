from __future__ import annotations
from dataclasses import dataclass, field
from enum import Enum
from types import TracebackType
from socket import socket, AddressFamily, SocketKind, IPPROTO_TCP
from truckconnect.telemetry_id import TelemetryID
from scssdk_truckconnect.truckconnect import Version
from nstreamcom import Collector, encode_with_size


@dataclass
class TrailerIndexOrCount:
    is_count: bool = field(default=False)
    index_or_count: int = field(default=0)

    @staticmethod
    def from_int(as_int: int) -> TrailerIndexOrCount:
        if not (0 <= as_int <= 255):
            raise ValueError("integer must be within [0, 255]")
        return TrailerIndexOrCount(as_int & 1 > 0, as_int >> 1)

    def __int__(self) -> int:
        return int(self.is_count) | (self.index_or_count << 1)


class RequestType(Enum):
    NoRequest = 0
    TelemetryID = 1
    RegisterDataDefinition = 2
    DefinedData = 3
    UnregisterDataDefinition = 4
    Version = 5
    ErrorResponse = 6


class CommunicationResult(Enum):
    Success = 0
    GenericSocketError = 1
    AlreadyConnected = 2
    NotConnected = 3
    Disconnected = 4
    Incomplete = 5
    CollectorError = 6
    NoPendingRequest = 7
    InvalidTelemetry = 8
    InvalidTrailerIndex = 9
    OtherRequestPending = 10
    OtherTelemetryIDPending = 11
    OtherTrailerIndexRequestPending = 12
    ReceivedOtherResponse = 13
    ReceivedOtherTelemetry = 14
    ReceivedOtherTrailerIndex = 15
    DeserializationFailure = 16
    TrailerIndexOutOfBounds = 17
    TrailerCountOutOfBounds = 18
    TrailerIndexOrCountWasCount = 19
    NullArgument = 20
    Empty = 21
    AlreadyRegistered = 22
    OtherDefinedDataPending = 23
    NotRegistered = 24
    ArrangeError = 25
    BadlyFormed = 26
    UnknownData = 27


class CommunicationError(Exception):
    def __init__(self, communication_result: CommunicationResult, *args: object) -> None:
        super().__init__(f"Communication Result:{communication_result}", *args)
        self.communication_result = communication_result


class Connection:
    PORT: int = 52878
    TELEMETRY_DATA_START: int = 1 + 2
    DATA_DEFINITION_DATA_START: int = 1 + 1
    DEFINED_DATA_DATA_START: int = 1 + 1

    def __init__(self, ip: str = "127.0.0.1") -> None:
        self.addr: tuple[str, int] = ip, Connection.PORT
        self.socket = socket(AddressFamily.AF_INET, SocketKind.SOCK_STREAM, IPPROTO_TCP)
        self._connected: bool = False
        self.pending_request: RequestType = RequestType.NoRequest
        self.pending_telemetry_id: TelemetryID = TelemetryID.Invalid
        self.pending_trailer_index_or_count: TrailerIndexOrCount = TrailerIndexOrCount()
        self.collector = Collector()

    @property
    def connected(self) -> bool:
        return self._connected

    def connect(self) -> None:
        if self.connected:
            raise CommunicationError(CommunicationResult.AlreadyConnected)
        self.socket.connect(self.addr)
        self._connected = True

    def receive_one(self) -> None:
        self._ensure_connected("receive_one")
        if self.pending_request == RequestType.NoRequest:
            raise CommunicationError(CommunicationResult.NoPendingRequest, "There is no request pending to receive")

        if not (recv := self.socket.recv(1)):
            raise CommunicationError(CommunicationResult.Disconnected)
        self.collector.collect(recv[0])

    def receive_all(self) -> None:
        self._ensure_connected("receive_all")
        if self.pending_request == RequestType.NoRequest:
            raise CommunicationError(CommunicationResult.NoPendingRequest, "There is no request pending to receive")

        if self.collector.data_ready:
            self.collector.reset()
        while not self.collector.error_state and not self.collector.data_ready:
            if not (recv := self.socket.recv(1)):
                raise CommunicationError(CommunicationResult.Disconnected)
            self.collector.collect(recv[0])

    def get_version(self) -> Version:
        self._ensure_connected("get_version")
        self._ensure_pending_request(RequestType.NoRequest)

        self.pending_request = RequestType.Version
        self.socket.send(encode_with_size([RequestType.Version.value]))
        self.receive_all()
        self.pending_request = RequestType.NoRequest

        self._ensure_received_request(RequestType.Version, exact_size=1 + 4)

        return Version.from_int(int.from_bytes(self.collector.bytearray[1:4], "little"))

    def send_request_for(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None) -> None:
        self._ensure_connected("send_request_for")
        self._ensure_pending_request(RequestType.NoRequest)
        trailer_index_or_count = trailer_index_or_count or TrailerIndexOrCount()
        self.socket.send(encode_with_size([
            RequestType.TelemetryID.value,
            telemetry_id.value,
            int(trailer_index_or_count)
        ]))
        self.pending_request = RequestType.TelemetryID
        self.pending_telemetry_id = telemetry_id
        self.pending_trailer_index_or_count = trailer_index_or_count

    def receive_for_request(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None) -> None:
        self._ensure_connected("receive_for_request")
        self._ensure_pending_request(RequestType.TelemetryID)
        trailer_index_or_count = trailer_index_or_count or TrailerIndexOrCount()

        if telemetry_id != self.pending_telemetry_id:
            raise CommunicationError(CommunicationResult.OtherTelemetryIDPending)
        if trailer_index_or_count != self.pending_trailer_index_or_count:
            raise CommunicationError(CommunicationResult.OtherTrailerIndexRequestPending)

        self.receive_all()
        self._ensure_received_request(RequestType.TelemetryID, minimum_size=3)

        if telemetry_id.value != self.collector.bytearray[1]:
            raise CommunicationError(CommunicationResult.ReceivedOtherTelemetry)

        if TrailerIndexOrCount.from_int(self.collector.bytearray[2]) != self.pending_trailer_index_or_count:
            raise CommunicationError(CommunicationResult.ReceivedOtherTrailerIndex)

        self.clear_pending_request()

    def disconnect(self) -> None:
        if not self.connected:
            raise CommunicationError(CommunicationResult.NotConnected)
        self.socket.close()
        self.pending_request = RequestType.NoRequest
        self.pending_telemetry_id = TelemetryID.Invalid
        self.pending_trailer_index_or_count = TrailerIndexOrCount()
        self.collector.reset()
        self._connected = False

    def clear_pending_request(self) -> None:
        self.pending_request = RequestType.NoRequest
        self.pending_telemetry_id = TelemetryID.Invalid
        self.pending_trailer_index_or_count = TrailerIndexOrCount()

    def __enter__(self) -> Connection:
        if not self.connected:
            self.connect()
        return self

    def __exit__(self, t: type[BaseException] | None, value: BaseException | None, traceback: TracebackType | None) -> None:
        del t, value, traceback
        if self.connected:
            self.disconnect()

    def _ensure_connected(self, operation_name: str) -> None:
        if not self.connected:
            raise CommunicationError(CommunicationResult.Disconnected, f"'{operation_name}' requires a connection.")

    def _ensure_received_request(self, request_type: RequestType, minimum_size: int | None = None, exact_size: int | None = None) -> None:
        assert not (minimum_size is not None and exact_size is not None), "minimum_size and exact_size are mutually exclusive arguments"
        assert (
            (minimum_size is not None and minimum_size > 0) or
            (exact_size is not None and exact_size > 0)
        ), "Must specify non-zero minimum_size or exact_size"

        if self.collector.next_size == 0:
            raise CommunicationError(CommunicationResult.UnknownData)

        if self.collector.bytearray[0] == RequestType.ErrorResponse.value:
            raise CommunicationError(CommunicationResult(self.collector.bytearray[0]))

        if self.collector.bytearray[0] != request_type.value:
            raise CommunicationError(CommunicationResult.ReceivedOtherResponse)

        if minimum_size:
            if self.collector.next_size < minimum_size:
                raise CommunicationError(CommunicationResult.UnknownData)
        else:
            if self.collector.next_size != exact_size:
                raise CommunicationError(CommunicationResult.UnknownData)

    def _ensure_pending_request(self, request_type: RequestType, message: str | None = None) -> None:
        if self.pending_request != request_type:
            if message:
                raise CommunicationError(CommunicationResult.OtherRequestPending, message)
            else:
                raise CommunicationError(CommunicationResult.OtherRequestPending)
