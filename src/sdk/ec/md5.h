#ifndef EC_MD5_H
#define EC_MD5_H

#include <ec/string.h>

namespace ec {
    int md5_sum(const void* data, size_t length, ECString& dest);
}

#endif
