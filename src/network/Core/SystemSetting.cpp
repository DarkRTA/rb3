#include "network/Core/SystemSetting.h"
#include "Platform/String.h"

namespace Quazal {
    SystemSetting::SystemSetting(const String &str, unsigned int ui)
        : unk0(0), unk4(0), m_strName(str), m_uiValue(ui), m_bIsImmutable(0) {
        GetList().push_back(this);
    }
}