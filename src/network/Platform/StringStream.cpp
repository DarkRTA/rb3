#include "Platform/StringStream.h"
#include "Platform/MemoryManager.h"

namespace Quazal {

    StringStream::StringStream(){
        m_szBuffer = m_szInitialBuffer;
        m_uiSize = 0x100;
        m_szCurrentPosition = m_szInitialBuffer;
        m_szInitialBuffer[0] = 0;
        m_bHex = false;
        m_bShowBase = true;
        m_bBoolAlpha = true;
    }

    StringStream::~StringStream(){
        if(m_szBuffer != m_szInitialBuffer){
            QUAZAL_DEFAULT_FREE(&m_szBuffer - 1, _InstType9);
        }
    }

    void hex(StringStream& ss){
        ss.m_bHex = true;
    }

    void dec(StringStream& ss){
        ss.m_bHex = false;
    }

}
