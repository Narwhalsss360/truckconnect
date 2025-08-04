namespace TruckConnect
{
    public struct Version
    {
        public static readonly Version CurrentVersion = new(0, 1, 0);

        public uint Patch;
        public uint Minor;
        public uint Major;

        public Version(uint major, uint minor, uint patch)
        {
            Major = major;
            Minor = minor;
            Patch = patch;
        }

        public Version(UInt32 versionUuint)
            : this(versionUuint & 0xFF, (versionUuint >> 8) & 0xFF, (versionUuint >> 16) & 0xFF) {}

        public Version()
            : this(0, 0, 0) {}

        public UInt32 ToUuint()
            => Patch | Minor << 8 | Major << 16;

        public override string ToString()
            => $"{Major}.{Minor}.{Patch}";
    }
}
