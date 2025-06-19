using System.Reflection;

namespace TruckConnect
{
    public class DataDefinition
    {
        public readonly int DefinitionID;

        public readonly DataMember[] Members;

        private DataDefinition()
        {
            DefinitionID = 256;
            Members = Array.Empty<DataMember>();
        }

        protected DataDefinition(int definitionID)
        {
            if (definitionID < 0 || definitionID > 255)
                throw new ArgumentException("A definition id must be within [0, 255]", nameof(definitionID));

            List<DataMember> members = new();
            foreach (PropertyInfo property in GetType().GetProperties())
                if (property.GetCustomAttribute<DataDefinitionMemberAttribute>() is DataDefinitionMemberAttribute member)
                    members.Add(new(member.ID, new(true, member.TrailerCount), property));
            foreach (FieldInfo field in GetType().GetFields())
                if (field.GetCustomAttribute<DataDefinitionMemberAttribute>() is DataDefinitionMemberAttribute member)
                    members.Add(new(member.ID, new(true, member.TrailerCount), field));
            Members = members.ToArray();
        }

        private DataDefinition(int definitionID, DataMember[] members)
        {
            if (definitionID < 0 || definitionID > 255)
                throw new ArgumentException("A definition id must be within [0, 255]", nameof(definitionID));
            DefinitionID = definitionID;
            Members = members;
        }

        public static DataDefinition Define(int definitionID, DataMember[] members) =>
            new(definitionID, members);

        public int StoreInto(byte[] data, int offset, object[] storages)
        {
            if (storages.Length != Members.Length)
                throw new ArgumentException("Storages length does not match members length.", nameof(storages));

            int totalRead = 0;
            for (int i = 0; i < Members.Length; i++)
                totalRead += storages[i].StorageFromBytes(Members[i].Metadata.SCSValueType, data, offset + totalRead);
            return totalRead;
        }

        public int Store(byte[] data, int offset = 0)
        {
            Type thisType = GetType();
            if (thisType == typeof(DataDefinition))
                return 0;

            int totalRead = 0;
            foreach (DataMember member in Members)
            {
                int thisRead;
                if (member.TrailerCount.IndexOrCount > 1)
                    member.Assign(this, data.ConstructStorageArray(member.TrailerCount.IndexOrCount, member.Metadata, offset + totalRead, out thisRead));
                else
                    member.Assign(this, data.ConstructStorage(member.Metadata, offset + totalRead, out thisRead));

                totalRead += thisRead;
            }
            return totalRead;
        }

        public object[] Construct(byte[] data, int offset, out int read)
        {
            object[] storages = new object[Members.Length];
            for (int i = 0; i < storages.Length; i++)
                storages[i] = Members[i].Metadata.ConstructStorage();
            read = StoreInto(data, offset, storages);
            return storages;
        }

        public object[] Construct(byte[] data, int offset) =>
            Construct(data, offset, out int read);

        protected async Task Request(Connection connection)
            => await connection.RequestAsync(this);

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

