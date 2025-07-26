#include "register_all.h"
#include "truckconnectextension.h"
#include "dynamic_store.h"
#include <scssdk/common/scssdk_telemetry_common_channels.h>
#include <scssdk/common/scssdk_telemetry_common_configs.h>
#include <scssdk/common/scssdk_telemetry_common_gameplay_events.h>
#include <scssdk/common/scssdk_telemetry_job_common_channels.h>
#include <scssdk/common/scssdk_telemetry_trailer_common_channels.h>
#include <scssdk/common/scssdk_telemetry_truck_common_channels.h>

using std::string;
using std::to_string;
using namespace truckconnect;
using namespace truckconnect::metadata;
using truckconnect::platform::debug_assert;

template <typename meta>
void handle_event(scs_event_t event, const void* const info, scs_context_t) {
	static_assert(meta::telemetry_type == telemetry_type::structure, "Expected an event structure");
	static_assert(offsetof(scs_telemetry_configuration_t, id) == offsetof(scs_telemetry_gameplay_event_t, id), "Offsets must be equal.");
	static_assert(offsetof(scs_telemetry_configuration_t, attributes) == offsetof(scs_telemetry_gameplay_event_t, attributes), "Offsets must be equal.");
	
	debug_assert(info != nullptr);
	const scs_telemetry_configuration_t& data = *reinterpret_cast<const scs_telemetry_configuration_t* const>(info);

	if (streq(data.id, "trailer")) {
		console_log(SCS_LOG_TYPE_message, IDENTSTR(handle_event), "Skipping 'trailer' data, waiting for indexed data");
		return;
	}

	const uint32_t& trailer_index = extract_trailer_index(data.id);
	const telemetry_id& event_info_id = trailer_index != SCS_U32_NIL ? configuration_trailer_info::id : id_of(data.id, true);
	debug_assert(event_info_id != telemetry_id::invalid);

	const uint32_t& structure_offset = master_offset_of(event_info_id, trailer_index);
	debug_assert(structure_offset != INVALID_OFFSET);

	void* const structure = &apply_offset<void*>(&current_master(), structure_offset);
	value_storage<uint32_t>& latest = apply_offset<value_storage<uint32_t>>(structure, event_info_latest_offset(event_info_id));
	latest.initialized = true;

	if (data.attributes->name == nullptr) {
		return;
	}

	for (const scs_named_value_t* current = data.attributes; current->name; current++) {
		constexpr const uint32_t selector_count_member_offset = event_info_member_offset_of(telemetry_id::configuration_hshifter_info, "selector.count");
		const event_info_member member = event_info_member_of(event_info_id, current->name);
		if (current->index != SCS_U32_NIL && member.structure_offset == selector_count_member_offset) {
			console_log(SCS_LOG_TYPE_message, IDENTSTR(handle_event), "Skipping hshifter selector.count configuration indexed member.");
			continue;
		}

		debug_assert((current->index != SCS_U32_NIL) == member.indexed);
		debug_assert(member.event_info_id != telemetry_id::invalid);
		debug_assert(member.scs_type_id == current->value.type);
		dynamic_store(current->value, &apply_offset<void*>(structure, member.structure_offset), current->index);
	}

	latest.value++;
}

template <typename meta, size_t trailer_index = INVALID_TRAILER_INDEX>
void store(const scs_string_t channel, const scs_u32_t index, const scs_value_t* const value, const scs_context_t) {
    using primitive_type = typename meta::primitive_type;
    constexpr const bool& indexed = meta::indexed;
    constexpr const uint32_t& max_count = meta::max_count;
    constexpr const bool& trailer_channel = meta::trailer_channel;
    constexpr const uint32_t offset = master_offset_of(meta::id, trailer_index);
    static_assert(meta::telemetry_type == telemetry_type::channel, "Template parameter was not a channel");
    static_assert(trailer_channel == (trailer_index != INVALID_TRAILER_INDEX), "Fatal: template meta parameter and trailer_index discrepancy.");
    static_assert(offset < sizeof(current_master()), "Specified offset will result in corrupt memory");
    debug_assert(meta::scs_type_id == value->type);
    
	if ifconstexpr (trailer_channel) {
		debug_assert(extract_trailer_index(channel) == trailer_index);
	} else {
		debug_assert(string(meta::macro) == channel);
	}

    if ifconstexpr (indexed) {
        using storage_type = value_array_storage<primitive_type, max_count>;
        if (index == SCS_U32_NIL) {
            console_log(SCS_LOG_TYPE_error, string("store<") + name_of(meta::id) + ", " + to_string(trailer_index) + ">", "Critical error: expected indexed telemetry, but value was not.");
            debug_assert(false);
            return;
        }

		storage_type& storage = apply_offset<storage_type>(&current_master(), offset);
        storage.values[index] = *reinterpret_cast<const primitive_type* const>(&value->value_bool.value);
        if (storage.count <= index) {
            storage.count = index + 1;
        }
        storage.initialized = true;
    } else {
        using storage_type = value_storage<primitive_type>;
        if (index != SCS_U32_NIL) {
            console_log(SCS_LOG_TYPE_error, string("store<") + name_of(meta::id) + ", " + to_string(trailer_index) + ">", "Critical error: expected non-indexed telemetry, but value was.");
            debug_assert(false);
            return;
        }

		storage_type& storage = apply_offset<storage_type>(&current_master(), offset);
        storage.value = *reinterpret_cast<const primitive_type* const>(&value->value_bool.value);
        storage.initialized = true;
    }
}

void register_all(scs_telemetry_register_for_channel_t register_for_channel, scs_telemetry_register_for_event_t register_for_event) {
	register_for_event(SCS_TELEMETRY_EVENT_configuration, handle_event<metadata::configuration>, nullptr);
	register_for_event(SCS_TELEMETRY_EVENT_gameplay, handle_event<metadata::gameplay>, nullptr);
	register_for_channel(SCS_TELEMETRY_CHANNEL_local_scale, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::channel_local_scale>, nullptr);
	register_for_channel(SCS_TELEMETRY_CHANNEL_game_time, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::channel_game_time>, nullptr);
	register_for_channel(SCS_TELEMETRY_CHANNEL_multiplayer_time_offset, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::channel_multiplayer_time_offset>, nullptr);
	register_for_channel(SCS_TELEMETRY_CHANNEL_next_rest_stop, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::channel_next_rest_stop>, nullptr);
	register_for_channel(SCS_TELEMETRY_JOB_CHANNEL_cargo_damage, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::job_channel_cargo_damage>, nullptr);
	register_for_channel("trailer.0.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 0>, nullptr);
	register_for_channel("trailer.1.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 1>, nullptr);
	register_for_channel("trailer.2.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 2>, nullptr);
	register_for_channel("trailer.3.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 3>, nullptr);
	register_for_channel("trailer.4.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 4>, nullptr);
	register_for_channel("trailer.5.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 5>, nullptr);
	register_for_channel("trailer.6.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 6>, nullptr);
	register_for_channel("trailer.7.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 7>, nullptr);
	register_for_channel("trailer.8.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 8>, nullptr);
	register_for_channel("trailer.9.connected", SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_connected, 9>, nullptr);
	register_for_channel("trailer.0.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 0>, nullptr);
	register_for_channel("trailer.1.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 1>, nullptr);
	register_for_channel("trailer.2.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 2>, nullptr);
	register_for_channel("trailer.3.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 3>, nullptr);
	register_for_channel("trailer.4.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 4>, nullptr);
	register_for_channel("trailer.5.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 5>, nullptr);
	register_for_channel("trailer.6.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 6>, nullptr);
	register_for_channel("trailer.7.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 7>, nullptr);
	register_for_channel("trailer.8.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 8>, nullptr);
	register_for_channel("trailer.9.cargo.damage", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_cargo_damage, 9>, nullptr);
	register_for_channel("trailer.0.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 0>, nullptr);
	register_for_channel("trailer.1.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 1>, nullptr);
	register_for_channel("trailer.2.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 2>, nullptr);
	register_for_channel("trailer.3.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 3>, nullptr);
	register_for_channel("trailer.4.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 4>, nullptr);
	register_for_channel("trailer.5.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 5>, nullptr);
	register_for_channel("trailer.6.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 6>, nullptr);
	register_for_channel("trailer.7.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 7>, nullptr);
	register_for_channel("trailer.8.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 8>, nullptr);
	register_for_channel("trailer.9.world.placement", SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_world_placement, 9>, nullptr);
	register_for_channel("trailer.0.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 0>, nullptr);
	register_for_channel("trailer.1.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 1>, nullptr);
	register_for_channel("trailer.2.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 2>, nullptr);
	register_for_channel("trailer.3.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 3>, nullptr);
	register_for_channel("trailer.4.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 4>, nullptr);
	register_for_channel("trailer.5.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 5>, nullptr);
	register_for_channel("trailer.6.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 6>, nullptr);
	register_for_channel("trailer.7.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 7>, nullptr);
	register_for_channel("trailer.8.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 8>, nullptr);
	register_for_channel("trailer.9.velocity.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_velocity, 9>, nullptr);
	register_for_channel("trailer.0.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 0>, nullptr);
	register_for_channel("trailer.1.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 1>, nullptr);
	register_for_channel("trailer.2.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 2>, nullptr);
	register_for_channel("trailer.3.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 3>, nullptr);
	register_for_channel("trailer.4.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 4>, nullptr);
	register_for_channel("trailer.5.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 5>, nullptr);
	register_for_channel("trailer.6.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 6>, nullptr);
	register_for_channel("trailer.7.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 7>, nullptr);
	register_for_channel("trailer.8.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 8>, nullptr);
	register_for_channel("trailer.9.velocity.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_velocity, 9>, nullptr);
	register_for_channel("trailer.0.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 0>, nullptr);
	register_for_channel("trailer.1.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 1>, nullptr);
	register_for_channel("trailer.2.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 2>, nullptr);
	register_for_channel("trailer.3.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 3>, nullptr);
	register_for_channel("trailer.4.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 4>, nullptr);
	register_for_channel("trailer.5.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 5>, nullptr);
	register_for_channel("trailer.6.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 6>, nullptr);
	register_for_channel("trailer.7.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 7>, nullptr);
	register_for_channel("trailer.8.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 8>, nullptr);
	register_for_channel("trailer.9.acceleration.linear", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_linear_acceleration, 9>, nullptr);
	register_for_channel("trailer.0.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 0>, nullptr);
	register_for_channel("trailer.1.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 1>, nullptr);
	register_for_channel("trailer.2.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 2>, nullptr);
	register_for_channel("trailer.3.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 3>, nullptr);
	register_for_channel("trailer.4.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 4>, nullptr);
	register_for_channel("trailer.5.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 5>, nullptr);
	register_for_channel("trailer.6.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 6>, nullptr);
	register_for_channel("trailer.7.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 7>, nullptr);
	register_for_channel("trailer.8.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 8>, nullptr);
	register_for_channel("trailer.9.acceleration.angular", SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_local_angular_acceleration, 9>, nullptr);
	register_for_channel("trailer.0.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 0>, nullptr);
	register_for_channel("trailer.1.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 1>, nullptr);
	register_for_channel("trailer.2.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 2>, nullptr);
	register_for_channel("trailer.3.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 3>, nullptr);
	register_for_channel("trailer.4.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 4>, nullptr);
	register_for_channel("trailer.5.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 5>, nullptr);
	register_for_channel("trailer.6.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 6>, nullptr);
	register_for_channel("trailer.7.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 7>, nullptr);
	register_for_channel("trailer.8.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 8>, nullptr);
	register_for_channel("trailer.9.wear.body", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_body, 9>, nullptr);
	register_for_channel("trailer.0.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 0>, nullptr);
	register_for_channel("trailer.1.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 1>, nullptr);
	register_for_channel("trailer.2.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 2>, nullptr);
	register_for_channel("trailer.3.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 3>, nullptr);
	register_for_channel("trailer.4.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 4>, nullptr);
	register_for_channel("trailer.5.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 5>, nullptr);
	register_for_channel("trailer.6.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 6>, nullptr);
	register_for_channel("trailer.7.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 7>, nullptr);
	register_for_channel("trailer.8.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 8>, nullptr);
	register_for_channel("trailer.9.wear.chassis", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_chassis, 9>, nullptr);
	register_for_channel("trailer.0.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 0>, nullptr);
	register_for_channel("trailer.1.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 1>, nullptr);
	register_for_channel("trailer.2.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 2>, nullptr);
	register_for_channel("trailer.3.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 3>, nullptr);
	register_for_channel("trailer.4.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 4>, nullptr);
	register_for_channel("trailer.5.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 5>, nullptr);
	register_for_channel("trailer.6.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 6>, nullptr);
	register_for_channel("trailer.7.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 7>, nullptr);
	register_for_channel("trailer.8.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 8>, nullptr);
	register_for_channel("trailer.9.wear.wheels", SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wear_wheels, 9>, nullptr);
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_susp_deflection::max_count; i++) {
		register_for_channel("trailer.0.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 0>, nullptr);
		register_for_channel("trailer.1.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 1>, nullptr);
		register_for_channel("trailer.2.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 2>, nullptr);
		register_for_channel("trailer.3.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 3>, nullptr);
		register_for_channel("trailer.4.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 4>, nullptr);
		register_for_channel("trailer.5.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 5>, nullptr);
		register_for_channel("trailer.6.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 6>, nullptr);
		register_for_channel("trailer.7.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 7>, nullptr);
		register_for_channel("trailer.8.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 8>, nullptr);
		register_for_channel("trailer.9.wheel.suspension.deflection", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_susp_deflection, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_on_ground::max_count; i++) {
		register_for_channel("trailer.0.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 0>, nullptr);
		register_for_channel("trailer.1.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 1>, nullptr);
		register_for_channel("trailer.2.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 2>, nullptr);
		register_for_channel("trailer.3.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 3>, nullptr);
		register_for_channel("trailer.4.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 4>, nullptr);
		register_for_channel("trailer.5.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 5>, nullptr);
		register_for_channel("trailer.6.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 6>, nullptr);
		register_for_channel("trailer.7.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 7>, nullptr);
		register_for_channel("trailer.8.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 8>, nullptr);
		register_for_channel("trailer.9.wheel.on_ground", i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_on_ground, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_substance::max_count; i++) {
		register_for_channel("trailer.0.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 0>, nullptr);
		register_for_channel("trailer.1.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 1>, nullptr);
		register_for_channel("trailer.2.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 2>, nullptr);
		register_for_channel("trailer.3.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 3>, nullptr);
		register_for_channel("trailer.4.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 4>, nullptr);
		register_for_channel("trailer.5.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 5>, nullptr);
		register_for_channel("trailer.6.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 6>, nullptr);
		register_for_channel("trailer.7.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 7>, nullptr);
		register_for_channel("trailer.8.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 8>, nullptr);
		register_for_channel("trailer.9.wheel.substance", i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_substance, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_velocity::max_count; i++) {
		register_for_channel("trailer.0.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 0>, nullptr);
		register_for_channel("trailer.1.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 1>, nullptr);
		register_for_channel("trailer.2.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 2>, nullptr);
		register_for_channel("trailer.3.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 3>, nullptr);
		register_for_channel("trailer.4.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 4>, nullptr);
		register_for_channel("trailer.5.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 5>, nullptr);
		register_for_channel("trailer.6.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 6>, nullptr);
		register_for_channel("trailer.7.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 7>, nullptr);
		register_for_channel("trailer.8.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 8>, nullptr);
		register_for_channel("trailer.9.wheel.angular_velocity", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_velocity, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_steering::max_count; i++) {
		register_for_channel("trailer.0.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 0>, nullptr);
		register_for_channel("trailer.1.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 1>, nullptr);
		register_for_channel("trailer.2.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 2>, nullptr);
		register_for_channel("trailer.3.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 3>, nullptr);
		register_for_channel("trailer.4.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 4>, nullptr);
		register_for_channel("trailer.5.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 5>, nullptr);
		register_for_channel("trailer.6.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 6>, nullptr);
		register_for_channel("trailer.7.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 7>, nullptr);
		register_for_channel("trailer.8.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 8>, nullptr);
		register_for_channel("trailer.9.wheel.steering", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_steering, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_rotation::max_count; i++) {
		register_for_channel("trailer.0.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 0>, nullptr);
		register_for_channel("trailer.1.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 1>, nullptr);
		register_for_channel("trailer.2.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 2>, nullptr);
		register_for_channel("trailer.3.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 3>, nullptr);
		register_for_channel("trailer.4.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 4>, nullptr);
		register_for_channel("trailer.5.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 5>, nullptr);
		register_for_channel("trailer.6.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 6>, nullptr);
		register_for_channel("trailer.7.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 7>, nullptr);
		register_for_channel("trailer.8.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 8>, nullptr);
		register_for_channel("trailer.9.wheel.rotation", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_rotation, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_lift::max_count; i++) {
		register_for_channel("trailer.0.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 0>, nullptr);
		register_for_channel("trailer.1.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 1>, nullptr);
		register_for_channel("trailer.2.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 2>, nullptr);
		register_for_channel("trailer.3.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 3>, nullptr);
		register_for_channel("trailer.4.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 4>, nullptr);
		register_for_channel("trailer.5.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 5>, nullptr);
		register_for_channel("trailer.6.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 6>, nullptr);
		register_for_channel("trailer.7.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 7>, nullptr);
		register_for_channel("trailer.8.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 8>, nullptr);
		register_for_channel("trailer.9.wheel.lift", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift, 9>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::trailer_channel_wheel_lift_offset::max_count; i++) {
		register_for_channel("trailer.0.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 0>, nullptr);
		register_for_channel("trailer.1.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 1>, nullptr);
		register_for_channel("trailer.2.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 2>, nullptr);
		register_for_channel("trailer.3.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 3>, nullptr);
		register_for_channel("trailer.4.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 4>, nullptr);
		register_for_channel("trailer.5.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 5>, nullptr);
		register_for_channel("trailer.6.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 6>, nullptr);
		register_for_channel("trailer.7.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 7>, nullptr);
		register_for_channel("trailer.8.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 8>, nullptr);
		register_for_channel("trailer.9.wheel.lift.offset", i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::trailer_channel_wheel_lift_offset, 9>, nullptr);
	}
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_world_placement, SCS_U32_NIL, SCS_VALUE_TYPE_dplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_world_placement>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_velocity, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_local_linear_velocity>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_velocity, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_local_angular_velocity>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_linear_acceleration, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_local_linear_acceleration>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_local_angular_acceleration, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_local_angular_acceleration>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cabin_offset, SCS_U32_NIL, SCS_VALUE_TYPE_fplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_cabin_offset>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_velocity, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_cabin_angular_velocity>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cabin_angular_acceleration, SCS_U32_NIL, SCS_VALUE_TYPE_fvector, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_cabin_angular_acceleration>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_head_offset, SCS_U32_NIL, SCS_VALUE_TYPE_fplacement, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_head_offset>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_speed, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_speed>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_engine_rpm, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_engine_rpm>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_engine_gear, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_engine_gear>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_displayed_gear, SCS_U32_NIL, SCS_VALUE_TYPE_s32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_displayed_gear>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_steering, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_input_steering>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_throttle, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_input_throttle>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_brake, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_input_brake>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_input_clutch, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_input_clutch>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_steering, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_effective_steering>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_throttle, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_effective_throttle>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_brake, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_effective_brake>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_effective_clutch, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_effective_clutch>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_cruise_control, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_cruise_control>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_slot, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_hshifter_slot>, nullptr);
	for (uint32_t i = 0; i < metadata::truck_channel_hshifter_selector::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_hshifter_selector, i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_hshifter_selector>, nullptr);
	}
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_parking_brake, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_parking_brake>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_motor_brake, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_motor_brake>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_retarder_level, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_retarder_level>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_brake_air_pressure>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_brake_air_pressure_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_air_pressure_emergency, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_brake_air_pressure_emergency>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_brake_temperature, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_brake_temperature>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_fuel>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_fuel_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel_average_consumption, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_fuel_average_consumption>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_fuel_range, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_fuel_range>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_adblue, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_adblue>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_adblue_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_adblue_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_oil_pressure>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_oil_pressure_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_oil_pressure_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_oil_temperature, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_oil_temperature>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_water_temperature>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_water_temperature_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_water_temperature_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_battery_voltage>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_battery_voltage_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_battery_voltage_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_electric_enabled, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_electric_enabled>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_engine_enabled, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_engine_enabled>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_lblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_lblinker>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_rblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_rblinker>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_hazard_warning, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_hazard_warning>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_lblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_lblinker>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_rblinker, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_rblinker>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_parking, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_parking>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_low_beam, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_low_beam>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_high_beam, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_high_beam>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_front, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_aux_front>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_aux_roof, SCS_U32_NIL, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_aux_roof>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_beacon, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_beacon>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_brake, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_brake>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_light_reverse, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_light_reverse>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wipers, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wipers>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_dashboard_backlight, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_dashboard_backlight>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_differential_lock, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_differential_lock>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_lift_axle>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_lift_axle_indicator, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_lift_axle_indicator>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_trailer_lift_axle>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_trailer_lift_axle_indicator, SCS_U32_NIL, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_trailer_lift_axle_indicator>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_engine, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wear_engine>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_transmission, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wear_transmission>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_cabin, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wear_cabin>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_chassis, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wear_chassis>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wear_wheels, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wear_wheels>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_odometer, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_odometer>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_distance, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_navigation_distance>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_time, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_navigation_time>, nullptr);
	register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_navigation_speed_limit, SCS_U32_NIL, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_navigation_speed_limit>, nullptr);
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_susp_deflection::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_susp_deflection, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_susp_deflection>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_on_ground::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_on_ground, i, SCS_VALUE_TYPE_bool, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_on_ground>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_substance::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_substance, i, SCS_VALUE_TYPE_u32, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_substance>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_velocity::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_velocity, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_velocity>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_steering::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_steering, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_steering>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_rotation::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_rotation, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_rotation>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_lift::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_lift>, nullptr);
	}
	for (uint32_t i = 0; i < metadata::truck_channel_wheel_lift_offset::max_count; i++) {
		register_for_channel(SCS_TELEMETRY_TRUCK_CHANNEL_wheel_lift_offset, i, SCS_VALUE_TYPE_float, SCS_TELEMETRY_CHANNEL_FLAG_none, store<metadata::truck_channel_wheel_lift_offset>, nullptr);
	}
}
