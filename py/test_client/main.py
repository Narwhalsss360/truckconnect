from sys import stderr, argv
from time import time, sleep
from typing import Callable
from truckconnect.connection import CommunicationError, CommunicationResult, Connection, TrailerIndexOrCount
from scssdk_telemetry.scssdk_dataclasses import SCS_TELEMETRY_trailers_count
from scssdk_truckconnect.truckconnect import Version, VERSION
from truckconnect.data import get_definition, data_definition, member
from truckconnect.telemetry_id import TelemetryID
from truckconnect.value_storage import SCSValueType, value_storage_from_bytes, is_value_storage
from truckconnect.master_structure import Master

RUN_FOR_SEC: float = 5 * 60
SLEEP_FOR: float = 0.050


def speed_update(connection: Connection) -> None:
    connection.send_request_for(TelemetryID.ChannelPaused)
    connection.receive_for_request(TelemetryID.ChannelPaused)
    paused_deserialized, _ = value_storage_from_bytes(
        SCSValueType.SCS_VALUE_TYPE_bool,
        connection.collector.bytearray,
        Connection.TELEMETRY_DATA_START
    )
    assert is_value_storage(paused_deserialized, bool)
    _, paused = paused_deserialized


    if paused:
        print("<paused>")
    else:
        connection.send_request_for(TelemetryID.TruckChannelSpeed)
        connection.receive_for_request(TelemetryID.TruckChannelSpeed)
        speed_deserialized, _ = value_storage_from_bytes(
            SCSValueType.SCS_VALUE_TYPE_float,
            connection.collector.bytearray,
            Connection.TELEMETRY_DATA_START
        )
        assert is_value_storage(speed_deserialized, float)
        speed_initialized, speed = speed_deserialized
        print(f"{f"{speed:0.2f}" if speed_initialized else "---"} m/s")


def master_update(connection: Connection) -> None:
    connection.send_request_for(TelemetryID.Master)
    connection.receive_for_request(TelemetryID.Master)
    master, _ = Master.from_bytes(
        connection.collector.bytearray,
        Connection.TELEMETRY_DATA_START
    )

    _, paused = master.channels.general.channel_paused
    if paused:
        print("<paused>")
    else:
        speed_initialized, speed = master.channels.truck.truck_channel_speed
        print(f"{f"{speed:0.2f}" if speed_initialized else "---"} m/s")


def trailer_telemetries_update(connection: Connection) -> None:
    connection.send_request_for(
        TelemetryID.TrailerChannelConnected,
        TrailerIndexOrCount(True, SCS_TELEMETRY_trailers_count)
    )
    connection.receive_for_request(
        TelemetryID.TrailerChannelConnected,
        TrailerIndexOrCount(True, SCS_TELEMETRY_trailers_count)
    )

    connected_storages: list[tuple[bool, bool]] = []
    total_read: int = 0
    for _ in range(SCS_TELEMETRY_trailers_count):
        deserialized, read = value_storage_from_bytes(
            SCSValueType.SCS_VALUE_TYPE_bool,
            connection.collector.bytearray,
            Connection.TELEMETRY_DATA_START + total_read
        )
        total_read += read
        assert is_value_storage(deserialized, bool)
        connected_storages.append(deserialized)

    out: str = ""
    for initialized, connected in connected_storages:
        if initialized:
            out += "Y" if connected else "N"
        else:
            out += "?"
    print(out)


@data_definition(0)
class Definition:
    game_time: tuple[bool, int] = member(telemetry_id=TelemetryID.ChannelGameTime)
    speed: tuple[bool, float] = member(telemetry_id=TelemetryID.TruckChannelSpeed)
    rpm: tuple[bool, float] = member(telemetry_id=TelemetryID.TruckChannelEngineRpm)
    gear: tuple[bool, int] = member(telemetry_id=TelemetryID.TruckChannelEngineGear)
    trailers_connected: list[tuple[bool, bool]] = member(telemetry_id=TelemetryID.TrailerChannelConnected, trailer_count=SCS_TELEMETRY_trailers_count)


def data_definitions_update(connection: Connection) -> None:
    if (definition := get_definition(Definition)) is None:
        assert False

    try:
        connection.request_data_definition(definition)
    except CommunicationError as err:
        if err.communication_result != CommunicationResult.NotRegistered:
            raise err
        connection.register_data_definition(definition)
        data_definitions_update(connection)
        return

    deserialized, _ = definition.deserialize(
        connection.collector.bytearray,
        Connection.DATA_DEFINITION_DATA_START
    )

    data = Definition(*deserialized)
    game_time_initialized, game_time = data.game_time
    speed_initialized, speed = data.speed
    rpm_initialized, rpm = data.rpm
    gear_initialized, gear = data.gear
    trailers_connected: list[tuple[bool, bool]] = data.trailers_connected

    gear_str: str
    if gear_initialized:
        if gear > 0:
            gear_str = f"A{gear}"
        elif gear == 0:
            gear_str = "N"
        else:
            gear_str = f"R{-gear}"
    else:
        gear_str = "---"

    trailers_connected_str: str = ""
    for initialized, connected in trailers_connected:
        if initialized:
            trailers_connected_str += "Y" if connected else "N"
        else:
            trailers_connected_str += "?"

    print(
        f"Time: {game_time if game_time_initialized else "---"} | "
        f"{f"{speed:0.2f}" if speed_initialized else "---"} m/s | "
        f"{f"{rpm:0.0f}" if rpm_initialized else "---"} rpm | "
        f"{gear_str} | "
        f"{trailers_connected_str}"
    )


UPDATERS: dict[str, Callable[[Connection], None]] = {
    "speed": speed_update,
    "master": master_update,
    "trailer": trailer_telemetries_update,
    "definitions": data_definitions_update
}


def main(connection: Connection) -> None:
    version: Version = connection.get_version()
    print(f"Server: {version}, Client: {VERSION}")
    if version.major != VERSION.major or version.minor != VERSION.minor:
        print("Version mismatch", file=stderr)
        return
    if version.patch < VERSION.patch:
        print("out-patched server", file=stderr)

    updater: Callable[[Connection], None]
    if len(argv) < 2:
        updater = master_update
        print(f"Using default updater, Available are {UPDATERS.keys()}")
    else:
        name: str = argv[1].lower()
        if name in UPDATERS:
            updater = UPDATERS[name]
        else:
            print(f"{name} is not an updater. Available are {UPDATERS.keys()}", file=stderr)
            return

    start = time()
    while time() - start <= RUN_FOR_SEC:
        updater(connection)
        sleep(SLEEP_FOR)


if __name__ == "__main__":
    try:
        with Connection() as connection:
            main(connection)
    except KeyboardInterrupt:
        print("^C", file=stderr)
