#pragma once
#include <nstreamcom.h>
#include <vector>

namespace truckconnect {
    namespace communication {
        using vector_decoder = nstreamcom::buffered_decoder<std::vector<uint8_t>::iterator>;

        class vector_collector : public nstreamcom::collector<vector_decoder> {
        public:
            using my_base = nstreamcom::collector<vector_decoder>;

            using iterator = std::vector<uint8_t>::iterator;

            using const_iterator = std::vector<uint8_t>::const_iterator;

            static constexpr uint32_t minimum_size = nstreamcom::as_collected_size(1);

            vector_collector(uint32_t initialize_size = minimum_size);

            vector_collector(const vector_collector& other);

            std::vector<uint8_t>& buffer();

            const std::vector<uint8_t>& buffer() const;

            iterator begin();

            iterator end();

            const_iterator cbegin() const;

            const_iterator cend() const;

            const uint32_t size() const;

            void expand();

            nstreamcom::collector_states dynamic_collect(uint8_t byte);

        protected:
            const uint32_t index();

            void notify(const uint32_t& index);
        
            virtual const uint32_t growth(uint32_t new_size);

            std::vector<uint8_t> _buffer;
        };
    }
}
