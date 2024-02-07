/*
    Compile unit: C:\rockband2\band2\src\meta\TourSavable.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801D9E98 -> 0x801DA4CC
*/
// Range: 0x801D9E98 -> 0x801D9F9C
void * TourSavable::TourSavable(class TourSavable * const this /* r29 */) {
    // Local variables
    struct DateTime now; // r1+0x10
    unsigned int uploadTimeInit; // r0
    struct DateTime then; // r1+0x8

    // References
    // -> struct [anonymous] __vt__11TourSavable;
}

// Range: 0x801D9F9C -> 0x801DA010
void * TourSavable::~TourSavable(class TourSavable * const this /* r30 */) {}

// Range: 0x801DA010 -> 0x801DA018
unsigned char TourSavable::IsDirtySave() {}

// Range: 0x801DA018 -> 0x801DA020
unsigned char TourSavable::IsDirtyUpload() {}

// Range: 0x801DA020 -> 0x801DA028
unsigned char TourSavable::IsNameUnchecked() {}

// Range: 0x801DA028 -> 0x801DA030
unsigned char TourSavable::IsMottoUnchecked() {}

// Range: 0x801DA030 -> 0x801DA0CC
unsigned char TourSavable::IsUploadNeeded(const class TourSavable * const this /* r29 */) {
    // Local variables
    struct DateTime now; // r1+0x8
    unsigned int timeDiff; // r30
}

// Range: 0x801DA0CC -> 0x801DA168
unsigned char TourSavable::IsUploadSecNeeded(const class TourSavable * const this /* r29 */) {
    // Local variables
    struct DateTime now; // r1+0x8
    unsigned int timeDiff; // r30
}

// Range: 0x801DA168 -> 0x801DA1A8
void TourSavable::SetDirty() {}

// Range: 0x801DA1A8 -> 0x801DA1B8
void TourSavable::SetUnchecked() {}

// Range: 0x801DA1B8 -> 0x801DA1CC
void TourSavable::SaveLoadComplete() {}

// Range: 0x801DA1CC -> 0x801DA1D4
void TourSavable::UploadAttempted() {}

// Range: 0x801DA1D4 -> 0x801DA1EC
void TourSavable::UploadComplete() {}

// Range: 0x801DA1EC -> 0x801DA204
void TourSavable::UploadSecComplete() {}

static class Symbol _s; // size: 0x4, address: 0x80A4DF04
// Range: 0x801DA204 -> 0x801DA4CC
class DataNode TourSavable::Handle(class TourSavable * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x6C
} __vt__11TourSavable; // size: 0x6C, address: 0x808A5364

