#pragma once
#include "Platform/String.h"
#include "Platform/qStd.h"
#include "SystemComponent.h"

namespace Quazal {
    class SystemComponentGroup : public SystemComponent {
    public:
        SystemComponentGroup(const String &);
        virtual ~SystemComponentGroup(); // 0x8
        virtual const char *GetType() const; // 0x14
        virtual bool IsAKindOf(const char *str) const; // 0x18
        virtual void EnforceDeclareSysComponentMacro(); // 0x1C
        virtual void TraceImpl(uint) const; // 0x20
        virtual void OnInitialize(); // 0x28
        virtual void OnTerminate(); // 0x2C
        virtual bool BeginInitialization(); // 0x30
        virtual bool EndInitialization(); // 0x34
        virtual bool BeginTermination(); // 0x38
        virtual bool EndTermination(); // 0x3C
        virtual _State TestState(); // 0x48
        virtual void DoWork(); // 0x4C

        void RegisterComponent(SystemComponent *);
        void UnregisterComponent(SystemComponent *);

        qList<SystemComponent *> m_lstComponents; // 0x18
    };
}