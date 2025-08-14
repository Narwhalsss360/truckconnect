from __future__ import annotations
from dataclasses import dataclass, field
from enum import Enum
from struct import unpack_from
from typing import Any, Callable, TypeGuard, TypeVar, Type
from scssdk_telemetry.scssdk_dataclasses import TYPE_SIZE_BY_ID


class SCSValueType(Enum):
    SCS_VALUE_TYPE_INVALID = 0
    SCS_VALUE_TYPE_bool = 1
    SCS_VALUE_TYPE_s32 = 2
    SCS_VALUE_TYPE_u32 = 3
    SCS_VALUE_TYPE_u64 = 4
    SCS_VALUE_TYPE_float = 5
    SCS_VALUE_TYPE_double = 6
    SCS_VALUE_TYPE_fvector = 7
    SCS_VALUE_TYPE_dvector = 8
    SCS_VALUE_TYPE_euler = 9
    SCS_VALUE_TYPE_fplacement = 10
    SCS_VALUE_TYPE_dplacement = 11
    SCS_VALUE_TYPE_string = 12
    SCS_VALUE_TYPE_s64 = 13


BufferType = bytes | bytearray


@dataclass
class SCSValueFVector:
    x: float = field(default=0.0)
    y: float = field(default=0.0)
    z: float = field(default=0.0)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[SCSValueFVector, int]:
        return SCSValueFVector(*unpack_from("=fff", buffer, offset)), TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_fvector.value]


@dataclass
class SCSValueDVector:
    x: float = field(default=0.0)
    y: float = field(default=0.0)
    z: float = field(default=0.0)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[SCSValueDVector, int]:
        return SCSValueDVector(*unpack_from("=ddd", buffer, offset)), TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_dvector.value]


@dataclass
class SCSValueEuler:
    heading: float = field(default=0.0)
    pitch: float = field(default=0.0)
    roll: float = field(default=0.0)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[SCSValueEuler, int]:
        return SCSValueEuler(*unpack_from("=fff", buffer, offset)), TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_euler.value]


@dataclass
class SCSValueFPlacement:
    position: SCSValueFVector = field(default_factory=SCSValueFVector)
    orientation: SCSValueEuler = field(default_factory=SCSValueEuler)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[SCSValueFPlacement, int]:
        position, position_read = SCSValueFVector.from_bytes(buffer, offset)
        orientation = SCSValueEuler.from_bytes(buffer, offset + position_read)[0]
        return SCSValueFPlacement(position, orientation), TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_fplacement.value]


@dataclass
class SCSValueDPlacement:
    position: SCSValueDVector = field(default_factory=SCSValueDVector)
    orientation: SCSValueEuler = field(default_factory=SCSValueEuler)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[SCSValueDPlacement, int]:
        position, position_read = SCSValueDVector.from_bytes(buffer, offset)
        orientation = SCSValueEuler.from_bytes(buffer, offset + position_read)[0]
        return SCSValueDPlacement(position, orientation), TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_dplacement.value]


def szstr_from_bytes(buffer: BufferType, offset: int = 0) -> tuple[str, int]:
    if len(buffer) == offset:
        raise ValueError("'offset' out of bounds")

    if buffer[offset] == 0:
        return "", 1

    end: int = offset
    for i, c in enumerate(buffer[offset:]):
        if c == 0:
            end = offset + i
            break

    if end == offset:
        raise ValueError('Non-null terminated string')

    return bytes(buffer[offset:end]).decode("utf-8"), end - offset + 1


def vector_bool_value_from_bytes(buffer, offset: int = 0) -> tuple[list[bool], int]:
    vector_size: int = unpack_from("=I", buffer, offset)[0]
    if vector_size == 0:
        return [], 4
    offset += 4

    bools: list[bool] = []
    byte: int = 0
    bit: int = 0
    for _ in range(vector_size):
        if bit == 8:
            bit = 0
            byte += 1
        bools.append(((buffer[offset + byte]) & (1 << bit)) > 0)
        bit += 1

    return bools, 4 + byte + 1


type ValueTypes = (
    bool |
    int |
    float |
    SCSValueFVector |
    SCSValueDVector |
    SCSValueEuler |
    SCSValueFPlacement |
    SCSValueDPlacement |
    str |
    list
)

VALUE_TYPES: tuple[type, ...] = (
    bool,
    int,
    float,
    SCSValueFVector,
    SCSValueDVector,
    SCSValueEuler,
    SCSValueFPlacement,
    SCSValueDPlacement,
    str,
    list
)


type ValueStorageTypes = (
    tuple[bool, ValueTypes] |
    tuple[bool, list[ValueTypes], int] |
    list[ValueTypes]
)


T = TypeVar("T")


def is_value_storage(storage: ValueStorageTypes, t: Type[T]) -> TypeGuard[tuple[bool, T]]:
    return (
        isinstance(storage, tuple) and
        len(storage) == 2 and
        isinstance(storage[0], bool) and isinstance(storage[1], t)
    )


def is_value_array_storage(storage: ValueStorageTypes, t: Type[T]) -> TypeGuard[tuple[bool, list[T], int]]:
    return (
        isinstance(storage, tuple) and
        len(storage) == 3 and
        isinstance(storage[0], bool) and
        isinstance(storage[1], list) and
        all(isinstance(x, t) for x in storage[1]) and
        isinstance(storage[2], int)
    )


def is_value_vector_storage(storage: ValueStorageTypes, t: Type[T]) -> TypeGuard[list[T]]:
    return (
        isinstance(storage, list) and
        all(isinstance(x, t) for x in storage)
    )


def is_storage_type(obj: Any) -> TypeGuard[ValueStorageTypes]:
    if isinstance(obj, tuple):
        if len(obj) == 2:
            return (
                isinstance(obj[0], bool) and
                isinstance(obj[1], VALUE_TYPES)
            )
        elif len(obj) == 3:
            return (
                isinstance(obj[0], bool) and
                isinstance(obj[1], list) and
                all(isinstance(x, VALUE_TYPES) for x in obj[1]) and
                isinstance(obj[2], int)
            )
    elif isinstance(obj, list):
        return all(isinstance(x, VALUE_TYPES) for x in obj)
    return False


DESERIALIZER_BY_ID: list[None | Callable[[BufferType, int], tuple[ValueTypes, int]]] = [
    None,
    (lambda buffer, offset: (unpack_from("=?", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_bool.value])),
    (lambda buffer, offset: (unpack_from("=i", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_s32.value])),
    (lambda buffer, offset: (unpack_from("=I", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_u32.value])),
    (lambda buffer, offset: (unpack_from("=Q", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_u64.value])),
    (lambda buffer, offset: (unpack_from("=f", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_float.value])),
    (lambda buffer, offset: (unpack_from("=d", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_double.value])),
    SCSValueFVector.from_bytes,
    SCSValueDVector.from_bytes,
    SCSValueEuler.from_bytes,
    SCSValueFPlacement.from_bytes,
    SCSValueDPlacement.from_bytes,
    szstr_from_bytes,
    (lambda buffer, offset: (unpack_from("=q", buffer, offset)[0], TYPE_SIZE_BY_ID[SCSValueType.SCS_VALUE_TYPE_s64.value]))
]


def value_storage_from_bytes(scs_value_type: SCSValueType, buffer: BufferType, offset: int = 0) -> tuple[tuple[bool, ValueTypes], int]:
    if not (deserializer := DESERIALIZER_BY_ID[scs_value_type.value]):
        raise ValueError("Invalid scs value type.")

    initialized: bool = unpack_from("=?", buffer, offset)[0]
    value, read = deserializer(buffer, offset + 1)
    return (initialized, value), 1 + read


def value_array_storage_from_bytes(scs_value_type: SCSValueType, array_size: int, buffer: BufferType, offset: int = 0) -> tuple[tuple[bool, list[ValueTypes], int], int]:
    if not (deserializer := DESERIALIZER_BY_ID[scs_value_type.value]):
        raise ValueError("Invalid scs value type.")
    if array_size <= 0:
        raise ValueError("'array_size' must be greater than 0")

    initialized: bool = unpack_from("=?", buffer, offset)[0]
    total_read = 1

    count: int = unpack_from("=I", buffer, offset + total_read)[0]
    total_read += 4

    array: list = []
    for _ in range(array_size):
        deserialized, read = deserializer(buffer, offset + total_read)
        array.append(deserialized)
        total_read += read
    return (initialized, array, count), total_read


def value_vector_storage_from_bytes(scs_value_type: SCSValueType, buffer: BufferType, offset: int = 0) -> tuple[list[ValueTypes], int]:
    if not (deserializer := DESERIALIZER_BY_ID[scs_value_type.value]):
        raise ValueError("Invalid scs value type.")

    if scs_value_type == SCSValueType.SCS_VALUE_TYPE_bool:
        def guard(_: list[bool]) -> TypeGuard[list[ValueTypes]]:
            return True

        vector, read = vector_bool_value_from_bytes(buffer, offset)
        assert guard(vector)
        return vector, read

    vector_size = unpack_from("=I", buffer, offset)[0]
    total_read: int = 4
    vector: list = []
    for _ in range(vector_size):
        value, read = deserializer(buffer, offset + total_read)
        vector.append(value)
        total_read += read
    return vector, total_read


def storage_from_bytes(scs_value_type: SCSValueType, buffer: BufferType, offset: int = 0, array_size: int | None = None, vector: bool = False) -> ValueStorageTypes:
    if array_size is not None and vector:
        raise ValueError("'array_size' and 'vector' are mutually exclusive")

    def guard(_) -> TypeGuard[ValueStorageTypes]:
        return True

    if array_size is not None:
        retval = value_array_storage_from_bytes(scs_value_type, array_size, buffer, offset)
        assert guard(retval)
        return retval
    elif vector:
        retval = value_vector_storage_from_bytes(scs_value_type, buffer, offset)
        assert guard(retval)
        return retval
    else:
        retval = value_storage_from_bytes(scs_value_type, buffer, offset)
        assert guard(retval)
        return retval
