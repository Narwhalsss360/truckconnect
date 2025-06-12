#include <truckconnect>
#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::to_string;
using truckconnect::platform::debug_assert;
using truckconnect::communication::communication_result;
using truckconnect::communication::connection;
using truckconnect::telemetry_id;
using truckconnect::communication::connect;
using truckconnect::communication::send_request_for;
using truckconnect::communication::receive_all;
using truckconnect::communication::disconnect;
using truckconnect::value_storage;
using truckconnect::apply_offset;

truckconnect::platform::sockets::error_int dbg_sockets_last_error() {
    return truckconnect::platform::sockets::last_error();
}

int simple_time_test() {
    debug_assert(truckconnect::platform::sockets::initialize());
    communication_result result = communication_result::success;
    connection connection = ::connection("127.0.0.1");
    debug_assert(communication_result::success == (result = connect(connection)));
    
    constexpr const uint32_t run_for_minutes = 5;
    truckconnect::metadata::channel_game_time::storage_type start_game_time;
    truckconnect::metadata::channel_local_scale::storage_type local_scale;

    while (true) {
        if (!local_scale.initialized) {
            debug_assert(communication_result::success == (result = send_request_for(connection, telemetry_id::channel_local_scale)));
            debug_assert(communication_result::success == (result = receive_all(connection)));
            debug_assert(truckconnect::from_bytes(connection.collector.buffer(), local_scale, 2));
        }

        debug_assert(communication_result::success == (result = send_request_for(connection, telemetry_id::channel_game_time)));
        debug_assert(communication_result::success == (result = receive_all(connection)));
        truckconnect::metadata::channel_game_time::storage_type game_time;
        debug_assert(truckconnect::from_bytes(connection.collector.buffer(), game_time, 2));

        if (!start_game_time.initialized) {
            start_game_time = game_time;
        } else if ((game_time.value - start_game_time.value) / local_scale.value >= run_for_minutes) {
            break;
        }

        cout
            << "Local Scale: " << (local_scale.initialized ? to_string(local_scale.value) : "---") << " "
            << "Game time: " << (game_time.initialized ? to_string(game_time.value) : "---") << " min\n";
    }

    cout << "Done!\n";
    debug_assert(communication_result::success == (result = disconnect(connection)));
    debug_assert(truckconnect::platform::sockets::deinitialize());
    return 0;
}


int main() {
    return simple_time_test();
}
