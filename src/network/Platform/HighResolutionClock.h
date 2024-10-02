#pragma once

#include "Platform/RootObject.h"
#include "Platform/Time.h"

namespace Quazal {
    class HighResolutionClock : public RootObject {
        public:
        HighResolutionClock() {}
        Time& GetTime();
    };
}
