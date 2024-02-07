/*
    Compile unit: C:\rockband2\system\src\synth\Sfx.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80588980 -> 0x8058AFC4
*/
class DataArray * types; // size: 0x4, address: 0x80A54630
class Symbol name; // size: 0x4, address: 0x80A54638
// Range: 0x80588980 -> 0x80588AFC
void * SfxInst::SfxInst(class SfxInst * const this /* r29 */, class Sfx * parent /* r30 */) {
    // Local variables
    class SfxMap * itr; // r31
    class SampleInst * samp; // r1+0xC

    // References
    // -> struct [anonymous] __vt__7SfxInst;
}

// Range: 0x80588AFC -> 0x80588C34
void * SfxInst::~SfxInst(class SfxInst * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7SfxInst;
}

// Range: 0x80588C34 -> 0x80588C9C
void SfxInst::StartImpl(class SfxInst * const this /* r30 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588C9C -> 0x80588CEC
void SfxInst::Stop(class SfxInst * const this /* r30 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588CEC -> 0x80588D5C
unsigned char SfxInst::IsRunning(class SfxInst * const this /* r30 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588D5C -> 0x80588DC8
void SfxInst::Pause(class SfxInst * const this /* r29 */, unsigned char pause /* r30 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588DC8 -> 0x80588E28
void SfxInst::SetSend(class SfxInst * const this /* r29 */, class FxSend * send /* r30 */) {
    // Local variables
    class SampleInst * * it; // r31
}

// Range: 0x80588E28 -> 0x80588E88
void SfxInst::SetSpeed(class SfxInst * const this /* r30 */, float speed /* f31 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588E88 -> 0x80588EBC
void SfxInst::SetTranspose(class SfxInst * const this /* r31 */) {}

// Range: 0x80588EBC -> 0x80588F20
void SfxInst::UpdateVolume(class SfxInst * const this /* r30 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588F20 -> 0x80588F80
void SfxInst::SetPan(class SfxInst * const this /* r30 */, float pan /* f31 */) {
    // Local variables
    class SampleInst * * itr; // r31
}

// Range: 0x80588F80 -> 0x80589034
void * Sfx::Sfx(class Sfx * const this /* r31 */) {
    // References
    // -> class Synth * TheSynth;
    // -> struct [anonymous] __vt__31ObjPtrList<7SfxInst,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6FxSend,9ObjectDir>;
    // -> struct [anonymous] __vt__3Sfx;
}

struct Node {
    // total size: 0xC
    class SfxInst * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x80589034 -> 0x80589038
void Sfx::SynthPoll() {}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x80589038 -> 0x805890A8
void Sfx::Pause(unsigned char p /* r31 */) {
    // Local variables
    class iterator itr; // r1+0x18
}

// Range: 0x805890A8 -> 0x80589210
class SeqInst * Sfx::MakeInstImpl(class Sfx * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80589210 -> 0x80589290
unsigned char Sfx::IsPlaying() {
    // Local variables
    class iterator itr; // r1+0x18
}

static class Symbol _s; // size: 0x4, address: 0x80A54640
// Range: 0x80589290 -> 0x805897F4
class DataNode Sfx::Handle(class Sfx * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__32ObjPtr<11SynthSample,9ObjectDir>;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A54648
static class Symbol _s; // size: 0x4, address: 0x80A54650
static class Symbol _s; // size: 0x4, address: 0x80A54658
static class Symbol _s; // size: 0x4, address: 0x80A54660
static class Symbol _s; // size: 0x4, address: 0x80A54668
static class Symbol _s; // size: 0x4, address: 0x80A54670
static class Symbol _s; // size: 0x4, address: 0x80A54678
static class Symbol _s; // size: 0x4, address: 0x80A54680
// Range: 0x805897F4 -> 0x80589FFC
unsigned char PropSync(class ADSR & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A54688
static class Symbol _s; // size: 0x4, address: 0x80A54690
static class Symbol _s; // size: 0x4, address: 0x80A54698
static class Symbol _s; // size: 0x4, address: 0x80A546A0
static class Symbol _s; // size: 0x4, address: 0x80A546A8
static class Symbol _s; // size: 0x4, address: 0x80A546B0
// Range: 0x80589FFC -> 0x8058A4D4
unsigned char PropSync(class SfxMap & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8058A4D4 -> 0x8058A624
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11SynthSample;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A546B8
static class Symbol _s; // size: 0x4, address: 0x80A546C0
static class Symbol _s; // size: 0x4, address: 0x80A546C8
// Range: 0x8058A624 -> 0x8058A810
unsigned char Sfx::SyncProperty(class Sfx * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8058A810 -> 0x8058AB28
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r31 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class SfxMap * it; // r30
    class SfxMap tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11SynthSample,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8058AB28 -> 0x8058AB6C
void Sfx::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8058AB6C -> 0x8058AC74
void Sfx::Load(class Sfx * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0xC
    float sendVolume; // r1+0x8

    // References
    // -> int sRev;
    // -> class Debug TheDebug;
}

// Range: 0x8058AC74 -> 0x8058AF14
void Sfx::Copy(class Sfx * const this /* r26 */, const class Object * o /* r27 */, enum CopyType type /* r25 */) {
    // Local variables
    const class Sfx * sfx; // r0

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11SynthSample,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__3Sfx;
}

// Range: 0x8058AF14 -> 0x8058AFC4
void Sfx::SetSend(class Sfx * const this /* r30 */, class FxSend * send /* r31 */) {
    // Local variables
    class iterator it; // r1+0x18
}

struct {
    // total size: 0x70
} __vt__7SfxInst; // size: 0x70, address: 0x8091EE38
struct {
    // total size: 0x6C
} __vt__3Sfx; // size: 0x6C, address: 0x8091EED8
struct {
    // total size: 0x18
} __vt__31ObjPtrList<7SfxInst,9ObjectDir>; // size: 0x18, address: 0x8091EF70
struct {
    // total size: 0x8
} __RTTI__31ObjPtrList<7SfxInst,9ObjectDir>; // size: 0x8, address: 0x8091EFB8
struct {
    // total size: 0x18
} __vt__32ObjPtr<11SynthSample,9ObjectDir>; // size: 0x18, address: 0x8091F0A0
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11SynthSample,9ObjectDir>; // size: 0x8, address: 0x8091F0E8
struct {
    // total size: 0x8
} __RTTI__PP10SampleInst; // size: 0x8, address: 0x8091F170
struct {
    // total size: 0x8
} __RTTI__P6SfxMap; // size: 0x8, address: 0x8091F188

