from sys import argv, stderr
import dataclasses
from os import get_terminal_size
from dataclasses import Field, asdict, is_dataclass
from types import NoneType
from typing import Annotated, Any, Callable, Optional
from socket import gethostbyname
from pathlib import Path
from json import dumps, loads, JSONEncoder
from time import sleep
from npycli import CLI, Command, EmptyEntriesError, ParsingError, CLIError, CommandArgumentError
from npycli.parameters import Alias, CommandParameter, CommandParameterType, Description, ParameterKind, ParseHooks
from npycli.ansi import ANSIControl, CURSOR_UP, CURSOR_HORIZONTAL_ABSOLUTE
from scssdk_truckconnect.truckconnect import VERSION, Telemetry, telemetries
from truckconnect.data import DataDefinition, DataMember, DeserializedType
from truckconnect.telemetry_id import TelemetryID
from truckconnect.connection import Connection, TrailerIndexOrCount
from truckconnect.value_storage import is_value_array_storage, is_value_storage, is_value_vector_storage


class TelemetryIDJSONEncoder(JSONEncoder):
    def default(self, o: Any):
        if isinstance(o, TelemetryID):
            return o.value
        return super().default(o)


class DefinitionsData:
    def __init__(self, deffile: Path, allow_default: bool = False) -> None:
        self.deffile: Path = deffile
        self.definitions: list[DataDefinition] = []
        self.names: dict[str, int] = {}

        if not deffile.exists():
            if allow_default:
                return
            raise FileExistsError(f"{deffile} does not exist")

        with open(deffile, "r", encoding="utf-8") as deffile_io:
            loaded: dict = loads(deffile_io.read())
            if "definitions" not in loaded:
                raise TypeError("deffile must contain \"definitions\" key")

            if not isinstance(loaded["definitions"], list):
                raise TypeError("deffile must \"definitions\" must be a list of DataDefinition")

            for definition in loaded["definitions"]:
                if "members" not in definition:
                    raise TypeError("deffile definition must contain \"members\" key")

                if not isinstance(definition["members"], list):
                    raise TypeError("deffile definition \"members\" must be a list of DataMember")

                members: list[DataMember] = []
                for member_dct in definition["members"]:
                    if "id" not in member_dct or "trailer_count" not in member_dct:
                        raise TypeError("deffile definition \"members\" must be a list of DataMember")
                    members.append(DataMember(TelemetryID(member_dct["id"]), member_dct["trailer_count"]))
                self.definitions.append(DataDefinition(definition["id"], members))

            if "names" not in loaded:
                raise TypeError("deffile must contain \"names\" key.")

            if not isinstance(loaded["names"], dict):
                raise TypeError("deffile \"names\" must be an object mapping strings to ints")
            for k, v in loaded["names"].items():
                if not isinstance(k, str) or not isinstance(v, int):
                    raise TypeError("deffile \"names\" must be an object mapping strings to ints")
            self.names = loaded["names"]

    def index(self, id_or_name: int | str) -> int:
        if isinstance(id_or_name, int):
            try:
                i, _ = next(filter(lambda i_d: i_d[1].id == id, enumerate(self.definitions)))
                return i
            except StopIteration:
                return -1
        if id_or_name not in self.names:
            raise KeyError(f"{id_or_name} is not a registered name.")
        return self.index(self.names[id_or_name])

    def __getitem__(self, id_or_name: int | str) -> DataDefinition | None:
        if isinstance(id_or_name, int):
            return next(filter(lambda d: d.id == id_or_name, self.definitions), None)
        if id_or_name not in self.names:
            raise KeyError(f"{id_or_name} is not a registered name.")
        return self[self.names[id_or_name]]

    def commit(self) -> None:
        with open(self.deffile, "w", encoding="utf-8") as deffile_io:
            deffile_io.write(
                dumps(
                    {
                        "names": self.names,
                        "definitions": [asdict(definition) for definition in self.definitions]
                    },
                    indent=4,
                    cls=TelemetryIDJSONEncoder
                )
            )


class InPlacePrint:
    def __init__(self) -> None:
        self.last_string: str | None = None

    @staticmethod
    def wrap_and_pad_lines(string: str) -> str:
        terminal_size = get_terminal_size()
        lines: list[str] = string.split("\n")
        for i in range(len(lines)):
            if len(lines[i]) > terminal_size.columns:
                this, next = lines[i][:terminal_size.columns], lines[i][terminal_size.columns:]
                lines[i] = this
                lines.insert(i + 1, next)
            lines[i] = f"{lines[i].ljust(terminal_size.columns)}{"" if i == len(lines) - 1 else "\n"}"
        return "".join(lines)

    def print(self, string: str) -> bool:
        string = InPlacePrint.wrap_and_pad_lines(string)
        line_count: int = string.count('\n') + 1
        terminal_size = get_terminal_size()
        if terminal_size.lines < line_count:
            print(string, end="")
            self.last_string = None
            return False

        if self.last_string is None:
            self.last_string = string
            print(string, end="")
            return True

        ANSIControl.send(CURSOR_HORIZONTAL_ABSOLUTE.with_args(0))
        if (cursor_up_count := self.last_string.count("\n")) != 0:
            ANSIControl.send(CURSOR_UP.with_args(cursor_up_count))
        print(string, end="")
        self.last_string = string
        return True

    def __call__(self, string: str) -> bool:
        return self.print(string)


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
    falsy: tuple[str, ...] = "false", "no", "n", "0"

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


def wrap_dc_str(instance, tabs: int = 0, repr_function: Callable[[Any], str] | None = None) -> str:
    repr_function = repr_function or repr
    out: str = f"{type(instance).__name__}(\n"
    fields: tuple[Field[Any], ...] = tuple(filter(lambda f: f.repr, dataclasses.fields(instance)))
    tabstr: str = TAB_CHARS * (tabs + 1)
    for i, field in enumerate(fields):
        out += f"{tabstr}{field.name}="
        value = getattr(instance, field.name)

        if isinstance(value, list):
            if not value:
                out += "[]"
            else:
                out += "[\n"
                for j, item in enumerate(value):
                    out += f"{tabstr}{TAB_CHARS}{wrap_dc_str(item, tabs + 2, repr_function) if is_dataclass(item) else repr_function(item)}"
                    if j != len(value) - 1:
                        out += ","
                    out += "\n"
                out += f"{tabstr}]"
        elif isinstance(value, dict):
            if not value:
                out += "{}"
            else:
                out += "{\n"
                for j, (k, v) in enumerate(value.items()):
                    out += f"{tabstr}{TAB_CHARS}{k}: "
                    out += wrap_dc_str(v, tabs + 2, repr_function) if is_dataclass(v) else f"{tabstr}{TAB_CHARS}{repr_function(v)}"
                    if j != len(value) - 1:
                        out += ","
                    out += "\n"
                out += f"{tabstr}}}"
        else:
            out += wrap_dc_str(value, tabs + 1, repr_function) if is_dataclass(value) else repr_function(value)

        if i != len(fields) - 1:
            out += ","
        out += "\n"
    out += f"{TAB_CHARS * tabs})"
    return out


def oneline_telemetry(telemetry: Telemetry) -> str:
    return f"{TelemetryID(telemetry.id)}({telemetry.id}): {telemetry.telemetry_type}"


def telemetry_value_pretty_print(storage: Any, oneline: bool = False) -> str:
    UNINITIALIZED: str = "<uninitialized>"

    if is_value_storage(storage):
        return telemetry_value_pretty_print(storage[1], oneline) if storage[0] else UNINITIALIZED

    if is_value_array_storage(storage):
        if not storage[0]:
            return UNINITIALIZED
        out: str = "["
        for i, x in enumerate(storage[1]):
            out += telemetry_value_pretty_print(x) if i < storage[2] else UNINITIALIZED
            if i != len(storage[1]) - 1:
                out += ", "
        out += "]"
        return out
    elif is_value_vector_storage(storage):
        out: str = "["
        for i, x in enumerate(storage):
            out += telemetry_value_pretty_print(x)
            if i != len(storage) - 1:
                out += ", "
        out += "]"
        return out
    elif isinstance(storage, list):
        out: str = "["
        for i, x in enumerate(storage):
            out += telemetry_value_pretty_print(x)
            if i != len(storage) - 1:
                out += ", "
        out += "]"
        return out
    elif is_dataclass(storage):
        return str(storage) if oneline else wrap_dc_str(storage, repr_function=telemetry_value_pretty_print)
    else:
        return str(storage)


def defined_data_str(definition: DataDefinition, deserialized_data: list[DeserializedType], oneline: bool) -> str:
    assert len(definition.members) == len(deserialized_data)
    out: str = ""
    for member, data in zip(definition.members, deserialized_data):
        out += f"{member.id.name}: {telemetry_value_pretty_print(data, oneline)}\n"
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

    if not oneline or oneline is None:
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
    socket_timeout: Annotated[Optional[float], Alias("socket-timeout", private=True), Description("Socket operation timeout in seconds.")] = None,
    oneline: Annotated[bool, Description("Print all dataclasses in one line.")] = False,
    show_read: Annotated[bool, Alias("show-read", private=False), Description("Show how many bytes were deserialized.")] = False,
    no_ansi: Annotated[bool, Alias("no-ansi", private=False), Description("Non-ANSI Terminal.")] = False
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
            deserialized, read = connection.request_telemetry(telemetry_id, trailer_index_or_count)
            return f"{f"({read} bytes): " if show_read else ""}{telemetry_value_pretty_print(deserialized, oneline)}"

        if listen < 0:
            raise CommandArgumentError("'listen' must be an integer representing the update interval is seconds.")

        in_place_print: InPlacePrint = InPlacePrint()
        printer = print if no_ansi else in_place_print
        try:
            while True:
                deserialized, read = connection.request_telemetry(telemetry_id, trailer_index_or_count)
                printer(f"{f"({read} bytes): " if show_read else ""}{telemetry_value_pretty_print(deserialized, oneline)}")
                sleep(listen)
        except KeyboardInterrupt:
            return "\n^C"


@cli.cmd(help="Define a data definition, Data member entry: TelemetryID|TelemetryID[count...]")
def define(
    id: Annotated[int, Description("The id/alias to assign to this definition."), ParseHooks(None, lambda id: min(max(0, id), 255))],
    *members: Annotated[DataMember, Description("The data members. Formats: 'TelemetryID' or 'TelemetryID[<count>]'.")],
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    overwrite: Annotated[bool, Description("Overwrite existing definition with same id.")] = False
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH

    definitions_data: DefinitionsData = DefinitionsData(deffile, True)
    existing: DataDefinition | None = next(filter(lambda d: d.id == id, definitions_data.definitions), None)
    if existing is not None:
        if not overwrite:
            raise CommandArgumentError(f"A definition with id {id} already exists.")
        definitions_data.definitions.remove(existing)

    definitions_data.definitions.append(DataDefinition(id, list(members)))
    definitions_data.commit()


@cli.cmd("alias-definition")
def alias_definition(
    id: Annotated[int, Description("The id of the definition to alias.")],
    alias: Annotated[str, Description("Alias of the definition")],
    *,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    overwrite: Annotated[bool, Description("Overwrite existing alias.")] = False
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    definitions_data: DefinitionsData = DefinitionsData(deffile, True)
    if alias in definitions_data.names:
        if not overwrite:
            raise CommandArgumentError(f"Alias ${alias} already exists.")
    definitions_data.names[alias] = id
    definitions_data.commit()


@cli.cmd(help="Show data definition by id, or all (default, no id)")
def definition(
    id: Annotated[Optional[int | str], Description("The id/alias of the definition to show information for. Default is all.")] = None,
    *,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    oneline: Annotated[Optional[bool], Description("Output definition information in one line.")] = None
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        return

    definitions_data: DefinitionsData = DefinitionsData(deffile)

    if id is None:
        printer = oneline_data_definition if oneline or (oneline is None) else wrap_dc_str
        for definition in definitions_data.definitions:
            print(printer(definition))
        print("Aliases:")
        for name, id in definitions_data.names.items():
            print(f"{name}: {id}")
        return

    printer = oneline_data_definition if oneline or (oneline is not None) else wrap_dc_str
    if (definition := definitions_data[id]) is None:
        raise CommandArgumentError(f"{id} not defined.")
    print(printer(definition))


@cli.cmd(help="Undefine a definition")
def undefine(
    id: Annotated[int | str, Description("The id/alias of the definition to undefine.")],
    *,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None
) -> None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        raise CommandArgumentError(f"Definition file {deffile} does not exist")
    definitions_data: DefinitionsData = DefinitionsData(deffile)

    if (index := definitions_data.index(id)) == -1:
        raise CommandArgumentError(f"{id} not defined.")

    definitions_data.definitions.pop(index)
    print(f"Undefined definition {id}")
    definitions_data.commit()


@cli.cmd("fetch-definition", help="Fetch and already defined definition")
def fetch_definition(
    id: Annotated[int | str, Description("The id/alias of the definition to fetch.")],
    hostname: Annotated[str, Description("Hostname of computer with truckconnect server running.")] = "127.0.0.1",
    listen: Annotated[Optional[float], Description("Specify a listent interval in seconds to continually fetch. Default will only fetch once.")] = None,
    *,
    deffile: Annotated[Optional[Path], Description("Definition file to use.")] = None,
    socket_timeout: Annotated[Optional[float], Alias("socket-timeout", private=True), Description("Socket operation timeout in seconds.")] = None,
    oneline: Annotated[bool, Description("Print all dataclasses in one line.")] = False,
    show_read: Annotated[bool, Alias("show-read", private=False), Description("Show how many bytes were deserialized.")] = False,
    no_ansi: Annotated[bool, Alias("no-ansi", private=False), Description("Non-ANSI Terminal.")] = False
) -> str | None:
    deffile = deffile or DEFAULT_DEFINITIONS_PATH
    if not deffile.exists():
        raise CommandArgumentError(f"Definition file {deffile} does not exist")
    definitions_data: DefinitionsData = DefinitionsData(deffile)

    if (definition := definitions_data[id]) is None:
        raise CommandArgumentError(f"{id} not defined.")

    with Connection(gethostbyname(hostname)) as connection:
        if socket_timeout and socket_timeout > 0:
            connection.socket.settimeout(socket_timeout)
        connection.register_data_definition(definition)
        if listen is None:
            connection.request_data_definition(definition)
            deserialized, read = definition.deserialize(connection.collector.bytearray, Connection.DATA_DEFINITION_DATA_START)
            return f"Definition {id}{f" ({read} bytes)" if show_read else ""}:\n" + defined_data_str(definition, deserialized, oneline)

        if listen < 0:
            raise CommandArgumentError("'listen' must be an integer representing the update interval is seconds.")
        try:
            in_place_print: InPlacePrint = InPlacePrint()
            printer = print if no_ansi else in_place_print

            while True:
                connection.request_data_definition(definition)
                deserialized, read = definition.deserialize(connection.collector.bytearray, Connection.DATA_DEFINITION_DATA_START)
                printer(f"Definition {id}{f" ({read} bytes)" if show_read else ""}:\n" + defined_data_str(definition, deserialized, oneline))
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
    def type_name(t: CommandParameterType) -> str:
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
            parameter.argument_types[0] is bool and
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
