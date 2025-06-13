#include <truckconnect>
#include <iostream>
#include <chrono>

using std::cout;
using std::to_string;
using namespace truckconnect;
using namespace truckconnect::platform;
using namespace truckconnect::communication;
using namespace truckconnect::data;

constexpr const data_definition_id& gauge_cluster_id = 0;

struct gauge_cluster {
    metadata::channel_game_time::storage_type game_time;
    metadata::truck_channel_engine_rpm::storage_type engine_rpm;
    metadata::truck_channel_speed::storage_type speed;
    metadata::truck_channel_odometer::storage_type odometer;
    metadata::truck_channel_fuel::storage_type fuel;
    metadata::truck_channel_oil_temperature::storage_type oil_temperature;
    metadata::truck_channel_light_lblinker::storage_type light_lblinker;
    metadata::truck_channel_light_rblinker::storage_type light_rblinker;

    void print() {
        cout <<
            (game_time.initialized ? to_string(game_time.value) : "-") << "min | " <<
            (engine_rpm.initialized ? to_string(engine_rpm.value) : "-") << "rpm | " <<
            (odometer.initialized ? to_string(odometer.value) : "-") << "km | " <<
            (fuel.initialized ? to_string(fuel.value) : "-") << "L | " <<
            (oil_temperature.initialized ? to_string(oil_temperature.value) : "-") << "C | " <<
            (light_lblinker.initialized ? (light_lblinker.value ? "<" : "-") : "_") << "-" <<
            (light_rblinker.initialized ? (light_rblinker.value ? ">" : "-") : "_");
    }
};

template<>
struct data_definition<gauge_cluster> {
    static constexpr const data_definition_id& id = gauge_cluster_id;

    static constexpr const data_member members[] = {
        member<metadata::channel_game_time>(offsetof(gauge_cluster, game_time)),
        member<metadata::truck_channel_engine_rpm>(offsetof(gauge_cluster, engine_rpm)),
        member<metadata::truck_channel_speed>(offsetof(gauge_cluster, speed)),
        member<metadata::truck_channel_odometer>(offsetof(gauge_cluster, odometer)),
        member<metadata::truck_channel_fuel>(offsetof(gauge_cluster, fuel)),
        member<metadata::truck_channel_oil_temperature>(offsetof(gauge_cluster, oil_temperature)),
        member<metadata::truck_channel_light_lblinker>(offsetof(gauge_cluster, light_lblinker)),
        member<metadata::truck_channel_light_rblinker>(offsetof(gauge_cluster, light_rblinker))
    };

    static constexpr const data_member_info_container<gauge_cluster> info = {};
};

int data_definition_test() {
    communication_result result;
    connection connection = ::connection("127.0.0.1");
    debug_assert(sockets::initialize());
    debug_assert(communication_result::success == (result = connect(connection)));

    debug_assert(communication_result::success == (result = register_data_definition(
        connection,
        gauge_cluster_id, data_definition<gauge_cluster>::members,
        _countof(data_definition<gauge_cluster>::members
    ))));

    while (true) {

    }

    debug_assert(communication_result::success == (result = unregister_data_definition(connection, gauge_cluster_id)));
    debug_assert(communication_result::success == (result = disconnect(connection)));
    debug_assert(sockets::deinitialize());
    return 0;
}
