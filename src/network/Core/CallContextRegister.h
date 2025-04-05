#pragma once
#include "Core/CallContext.h"
#include "Core/PeriodicJob.h"
#include "Core/SystemComponent.h"
#include "MethodCallJob.h"
#include "Platform/qStd.h"

namespace Quazal {
    class CallContextRegister : public SystemComponent {
    public:
        CallContextRegister();
        virtual ~CallContextRegister(); // 0x8
        virtual const char *GetType() const; // 0x14
        virtual bool IsAKindOf(const char *str) const; // 0x18
        virtual void EnforceDeclareSysComponentMacro(); // 0x1C
        virtual bool BeginInitialization(); // 0x30
        virtual bool BeginTermination(); // 0x38

        void Start();
        void Stop();
        void CheckExpiredCalls(int);

        qMap<unsigned int, CallContext *> m_mapCallContextes; // 0x18
        unsigned int m_uiNextID; // 0x30
        MethodCallJob<CallContextRegister, int, PeriodicJob>
            *m_pCheckExpiredCallsJob; // 0x34
    };
}