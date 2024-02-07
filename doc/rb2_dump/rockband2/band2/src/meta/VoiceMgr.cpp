/*
    Compile unit: C:\rockband2\band2\src\meta\VoiceMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801EFDA4 -> 0x801F0240
*/
// Range: 0x801EFDA4 -> 0x801EFF24
void * VoiceMgr::~VoiceMgr(class VoiceMgr * const this /* r29 */) {}

// Range: 0x801EFF24 -> 0x801F01B0
void VoiceMgr::AddEvents(class VoiceMgr * const this /* r28 */, class DataArray * voice /* r29 */) {
    // Local variables
    int i; // r30
    struct EventData event; // r1+0x3C
    int f; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ28VoiceMgr8FileData;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ28VoiceMgr8FileData; // size: 0x8, address: 0x808A7BF0
// Range: 0x801F01B0 -> 0x801F01E8
struct EventData * VoiceMgr::FindEvent() {
    // Local variables
    struct EventData * it; // r6
}

// Range: 0x801F01E8 -> 0x801F0220
int VoiceMgr::GetNextIndex() {
    // Local variables
    int index; // r3
}

// Range: 0x801F0220 -> 0x801F0228
unsigned char VoiceMgr::HasStream() {}

// Range: 0x801F0228 -> 0x801F0230
void VoiceMgr::Abort() {}

// Range: 0x801F0230 -> 0x801F0238
void VoiceMgr::Poll() {}

// Range: 0x801F0238 -> 0x801F0240
void VoiceMgr::SetPaused() {}

struct {
    // total size: 0x8
} __RTTI__PQ28VoiceMgr9EventData; // size: 0x8, address: 0x808A7C78

