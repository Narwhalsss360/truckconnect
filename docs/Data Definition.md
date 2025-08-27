# Data Definition

A data definition consists of an id 0-255, and ordered members.

## Data Member

- TelemetryID
- Trailer Count
- (C++): offset

To use definitions, register your data definition for each new connection, then you may request. You may unregister data definitions, although it's not required.

All data would be buffered, packed. 
You may access your data directly in the connection's buffer, with the `DEFINED_DATA_DATA_START` constant offset. 
Defining data is specific to the language. C# uses a class or base class (automatically defines on current instance), and a `Define<T>` for value-types. C++ uses template specializations. In python, a data definition can be created using the `data_definition(id: int)` decorator on a class, similar to the `dataclass` decorator as `data_definition` is a wrapper. Otherwise data definitions can be deserialized into a tuple of the telemetries in the data definition. 
Specific languages also include API calls to structure the data into your `struct/class` with a corresponding data definition.

See the samples for each language.
