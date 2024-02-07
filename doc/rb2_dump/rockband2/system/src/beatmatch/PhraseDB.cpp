/*
    Compile unit: C:\rockband2\system\src\beatmatch\PhraseDB.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802F4D8C -> 0x802F53AC
*/
// Range: 0x802F4D8C -> 0x802F4DA0
void * Phrase::Phrase() {}

// Range: 0x802F4DA0 -> 0x802F4DBC
unsigned char PhraseMsCmp() {}

// Range: 0x802F4DBC -> 0x802F4DE0
unsigned char PhraseTickCmp() {}

// Range: 0x802F4DE0 -> 0x802F4E70
unsigned char PhraseList::IsMsInPhrase(const class PhraseList * const this /* r31 */, float ms /* r1+0x8 */) {}

// Range: 0x802F4E70 -> 0x802F4EF8
unsigned char PhraseList::IsTickInPhrase(const class PhraseList * const this /* r31 */, int tick /* r1+0x8 */) {}

// Range: 0x802F4EF8 -> 0x802F4FC0
void * PhraseListCollection::PhraseListCollection(class PhraseListCollection * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802F4FC0 -> 0x802F5108
void * PhraseListCollection::~PhraseListCollection(class PhraseListCollection * const this /* r29 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802F5108 -> 0x802F5124
void PhraseListCollection::AddPhrase(enum BeatmatchPhraseType type /* r0 */) {}

// Range: 0x802F5124 -> 0x802F514C
void * PhraseDB::PhraseDB() {}

// Range: 0x802F514C -> 0x802F52F4
void * PhraseDB::~PhraseDB(class PhraseDB * const this /* r29 */) {
    // Local variables
    int i; // r31
}

// Range: 0x802F52F4 -> 0x802F53AC
class PhraseList & PhraseDB::GetPhraseList(const class PhraseDB * const this /* r29 */, int track /* r30 */, enum BeatmatchPhraseType type /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PP20PhraseListCollection; // size: 0x8, address: 0x808CD130
struct {
    // total size: 0x8
} __RTTI__PP10PhraseList; // size: 0x8, address: 0x808CD148
struct {
    // total size: 0x8
} __RTTI__P6Phrase; // size: 0x8, address: 0x808CD160

