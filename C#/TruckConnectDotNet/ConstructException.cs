namespace TruckConnect
{
    public class ConstructException(string? message = null, Exception? inner = null) : Exception(message, inner)
    {}
}
