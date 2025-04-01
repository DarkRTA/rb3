#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class DateTime : public RootObject {
    public:
        DateTime();
        DateTime(const DateTime &);
        DateTime &operator=(const DateTime &);
        ~DateTime() {}
        operator unsigned long long() const;
        bool operator>(const DateTime &) const;

        unsigned int GetYear() const;
        unsigned int GetMonth() const;
        unsigned int GetDay() const;
        unsigned int GetHour() const;
        unsigned int GetMinute() const;
        unsigned int GetSecond() const;

        static const DateTime &Never;
        static void GetSystemTime(Quazal::DateTime &);

        unsigned long long m_ui64Value;
    };
}
