from sys import argv, stderr
import dataclasses
from dataclasses import Field, asdict, is_dataclass
from types import NoneType
from typing import Annotated, Any, Optional
from socket import gethostbyname
from pathlib import Path
from json import dumps, loads, JSONEncoder
from time import sleep
from npycli import CLI, Command, EmptyEntriesError, ParsingError, CLIError, CommandArgumentError
from npycli.parameters import Alias, CommandParameter, Description, ParameterKind, ParseHooks
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
        return TelemetryID(int(s))
    except ValueError:
        ...

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


def load_definitions(deffile: Path) -> list[DataDefinition]:
    if not deffile.exists():
        raise FileExistsError(f"{deffile} does not exist")

    definitions: list[DataDefinition] = []
    with open(deffile, "r", encoding="utf-8") as deffile_io:
        for definition in loads(deffile_io.read()):
            members: list[DataMember] = []
            for member_dct in definition["members"]:
                members.append(DataMember(TelemetryID(member_dct["id"]), member_dct["trailer_count"]))
            definitions.append(DataDefinition(definition["id"], members))
    return definitions


def write_definitions(deffile: Path, definitions: list[DataDefinition]) -> None:
    with open(deffile, "w", encoding="utf-8") as deffile_io:
        deffile_io.write(
            dumps(
                [asdict(definition) for definition in definitions],
                indent=4,
                cls=TelemetryIDJSONEncoder
            )
        )


def type_from_str(s: str) -> type:
    if not isinstance(t := globals().get(s.strip()), type):
        raise ParsingError(f"{s} is not a type.")
    return t


cli: CLI = CLI(
    "truckconnect util",
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
def telemetry(
    telemetry_id: Annotated[Optional[TelemetryID], Alias("telemetry-id", private=True), Description("The telemetry id name to show information for.")] = None,
    oneline: Annotated[Optional[bool], Description("Output telemetry information in one line.")] = None
) -> None:
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


@cli.cmd("get-version", help="Get the version of this client, and then the truckconnect server.")
def get_version(
    hostname: Annotated[str, Description("Hostname of computer with truckconnect server running.")] = "127.0.0.1",
    socket_timeout: Annotated[Optional[float], Alias("socket-timeout", private=True), Description("Socket operation timeout in seconds.")] = None
) -> str | None:
    print(f"Client version: {str(VERSION)}")
    with Connection(gethostbyname(hostname)) as connection:
        if socket_timeout and socket_timeout > 0:
            connection.socket.settimeout(socket_timeout)
        try:
            print(f"Server version: {str(connection.get_version())}")
        except KeyboardInterrupt:
            return "\n^C"


@cli.cmd("fetch-telemetry", help="Fetch a specific telemetry")
def fetch_telemetry(
    telemetry_id: Annotated[TelemetryID, Alias("telemetry-id", private=True), Description("The telemetry id to fetch.")],
    hostname: Annotated[str, Description("Hostname of computer with truckconnect server running.")] = "127.0.0.1",
    listen: Annotated[Optional[float], Description("Specify a listent interval in seconds to continually fetch. Default will only fetch once.")] = None,
    *,
    index: Annotated[Optional[int], Alias("trailer-index"), Description("The trailer index to get telemetry for. Must be used only for trailer telemetries and cannot be used with count.")] = None,
    count: Annotated[Optional[int], Alias("trailer-count"), Description("The trailer count to get telemetry for. Must be used only for trailer telemetries and cannot be used with index.")] = None,
    socket_timeout: Annotated[Optional[float], Alias("socket-timeout", private=True), Description("Socket operation timeout in seconds.")] = None
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
        if socket_timeout and socket_timeout > 0:
            connection.socket.settimeout(socket_timeout)
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
def define(
    id: Annotated[int, Description("The id to assign to this definition."), ParseHooks(None, lambda id: min(max(0, id), 255))],
    *members: Annotated[DataMember, Description("The data members. Formats: 'TelemetryID' or 'TelemetryID[<count>]'.")],
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    overwrite: Annotated[bool, Description("Overwrite existing definition with same id.")] = False
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    definitions: list[DataDefinition] = load_definitions(deffile) if deffile.exists() else []
    existing: DataDefinition | None = next(filter(lambda d: d.id == id, definitions), None)
    if existing is not None:
        if not overwrite:
            raise CommandArgumentError(f"A definition with id {id} already exists.")
        definitions.remove(existing)

    definitions.append(DataDefinition(id, list(members)))
    write_definitions(deffile, definitions)


@cli.cmd(help="Show data definition by id, or all (default, no id)")
def definition(
    id: Annotated[Optional[int], Description("The id of the definition to show information for. Default is all.")] = None,
    *,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    oneline: Annotated[Optional[bool], Description("Output definition information in one line.")] = None
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        return

    definitions: list[DataDefinition] = load_definitions(deffile)

    if id is None:
        printer = oneline_data_definition if oneline or (oneline is None) else wrap_dc_str
        for definition in definitions:
            print(printer(definition))
        return

    try:
        printer = oneline_data_definition if oneline or (oneline is not None) else wrap_dc_str
        print(printer(next(filter(lambda d: d.id == id, definitions))))
    except StopIteration:
        raise CommandArgumentError(f"{id} not defined.")


@cli.cmd(help="Undefine a definition")
def undefine(
    id: Annotated[int, Description("The id of the definition to undefine.")],
    *,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        raise CommandArgumentError(f"Definition file {deffile} does not exist")
    definitions: list[DataDefinition] = load_definitions(deffile)

    try:
        i, _ = next(filter(lambda i_d: i_d[1].id == id, enumerate(definitions)))
        definitions.pop(i)
        print(f"Undefined definition {id}")
    except StopIteration:
        raise CommandArgumentError(f"{id} not defined.")
    write_definitions(deffile, definitions)


@cli.cmd("fetch-definition", help="Fetch and already defined definition")
def fetch_definition(
    id: Annotated[int, Description("The id of the definition to fetch.")],
    hostname: Annotated[str, Description("Hostname of computer with truckconnect server running.")] = "127.0.0.1",
    listen: Annotated[Optional[float], Description("Specify a listent interval in seconds to continually fetch. Default will only fetch once.")] = None,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    socket_timeout: Annotated[Optional[float], Alias("socket-timeout", private=True), Description("Socket operation timeout in seconds.")] = None
) -> str | None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        raise CommandArgumentError(f"Definition file {deffile} does not exist")
    definitions: list[DataDefinition] = load_definitions(deffile)

    try:
        definition: DataDefinition = next(filter(lambda d: d.id == id, definitions))
    except StopIteration:
        raise CommandArgumentError(f"{id} not defined.")

    with Connection(gethostbyname(hostname)) as connection:
        if socket_timeout and socket_timeout > 0:
            connection.socket.settimeout(socket_timeout)
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


@cli.cmd(name='help', help='Show help for a command or all commands.')
def help_cmd(
    command_name: Optional[str] = None,
    parameter_name: Optional[str] = None,
    /,
    extended: Annotated[bool, Description("Show extended information.")] = False
) -> str:
    def type_name(t: type) -> str:
        if t == NoneType:
            return str(None)
        return t.__name__

    def annotation_preview(parameter: CommandParameter) -> str:
        if parameter.annotation_preview:
            return parameter.annotation_preview
        out: str = ""
        for i, t in enumerate(parameter.argument_types):
            out += type_name(t)
            if i != len(parameter.argument_types) - 1:
                out += " | "
        return out

    def default_preview(parameter: CommandParameter) -> str | None:
        if parameter.default == parameter.empty:
            return None
        if parameter.default_preview:
            return parameter.default_preview
        return repr(parameter.default)

    def basic_parameter_help(parameter: CommandParameter) -> str:
        if (
            parameter.default != parameter.empty and
            parameter.argument_types[0] == bool and
            parameter.kind in (ParameterKind.POSITIONAL_OR_KEYWORD, ParameterKind.KEYWORD_ONLY)
        ):
            return (
                "["
                    f"{parameter.name}: "
                    f"{annotation_preview(parameter)} = {default_preview(parameter)}"
                "]"
            )
        else:
            return (
                "<"
                f"{"*" if parameter.kind == ParameterKind.VAR_POSITIONAL else ""}"
                f"{"**" if parameter.kind == ParameterKind.VAR_KEYWORD else ""}"
                f"{parameter.name}: "
                f"{annotation_preview(parameter)}"
                f"{"" if (default := default_preview(parameter)) is None else f" = {default}"}"
                ">"
            )

    def extended_parameter_help(parameter: CommandParameter) -> str:
        tabstr = TAB_CHARS
        out = tabstr
        for i, name in enumerate(parameter.names):
            out += name
            if i != len(parameter.names) - 1:
                out += " "
        out += "\n"

        tabstr = TAB_CHARS * 2
        out += f"{tabstr}Kind: {parameter.kind.name}\n"
        out += f"{tabstr}Annotation: {annotation_preview(parameter)}\n"

        out += f"{tabstr}Types:\n"
        for i, t in enumerate(parameter.argument_types):
            out += f"{tabstr}{TAB_CHARS}{type_name(t)}"
            if i != len(parameter.argument_types) - 1:
                out += "\n"

        if (default := default_preview(parameter)) is not None:
            out += f"\n{tabstr}Default: {default}"

        if parameter.parse_hooks is not None:
            out += f"\n{tabstr}Parse Hooks:"
            if parameter.parse_hooks.pre is not None:
                out += f"\n{tabstr}{TAB_CHARS}Pre-Hook: {getattr(parameter.parse_hooks.pre, "__name__", "...")}"
            if parameter.parse_hooks.post is not None:
                out += f"\n{tabstr}{TAB_CHARS}Post-Hook: {getattr(parameter.parse_hooks.post, "__name__", "...")}"
            if parameter.parse_hooks.err is not None:
                out += f"\n{tabstr}{TAB_CHARS}Error-Hook: {getattr(parameter.parse_hooks.err, "__name__", "...")}"

        if parameter.description:
            out += f"\n{tabstr}Description: {parameter.description.replace("\n", f"\n{tabstr}")}"

        return out

    def basic_command_help(command: Command) -> str:
        out: str = f"{command.name} "
        last_positional_only_index: int = -1
        for i, parameter in enumerate(command.parameters):
            if parameter.kind == ParameterKind.POSITIONAL_ONLY:
                last_positional_only_index = i
            else:
                break

        for i, parameter in enumerate(command.parameters):
            out += basic_parameter_help(parameter)
            if i == last_positional_only_index:
                out += " /"
            if i != len(command.parameters) - 1:
                out += " "
        return out

    def extended_command_help(command: Command) -> str:
        out: str = ""
        for i, name in enumerate(command.names):
            out += name
            if i != len(command.names) - 1:
                out += " "
        out += "\n"

        out += "Parameters:\n"
        for i, parameter in enumerate(command.parameters):
            out += extended_parameter_help(parameter)
            if i != len(command.parameters) - 1:
                out += "\n"

        return out

    command_help, parameter_help = (extended_command_help, extended_parameter_help) if extended else (basic_command_help, basic_parameter_help)

    if command_name is None:
        out: str = ""
        for i, command in enumerate(cli.commands):
            out += f"{command_help(command)}"
            if i != len(cli.commands) - 1:
                out += "\n"
        return out

    if (command := cli.get_command(command_name)) is None:
        return f"{command_name} is not a command."

    if parameter_name is not None:
        if (parameter := next(filter(lambda p: parameter_name in p.names, command.parameters)), None) is None:
            return f"'{parameter_name}' is not a parameter"
        return parameter_help(parameter)
    return command_help(command)


@cli.retvals()
def retvals(command: Command, retval: Any | None) -> None:
    if retval is not None:
        if isinstance(retval, str):
            print(f"{command.name}:{'\n' if '\n' in retval else ""}{retval}")
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
