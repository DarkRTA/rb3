#include "Platform/CriticalSection.h"

namespace Quazal {

    CriticalSection::CriticalSection(unsigned int ui) : m_oMutex(), m_oLockChecker(ui) {

    }

    CriticalSection::~CriticalSection(){
        
    }

    void CriticalSection::EnterImpl(){
        if(MutexPrimitive::s_bNoOp) return;
        else m_oMutex.EnterImpl();
    }

    void CriticalSection::LeaveImpl(){
        if(MutexPrimitive::s_bNoOp) return;
        else m_oMutex.LeaveImpl();
    }

}
