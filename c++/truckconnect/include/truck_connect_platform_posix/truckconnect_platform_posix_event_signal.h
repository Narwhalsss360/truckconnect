#pragma once
#include "truckconnect_platform_posix.h"
#include <ctime>
#include <locale>
#include <mutex>
#include <pthread.h>

namespace truckconnect {
    namespace platform {
        namespace event_signal {
            struct user_space_signal {
                bool signaled;

                std::mutex mutex = {};

                pthread_t main_id = pthread_t();

                user_space_signal(bool initial_state, pthread_t main_id)
                    : signaled(initial_state), main_id(main_id) {}
            };

            using signal = user_space_signal*;

            constexpr const signal INVALID_SIGNAL = nullptr;

            using error_int = int;

            using timeout_int = uint32_t;

            constexpr const timeout_int NO_TIMEOUT = static_cast<uint32_t>(-1);

            static inline error_int last_error() {
                return 0;
            }

            enum class signal_state {
                not_signaled,
                signaled,
                error
            };

            static inline signal create_signal(bool initial_state = false) {
                return new user_space_signal(initial_state, pthread_self());
            }

            static signal_state wait(const signal& signal, timeout_int timeout = NO_TIMEOUT) {
                std::clock_t end = std::clock() + (timeout * CLOCKS_PER_SEC) / 1000;

                do {
                    signal->mutex.lock();
                    if (signal->signaled) {
                        if (pthread_self() != signal->main_id) {
                            signal->signaled = false;
                        }
                        signal->mutex.unlock();
                        return signal_state::signaled;
                    }
                    signal->mutex.unlock();
                } while (std::clock() < end);

                return signal_state::not_signaled;
            }

            static signal_state signaled(const signal& signal) {
                return wait(signal, 0);
            }

            static bool set(const signal& signal) {
                signal->mutex.lock();
                signal->signaled = true;
                signal->mutex.unlock();
                return true;
            }

            static bool reset(const signal& signal) {
                signal->mutex.lock();
                signal->signaled = false;
                signal->mutex.unlock();
                return true;
            }

            static inline bool destroy_signal(const signal& signal) {
                delete signal;
                return true;
            }
        }
    }
}
