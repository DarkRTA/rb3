/*
    Compile unit: C:\rockband2\system\src\net\NetSearchResult.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80528D74 -> 0x80529364
*/
// Range: 0x80528D74 -> 0x80528DA4
class NetSearchResult * NetSearchResult::New() {}

// Range: 0x80528DA4 -> 0x80528EA8
void * NetSearchResult::NetSearchResult(class NetSearchResult * const this /* r31 */) {
    // Local variables
    class MemStream settingsData; // r1+0x10

    // References
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__19MatchmakingSettings;
    // -> struct [anonymous] __vt__15NetSearchResult;
}

// Range: 0x80528EA8 -> 0x80528F6C
void * NetSearchResult::~NetSearchResult(class NetSearchResult * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15NetSearchResult;
}

// Range: 0x80528F6C -> 0x80528FE4
void NetSearchResult::Save(const class NetSearchResult * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80528FE4 -> 0x8052905C
void NetSearchResult::Load(class NetSearchResult * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    unsigned char slots; // r1+0x8
}

// Range: 0x8052905C -> 0x805290E8
unsigned char NetSearchResult::Equals(const class NetSearchResult * const this /* r29 */, const class NetSearchResult * result /* r30 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A53CBC
// Range: 0x805290E8 -> 0x80529364
class DataNode NetSearchResult::Handle(class NetSearchResult * const this /* r28 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x5C
} __vt__15NetSearchResult; // size: 0x5C, address: 0x80905A50
struct {
    // total size: 0x8
} __RTTI__15NetSearchResult; // size: 0x8, address: 0x80905AD8

