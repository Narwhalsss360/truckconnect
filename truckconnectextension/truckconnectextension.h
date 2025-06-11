#pragma once
#include <truckconnect.h>
#include <scssdk/scssdk.h>
#include <scssdk/scssdk_telemetry.h>
#include <string>

void console_log(scs_log_type_t type, const std::string& badge, const std::string& message);

static void console_log(scs_log_type_t type, const std::string& message) {
    console_log(type, "", message);
}
