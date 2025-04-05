#pragma once
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"
#include "Platform/MutexPrimitive.h"

namespace Quazal {
    class ScopedCS : public RootObject {
    public:
        ScopedCS(CriticalSection &cs) : m_bInScope(true), critSec(&cs) {
            if (!MutexPrimitive::s_bNoOp)
                cs.EnterImpl();
        }

        ~ScopedCS() { EndScope(); }

        void EndScope() {
            if (m_bInScope) {
                CriticalSection *cs = critSec;
                if (!MutexPrimitive::s_bNoOp)
                    cs->LeaveImpl();
                m_bInScope = false;
            }
        }

        bool m_bInScope; // 0x0
        CriticalSection *critSec;
    };
}
