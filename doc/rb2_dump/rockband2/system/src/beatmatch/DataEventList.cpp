/*
    Compile unit: C:\rockband2\system\src\beatmatch\DataEventList.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D62CC -> 0x802D70F0
*/
// Range: 0x802D62CC -> 0x802D6318
void * DataEventList::DataEventList() {}

// Range: 0x802D6318 -> 0x802D64E4
void * DataEventList::~DataEventList(class DataEventList * const this /* r30 */) {}

// Range: 0x802D64E4 -> 0x802D657C
void DataEventList::Compress(class DataEventList * const this /* r29 */, class DataArray * temp /* r30 */, int element /* r31 */) {}

// Range: 0x802D657C -> 0x802D6764
void DataEventList::InsertEvent(class DataEventList * const this /* r31 */, float start /* f30 */, float end /* f31 */, const class DataNode & ev /* r28 */, int at /* r29 */) {
    // Local variables
    class DataEvent tmp; // r1+0x14
    struct CompEv tmp; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D6764 -> 0x802D67D0
int DataEventList::FindStartFromBack() {
    // Local variables
    int i; // r5
}

// Range: 0x802D67D0 -> 0x802D6894
void DataEventList::Reset(class DataEventList * const this /* r31 */, float frame /* r1+0x8 */) {}

// Range: 0x802D6894 -> 0x802D68E0
class DataEvent & DataEventList::Event() {}

// Range: 0x802D68E0 -> 0x802D6950
class DataEvent * DataEventList::NextEvent() {}

// Range: 0x802D6950 -> 0x802D69EC
float * DataEventList::EndPtr(class DataEventList * const this /* r30 */, int index /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D69EC -> 0x802D6A70
void DataEventList::Invert() {
    // Local variables
    int i; // r5
    float tmp; // f2
    int i; // r5
    float tmp; // f2
}

// Range: 0x802D6A70 -> 0x802D6B68
void DataEventList::SecOffset(class DataEventList * const this /* r29 */) {
    // Local variables
    float ms; // f31
    int i; // r30
    int i; // r30
}

// Range: 0x802D6B68 -> 0x802D6F40
void DataEventList::Compact(class DataEventList * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__PQ213DataEventList6CompEv;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P9DataEvent;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ213DataEventList6CompEv; // size: 0x8, address: 0x808CAA20
struct {
    // total size: 0x8
} __RTTI__P9DataEvent; // size: 0x8, address: 0x808CAA38
// Range: 0x802D6F40 -> 0x802D70F0
void DataEventList::Clear(class DataEventList * const this /* r31 */) {}


