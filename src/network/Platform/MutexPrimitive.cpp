#include "Platform/MutexPrimitive.h"

namespace Quazal {

    bool MutexPrimitive::s_bNoOp = false;

    MutexPrimitive::MutexPrimitive(){
        const char* evil = "MutexPrimitive.cpp";
        m_hMutex = (OSMutex *)MemoryManager::Allocate(
            MemoryManager::GetDefaultMemoryManager(), 0x18, evil, 0x65, MemoryManager ::_InstType8);
        ;
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
