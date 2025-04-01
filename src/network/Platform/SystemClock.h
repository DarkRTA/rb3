#pragma once
#include "Platform/Time.h"

namespace Quazal {
    class SystemClock {
    public:
        static Time GetTimeImpl(bool);
    };
}