#include "vector_collector.h"

namespace truckconnect {
    namespace communication {
        using std::vector;

        using namespace nstreamcom;

        using my_base = vector_collector::my_base;

        using iterator = vector_collector::iterator;

        using const_iterator = vector_collector::const_iterator;

        vector_collector::vector_collector(uint32_t initialize_size)
            : my_base(iterator(), iterator()), _buffer(initialize_size < minimum_size ? minimum_size : initialize_size)
        {
            _decoder.use(
                _buffer.begin(),
                _buffer.end(),
                _buffer.begin(),
                _buffer.begin()
            );
        }

        std::vector<uint8_t>& vector_collector::buffer() {
            return _buffer;
        }

        const std::vector<uint8_t>& vector_collector::buffer() const {
            return _buffer;
        }

        iterator vector_collector::begin() {
            return _buffer.begin();
        }

        iterator vector_collector::end() {
            return _buffer.end();
        }

        const_iterator vector_collector::cbegin() const {
            return _buffer.cbegin();
        }

        const_iterator vector_collector::cend() const {
            return _buffer.cend();
        }

        const uint32_t vector_collector::size() const {
            return static_cast<uint32_t>(_buffer.size());
        }

        bool vector_collector::expand() {
            const uint32_t current_index = index();
            const uint32_t new_size = size() + minimum_size;
            if (_state != collector_states::BUFFER_FULL) {
                _buffer.reserve(growth(new_size));
            } else {
                _buffer.resize(growth(new_size));
            }
            
            notify(current_index);
            return true;
        }

        const uint32_t vector_collector::index() {
            return static_cast<uint32_t>(_decoder.position() - _decoder.begin());
        }

        void vector_collector::notify(const uint32_t& index) {
            _decoder.use(
                _buffer.begin(),
                _buffer.end(),
                _buffer.begin() + index,
                _buffer.begin() + (index == 0 ? 0 : index - 1)
            );

            expanded();
        }

        const uint32_t vector_collector::growth(uint32_t new_size) {
            if (size() > UINT32_MAX - size() / 2) {
                return UINT32_MAX;
            }

            const uint32_t result = size() + size() / 2;

            if (new_size < result) {
                return new_size;
            }

            return result;
        }
    }
}