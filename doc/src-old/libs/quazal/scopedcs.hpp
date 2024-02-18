#ifndef QUAZAL_SCOPEDCS_HPP
#define QUAZAL_SCOPEDCS_HPP
#include "rootobject.hpp"
#include "criticalsection.hpp"

namespace Quazal {
    class ScopedCS : RootObject {
    public:
        ScopedCS(CriticalSection &);
        ~ScopedCS();
    };
}

#endif
