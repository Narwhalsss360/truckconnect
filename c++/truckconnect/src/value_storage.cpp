#include <value_storage.h>

using std::string;
using std::vector;
using std::copy;

namespace truckconnect {
    void append_bytes(const string& str, vector<uint8_t>& out) {
        out.resize(out.size() + str.size() + 1);
        copy(str.c_str(), str.c_str() + str.size() + 1, out.end() - str.size() - 1);
    }

    bool from_bytes(const vector<uint8_t>& as_bytes, string& out, uint32_t& read, const uint32_t& offset) {
        if (as_bytes.size() <= offset) {
            return false;
        }

        if (as_bytes[offset] == 0) {
            out.clear();
            read = 1;
            return true;
        }

        uint32_t end = offset;
        for (int i = offset; i < as_bytes.size(); i++) {
            if (as_bytes[i] == 0) {
                end = i;
                break;
            }
        }

        if (end == offset) {
            read = 0;
            return false;
        }

        const uint32_t& size = end - offset;
        out.resize(size);
        copy(as_bytes.begin() + offset, as_bytes.begin() + offset + size, out.begin());
        read = size + 1;
        return true;
    }
}

