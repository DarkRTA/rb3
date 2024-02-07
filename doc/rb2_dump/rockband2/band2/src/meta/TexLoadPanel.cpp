/*
    Compile unit: C:\rockband2\band2\src\meta\TexLoadPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80196084 -> 0x80196D80
*/
class DataArray * types; // size: 0x4, address: 0x80A4D070
// Range: 0x80196084 -> 0x8019615C
void * DynamicTex::~DynamicTex(class DynamicTex * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10DynamicTex;
}

// Range: 0x8019615C -> 0x80196164
unsigned char __eq() {}

// Range: 0x80196164 -> 0x801961B8
void TexLoadPanel::Load(class TexLoadPanel * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x801961B8 -> 0x801961FC
unsigned char TexLoadPanel::IsLoaded(class TexLoadPanel * const this /* r31 */) {}

// Range: 0x801961FC -> 0x80196230
void TexLoadPanel::FinishLoad(class TexLoadPanel * const this /* r31 */) {}

// Range: 0x80196230 -> 0x80196314
void TexLoadPanel::Unload(class TexLoadPanel * const this /* r29 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x80196314 -> 0x80196420
void TexLoadPanel::ContentFailed(const char * contentName /* r29 */) {
    // Local variables
    class DLCTex * dlc; // r0
    class String c; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x80196420 -> 0x801964A4
class DLCTex * TexLoadPanel::NextDLCTex(class TexLoadPanel * const this /* r30 */) {
    // Local variables
    class DynamicTex * * d; // r31
    class DLCTex * dlc; // r0

    // References
    // -> struct [anonymous] __RTTI__10DynamicTex;
    // -> struct [anonymous] __RTTI__6DLCTex;
}

// Range: 0x801964A4 -> 0x80196520
unsigned char TexLoadPanel::TexturesLoaded(const class TexLoadPanel * const this /* r30 */) {
    // Local variables
    class DynamicTex * const * tit; // r31
    class DynamicTex * t; // r3
}

static class Symbol register_for_content; // size: 0x4, address: 0x80A4D078
// Range: 0x80196520 -> 0x801965C0
unsigned char TexLoadPanel::RegisterForContent() {
    // Local variables
    class DataArray * r; // r31

    // References
    // -> static class Symbol register_for_content;
}

// Range: 0x801965C0 -> 0x801967AC
void TexLoadPanel::FinalizeTextures(class TexLoadPanel * const this /* r26 */) {
    // Local variables
    class DynamicTex * * tit; // r28
    class DynamicTex * t; // r27

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801967AC -> 0x8019686C
class DynamicTex * TexLoadPanel::AddTex(class TexLoadPanel * const this /* r28 */, const char * path /* r29 */, const char * mat_name /* r30 */, unsigned char new_mat /* r31 */) {
    // Local variables
    class DynamicTex * dt; // r1+0xC
}

// Range: 0x8019686C -> 0x801969A4
void TexLoadPanel::AddDLCTex(class TexLoadPanel * const this /* r26 */, class Symbol & song /* r27 */, const char * mat_name /* r28 */, class RndTex * loading_tex /* r29 */, class RndTex * fail_tex /* r30 */) {
    // References
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4D080
// Range: 0x801969A4 -> 0x80196D80
class DataNode TexLoadPanel::Handle(class TexLoadPanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xF4
} __vt__12TexLoadPanel; // size: 0xF4, address: 0x8089D628
struct {
    // total size: 0xC
} __vt__6DLCTex; // size: 0xC, address: 0x8089D758
struct {
    // total size: 0x8
} __RTTI__6DLCTex; // size: 0x8, address: 0x8089D778
struct {
    // total size: 0xC
} __vt__10DynamicTex; // size: 0xC, address: 0x8089D780
struct {
    // total size: 0x8
} __RTTI__10DynamicTex; // size: 0x8, address: 0x8089D798
struct {
    // total size: 0x8
} __RTTI__PP10DynamicTex; // size: 0x8, address: 0x8089D8C8

