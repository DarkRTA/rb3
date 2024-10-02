#ifndef PLATFORM_DATETIME_H
#define PLATFORM_DATETIME_H

namespace Quazal {
    class DateTime {
    public:
        DateTime();
        DateTime(const DateTime&);
        DateTime& operator=(const DateTime&);
        operator unsigned long long() const;
        bool operator>(const DateTime&) const;

        unsigned int GetYear() const;
        unsigned int GetMonth() const;
        unsigned int GetDay() const;
        unsigned int GetHour() const;
        unsigned int GetMinute() const;
        unsigned int GetSecond() const;

        static const DateTime& Never;
        static void GetSystemTime(Quazal::DateTime&);

        unsigned long long m_ui64Value;
    };
}

#endif
