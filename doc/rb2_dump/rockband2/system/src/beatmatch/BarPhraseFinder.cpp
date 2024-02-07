/*
    Compile unit: C:\rockband2\system\src\beatmatch\BarPhraseFinder.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D12F8 -> 0x802D1840
*/
class BarPhraseFinder : public PhraseFinder {
    // total size: 0x10
    class GameGemInfoList * mGemInfoList; // offset 0x4, size 0x4
    class BarFinder * mBarFinder; // offset 0x8, size 0x4
    int mNumBarsToCatch; // offset 0xC, size 0x4
};
// Range: 0x802D12F8 -> 0x802D135C
void * BarPhraseFinder::BarPhraseFinder(class BarPhraseFinder * const this /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15BarPhraseFinder;
}

class PhraseFinder {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
// Range: 0x802D135C -> 0x802D1410
int BarPhraseFinder::NextValidStart(const class BarPhraseFinder * const this /* r30 */) {
    // Local variables
    int bar; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D1410 -> 0x802D1488
unsigned char BarPhraseFinder::PhraseAtOrAfter(const class BarPhraseFinder * const this /* r29 */, int first_gem /* r30 */, struct PhraseInfo & info /* r31 */) {
    // Local variables
    int bar; // r1+0x8
}

// Range: 0x802D1488 -> 0x802D1840
unsigned char BarPhraseFinder::LookForPhrase(const class BarPhraseFinder * const this /* r27 */, int & bar /* r28 */, struct PhraseInfo & info /* r29 */) {
    // Local variables
    int num_bars; // r0
    int last_bar; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x14
} __vt__15BarPhraseFinder; // size: 0x14, address: 0x808C9FE0
struct {
    // total size: 0x8
} __RTTI__15BarPhraseFinder; // size: 0x8, address: 0x808CA018
struct {
    // total size: 0x8
} __RTTI__12PhraseFinder; // size: 0x8, address: 0x808CA030

