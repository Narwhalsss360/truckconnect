/*
* Please see `basictelemetry` or `trailertelemetry` sample first, for some extra explanation on some operations.
*/

#include <cinttypes>
#include <iostream>
#include <thread>
#include <chrono>
#include <truckconnect>
#include <ctime>
#include <string>

constexpr const char* const IP = "127.0.0.1";

template <typename T>
std::string value_or_default(const truckconnect::value_storage<T>& storage, const char* const& uninitialized = "---") {
    if (!storage.initialized) {
        return uninitialized;
    }
    return std::to_string(storage.value);
}

bool once(truckconnect::communication::connection& connection) {
    using std::cout;
    using std::endl;

    using all_channels = truckconnect::metadata::channels;

    all_channels::storage_type channels;

    truckconnect::communication::communication_result result = truckconnect::communication::request<all_channels>(connection, channels);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "request<all_channels>(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return false;
    }

    if (channels.general.channel_paused.value) {
        cout << "<paused>\n";
        return true;
    }

    cout <<
        "time: " << value_or_default(channels.general.channel_game_time) << ' ' <<
        "local scale: " << value_or_default(channels.general.channel_local_scale) << ' ' <<
        "on: " << value_or_default(channels.truck.truck_channel_engine_enabled) << ' ' <<
        value_or_default(channels.truck.truck_channel_engine_rpm) << "rpm " <<
        value_or_default(channels.truck.truck_channel_engine_gear) << ' ' <<
        value_or_default(channels.truck.truck_channel_speed) << "m/s ";

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
