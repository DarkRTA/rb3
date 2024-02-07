/*
    Compile unit: C:\rockband2\system\src\char\CharDriver.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8034C938 -> 0x80351F20
*/
class DataArray * types; // size: 0x4, address: 0x80A50DF0
// Range: 0x8034C938 -> 0x8034CAF4
void * CharDriver::CharDriver(class CharDriver * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__24ObjDirPtr<11CharClipSet>;
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharDriver;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8034CAF4 -> 0x8034CEE4
void * CharDriver::~CharDriver(class CharDriver * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtr<15CharBonesObject,9ObjectDir>;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__24ObjDirPtr<11CharClipSet>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__10CharDriver;
}

// Range: 0x8034CEE4 -> 0x8034CEF4
void CharDriver::Highlight() {}

// Range: 0x8034CEF4 -> 0x8034CF80
void CharDriver::Enter(class CharDriver * const this /* r31 */) {}

// Range: 0x8034CF80 -> 0x8034CFFC
void CharDriver::Exit(class CharDriver * const this /* r31 */) {}

// Range: 0x8034CFFC -> 0x8034D03C
void CharDriver::Clear(class CharDriver * const this /* r31 */) {}

// Range: 0x8034D03C -> 0x8034D2F0
void CharDriver::SetClips(class CharDriver * const this /* r31 */, class ObjDirPtr & c /* r25 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8034D2F0 -> 0x8034D370
void CharDriver::SetBones(class CharDriver * const this /* r30 */, class CharBonesObject * bones /* r31 */) {}

// Range: 0x8034D370 -> 0x8034D388
void CharDriver::SetApply() {}

// Range: 0x8034D388 -> 0x8034D59C
void CharDriver::SyncBones(class CharDriver * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14CharBonesAlloc;
    // -> struct [anonymous] __vt__15CharBonesObject;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8034D59C -> 0x8034D5D8
unsigned char CharDriver::Starved() {}

// Range: 0x8034D5D8 -> 0x8034D6DC
class CharClipDriver * CharDriver::Play(class CharDriver * const this /* r29 */, class CharClip * c /* r30 */, int playFlags /* r31 */, float startFrame /* f30 */, float deltaStart /* f31 */) {}

// Range: 0x8034D6DC -> 0x8034D764
class CharClipDriver * CharDriver::Play(class CharDriver * const this /* r29 */, const class DataNode & n /* r30 */, int playFlags /* r31 */, float startFrame /* f30 */, float deltaStart /* f31 */) {}

// Range: 0x8034D764 -> 0x8034D8A4
class CharClipDriver * CharDriver::PlayGroup(class CharDriver * const this /* r27 */, const char * groupName /* r28 */, int playFlags /* r29 */, float startFrame /* f30 */, float deltaStart /* f31 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct FindRestrictLength {
    // total size: 0xC
    float mLength; // offset 0x0, size 0x4
    int mSafeFlags; // offset 0x4, size 0x4
    const class DataNode & mNode; // offset 0x8, size 0x4
};
// Range: 0x8034D8A4 -> 0x8034DB54
class CharClipDriver * CharDriver::PlayIfSafe(class CharDriver * const this /* r29 */, const class DataNode & n /* r30 */, int playFlags /* r31 */, int safeFlags /* r26 */, float length /* f31 */) {
    // Local variables
    class CharClipDriver * d; // r0
    struct FindRestrictLength match; // r1+0x44
    class String s; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8034DB54 -> 0x8034DBA8
void CharDriver::ExitUnplaying(class CharDriver * const this /* r31 */) {}

// Range: 0x8034DBA8 -> 0x8034DBB4
void CharDriver::SetStarved() {}

// Range: 0x8034DBB4 -> 0x8034DC4C
void CharDriver::SetBeatScale(class CharDriver * const this /* r31 */, float newScale /* f31 */) {
    // Local variables
    class CharClipDriver * fp; // r3
    float invScale; // f1
    class CharClipDriver * cd; // r6
}

// Range: 0x8034DC4C -> 0x8034DD64
float CharDriver::EvaluateFlags(int flags /* r30 */) {
    // Local variables
    float weight; // f30
    float flagWeight; // f29
    class CharClipDriver * cd; // r31
    float w; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8034DD64 -> 0x8034DD88
class CharClipDriver * CharDriver::Last() {
    // Local variables
    class CharClipDriver * cd; // r3
}

// Range: 0x8034DD88 -> 0x8034DDAC
class CharClipDriver * CharDriver::Before() {
    // Local variables
    class CharClipDriver * cd; // r3
}

// Range: 0x8034DDAC -> 0x8034DDD4
class CharClipDriver * CharDriver::FirstPlaying() {
    // Local variables
    class CharClipDriver * cd; // r3
}

// Range: 0x8034DDD4 -> 0x8034DF00
class CharClipDriver * CharDriver::MostPlaying() {
    // Local variables
    float maxWeight; // f30
    class CharClipDriver * best; // r31
    float weight; // f29
    class CharClipDriver * cd; // r30
    float w; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8034DF00 -> 0x8034DF18
static class CharClip * ClipOf() {}

// Range: 0x8034DF18 -> 0x8034DF20
class CharClip * CharDriver::FirstClip() {}

// Range: 0x8034DF20 -> 0x8034DF44
class CharClip * CharDriver::LastClip() {}

// Range: 0x8034DF44 -> 0x8034DF68
class CharClip * CharDriver::FirstPlayingClip() {}

// Range: 0x8034DF68 -> 0x8034DFB0
void CharDriver::Offset(class CharDriver * const this /* r31 */) {}

// Range: 0x8034DFB0 -> 0x8034E030
void CharDriver::PollDeps() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8034E030 -> 0x8034E084
void CharDriver::Replace(class CharDriver * const this /* r30 */, class Object * from /* r31 */) {}

// Range: 0x8034E084 -> 0x8034E0E0
void CharDriver::Load(class CharDriver * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A50DF8
static class FilePath sClipsPath; // size: 0xC, address: 0x8097DFB4
static class Message msg; // size: 0x8, address: 0x8097DFD0
// Range: 0x8034E0E0 -> 0x8034ED68
void CharDriver::PreLoad(class CharDriver * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int tmp; // r1+0x18
    class ObjPtr p; // r1+0x3C

    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __vt__32ObjPtr<11CharClipSet,9ObjectDir>;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> static class FilePath sClipsPath;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8034ED68 -> 0x8034F008
void CharDriver::PostLoad(class CharDriver * const this /* r31 */, class BinStream & d /* r25 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> static int gRev;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8034F008 -> 0x8034F350
void CharDriver::Copy(class CharDriver * const this /* r31 */, const class Object * o /* r25 */, enum CopyType type /* r24 */) {
    // Local variables
    const class CharDriver * d; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharDriver;
}

static class Symbol _s; // size: 0x4, address: 0x80A50E00
static class Symbol _s; // size: 0x4, address: 0x80A50E08
static class Symbol _s; // size: 0x4, address: 0x80A50E10
static class Symbol _s; // size: 0x4, address: 0x80A50E18
static class Symbol _s; // size: 0x4, address: 0x80A50E20
static class Symbol _s; // size: 0x4, address: 0x80A50E28
static class Symbol _s; // size: 0x4, address: 0x80A50E30
static class Symbol _s; // size: 0x4, address: 0x80A50E38
static class Symbol _s; // size: 0x4, address: 0x80A50E40
static class Symbol _s; // size: 0x4, address: 0x80A50E48
static class Symbol _s; // size: 0x4, address: 0x80A50E50
static class Symbol _s; // size: 0x4, address: 0x80A50E58
static class Symbol _s; // size: 0x4, address: 0x80A50E60
static class Symbol _s; // size: 0x4, address: 0x80A50E68
static class Symbol _s; // size: 0x4, address: 0x80A50E70
static class Symbol _s; // size: 0x4, address: 0x80A50E78
// Range: 0x8034F350 -> 0x8034FD24
class DataNode CharDriver::Handle(class CharDriver * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28
    class DataNode _n; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class FilePath sClipsPath;
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

// Range: 0x8034FD24 -> 0x803508E8
class DataNode CharDriver::OnLoadClips(class CharDriver * const this /* r30 */, const class DataArray * msg /* r24 */) {
    // Local variables
    unsigned char async; // r0

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__24ObjDirPtr<11CharClipSet>;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x803508E8 -> 0x803509D0
class DataNode CharDriver::OnPlay(class CharDriver * const this /* r29 */, const class DataArray * msg /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803509D0 -> 0x80350A94
class DataNode CharDriver::OnPlayIfSafe(class CharDriver * const this /* r28 */, const class DataArray * msg /* r29 */) {}

// Range: 0x80350A94 -> 0x80350B84
class DataNode CharDriver::OnPlayGroup(class CharDriver * const this /* r29 */, const class DataArray * msg /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80350B84 -> 0x80350D5C
class DataNode CharDriver::OnPlayGroupFlags(class CharDriver * const this /* r27 */, const class DataArray * msg /* r28 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80350D5C -> 0x80350DAC
class DataNode CharDriver::OnGetFirstPlayingFlags() {
    // Local variables
    class CharClip * clip; // r0
}

// Range: 0x80350DAC -> 0x80350DFC
class DataNode CharDriver::OnGetFirstFlags() {
    // Local variables
    class CharClip * clip; // r0
}

// Range: 0x80350DFC -> 0x80350EAC
class DataNode CharDriver::OnPrint(class CharDriver * const this /* r31 */) {
    // Local variables
    class CharClipDriver * cd; // r31

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A50E80
static class Symbol _s; // size: 0x4, address: 0x80A50E88
static class Symbol _s; // size: 0x4, address: 0x80A50E90
static class Symbol _s; // size: 0x4, address: 0x80A50E98
static class Symbol _s; // size: 0x4, address: 0x80A50EA0
static class Symbol _s; // size: 0x4, address: 0x80A50EA8
static class Symbol _s; // size: 0x4, address: 0x80A50EB0
// Range: 0x80350EAC -> 0x80351D68
unsigned char CharDriver::SyncProperty(class CharDriver * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class FilePath sNull;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__24ObjDirPtr<11CharClipSet>;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15CharBonesObject;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xF8
} __vt__10CharDriver; // size: 0xF8, address: 0x808D4E60
struct {
    // total size: 0x18
} __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>; // size: 0x18, address: 0x808D5068
struct {
    // total size: 0x8
} __RTTI__40ObjOwnerPtr<14CharWeightable,9ObjectDir>; // size: 0x8, address: 0x808D50B8
// Range: 0x80351D68 -> 0x80351DBC
static void __sinit_\CharDriver_cpp() {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class FilePath sClipsPath;
}


