# Value Storage

### Strings

Strings are serialized as null-terminated UTF-8/8-bit ASCII bytes.

## Non-Primitive Values

For any non-primitive values, a structure exists. For C++, the `scssdk` structures are used.

## Value Storage

- Initialized: 1-Byte Bool
- Value: Generic Type

_Serialization order:_ Initialized, Value
_Python Tuple:_ Initialized, Value

## Value Array Storage

- Initialized: 1-Byte Bool
- Values: Array Of Generic Type
- Count: 4-Byte Unsigned Integer

_Serialization order_: Initialized, Count, Values...
_Python Tuple:_ Initialized, Value, Count

## Value Vector Storage

- Values: Dynamic Array Of Generic Type

_Value vector storages of booleans are serialized as bits._

_Serialization order_: 4-Byte Unsigned Integer Size, Values...
_Python:_ list

See [Master Structure](./Master%20Structure.md)
