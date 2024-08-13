#include <ec/string.h>
#include <MSL_C++/cstdio>

static char hextbl[] = "0123456789abcdef";

namespace ec {

    ECOstringstream& ECOstringstream::operator<<(const ECString& str) {
        m_Buffer.append(str);
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(const char* str) {
        m_Buffer.append(str);
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(char value) {
        m_Buffer.append(value);
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(bool value) {
        if (value) {
            m_Buffer.append("1");
        } else {
            m_Buffer.append("0");
        }
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(unsigned long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%u", value);
        m_Buffer.append(buffer);
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%d", value);
        m_Buffer.append(buffer);
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(unsigned long long value) {
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%llu", value);
        m_Buffer.append(buffer);
        return *this;
    }

    ECOstringstream& ECOstringstream::operator<<(long long value) {
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
    ECString tostring<const char*>(const char* value) {
        ECOstringstream stream;
        stream << value;
        return stream.str();
    }

    ECString toHexString(unsigned long long value, int digits) {
        if (digits >= 16) {
            digits = 16;
        }

        char buffer[17];
        snprintf(buffer, sizeof(buffer), "%0*llX", digits, value);
        return ECString(buffer);
    }

}
