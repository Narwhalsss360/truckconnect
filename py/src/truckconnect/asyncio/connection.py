from __future__ import annotations
from types import TracebackType
from socket import socket, AddressFamily, SocketKind, IPPROTO_TCP, SHUT_RDWR
from typing import Callable, Optional, Type, TypeVar
from asyncio import AbstractEventLoop, get_event_loop
from truckconnect.telemetry_id import TelemetryID
from scssdk_truckconnect.truckconnect import Version, Telemetry, telemetries, TelemetryType
from nstreamcom import Collector, encode_with_size
from truckconnect.value_storage import BufferType, value_storage_from_bytes, value_array_storage_from_bytes, SCSValueType
from ..data import DATA_DEFINITION_ATTR_NAME, NON_CHANNEL_TYPES, DataDefinition, DeserializedType, NON_CHANNEL_DESERIALIZERS
from ..connection import TrailerIndexOrCount, RequestType, CommunicationResult, CommunicationError


T = TypeVar("T")


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
        self.definitions: list[DataDefinition] = []

    @property
    def connected(self) -> bool:
        return self._connected

    async def connect(self, loop: Optional[AbstractEventLoop] = None) -> None:
        loop = loop or get_event_loop()
        if self.connected:
            raise CommunicationError(CommunicationResult.AlreadyConnected)
        await loop.sock_connect(self.socket, self.addr)
        self._connected = True

    async def receive_one(self, loop: Optional[AbstractEventLoop] = None) -> None:
        loop = loop or get_event_loop()
        self._ensure_connected("receive_one")
        if self.pending_request == RequestType.NoRequest:
            raise CommunicationError(CommunicationResult.NoPendingRequest, "There is no request pending to receive")

        if not (recv := await loop.sock_recv(self.socket, 1)):
            raise CommunicationError(CommunicationResult.Disconnected)
        self.collector.collect(recv[0])

    async def receive_all(self, loop: Optional[AbstractEventLoop] = None) -> None:
        loop = loop or get_event_loop()
        self._ensure_connected("receive_all")
        if self.pending_request == RequestType.NoRequest:
            raise CommunicationError(CommunicationResult.NoPendingRequest, "There is no request pending to receive")

        if self.collector.data_ready:
            self.collector.reset()
        while not self.collector.error_state and not self.collector.data_ready:
            if not (recv := await loop.sock_recv(self.socket, 1)):
                raise CommunicationError(CommunicationResult.Disconnected)
            self.collector.collect(recv[0])

    async def get_version(self, loop: Optional[AbstractEventLoop] = None) -> Version:
        self._ensure_connected("get_version")
        self._ensure_pending_request(RequestType.NoRequest)

        self.pending_request = RequestType.Version
        self.socket.send(encode_with_size([RequestType.Version.value]))
        await self.receive_all(loop)
        self.pending_request = RequestType.NoRequest

        self._ensure_received_request(RequestType.Version, exact_size=1 + 4)

        return Version.from_int(int.from_bytes(self.collector.bytearray[1:4], "little"))

    def send_request_for(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None, loop: Optional[AbstractEventLoop] = None) -> None:
        loop = loop or get_event_loop()
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

    async def receive_for_request(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None, loop: Optional[AbstractEventLoop] = None) -> None:
        self._ensure_connected("receive_for_request")
        self._ensure_pending_request(RequestType.TelemetryID)
        trailer_index_or_count = trailer_index_or_count or TrailerIndexOrCount()

        if telemetry_id != self.pending_telemetry_id:
            raise CommunicationError(CommunicationResult.OtherTelemetryIDPending)
        if trailer_index_or_count != self.pending_trailer_index_or_count:
            raise CommunicationError(CommunicationResult.OtherTrailerIndexRequestPending)

        await self.receive_all(loop)
        self.clear_pending_request()
        self._ensure_received_request(RequestType.TelemetryID, minimum_size=3)

        if telemetry_id.value != self.collector.bytearray[1]:
            raise CommunicationError(CommunicationResult.ReceivedOtherTelemetry)

        if TrailerIndexOrCount.from_int(self.collector.bytearray[2]) != trailer_index_or_count:
            raise CommunicationError(CommunicationResult.ReceivedOtherTrailerIndex)

    async def request_telemetry(
        self,
        telemetry_id: TelemetryID | Type[T],
        trailer_index_or_count: TrailerIndexOrCount | None = None,
        loop: Optional[AbstractEventLoop] = None
    ) -> tuple[T, int] | tuple[DeserializedType, int]:
        if isinstance(telemetry_id, type):
            type_to_id: dict[type, TelemetryID] = { v: k for k, v in NON_CHANNEL_TYPES.items() }
            if telemetry_id not in type_to_id:
                raise TypeError(f"The type's '{telemetry_id}' telemetry ID could not be inferred.")
            telemetry_id = type_to_id[telemetry_id]
        trailer_index_or_count = trailer_index_or_count or TrailerIndexOrCount()

        self.send_request_for(telemetry_id, trailer_index_or_count, loop)
        await self.receive_for_request(telemetry_id, trailer_index_or_count, loop)

        telemetry: Telemetry = telemetries()[telemetry_id.value]
        deserializer: Callable[[BufferType, int], tuple[DeserializedType, int]]
        if telemetry.telemetry_type == TelemetryType.Channel:
            if telemetry.indexed:
                deserializer = lambda buffer, offset: value_array_storage_from_bytes(SCSValueType(telemetry.scs_type_id), telemetry.as_channel.max_count, buffer, offset)
            else:
                deserializer = lambda buffer, offset: value_storage_from_bytes(SCSValueType(telemetry.scs_type_id), buffer, offset)
        else:
            deserializer = NON_CHANNEL_DESERIALIZERS[telemetry_id]

        if trailer_index_or_count.is_count:
            deserialized_list: list[DeserializedType] = []
            total_read: int = 0
            for _ in range(trailer_index_or_count.index_or_count):
                deserialized, read = deserializer(self.collector.bytearray, Connection.TELEMETRY_DATA_START + total_read)
                total_read += read
                deserialized_list.append(deserialized)
            return deserialized_list, total_read
        else:
            return deserializer(self.collector.bytearray, Connection.TELEMETRY_DATA_START)

    async def request_telemetry_structure(self, structure_type: Type[T], trailer_index_or_count: TrailerIndexOrCount | None = None, loop: Optional[AbstractEventLoop] = None) -> tuple[T, int]:
        if (telemetry_id := {v: k for k, v in NON_CHANNEL_TYPES.items()}.get(structure_type)) is None:
            raise TypeError(f"The type's '{structure_type}' telemetry ID could not be inferred.")
        structure, read = await self.request_telemetry(telemetry_id, trailer_index_or_count, loop)
        assert isinstance(structure, structure_type)
        return structure, read

    def get_definition(self, id_or_definition: int | DataDefinition) -> DataDefinition | None:
        if isinstance(id_or_definition, int):
            try:
                return next(filter(lambda d: d.id == id_or_definition, self.definitions))
            except StopIteration:
                return None
        else:
            try:
                self.definitions.index(id_or_definition)
                return id_or_definition
            except ValueError:
                return None

    async def register_data_definition(self, definition_or_type: DataDefinition | type, loop: Optional[AbstractEventLoop] = None) -> None:
        if isinstance(definition_or_type, type):
            if not hasattr(definition_or_type, DATA_DEFINITION_ATTR_NAME):
                raise TypeError("The provided type is not a data definition")
            definition_or_type = getattr(definition_or_type, DATA_DEFINITION_ATTR_NAME)
            assert isinstance(definition_or_type, DataDefinition)

        if self.get_definition(definition_or_type) is not None:
            raise CommunicationError(CommunicationResult.AlreadyRegistered)

        self._ensure_connected("register_data_definition")
        self._ensure_pending_request(RequestType.NoRequest)
        self.socket.send(encode_with_size(
            bytearray([RequestType.RegisterDataDefinition.value]) + definition_or_type.to_bytes()
        ))
        self.pending_request = RequestType.RegisterDataDefinition
        await self.receive_all(loop)
        self.clear_pending_request()
        self._ensure_received_request(RequestType.RegisterDataDefinition, exact_size=2)
        if self.collector.bytearray[1] != definition_or_type.id:
            raise CommunicationError(CommunicationResult.UnknownData)

        self.definitions.append(definition_or_type)

    async def request_data_definition(self, id_or_definition_or_type: int | DataDefinition | Type[T], loop: Optional[AbstractEventLoop] = None) -> T | None:
        cls: type | None = None
        if isinstance(id_or_definition_or_type, type):
            cls = id_or_definition_or_type
            if not hasattr(id_or_definition_or_type, DATA_DEFINITION_ATTR_NAME):
                raise TypeError("The provided type is not a data definition")
            id_or_definition_or_type = getattr(id_or_definition_or_type, DATA_DEFINITION_ATTR_NAME)
            assert isinstance(id_or_definition_or_type, DataDefinition)

        if (definition := self.get_definition(id_or_definition_or_type)) is None:
            raise CommunicationError(CommunicationResult.NotRegistered)

        self._ensure_connected("request_data_definition")
        self._ensure_pending_request(RequestType.NoRequest)
        self.socket.send(encode_with_size([RequestType.DefinedData.value, definition.id]))
        self.pending_request = RequestType.DefinedData
        await self.receive_all(loop)
        self.clear_pending_request()
        self._ensure_received_request(RequestType.DefinedData, minimum_size=2)
        if self.collector.bytearray[1] != definition.id:
            raise CommunicationError(CommunicationResult.UnknownData)

        if cls is not None:
            return cls(*(definition.deserialize(self.collector.bytearray, Connection.DATA_DEFINITION_DATA_START)[0]))

    async def unregister_data_definition(self, id_or_definition_or_type: int | DataDefinition | type, loop: Optional[AbstractEventLoop] = None) -> None:
        if isinstance(id_or_definition_or_type, type):
            if not hasattr(id_or_definition_or_type, DATA_DEFINITION_ATTR_NAME):
                raise TypeError("The provided type is not a data definition")
            id_or_definition_or_type = getattr(id_or_definition_or_type, DATA_DEFINITION_ATTR_NAME)
            assert isinstance(id_or_definition_or_type, DataDefinition)

        if (definition := self.get_definition(id_or_definition_or_type)) is None:
            raise CommunicationError(CommunicationResult.NotRegistered)

        self._ensure_connected("unregister_data_definition")
        self._ensure_pending_request(RequestType.NoRequest)
        self.socket.send(encode_with_size([RequestType.UnregisterDataDefinition.value, definition.id]))
        self.pending_request = RequestType.UnregisterDataDefinition
        await self.receive_all(loop)
        self.clear_pending_request()
        self._ensure_received_request(RequestType.UnregisterDataDefinition, exact_size=2)
        if self.collector.bytearray[1] != definition.id:
            raise CommunicationError(CommunicationResult.UnknownData)

        self.definitions.remove(definition)

    def disconnect(self) -> None:
        if not self.connected:
            raise CommunicationError(CommunicationResult.NotConnected)

        try:
            self.socket.shutdown(SHUT_RDWR)
        except (OSError, RuntimeError):
            pass

        try:
            while self.socket.recv(64):
                continue
        except (OSError, RuntimeError, TimeoutError):
            pass

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

    async def __aenter__(self) -> Connection:
        if not self.connected:
            await self.connect()
        return self

    async def __aexit__(self, t: type[BaseException] | None, value: BaseException | None, traceback: TracebackType | None) -> None:
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
            raise CommunicationError(CommunicationResult(self.collector.bytearray[1]))

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
