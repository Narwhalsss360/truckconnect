namespace TruckConnect
{
    public class DataDefinition
    {
        public readonly DataMember[] Members;

        protected DataDefinition()
        {
            throw new NotImplementedException();
        }

        private DataDefinition(DataMember[] members) =>
            Members = members;

        public static DataDefinition Define(DataMember[] members) =>
            new(members);

        public byte[] AsBytes()
        {
            byte[] bytes = new byte[DataMember.SIZE_AS_BYTES * Members.Length];
            for (int i = 0; i < bytes.Length; i++)
                Array.Copy(Members[i].AsBytes(), 0, bytes, i * DataMember.SIZE_AS_BYTES, DataMember.SIZE_AS_BYTES);
            return bytes;
        }
    }
}

