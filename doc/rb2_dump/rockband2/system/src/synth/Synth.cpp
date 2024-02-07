/*
    Compile unit: C:\rockband2\system\src\synth\Synth.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80592298 -> 0x80595A18
*/
class Symbol name; // size: 0x4, address: 0x80A5471C
class Symbol name; // size: 0x4, address: 0x80A54724
static float kDBWidth; // size: 0x4, address: 0x80A57CF8
// Range: 0x80592298 -> 0x805923AC
class DataNode returnMasterKey(class DataArray * msg /* r28 */) {
    // Local variables
    unsigned char someMasher[64]; // r1+0x10
    unsigned char callName[4]; // r1+0x8
    int i; // r5
    class DataArray * a; // r29
    unsigned long masher; // r0
}

class Synth * TheSynth; // size: 0x4, address: 0x80A54728
// Range: 0x805923AC -> 0x805924F0
void * Synth::Synth(class Synth * const this /* r29 */) {
    // Local variables
    const class DataArray * data; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Synth * TheSynth;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__11ByteGrinder;
    // -> struct [anonymous] __vt__5Synth;
}

// Range: 0x805924F0 -> 0x80592574
static class Loader * WavFactory(const class FilePath & file /* r29 */, enum LoaderPos pos /* r30 */) {
    // References
    // -> class Synth * TheSynth;
}

// Range: 0x80592574 -> 0x80592BCC
void Synth::Init(class Synth * const this /* r30 */) {
    // Local variables
    class DataArray * cfg; // r29
    int i; // r29

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
}

class SynthDir : public ObjectDir {
    // total size: 0xAC
};
// Range: 0x80592BCC -> 0x80592C84
void Synth::InitSecurity(class Synth * const this /* r29 */) {
    // Local variables
    char functionName[256]; // r1+0x10
    int i; // r31
    int j; // r30
}

// Range: 0x80592C84 -> 0x80592E50
void Synth::Terminate(class Synth * const this /* r31 */) {}

// Range: 0x80592E50 -> 0x80592E58
void Synth::SetMasterVolume() {}

// Range: 0x80592E58 -> 0x80592E64
float Synth::GetMasterVolume() {}

// Range: 0x80592E64 -> 0x80592F24
void Synth::Poll(class Synth * const this /* r31 */) {
    // Local variables
    int i; // r6
}

// Range: 0x80592F24 -> 0x80593178
void Synth::SetFX(class Synth * const this /* r25 */, const class DataArray * data /* r26 */) {
    // Local variables
    int core; // r28
    const char * name; // r0
    const class DataArray * coreData; // r27
    float volume; // f31
    float delay; // f30
    float feedback; // f29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80593178 -> 0x805931F8
void Synth::RegisterBank(class ObjectDir * dir /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std23_List_node<P9ObjectDir>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std23_List_node<P9ObjectDir>; // size: 0x8, address: 0x8091FF58
// Range: 0x805931F8 -> 0x80593294
void Synth::UnregisterBank(class ObjectDir * dir /* r31 */) {}

// Range: 0x80593294 -> 0x8059329C
int Synth::GetNumMics() {}

// Range: 0x8059329C -> 0x80593314
void Synth::StopPlaybackAllMics(class Synth * const this /* r30 */) {
    // Local variables
    int i; // r31
    class Mic * mic; // r0
}

// Range: 0x80593314 -> 0x8059342C
void Synth::SetMic(class Synth * const this /* r29 */, const class DataArray * data /* r30 */) {
    // Local variables
    int i; // r31
    class Mic * mic; // r0
}

// Range: 0x8059342C -> 0x80593480
class Mic * Synth::GetMic(class Synth * const this /* r30 */, int i /* r31 */) {}

// Range: 0x80593480 -> 0x80593504
void SynthTerminate() {
    // References
    // -> class Debug TheDebug;
    // -> class Synth * TheSynth;
}

static char cacheFile[256]; // size: 0x100, address: 0x80983420
// Range: 0x80593504 -> 0x80593688
char * Synth::CacheWav(class Synth * const this /* r25 */, const char * wavFile /* r26 */) {
    // Local variables
    enum Platform plat; // r0
    class DepChecker dc; // r1+0x14
    const char * cmd; // r0

    // References
    // -> class Debug TheDebug;
    // -> static char cacheFile[256];
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80593688 -> 0x805936E8
void Synth::ToggleHud(class Synth * const this /* r31 */) {}

// Range: 0x805936E8 -> 0x80593A24
void Synth::DrawMeter(float & y0 /* r29 */, float lvl /* f28 */, float pkLvl /* f29 */) {
    // Local variables
    class Color gray; // r1+0xA0
    class Color black; // r1+0x90
    class Color white; // r1+0x80
    class Color green; // r1+0x70
    class Color red; // r1+0x60
    float labStart; // f1
    float x0; // f31
    float width; // f30
    float fullness; // f28
    class Rect bgr; // r1+0x50
    class Rect fgr; // r1+0x40
    float pkFull; // f2
    class Rect pk; // r1+0x30
    class Color white; // r1+0x20

    // References
    // -> static float kDBWidth;
    // -> class Rnd & TheRnd;
}

// Range: 0x80593A24 -> 0x80593BBC
void Synth::DrawMeterScale(float & y0 /* r31 */) {
    // Local variables
    float meterStartX; // f31
    float meterWidth; // f30
    class Color white; // r1+0x30

    // References
    // -> static float kDBWidth;
    // -> class Rnd & TheRnd;
}

// Range: 0x80593BBC -> 0x80593E8C
float Synth::UpdateOverlay(class Synth * const this /* r31 */, float y0 /* r1+0x10 */) {
    // Local variables
    class Color white; // r1+0x30
    int i; // r29
    int i; // r29
    float lvl; // f31
    float pkLvl; // f2
    struct _List_iterator itr; // r1+0x24
    class Object * o; // r29
    class Sfx * sfx; // r3

    // References
    // -> struct [anonymous] __RTTI__13SynthPollable;
    // -> struct [anonymous] __RTTI__3Sfx;
    // -> class list sPollables;
    // -> class Rnd & TheRnd;
}

// Range: 0x80593E8C -> 0x80593F14
class DataNode Synth::OnStartMic(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x80593F14 -> 0x80593F9C
class DataNode Synth::OnStopMic(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x80593F9C -> 0x80593FE4
class DataNode Synth::OnNumConnectedMics() {}

// Range: 0x80593FE4 -> 0x80594078
class DataNode Synth::OnIsMicConnected(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x80594078 -> 0x80594100
class DataNode Synth::OnIsMicRunning(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x80594100 -> 0x80594188
class DataNode Synth::OnIsMicUserTalking(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x80594188 -> 0x80594210
class DataNode Synth::OnMicUserPercentTalking(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x80594210 -> 0x80594284
class DataNode Synth::OnSetMicVolume(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {
    // Local variables
    float vol; // f0
}

// Range: 0x80594284 -> 0x805942F0
class DataNode Synth::OnSetFX(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x805942F0 -> 0x8059438C
class DataNode Synth::OnSetFXVol(class Synth * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x8059438C -> 0x80594418
void Synth::StopAllSfx() {
    // Local variables
    struct _List_iterator itr; // r1+0x18
    class Sequence * seq; // r0

    // References
    // -> struct [anonymous] __RTTI__13SynthPollable;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class list sPollables;
}

// Range: 0x80594418 -> 0x805944B4
void Synth::PauseAllSfx(unsigned char pause /* r31 */) {
    // Local variables
    struct _List_iterator itr; // r1+0x18
    class Sfx * sfx; // r0

    // References
    // -> struct [anonymous] __RTTI__13SynthPollable;
    // -> struct [anonymous] __RTTI__3Sfx;
    // -> class list sPollables;
}

// Range: 0x805944B4 -> 0x805945F4
class DataNode Synth::OnPassthrough(class Synth * const this /* r29 */, class DataArray * msg /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805945F4 -> 0x805946D8
void Synth::Play(class Synth * const this /* r30 */, const char * name /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
}

static class Symbol _s; // size: 0x4, address: 0x80A54730
static class Symbol _s; // size: 0x4, address: 0x80A54738
static class Symbol _s; // size: 0x4, address: 0x80A54740
static class Symbol _s; // size: 0x4, address: 0x80A54748
static class Symbol _s; // size: 0x4, address: 0x80A54750
static class Symbol _s; // size: 0x4, address: 0x80A54758
static class Symbol _s; // size: 0x4, address: 0x80A54760
static class Symbol _s; // size: 0x4, address: 0x80A54768
static class Symbol _s; // size: 0x4, address: 0x80A54770
static class Symbol _s; // size: 0x4, address: 0x80A54778
static class Symbol _s; // size: 0x4, address: 0x80A54780
static class Symbol _s; // size: 0x4, address: 0x80A54788
static class Symbol _s; // size: 0x4, address: 0x80A54790
static class Symbol _s; // size: 0x4, address: 0x80A54798
static class Symbol _s; // size: 0x4, address: 0x80A547A0
static class Symbol _s; // size: 0x4, address: 0x80A547A8
static class Symbol _s; // size: 0x4, address: 0x80A547B0
static class Symbol _s; // size: 0x4, address: 0x80A547B8
static class Symbol _s; // size: 0x4, address: 0x80A547C0
static class Symbol _s; // size: 0x4, address: 0x80A547C8
static class Symbol _s; // size: 0x4, address: 0x80A547D0
static class Symbol _s; // size: 0x4, address: 0x80A547D8
static class Symbol _s; // size: 0x4, address: 0x80A547E0
static class Symbol _s; // size: 0x4, address: 0x80A547E8
// Range: 0x805946D8 -> 0x80595394
class DataNode Synth::Handle(class Synth * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x14
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28
    class DataNode r; // r1+0x20
    class DataNode _n; // r1+0x18

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80595394 -> 0x805953D4
class Stream * Synth::NewStream(float startMs /* f31 */) {}

// Range: 0x805953D4 -> 0x80595414
class Stream * Synth::NewBufStream(float startMs /* f31 */) {}

static char gFakeFile[16]; // size: 0x10, address: 0x80983520
// Range: 0x80595414 -> 0x805954DC
void Synth::NewStreamFile(class File * & fileOut /* r29 */, class Symbol & extOut /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static char gFakeFile[16];
    // -> struct [anonymous] __vt__7BufFile;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class SynthSample * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x805954DC -> 0x80595804
int Synth::GetSampleMem(enum Platform plat /* r30 */) {
    // Local variables
    int tot; // r31
    class ObjDirItr itr; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11SynthSample;
}

// Range: 0x80595804 -> 0x80595920
int Synth::GetFXOverhead() {
    // Local variables
    int fxWorkSizes[10]; // r1+0x20
    const class DataArray * synthData; // r30
    int overhead; // r4
}

// Range: 0x80595920 -> 0x805959D4
int Synth::GetSPUOverhead(class Synth * const this /* r30 */) {
    // Local variables
    const class DataArray * synthData; // r31
    int overhead; // r31
}

// Range: 0x805959D4 -> 0x805959D8
void * FxParamAutoLock::FxParamAutoLock() {}

// Range: 0x805959D8 -> 0x80595A18
void * FxParamAutoLock::~FxParamAutoLock(class FxParamAutoLock * const this /* r31 */) {}

struct {
    // total size: 0xF0
} __vt__5Synth; // size: 0xF0, address: 0x80920460
struct {
    // total size: 0xC
} __vt__11ByteGrinder; // size: 0xC, address: 0x80920580
struct {
    // total size: 0x8
} __RTTI__11ByteGrinder; // size: 0x8, address: 0x80920598
struct {
    // total size: 0x8
} __RTTI__PP3Mic; // size: 0x8, address: 0x80920718
struct _OKToMemCpy {
    // total size: 0x1
};

