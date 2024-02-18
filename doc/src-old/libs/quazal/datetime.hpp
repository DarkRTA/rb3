#ifndef QUAZAL_DATETIME_HPP
#define QUAZAL_DATETIME_HPP

namespace Quazal {
    class DateTime {
    public:
        DateTime();
        DateTime(const DateTime &);
        DateTime *operator=(const DateTime &);
        operator unsigned long long() const;
        unsigned int GetYear() const;

        unsigned long long num;
    };
}

#endif
