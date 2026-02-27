#ifndef EC_STRING_H
#define EC_STRING_H

#include <MSL_C++/string>
#include <ec/mem.h>
#include <ec/result.h>

typedef std::basic_string<char, std::char_traits<char>, ECAllocator<char> > ECString;

namespace ec {

    class ECOstringstream {
    public:
        ECOstringstream& operator<<(const ECString& str);
        ECOstringstream& operator<<(const char* str);
        ECOstringstream& operator<<(char value);
        ECOstringstream& operator<<(bool value);
        ECOstringstream& operator<<(unsigned long value);
        ECOstringstream& operator<<(long value);
        ECOstringstream& operator<<(unsigned long long value);
        ECOstringstream& operator<<(long long value);
        ECOstringstream& operator<<(int value);

        ECString str() { return m_Buffer; }

    private:
        ECString m_Buffer;
    };

    template <typename T>
    ECString tostring(T value);

    ECString toHexString(unsigned long long value, int digits);

    int hex_encode(const unsigned char* data, size_t length, ECString& dest);
    int hex_decode(const ECString& data, unsigned char* dest, size_t length);

    ECResult xml_escape(const ECString &src, ECString &dest);
    ECResult xml_unescape(const ECString &src, ECString &dest);

}

#endif
