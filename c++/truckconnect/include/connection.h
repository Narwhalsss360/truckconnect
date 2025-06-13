#pragma once
#include "truckconnect_platform.h"
#include "vector_collector.h"
#include "telemetry_metadata.h"
#include "byte_converters.h"
#include "data.h"
#include <string>
#include <functional>

namespace truckconnect {
    namespace communication {
        constexpr const uint16_t PORT = 52878;
        
        using namespace platform;
        
        namespace request_types {
            enum request_type : uint8_t {
                none,
                telemetry_id,
                register_data_definition,
                defined_data,
                unregister_data_definition
            };
        }

        using request_types::request_type;

        struct trailer_index_or_count {
            bool is_count : 1;
            uint8_t index_or_count : 7;

            constexpr trailer_index_or_count(const uint8_t& index)
                : is_count(false), index_or_count(index) {}

            explicit constexpr trailer_index_or_count(const bool& is_count, const uint8_t& index_or_count)
                : is_count(is_count), index_or_count(index_or_count) {}

            inline const bool operator==(const trailer_index_or_count& other) const {
                return is_count == other.is_count && index_or_count == other.index_or_count;
            }

            inline const bool operator!=(const trailer_index_or_count& other) const {
                return !(*this == other);
            }
        };

        constexpr const trailer_index_or_count& INVALID_TRAILER_INDEX_OR_COUNT = trailer_index_or_count(false, static_cast<uint8_t>(metadata::INVALID_TRAILER_INDEX));

        constexpr const trailer_index_or_count& DEFAULT_TRAILER_INDEX_OR_COUNT = trailer_index_or_count(false, 0);

        struct connection {
            sockets::socket socket;
            sockaddr_in addr;
            socklen_t addr_len;
            vector_collector collector;
            request_type pending_request;
            uint16_t request_data;
            std::vector<data::data_definition_value> data_definitions;

            static constexpr const uint32_t TELEMTRY_DATA_START = sizeof(pending_request) + sizeof(request_data);

            static constexpr const uint32_t DATA_DEFINITION_DATA_START = sizeof(pending_request) + sizeof(data::data_definition_id);

            static constexpr const uint32_t DEFINED_DATA_DATA_START = sizeof(pending_request) + sizeof(data::data_definition_id);

            inline telemetry_id& request_data_telemetry_id() {
                return apply_offset<telemetry_id>(&request_data, 0);
            }

            inline trailer_index_or_count& request_data_trailer_index_or_count() {
                return apply_offset<trailer_index_or_count>(&request_data, 1);
            }

            inline data::data_definition_id& requst_data_data_definition_id() {
                return apply_offset<data::data_definition_id>(&request_data, 0);
            }

            inline void clear_pending_request() {
                pending_request = request_type::none;
            }

            connection(const std::string& address = "");

            operator const bool() const;
        };

        namespace communication_results {
            enum communication_result {
                success,
                generic_socket_error,
                already_connected,
                not_connected,
                disconnected,
                incomplete,
                collector_error,
                no_pending_request,
                invalid_trailer_index,
                other_request_pending,
                other_telemetry_id_pending,
                other_trailer_index_request_pending,
                received_other_response,
                received_other_telemetry,
                received_other_trailer_index,
                deserialization_failure,
                trailer_index_out_of_bounds,
                trailer_count_out_of_bounds,
                trailer_index_or_count_was_count,
                null_argument,
                empty,
                already_registered,
                other_defined_data_pending,
                not_registered,
                unknown_data
            };
        }

        constexpr const std::array<uint8_t, 3> form_telemetry_request(const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count) {
            return {
                request_type::telemetry_id,
                id,
                *(const uint8_t* const)(&trailer_index_or_count)
            };
        }

        static inline void form_register_data_definition_request(const data::data_definition_id& id, const data::data_member* const& members, const uint32_t& count, std::vector<uint8_t>& formed) {
            formed.reserve(1 + 1 + count * data::data_member_serialization_info::packed_size);
            formed.emplace_back(request_type::register_data_definition);
            formed.emplace_back(id);
            for (uint32_t i = 0; i < count; i++) {
                append_bytes(members[i], formed);
            }
        }

        static inline std::array<uint8_t, 2> form_defined_data_request(const data::data_definition_id& id) {
            return {
                request_type::defined_data,
                id
            };
        }

        using communication_results::communication_result;

        communication_result connect(connection& connection);

        communication_result send_request_for(connection& connection, const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT);

        communication_result receive_one(connection& connection);

        communication_result receive_all(connection& connection, std::function<void(const std::vector<uint8_t>&)> received_callback);

        static inline communication_result receive_all(connection& connection) {
            return receive_all(connection, [](const std::vector<uint8_t>&) {});
        }

        communication_result receive_for_request(connection& connection, const telemetry_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT);

        static inline communication_result receive_for_request(connection& connection, const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT) {
            return receive_for_request(connection, id, [](const std::vector<uint8_t>&) {}, trailer_index_or_count);
        }

        communication_result request(connection& connection, const telemetry_id& id, std::function<void(const std::vector<uint8_t>&)> received_callback, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT);

        static inline communication_result request(connection& connection, const telemetry_id& id, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT) {
            return request(connection, id, [](const std::vector<uint8_t>&) {}, trailer_index_or_count);
        }

        template <typename meta>
        communication_result request(connection& connection, std::function<void(const typename meta::storage_type&)> received_callback, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT) {
            if (trailer_index_or_count.is_count) {
                return communication_result::trailer_index_or_count_was_count;
            }

            communication_result result = request(connection, meta::id, trailer_index_or_count);
            if (result == communication_result::success) {
                typename meta::storage_type destination;
                if (from_bytes(connection.collector.buffer(), destination, connection::TELEMTRY_DATA_START)) {
                    received_callback(destination);
                } else {
                    result = communication_result::deserialization_failure;
                }
            }
            return result;
        }
        
        template <typename meta>
        communication_result request(connection& connection, typename meta::storage_type& destination, const trailer_index_or_count& trailer_index_or_count = DEFAULT_TRAILER_INDEX_OR_COUNT) {
            communication_result result = request(connection, meta::id, trailer_index_or_count);
            if (result == communication_result::success) {
                if (!from_bytes(connection.collector.buffer(), destination, connection::TELEMTRY_DATA_START)) {
                    result = communication_result::deserialization_failure;
                }
            }
            return result;
        }

        template <typename meta, uint32_t trailer_count>
        communication_result request(connection& connection, std::function<void(const typename meta::storage_type (&)[trailer_count])> received_callback) {
            static_assert(trailer_count <= SCS_TELEMETRY_trailers_count, "'count' is over the trailer count limit.");
            static_assert(meta::trailer_channel, "This request overload is only for trailer channels.");

            communication_result result = request(connection, meta::id, trailer_index_or_count(true, trailer_count));
            if (result == communication_result::success) {
                typename meta::storage_type destination[trailer_count];
                if (from_bytes(connection.collector.buffer(), destination, connection::TELEMTRY_DATA_START)) {
                    received_callback(destination);
                } else {
                    result = communication_result::deserialization_failure;
                }
            }
            return result;
        }

        template <typename meta, uint32_t trailer_count>
        communication_result request(connection& connection, typename meta::storage_type (&array)[trailer_count]) {
            static_assert(trailer_count <= SCS_TELEMETRY_trailers_count, "'trailer_count' is over the trailer count limit.");
            static_assert(meta::trailer_channel, "This request overload is only for trailer channels.");

            communication_result result = request(connection, meta::id, trailer_index_or_count(true, trailer_count));
            if (result == communication_result::success) {
                if (!from_bytes(
                    connection.collector.buffer(),
                    array,
                    connection::TELEMTRY_DATA_START)) {
                    result = communication_result::deserialization_failure;
                }
            }
            return result;
        }

        template <typename meta, uint32_t trailer_count>
        communication_result request(connection& connection, std::array<typename meta::storage_type, trailer_count>& array) {
            return request<meta, trailer_count>(
                connection,
                *reinterpret_cast<typename meta::storage_type (* const)[trailer_count]>(array.data())
            );
        }

        communication_result register_data_definition(connection& connection, const data::data_definition_id& id, const data::data_member* const& members, const uint32_t& count);

        communication_result send_request_for(connection& connection, const data::data_definition_id& id);

        communication_result receive_for_request(connection& connection, const data::data_definition_id& id, std::function<void(const void* const)> received_callback);

        communication_result request(connection& connection, const data::data_definition_id& id, std::function<void(const void* const)> received_callback);

        static inline communication_result request(connection& connection, const data::data_definition_id& id) {
            return request(connection, id, [](const void* const) {});
        }

        communication_result unregister_data_definition(connection& connection, const data::data_definition_id& id);

        communication_result disconnect(connection& connection);
    }
}
