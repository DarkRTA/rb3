#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    union UserContextStorage {
        unsigned int m_uiValue; // offset 0x0, size 0x4
        float m_dValue; // offset 0x0, size 0x4
        unsigned char m_bValue; // offset 0x0, size 0x1
        void *m_pPointer; // offset 0x0, size 0x4
    };
    class UserContext : public RootObject {
    public:
        UserContext() { m_uContextStorage.m_uiValue = 0; }

    private:
        // total size: 0x4
        union UserContextStorage m_uContextStorage; // offset 0x0, size 0x4
    };
}