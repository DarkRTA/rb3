/*
    Compile unit: C:\rockband2\system\src\beatmatch\MidiParserMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802F21B8 -> 0x802F3034
*/
class MidiParserMgr * TheMidiParserMgr; // size: 0x4, address: 0x80A50738
// Range: 0x802F21B8 -> 0x802F2398
void * MidiParserMgr::MidiParserMgr(class MidiParserMgr * const this /* r31 */, class SongData * songData /* r30 */) {
    // Local variables
    class DataArray * d; // r30

    // References
    // -> class ObjectDir * sMainDir;
    // -> class LoadMgr TheLoadMgr;
    // -> class MidiParserMgr * TheMidiParserMgr;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__13MidiParserMgr;
}

// Range: 0x802F2398 -> 0x802F24A4
void * MidiParserMgr::~MidiParserMgr(class MidiParserMgr * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13MidiParserMgr;
}

// Range: 0x802F24A4 -> 0x802F2534
void MidiParserMgr::Reset() {
    // Local variables
    float beat; // f31
    const class list & parsers; // r31
    struct _List_iterator it; // r1+0x18

    // References
    // -> class list sParsers;
}

// Range: 0x802F2534 -> 0x802F25B0
void MidiParserMgr::Reset() {
    // Local variables
    const class list & parsers; // r31
    struct _List_iterator it; // r1+0x18

    // References
    // -> class list sParsers;
}

// Range: 0x802F25B0 -> 0x802F261C
void MidiParserMgr::Poll() {
    // Local variables
    const class list & parsers; // r31
    struct _List_iterator it; // r1+0x18

    // References
    // -> class list sParsers;
}

// Range: 0x802F261C -> 0x802F2784
void MidiParserMgr::FreeAllData(class MidiParserMgr * const this /* r31 */) {
    // Local variables
    int i; // r30
}

// Range: 0x802F2784 -> 0x802F2850
void MidiParserMgr::OnNewTrack(class MidiParserMgr * const this /* r30 */) {
    // Local variables
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x14
}

// Range: 0x802F2850 -> 0x802F2984
void MidiParserMgr::OnEndOfTrack(class MidiParserMgr * const this /* r31 */) {
    // Local variables
    int track; // r4
    class GameGemList * gems; // r30
    const class list & parsers; // r29
    struct _List_iterator it; // r1+0x24
    class MidiParser * mp; // r3

    // References
    // -> class list sParsers;
    // -> const char * gNullStr;
}

// Range: 0x802F2984 -> 0x802F2988
void MidiParserMgr::OnAllTracksRead() {}

// Range: 0x802F2988 -> 0x802F2A08
void MidiParserMgr::FinishLoad(class MidiParserMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802F2A08 -> 0x802F2AC8
void MidiParserMgr::OnMidiMessage(class MidiParserMgr * const this /* r28 */, int tick /* r29 */, unsigned char data1 /* r30 */) {
    // Local variables
    int startTick; // r1+0x20
    const class list & parsers; // r31
    struct _List_iterator it; // r1+0x1C
    class MidiParser * mp; // r3

    // References
    // -> class list sParsers;
}

// Range: 0x802F2AC8 -> 0x802F2B68
char * MidiParserMgr::StripEndBracket(char * buffer /* r30 */) {
    // Local variables
    const char * c; // r5
    char * d; // r31

    // References
    // -> class Debug TheDebug;
    // -> class MidiParserMgr * TheMidiParserMgr;
}

// Range: 0x802F2B68 -> 0x802F2C58
class DataArray * MidiParserMgr::ParseString(class MidiParserMgr * const this /* r29 */, const char * str /* r6 */, int startTick /* r30 */) {
    // Local variables
    char buffer[256]; // r1+0x10
    class DataArray * ret; // r31
    const char * _err; // r8
    const char * m; // r0

    // References
    // -> class MidiParserMgr * TheMidiParserMgr;
    // -> long TheDebugJump[100];
    // -> class Debug TheDebug;
}

// Range: 0x802F2C58 -> 0x802F2D64
void MidiParserMgr::OnText(class MidiParserMgr * const this /* r29 */, int tick /* r30 */, const char * str /* r31 */) {
    // Local variables
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x14
    class DataArray * data; // r0
    struct TextEvent text; // r1+0x18
}

// Range: 0x802F2D64 -> 0x802F2E84
unsigned char MidiParserMgr::CreateNote(class MidiParserMgr * const this /* r27 */, int tick /* r28 */, unsigned char status /* r29 */, unsigned char data1 /* r30 */, int & start_tick /* r31 */) {
    // Local variables
    int onTick; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F2E84 -> 0x802F2EBC
void MidiParserMgr::SetMidiReader(class MidiParserMgr * const this /* r31 */) {}

// Range: 0x802F2EBC -> 0x802F2F40
class DataEventList * MidiParserMgr::GetEventsList(class MidiParserMgr * const this /* r31 */) {
    // Local variables
    class MidiParser * evParser; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F2F40 -> 0x802F3008
class MidiParser * MidiParserMgr::GetParser(class Symbol & name /* r29 */) {
    // Local variables
    const class list & parsers; // r30
    struct _List_iterator it; // r1+0x18

    // References
    // -> const char * gNullStr;
    // -> class list sParsers;
}

struct {
    // total size: 0x30
} __vt__13MidiParserMgr; // size: 0x30, address: 0x808CCE48
struct {
    // total size: 0x8
} __RTTI__13MidiParserMgr; // size: 0x8, address: 0x808CCE98
// Range: 0x802F3008 -> 0x802F3034
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PQ210MidiParser9TextEvent; // size: 0x8, address: 0x808CCED8

