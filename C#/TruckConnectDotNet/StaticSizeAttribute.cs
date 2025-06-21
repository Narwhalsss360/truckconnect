namespace TruckConnect
{
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
    public class StaticSizeAttribute(UInt32 staticSize) : Attribute
    {
        public readonly UInt32 StaticSize = staticSize;
    }
}
