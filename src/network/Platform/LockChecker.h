#ifndef PLATFORM_LOCKCHECKER_H
#define PLATFORM_LOCKCHECKER_H
#include "Platform/RootObject.h"

namespace Quazal {
    class LockChecker : public RootObject {
    public:
        LockChecker(unsigned int);
        ~LockChecker();

        bool m_bLockRestrictionsInUse;
        unsigned int m_uiLockMask;
        unsigned int m_uiRecursionLevel;
        unsigned int m_uiMaximumLockRecursion;
    };
}

#endif
