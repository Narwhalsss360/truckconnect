from dataclasses import dataclass, field, Field, MISSING
from inspect import get_annotations
from typing import Callable, Type, TypeGuard, TypeVar, Any, get_origin, get_args
from .value_storage import (
    SCS_VALUE_TYPE_TO_TYPE,
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


DATA_DEFINITION_ATTR_NAME: str = "__data_definition__"


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


NON_CHANNEL_TYPES: dict[TelemetryID, type] = {
    TelemetryID.GameplayPlayerUseTrainInfo: GameplayPlayerUseTrainInfo,
    TelemetryID.GameplayPlayerUseFerryInfo: GameplayPlayerUseFerryInfo,
    TelemetryID.GameplayPlayerTollgatePaidInfo: GameplayPlayerTollgatePaidInfo,
    TelemetryID.GameplayPlayerFinedInfo: GameplayPlayerFinedInfo,
    TelemetryID.GameplayJobDeliveredInfo: GameplayJobDeliveredInfo,
    TelemetryID.GameplayJobCancelledInfo: GameplayJobCancelledInfo,
    TelemetryID.ConfigurationJobInfo: ConfigurationJobInfo,
    TelemetryID.ConfigurationTrailerInfo: ConfigurationTrailerInfo,
    TelemetryID.ConfigurationTruckInfo: ConfigurationTruckInfo,
    TelemetryID.ConfigurationHshifterInfo: ConfigurationHshifterInfo,
    TelemetryID.ConfigurationControlsInfo: ConfigurationControlsInfo,
    TelemetryID.ConfigurationSubstancesInfo: ConfigurationSubstancesInfo,
    TelemetryID.Trailer: Trailer,
    TelemetryID.Truck: Truck,
    TelemetryID.General: General,
    TelemetryID.Channels: Channels,
    TelemetryID.Gameplay: Gameplay,
    TelemetryID.Configuration: Configuration,
    TelemetryID.Master: Master
}


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


class DataClassDataMemberField(Field):
    def __init__(
        self,
        telemetry_id: TelemetryID,
        trailer_count: int,
        default,
        default_factory,
        init,
        repr,
        hash,
        compare,
        metadata,
        kw_only
    ) -> None:
        super().__init__(
            default,
            default_factory,
            init,
            repr,
            hash,
            compare,
            metadata,
            kw_only
        )
        self.telemetry_id = telemetry_id
        self.trailer_count = trailer_count


def member(
    telemetry_id: TelemetryID = TelemetryID.Invalid,
    trailer_count: int = 0,
    default=MISSING,
    default_factory=MISSING,
    init=True,
    repr=True,
    hash=None,
    compare=True,
    metadata=None,
    kw_only=MISSING
) -> Any:
    if default is not MISSING and default_factory is not MISSING:
        raise ValueError('default and default_factory are mutually exclusive')
    return DataClassDataMemberField(
        telemetry_id,
        trailer_count,
        default,
        default_factory,
        init,
        repr,
        hash,
        compare,
        metadata,
        kw_only
    )


def data_definition(
    id: int,
    /,
    *,
    init=True,
    repr=True,
    eq=True,
    order=False,
    unsafe_hash=False,
    frozen=False,
    match_args=True,
    kw_only=False,
    slots=False,
    weakref_slot=False
):
    def wrap(cls):
        data_definition: DataDefinition = DataDefinition(id, [])
        a = get_annotations(cls)
        for member_name, annotation in a.items():
            member = getattr(cls, member_name)
            if not isinstance(member, DataClassDataMemberField):
                continue

            if member.telemetry_id == TelemetryID.Invalid:
                if not isinstance(annotation, type):
                    raise TypeError(f"{member_name}:Telemetry ID cannot be infered by type")
                if not annotation in NON_CHANNEL_TYPES.values():
                    raise TypeError(f"{member_name}: Telemetry ID cannot be infered by type")
                member.telemetry_id = ({v: k for k, v in NON_CHANNEL_TYPES.items()})[annotation]

            if member.default is MISSING and member.default_factory is MISSING:
                telemetry: Telemetry = telemetries()[member.telemetry_id.value]
                if member.trailer_count == 0:
                    if telemetry.is_channel:
                        if get_origin(annotation) != tuple:
                            raise TypeError(f"{member_name}: All channel telemetries must be a tuple")

                        value_type: type = SCS_VALUE_TYPE_TO_TYPE[SCSValueType(telemetry.scs_type_id)]
                        type_args: tuple[type, ...] = get_args(annotation)
                        if telemetry.as_channel.indexed:
                            if len(type_args) != 3 or type_args[0] != bool or type_args[1] != value_type or type_args[2] != int:
                                raise TypeError(f"{member_name}: Annotation must be tuple[bool, {value_type.__name__}].")
                            member.default_factory = lambda: (False, value_type(), 0)
                        else:
                            if len(type_args) != 2 or type_args[0] != bool or type_args[1] != value_type:
                                raise TypeError(f"{member_name}: Annotation must be tuple[bool, {value_type.__name__}].")
                            member.default_factory = lambda: (False, value_type())
                    else:
                        if annotation != NON_CHANNEL_TYPES[member.telemetry_id]:
                            raise TypeError(f"{member_name}: Telemetry ID does not match type")
                        member.default_factory = NON_CHANNEL_TYPES[member.telemetry_id]
                else:
                    if get_origin(annotation) != list:
                        raise TypeError(f"{member_name}: telemetries non-zero trailer_count members must be a list")

                    type_args: tuple[type, ...] = get_args(annotation)
                    if telemetry.is_channel:
                        if len(type_args) != 1 or get_origin(type_args[0]) != tuple:
                            raise TypeError(f"{member_name}: All channel telemetries must be a tuple")
                        value_type: type = SCS_VALUE_TYPE_TO_TYPE[SCSValueType(telemetry.scs_type_id)]
                        type_args: tuple[type, ...] = get_args(type_args[0])
                        if telemetry.as_channel.indexed:
                            if len(type_args) != 3 or type_args[0] != bool or type_args[1] != value_type or type_args[2] != int:
                                raise TypeError(f"{member_name}: Annotation must be tuple[bool, {value_type.__name__}].")
                        else:
                            if len(type_args) != 2 or type_args[0] != bool or type_args[1] != value_type:
                                raise TypeError(f"{member_name}: Annotation must be tuple[bool, {value_type.__name__}].")
                    else:
                        if len(type_args) != 1 or type_args[0] != NON_CHANNEL_TYPES[member.telemetry_id]:
                            raise TypeError(f"{member_name}: Telemetry ID does not match type")
                    member.default_factory = lambda: []

            data_definition.members.append(DataMember(member.telemetry_id, member.trailer_count))
        setattr(cls, DATA_DEFINITION_ATTR_NAME, data_definition)
        return dataclass(
            cls,
            init=init,
            repr=repr,
            eq=eq,
            order=order,
            unsafe_hash=unsafe_hash,
            frozen=frozen,
            match_args=match_args,
            kw_only=kw_only,
            slots=slots,
            weakref_slot=weakref_slot
        )

    return wrap


def get_definition(obj_or_cls: Any) -> DataDefinition | None:
    if isinstance(obj_or_cls, type):
        if hasattr(obj_or_cls, DATA_DEFINITION_ATTR_NAME):
            return getattr(obj_or_cls, DATA_DEFINITION_ATTR_NAME)
    return get_definition(type(obj_or_cls))
