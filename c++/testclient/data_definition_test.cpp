// Pack structures for reinterpret_cast
#ifdef _WIN32
#pragma pack(push, 1)
#include <master_structure.h>
#pragma pack(pop)
#endif

#include <truckconnect>
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::to_string;
using namespace truckconnect;
using namespace truckconnect::platform;
using namespace truckconnect::communication;
using namespace truckconnect::data;

constexpr const data_definition_id& gauge_cluster_id = 0;



#ifdef _WIN32
#pragma pack(push, 1)
#endif
struct gauge_cluster {
    static constexpr const telemetry_id ids[] {
        metadata::channel_game_time::id,
        metadata::truck_channel_engine_rpm::id,
        metadata::truck_channel_speed::id,
        metadata::truck_channel_odometer::id,
        metadata::truck_channel_fuel::id,
        metadata::truck_channel_oil_temperature::id,
        metadata::truck_channel_light_lblinker::id,
        metadata::truck_channel_light_rblinker::id,
        metadata::trailer_channel_connected::id
    };

    storage_type_of<ids[0]> game_time;
    storage_type_of<ids[1]> engine_rpm;
    storage_type_of<ids[2]> speed;
    storage_type_of<ids[3]> odometer;
    storage_type_of<ids[4]> fuel;
    storage_type_of<ids[5]> oil_temperature;
    storage_type_of<ids[6]> light_lblinker;
    storage_type_of<ids[7]> light_rblinker;
    std::array<storage_type_of<ids[8]>, SCS_TELEMETRY_trailers_count> trailer_channel_connected;

    void print() const {
        cout <<
            (game_time.initialized ? to_string(game_time.value) : "-") << "min | " <<
            (engine_rpm.initialized ? to_string(engine_rpm.value) : "-") << "rpm | " <<
            (speed.initialized ? to_string(speed.value * (60 * 60) / 1000) : "-") << "kmh | " <<
            (odometer.initialized ? to_string(odometer.value) : "-") << "km | " <<
            (fuel.initialized ? to_string(fuel.value) : "-") << "L | " <<
            (oil_temperature.initialized ? to_string(oil_temperature.value) : "-") << "C | " <<
            (light_lblinker.initialized ? (light_lblinker.value ? "<" : "-") : "_") << "-" <<
            (light_rblinker.initialized ? (light_rblinker.value ? ">" : "-") : "_") <<
            " | Trailers: ";

        for (const metadata::trailer_channel_connected::storage_type& connected : trailer_channel_connected) {
            cout << (
                connected.initialized ?
                    connected.value ? (
                        "Y"
                    ) : (
                        "N"
                    ) : (
                    "-"
                )
            );
        }
    }
};
#ifdef _WIN32
#pragma pack(pop)
#endif

template<>
struct truckconnect::data::data_definition<gauge_cluster> {
    static constexpr const data_definition_id& id = gauge_cluster_id;

    static constexpr const data_member members[] = {
        data_member(gauge_cluster::ids[0], offsetof(gauge_cluster, game_time)),
        data_member(gauge_cluster::ids[1], offsetof(gauge_cluster, engine_rpm)),
        data_member(gauge_cluster::ids[2], offsetof(gauge_cluster, speed)),
        data_member(gauge_cluster::ids[3], offsetof(gauge_cluster, odometer)),
        data_member(gauge_cluster::ids[4], offsetof(gauge_cluster, fuel)),
        data_member(gauge_cluster::ids[5], offsetof(gauge_cluster, oil_temperature)),
        data_member(gauge_cluster::ids[6], offsetof(gauge_cluster, light_lblinker)),
        data_member(gauge_cluster::ids[7], offsetof(gauge_cluster, light_rblinker)),
        data_member(gauge_cluster::ids[8], offsetof(gauge_cluster, trailer_channel_connected), SCS_TELEMETRY_trailers_count)
    };

    static constexpr const data_member_info_container<gauge_cluster> info = {};
};

struct just_trailer_data {
    metadata::trailer::storage_type trailers[SCS_TELEMETRY_trailers_count];
};

template<>
struct truckconnect::data::data_definition<just_trailer_data> {
    static constexpr const data_definition_id id = 1;

    static constexpr const data_member members[] = {
        member<metadata::trailer>(offsetof(just_trailer_data, trailers), SCS_TELEMETRY_trailers_count)
    };
};

int data_definition_test() {
    communication_result result;
    connection connection = ::connection("127.0.0.1");
    debug_assert(sockets::initialize());
    debug_assert(communication_result::success == (result = connect(connection)));
    debug_assert(communication_result::success == (result = register_data_definition<gauge_cluster>(connection)));
    debug_assert(communication_result::success == (result = register_data_definition<just_trailer_data>(connection)));

    metadata::channel_paused::storage_type paused;
    gauge_cluster cluster;
    just_trailer_data trailer_data;
    while (true) {
        using namespace std::chrono_literals;
        debug_assert((communication_result::success == (result = request<metadata::channel_paused>(connection, paused))));
        if (paused.initialized && paused.value) {
            std::this_thread::sleep_for(65ms);
            continue;
        }

        debug_assert((communication_result::success == (result = request(connection, cluster))));
        debug_assert((communication_result::success == (result = request(connection, trailer_data))));
        cluster.print();
        cout << "\n";

        std::this_thread::sleep_for(25ms);
    }

    debug_assert(communication_result::success == (result = unregister_data_definition<just_trailer_data>(connection)));
    debug_assert(communication_result::success == (result = unregister_data_definition<gauge_cluster>(connection)));
    debug_assert(communication_result::success == (result = disconnect(connection)));
    debug_assert(sockets::deinitialize());
    return 0;
}
