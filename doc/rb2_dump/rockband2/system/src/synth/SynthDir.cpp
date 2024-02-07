/*
    Compile unit: C:\rockband2\system\src\synth\SynthDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80596840 -> 0x80596E34
*/
class DataArray * types; // size: 0x4, address: 0x80A547F0
// Range: 0x80596840 -> 0x805968C8
void * SynthDir::SynthDir(class SynthDir * const this /* r31 */) {
    // References
    // -> class Synth * TheSynth;
    // -> struct [anonymous] __vt__8SynthDir;
}

// Range: 0x805968C8 -> 0x80596980
void * SynthDir::~SynthDir(class SynthDir * const this /* r29 */) {
    // References
    // -> class Synth * TheSynth;
    // -> struct [anonymous] __vt__8SynthDir;
}

static int gRev; // size: 0x4, address: 0x80A547F8
// Range: 0x80596980 -> 0x805969C4
void SynthDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805969C4 -> 0x80596A6C
void SynthDir::PreLoad(class SynthDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> static int gRev;
}

// Range: 0x80596A6C -> 0x80596AEC
void SynthDir::PostLoad(class SynthDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x80596AEC -> 0x80596AF0
void SynthDir::Copy() {}

// Range: 0x80596AF0 -> 0x80596DB4
class DataNode SynthDir::Handle(class SynthDir * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

// Range: 0x80596DB4 -> 0x80596E34
unsigned char SynthDir::SyncProperty(class SynthDir * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xB0
} __vt__8SynthDir; // size: 0xB0, address: 0x80920988
struct {
    // total size: 0x8
} __RTTI__8SynthDir; // size: 0x8, address: 0x80920A60

