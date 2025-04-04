#pragma once
#include "Core.h"
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"

namespace Quazal {
    class Scheduler : public RootObject {
    public:
        static bool CurrentThreadCanWaitForJob();
        static CriticalSection s_csGlobalSystemLock;
        static Scheduler *GetInstance() {
            Core *inst = Core::GetInstance();
            return !inst ? nullptr : inst->m_pScheduler;
            if (!inst)
                return nullptr;
            else
                return inst->m_pScheduler;
        }
    };
}
