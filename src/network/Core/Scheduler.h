#pragma once
#include "Platform/CriticalSection.h"

namespace Quazal {
    class Scheduler {
    public:
        static bool CurrentThreadCanWaitForJob();
        static CriticalSection s_csGlobalSystemLock;
    };
}
