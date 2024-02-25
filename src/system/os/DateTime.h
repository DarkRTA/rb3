#ifndef OS_DATETIME_H
#define OS_DATETIME_H
#include "utl/Str.h"
#include "utl/BinStream.h"

class DateTime {
public:
    unsigned char mSec;
    unsigned char mMin;
    unsigned char mHour;
    unsigned char mDay;
    unsigned char mMonth;
    unsigned char mYear;

    DateTime(unsigned int);
    DateTime(unsigned short, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
    void GetDateAndTime(DateTime&);
    unsigned int ToCode() const;
    void ToString(String&) const;
    void ToDateString(String&) const;
    void ToMiniDateString(String&) const;
    unsigned short Year() const;
};

void DateTimeInit();
BinStream& operator<<(BinStream&, const DateTime&);
BinStream& operator>>(BinStream&, DateTime&);

#endif
