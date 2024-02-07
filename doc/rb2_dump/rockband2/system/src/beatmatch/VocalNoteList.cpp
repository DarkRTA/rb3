/*
    Compile unit: C:\rockband2\system\src\beatmatch\VocalNoteList.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80306C28 -> 0x80308230
*/
// Range: 0x80306C28 -> 0x80306C74
void * VocalPhrase::VocalPhrase() {}

float gFreestyleMinDurationMs; // size: 0x4, address: 0x80A46CD4
float gFreestylePadMs; // size: 0x4, address: 0x80A46CD8
// Range: 0x80306C74 -> 0x80306DC8
void * VocalNoteList::VocalNoteList(class VocalNoteList * const this /* r28 */) {
    // Local variables
    class DataArray * vox; // r29

    // References
    // -> float gFreestylePadMs;
    // -> float gFreestyleMinDurationMs;
}

// Range: 0x80306DC8 -> 0x80306EE0
void VocalNoteList::AddNote(class VocalNoteList * const this /* r31 */, const class VocalNote & note /* r29 */) {
    // Local variables
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x10
}

// Range: 0x80306EE0 -> 0x803078F4
void VocalNoteList::NotesDone(class VocalNoteList * const this /* r24 */, const class TempoMap & tempoMap /* r25 */) {
    // Local variables
    int firstPhrase; // r26
    class VocalPhrase p; // r1+0xF8
    int noteIdx; // r28
    int phraseIdx; // r27
    unsigned char unpitched; // r26
    int i; // r3
    int i; // r26
    int tick; // r28
    unsigned char continueFreestyle; // r26
    unsigned int i; // r27
    int start; // r28
    class VocalPhrase p; // r1+0xC8
    int deadSpace; // r28
    class VocalPhrase p; // r1+0x98
    int j; // r5
    float startMs; // f0
    float endMs; // f0
    unsigned char cfs; // r4

    // References
    // -> float gFreestylePadMs;
    // -> float gFreestyleMinDurationMs;
    // -> class Debug TheDebug;
}

// Range: 0x803078F4 -> 0x80307A74
float VocalNoteList::PitchAt(const class VocalNoteList * const this /* r30 */, float ms /* r1+0x8 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80307A74 -> 0x80307B10
class VocalNote * VocalNoteList::NextNote(const class VocalNoteList * const this /* r31 */, float ms /* r1+0x8 */) {}

// Range: 0x80307B10 -> 0x80307B6C
int VocalNoteList::NextNoteIndex(const class VocalNoteList * const this /* r31 */) {
    // Local variables
    const class VocalNote * note; // r0
}

// Range: 0x80307B6C -> 0x80307C3C
class VocalNote * VocalNoteList::NoteAt(const class VocalNoteList * const this /* r30 */, float ms /* r1+0x8 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80307C3C -> 0x80307DCC
void VocalNoteList::StartPlayerPhrase(class VocalNoteList * const this /* r29 */, int tick /* r30 */, int player /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80307DCC -> 0x80307F04
void VocalNoteList::EndPlayerPhrase(class VocalNoteList * const this /* r28 */, int tick /* r29 */) {
    // Local variables
    int duration; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80307F04 -> 0x80307F74
void VocalNoteList::AddTambourineGem(int tick /* r1+0x8 */) {}

// Range: 0x80307F74 -> 0x80307F7C
void VocalNoteList::SetSongName() {}

// Range: 0x80307F7C -> 0x80308194
void VocalNoteList::Finalize(class VocalNoteList * const this /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P9VocalNote;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80308194 -> 0x80308230
unsigned char VocalPhrase::PlayableBy(const class VocalPhrase * const this /* r30 */, int activeNum /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


