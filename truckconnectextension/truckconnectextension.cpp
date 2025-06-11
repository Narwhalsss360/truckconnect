#include "truckconnectextension.h"
#include <scssdk/scssdk_telemetry_event.h>

using std::string;

scs_telemetry_init_params_v101_t init;

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

    console_log(SCS_LOG_TYPE_message, "Initialized!");
    return SCS_RESULT_ok;
}

SCSAPI_VOID scs_telemetry_shutdown() {
    console_log(SCS_LOG_TYPE_message, "Deinitialized!");
}
