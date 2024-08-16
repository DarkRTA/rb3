#include <ec/string.h>
#include <ec/vector.h>

#include <MSL_C++/cstdio>

#include "macros.h"
#include "decomp.h"

static char *hextbl = "0123456789abcdef";

namespace ec {

    ECOstringstream &ECOstringstream::operator<<(const ECString &str) {
        m_Buffer.append(str);
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(const char *str) {
        m_Buffer.append(str);
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(char value) {
        m_Buffer.append(value);
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(bool value) {
        if (value) {
            m_Buffer.append("1");
        } else {
            m_Buffer.append("0");
        }
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(unsigned long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%u", value);
        m_Buffer.append(buffer);
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%d", value);
        m_Buffer.append(buffer);
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(unsigned long long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%llu", value);
        m_Buffer.append(buffer);
        return *this;
    }

    ECOstringstream &ECOstringstream::operator<<(long long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%lld", value);
        m_Buffer.append(buffer);
        return *this;
    }

    template <>
    ECString tostring<long>(long value) {
        ECOstringstream stream;
        stream << value;
        return stream.str();
    }

    template <>
    ECString tostring<unsigned long>(unsigned long value) {
        ECOstringstream stream;
        stream << value;
        return stream.str();
    }

    template <>
    ECString tostring<long long>(long long value) {
        ECOstringstream stream;
        stream << value;
        return stream.str();
    }

    template <>
    ECString tostring<unsigned long long>(unsigned long long value) {
        ECOstringstream stream;
        stream << value;
        return stream.str();
    }

    template <>
    ECString tostring<const char *>(const char *value) {
        ECOstringstream stream;
        stream << value;
        return stream.str();
    }

    ECString toHexString(unsigned long long value, int digits) {
        if ((unsigned int)digits >= 17) {
            digits = 16;
        }

        char buffer[17];
        std::snprintf(buffer, sizeof(buffer), "%0*llX", digits, value);
        return ECString(buffer);
    }

    DECOMP_FORCEFUNC(ec_string, ECString, operator+=("a"));

#pragma dont_inline on
    void FORCEFUNC_string_get_pointer() {
        const ECString dummy;
        dummy.get_pointer();
    };
#pragma dont_inline reset

    // template version to force correct stack usage in non-template version
    // due to taking std::insert_iterator as an argument
    template <typename OutIter>
    int hex_encode(const unsigned char *data, size_t length, OutIter dest) {
        const unsigned char *end = data + length;
        int charCount = 0;
        while (data != end) {
            unsigned char a = *data++;
            *dest++ = hextbl[(a >> 4) & 0x0F];
            *dest++ = hextbl[(a >> 0) & 0x0F];
            charCount += 2;
        }

        return charCount;
    }

    int hex_encode(const unsigned char *data, size_t length, ECString &dest) {
        return hex_encode(data, length, std::inserter(dest, dest.end()));
    }

    template <typename InIter, typename OutIter>
    int hex_decode(InIter begin, InIter end, OutIter dest) {
        int charCount = 0;
        int decodedValue = 0;
        int byteCount = 0;
        for (InIter it = begin; it != end;) {
            unsigned int c = *it++;

            unsigned int value = 0;
            if (((c - '0') & 0xFF) <= 9) {
                value = (c - '0');
            } else {
                if (((c - 'a') & 0xFF) <= 5) {
                    value = (c - 'a') + 0xA;
                } else {
                    if (((c - 'A') & 0xFF) <= 5) {
                        value = (c - 'A') + 0xA;
                    }
                }
            }

            if (!(charCount % 2)) {
                decodedValue = value << 4;
            } else {
                decodedValue |= value;
                *dest++ = decodedValue;
                byteCount++;
            }

            charCount++;
        }

        if ((charCount % 2)) {
            *dest++ = decodedValue;
            byteCount++;
        }

        return byteCount;
    }

    int hex_decode(const ECString &data, unsigned char *dest, size_t length) {
        ECVector<char> vec;
        int decoded = hex_decode(data.begin(), data.end(), std::inserter(vec, vec.end()));
        if (decoded < 0) {
            return -1;
        }

        std::memcpy(dest, vec.data(), length);

        decoded = vec.size();
        if (decoded > length) {
            decoded = length;
        }

        return decoded;
    }

}
