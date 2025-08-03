#pragma once

#if defined(_WIN32)
#include "truck_connect_platform_win/truckconnect_platform_win.h"
#include "truck_connect_platform_win/includes.h"
#elif defined(__unix__)
#include "truck_connect_platform_posix/truckconnect_platform_posix.h"
#include "truck_connect_platform_posix/includes.h"
#else
#error "truckconnect_platform: Unknown platform"
#endif
