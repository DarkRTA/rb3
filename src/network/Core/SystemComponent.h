#pragma once

#include "Platform/RefCountedObject.h"
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "types.h"

namespace Quazal {
class SystemComponent : public RefCountedObject {
    enum _State {
        Uninitialized       = 0x1,
        Initializing        = 0x2,
        Ready               = 0x4,
        ReadyInUse          = 0x8,
        TerminatingInUse    = 0x10,
        Terminating         = 0x20,
        Terminated          = 0x40,
        Faulty              = 0x80,
        Unknown             = 0x100,
        Invalid             = -1
    };

    class Use : public RootObject {
        public:
        Use(SystemComponent*, const char*);
        ~Use();

        SystemComponent* mComponent; // 0x0
        const char* mName; // 0x4
        bool mComponentExists; // 0x8
    };

    static const char* type() { return "SystemComponent"; }

    SystemComponent(const String&);
    virtual ~SystemComponent(); // 0x8
    virtual RefCountedObject* AcquireRef(); // 0xC
    virtual void ReleaseRef(); // 0x10
    virtual const char* GetType() const { return type(); } // 0x14
    virtual bool IsAKindOf(const char* str) const { return type() == str; } // 0x18
    virtual void V_Unk7() = 0; // 0x1C
    virtual void TraceImpl(uint) const; // 0x20
    virtual _State StateTransition(_State); // 0x24
    virtual void OnInitialize(); // 0x28
    virtual void OnTerminate(); // 0x2C
    virtual bool BeginInitialization(); // 0x30
    virtual bool EndInitialization(); // 0x34
    virtual bool BeginTermination(); // 0x38
    virtual bool EndTermination(); // 0x3C
    virtual bool ValidTransition(_State); // 0x40
    virtual bool UseIsAllowed(); // 0x44
    virtual void TestState(); // 0x48
    virtual void DoWork(); // 0x4C

    void SetName(const Quazal::String&);
    bool SetState(_State, bool);
    void SetParent(Quazal::SystemComponent*);
    void Trace(unsigned int, bool) const;
    _State Initialize();
    _State Terminate();
    void WaitForTerminatedState(unsigned int);

    Quazal::String mName; // 0x8
    _State mState; // 0xC
    u32 mRefs; // 0x10
    SystemComponent* mParent; // 0x14
};
}
