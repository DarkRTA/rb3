/*
    Compile unit: C:\rockband2\system\src\synth\SynthSample.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805970E8 -> 0x80598174
*/
class DataArray * types; // size: 0x4, address: 0x80A54800
class FileLoader * sLoader; // size: 0x4, address: 0x80A54808
class SynthSample * sLoading; // size: 0x4, address: 0x80A5480C
// Range: 0x805970E8 -> 0x805970F8
static void * SampleAlloc() {}

// Range: 0x805970F8 -> 0x80597164
void SynthSample::Init() {
    // References
    // -> class Symbol name;
}

// Range: 0x80597164 -> 0x805971DC
void * SynthSample::SynthSample(class SynthSample * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__11SynthSample;
}

// Range: 0x805971DC -> 0x80597234
void SynthSample::SetFile(class SynthSample * const this /* r31 */) {
    // References
    // -> class FilePath sRoot;
}

// Range: 0x80597234 -> 0x80597300
void * SynthSample::~SynthSample(class SynthSample * const this /* r30 */) {
    // References
    // -> class FileLoader * sLoader;
    // -> class SynthSample * sLoading;
    // -> struct [anonymous] __vt__11SynthSample;
}

// Range: 0x80597300 -> 0x80597308
int SynthSample::GetSampleRate() {}

// Range: 0x80597308 -> 0x80597310
enum Format SynthSample::GetFormat() {}

// Range: 0x80597310 -> 0x80597328
void SynthSample::SetIsLooped() {}

// Range: 0x80597328 -> 0x80597330
unsigned char SynthSample::GetIsLooped() {}

// Range: 0x80597330 -> 0x80597348
void SynthSample::SetLoopStartSamp() {}

// Range: 0x80597348 -> 0x80597350
int SynthSample::GetLoopStartSamp() {}

// Range: 0x80597350 -> 0x80597368
void SynthSample::SetLoopEndSamp() {}

// Range: 0x80597368 -> 0x805974A0
void SynthSample::Sync(class SynthSample * const this /* r29 */) {
    // Local variables
    class FileLoader * l; // r30
    int size; // r1+0x8
    class BufStream bs; // r1+0xC

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10FileLoader;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x805974A0 -> 0x805974E4
void SynthSample::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805974E4 -> 0x80597540
void SynthSample::Load(class SynthSample * const this /* r30 */, class BinStream & s /* r31 */) {}

// Range: 0x80597540 -> 0x805976C0
void SynthSample::PreLoad(class SynthSample * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class SynthSample * sLoading;
    // -> class FileLoader * sLoader;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10FileLoader;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
}

// Range: 0x805976C0 -> 0x805976F4
void SynthSample::PostLoad() {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class SynthSample * sLoading;
    // -> class FileLoader * sLoader;
}

// Range: 0x805976F4 -> 0x805977A8
void SynthSample::Copy(class SynthSample * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class SynthSample * s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11SynthSample;
}

// Range: 0x805977A8 -> 0x80597A50
class DataNode SynthSample::Handle(class SynthSample * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A54814
static class Symbol _s; // size: 0x4, address: 0x80A5481C
static class Symbol _s; // size: 0x4, address: 0x80A54824
static class Symbol _s; // size: 0x4, address: 0x80A5482C
static class Symbol _s; // size: 0x4, address: 0x80A54834
static class Symbol _s; // size: 0x4, address: 0x80A5483C
static class Symbol _s; // size: 0x4, address: 0x80A54844
// Range: 0x80597A50 -> 0x805980A4
unsigned char SynthSample::SyncProperty(class SynthSample * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
}

// Range: 0x805980A4 -> 0x805980C4
int SynthSample::GetPlatformSize() {}

// Range: 0x805980C4 -> 0x80598174
class DataNode SynthSample::OnBankSize(unsigned char kB /* r31 */) {
    // Local variables
    int mem; // r0

    // References
    // -> class Synth * TheSynth;
}

struct {
    // total size: 0x60
} __vt__11SynthSample; // size: 0x60, address: 0x80920BF8

