#include "os/DateTime.h"
#include "utl/MakeString.h"
#include "utl/Symbol.h"
#include "os/Debug.h"
#include <revolution/os.h>

void DateTimeInit(){}

void GetDateAndTime(DateTime& dt){
    OSCalendarTime os_struct;
    OSTicksToCalendarTime(OSGetTime(), &os_struct);
    dt.mSec = os_struct.sec;
    dt.mMin = os_struct.min;
    dt.mHour = os_struct.hour;
    dt.mDay = os_struct.month_day;
    dt.mMonth = os_struct.month;
    dt.mYear = os_struct.year - 1900;
}

DateTime::DateTime(unsigned int code){
    mYear = (code / 0x1FA4000) + 100;
    mMonth = (code % 0x1FA4000) / 0x2A3000;
}

// void __thiscall DateTime::DateTime(DateTime *this,uint param_1)

// {
//   DateTime DVar1;
//   uint uVar2;
  
//   this[5] = (DateTime)((char)(param_1 / 0x1fa4000) + 'd');
//   this[4] = SUB41((param_1 % 0x1fa4000) / 0x2a3000,0);
//   uVar2 = (param_1 % 0x1fa4000) % 0x2a3000;
//   this[3] = SUB41(uVar2 / 0x15180,0);
//   uVar2 = uVar2 % 0x15180;
//   this[2] = SUB41(uVar2 / 0xe10,0);
//   uVar2 = uVar2 % 0xe10;
//   DVar1 = SUB41(uVar2 / 0x3c,0);
//   this[1] = DVar1;
//   *this = (DateTime)((char)uVar2 + (char)DVar1 * -0x3c);
//   return;
// }

DateTime::DateTime(unsigned short year, unsigned char month, unsigned char day, 
    unsigned char hr, unsigned char min, unsigned char sec) {
    mYear = year - 1900;
    mMonth = month - 1;
    mDay = day;
    mHour = hr;
    mMin = min;
    mSec = sec;
}

unsigned int DateTime::ToCode() const {
    return ((unsigned int)mDay * 0x15180) + ((unsigned int)mMonth * 0x2A3000) + (mYear - 100)*0x1FA4000 + ((unsigned int)mHour * 0xE10) + ((unsigned int)mMin * 0x3C) + (unsigned int)mSec;
}

// uint __thiscall DateTime::ToCode(DateTime *this)

// {
//   return (uint)this->mHour * 0xe10 + (uint)this->mSec + (uint)this->mMin * 0x3c +
//          (this->mYear - 100) * 0x1fa4000 +
//          (uint)this->mMonth * 0x2a3000 + (uint)this->mDay * 0x15180;
// }

void DateTime::ToString(String& str) const {
    ToDateString(str);
    str += MakeString(" %02d:%02d:%02d", mHour, mMin, mSec);
}

void DateTime::ToDateString(String& str) const {
    ToMiniDateString(str);
    str += MakeString("/%04d", mYear + 1900);
}

void DateTime::ToMiniDateString(String& str) const {
    str += MakeString("%02d/%02d", mMonth + 1, mDay);
}

unsigned short DateTime::Year() const {
    return (unsigned short)mYear + 1900;
}

namespace {
    Symbol MonthToken(int month){
        MILO_ASSERT(( 0) <= (month) && (month) <= ( 11), 0xF5);
        static Symbol month_symbols[12] = {
            "month_january", "month_february", "month_march", "month_april",
            "month_may", "month_june", "month_july", "month_august",
            "month_september", "month_october", "month_november", "month_december"
        };
        return month_symbols[month];
    }
}

BinStream& operator<<(BinStream& bs, const DateTime& dt){
    bs << dt.mSec << dt.mMin << dt.mHour << dt.mDay << dt.mMonth << dt.mYear;
    return bs;
}

BinStream& operator>>(BinStream& bs, DateTime& dt){
    bs >> dt.mSec >> dt.mMin >> dt.mHour >> dt.mDay >> dt.mMonth >> dt.mYear;
    return bs;
}
