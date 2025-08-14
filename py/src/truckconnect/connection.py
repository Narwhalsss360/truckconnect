from __future__ import annotations
from dataclasses import dataclass, field
from enum import Enum
from truckconnect.telemetry_id import TelemetryID
from socket import socket, AddressFamily, SocketKind, IPPROTO_TCP
from nstreamcom import Collector


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
    PORT: int = 52787
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
