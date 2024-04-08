#include "Platform/LockChecker.h"

namespace Quazal {

    LockChecker::LockChecker(unsigned int ui) : m_bLockRestrictionsInUse(false), 
        m_uiLockMask(ui), m_uiRecursionLevel(0), m_uiMaximumLockRecursion(0) {
        
    }

    LockChecker::~LockChecker(){
    
    }

}
