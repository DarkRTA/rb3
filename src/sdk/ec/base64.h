#ifndef EC_BASE64_H
#define EC_BASE64_H

#include <ec/result.h>
#include <ec/string.h>

namespace ec {

    ECResult base64_decode(const ECString&, ECString&);
    ECResult base64_encode(const void*, unsigned long, ECString&);

}

#endif
