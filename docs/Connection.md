# Connection

Connections are done by TCP IPv4 stream sockets on port 52878. Messages are encodedand decoded/collected using `NStreamCom`.

**Trailer Index Or Count**: For trailer telemetry requestsyou may specify either a trailer index, or a trailer count. 
Use the `TrailerIndexOrCount`/`trailer_index_or_count` type. 

On windows C++, the API used is WinSock2, which requires initialization before first use, and deinitialization after use. Use `bool sockets::initialize()` and `bool sockets::deinitialize()` for this, which returns `true` on success.

**Request Types**:

- `None` = 0`NoRequest` in Python
- `TelemetryID` = 1
- `RegisterDataDefinition` = 2
- `DefinedData` = 3
- `UnregisterDataDefinition` = 4
- `Version` = 5
- `ErrorResponse` = 6

**Communication Results**:

- `Success` = 0
- `GenericSocketError` = 1
- `AlreadyConnected` = 2
- `NotConnected` = 3
- `Disconnected` = 4
- `Incomplete` = 5
- `CollectorError` = 6
- `NoPendingRequest` = 7
- `InvalidTelemetry` = 8
- `InvalidTrailerIndex` = 9
- `OtherRequestPending` = 10
- `OtherTelemetryIDPending` = 11
- `OtherTrailerIndexRequestPending` = 12
- `ReceivedOtherResponse` = 13
- `ReceivedOtherTelemetry` = 14
- `ReceivedOtherTrailerIndex` = 15
- `DeserializationFailure` = 16
- `TrailerIndexOutOfBounds` = 17
- `TrailerCountOutOfBounds` = 18
- `TrailerIndexOrCountWasCount` = 19
- `NullArgument` = 20
- `Empty` = 21
- `AlreadyRegistered` = 22
- `OtherDefinedDataPending` = 23
- `NotRegistered` = 24
- `ArrangeError` = 25
- `BadlyFormed` = 26
- `UnknownData` = 27


_In C++ errors are values and in others, errors are exceptions (C#, Python)._

**Connection Type**:

The type holds all of the current communication state. The IP address is the constructor parameter (default `127.0.0.1`).

**Functions (C++)**:

All return `truckconnect::communication_result`

- `connect(connection& connection)`
- `send_version_request(connection& connection)`
- `receive_for_version(connection& connection, version_t& version)`
- `get_version(connection& connection, version_t& version)`
- `send_request_for(connection& connection, const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `receive_one(connection& connection)`
- `receive_all(connection& connection, std::function<void(const std::vector<uint8_t>&)> received_callback)`
- `receive_all(connection& connection)`
- `receive_for_request(connection& connection, const telemetry_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `receive_for_request(connection& connection, const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `request(connection& connection, const telemetry_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `request(connection& connection, const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `request(connection& connection, std::function<void(const typename meta::storage_type&)> received_callback, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `request(connection& connection, typename meta::storage_type& destination, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT)`
- `request(connection& connection, std::function<void(const typename meta::storage_type (&)[trailer_count])> received_callback)`
- `request(connection& connection, typename meta::storage_type (&array)[trailer_count])`
- `request(connection& connection, std::array<typename meta::storage_type, trailer_count>& array)`
- `register_data_definition(connection& connection, const data::data_definition_id& id, const data::data_member* const& members, const uint32_t& count)`
- `register_data_definition(connection& connection)`
- `get_definition(connection& connection, const data::data_definition_id& id, data::data_definition_value& definition)`
- `send_request_for(connection& connection, const data::data_definition_id& id)`
- `receive_for_request(connection& connection, const data::data_definition_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback)`
- `request(connection& connection, const data::data_definition_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback)`
- `request(connection& connection, data_structure& out)`
- `request(connection& connection, const data::data_definition_id& id)`
- `unregister_data_definition(connection& connection, const data::data_definition_id& id)`
- `unregister_data_definition(connection& connection)`
- `disconnect(connection& connection)`

**Functions (C#)**:

- `ConnectAsync(CancellationToken cancellationToken = default)`
- `Connect()`
- `ClearPendingRequest()`
- `SendRequestForAsync(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null, CancellationToken cancellationToken = default)`
- `GetVersion(CancellationToken cancellationToken = default)`
- `ReceiveOne(CancellationToken cancellationToken = default)`
- `ReceiveAllAsync(CancellationToken cancellationToken = default)`
- `ReceiveForRequest(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null, CancellationToken cancellationToken = default)`
- `RequestAsync(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default)`
- `RequestAsync<T>(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default) where T : struct`
- `RequestAsync<T>(TrailerIndexOrCount? trailerIndexOrCount = null, CancellationToken cancellationToken = default) where T : struct`
- `RequestArrayAsync<T>(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default) where T : struct`
- `GetDefinition(int definitionID)`
- `RegisterDataDefinitionAsync(DataDefinition dataDefinition, CancellationToken cancellationToken = default)`
- `RequestAsync(int definitionID, CancellationToken cancellationToken = default)`
- `RequestAsync(DataDefinition definition, CancellationToken cancellationToken = default)`
- `RequestAsync<T>(DataDefinition definition, CancellationToken cancellationToken = default) where T : struct`
- `UnregisterDataDefinitionAsync(int definitionID, CancellationToken cancellationToken = default)`
- `UnregisterDataDefinitionAsync(DataDefinition definition, CancellationToken cancellationToken = default) =>`
- ` Disconnect()`

**Functions (Python)**:

- `@property connected(self) -> bool`
- `connect(self) -> None`
- `receive_one(self) -> None`
- `receive_all(self) -> None`
- `get_version(self) -> Version`
- `send_request_for(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None) -> None`
- `receive_for_request(self, telemetry_id: TelemetryID, trailer_index_or_count: TrailerIndexOrCount | None = None) -> None`
- `request_telemetry`
- `request_telemetry_structure(self, structure_type: Type[T], trailer_index_or_count: TrailerIndexOrCount | None = None) -> tuple[T, int]`
- `get_definition(self, id_or_definition: int | DataDefinition) -> DataDefinition | None`
- `register_data_definition(self, definition_or_type: DataDefinition | type) -> None`
- `request_data_definition(self, id_or_definition_or_type: int | DataDefinition | Type[T]) -> T | None`
- `unregister_data_definition(self, id_or_definition_or_type: int | DataDefinition | type) -> None`
- `disconnect(self) -> None`
- `clear_pending_request(self) -> None`

