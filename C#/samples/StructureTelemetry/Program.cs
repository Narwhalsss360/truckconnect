using System.Diagnostics;
using System.Reflection;
using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(5);

Connection connection = new();
await connection.ConnectAsync();

DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    //A structure telemetry may be requested just by telemplate argument.
    var master = await connection.RequestAsync<MasterStorage>();

    if (master.Channels.General.ChannelPaused.Value)
    {
        Console.WriteLine("<paused>");
        continue;
    }

    Console.Clear();
    Console.SetCursorPosition(0, 0);
    Console.Write("Press any key to refresh.\nMaster:");
    Console.WriteLine(FormatEverything(master, Console.WindowWidth, tabChars: "    "));
    Console.WriteLine("Press any key to refresh");
    Console.ReadKey();
}

connection.Disconnect();

string FormatEverything(dynamic telemetry, int width, string uninitializedString = "<uninitialized>", string tabChars = "  ", int depth = 0)
{
    Type type = telemetry.GetType();
    string @out;
    string tabs = Repeat(tabChars, depth);

    if (type.IsArray)
    {
        @out = "\n";
        for (int i = 0; i < telemetry.Length; i++)
            @out += $"{tabs}{tabChars}[{i}]: " + FormatEverything(telemetry[i], width, uninitializedString, tabChars, depth + 1);
    }
    else if (type.IsTelemetryStructure())
    {
        @out = "\n";
        foreach (FieldInfo field in type.GetFields())
            @out += $"{tabs}{tabChars}{field.Name}: " + FormatEverything(field.GetValue(telemetry), width, uninitializedString, tabChars, depth + 1);
    }
    else if (type.IsStorageType())
    {
        Type genericType = type.GetGenericStorageTypeDefinition()!; //Cannot be null if IsStorageType() == true
        if (genericType == typeof(ValueStorage<>))
        {
            @out = (telemetry.Initialized ? telemetry.Value.ToString() : uninitializedString) + '\n';
        }
        else
        {
            int count = genericType == typeof(ValueArrayStorage<>) ? (int)telemetry.Count : telemetry.Values.Count;
            @out = "\n";
            tabs += tabChars;
            for (int i = 0; i < count; i++)
                @out += $"{tabs}[{i}]: {telemetry.Values[i]}\n";
        }
    }
    else
        @out = "";

    return @out;
}

string Repeat(string c, int count)
{
    string s = string.Empty;
    for (int i = 0; i < count; i++)
        s += c;
    return s;
}

