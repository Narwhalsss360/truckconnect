#pragma once

#ifdef _WIN32
#include "truck_connect_platform_win/truckconnect_platform_win.h"
#include "truck_connect_platform_win/includes.h"
#else
#error "truckconnect_platform: Unknown platform"
#endif
