#ifndef PLATFORM_TIME_H
#define PLATFORM_TIME_H
// #include "Platform/RootObject.h"

namespace Quazal {
    class Time {
    public:
        void GetTime();
        Time& operator=(const Time&);
        Time& operator=(unsigned long long);
        operator unsigned long long();
        operator unsigned long long() const;

        unsigned long long m_ui64Value;
    };
}

#endif
