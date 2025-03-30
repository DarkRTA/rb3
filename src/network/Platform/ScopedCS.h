#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"
#include "Platform/MutexPrimitive.h"

namespace Quazal {
    class ScopedCS : public RootObject {
    public:
        ScopedCS(CriticalSection &cs) : unk0(true), critSec(&cs) {
            if (!MutexPrimitive::s_bNoOp)
                critSec->EnterImpl();
        }

        ~ScopedCS() { EndScope(); }

        void EndScope() {
            if (unk0) {
                CriticalSection *cs = critSec;
                if (!MutexPrimitive::s_bNoOp)
                    cs->LeaveImpl();
                unk0 = false;
            }
        }

        bool unk0;
        CriticalSection *critSec;
    };
}
