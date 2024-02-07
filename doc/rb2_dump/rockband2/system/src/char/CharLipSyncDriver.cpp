/*
    Compile unit: C:\rockband2\system\src\char\CharLipSyncDriver.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803803B8 -> 0x80383DC4
*/
class DataArray * types; // size: 0x4, address: 0x80A51210
// Range: 0x803803B8 -> 0x80380598
void * CharLipSyncDriver::CharLipSyncDriver(class CharLipSyncDriver * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
    // -> struct [anonymous] __vt__38ObjPtr<17CharLipSyncDriver,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11CharClipSet,9ObjectDir>;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__17CharLipSyncDriver;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
}

// Range: 0x80380598 -> 0x803809AC
void * CharLipSyncDriver::~CharLipSyncDriver(class CharLipSyncDriver * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11CharClipSet,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__38ObjPtr<17CharLipSyncDriver,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
    // -> struct [anonymous] __vt__17CharLipSyncDriver;
}

// Range: 0x803809AC -> 0x80380B10
void CharLipSyncDriver::Enter(class CharLipSyncDriver * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80380B10 -> 0x80380B90
void CharLipSyncDriver::SetClips(class CharLipSyncDriver * const this /* r30 */, class CharClipSet * c /* r31 */) {}

// Range: 0x80380B90 -> 0x80380DC4
void CharLipSyncDriver::SetSong(class CharLipSyncDriver * const this /* r29 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

static class Timer * _t; // size: 0x4, address: 0x80A51218
// Range: 0x80380DC4 -> 0x80381310
void CharLipSyncDriver::Poll(class CharLipSyncDriver * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC
    float myWeight; // f0
    float audioTime; // f1
    int i; // r27
    float weight; // f28
    class CharClip * clip; // r28
    float frame; // f2
    float audioTime; // f1
    int i; // r26
    float weight; // f28
    class CharClip * clip; // r4
    float frame; // f2

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
}

// Range: 0x80381310 -> 0x80381390
void CharLipSyncDriver::PollDeps() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80381390 -> 0x80381474
void CharLipSyncDriver::Save(class CharLipSyncDriver * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class FilePath sRoot;
    // -> class FilePath sNull;
}

static int gRev; // size: 0x4, address: 0x80A51220
// Range: 0x80381474 -> 0x803814D0
void CharLipSyncDriver::Load(class CharLipSyncDriver * const this /* r30 */, class BinStream & d /* r31 */) {}

static class Message changeSong; // size: 0x8, address: 0x8097E000
// Range: 0x803814D0 -> 0x80381D24
void CharLipSyncDriver::PreLoad(class CharLipSyncDriver * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class FilePath songPath; // r1+0x34

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> static class Message changeSong;
    // -> struct [anonymous] __vt__7Message;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80381D24 -> 0x80381EC0
void CharLipSyncDriver::PostLoad(class CharLipSyncDriver * const this /* r28 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x80381EC0 -> 0x80382230
void CharLipSyncDriver::Copy(class CharLipSyncDriver * const this /* r31 */, const class Object * o /* r29 */, enum CopyType type /* r28 */) {
    // Local variables
    const class CharLipSyncDriver * b; // r0

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17CharLipSyncDriver;
}

static class Symbol _s; // size: 0x4, address: 0x80A51228
// Range: 0x80382230 -> 0x8038264C
class DataNode CharLipSyncDriver::Handle(class CharLipSyncDriver * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8038264C -> 0x80383178
class DataNode CharLipSyncDriver::OnLoadSong(class CharLipSyncDriver * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    unsigned char async; // r0

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

static class Symbol _s; // size: 0x4, address: 0x80A51230
static class Symbol _s; // size: 0x4, address: 0x80A51238
static class Symbol _s; // size: 0x4, address: 0x80A51240
static class Symbol _s; // size: 0x4, address: 0x80A51248
static class Symbol _s; // size: 0x4, address: 0x80A51250
static class Symbol _s; // size: 0x4, address: 0x80A51258
static class Symbol _s; // size: 0x4, address: 0x80A51260
// Range: 0x80383178 -> 0x80383C68
unsigned char CharLipSyncDriver::SyncProperty(class CharLipSyncDriver * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class FilePath sNull;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80383C68 -> 0x80383DC4
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17CharLipSyncDriver;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xC4
} __vt__17CharLipSyncDriver; // size: 0xC4, address: 0x808D9AB0
struct {
    // total size: 0x8
} __RTTI__17CharLipSyncDriver; // size: 0x8, address: 0x808D9BB8
struct {
    // total size: 0x18
} __vt__38ObjPtr<17CharLipSyncDriver,9ObjectDir>; // size: 0x18, address: 0x808D9C10
struct {
    // total size: 0x8
} __RTTI__38ObjPtr<17CharLipSyncDriver,9ObjectDir>; // size: 0x8, address: 0x808D9C60

