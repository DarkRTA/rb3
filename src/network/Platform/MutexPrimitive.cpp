#include "Platform/MutexPrimitive.h"

bool Quazal::MutexPrimitive::s_bNoOp = false;

Quazal::MutexPrimitive::MutexPrimitive(){
    m_hMutex = (OSMutex*)QUAZAL_DEFAULT_ALLOC(0x18, 0x65, _InstType8);
    OSInitMutex(m_hMutex);
}

Quazal::MutexPrimitive::~MutexPrimitive(){
    QUAZAL_DEFAULT_FREE(m_hMutex, _InstType8);
    m_hMutex = 0;
}

void Quazal::MutexPrimitive::EnterImpl(){
    OSLockMutex(m_hMutex);
}

void Quazal::MutexPrimitive::LeaveImpl(){
    OSUnlockMutex(m_hMutex);
}
