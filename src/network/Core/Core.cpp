#include "network/Core/Core.h"
#include "CallContextRegister.h"
#include "Core.h"
#include "Platform/MutexPrimitive.h"
#include "Platform/ScopedCS.h"
#include "Scheduler.h"

namespace Quazal {
    unsigned int Core::s_uiCoreCount;
    bool Core::s_bUsesThreads = true;
    bool Core::s_bIsThreadSafe = true;

    Core::Core() : m_psInstance(3) {
        if (s_bUsesThreads && !s_bIsThreadSafe) {
            s_bIsThreadSafe = true;
        }
        if (s_bIsThreadSafe) {
            bool old = MutexPrimitive::s_bNoOp;
            MutexPrimitive::s_bNoOp = false;
            if (old) {
                Scheduler::s_csGlobalSystemLock.EnterImpl();
            }
        } else {
            if (!MutexPrimitive::s_bNoOp) {
                Scheduler::s_csGlobalSystemLock.LeaveImpl();
            }
            MutexPrimitive::s_bNoOp = true;
        }
        {
            ScopedCS cs(Scheduler::s_csGlobalSystemLock);
            s_uiCoreCount++;
        }
        m_psInstance.SetDelegatorInstance(this);
        m_pScheduler = new (__FILE__, 0x53) Scheduler(8, nullptr);
        if (s_bUsesThreads) {
            m_pScheduler->StartDispatcherThread();
        }
        m_pCallContextRegister = new (__FILE__, 0x59) CallContextRegister();
    }

    Core::~Core() {}

    void Core::AcquireInstance() {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        if (!GetInstance()) {
            new (__FILE__, 0x7F) Core(); // but why tho
        } else {
            GetInstance()->AcquireRef();
        }
    }

    void Core::ReleaseInstance() {
        ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        GetInstance()->ReleaseRef();
    }

}