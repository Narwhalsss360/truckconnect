#include <truckconnect>
#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::to_string;
using namespace truckconnect;
using namespace platform;
using namespace communication;

sockets::error_int dbg_sockets_last_error() {
    return sockets::last_error();
}

int busy_request_test() {
    debug_assert(sockets::initialize());
    communication_result result = communication_result::success;
    connection connection = ::connection("127.0.0.1");
    debug_assert(communication_result::success == (result = connect(connection)));
    
    constexpr const uint32_t run_for_minutes = 5;
    metadata::channel_game_time::storage_type start_game_time;
    metadata::channel_game_time::storage_type game_time;
    metadata::channel_local_scale::storage_type local_scale;
    std::array<metadata::trailer_channel_connected::storage_type, SCS_TELEMETRY_trailers_count> trailer_connected;

    while (true) {
        if (!local_scale.initialized) {
            debug_assert(communication_result::success == (result = request<metadata::channel_local_scale>(
                connection,
                [&](const metadata::channel_local_scale::storage_type& received) {
                    local_scale = received;
                }
            )));
            debug_assert(from_bytes(connection.collector.buffer(), local_scale, connection::DATA_START));
        }

        debug_assert(communication_result::success == (result = request<metadata::channel_game_time>(connection, game_time)));
        debug_assert(communication_result::success == (result = request<metadata::trailer_channel_connected>(connection, trailer_connected)));

        if (!start_game_time.initialized) {
            start_game_time = game_time;
        } else if ((game_time.value - start_game_time.value) / local_scale.value >= run_for_minutes) {
            break;
        }

        cout
            << "Local Scale: " << (local_scale.initialized ? to_string(local_scale.value) : "---") << " "
            << "Game time: " << (game_time.initialized ? to_string(game_time.value) : "---") << " min ";

        cout << '|';
        for (int i = 0; i < SCS_TELEMETRY_trailers_count; i++) {
            cout
                << (trailer_connected[i].initialized ?
                (trailer_connected[i].value ? "-" : " ") :
                "?");
        }

        cout << "\n";
    }

    cout << "Done!\n";
    debug_assert(communication_result::success == (result = disconnect(connection)));
    debug_assert(sockets::deinitialize());
    return 0;
}
