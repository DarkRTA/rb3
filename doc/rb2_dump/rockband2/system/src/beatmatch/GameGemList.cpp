/*
    Compile unit: C:\rockband2\system\src\beatmatch\GameGemList.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802DF13C -> 0x802DF7E0
*/
// Range: 0x802DF13C -> 0x802DF158
void * GameGemList::GameGemList() {}

// Range: 0x802DF158 -> 0x802DF33C
unsigned char GameGemList::AddMultiGem(class GameGemList * const this /* r31 */, const class MultiGemInfo & info /* r29 */) {
    // Local variables
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x18
    unsigned char will_be_no_strum; // r0
}

// Range: 0x802DF33C -> 0x802DF3B8
int GameGemList::ClosestMarkerIdxAtOrAfter(const class GameGemList * const this /* r31 */, float ms /* r1+0x8 */) {}

// Range: 0x802DF3B8 -> 0x802DF434
int GameGemList::ClosestMarkerIdxAtOrAfterTick(const class GameGemList * const this /* r31 */, int tick /* r1+0x8 */) {}

// Range: 0x802DF434 -> 0x802DF4EC
float GameGemList::TimeAtNext(const class GameGemList * const this /* r30 */, int idx /* r31 */) {
    // Local variables
    int new_idx; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802DF4EC -> 0x802DF678
void GameGemList::Finalize(class GameGemList * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P7GameGem;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x802DF678 -> 0x802DF6E0
void GameGemList::RecalculateGemTimes(class GameGemList * const this /* r29 */, class TempoMap * tempo /* r30 */) {
    // Local variables
    class GameGem * it; // r31
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
static class Symbol chord_hopos; // size: 0x4, address: 0x80A505D4
// Range: 0x802DF6E0 -> 0x802DF7E0
unsigned char GameGemList::WillBeNoStrum(class GameGemList * const this /* r29 */, const class MultiGemInfo & info /* r30 */) {
    // References
    // -> static class Symbol chord_hopos;
}


