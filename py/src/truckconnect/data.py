from dataclasses import dataclass, field
from typing import Callable, Type, TypeGuard, TypeVar
from .value_storage import (
    BufferType,
    SCSValueType,
    ValueStorageTypes,
    is_storage_type,
    is_value_storage,
    is_value_array_storage,
    is_value_vector_storage,
    value_storage_from_bytes,
    value_array_storage_from_bytes
)
from .telemetry_id import TelemetryID
from scssdk_truckconnect.truckconnect import Telemetry, TelemetryType, telemetries
from .master_structure import (
    GameplayPlayerUseTrainInfo,
    GameplayPlayerUseFerryInfo,
    GameplayPlayerTollgatePaidInfo,
    GameplayPlayerFinedInfo,
    GameplayJobDeliveredInfo,
    GameplayJobCancelledInfo,
    ConfigurationJobInfo,
    ConfigurationTrailerInfo,
    ConfigurationTruckInfo,
    ConfigurationHshifterInfo,
    ConfigurationControlsInfo,
    ConfigurationSubstancesInfo,
    Trailer,
    Truck,
    General,
    Channels,
    Gameplay,
    Configuration,
    Master
)


@dataclass
class DataMember:
    id: TelemetryID
    trailer_count: int = field(default=0)

    def to_bytes(self) -> bytearray:
        return bytearray([
            self.id.value,
            0, 0, 0, 0,
            self.trailer_count
        ])


DeserializedType = (
    ValueStorageTypes |
    GameplayPlayerUseTrainInfo |
    GameplayPlayerUseFerryInfo |
    GameplayPlayerTollgatePaidInfo |
    GameplayPlayerFinedInfo |
    GameplayJobDeliveredInfo |
    GameplayJobCancelledInfo |
    ConfigurationJobInfo |
    ConfigurationTrailerInfo |
    ConfigurationTruckInfo |
    ConfigurationHshifterInfo |
    ConfigurationControlsInfo |
    ConfigurationSubstancesInfo |
    Trailer |
    Truck |
    General |
    Channels |
    Gameplay |
    Configuration |
    Master |
    list
)


NON_CHANNEL_DESERIALIZERS: dict[TelemetryID, Callable[[BufferType, int], tuple[DeserializedType, int]]] = {
    TelemetryID.GameplayPlayerUseTrainInfo: GameplayPlayerUseTrainInfo.from_bytes,
    TelemetryID.GameplayPlayerUseFerryInfo: GameplayPlayerUseFerryInfo.from_bytes,
    TelemetryID.GameplayPlayerTollgatePaidInfo: GameplayPlayerTollgatePaidInfo.from_bytes,
    TelemetryID.GameplayPlayerFinedInfo: GameplayPlayerFinedInfo.from_bytes,
    TelemetryID.GameplayJobDeliveredInfo: GameplayJobDeliveredInfo.from_bytes,
    TelemetryID.GameplayJobCancelledInfo: GameplayJobCancelledInfo.from_bytes,
    TelemetryID.ConfigurationJobInfo: ConfigurationJobInfo.from_bytes,
    TelemetryID.ConfigurationTrailerInfo: ConfigurationTrailerInfo.from_bytes,
    TelemetryID.ConfigurationTruckInfo: ConfigurationTruckInfo.from_bytes,
    TelemetryID.ConfigurationHshifterInfo: ConfigurationHshifterInfo.from_bytes,
    TelemetryID.ConfigurationControlsInfo: ConfigurationControlsInfo.from_bytes,
    TelemetryID.ConfigurationSubstancesInfo: ConfigurationSubstancesInfo.from_bytes,
    TelemetryID.Trailer: Trailer.from_bytes,
    TelemetryID.Truck: Truck.from_bytes,
    TelemetryID.General: General.from_bytes,
    TelemetryID.Channels: Channels.from_bytes,
    TelemetryID.Gameplay: Gameplay.from_bytes,
    TelemetryID.Configuration: Configuration.from_bytes,
    TelemetryID.Master: Master.from_bytes
}


@dataclass
class DataDefinition:
    INVALID_DATA_DEFINITION_ID = 255

    id: int
    members: list[DataMember]

    def to_bytes(self) -> bytearray:
        as_bytes: bytearray = bytearray()
        as_bytes.append(self.id)
        for member in self.members:
            as_bytes.extend(member.to_bytes())
        return as_bytes

    def deserialize(self, buffer: BufferType, offset: int = 0) -> tuple[list[DeserializedType], int]:
        deserialized_definition: list[DeserializedType] = []
        total_read: int = 0

        for member in self.members:
            telemetry: Telemetry = telemetries()[member.id.value]
            deserializer: Callable[[BufferType, int], tuple[DeserializedType, int]]
            if telemetry.telemetry_type == TelemetryType.Channel:
                if telemetry.indexed:
                    deserializer = lambda buffer, offset: value_array_storage_from_bytes(SCSValueType(telemetry.scs_type_id), telemetry.as_channel.max_count, buffer, offset)
                else:
                    deserializer = lambda buffer, offset: value_storage_from_bytes(SCSValueType(telemetry.scs_type_id), buffer, offset)
            else:
                deserializer = NON_CHANNEL_DESERIALIZERS[member.id]

            if member.trailer_count == 0:
                deserialized, read = deserializer(buffer, offset + total_read)
                total_read += read
                deserialized_definition.append(deserialized)
            else:
                deserialized_list: list[DeserializedType] = []
                for _ in range(member.trailer_count):
                    deserialized, read = deserializer(buffer, offset + total_read)
                    total_read += read
                    deserialized_list.append(deserialized)
                deserialized_definition.append(deserialized_list)

        return deserialized_definition, total_read


T = TypeVar("T")


def is_value_storage_array(trailer_array: list, t: Type[T]) -> TypeGuard[list[tuple[bool, T]]]:
    return all(is_storage_type(x) and is_value_storage(x, t) for x in trailer_array)


def is_value_array_storage_array(trailer_array: list, t: Type[T]) -> TypeGuard[list[tuple[bool, T, int]]]:
    return all(is_storage_type(x) and is_value_array_storage(x, t) for x in trailer_array)


def is_value_vector_storage_array(trailer_array: list, t: Type[T]) -> TypeGuard[list[list[T]]]:
    return all(is_storage_type(x) and is_value_vector_storage(x, t) for x in trailer_array)
