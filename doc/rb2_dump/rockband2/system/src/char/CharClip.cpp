/*
    Compile unit: C:\rockband2\system\src\char\CharClip.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80327A78 -> 0x8032B960
*/
static class Symbol ccg; // size: 0x4, address: 0x80A50AA4
// Range: 0x80327A78 -> 0x80327CE4
unsigned char CharClip::Match(class CharClip * const this /* r29 */, const class DataNode & n /* r30 */) {
    // Local variables
    class DataArray * d; // r31
    int i; // r30
    const char * str; // r30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
    // -> static class Symbol ccg;
}

// Range: 0x80327CE4 -> 0x80327CF8
void * FrameEvent::FrameEvent() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80327CF8 -> 0x80327D14
void * FrameEvent::FrameEvent() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80327D14 -> 0x80327D28
class FrameEvent & FrameEvent::__as() {}

// Range: 0x80327D28 -> 0x80327D80
void FrameEvent::Save(class FrameEvent * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80327D80 -> 0x80327DD0
void FrameEvent::Load(class FrameEvent * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80327DD0 -> 0x80327EC0
void * CharClip::CharClip(class CharClip * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__8CharClip;
}

// Range: 0x80327EC0 -> 0x80327FF0
void * CharClip::~CharClip(class CharClip * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__8CharClip;
}

// Range: 0x80327FF0 -> 0x80328068
void CharClip::StuffBones(class CharBones & bones /* r30 */) {
    // Local variables
    class list b; // r1+0x18
}

// Range: 0x80328068 -> 0x8032806C
int CharClip::AllocSize() {}

// Range: 0x8032806C -> 0x8032807C
int CharClip::NodesSize() {}

// Range: 0x8032807C -> 0x80328098
void CharClip::SetStart() {}

// Range: 0x80328098 -> 0x803280B4
void CharClip::SetEnd() {}

// Range: 0x803280B4 -> 0x803280D0
void CharClip::SetFramesPerSec() {}

// Range: 0x803280D0 -> 0x803280EC
void CharClip::SetPlayFlags() {}

// Range: 0x803280EC -> 0x80328108
void CharClip::SetFlags() {}

// Range: 0x80328108 -> 0x80328124
void CharClip::SetBlendWidth() {}

// Range: 0x80328124 -> 0x803281F0
unsigned char CharClip::SharesGroups(class CharClip * const this /* r30 */, class CharClip * c /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class Object * o; // r0
    const class CharClipGroup * group; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x803281F0 -> 0x80328218
class CharClipSet * CharClip::GetCharClipSet() {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
}

// Range: 0x80328218 -> 0x80328258
class NodeVector * CharClip::FindNodes() {
    // Local variables
    class NodeVector * n; // r5
}

// Range: 0x80328258 -> 0x803282D0
struct CharGraphNode * CharClip::FindFirstNode(float frame /* f31 */) {
    // Local variables
    const class NodeVector * n; // r0
    int i; // r5
}

// Range: 0x803282D0 -> 0x80328348
struct CharGraphNode * CharClip::FindLastNode(float frame /* f31 */) {
    // Local variables
    const class NodeVector * n; // r0
    int i; // r5
}

static struct CharGraphNode node; // size: 0x8, address: 0x8097DE30
// Range: 0x80328348 -> 0x80328564
struct CharGraphNode * CharClip::FindNode(const class CharClip * const this /* r28 */, class CharClip * clip /* r29 */, float frame /* f31 */) {
    // Local variables
    const struct CharGraphNode * n; // r30
    float beatAlign; // f30
    float endBorder; // f1
    float f; // f2

    // References
    // -> static struct CharGraphNode node;
    // -> class Debug TheDebug;
}

// Range: 0x80328564 -> 0x80328650
void CharClip::Replace(class CharClip * const this /* r29 */) {
    // Local variables
    class NodeVector * n; // r30
    class CharClip * clip; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x80328650 -> 0x803286D0
void CharClip::ClearAllNodes(class CharClip * const this /* r30 */) {
    // Local variables
    const class NodeVector * n; // r31
}

// Range: 0x803286D0 -> 0x80328774
void CharClip::RemoveNodes(class CharClip * const this /* r29 */, class CharClip * clip /* r30 */) {
    // Local variables
    class NodeVector * n; // r31
    char * next; // r30
}

// Range: 0x80328774 -> 0x803288A4
class NodeVector * CharClip::ResizeNodes(class CharClip * const this /* r27 */, int newSize /* r28 */, const class NodeVector * old /* r29 */) {
    // Local variables
    int n; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803288A4 -> 0x80328A1C
void CharClip::AddNode(class CharClip * const this /* r28 */, class CharClip * clip /* r29 */, const struct CharGraphNode & node /* r30 */) {
    // Local variables
    class NodeVector * n; // r31
    int newSize; // r0
    int moveSize; // r29
    int i; // r5
    int j; // r6
}

// Range: 0x80328A1C -> 0x80328A58
void CharClip::SortEvents(class CharClip * const this /* r4 */) {}

struct SortByFrame {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
static int gRev; // size: 0x4, address: 0x80A50AAC
// Range: 0x80328A58 -> 0x80328CDC
void CharClip::Save(class CharClip * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int count; // r4
    class NodeVector * n; // r3
    class NodeVector * n; // r28
    int i; // r27
    int i; // r27
}

// Range: 0x80328CDC -> 0x80328D70
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class ObjectDir * sdir; // size: 0x4, address: 0x80A50AB0
// Range: 0x80328D70 -> 0x803296AC
void CharClip::Load(class CharClip * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int num; // r1+0x40
    int i; // r27
    char name[256]; // r1+0x220
    int numNodes; // r1+0x3C
    int j; // r26
    struct CharGraphNode n; // r1+0x58
    int maxSize; // r1+0x38
    int num; // r1+0x34
    class NodeVector * start; // r26
    class NodeVector * n; // r25
    int i; // r24
    char name[256]; // r1+0x120
    int j; // r28
    int size; // r1+0x30
    int j; // r27
    struct CharGraphNode n; // r1+0x50
    int num; // r1+0x2C
    class String tmp; // r1+0x90
    int i; // r24
    int num; // r1+0x28
    int i; // r24
    class String s; // r1+0x84
    float lastFrame; // f31
    int num; // r1+0x24
    int i; // r24
    float frame; // r1+0x20

    // References
    // -> static class ObjectDir * sdir;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803296AC -> 0x803298AC
void CharClip::Copy(class CharClip * const this /* r30 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class CharClip * c; // r0
    int i; // r27

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x803298AC -> 0x803298DC
void CharClip::SetDefaultBlend() {
    // Local variables
    int f; // r1+0x8
}

// Range: 0x803298DC -> 0x8032990C
void CharClip::SetDefaultLoop() {
    // Local variables
    int f; // r1+0x8
}

// Range: 0x8032990C -> 0x80329944
void CharClip::SetBeatAlignMode() {
    // Local variables
    int f; // r1+0x8
}

// Range: 0x80329944 -> 0x803299FC
int CharClip::InGroups(class CharClip * const this /* r30 */) {
    // Local variables
    int count; // r31
    struct _List_iterator i; // r1+0x18
    class Object * o; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

static class Symbol s; // size: 0x4, address: 0x80A50AB8
// Range: 0x803299FC -> 0x80329B54
void CharClip::MakeMRU(class CharClip * const this /* r30 */) {
    // Local variables
    class CharClipGroup * groups[256]; // r1+0x20
    int num; // r31
    struct _List_iterator i; // r1+0x1C
    class Object * o; // r28
    class CharClipGroup * g; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
    // -> static class Symbol s;
}

// Range: 0x80329B54 -> 0x80329C78
void CharClip::LockAndDelete(class CharClip * * deathRow /* r29 */, int count /* r30 */, int remaining /* r31 */) {
    // Local variables
    int i; // r5
    class CharClip * c; // r6
    class CharClip * c; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A50AC0
static class Symbol _s; // size: 0x4, address: 0x80A50AC8
static class Symbol _s; // size: 0x4, address: 0x80A50AD0
static class Symbol _s; // size: 0x4, address: 0x80A50AD8
static class Symbol _s; // size: 0x4, address: 0x80A50AE0
// Range: 0x80329C78 -> 0x8032A470
class DataNode CharClip::Handle(class CharClip * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8032A470 -> 0x8032A5DC
class DataNode CharClip::OnGroups(class DataNode * n /* r29 */, class CharClip * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class Object * o; // r0
    class CharClipGroup * group; // r3

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13CharClipGroup;
}

// Range: 0x8032A5DC -> 0x8032A8B8
float CharClip::CheckStick(class CharClip * const this /* r27 */, float tolerance /* f30 */) {
    // Local variables
    class RndTransformable * stick; // r28
    class RndTransformable * arm; // r30
    class CharBonesMeshes bones; // r1+0x30
    class Vector3 stickDown; // r1+0x20
    class Vector3 armDown; // r1+0x10
    float angle; // f31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Symbol _s; // size: 0x4, address: 0x80A50AE8
static class Symbol _s; // size: 0x4, address: 0x80A50AF0
// Range: 0x8032A8B8 -> 0x8032AA84
unsigned char PropSync(class FrameEvent & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A50AF8
static class Symbol _s; // size: 0x4, address: 0x80A50B00
static class Symbol _s; // size: 0x4, address: 0x80A50B08
static class Symbol _s; // size: 0x4, address: 0x80A50B10
static class Symbol _s; // size: 0x4, address: 0x80A50B18
static class Symbol _s; // size: 0x4, address: 0x80A50B20
static class Symbol _s; // size: 0x4, address: 0x80A50B28
static class Symbol _s; // size: 0x4, address: 0x80A50B30
static class Symbol _s; // size: 0x4, address: 0x80A50B38
static class Symbol _s; // size: 0x4, address: 0x80A50B40
static class Symbol _s; // size: 0x4, address: 0x80A50B48
static class Symbol _s; // size: 0x4, address: 0x80A50B50
static class Symbol _s; // size: 0x4, address: 0x80A50B58
static class Symbol _s; // size: 0x4, address: 0x80A50B60
static class Symbol _s; // size: 0x4, address: 0x80A50B68
static class Symbol _s; // size: 0x4, address: 0x80A50B70
static class Symbol _s; // size: 0x4, address: 0x80A50B78
static class Symbol _s; // size: 0x4, address: 0x80A50B80
static class Symbol _s; // size: 0x4, address: 0x80A50B88
// Range: 0x8032AA84 -> 0x8032B76C
unsigned char CharClip::SyncProperty(class CharClip * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
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

// Range: 0x8032B76C -> 0x8032B960
unsigned char PropSync(class vector & v /* r31 */, class DataNode & n /* r26 */, class DataArray * prop /* r27 */, int i /* r30 */, enum PropOp op /* r29 */) {
    // Local variables
    class FrameEvent * it; // r28
    class FrameEvent tmp; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xA8
} __vt__8CharClip; // size: 0xA8, address: 0x808D1910
struct {
    // total size: 0x8
} __RTTI__PQ28CharClip10FrameEvent; // size: 0x8, address: 0x808D1A88

