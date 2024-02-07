/*
    Compile unit: C:\rockband2\system\src\utl\MemStats.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80619750 -> 0x80619AA0
*/
// Range: 0x80619750 -> 0x80619770
int SizeLess() {}

// Range: 0x80619770 -> 0x8061977C
int NameLess() {}

// Range: 0x8061977C -> 0x80619794
void * BlockStatTable::BlockStatTable() {}

// Range: 0x80619794 -> 0x806197A0
void BlockStatTable::Clear() {}

// Range: 0x806197A0 -> 0x8061982C
class BlockStat & BlockStatTable::GetBlockStat(class BlockStatTable * const this /* r30 */, int iStat /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061982C -> 0x806199E4
void BlockStatTable::Update(class BlockStatTable * const this /* r28 */, const char * name /* r24 */, unsigned char heap /* r29 */, int sizeReq /* r1+0x8 */, int sizeAct /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x806199E4 -> 0x806199F8
void BlockStatTable::SortBySize() {}

// Range: 0x806199F8 -> 0x80619A0C
void BlockStatTable::SortByName() {}

// Range: 0x80619A0C -> 0x80619A78
void HeapStats::Alloc() {}

// Range: 0x80619A78 -> 0x80619AA0
void HeapStats::Free() {}


