/*
* Please see another sample for some extra explanation on some operations.
*/

#include <cinttypes>
#include <iostream>
#include <thread>
#include <chrono>
#include <truckconnect>
#include <ctime>
#include <string>
#include <cstdio>

constexpr const char* const IP = "127.0.0.1";

//Using statements for less typing...
using truckconnect::data::data_definition_id;
using truckconnect::data::data_definition;
using truckconnect::data::data_member;
using truckconnect::data::member;
using truckconnect::metadata::channel_paused;
using truckconnect::metadata::truck_channel_engine_enabled;
using truckconnect::metadata::truck_channel_electric_enabled;
using truckconnect::metadata::truck_channel_engine_rpm;
using truckconnect::metadata::truck_channel_engine_gear;
using truckconnect::metadata::truck_channel_displayed_gear;
using truckconnect::metadata::truck_channel_speed;
using truckconnect::metadata::truck_channel_parking_brake;
using truckconnect::metadata::truck_channel_oil_pressure_warning;
using truckconnect::metadata::truck_channel_battery_voltage_warning;
using truckconnect::metadata::truck_channel_light_lblinker;
using truckconnect::metadata::truck_channel_light_rblinker;
using truckconnect::metadata::trailer_channel_connected;

//Define your structure of data that you'd like.
struct gauge_cluster {
    channel_paused::storage_type paused;
    truck_channel_engine_enabled::storage_type engine_enabled;
    truck_channel_electric_enabled::storage_type electric_enabled;
    truck_channel_engine_rpm::storage_type engine_rpm;
    truck_channel_engine_gear::storage_type engine_gear;
    truck_channel_displayed_gear::storage_type displayed_gear;
    truck_channel_speed::storage_type speed;
    truck_channel_parking_brake::storage_type parking_brake;
    truck_channel_oil_pressure_warning::storage_type oil_pressure_warning;
    truck_channel_battery_voltage_warning::storage_type battery_voltage_warning;
    truck_channel_light_lblinker::storage_type light_lblinker;
    truck_channel_light_rblinker::storage_type light_rblinker;
    trailer_channel_connected::storage_type trailer_connected[SCS_TELEMETRY_trailers_count];
};

//Give your definition an ID, 0-255.
constexpr const data_definition_id GAUGE_CLUSTER_ID = 0;

//Then define a template specialization of data_definition.
template <>
struct truckconnect::data::data_definition<gauge_cluster> {
    //Must define a `static constexpr const data_defintition_id id` member.
    static constexpr const data_definition_id id = GAUGE_CLUSTER_ID;

    //Must define a `static constexpr const data_member[] members` member.
    static constexpr const data_member members[] = {
        member<channel_paused>(offsetof(gauge_cluster, paused)),
        member<truck_channel_engine_enabled>(offsetof(gauge_cluster, engine_enabled)),
        member<truck_channel_electric_enabled>(offsetof(gauge_cluster, electric_enabled)),
        member<truck_channel_engine_rpm>(offsetof(gauge_cluster, engine_rpm)),
        member<truck_channel_engine_gear>(offsetof(gauge_cluster, engine_gear)),
        member<truck_channel_displayed_gear>(offsetof(gauge_cluster, displayed_gear)),
        member<truck_channel_speed>(offsetof(gauge_cluster, speed)),
        member<truck_channel_parking_brake>(offsetof(gauge_cluster, parking_brake)),
        member<truck_channel_oil_pressure_warning>(offsetof(gauge_cluster, oil_pressure_warning)),
        member<truck_channel_battery_voltage_warning>(offsetof(gauge_cluster, battery_voltage_warning)),
        member<truck_channel_light_lblinker>(offsetof(gauge_cluster, light_lblinker)),
        member<truck_channel_light_rblinker>(offsetof(gauge_cluster, light_rblinker)),
        //For trailer data, specify how many trailers you'd like your data for.
        member<trailer_channel_connected>(offsetof(gauge_cluster, trailer_connected), SCS_TELEMETRY_trailers_count)
    };
};

template <typename T>
std::string value_or_default(const truckconnect::value_storage<T>& storage, const char* const& uninitialized = "---") {
    if (!storage.initialized) {
        return uninitialized;
    }
    return std::to_string(storage.value);
}

//Creating an overload for limiting float decimal points.
std::string value_or_default(const truckconnect::value_storage<float>& storage, const char* const& uninitialized = "---") {
    if (!storage.initialized) {
        return uninitialized;
    }
    char buffer[128];
    std::snprintf(buffer, sizeof(buffer), "%.1f", storage.value);
    return std::string(buffer);
}

bool once(truckconnect::communication::connection& connection) {
    using std::cout;
    using std::endl;

    gauge_cluster cluster;
    truckconnect::communication::communication_result result = truckconnect::communication::request<gauge_cluster>(connection, cluster);

    if (cluster.paused.value) {
        cout << "<paused>\n";
        return true;
    }

    int trailers_connected = 0;
    for (int i = 0; i < SCS_TELEMETRY_trailers_count; i++) {
        trailers_connected = i + 1;
        if (!cluster.trailer_connected[i].initialized || !cluster.trailer_connected[i].value) {
            break;
        }
    }

    cout <<
        "engine_enabled: " << value_or_default(cluster.engine_enabled) <<
        "|electric_enabled: " << value_or_default(cluster.electric_enabled) <<
        "|engine_rpm: " << value_or_default(cluster.engine_rpm) <<
        "|engine_gear: " << value_or_default(cluster.engine_gear) <<
        "|displayed_gear: " << value_or_default(cluster.displayed_gear) <<
        "|speed: " << value_or_default(cluster.speed) <<
        "|parking_brake: " << value_or_default(cluster.parking_brake) <<
        "|oil_pressure_warning: " << value_or_default(cluster.oil_pressure_warning) <<
        "|battery_voltage_warning: " << value_or_default(cluster.battery_voltage_warning) <<
        "|light_lblinker: " << value_or_default(cluster.light_lblinker) <<
        "|light_rblinker: " << value_or_default(cluster.light_rblinker) <<
        '|' << trailers_connected << " trailer(s)";

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

    truckconnect::version_t version;
    result = truckconnect::communication::get_version(connection, version);

    if (result != truckconnect::communication::communication_result::success) {
        cout << "get_version(...) failure code : " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    if (version.major != truckconnect::version.major || version.minor != truckconnect::version.minor) {
        cout << "Version mismatch, client:" << std::to_string(truckconnect::version) << ", server:" << std::to_string(version) << endl;
        return 1;
    }

    //Register your data definition, this also does some static checks to avoid foot-guns.
    result = truckconnect::communication::register_data_definition<gauge_cluster>(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "register_data_definition(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

    clock_t start_time = clock();
    do {
        if (!once(connection)) {
            break;
        }
    } while (clock() - start_time < RUN_FOR);

    //Unregister, not really necessary if you're disconnecting right after.
    result = truckconnect::communication::unregister_data_definition<gauge_cluster>(connection);
    if (result != truckconnect::communication::communication_result::success) {
        cout << "unregister_data_definition(...) failure code: " << truckconnect::communication::communication_result_string[result] << endl;
        return 1;
    }

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
