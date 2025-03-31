#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class Time : public RootObject {
    public:
        Time() : m_ui64Value(0) {}
        Time(unsigned long long val) : m_ui64Value(val) {}
        ~Time() {}
        void GetTime();
        Time &operator=(const Time &);
        Time &operator=(unsigned long long);
        operator unsigned long long();
        operator unsigned long long() const;

        unsigned long long m_ui64Value;
    };
}
