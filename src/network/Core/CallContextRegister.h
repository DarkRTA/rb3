#pragma once
#include "Core/CallContext.h"
#include "Core/SystemComponent.h"
#include "Platform/qStd.h"

namespace Quazal {
    class CallContextRegister : public SystemComponent {
    public:
        CallContextRegister();
        virtual ~CallContextRegister(); // 0x8
        virtual const char *GetType() const { return type(); } // 0x14
        virtual bool IsAKindOf(const char *str) const { return type() == str; } // 0x18
        virtual void EnforceDeclareSysComponentMacro(); // 0x1C
        virtual bool BeginInitialization(); // 0x30
        virtual bool BeginTermination(); // 0x38

        qMap<unsigned int, CallContext *> m_mapCallContextes;
        unsigned int m_uiNextID;
        int m_pCheckExpiredCallsJob;
    };
}