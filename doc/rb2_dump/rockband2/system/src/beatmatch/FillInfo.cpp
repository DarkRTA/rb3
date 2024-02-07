/*
    Compile unit: C:\rockband2\system\src\beatmatch\FillInfo.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802DBBEC -> 0x802DC1CC
*/
// Range: 0x802DBBEC -> 0x802DBC0C
unsigned char FillExtentCmp() {}

// Range: 0x802DBC0C -> 0x802DBC28
unsigned char FillExtentCmpIncludingEnd() {}

// Range: 0x802DBC28 -> 0x802DBD1C
unsigned char FillInfo::AddFill() {
    // Local variables
    int new_tick; // r6
    int new_duration; // r5
}

// Range: 0x802DBD1C -> 0x802DBDB0
unsigned char FillInfo::FillAt(const class FillInfo * const this /* r31 */, int tick /* r1+0x8 */, unsigned char include_end /* r0 */) {}

// Range: 0x802DBDB0 -> 0x802DBE6C
unsigned char FillInfo::FillAt(const class FillInfo * const this /* r30 */, int tick /* r1+0x8 */, struct FillExtent & outExtent /* r31 */) {}

// Range: 0x802DBE6C -> 0x802DBEAC
unsigned char FillInfo::NextFillExtents() {
    // Local variables
    const struct FillExtent * it; // r6
}

// Range: 0x802DBEAC -> 0x802DBEFC
unsigned char FillInfo::FillExtentAtOrBefore() {
    // Local variables
    const struct FillExtent * it; // r7
}

// Range: 0x802DBEFC -> 0x802DBFA8
unsigned char FillInfo::AddLanes() {}

// Range: 0x802DBFA8 -> 0x802DBFEC
void FillInfo::WipeFills() {}

// Range: 0x802DBFEC -> 0x802DC190
void * FillInfo::FillInfo(class FillInfo * const this /* r30 */, const class TickedInfoCollection & lanes /* r28 */, const class vector & solos /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__P10FillExtent;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P13TickedInfo<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__8FillInfo;
}

struct {
    // total size: 0x8
} __RTTI__P10FillExtent; // size: 0x8, address: 0x808CAF68
// Range: 0x802DC190 -> 0x802DC1CC
void * DrumFillInfo::DrumFillInfo(class DrumFillInfo * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12DrumFillInfo;
}


