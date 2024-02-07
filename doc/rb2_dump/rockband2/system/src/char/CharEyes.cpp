/*
    Compile unit: C:\rockband2\system\src\char\CharEyes.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80354110 -> 0x80357E4C
*/
class DataArray * types; // size: 0x4, address: 0x80A50EE8
static float kMaxEyeAng; // size: 0x4, address: 0x80A56CE0
static float kMaxLook; // size: 0x4, address: 0x80A56CE4
static float kMinLook; // size: 0x4, address: 0x80A56CE8
// Range: 0x80354110 -> 0x8035418C
void * EyeDesc::EyeDesc() {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>;
}

// Range: 0x8035418C -> 0x8035425C
void * EyeDesc::EyeDesc(struct EyeDesc * const this /* r30 */, const struct EyeDesc & d /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>;
}

// Range: 0x8035425C -> 0x80354360
struct EyeDesc & EyeDesc::__as(struct EyeDesc * const this /* r29 */, const struct EyeDesc & d /* r30 */) {}

// Range: 0x80354360 -> 0x80354550
void * CharEyes::CharEyes(class CharEyes * const this /* r31 */) {
    // References
    // -> static float kMaxEyeAng;
    // -> struct [anonymous] __vt__37ObjPtr<16CharWeightSetter,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13CharFaceServo,9ObjectDir>;
    // -> struct [anonymous] __vt__8CharEyes;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80354550 -> 0x80354878
void * CharEyes::~CharEyes(class CharEyes * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__40ObjOwnerPtr<14CharWeightable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13CharFaceServo,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16CharWeightSetter,9ObjectDir>;
}

// Range: 0x80354878 -> 0x80354974
void CharEyes::Enter(class CharEyes * const this /* r30 */) {
    // Local variables
    class RndTransformable * head; // r31
    struct EyeDesc * it; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80354974 -> 0x80354AFC
void CharEyes::Exit(class CharEyes * const this /* r31 */) {
    // Local variables
    struct EyeDesc * it; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Drawable * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Drawable * * _M_start; // offset 0x0, size 0x4
    class Drawable * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class RndGraph {
    // total size: 0x18
protected:
    unsigned char mEnable; // offset 0x0, size 0x1
    unsigned char mDrawFixedZ; // offset 0x1, size 0x1
    float mZ; // offset 0x4, size 0x4
    void * mId; // offset 0x8, size 0x4
    class vector mStuff; // offset 0xC, size 0xC
};
// Range: 0x80354AFC -> 0x80354D64
void CharEyes::Highlight(class CharEyes * const this /* r31 */) {
    // Local variables
    class RndGraph * g; // r29
    class RndTransformable * eye; // r30
    struct EyeDesc * it; // r28
    class Vector3 d; // r1+0x50
    struct Interest * it; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80354D64 -> 0x80355480
void CharEyes::Poll(class CharEyes * const this /* r31 */) {
    // Local variables
    class RndTransformable * h; // r29
    float camWeight; // f29
    float blinkWeight; // f0
    unsigned char blink; // r30
    class Vector3 delta; // r1+0x10
    float cang; // f0
    float sec; // f0
    float d; // f0
    class RndTransformable * dest; // r29
    float weight; // f0
    class RndCam * srcCam; // r30
    class Transform t; // r1+0x60
    class Transform t; // r1+0x20
    struct EyeDesc * it; // r29
    float height; // f29

    // References
    // -> class Rnd & TheRnd;
    // -> class RndCam * sCurrent;
    // -> class WorldDir * TheWorld;
    // -> static float kMinLook;
    // -> static float kMaxLook;
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80355480 -> 0x803554FC
class RndTransformable * CharEyes::GetDest() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803554FC -> 0x8035559C
class RndTransformable * CharEyes::GetHead() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8035559C -> 0x80355A74
void CharEyes::NextLook(class CharEyes * const this /* r31 */) {
    // Local variables
    class Vector3 facing; // r1+0x60
    class Vector3 delta; // r1+0x50
    float d; // f0
    float tanang; // f0
    class RndTransformable * d; // r29
    float h; // f1
    float scale; // f1
    class Vector3 delta; // r1+0x40
    struct Interest * it; // r28
    class Vector3 b; // r1+0x30
    float dist; // f0
    class Vector3 c; // r1+0x20
    float d2; // f0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static float kMaxEyeAng;
}

// Range: 0x80355A74 -> 0x80355DCC
void CharEyes::Replace(class CharEyes * const this /* r28 */, class Object * from /* r29 */, class Object * to /* r30 */) {
    // Local variables
    struct Interest * it; // r31
    struct EyeDesc * it; // r31

    // References
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__10CharLookAt;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80355DCC -> 0x80355E84
void CharEyes::ListPollChildren(const class CharEyes * const this /* r28 */, class list & l /* r29 */) {
    // Local variables
    const struct EyeDesc * it; // r30

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>; // size: 0x8, address: 0x808D5C18
// Range: 0x80355E84 -> 0x80356030
void CharEyes::PollDeps(class CharEyes * const this /* r29 */, class list & changedBy /* r30 */, class list & change /* r31 */) {
    // Local variables
    struct Interest * it; // r27

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80356030 -> 0x80356084
void __ls(class BinStream & d /* r30 */, const struct Interest & interest /* r31 */) {}

// Range: 0x80356084 -> 0x803560D8
class BinStream & __ls(class BinStream & d /* r30 */, const struct EyeDesc & desc /* r31 */) {}

// Range: 0x803560D8 -> 0x8035616C
void CharEyes::Save(class CharEyes * const this /* r30 */, class BinStream & d /* r31 */) {}

static int gRev; // size: 0x4, address: 0x80A50EF0
// Range: 0x8035616C -> 0x803561B8
void __rs(class BinStream & d /* r30 */, struct Interest & interest /* r31 */) {}

// Range: 0x803561B8 -> 0x80356218
class BinStream & __rs(class BinStream & d /* r30 */, struct EyeDesc & desc /* r31 */) {
    // References
    // -> static int gRev;
}

struct Node {
    // total size: 0xC
    class CharLookAt * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x80356218 -> 0x80356954
void CharEyes::Load(class CharEyes * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    class ObjPtrList eyes; // r1+0x4C
    int i; // r30
    class iterator it; // r1+0x3C
    class ObjPtr rightLid; // r1+0x40

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__35ObjPtrList<10CharLookAt,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80356954 -> 0x80356E24
void CharEyes::Copy(class CharEyes * const this /* r28 */, const class Object * o /* r26 */, enum CopyType type /* r25 */) {
    // Local variables
    const class CharEyes * e; // r0

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharEyes;
}

static class Symbol _s; // size: 0x4, address: 0x80A50EF8
// Range: 0x80356E24 -> 0x80357240
class DataNode CharEyes::Handle(class CharEyes * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
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

// Range: 0x80357240 -> 0x80357558
class DataNode CharEyes::OnAddInterest(class CharEyes * const this /* r30 */, class DataArray * msg /* r25 */) {
    // Local variables
    struct Interest interest; // r1+0x28

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
}

static class Symbol _s; // size: 0x4, address: 0x80A50F00
static class Symbol _s; // size: 0x4, address: 0x80A50F08
static class Symbol _s; // size: 0x4, address: 0x80A50F10
// Range: 0x80357558 -> 0x803576B8
unsigned char PropSync(struct EyeDesc & _me /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x803576B8 -> 0x803577F8
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10CharLookAt;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A50F18
static class Symbol _s; // size: 0x4, address: 0x80A50F20
// Range: 0x803577F8 -> 0x803579B0
unsigned char PropSync(struct Interest & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A50F28
static class Symbol _s; // size: 0x4, address: 0x80A50F30
static class Symbol _s; // size: 0x4, address: 0x80A50F38
static class Symbol _s; // size: 0x4, address: 0x80A50F40
// Range: 0x803579B0 -> 0x80357B70
unsigned char CharEyes::SyncProperty(class CharEyes * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80357B70 -> 0x80357E4C
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    struct Interest * it; // r31
    struct Interest tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x18
} __vt__35ObjPtrList<10CharLookAt,9ObjectDir>; // size: 0x18, address: 0x808D5D78
struct {
    // total size: 0x8
} __RTTI__35ObjPtrList<10CharLookAt,9ObjectDir>; // size: 0x8, address: 0x808D5DC0
struct {
    // total size: 0xF4
} __vt__8CharEyes; // size: 0xF4, address: 0x808D5DC8
struct {
    // total size: 0x8
} __RTTI__8CharEyes; // size: 0x8, address: 0x808D5F00
struct {
    // total size: 0x18
} __vt__34ObjPtr<13CharFaceServo,9ObjectDir>; // size: 0x18, address: 0x808D5F08
struct {
    // total size: 0x8
} __RTTI__34ObjPtr<13CharFaceServo,9ObjectDir>; // size: 0x8, address: 0x808D5F50
struct {
    // total size: 0x18
} __vt__36ObjOwnerPtr<10CharLookAt,9ObjectDir>; // size: 0x18, address: 0x808D5F58
struct {
    // total size: 0x8
} __RTTI__36ObjOwnerPtr<10CharLookAt,9ObjectDir>; // size: 0x8, address: 0x808D5FA0
struct {
    // total size: 0x8
} __RTTI__13CharFaceServo; // size: 0x8, address: 0x808D6000
struct {
    // total size: 0x8
} __RTTI__10CharLookAt; // size: 0x8, address: 0x808D6090
struct {
    // total size: 0x8
} __RTTI__16CharWeightSetter; // size: 0x8, address: 0x808D60D8
struct {
    // total size: 0x18
} __vt__37ObjPtr<16CharWeightSetter,9ObjectDir>; // size: 0x18, address: 0x808D60E0
struct {
    // total size: 0x8
} __RTTI__37ObjPtr<16CharWeightSetter,9ObjectDir>; // size: 0x8, address: 0x808D6128
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndPollable * _M_data; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ28CharEyes7EyeDesc; // size: 0x8, address: 0x808D6528
struct {
    // total size: 0x8
} __RTTI__PQ28CharEyes8Interest; // size: 0x8, address: 0x808D6548

