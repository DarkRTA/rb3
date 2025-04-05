#include "network/Core/CallContextRegister.h"
#include "Core/PeriodicJob.h"
#include "Core/SystemComponent.h"
#include "MethodCallJob.h"
#include "Platform/String.h"
#include "Scheduler.h"

namespace Quazal {
    CallContextRegister::CallContextRegister()
        : SystemComponent("CallContextRegister"), m_uiNextID(1),
          m_pCheckExpiredCallsJob(0) {}

    CallContextRegister::~CallContextRegister() {}

    bool CallContextRegister::BeginInitialization() {
        Start();
        return true;
    }

    inline static const char *FileName() { return __FILE__; }

    inline static const char *FuncName() {
        return "CallContextRegister::CheckExpiredCalls";
    }

    inline void CallContextRegister::Start() {
        m_pCheckExpiredCallsJob =
            new (FileName(), 0x49) MethodCallJob<CallContextRegister, int, PeriodicJob>(
                FuncName(), this, &CallContextRegister::CheckExpiredCalls, 0
            );
        m_pCheckExpiredCallsJob->unk34 = 100;
        m_pCheckExpiredCallsJob->AcquireRef();
        Scheduler::GetInstance()->Queue(m_pCheckExpiredCallsJob, false);
    }
}