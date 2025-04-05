#pragma once
#include "Core/CallContextRegister.h"
#include "Core/InstanceControl.h"
#include "Core/PseudoSingleton.h"
#include "Platform/RefCountedObject.h"
#include "SecurityContextManager.h"

namespace Quazal {
    class Scheduler;

    class Core : public RefCountedObject {
    public:
        Core();
        virtual ~Core();

        void AcquireInstance();
        void ReleaseInstance();

        static bool s_bUsesThreads;
        static bool s_bIsThreadSafe;
        static unsigned int s_uiCoreCount;
        // lol, gotta love unsafe static casts
        static Core *GetInstance() {
            InstanceControl *inst =
                (InstanceControl *)InstanceControl::s_oInstanceTable
                    .GetInstanceFromVector(3, PseudoSingleton::GetCurrentContext());
            return inst ? (Core *)inst->m_pDelegatorInstance : nullptr;
        }

        Scheduler *m_pScheduler; // 0x8
        CallContextRegister *m_pCallContextRegister; // 0xc
        int unk10; // 0x10 - SystemComponents*
        SecurityContextManager *m_pSecurityContextManager; // 0x14
        PseudoSingleton m_psInstance; // 0x18
    };
}