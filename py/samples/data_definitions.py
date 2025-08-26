from time import sleep
from os import get_terminal_size
from scssdk_telemetry.scssdk_dataclasses import SCS_TELEMETRY_trailers_count
from scssdk_truckconnect.truckconnect import VERSION, Version
from truckconnect.data import data_definition, member
from truckconnect.telemetry_id import TelemetryID
from truckconnect.connection import Connection


IP: str = "127.0.0.1"
SLEEP_FOR_SECS: float = 0.250


@data_definition(0)
class GameStatus:
    paused: tuple[bool, bool] = member(TelemetryID.ChannelPaused)
    game_time: tuple[bool, int] = member(TelemetryID.ChannelGameTime)
    local_scale: tuple[bool, float] = member(TelemetryID.ChannelLocalScale)


@data_definition(1)
class GaugeCluster:
    engine_enabled: tuple[bool, bool] = member(TelemetryID.TruckChannelEngineEnabled)
    electric_enabled: tuple[bool, bool] = member(TelemetryID.TruckChannelElectricEnabled)
    engine_rpm: tuple[bool, float] = member(TelemetryID.TruckChannelEngineRpm)
    speed: tuple[bool, float] = member(TelemetryID.TruckChannelSpeed)
    light_lblinker: tuple[bool, bool] = member(TelemetryID.TruckChannelLightLblinker)
    light_rblinker: tuple[bool, bool] = member(TelemetryID.TruckChannelLightRblinker)
    cargo_damage: list[tuple[bool, float]] = member(TelemetryID.TrailerChannelCargoDamage, SCS_TELEMETRY_trailers_count)


def main() -> None:
    # Or use connection.connect(), connection.disconnect() for manual resource management.
    with Connection(IP) as connection:
        version: Version = connection.get_version()
        if version.major != VERSION.major or version.minor != VERSION.minor:
            print(f"Version mismatch Client:{VERSION}, Server: {version}")
            return

        connection.register_data_definition(GameStatus)
        connection.register_data_definition(GaugeCluster)
        while True:
            try:
                game_status: GameStatus | None = connection.request_data_definition(GameStatus)
                assert game_status is not None
                gauge_cluster: GaugeCluster | None = connection.request_data_definition(GaugeCluster)
                assert gauge_cluster is not None

                if game_status.paused[1]:
                    print("<paused>")
                    sleep(SLEEP_FOR_SECS)
                    continue

                if not gauge_cluster.electric_enabled[1]:
                    print("<off>")
                    sleep(SLEEP_FOR_SECS)
                    continue

                print(
                    f"{f"{gauge_cluster.speed[1]:0.2f}" if gauge_cluster.speed[0] else "---"} m/s | "
                    f"{f"{gauge_cluster.engine_rpm[1]:0.0f}" if gauge_cluster.engine_rpm[0] else "---"} rpm | "
                    f"{("<" if gauge_cluster.light_lblinker[1] else "-") if gauge_cluster.light_lblinker[0] else "_"}-{(">" if gauge_cluster.light_rblinker[1] else "-") if gauge_cluster.light_rblinker[0] else "_"}"
                )

                print("Damage Report:")
                for i, (initialized, damage) in enumerate(gauge_cluster.cargo_damage):
                    print(f"\tTrailer {i + 1} Damage: {f"{damage * 100:0.1f}%" if initialized else "N/A"}")
                print("-" * get_terminal_size().columns)

                sleep(SLEEP_FOR_SECS)
            except KeyboardInterrupt:
                print("^C")
                break
        connection.unregister_data_definition(GameStatus)
        connection.unregister_data_definition(GaugeCluster)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("^C")
