# Metadata

# C++

Telemetry metadata are stored in the `truckconnect::metadata` namespace, where data are stored in structures as static constant-expression fields. 

Each structure has a different set of fields depending on the telemetry type.

**Metadata Functions:**
- `telemtry_type_of(const telemetry_id& id)`
- `master_offset_of(const telemetry_id& id, const uint32_t& trailer_index = INVALID_TRAILER_INDEX)`
- `structure_offset_of(const telemetry_id& id)`
- `indexed(const telemetry_id& id)`
- `max_count(const telemetry_id& id)`
- `is_trailer_channel(const telemetry_id& id)`
- `scs_type_id_of(const telemetry_id& id)`
- `streq(char const* a, char const* b)`
- `id_of(const char* const macro, const bool& is_event_info = false)`
- `name_of(const telemetry_id& id)`
- `size_of(const telemetry_id& id)`
- `offset_of_latest(const telemetry_id& id)`
- `event_info_member_offset_of(const telemetry_id& id, const char* const member)`
- `event_info_member_scs_type_id(const telemetry_id& id, const char* const member)`
- `event_info_member_indexed(const telemetry_id& id, const char* const member)`
- `event_info_latest_offset(const telemetry_id& id)`
- `event_info_member_of(const telemetry_id& id, const char* const member)`
- `is_custom_channel(const telemetry_id& id)`
- `metadata_value_of(const telemetry_id& id)`
- `is_constant_size(const telemetry_id& id)`
- `extract_trailer_index(const char* const cstr, const bool reversing = true, size_t count = 0)`: `reversing` and `count` is unused.
- `is_trailer_telemetry(const telemetry_id& id)`

# C#

The `TruckConnect.Metadata` class is what is used to describe all telemetry metadata. 
There exists a `public static readonly Metadata[] METADATA` field which has all instances of metadata. 
Retrieve metadata by id by using `Metadata.ByID(TelemetryID)`

# Python

Since python was used for meta-programming and code generation, the `truckconnect` API is fragmented in modules. 
Metadata is stored in the `Telemetry` class from the `scssdk_truckconnect.truckconnect` module. It's `id` member is _not_ of 
the `TelemetryID` enum type, but an integer. All telemetries get built from a json file, and can be accessed by the 
`telemetries() -> list[Telemetry]` function.

