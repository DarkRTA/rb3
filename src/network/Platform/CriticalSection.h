#ifndef PLATFORM_CRITICALSECTION_H
#define PLATFORM_CRITICALSECTION_H
#include "Platform/RootObject.h"
#include "Platform/MutexPrimitive.h"
#include "Platform/LockChecker.h"

namespace Quazal {
    class CriticalSection : public RootObject {
    public:
        CriticalSection(unsigned int);
        ~CriticalSection();
        void EnterImpl();
        void LeaveImpl();

        MutexPrimitive m_oMutex;
        LockChecker m_oLockChecker;
    };
}

#endif
