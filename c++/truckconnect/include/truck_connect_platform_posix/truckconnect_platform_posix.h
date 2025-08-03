#pragma once
#ifdef __unix__
#ifdef _DEBUG
#define TRUCKCONNECT_DEBUG
#endif

#define TRUCKCONNECT_PLATFORM_POSIX
#define TRUCKCONNECT_PLATFORM "posix"
#include <errno.h>
#include <signal.h>

namespace truckconnect {
    namespace platform {
        constexpr const char* const name = TRUCKCONNECT_PLATFORM;

        using error_int = int;

        static inline error_int last_error() {
            return errno;
        }

        static inline void debug_assert(const bool& condition) {
#ifdef TRUCKCONNECT_DEBUG
            if (!condition) {
                while (raise(SIGTRAP) != 0);
            }
#endif
        }
    }
}

#endif
