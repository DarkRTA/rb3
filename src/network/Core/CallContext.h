#pragma once
#include "Platform/RefCountedObject.h"
#include "Platform/Result.h"
#include "Platform/Time.h"
#include "Platform/qStd.h"

namespace Quazal {
    class CallContext : public RefCountedObject {
    public:
        enum _State {
        };
        CallContext();
        virtual ~CallContext();
        virtual bool FlagsAreValid() const;
        virtual void BeginTransition(_State, qResult, bool);
        virtual void ProcessCallCompletion();

        unsigned int unk8; // 0x8
        _State unkc; // 0xc
        qList<int> unk10; // 0x10
        qVector<int> unk18; // 0x18
        qResult unk20; // 0x20
        int unk30;
        int unk34;
        int unk38;
        int unk3c;
        Time unk40; // 0x40
    };
}
