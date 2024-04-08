#include "Platform/StringStream.h"
#include "Platform/MemoryManager.h"

Quazal::StringStream::StringStream(){
    m_szBuffer = m_szInitialBuffer;
    m_uiSize = 0x100;
    m_szCurrentPosition = m_szInitialBuffer;
    m_szInitialBuffer[0] = 0;
    m_bHex = false;
    m_bShowBase = true;
    m_bBoolAlpha = true;
}

Quazal::StringStream::~StringStream(){
    if(m_szBuffer != m_szInitialBuffer){
        QUAZAL_DEFAULT_FREE(&m_szBuffer - 1, _InstType9);
    }
}

void Quazal::hex(Quazal::StringStream& ss){
    ss.m_bHex = true;
}

void Quazal::dec(Quazal::StringStream& ss){
    ss.m_bHex = false;
}
