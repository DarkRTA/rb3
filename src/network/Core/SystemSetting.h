#pragma once
#include "Platform/RootObject.h"
#include "Platform/String.h"
#include "Platform/qChain.h"

namespace Quazal {
    class SystemSetting : public RootObject {
    public:
        SystemSetting(const String &, unsigned int);
        ~SystemSetting();

        qChain<SystemSetting *> &GetList() {
            static qChain<SystemSetting *> s_lstSettings;
            return s_lstSettings;
        }

        int unk0, unk4;
        String m_strName; // 0x8
        unsigned int m_uiValue; // 0xc
        bool m_bIsImmutable; // 0x10
    };
}