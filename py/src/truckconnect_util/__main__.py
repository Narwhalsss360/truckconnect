from sys import argv
import dataclasses
from dataclasses import Field
from typing import Any, Optional
from socket import gethostbyname
from npycli import CLI, Command, EmptyEntriesError, ParsingError, CLIError, CommandArgumentError
from scssdk_truckconnect.truckconnect import Telemetry, telemetries
from truckconnect.data import DeserializedType
from truckconnect.telemetry_id import TelemetryID
from truckconnect.connection import Connection, TrailerIndexOrCount


TAB_CHARS: str = " " * 4


def telemetry_id_from_str(s: str) -> TelemetryID:
    try:
        return TelemetryID[s]
    except KeyError:
        raise ParsingError(f"The following is not a telemetry id: '{s}'")


def bool_from_str(s: str) -> bool:
    s = s.strip().lower()
    truthy: tuple[str, ...] = "true", "yes", "y", "1"
    falsy: tuple[str, ...] = "false", "no", "m", "0"

    if s in truthy:
        return True
    elif s in falsy:
        return False
    raise ParsingError(f"'{s}' is neither truthy or falsy")


def trailer_index_or_count_from_str(s: str) -> TrailerIndexOrCount:
    s = s.strip().lower()
    if s.startswith("index:"):
        return TrailerIndexOrCount(False, int(s[len("index:")]))
    elif s.startswith("count:"):
        return TrailerIndexOrCount(True, int(s[len("index:")]))
    raise ParsingError(f"{s} was an invalid for TrailerIndexOrCount. usage: count:2 or index:2")


def type_from_str(s: str) -> type:
    if not isinstance(t := globals().get(s.strip()), type):
        raise ParsingError(f"{s} is not a type.")
    return t


cli: CLI = CLI(
    parsers={
        TelemetryID: telemetry_id_from_str,
        bool: bool_from_str,
        TrailerIndexOrCount: trailer_index_or_count_from_str,
        type: type_from_str
    }
)


def wrap_dc_str(instance) -> str:
    out: str = f"{type(instance).__name__}(\n"
    fields: tuple[Field[Any], ...] = tuple(filter(lambda f: f.repr, dataclasses.fields(instance)))
    for i, field in enumerate(fields):
        out += f"{TAB_CHARS}{field.name}={repr(getattr(instance, field.name))}"
        if i != len(fields) - 1:
            out += ","
        out += "\n"
    out += ")"
    return out


def oneline_telemetry(telemetry: Telemetry) -> str:
    return f"{TelemetryID(telemetry.id)}({telemetry.id}): {telemetry.telemetry_type}"


@cli.cmd(help="Show all telemetries, or specify a telemetry to show details of")
def telemetry(telemetry_id: Optional[TelemetryID] = None, oneline: Optional[bool] = None) -> None:
    if telemetry_id is None:
        oneline = True if oneline is None else oneline
        if oneline:
            for telemetry in telemetries():
                print(oneline_telemetry(telemetry))
        else:
            for telemetry in telemetries():
                print(wrap_dc_str(telemetry))
        return

    if telemetry_id == TelemetryID.Invalid:
        print("N/A")
        return

    if oneline == False or oneline is None:
        print(wrap_dc_str(telemetries()[telemetry_id.value]))
    else:
        print(oneline_telemetry(telemetries()[telemetry_id.value]))


@cli.cmd("fetch-telemetry", help="Fetch a specific telemetry")
def fetch_telemetry(
    telemetry_id: TelemetryID,
    hostname: str = "127.0.0.1",
    listen: bool = False,
    *,
    index: Optional[int] = None,
    count: Optional[int] = None,
) -> tuple[DeserializedType, int] | str:
    trailer_index_or_count: TrailerIndexOrCount = TrailerIndexOrCount(False, 0)

    if index is not None and count is not None:
        raise CommandArgumentError("'trailer_index' and 'trailer_count' are mutually exclusive")
    if index is not None:
        trailer_index_or_count.index_or_count = index
    if count is not None:
        trailer_index_or_count.is_count = True
        trailer_index_or_count.index_or_count = count

    with Connection(gethostbyname(hostname)) as connection:
        if not listen:
            return connection.request_telemetry(telemetry_id, trailer_index_or_count)
        try:
            while True:
                print(repr(connection.request_telemetry(telemetry_id, trailer_index_or_count)))
        except KeyboardInterrupt:
            return "\n^C"


@cli.retvals()
def retvals(command: Command, retval: Any | None) -> None:
    if retval is not None:
        print(f"{command.name}:{repr(retval)}")


@cli.errors()
def errors(command: Command, exc: Exception) -> None:
    raise exc


def main() -> None:
    try:
        cli.exec(argv[1:])
    except EmptyEntriesError:
        pass
    except CLIError as err:
        print(f'{err.__class__.__name__}: {err.args[0]}')


if __name__ == "__main__":
    main()
