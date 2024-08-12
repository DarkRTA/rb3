#ifndef EC_STRING_H
#define EC_STRING_H

#include <MSL_C++/string>
#include <ec/mem.h>

typedef std::basic_string<char, std::char_traits<char>, ECAllocator<char> > ECString;

namespace ec {

    int hex_encode(const unsigned char* data, size_t length, ECString& dest);

}

#endif
