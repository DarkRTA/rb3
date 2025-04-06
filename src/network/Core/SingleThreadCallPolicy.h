#pragma once
#include "CallPolicy.h"

namespace Quazal {
    class SingleThreadCallPolicy : public CallPolicy {
    public:
        SingleThreadCallPolicy();
        virtual ~SingleThreadCallPolicy() {}
        virtual void BeginCallImpl();
        virtual void EndCallImpl();

        void SetMaximumRecursionLevel(unsigned int);
        bool CurrentThreadIsDispatchingJobs() const;

        unsigned int m_uiCurrentRecursionLevel; // 0x4
        unsigned int m_uiCurrentThread; // 0x8
        unsigned int m_uiMaximumRecursionLevel; // 0xc
        unsigned int m_uiValidThread; // 0x10
    };
}