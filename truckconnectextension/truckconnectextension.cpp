#include "truckconnectextension.h"
#include "register_all.h"
#include "clients.h"
#include <scssdk/scssdk_telemetry_event.h>
#include <ctime>

using std::string;
using std::to_string;
using truckconnect::platform::event_signal::signal;
using truckconnect::platform::event_signal::INVALID_SIGNAL;
using truckconnect::platform::event_signal::create_signal;
using truckconnect::platform::event_signal::destroy_signal;
using truckconnect::master_storage;

scs_telemetry_init_params_v101_t init;
static signal _frame_end_signal = INVALID_SIGNAL;
static master_storage master;

master_storage& current_master() {
    return master;
}

const signal& frame_end_signal() {
    return _frame_end_signal;
}

void console_log(scs_log_type_t type, const string& badge, const string& message) {
    if (init.common.log == nullptr) {
        return;
    }

    if (badge.empty()) {
        init.common.log(type, (string("[truckconnect] ") + message).c_str());
    } else {
        init.common.log(type, (string("[truckconnect] ") + "(" + badge + ") " + message).c_str());
    }
}

SCSAPI_VOID paused(scs_event_t event, const void* const event_info, scs_context_t) {
    master.channels.general.channel_paused.value = true;
}

SCSAPI_VOID started(scs_event_t event, const void* const event_info, scs_context_t) {
    master.channels.general.channel_paused.value = false;
}

SCSAPI_VOID frame_end(scs_event_t event, const void* const event_info, scs_context_t context) {
    using namespace truckconnect::platform::event_signal;
    constexpr const std::clock_t NOTIFY_LAP_INTERVAL = 5000;
    constexpr const std::clock_t NOTIFY_MEMORY_USAGE_INTERVAL = 5 * 60 * 1000;

    static std::clock_t now;
    static std::clock_t last_lap = {};
    static std::clock_t last_memory_notify = {};
    static uint32_t laps = 0;

    now = std::clock();
    switch (signaled(frame_end_signal())) {
    case signal_state::signaled:
        laps++;
        if (now - last_lap >= NOTIFY_LAP_INTERVAL) {
            console_log(SCS_LOG_TYPE_warning, IDENTSTR(frame_end), "Game thread lapped dispatcher thread " + to_string(laps) + " times in the last " + to_string(NOTIFY_LAP_INTERVAL) + "ms.");
            laps = 0;
            last_lap = now;
        }
        break;
    case signal_state::not_signaled:
        if (!set(frame_end_signal())) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(frame_end), "Signal set(...) error: " + to_string(last_error()));
        }
        break;
    case signal_state::error:
        console_log(SCS_LOG_TYPE_error, IDENTSTR(frame_end), "Singal signaled(...) error: " + to_string(last_error()));
        break;
    default:
        console_log(SCS_LOG_TYPE_error, IDENTSTR(frame_end), "Signal signaled(...) unknown result."); break;
    }

    if (now - last_memory_notify >= NOTIFY_MEMORY_USAGE_INTERVAL) {
        console_log(SCS_LOG_TYPE_message, "Master structure memory usage: " + to_string(memory_usage(current_master())) + " bytes.");
        last_memory_notify = now;
    }
}

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
    if (version != SCS_TELEMETRY_VERSION_CURRENT) {
        return SCS_RESULT_unsupported;
    }
    init = *reinterpret_cast<const scs_telemetry_init_params_v101_t* const>(params);

    _frame_end_signal = create_signal();
    if (_frame_end_signal == INVALID_SIGNAL) {
        console_log(SCS_LOG_TYPE_error, "Initialization failure. " + IDENTSTR(_frame_end_signal));
        return SCS_RESULT_generic_error;
    }

    if (!clients_init()) {
        return SCS_RESULT_generic_error;
    }

    scs_result_t result = SCS_RESULT_ok;

    if ((result = init.register_for_event(SCS_TELEMETRY_EVENT_frame_end, frame_end, nullptr)) != SCS_RESULT_ok) {
        return result;
    }
    if ((result = init.register_for_event(SCS_TELEMETRY_EVENT_paused, paused, nullptr)) != SCS_RESULT_ok) {
        return result;
    }
    if ((result = init.register_for_event(SCS_TELEMETRY_EVENT_started, started, nullptr)) != SCS_RESULT_ok) {
        return result;
    }
    register_all(init.register_for_channel, init.register_for_event);

    master.channels.general.channel_paused.value = true;
    master.channels.general.channel_paused.initialized = true;
    console_log(SCS_LOG_TYPE_message, "Initialized!");
    return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
    clients_deinit();

    if (!destroy_signal(frame_end_signal())) {
        console_log(SCS_LOG_TYPE_error, "Deinitialization failure. " + IDENTSTR(_frame_end_signal) + to_string(truckconnect::platform::event_signal::last_error()));
    }

    console_log(SCS_LOG_TYPE_message, "Deinitialized!");
}
