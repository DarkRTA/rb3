/*
    Compile unit: C:\rockband2\system\src\char\CharClipDriver.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8032D060 -> 0x8032E290
*/
// Range: 0x8032D060 -> 0x8032D168
void * CharClipDriver::CharClipDriver(class CharClipDriver * const this /* r29 */, class Object * owner /* r30 */, const class CharClipDriver & d /* r31 */) {
    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>;
}

// Range: 0x8032D168 -> 0x8032D1E8
void * CharClipDriver::~CharClipDriver(class CharClipDriver * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>;
}

static class Symbol exit; // size: 0x4, address: 0x80A50B9C
// Range: 0x8032D1E8 -> 0x8032D28C
class CharClipDriver * CharClipDriver::Exit(class CharClipDriver * const this /* r30 */, unsigned char stack /* r31 */) {
    // Local variables
    class CharClipDriver * next; // r31

    // References
    // -> static class Symbol exit;
}

// Range: 0x8032D28C -> 0x8032D2D4
void CharClipDriver::DeleteStack(class CharClipDriver * const this /* r31 */) {}

// Range: 0x8032D2D4 -> 0x8032D33C
class CharClipDriver * CharClipDriver::DeleteClip(class CharClipDriver * const this /* r31 */) {}

// Range: 0x8032D33C -> 0x8032DA1C
float CharClipDriver::Evaluate(class CharClipDriver * const this /* r31 */, float frame /* f29 */, float dframe /* f30 */, float dt /* f27 */) {
    // Local variables
    float nextWeight; // f31
    unsigned char rt; // r0
    unsigned char ut; // r0
    float rampDelta; // f0
    float oldFrame; // f28
    float delta; // f0
    float dfrac; // f1
    float length; // f28
    float length; // f28
    float w; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032DA1C -> 0x8032DB3C
void CharClipDriver::ScaleAdd(class CharClipDriver * const this /* r30 */, class CharBones & bones /* r31 */, float weight /* f30 */) {
    // Local variables
    float w; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032DB3C -> 0x8032DC90
void CharClipDriver::RotateTo(class CharClipDriver * const this /* r30 */, class CharBones & bones /* r31 */, float weight /* f30 */) {
    // Local variables
    float w; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8032DC90 -> 0x8032DDD0
float CharClipDriver::AlignToFrame(class CharClipDriver * const this /* r31 */) {
    // Local variables
    float alignBeat; // f31
    float delta; // f30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol enter; // size: 0x4, address: 0x80A50BA4
static class DataNode & instant; // size: 0x4, address: 0x80A50BAC
// Range: 0x8032DDD0 -> 0x8032DFB4
void CharClipDriver::PlayEvents(class CharClipDriver * const this /* r31 */, float oldFrame /* f31 */) {
    // Local variables
    float frame; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class DataNode & instant;
    // -> static class Symbol enter;
}

static class DataNode & dude; // size: 0x4, address: 0x80A50BB4
static class Message h; // size: 0x8, address: 0x8097DE60
// Range: 0x8032DFB4 -> 0x8032E290
void CharClipDriver::ExecuteEvent(class CharClipDriver * const this /* r30 */, class Symbol & handler /* r31 */) {
    // References
    // -> static class Message h;
    // -> struct [anonymous] __vt__7Message;
    // -> static class DataNode & dude;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

struct {
    // total size: 0x18
} __vt__33ObjOwnerPtr<8CharClip,9ObjectDir>; // size: 0x18, address: 0x808D1CB0
struct {
    // total size: 0x8
} __RTTI__33ObjOwnerPtr<8CharClip,9ObjectDir>; // size: 0x8, address: 0x808D1CF8

