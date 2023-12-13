#ifndef QUAZAL_CRITICALSECTION_HPP
#define QUAZAL_CRITICALSECTION_HPP
#include "rootobject.hpp"

namespace Quazal {
    class CriticalSection : RootObject {
    public:
        CriticalSection(unsigned int);
        ~CriticalSection();

        int mutexprimitive;
        int lockchecker;
    };
}

#endif