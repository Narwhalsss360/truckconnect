/*
* Please see `basictelemetry` sample first, for some extra explanation on some operations.
*/

#include <cinttypes>
#include <iostream>
#include <thread>
#include <chrono>
#include <truckconnect>
#include <ctime>

constexpr const char* const IP = "127.0.0.1";

bool once(truckconnect::communication::connection& connection) {
    using std::cout;
    using std::endl;

    using trailer_telemetry = truckconnect::metadata::trailer_channel_cargo_damage;
    static_assert(trailer_telemetry::trailer_channel, "Please use a trailer channel telemetry for this sample.");

    //This macro is the maximum number of trailer. You may also use std::array
    trailer_telemetry::storage_type storages[SCS_TELEMETRY_trailers_count];

    truckconnect::communication::communication_result result = truckconnect::communication::request<trailer_telemetry>(connection, storages);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "telemetry request<...>(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }

    //Checking if the game is paused.
    truckconnect::value_storage<bool> paused; //or tuckconnect::metadata::channel_paused::storage_type
    result = truckconnect::communication::request<truckconnect::metadata::channel_paused>(connection, paused);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "paused request<...>(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }

    if (paused.value) {
        cout << "<paused>\n";
        return true;
    }

    for (uint32_t i = 0; i < SCS_TELEMETRY_trailers_count; i++) {
        cout << "trailer " << i << ": ";
        if (!storages[i].initialized) {
            cout << "<uninitialized>\n";
        } else {
            //Please use a telemetry that is a primitve, or overload your own << operator.
            cout << storages[i].value << '\n';
        }
    }
    cout << '\n';
    return true;
}

int main() {
    using std::cout;
    using std::endl;
    using std::clock_t;
    using std::clock;
    using namespace std::chrono_literals;

    constexpr const clock_t RUN_FOR = 5 * 60 * 1000;

    if (!truckconnect::platform::sockets::initialize()) {
        cout << "Platform sockets initialization error" << endl;
        return 1;
    }

    truckconnect::communication::connection connection = truckconnect::communication::connection(IP);
    truckconnect::communication::communication_result result = truckconnect::communication::connect(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "connect(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    clock_t start_time = clock();
    do {
        if (!once(connection)) {
            break;
        }
    } while (clock() - start_time < RUN_FOR);

    result = truckconnect::communication::disconnect(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "disconnect(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    if (!truckconnect::platform::sockets::deinitialize()) {
        cout << "Platform sockets deinitialization error" << endl;
        return 1;
    }

	return 0;
}
