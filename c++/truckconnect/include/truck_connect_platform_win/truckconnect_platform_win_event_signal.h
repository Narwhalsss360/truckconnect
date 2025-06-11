#pragma once
#include "truckconnect_platform_win.h"

namespace truckconnect {
    namespace platform {
        namespace event_signal {
            using signal = HANDLE;

            constexpr const signal INVALID_SIGNAL = NULL;

            using error_int = truckconnect::platform::error_int;

            using timeout_int = DWORD;

            constexpr const timeout_int NO_TIMEOUT = INFINITE;

            static inline error_int last_error() {
                return GetLastError();
            }

            enum class signal_state {
                not_signaled,
                signaled,
                error
            };

            static inline signal create_signal(bool initial_state = false, const char* const name = "") {
                return CreateEventA(NULL, initial_state ? TRUE : FALSE, initial_state ? TRUE : FALSE, name);
            }

            static signal_state wait(const signal& signal, timeout_int timeout = NO_TIMEOUT) {
                switch (WaitForSingleObject(signal, timeout))
                {
                case WAIT_TIMEOUT:
                    return signal_state::not_signaled;
                case WAIT_OBJECT_0:
                    return signal_state::signaled;
                case WAIT_FAILED:
                default:
                    return signal_state::error;
                }
            }

            static signal_state signaled(const signal& signal) {
                return wait(signal, 0);
            }

            static bool set(const signal& signal) {
                return SetEvent(signal) == TRUE;
            }

            static bool reset(const signal& signal) {
                return ResetEvent(signal) == TRUE;
            }

            static inline bool destroy_signal(const signal& signal) {
                return CloseHandle(signal) == TRUE;
            }
        }
    }
}