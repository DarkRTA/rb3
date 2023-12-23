#ifndef QUAZAL_HIGHRESOLUTIONCLOCK_HPP
#define QUAZAL_HIGHRESOLUTIONCLOCK_HPP
#include "time.hpp"

namespace Quazal {
    class HighResolutionClock : public Time {
    public:
        void GetTime();
    };
}

#endif
