#ifndef PLATFORM_CRITICALSECTION_H
#define PLATFORM_CRITICALSECTION_H
#include "Platform/RootObject.h"

namespace Quazal {
    class CriticalSection : public RootObject {
    public:
        CriticalSection(unsigned int);
        ~CriticalSection();

        int mutexprimitive;
        int lockchecker;
    };
}

#endif
