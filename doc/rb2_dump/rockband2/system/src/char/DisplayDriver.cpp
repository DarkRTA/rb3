/*
    Compile unit: C:\rockband2\system\src\char\DisplayDriver.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803A725C -> 0x803A8A10
*/
static float kXOffset; // size: 0x4, address: 0x80A56F58
static float kBarHeight; // size: 0x4, address: 0x80A56F5C
static float kSpacing; // size: 0x4, address: 0x80A56F60
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class MsgSource * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x803A725C -> 0x803A75C4
static class Object * FindSource(class Object * d /* r31 */) {
    // Local variables
    class ObjDirItr p; // r1+0x2C
    struct _List_iterator it; // r1+0x28

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9MsgSource;
    // -> class ObjectDir * sMainDir;
}

static class Message msg; // size: 0x8, address: 0x8097E048
class CharDriverDisplay {
    // total size: 0x20
protected:
    float mBeatScale; // offset 0x0, size 0x4
    class vector mXOffsets; // offset 0x4, size 0xC
    float mYOffset; // offset 0x10, size 0x4
    float mBarWidth; // offset 0x14, size 0x4
    float mEm; // offset 0x18, size 0x4
    float mRight; // offset 0x1C, size 0x4
};
// Range: 0x803A75C4 -> 0x803A7FA8
float CharDriverDisplay::Draw(class CharDriverDisplay * const this /* r23 */, class CharDriver * d /* r24 */, float top /* f30 */) {
    // Local variables
    int count; // r29
    class Object * source; // r30
    float bottom; // f31
    char buffer[256]; // r1+0x100
    class CharClipDriver * cd; // r0
    float frame; // f29
    float sample; // f2
    class CharClipDriver * c; // r22
    class CharClipDriver * entryB; // r28
    int aCount; // r27
    const class NodeVector * nv; // r0
    int i; // r26
    int aOffset; // r21
    int bOffset; // r25
    class Vector2 p; // r1+0x68
    int j; // r20
    class CharClipDriver * c; // r0
    unsigned char first; // r20
    int i; // r21
    class Vector2 p; // r1+0x60
    float height; // f29
    class Rect r; // r1+0xF0

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static float kXOffset;
    // -> static float kSpacing;
    // -> class Rnd & TheRnd;
}

// Range: 0x803A7FA8 -> 0x803A8240
void CharDriverDisplay::SetOffsets(class CharDriverDisplay * const this /* r30 */, float top /* f30 */, class CharDriver * d /* r31 */) {
    // Local variables
    class CharClipDriver * c; // r26
    float tmp; // f31
    int i; // r25

    // References
    // -> static float kXOffset;
    // -> static float kSpacing;
    // -> class Rnd & TheRnd;
}

// Range: 0x803A8240 -> 0x803A83E4
void CharDriverDisplay::DrawTransition(class CharDriverDisplay * const this /* r29 */, class CharClipDriver * d /* r30 */, int which /* r31 */, float frame /* f30 */, float blendWidth /* f31 */) {
    // Local variables
    class Rect r; // r1+0x30

    // References
    // -> class Rnd & TheRnd;
    // -> static float kBarHeight;
}

// Range: 0x803A83E4 -> 0x803A874C
void CharDriverDisplay::DrawTrack(class CharDriverDisplay * const this /* r29 */, int which /* r30 */) {
    // Local variables
    class CharClip * c; // r0
    class Rect r; // r1+0xA0
    class Color col; // r1+0x90
    float kTickHeight; // f30
    float beat; // f29
    float beatScale; // f0
    float firstBeat; // f28
    class Color col; // r1+0x80
    float height; // f27
    class Rect r; // r1+0x70

    // References
    // -> class Rnd & TheRnd;
    // -> static float kBarHeight;
}

// Range: 0x803A874C -> 0x803A884C
void CharDriverDisplay::DrawBeat(class CharDriverDisplay * const this /* r28 */, int which /* r29 */, float beat /* f30 */, const class Color & col /* r30 */) {
    // Local variables
    const char * s; // r0

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x803A884C -> 0x803A8940
void CharDriverDisplay::DrawCursor(class CharDriverDisplay * const this /* r30 */, int which /* r31 */, float frame /* f30 */) {
    // Local variables
    float kOver; // f31
    class Rect r; // r1+0x20

    // References
    // -> class Rnd & TheRnd;
    // -> static float kBarHeight;
}

// Range: 0x803A8940 -> 0x803A8958
float CharDriverDisplay::GetX() {}

// Range: 0x803A8958 -> 0x803A8998
float CharDriverDisplay::GetY() {
    // References
    // -> static float kSpacing;
}

// Range: 0x803A8998 -> 0x803A8A10
float DisplayCharDriver() {
    // Local variables
    class CharDriverDisplay dc; // r1+0x10
}


