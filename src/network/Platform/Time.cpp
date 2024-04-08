#include "Platform/Time.h"

namespace Quazal {
    Time& Time::operator=(const Time& time){
        m_ui64Value = time.m_ui64Value;
    }

    Time& Time::operator=(unsigned long long ull){
        m_ui64Value = ull;
    }

    Time::operator unsigned long long(){
        return m_ui64Value;
    }

    Time::operator unsigned long long() const {
        return m_ui64Value;
    }
}
