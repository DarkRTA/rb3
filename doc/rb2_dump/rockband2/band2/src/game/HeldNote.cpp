/*
    Compile unit: C:\rockband2\band2\src\game\HeldNote.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800726F8 -> 0x80072A50
*/
// Range: 0x800726F8 -> 0x80072720
void * HeldNote::HeldNote() {}

// Range: 0x80072720 -> 0x800727A4
void * HeldNote::HeldNote(class HeldNote * const this /* r28 */, enum TrackType type /* r29 */) {
    // Local variables
    int numSlots; // r0

    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x800727A4 -> 0x800727E4
unsigned char HeldNote::IsDone() {}

// Range: 0x800727E4 -> 0x800729A4
float HeldNote::SetHoldTime(class HeldNote * const this /* r30 */, float ms /* f30 */) {
    // Local variables
    float held; // f30
    float total; // f0
    float fraction; // f30
    float points; // f2
    float newPoints; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800729A4 -> 0x80072A50
float HeldNote::GetPointFraction(class HeldNote * const this /* r31 */) {
    // Local variables
    int head; // r5
    float tail; // f1
    int possible; // r7

    // References
    // -> class Debug TheDebug;
    // -> class Scoring * TheScoring;
}


