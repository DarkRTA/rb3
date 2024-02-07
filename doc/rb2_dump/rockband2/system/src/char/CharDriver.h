/*
    Compile unit: C:\rockband2\system\src\char\CharDriver.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80352124 -> 0x80352A94
*/
// Range: 0x80352124 -> 0x803521F8
void CharDriver::Transfer(class CharDriver * const this /* r30 */, const class CharDriver & cd /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803521F8 -> 0x803523A0
class CharClip * CharDriver::FindClip(class CharDriver * const this /* r28 */, const class DataNode & n /* r29 */, unsigned char fail /* r31 */) {
    // Local variables
    class CharClip * c; // r30
    class String s; // r1+0x14

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x803523A0 -> 0x803528BC
void CharDriver::Poll(class CharDriver * const this /* r30 */) {
    // Local variables
    float beat; // f29
    float dbeat; // f31
    const class SongPos & s; // r0
    class CharClipDriver * fp; // r29
    int firstAlign; // r0
    int align; // r28
    class CharClipDriver * cd; // r3
    int beatDiff; // r3
    class CharClipDriver * cd; // r4
    int flags; // r1+0x10
    float weight; // f30
    float w; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803528BC -> 0x80352900
class Symbol CharDriver::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x80352900 -> 0x80352A94
void CharDriver::SetType(class CharDriver * const this /* r29 */, class Symbol & CharDriver /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}


