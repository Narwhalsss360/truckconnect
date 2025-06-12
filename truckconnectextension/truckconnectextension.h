#pragma once
#include <truckconnect.h>
#include <scssdk/scssdk.h>
#include <scssdk/scssdk_telemetry.h>
#include <string>

#define IDENTSTR(ident) std::string(#ident)

extern truckconnect::master_storage& current_master();

const truckconnect::platform::event_signal::signal& frame_end_signal();

void console_log(scs_log_type_t type, const std::string& badge, const std::string& message);

static void console_log(scs_log_type_t type, const std::string& message) {
    console_log(type, "", message);
}
