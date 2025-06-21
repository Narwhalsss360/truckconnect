namespace TruckConnect
{
    public class ErrorResponseException(string? message = null, Exception? inner = null) : Exception(message, inner)
    {}
}

