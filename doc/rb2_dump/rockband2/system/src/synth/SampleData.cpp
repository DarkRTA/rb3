/*
    Compile unit: C:\rockband2\system\src\synth\SampleData.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805814F8 -> 0x80581ADC
*/
void * (* sAlloc)(int); // size: 0x4, address: 0x80A54568
void (* sFree)(void *); // size: 0x4, address: 0x80A5456C
// Range: 0x805814F8 -> 0x80581504
void SampleData::SetAllocator() {
    // References
    // -> void (* sFree)(void *);
    // -> void * (* sAlloc)(int);
}

// Range: 0x80581504 -> 0x8058153C
void * SampleData::SampleData(class SampleData * const this /* r31 */) {}

// Range: 0x8058153C -> 0x8058159C
void * SampleData::~SampleData(class SampleData * const this /* r30 */) {
    // References
    // -> void (* sFree)(void *);
}

// Range: 0x8058159C -> 0x80581724
void SampleData::Load(class SampleData * const this /* r29 */, class BinStream & s /* r30 */, const class FilePath & fp /* r31 */) {
    // Local variables
    int rev; // r1+0x10
    int fmt; // r1+0xC
    unsigned char haveData; // r3

    // References
    // -> void * (* sAlloc)(int);
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
}

// Range: 0x80581724 -> 0x8058191C
void SampleData::LoadWAV(class SampleData * const this /* r28 */, class BinStream & s /* r29 */, const class FilePath & f /* r30 */) {
    // Local variables
    class WaveFile wf; // r1+0x58
    class WaveFileData wfd; // r1+0x30

    // References
    // -> void * (* sAlloc)(int);
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x8058191C -> 0x8058196C
void SampleData::Reset(class SampleData * const this /* r31 */) {
    // References
    // -> void (* sFree)(void *);
}

// Range: 0x8058196C -> 0x80581ADC
int SampleData::SizeAs(const class SampleData * const this /* r31 */) {
    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}


