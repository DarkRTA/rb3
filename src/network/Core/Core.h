#pragma once
#include "Core/InstanceControl.h"
#include "Core/PseudoSingleton.h"
#include "Platform/RefCountedObject.h"

namespace Quazal {
    class Scheduler;

    class Core : public RefCountedObject {
    public:
        Core();
        virtual ~Core();

        static bool s_bUsesThreads;
        // lol, gotta love unsafe static casts
        static Core *GetInstance() {
            InstanceControl *inst =
                (InstanceControl *)InstanceControl::s_oInstanceTable
                    .GetInstanceFromVector(3, PseudoSingleton::GetCurrentContext());
            return inst ? (Core *)inst->m_pDelegatorInstance : nullptr;
        }

        Scheduler *m_pScheduler; // 0x8
    };
}