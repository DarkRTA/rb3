/*
    Compile unit: C:\rockband2\band2\src\bandtrack\GemSmasher.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8001F1B8 -> 0x8001F9D0
*/
// Range: 0x8001F1B8 -> 0x8001F1D0
void * GemSmasher::GemSmasher() {
    // References
    // -> struct [anonymous] __vt__10GemSmasher;
}

// Range: 0x8001F1D0 -> 0x8001F210
void * GemSmasher::~GemSmasher(class GemSmasher * const this /* r31 */) {}

// Range: 0x8001F210 -> 0x8001F260
class GemSmasher * NewGemSmasher(int slot /* r30 */, class RndDir * dir /* r31 */) {}

// Range: 0x8001F260 -> 0x8001F268
int GemSmasher::Slot() {}

// Range: 0x8001F268 -> 0x8001F278
unsigned char GemSmasher::Null() {}

static class Message msg; // size: 0x8, address: 0x80976B78
// Range: 0x8001F278 -> 0x8001F434
void GemSmasher::Send(class GemSmasher * const this /* r31 */, class Symbol & message /* r30 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80976B90
// Range: 0x8001F434 -> 0x8001F644
void GemSmasher::SetShowing(class GemSmasher * const this /* r30 */, unsigned char showing /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80976BA8
// Range: 0x8001F644 -> 0x8001F854
void GemSmasher::SetGlowing(class GemSmasher * const this /* r30 */, unsigned char glowing /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol glow; // size: 0x4, address: 0x80A48F6C
// Range: 0x8001F854 -> 0x8001F8E4
unsigned char GemSmasher::Glowing(const class GemSmasher * const this /* r31 */) {
    // References
    // -> static class Symbol glow;
}

// Range: 0x8001F8E4 -> 0x8001F9D0
void GemSmasher::SetLOD(const class GemSmasher * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndParticleSys;
}

struct {
    // total size: 0x20
} __vt__10GemSmasher; // size: 0x20, address: 0x8086E630
struct {
    // total size: 0x8
} __RTTI__10GemSmasher; // size: 0x8, address: 0x8086E660

