from sys import argv, stderr
import dataclasses
from dataclasses import Field, asdict, is_dataclass
from typing import Any, Optional
from socket import gethostbyname
from pathlib import Path
from json import dumps, loads, JSONEncoder
from time import sleep
from npycli import CLI, Command, EmptyEntriesError, ParsingError, CLIError, CommandArgumentError
from scssdk_truckconnect.truckconnect import VERSION, Telemetry, telemetries
from truckconnect.data import DataDefinition, DataMember, DeserializedType
from truckconnect.telemetry_id import TelemetryID
from truckconnect.connection import Connection, TrailerIndexOrCount


class TelemetryIDJSONEncoder(JSONEncoder):
    def default(self, o: Any):
        if isinstance(o, TelemetryID):
            return o.value
        return super().default(o)


TAB_CHARS: str = " " * 4
DEFAULT_DEFINITIONS_PATH: Path = Path.home() / ".tcutildef.json"


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


def extract_name_and_index(name_with_index: str) -> tuple[str, int]:
    if not name_with_index:
        return name_with_index, -1

    if name_with_index[-1] != ']':
        return name_with_index, -1

    try:
        open_bracket_index: int = name_with_index.index('[')
    except ValueError:
        return name_with_index, -1

    try:
        return name_with_index[:open_bracket_index], int(name_with_index[open_bracket_index + 1:-1])
    except ValueError:
        return name_with_index, -1


def data_member_from_str(s: str) -> DataMember:
    id, count = extract_name_and_index(s.strip())
    count = 0 if count == -1 else count
    id = telemetry_id_from_str(id)
    return DataMember(id, count)


class DataMemberVarArgsParser(DataMember):
    def __init__(self, s: str) -> None:
        parsed = data_member_from_str(s)
        super().__init__(parsed.id, parsed.trailer_count)


def type_from_str(s: str) -> type:
    if not isinstance(t := globals().get(s.strip()), type):
        raise ParsingError(f"{s} is not a type.")
    return t


cli: CLI = CLI(
    parsers={
        TelemetryID: telemetry_id_from_str,
        bool: bool_from_str,
        TrailerIndexOrCount: trailer_index_or_count_from_str,
        type: type_from_str,
        Path: lambda s: Path(s),
        DataMember: data_member_from_str
    }
)


def wrap_dc_str(instance, tabs: int = 0) -> str:
    out: str = f"{TAB_CHARS * tabs}{type(instance).__name__}(\n"
    fields: tuple[Field[Any], ...] = tuple(filter(lambda f: f.repr, dataclasses.fields(instance)))
    tabstr: str = TAB_CHARS * (tabs + 1)
    for i, field in enumerate(fields):
        out += f"{tabstr}{field.name}="
        value = getattr(instance, field.name)

        if isinstance(value, list):
            out += "[\n"
            for j, item in enumerate(value):
                out += wrap_dc_str(item, tabs + 2) if is_dataclass(item) else f"{tabstr}{TAB_CHARS}{repr(item)}"
                if j != len(value) - 1:
                    out += ","
                out += "\n"
            out += f"{tabstr}]"
        elif isinstance(value, dict):
            out += "{\n"
            for j, (k, v) in enumerate(value.items()):
                out += f"{tabstr}{TAB_CHARS}{k}: "
                out += wrap_dc_str(v, tabs + 2) if is_dataclass(v) else f"{tabstr}{TAB_CHARS}{repr(v)}"
                if j != len(value) - 1:
                    out += ","
                out += "\n"
            out += f"{tabstr}}}"
        else:
            out += wrap_dc_str(value, tabs + 1) if is_dataclass(value) else repr(value)

        if i != len(fields) - 1:
            out += ","
        out += "\n"
    out += f"{TAB_CHARS * tabs})"
    return out


def oneline_telemetry(telemetry: Telemetry) -> str:
    return f"{TelemetryID(telemetry.id)}({telemetry.id}): {telemetry.telemetry_type}"


def defined_data_str(definition: DataDefinition, deserialized_data: list[DeserializedType]) -> str:
    assert len(definition.members) == len(deserialized_data)
    out: str = ""
    for member, data in zip(definition.members, deserialized_data):
        out += f"{member.id.name}: {data}\n"
    return out


def oneline_data_definition(definition: DataDefinition) -> str:
    out: str = f"Definition ({definition.id}): "
    for i, member in enumerate(definition.members):
        out += member.id.name
        if member.trailer_count != 0:
            out += f"[{member.trailer_count}]"
        if i != len(definition.members) - 1:
            out += ", "
    return out


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


@cli.cmd("get-version")
def get_version(hostname: str = "127.0.0.1") -> str | None:
    print(f"Client version: {str(VERSION)}")
    with Connection(gethostbyname(hostname)) as connection:
        try:
            print(f"Server version: {str(connection.get_version())}")
        except KeyboardInterrupt:
            return "\n^C"


@cli.cmd("fetch-telemetry", help="Fetch a specific telemetry")
def fetch_telemetry(
    telemetry_id: TelemetryID,
    hostname: str = "127.0.0.1",
    listen: Optional[float] = None,
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
        if listen is None:
            return connection.request_telemetry(telemetry_id, trailer_index_or_count)

        if listen < 0:
            raise CommandArgumentError(f"'listen' must be an integer representing the update interval is seconds.")
        try:
            while True:
                print(repr(connection.request_telemetry(telemetry_id, trailer_index_or_count)))
                sleep(listen)
        except KeyboardInterrupt:
            return "\n^C"


@cli.cmd(help="Define a data definition, Data member entry: TelemetryID|TelemetryID[count...]")
def define(id: int, *members: DataMemberVarArgsParser, deffile: Optional[Path] = None) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH

    definitions: list[DataDefinition] = []
    if deffile.exists():
        with open(deffile, "r", encoding="utf-8") as deffile_io:
            for definition in loads(deffile_io.read()):
                load_members: list[DataMember] = []
                for member_dct in definition["members"]:
                    load_members.append(DataMember(TelemetryID(member_dct["id"]), member_dct["trailer_count"]))
                definitions.append(DataDefinition(definition["id"], load_members))

    definitions.append(DataDefinition(id, list(members)))

    with open(deffile, "w", encoding="utf-8") as deffile_io:
        deffile_io.write(
            dumps(
                [asdict(definition) for definition in definitions],
                indent=4,
                cls=TelemetryIDJSONEncoder
            )
        )


@cli.cmd(help="Show data definition by id, or all (default, no id)")
def definition(id: Optional[int] = None, *, deffile: Optional[Path] = None, oneline: bool = False) -> None:
    if deffile is None:
        if not DEFAULT_DEFINITIONS_PATH.exists():
            return
        deffile = DEFAULT_DEFINITIONS_PATH

    if not deffile.exists():
        raise CommandArgumentError(f"File {str(deffile)} does not exist.")

    definitions: list[DataDefinition] = []
    with open(deffile, "r", encoding="utf-8") as deffile_io:
        for definition in loads(deffile_io.read()):
            members: list[DataMember] = []
            for member_dct in definition["members"]:
                members.append(DataMember(TelemetryID(member_dct["id"]), member_dct["trailer_count"]))
            definitions.append(DataDefinition(definition["id"], members))

    printer = oneline_data_definition if oneline else wrap_dc_str

    if id is None:
        for definition in definitions:
            print(printer(definition))
        return

    try:
        print(printer(next(filter(lambda d: d.id == id, definitions))))
    except StopIteration:
        raise CommandArgumentError(f"{id} not defined.")


@cli.cmd(help="Undefine a definition")
def undefine(id: int, *, deffile: Optional[Path] = None) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        raise CommandArgumentError(f"File {str(deffile)} does not exist.")

    definitions: list[DataDefinition] = []
    with open(deffile, "r", encoding="utf-8") as deffile_io:
        for definition in loads(deffile_io.read()):
            members: list[DataMember] = []
            for member_dct in definition["members"]:
                members.append(DataMember(TelemetryID(member_dct["id"]), member_dct["trailer_count"]))
            definitions.append(DataDefinition(definition["id"], members))

    try:
        i, _ = next(filter(lambda i_d: i_d[1].id == id, enumerate(definitions)))
        definitions.pop(i)
        print(f"Undefined {id}")
    except StopIteration:
        raise CommandArgumentError(f"{id} not defined.")

    with open(deffile, "w", encoding="utf-8") as deffile_io:
        deffile_io.write(
            dumps(
                [asdict(definition) for definition in definitions],
                indent=4,
                cls=TelemetryIDJSONEncoder
            )
        )


@cli.cmd("fetch-definition", help="Fetch and already defined definition")
def fetch_definition(id: int, hostname: str = "127.0.0.1", listen: Optional[float] = None, deffile: Optional[Path] = None) -> str | None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        raise CommandArgumentError(f"File {str(deffile)} does not exist.")

    definitions: list[DataDefinition] = []
    with open(deffile, "r", encoding="utf-8") as deffile_io:
        for definition_dct in loads(deffile_io.read()):
            members: list[DataMember] = []
            for member_dct in definition_dct["members"]:
                members.append(DataMember(TelemetryID(member_dct["id"]), member_dct["trailer_count"]))
            definitions.append(DataDefinition(definition_dct["id"], members))

    try:
        definition: DataDefinition = next(filter(lambda d: d.id == id, definitions))
    except StopIteration:
        raise CommandArgumentError(f"{id} not defined.")

    with Connection(gethostbyname(hostname)) as connection:
        connection.register_data_definition(definition)
        if listen is None:
            connection.request_data_definition(definition)
            deserialized, _ = definition.deserialize(connection.collector.bytearray, Connection.DATA_DEFINITION_DATA_START)
            return f"Definition {id}:\n" + defined_data_str(definition, deserialized)

        if listen < 0:
            raise CommandArgumentError(f"'listen' must be an integer representing the update interval is seconds.")
        try:
            while True:
                connection.request_data_definition(definition)
                deserialized, _ = definition.deserialize(connection.collector.bytearray, Connection.DATA_DEFINITION_DATA_START)
                print(defined_data_str(definition, deserialized))
                sleep(listen)
        except KeyboardInterrupt:
            return "\n^C"

@cli.retvals()
def retvals(command: Command, retval: Any | None) -> None:
    if retval is not None:
        if isinstance(retval, str):
            print(f"{command.name}:{retval}")
        else:
            print(f"{command.name}:{repr(retval)}")


@cli.errors()
def errors(command: Command, exc: Exception) -> None:
    print(f"An error occurred executing commmand {command.name}: {exc}", file=stderr)
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
