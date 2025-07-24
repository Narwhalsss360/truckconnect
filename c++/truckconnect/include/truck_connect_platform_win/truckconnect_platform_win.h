#pragma once
#ifdef _WIN32
#ifdef _DEBUG
#define TRUCKCONNECT_DEBUG
#endif

#define TRUCKCONNECT_PLATFORM_WIN
#define TRUCKCONNECT_PLATFORM "windows"
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

namespace truckconnect {
    namespace platform {
        constexpr const char* const name = TRUCKCONNECT_PLATFORM;

        using error_int = DWORD;

        static inline error_int last_error() {
            return GetLastError();
        }

        static inline void debug_assert(const bool& condition) {
#ifdef TRUCKCONNECT_DEBUG
            if (!condition) {
                __debugbreak();
            }
#endif
        }
    }
}

#endif
