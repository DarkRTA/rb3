/*
    Compile unit: C:\rockband2\system\src\os\DateTime.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805AE438 -> 0x805AE87C
*/
// Range: 0x805AE438 -> 0x805AE43C
void DateTimeInit() {}

struct OSCalendarTime {
    // total size: 0x28
    int sec; // offset 0x0, size 0x4
    int min; // offset 0x4, size 0x4
    int hour; // offset 0x8, size 0x4
    int mday; // offset 0xC, size 0x4
    int mon; // offset 0x10, size 0x4
    int year; // offset 0x14, size 0x4
    int wday; // offset 0x18, size 0x4
    int yday; // offset 0x1C, size 0x4
    int msec; // offset 0x20, size 0x4
    int usec; // offset 0x24, size 0x4
};
// Range: 0x805AE43C -> 0x805AE4A4
void GetDateAndTime(struct DateTime & out /* r31 */) {
    // Local variables
    struct OSCalendarTime td; // r1+0x8
}

// Range: 0x805AE4A4 -> 0x805AE558
void * DateTime::DateTime(unsigned int code /* r7 */) {
    // Local variables
    int year; // r6
}

// Range: 0x805AE558 -> 0x805AE57C
void * DateTime::DateTime() {}

// Range: 0x805AE57C -> 0x805AE5DC
unsigned int DateTime::ToCode() {}

// Range: 0x805AE5DC -> 0x805AE640
void DateTime::ToString(const struct DateTime * const this /* r9 */, class String & str /* r31 */) {}

// Range: 0x805AE640 -> 0x805AE698
void DateTime::ToDateString(const struct DateTime * const this /* r6 */, class String & str /* r31 */) {}

// Range: 0x805AE698 -> 0x805AE734
unsigned char __lt() {
    // Local variables
    unsigned int lhsdate; // r7
    unsigned int lhstime; // r8
    unsigned int rhsdate; // r9
    unsigned int rhstime; // r0
}

// Range: 0x805AE734 -> 0x805AE7EC
class BinStream & __ls(class BinStream & s /* r31 */) {}

// Range: 0x805AE7EC -> 0x805AE87C
class BinStream & __rs(class BinStream & s /* r30 */, struct DateTime & obj /* r31 */) {}


