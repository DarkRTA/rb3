/*
    Compile unit: C:\rockband2\system\src\midi\MidiReader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803BC6B8 -> 0x803BDB00
*/
class MidiChunkID {
    // total size: 0x4
    char mStr[4]; // offset 0x0, size 0x4
};
class MidiChunkID kMThd; // size: 0x4, address: 0x80A51758
class MidiChunkID kMTrk; // size: 0x4, address: 0x80A5175C
// Range: 0x803BC6B8 -> 0x803BC800
static unsigned char DefaultMidiLess() {}

unsigned char sVerify; // size: 0x1, address: 0x80A51760
// Range: 0x803BC800 -> 0x803BC8E8
void * MidiReader::MidiReader(class MidiReader * const this /* r29 */, class BinStream & stream /* r0 */, class MidiReceiver & recvr /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BC8E8 -> 0x803BC960
void MidiReader::Init(class MidiReader * const this /* r31 */) {}

// Range: 0x803BC960 -> 0x803BCB3C
void * MidiReader::~MidiReader(class MidiReader * const this /* r30 */) {}

// Range: 0x803BCC10 -> 0x803BCC74
void MidiReader::ReadAllTracks(class MidiReader * const this /* r31 */) {}

// Range: 0x803BCC74 -> 0x803BCCE4
unsigned char MidiReader::ReadSomeEvents(class MidiReader * const this /* r29 */, int num_events /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x803BCCE4 -> 0x803BCD38
unsigned char MidiReader::ReadTrack(class MidiReader * const this /* r31 */) {}

// Range: 0x803BCD38 -> 0x803BCDDC
void MidiReader::SkipCurrentTrack(class MidiReader * const this /* r31 */) {}

// Range: 0x803BCDDC -> 0x803BCDE4
char * MidiReader::GetFilename() {}

// Range: 0x803BCDE4 -> 0x803BCE78
void MidiReader::ReadNextEvent(class MidiReader * const this /* r31 */) {
    // Local variables
    const char * _err; // r4

    // References
    // -> long TheDebugJump[100];
    // -> class Debug TheDebug;
    // -> unsigned char sVerify;
}

// Range: 0x803BCE78 -> 0x803BCEB8
void MidiReader::ReadNextEventImpl() {}

class MidiChunkHeader {
    // total size: 0x8
    class MidiChunkID mID; // offset 0x0, size 0x4
    unsigned int mLength; // offset 0x4, size 0x4
};
// Range: 0x803BCEB8 -> 0x803BD0E8
void MidiReader::ReadFileHeader(class MidiReader * const this /* r29 */, class BinStream & stream /* r30 */) {
    // Local variables
    class MidiChunkHeader hdr; // r1+0x10
    signed short format; // r1+0x8

    // References
    // -> class MidiChunkID kMThd;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BD0E8 -> 0x803BD228
void MidiReader::ReadTrackHeader(class MidiReader * const this /* r29 */, class BinStream & stream /* r30 */) {
    // Local variables
    class MidiChunkHeader trackHdr; // r1+0x8

    // References
    // -> class MidiChunkID kMTrk;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class MidiVarLenNumber {
    // total size: 0x4
    int mValue; // offset 0x0, size 0x4
};
// Range: 0x803BD228 -> 0x803BD3F8
void MidiReader::ReadEvent(class MidiReader * const this /* r29 */, class BinStream & stream /* r30 */) {
    // Local variables
    unsigned char status; // r1+0x9
    unsigned char data1; // r1+0x8
    unsigned char runningStatus; // r27
    class MidiVarLenNumber deltaTick; // r1+0xC
    int curTick; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BD3F8 -> 0x803BD518
void MidiReader::ReadMidiEvent(class MidiReader * const this /* r28 */, int tick /* r29 */, unsigned char status /* r30 */, unsigned char data1 /* r31 */) {
    // Local variables
    unsigned char data2; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803BD518 -> 0x803BD5D4
void MidiReader::ReadSystemEvent(class MidiReader * const this /* r29 */, int tick /* r30 */, class BinStream & stream /* r31 */) {
    // Local variables
    class MidiVarLenNumber len; // r1+0xC
    unsigned char type; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803BD5D4 -> 0x803BD930
void MidiReader::ReadMetaEvent(class MidiReader * const this /* r27 */, int tick /* r28 */, unsigned char type /* r25 */, class BinStream & stream /* r29 */) {
    // Local variables
    class MidiVarLenNumber len; // r1+0x1C
    int startPos; // r0
    char s[256]; // r1+0x20
    unsigned char a; // r1+0xC
    unsigned char b; // r1+0xB
    unsigned char c; // r1+0xA
    int tempo; // r26
    unsigned char numer; // r1+0x9
    unsigned char denomExp; // r1+0x8
    int denom; // r26
    int m; // r1+0x18
    int b; // r1+0x14
    int t; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BD930 -> 0x803BD9E8
void MidiReader::QueueChannelMsg() {
    // Local variables
    struct Midi m; // r1+0x10
}

// Range: 0x803BD9E8 -> 0x803BDB00
void MidiReader::ProcessMidiList(class MidiReader * const this /* r31 */) {
    // Local variables
    struct Midi * it; // r30
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ210MidiReader4Midi; // size: 0x8, address: 0x808E0108

