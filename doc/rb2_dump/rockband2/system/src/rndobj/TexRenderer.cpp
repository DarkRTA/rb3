/*
    Compile unit: C:\rockband2\system\src\rndobj\TexRenderer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8050263C -> 0x805048B4
*/
class DataArray * types; // size: 0x4, address: 0x80A539D0
// Range: 0x8050263C -> 0x805027F4
void * RndTexRenderer::RndTexRenderer(class RndTexRenderer * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__14RndTexRenderer;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x805027F4 -> 0x80502988
void * RndTexRenderer::~RndTexRenderer(class RndTexRenderer * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__14RndTexRenderer;
}

// Range: 0x80502988 -> 0x80502A14
void RndTexRenderer::ListAnimChildren(class list & anims /* r30 */) {
    // Local variables
    class RndAnimatable * anim; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13RndAnimatable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80502A14 -> 0x80502A9C
void RndTexRenderer::ListDrawChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80502A9C -> 0x80502AA0
void RndTexRenderer::DrawBefore() {}

// Range: 0x80502AA0 -> 0x80502AA4
void RndTexRenderer::DrawAfter() {}

// Range: 0x80502AA4 -> 0x80502AB8
void RndTexRenderer::DrawShowing() {}

static class DebugWarner _dw; // size: 0x100, address: 0x80981730
static class Message preRender; // size: 0x8, address: 0x80981840
// Range: 0x80502AB8 -> 0x80503440
void RndTexRenderer::DrawToTexture(class RndTexRenderer * const this /* r29 */) {
    // Local variables
    class RndCam * cam; // r31
    class Transform curXfm; // r1+0xB0
    float curFov; // f31
    class RndDir * proxy; // r30
    class Transform t; // r1+0x70
    float length; // f30
    float fov; // f0
    int i; // r27

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> class RndCam * sCurrent;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> static class Message preRender;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> class Rnd & TheRnd;
}

// Range: 0x80503440 -> 0x80503480
float RndTexRenderer::StartFrame() {
    // Local variables
    class RndAnimatable * anim; // r0
}

// Range: 0x80503480 -> 0x805034C0
float RndTexRenderer::EndFrame() {
    // Local variables
    class RndAnimatable * anim; // r0
}

// Range: 0x805034C0 -> 0x8050352C
void RndTexRenderer::SetFrame(class RndTexRenderer * const this /* r31 */, float f /* f30 */, float blend /* f31 */) {
    // Local variables
    class RndAnimatable * anim; // r0
}

// Range: 0x8050352C -> 0x80503560
class RndAnimatable * RndTexRenderer::GetAnim() {
    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
}

// Range: 0x80503560 -> 0x8050356C
void RndTexRenderer::AddPreClearDraw() {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8050356C -> 0x80503578
void RndTexRenderer::RemovePreClearDraw() {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80503578 -> 0x805035C0
void RndTexRenderer::UpdatePreClearState(class RndTexRenderer * const this /* r31 */) {}

// Range: 0x805035C0 -> 0x80503750
void RndTexRenderer::Copy(class RndTexRenderer * const this /* r31 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndTexRenderer * e; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
}

// Range: 0x80503750 -> 0x80503794
void RndTexRenderer::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80503794 -> 0x80503B2C
void RndTexRenderer::Load(class RndTexRenderer * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x14
    class FilePath f; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
}

// Range: 0x80503B2C -> 0x8050404C
class DataNode RndTexRenderer::Handle(class RndTexRenderer * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A539D8
static class Symbol _s; // size: 0x4, address: 0x80A539E0
static class Symbol _s; // size: 0x4, address: 0x80A539E8
static class Symbol _s; // size: 0x4, address: 0x80A539F0
static class Symbol _s; // size: 0x4, address: 0x80A539F8
static class Symbol _s; // size: 0x4, address: 0x80A53A00
static class Symbol _s; // size: 0x4, address: 0x80A53A08
static class Symbol _s; // size: 0x4, address: 0x80A53A10
static class Symbol _s; // size: 0x4, address: 0x80A53A18
// Range: 0x8050404C -> 0x805048B4
unsigned char RndTexRenderer::SyncProperty(class RndTexRenderer * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x11C
} __vt__14RndTexRenderer; // size: 0x11C, address: 0x80901D30

