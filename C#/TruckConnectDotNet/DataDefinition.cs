namespace TruckConnect
{
    public class DataDefinition
    {
        public readonly int DefinitionID;

        public readonly DataMember[] Members;

        public readonly Metadata[] MemberMetadata;

        protected DataDefinition()
        {
            throw new NotImplementedException();
        }

        private DataDefinition(int definitionID, DataMember[] members)
        {
            if (definitionID < 0 || definitionID > 255)
                throw new ArgumentException("A definition id must be within [0, 255]", nameof(definitionID));

            Members = members;
            MemberMetadata = new Metadata[members.Length];
            for (int i = 0; i < Members.Length; i++)
            {
                if (Metadata.ByID(Members[i].ID) is not Metadata metadata)
                    throw new ArgumentException("A member ID was invalid", nameof(members));
                if (metadata.TelemetryType != TelemetryType.Channel)
                    throw new NotImplementedException("Only channels are implemented.");
                MemberMetadata[i] = metadata;
            }
        }

        public int StoreInto(byte[] data, int offset, object[] storages)
        {
            if (storages.Length != Members.Length)
                throw new ArgumentException("Storages length does not match members length.", nameof(storages));

            int totalRead = 0;
            for (int i = 0; i < Members.Length; i++)
                totalRead += storages[i].StorageFromBytes(MemberMetadata[i].SCSValueType!.Value, data, offset + totalRead);
            return totalRead;
        }

        public object[] Construct(byte[] data, int offset, out int read)
        {
            object[] storages = new object[Members.Length];
            for (int i = 0; i < storages.Length; i++)
            {
                if (Activator.CreateInstance(MemberMetadata[i].GetGenericStorageTypeDefinition().MakeGenericType(MemberMetadata[i].SCSValueType!.Value.GetTypeOfSCSValueType())) is not object storage)
                    throw new NotImplementedException();
                storages[i] = storage;
            }

            read = StoreInto(data, offset, storages);
            return storages;
        }

        public object[] Construct(byte[] data, int offset) =>
            Construct(data, offset, out int read);

        public static DataDefinition Define(int definitionID, DataMember[] members) =>
            new(definitionID, members);

        public byte[] FormRegistrationRequest()
        {
            byte[] bytes = new byte[1 + 1 + DataMember.SIZE_AS_BYTES * Members.Length];
            bytes[0] = (byte)Connection.RequestType.RegisterDataDefinition;
            bytes[1] = (byte)DefinitionID;
            for (int i = 0; i < Members.Length; i++)
                Array.Copy(Members[i].AsBytes(), 0, bytes, 2 + i * DataMember.SIZE_AS_BYTES, DataMember.SIZE_AS_BYTES);
            return bytes;
        }

        public byte[] FormUnregistrationRequest() =>
            [(byte)Connection.RequestType.UnregisterDataDefinition, (byte)DefinitionID];
    }
}

