#pragma once
#include "scssdk/common/scssdk_telemetry_common_configs.h"
#include "telemetry_metadata.h"
#include "metadata_functions.h"
#include "packed_size.h"
#include "byte_converters.h"

namespace truckconnect {
    namespace data {
        using data_definition_id = uint8_t;

        constexpr const data_definition_id INVALID_DATA_DEFINITION_ID = static_cast<data_definition_id>(-1);

        struct data_member {
            telemetry_id telemetry_id;

            uint32_t offset;

            trailer_index_uint trailer_count;

            constexpr data_member(const truckconnect::telemetry_id& telemetry_id = telemetry_id::invalid, const uint32_t& offset = 0, const trailer_index_uint trailer_count = metadata::INVALID_TRAILER_INDEX)
                : telemetry_id(telemetry_id), offset(offset), trailer_count(trailer_count) {}
        };

        struct data_member_serialization_info {
            static constexpr const bool constant_size = true;

            static constexpr const uint32_t ordered_sizes[] = {
                sizeof(data_member::telemetry_id),
                sizeof(data_member::offset),
                sizeof(data_member::trailer_count)
            };

            static constexpr const uint32_t ordered_offsets[] = {
                offsetof(data_member, telemetry_id),
                offsetof(data_member, offset),
                offsetof(data_member, trailer_count)
            };

            static constexpr const uint32_t packed_size = sum(ordered_sizes);

            static constexpr const uint32_t count = countof(ordered_sizes);

            static_assert(countof(ordered_sizes) == countof(ordered_offsets), "sizes and offsets must be equal count");
        };

        constexpr const data_member INVALID_DATA_MEMBER = data_member(telemetry_id::invalid);

        template <typename data_structure>
        struct data_definition;

        template<>
        struct data_definition<void> {
            data_definition_id id;

            std::vector<data_member> members;

            data_definition(const data_definition_id& id = INVALID_DATA_DEFINITION_ID, const std::vector<data_member>& members = {})
                : id(id), members(members) {}
        };

        using data_definition_value = data_definition<void>;

        template <uint32_t count>
        constexpr const uint32_t packed_size_of(const data_member (&members)[count], const uint32_t& i = 0) {
            return
                i == count ? (
                    0
                ) : (
                    metadata::is_trailer_channel(members[i].telemetry_id) ? (
                        metadata::packed_size_of(members[i].telemetry_id) * members[i].trailer_count
                    ) : (
                        metadata::packed_size_of(members[i].telemetry_id)
                    )
                    + packed_size_of(members, i + 1)
                );
        }

        template <uint32_t count>
        constexpr const bool is_constant_size(const data_member (&members)[count], const uint32_t& i = 0) {
            return i == count ? true : (metadata::is_constant_size(members[i].telemetry_id) ? is_constant_size(members, i + 1) : false);
        }

        template <uint32_t count>
        constexpr const bool has_valid_trailer_count_for_trailer_telemetries(const data_member (&members)[count], const uint32_t& i = 0) {
            return
                i == count ? (
                    true
                ) : (
                    metadata::is_trailer_telemetry(members[i].telemetry_id) ? (
                        members[i].trailer_count > SCS_TELEMETRY_trailers_count ? (
                            false
                        ) : (
                            has_valid_trailer_count_for_trailer_telemetries(members, i + 1)
                        )
                    ) : (
                        has_valid_trailer_count_for_trailer_telemetries(members, i + 1)
                    )
                );
        }

        template <uint32_t count>
        constexpr const bool has_invalid_trailer_count_for_non_trailer_telemetries(const data_member (&members)[count], const uint32_t& i = 0) {
            return
                i == count ? (
                    true
                ) : (
                    metadata::is_trailer_telemetry(members[i].telemetry_id) ? (
                        has_invalid_trailer_count_for_non_trailer_telemetries(members, i + 1)
                    ) : (
                        members[i].trailer_count == static_cast<uint8_t>(metadata::INVALID_TRAILER_INDEX) ? (
                            has_invalid_trailer_count_for_non_trailer_telemetries(members, i + 1)
                        ) : (
                            false
                        )
                    )
                );
        }

        template <uint32_t count>
        constexpr const uint32_t sum_of_sizes(const data_member (&members)[count], const uint32_t& i = 0) {
            return
                i == count ? (
                    0
                ) : (
                    metadata::is_trailer_telemetry(members[i].telemetry_id) ? (
                        metadata::size_of(members[i].telemetry_id) * members[i].trailer_count
                    ) : (
                        metadata::size_of(members[i].telemetry_id)
                    )
                    + sum_of_sizes(members, i + 1)
                );
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
            return i == count ? false : (members[i].telemetry_id == telemetry_id::invalid ? true : contains_invalid_data_member(members, i + 1));
        }

        template <uint32_t count>
        constexpr const data_member& last_member_in_memory(const data_member (&members)[count], const uint32_t& i = 0, const data_member& last = INVALID_DATA_MEMBER) {
            return members[i];
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
                    members[i].offset + metadata::size_of(members[i].telemetry_id) <= members[i + 1].offset ? (
                        overlapping_members(members, i + 1)
                    ) : (
                        true
                    )
                );
        }

        template <typename data_structure>
        struct data_member_info_container {
            using definition = data_definition<data_structure>;

            static_assert(data_definition<data_structure>::id == 0 ? true : true, "'id' must be a member of a data_definition.");

            static_assert(data_definition<data_structure>::members == 0 ? true : true, "'members' must be a member of a data_definition.");

            static constexpr const data_definition_id id = definition::id;

            static constexpr const uint32_t& member_count = sizeof(definition::members) / sizeof(definition::members[0]);

            static constexpr const bool& contains_invalid_data_member = truckconnect::data::contains_invalid_data_member(data_definition<data_structure>::members);
            static_assert(!contains_invalid_data_member, "A data member is invalid.");

            static constexpr const bool& unique_offsets = truckconnect::data::unique_offsets(data_definition<data_structure>::members);
            static_assert(unique_offsets, "Data members do not have unique offsets.");

            static constexpr const uint32_t& packed_size = packed_size_of(data_definition<data_structure>::members);
            static_assert(packed_size <= sizeof(data_structure), "Size of members is bigger than structure.");

            static constexpr const data_member& last_member_in_memory = truckconnect::data::last_member_in_memory(data_definition<data_structure>::members);
            static_assert(last_member_in_memory.offset + metadata::size_of(last_member_in_memory.telemetry_id) <= sizeof(data_structure), "Last member is past structure memory bounds.");

            static constexpr const bool& has_invalid_trailer_count_for_non_trailer_telemetries = truckconnect::data::has_invalid_trailer_count_for_non_trailer_telemetries(data_definition<data_structure>::members);
            static_assert(has_invalid_trailer_count_for_non_trailer_telemetries, "A non-trailer channel has a 'trailer_count' specified.");

            static constexpr const bool& has_valid_trailer_count_for_trailer_telemetries = truckconnect::data::has_valid_trailer_count_for_trailer_telemetries(data_definition<data_structure>::members);
            static_assert(has_valid_trailer_count_for_trailer_telemetries, "A trailer channel has a 'trailer_count' which is invalid.");

            static constexpr const bool& is_offset_strictly_monotonically_increasing = truckconnect::data::is_offset_strictly_monotonically_increasing(data_definition<data_structure>::members);

            static constexpr const bool& overlapping_members = truckconnect::data::overlapping_members(data_definition<data_structure>::members);

            //Not implemented for non-is_offset_strictly_monotonically_increasing
            static_assert(is_offset_strictly_monotonically_increasing ? !overlapping_members : true, "Data member sizes/offsets overlap.");

            static constexpr const bool& is_packed = packed_size == sizeof(data_structure);

            static constexpr const bool& is_constant_size = truckconnect::data::is_constant_size(data_definition<data_structure>::members);

            static constexpr const uint32_t& sum_of_sizes = ::truckconnect::data::sum_of_sizes(data_definition<data_structure>::members);

            static constexpr const bool& reinterpretable = is_offset_strictly_monotonically_increasing && is_constant_size && is_packed && sum_of_sizes == sizeof(data_structure);
        };

        template <typename meta>
        constexpr const data_member member(const uint32_t& offset, const trailer_index_uint& trailer_count = metadata::INVALID_TRAILER_INDEX) {
            return data_member(meta::id, offset, trailer_count);
        }

        constexpr const size_t data_member_ordered_size(const uint32_t& i) {
            return data_member_serialization_info::ordered_sizes[i];
        }

        static inline const uint8_t* const data_member_ordered_offset(const data_member& member, const uint32_t& i) {
            return reinterpret_cast<const uint8_t* const>(&member) + data_member_serialization_info::ordered_offsets[i];
        }

        static inline uint8_t* const data_member_ordered_offset(data_member& member, const uint32_t& i) {
            return reinterpret_cast<uint8_t* const>(&member) + data_member_serialization_info::ordered_offsets[i];
        }

        constexpr const uint32_t data_member_packed_size() {
            return data_member_serialization_info::packed_size;
        }

        static inline void append_bytes(const data_member& member, std::vector<uint8_t>& out, const uint32_t& i = 0) {
            if (i >= data_member_serialization_info::count) {
                return;
            } else if (i == 0) {
                if (out.capacity() - out.size() < data_member_serialization_info::packed_size) {
                    out.reserve(out.size() + data_member_serialization_info::packed_size);
                }
            }

            out.resize(out.size() + data_member_ordered_size(i));
            std::copy(data_member_ordered_offset(member, i), data_member_ordered_offset(member, i) + data_member_ordered_size(i), out.end() - data_member_ordered_size(i));
            append_bytes(member, out, i + 1);
        }

        static inline bool from_bytes(const std::vector<uint8_t>& bytes, data_member& member, const uint32_t& offset = 0, const uint32_t& i = 0) {
            constexpr const uint32_t (&ordered_sizes)[data_member_serialization_info::count] = data_member_serialization_info::ordered_sizes;
            if (i >= data_member_serialization_info::count) {
                return true;
            } else if (i == 0) {
                if (bytes.size() - offset < data_member_serialization_info::packed_size) {
                    return false;
                }
            }

            std::copy(
                bytes.cbegin() + offset + sum(ordered_sizes, i),
                bytes.cbegin() + offset + sum(ordered_sizes, i + 1),
                data_member_ordered_offset(member, i)
            );

            return from_bytes(bytes, member, offset, i + 1);
        }

        static inline bool arrange_unsafe(const data_member* const& members, const uint32_t& count, const std::vector<uint8_t>& data, const uint32_t& offset, void* const out) {
            uint32_t at = offset;
            uint32_t read;
            for (uint32_t i = 0; i < count; i++) {
                const uint32_t size = metadata::packed_size_of(members[i].telemetry_id);
                if (at + size > data.size()) {
                    return false;
                }

                if (!truckconnect::from_bytes(members[i].telemetry_id, data, &apply_offset<uint8_t>(out, members[i].offset), at, read)) {
                    return false;
                }
                at += size;
            }

            return true;
        }

        static inline bool arrange_unsafe(const data_definition_value& definition, const std::vector<uint8_t>& data, const uint32_t& offset, void* const out) {
            return arrange_unsafe(definition.members.data(), static_cast<uint32_t>(definition.members.size()), data, offset, out);
        }

        template <typename data_structure>
        bool arrange_recursive(const std::vector<uint8_t>& bytes, const uint32_t& offset, data_structure& out, const uint32_t& i) {
            using definition = data_definition<data_structure>;
            using member_info = data_member_info_container<data_structure>;

            constexpr const member_info info = {};
            uint8_t* const& out_start = reinterpret_cast<uint8_t* const>(&out);
            const data_member& member = definition::members[i];

            if (i == info.member_count) {
                return true;
            }

            uint32_t read;
            if (!truckconnect::from_bytes(member.telemetry_id, bytes, out_start + member.offset, offset, read)) {
                return false;
            }

            return arrange_recursive(bytes, offset + read, out, i + 1);
        }


        template <typename data_structure>
        bool arrange(const std::vector<uint8_t>& bytes, const uint32_t& offset, data_structure& out) {
            using member_info = data_member_info_container<data_structure>;


            if (member_info::reinterpretable) {
                if (bytes.size() - offset >= sizeof(data_structure)) {
                    out = apply_offset<data_structure>(bytes.data(), offset);
                    return true;
                }
            }

            return arrange_recursive(bytes, offset, out, 0);
        }

        static inline bool arrange(const data_definition_value& defintition, const std::vector<uint8_t>& data, const uint32_t& offset, std::vector<uint8_t>& out) {
            uint32_t at = offset;
            uint32_t read;
            for (const data_member& member : defintition.members) {
                const uint32_t size = metadata::packed_size_of(member.telemetry_id);
                if (at + size > data.size()) {
                    return false;
                }

                if (out.size() <= member.offset) {
                    out.resize(out.size() + member.offset + size);
                } else if (out.size() <= member.offset + size) {
                    out.resize(out.size() + member.offset + size);
                }

                if (!truckconnect::from_bytes(member.telemetry_id, data, out.data() + member.offset, at, read)) {
                    return false;
                }
                at += size;
            }

            return true;
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
