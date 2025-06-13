#pragma once
#include "telemetry_metadata.h"
#include "metadata_functions.h"

namespace truckconnect {
    namespace data {
        using data_definition_id = uint8_t;

        struct data_member {
            const metadata::metadata_value& metadata;

            const uint32_t offset;

            const uint8_t trailer_index;

            constexpr data_member(const metadata::metadata_value& metadata, const uint32_t& offset = 0, const uint8_t trailer_index = static_cast<uint8_t>(metadata::INVALID_TRAILER_INDEX))
                : metadata(metadata), offset(offset), trailer_index(trailer_index) {}
        };

        constexpr const data_member& INVALID_DATA_MEMBER = data_member(metadata::INVALID_METADATA);

        template <typename data_structure>
        struct data_definition;

        template<>
        struct data_definition<void> {
            const data_definition_id& id;

            const data_member* const& members;

            const uint32_t count;

            constexpr data_definition(const data_definition_id& id, const metadata::metadata_value& metadata, const uint32_t& count)
                : id(id), members(members), count(count) {}
        };

        using data_definition_value = data_definition<void>;

        template <uint32_t count>
        constexpr const uint32_t packed_size_of(const data_member (&members)[count], const uint32_t& i = 0) {
            return i == count ? 0 : metadata::packed_size_of(members[i].metadata.id) + packed_size_of(members, i + 1);
        }

        template <uint32_t count>
        constexpr const bool constant_sized(const data_member (&members)[count], const uint32_t& i = 0) {
            return i == count ? true : (members[i].metadata.constant_size ? constant_sized(members, i + 1) : false);
        }

        template <uint32_t count>
        constexpr const uint32_t sum_of_sizes(const data_member (&members)[count], const uint32_t& i = 0) {
            return i == count ? 0 : members[i].metadata.storage_size + sum_of_sizes(members, i + 1);
        }

        template <uint32_t count>
        constexpr const bool unique_offsets(const data_member(&members)[count], const uint32_t& start = 0, const uint32_t& end = 1) {
            return
                start == count ? (
                    true
                ) : (
                    end == count ? (
                        unique_offsets(members, start + 1, start + 2)
                    ) : (
                        members[start].offset != members[end].offset ? (
                            unique_offsets(members, start, end + 1)
                        ) : (
                            false
                        )
                    )
                );
        }

        template <uint32_t count>
        constexpr const bool contains_invalid_data_member(const data_member (&members)[count], const uint32_t& i = 0) {
            return i == count ? false : (members[i].metadata.id == telemetry_id::invalid ? true : contains_invalid_data_member(members, i + 1));
        }

        template <uint32_t count>
        constexpr const data_member& last_member_in_memory(const data_member (&members)[count], const uint32_t& i = 0, const data_member& last = INVALID_DATA_MEMBER) {
            return i == count ? last : last_member_in_memory(members, i + 1, members[i].offset > last.offset ? members[i] : last);
        }

        template <uint32_t count>
        constexpr const bool is_offset_strictly_monotonically_increasing(const data_member (&members)[count], const uint32_t& i = 0, const data_member& last = INVALID_DATA_MEMBER) {
            return i == count ? (
                true
            ) : (
                members[i].offset < last.offset ? (
                    false
                ) : (
                    is_offset_strictly_monotonically_increasing(members, i + 1, members[i])
                )
            );
        }

        template <uint32_t count>
        constexpr const bool overlapping_members(const data_member (&members)[count], const uint32_t& i = 0) {
            return
                i + 1 == count ? (
                    false
                ) : (
                    members[i].offset + members[i].metadata.storage_size <= members[i + 1].offset ? (
                        overlapping_members(members, i + 1)
                    ) : (
                        true
                    )
                );
        }

        template <typename data_structure>
        struct data_member_info_container {
            static_assert(data_definition<data_structure>::id == 0 ? true : true, "'id' must be a member of a data_definition.");

            static_assert(data_definition<data_structure>::members == 0 ? true : true, "'members' must be a member of a data_definition.");

            static constexpr const bool& contains_invalid_data_member = truckconnect::data::contains_invalid_data_member(data_definition<data_structure>::members);
            static_assert(!contains_invalid_data_member, "A data member is invalid.");

            static constexpr const bool& unique_offsets = truckconnect::data::unique_offsets(data_definition<data_structure>::members);
            static_assert(unique_offsets, "Data members do not have unique offsets.");

            static constexpr const uint32_t& packed_size = packed_size_of(data_definition<data_structure>::members);
            static_assert(packed_size < sizeof(data_structure), "Size of members is bigger than structure.");

            static constexpr const bool& is_packed = packed_size == sizeof(data_structure);

            static constexpr const bool& is_constant_size = constant_sized(data_definition<data_structure>::members);

            static constexpr const uint32_t& sum_of_sizes = ::truckconnect::data::sum_of_sizes(data_definition<data_structure>::members);

            static constexpr const data_member& last_member_in_memory = truckconnect::data::last_member_in_memory(data_definition<data_structure>::members);
            static_assert(last_member_in_memory.offset + last_member_in_memory.metadata.storage_size <= sizeof(data_structure), "Last member is past structure memory bounds.");

            static constexpr const bool& is_offset_strictly_monotonically_increasing = truckconnect::data::is_offset_strictly_monotonically_increasing(data_definition<data_structure>::members);

            //Not implemented for non-is_offset_strictly_monotonically_increasing
            static constexpr const bool& overlapping_members = truckconnect::data::overlapping_members(data_definition<data_structure>::members);
            static_assert(is_offset_strictly_monotonically_increasing ? !overlapping_members : true, "Data member sizes/offsets overlap.");
        };

        template <typename meta>
        constexpr const data_member member(const uint32_t& offset, const uint8_t& trailer_index = static_cast<uint8_t>(metadata::INVALID_TRAILER_INDEX)) {
            return data_member(meta::metadata_value, offset, trailer_index);
        }
    }
}

#define TC_DATA_MEMBERS(...) { __VA_ARGS__ }

#define TC_DATA_DEFINITION(type_name, definition_id, definition_members) template<> struct truckconnect::data::data_definition<type_name> { \
        static constexpr const truckconnect::data::data_definition_id id = definition_id; \
        static constexpr const truckconnect::data::data_member members[] = definition_members; \
        using info_container = truckconnect::data::data_member_info_container<type_name>; \
        info_container static_check; \
    }
