#include "Platform/MutexPrimitive.h"

namespace Quazal {

    bool MutexPrimitive::s_bNoOp = false;

    MutexPrimitive::MutexPrimitive(){
        m_hMutex = (OSMutex*)QUAZAL_DEFAULT_ALLOC(0x18, 0x65, _InstType8);
        OSInitMutex(m_hMutex);
    }

    MutexPrimitive::~MutexPrimitive(){
        QUAZAL_DEFAULT_FREE(m_hMutex, _InstType8);
        m_hMutex = 0;
    }

    void MutexPrimitive::EnterImpl(){
        OSLockMutex(m_hMutex);
    }

    void MutexPrimitive::LeaveImpl(){
        OSUnlockMutex(m_hMutex);
    }

}
