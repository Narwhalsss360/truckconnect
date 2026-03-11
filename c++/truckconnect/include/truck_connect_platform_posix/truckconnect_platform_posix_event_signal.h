#pragma once
#include "truckconnect_platform_posix.h"
#include <cerrno>
#include <cstdint>
#include <ctime>
#include <pthread.h>

namespace truckconnect {
    namespace platform {
        namespace event_signal {
            struct cond_var_bundle {
                pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
                pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
                bool signaled = false;
                pthread_t creator = pthread_t();
            };

            using signal = cond_var_bundle*;

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
                cond_var_bundle* bundle = new cond_var_bundle;
                bundle->creator = pthread_self();
                bundle->signaled = initial_state;
                pthread_cond_init(&bundle->cond, NULL); // Documented to never return an error value
                return bundle;
            }

            static signal_state wait(const signal& signal, timeout_int timeout = NO_TIMEOUT) {
                if (pthread_self() == signal->creator) {
                    return signal_state::error;
                }

                if (pthread_mutex_lock(&signal->mutex) != 0) {
                    return signal_state::error;
                }

                signal_state state;
                if (signal->signaled) {
                    state = signal_state::signaled;
                } else if (timeout == NO_TIMEOUT) {
                    pthread_cond_wait(&signal->cond, &signal->mutex);
                    state = signal_state::signaled;
                } else {
                    timespec ts;
                    ts.tv_sec = timeout / 1000;
                    ts.tv_nsec = (timeout % 1000) * 1000000;
                    if (pthread_cond_timedwait(&signal->cond, &signal->mutex, &ts) == ETIMEDOUT) {
                        state = signal_state::not_signaled;
                    } else {
                        state = signal_state::signaled;
                    }
                }
                signal->signaled = false;

                if (pthread_mutex_unlock(&signal->mutex) != 0) {
                    return signal_state::error;
                }

                return state;
            }

            static signal_state signaled(const signal& signal) {
                return signal->signaled ? signal_state::signaled : signal_state::not_signaled;
            }

            static bool set(const signal& signal) {
                signal->signaled = true;
                pthread_cond_signal(&signal->cond);
                return true;
            }

            static bool reset(const signal& signal) {
                signal->signaled = false;
                return true;
            }

            static inline bool destroy_signal(const signal& signal) {
                delete signal;
                return true;
            }
        }
    }
}
