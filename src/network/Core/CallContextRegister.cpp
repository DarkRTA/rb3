#include "network/Core/CallContextRegister.h"
#include "Core/CallContext.h"
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
        m_pCheckExpiredCallsJob->m_tiPeriod = 100;
        m_pCheckExpiredCallsJob->AcquireRef();
        Scheduler::GetInstance()->Queue(m_pCheckExpiredCallsJob, false);
    }

    bool CallContextRegister::BeginTermination() {
        Stop();
        return true;
    }

    inline void CallContextRegister::Stop() {
        if (!Scheduler::GetInstance()->Cancel(m_pCheckExpiredCallsJob)) {
            m_pCheckExpiredCallsJob->SetToCancel();
        }
        m_pCheckExpiredCallsJob->ReleaseRef();
        m_pCheckExpiredCallsJob = nullptr;
    }

    unsigned int CallContextRegister::Register(CallContext *ctx) {
        unsigned int id = m_uiNextID++;
        m_mapCallContextes[id] = ctx;
        return id;
    }

    void CallContextRegister::Unregister(unsigned int id) {
        m_mapCallContextes.erase(id);
    }

    CallContext *CallContextRegister::GetCallContext(unsigned int id) {
        qMap<unsigned int, CallContext *>::iterator it = m_mapCallContextes.find(id);
        if (it == m_mapCallContextes.end())
            return nullptr;
        else
            return it->second;
    }
}