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

    DateTime(){
        memset(&mSec, 0, 6);
    }
    DateTime(unsigned int);
    DateTime(unsigned short, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
    void GetDateAndTime(DateTime&);
    unsigned int ToCode() const;
    void ToString(class String&) const;
    void ToDateString(class String&) const;
    void ToMiniDateString(class String&) const;
    int Year() const;
    void Format(class String&) const;
};

void DateTimeInit();
void GetDateAndTime(DateTime&);
BinStream& operator<<(BinStream&, const DateTime&);
BinStream& operator>>(BinStream&, DateTime&);

#endif
