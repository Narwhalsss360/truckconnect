#pragma once
#ifdef PICO_RP2040
#define TRUCKCONNECT_DEBUG
#if defined(_DEBUG) && !defined(TRUCKCONNECT_DEBUG) && !defined(NDEBUG)
#define TRUCKCONNECT_DEBUG
#endif

#define TRUCKCONNECT_PLATFORM_RP2040
#define TRUCKCONNECT_PLATFORM "rp2040"
#include <errno.h>
#include <assert.h>

namespace truckconnect {
    namespace platform {
        constexpr const char* const name = TRUCKCONNECT_PLATFORM;

        using error_int = int;

        static inline error_int last_error() {
            return errno;
        }

        static inline void debug_assert(const bool& condition) {
#ifdef TRUCKCONNECT_DEBUG
            assert(condition);
#endif
        }
    }
}

#endif
