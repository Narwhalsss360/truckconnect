#include "truckconnectextension.h"
#include <scssdk/scssdk_telemetry_event.h>

using std::string;
using std::to_string;
using truckconnect::platform::event_signal::signal;
using truckconnect::platform::event_signal::INVALID_SIGNAL;
using truckconnect::platform::event_signal::create_signal;
using truckconnect::platform::event_signal::destroy_signal;
using truckconnect::master_storage;

scs_telemetry_init_params_v101_t init;
static signal _frame_end_signal = INVALID_SIGNAL;
master_storage master;

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

SCSAPI_VOID frame_end(scs_event_t event, const void* const event_info, scs_context_t context) {

}

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params) {
    if (version != SCS_TELEMETRY_VERSION_CURRENT) {
        return SCS_RESULT_unsupported;
    }

    init = *reinterpret_cast<const scs_telemetry_init_params_v101_t* const>(params);
    scs_result_t result = SCS_RESULT_ok;

    if ((result = init.register_for_event(SCS_TELEMETRY_EVENT_frame_end, frame_end, nullptr)) != SCS_RESULT_ok) {
        return result;
    }

    _frame_end_signal = create_signal();

    if (_frame_end_signal == INVALID_SIGNAL) {
        console_log(SCS_LOG_TYPE_error, "Initialization failure. " + IDENTSTR(_frame_end_signal));
        return SCS_RESULT_generic_error;
    }

    console_log(SCS_LOG_TYPE_message, "Initialized!");
    return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
    if (!destroy_signal(frame_end_signal())) {
        console_log(SCS_LOG_TYPE_error, "Deinitialization failure. " + IDENTSTR(_frame_end_signal) + to_string(truckconnect::platform::event_signal::last_error()));
    }

    console_log(SCS_LOG_TYPE_message, "Deinitialized!");
}
