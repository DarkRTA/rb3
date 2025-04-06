#include "network/Core/Core.h"
#include "CallContextRegister.h"
#include "Core.h"
#include "Core/SecurityContextManager.h"
#include "Core/SystemComponents.h"
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
            volatile ScopedCS cs(Scheduler::s_csGlobalSystemLock);
            s_uiCoreCount++;
        }
        m_psInstance.SetDelegatorInstance(this);
        m_pScheduler = new (__FILE__, 0x53) Scheduler(8, nullptr);
        if (s_bUsesThreads) {
            m_pScheduler->StartDispatcherThread();
        }
        m_pCallContextRegister = new (__FILE__, 0x59) CallContextRegister();
        m_pSystemComponents = new (__FILE__, 0x5A) SystemComponents();
        m_pSystemComponents->unk2c->RegisterComponent(m_pCallContextRegister);
        m_pSecurityContextManager = new (__FILE__, 0x5C) SecurityContextManager();
        ScopedCS cs(Scheduler::GetInstance()->unk38);
        m_pSystemComponents->unk2c->Initialize();
    }

    Core::~Core() {
        {
            ScopedCS cs(Scheduler::GetInstance()->unk38);
            m_pSystemComponents->unk2c->Terminate();
        }
        m_pSystemComponents->WaitForTerminatedState(-1);
        m_pSystemComponents->unk2c->UnregisterComponent(m_pCallContextRegister);
        delete m_pScheduler;
        delete m_pSystemComponents;
        delete m_pSecurityContextManager;
        volatile ScopedCS cs(Scheduler::s_csGlobalSystemLock);
        s_uiCoreCount--;
    }

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