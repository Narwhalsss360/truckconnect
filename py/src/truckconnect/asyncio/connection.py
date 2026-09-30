from __future__ import annotations

from asyncio import to_thread
from types import TracebackType
from typing import Self, TypeVar

from scssdk_truckconnect.truckconnect import (
    Version,
)

from truckconnect.chunk_collector import ChunkCollector
from truckconnect.telemetry_id import TelemetryID

from .. import connection
from ..connection import (
    DEFAULT_CHUNK_SIZE,
    RequestType,
    TrailerIndexOrCount,
)
from ..data import (
    DataDefinition,
    DeserializedType,
)

T = TypeVar("T")


class Connection:
    PORT: int = connection.Connection.PORT
    TELEMETRY_DATA_START: int = connection.Connection.TELEMETRY_DATA_START
    DATA_DEFINITION_DATA_START: int = connection.Connection.DATA_DEFINITION_DATA_START
    DEFINED_DATA_DATA_START: int = connection.Connection.DEFINED_DATA_DATA_START

    def __init__(self, ip: str = "127.0.0.1") -> None:
        self._connection: connection.Connection = connection.Connection(ip)

    @property
    def addr(self: Connection) -> tuple[str, int]:
        return self._connection.addr

    @property
    def pending_request(self: Connection) -> RequestType:
        return self._connection.pending_request

    @property
    def pending_telemetry_id(self: Connection) -> TelemetryID:
        return self._connection.pending_telemetry_id

    @property
    def pending_trailer_index_or_count(self: Connection) -> TrailerIndexOrCount:
        return self._connection.pending_trailer_index_or_count

    @property
    def collector(self: Connection) -> ChunkCollector:
        return self._connection.collector

    @property
    def definitions(self: Connection) -> list[DataDefinition]:
        return self._connection.definitions

    @property
    def connected(self) -> bool:
        return self._connection._connected

    async def connect(self) -> None:
        return await to_thread(self._connection.connect)

    async def receive_one_chunk(self, chunk_size: int = DEFAULT_CHUNK_SIZE) -> None:
        return await to_thread(self._connection.receive_one_chunk, chunk_size)

    async def receive_all_chunks(self, chunk_size: int = DEFAULT_CHUNK_SIZE) -> None:
        return await to_thread(self._connection.receive_all_chunks, chunk_size)

    async def get_version(self) -> Version:
        return await to_thread(self._connection.get_version)

    async def send_request_for(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None) -> None:
        return await to_thread(self._connection.send_request_for, telemetry_id, trailer_index_or_count)

    async def receive_for_request(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None, chunk_size: int = DEFAULT_CHUNK_SIZE) -> None:
        return await to_thread(self._connection.receive_for_request, telemetry_id, trailer_index_or_count, chunk_size)

    async def request_telemetry(
        self,
        telemetry_id: TelemetryID | type[T],
        trailer_index_or_count: TrailerIndexOrCount | None = None,
        chunk_size: int = DEFAULT_CHUNK_SIZE
    ) -> tuple[T, int] | tuple[DeserializedType, int]:
        return await to_thread(self._connection.request_telemetry, telemetry_id, trailer_index_or_count, chunk_size)

    async def request_telemetry_structure(self, structure_type: type[T], trailer_index_or_count: TrailerIndexOrCount | None = None, chunk_size: int = DEFAULT_CHUNK_SIZE) -> tuple[T, int]:
        return await to_thread(self._connection.request_telemetry_structure, structure_type, trailer_index_or_count, chunk_size)

    def get_definition(self, id_or_definition: int | DataDefinition) -> DataDefinition | None:
        return self._connection.get_definition(id_or_definition)

    async def register_data_definition(self, definition_or_type: DataDefinition | type) -> None:
        return await to_thread(self._connection.register_data_definition, definition_or_type)

    async def request_data_definition(self, id_or_definition_or_type: int | DataDefinition | type[T], chunk_size: int = DEFAULT_CHUNK_SIZE) -> T | None:
        return await to_thread(self._connection.request_data_definition, id_or_definition_or_type, chunk_size)

    async def unregister_data_definition(self, id_or_definition_or_type: int | DataDefinition | type) -> None:
        return await to_thread(self._connection.unregister_data_definition, id_or_definition_or_type)

    def disconnect(self) -> None:
        return self._connection.disconnect()

    def clear_pending_request(self) -> None:
        return self._connection.clear_pending_request()

    async def __aenter__(self) -> Self:
        await to_thread(self._connection.__enter__)
        return self

    async def __aexit__(self, t: type[BaseException] | None, value: BaseException | None, traceback: TracebackType | None) -> None:
        return await to_thread(self._connection.__exit__, t, value, traceback)


