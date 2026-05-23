#ifndef RVL_EC_DK_H
#define RVL_EC_DK_H

#include <ec/result.h>
#include <revolution/ec/ec.h>

namespace ec {
    ECResult init(ECNameValue *, unsigned long);
    ECResult shutdown();
}

#endif