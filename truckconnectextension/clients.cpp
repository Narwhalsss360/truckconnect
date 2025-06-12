#include "clients.h"
#include <thread>

using std::to_string;
using std::thread;
using namespace truckconnect::platform;
using namespace truckconnect::platform::event_signal;

sockets::socket listener = sockets::INVALID;
thread dispatcher;
volatile bool stop = false;
void dispatcher_start();

void cleanup_listener() {
    if (listener == sockets::INVALID) {
        return;
    }

    if (closesocket(listener) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(cleanup_listener), "closesocket(listener) error: " + to_string(sockets::last_error()));
    }

    listener = sockets::INVALID;
}

bool clients_init() {
    if (!sockets::initialize()) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "Slatform sockets initialization failure.");
        return false;
    }

    listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listener == sockets::INVALID) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "socket(...) creation failure " + to_string(sockets::last_error()));
        return false;
    }

    sockaddr_in all;
    all.sin_family = AF_INET;
    *reinterpret_cast<uint32_t* const>(&all.sin_addr) = 0;
    all.sin_port = htons(truckconnect::communication::PORT);

    if (bind(listener, reinterpret_cast<sockaddr* const>(&all), sizeof(all)) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "bind(...) failure " + to_string(sockets::last_error()));
        cleanup_listener();
        return false;
    }

    if (!sockets::nonblocking(listener)) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "nonblocking(...) failure " + to_string(sockets::last_error()));
        cleanup_listener();
        return false;
    }

    if (listen(listener, LISTENER_BACKLOG) == sockets::ERROR_RESULT) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_init), "listen(...) failure " + to_string(sockets::last_error()));
        cleanup_listener();
        return false;
    }

    dispatcher = thread(dispatcher_start);
    stop = false;
    return true;
}

void dispatcher_start() {
    do {
        //...

        switch (wait(frame_end_signal())) {
            case signal_state::signaled:
                break;
            case signal_state::not_signaled:
                console_log(SCS_LOG_TYPE_warning, IDENTSTR(dispatcher_start), "Unexpected not_signaled result from wait(...) with no timeout.");
                break;
            case signal_state::error:
                console_log(SCS_LOG_TYPE_error, IDENTSTR(dispatcher_start), "Signal wait(...) error: " + to_string(event_signal::last_error()));
                break;
            default:
                break;
        }
    } while (!stop);
}

void clients_deinit() {
    stop = true;
    if (dispatcher.joinable()) {
        if (!set(frame_end_signal())) {
            console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "Signal set(...) error: " + to_string(event_signal::last_error()) + " game thread may block!");
        }
        dispatcher.join();
    }

    cleanup_listener();

    if (!sockets::deinitialize()) {
        console_log(SCS_LOG_TYPE_error, IDENTSTR(clients_deinit), "Sockets deinitialization error.");
    }
}
