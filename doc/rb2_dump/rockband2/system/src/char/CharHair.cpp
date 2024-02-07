/*
    Compile unit: C:\rockband2\system\src\char\CharHair.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8035D848 -> 0x80363CA0
*/
struct {
    // total size: 0x8
} __RTTI__PQ28CharHair5Point; // size: 0x8, address: 0x808D6E88
class DataArray * types; // size: 0x4, address: 0x80A50FA0
// Range: 0x8035D848 -> 0x8035DA2C
void Strand::SetRoot(class Strand * const this /* r28 */) {
    // Local variables
    int i; // r31
    class RndTransformable * r; // r30
    class RndTransformable * r; // r30
    struct Point * last; // r30
    int i; // r31
    class RndTransformable * bone; // r29
    struct Point & p; // r29
}

// Range: 0x8035DA2C -> 0x8035DB64
void CharHair::SetCloth() {
    // Local variables
    int i; // r5
    class Strand & s; // r11
    class Strand & lastStrand; // r0
    int j; // r12
}

// Range: 0x8035DB64 -> 0x8035DDD8
void Strand::SetAngle(class Strand * const this /* r31 */) {
    // Local variables
    class Matrix3 m; // r1+0x40
}

class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gHairs; // size: 0xC, address: 0x8097DFE4
// Range: 0x8035DDD8 -> 0x8035DF88
void * CharHair::CharHair(class CharHair * const this /* r1+0x8 */) {
    // References
    // -> static class vector gHairs;
    // -> struct [anonymous] __vt__8CharHair;
    // -> struct [anonymous] __vt__12CharPollable;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8035DF88 -> 0x8035E3A0
void * CharHair::~CharHair(class CharHair * const this /* r1+0x8 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11CharCollide,9ObjectDir>;
    // -> static class vector gHairs;
    // -> struct [anonymous] __vt__8CharHair;
}

// Range: 0x8035E3A0 -> 0x8035E3B0
void CharHair::Enter() {}

// Range: 0x8035E3B0 -> 0x8035E618
void CharHair::DoReset(class CharHair * const this /* r27 */, int loops /* r28 */) {
    // Local variables
    unsigned char oldSimulate; // r31
    int i; // r30
    class ObjVector & ps; // r0
    class Transform t; // r1+0x10
    int j; // r29
    float oldInertia; // f31
    float oldFriction; // f30
    int i; // r25
}

// Range: 0x8035E618 -> 0x8035E724
static unsigned char StrandVisible(class Strand & s /* r29 */) {
    // Local variables
    class Vector3 delta; // r1+0x10

    // References
    // -> class RndCam * sCurrent;
}

// Range: 0x8035E724 -> 0x8035F3A4
void CharHair::Highlight(class CharHair * const this /* r26 */) {
    // Local variables
    int i; // r28
    class Strand & s; // r0
    class Strand & lastStrand; // r0
    class ObjVector & ps; // r0
    class Transform t; // r1+0x240
    int j; // r25
    class Vector3 lastPos; // r1+0x1F0
    class Transform t; // r1+0x200
    class Vector3 b; // r1+0x1E0
    class Vector3 lastPos; // r1+0x1D0
    int j; // r27
    class Vector3 delta; // r1+0x1C0
    float l; // f0
    float minLength; // f30
    float maxLength; // f29
    class Vector3 end; // r1+0x1B0
    class Vector3 start; // r1+0x1A0
    class Vector3 tmp; // r1+0x190
    class iterator it; // r1+0x20
    class Color col; // r1+0x180

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x8035F3A4 -> 0x8035F448
void CharHair::SetName(class CharHair * const this /* r28 */, class ObjectDir * d /* r29 */) {
    // References
    // -> struct [anonymous] __RTTI__8WorldDir;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9Character;
}

// Range: 0x8035F448 -> 0x8035F510
void CharHair::Poll(class CharHair * const this /* r30 */) {
    // Local variables
    float kFPS; // f1

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8035F510 -> 0x8035FC8C
void CharHair::Simulate(class CharHair * const this /* r25 */) {
    // Local variables
    float kTimeDelta; // f2
    float kTimeCorrection; // f3
    float kGrav; // f31
    float kWeight; // f30
    int i; // r30
    class Strand & lastStrand; // r29
    class Strand & s; // r28
    class Transform t; // r1+0xB0
    class ObjVector & ps; // r28
    int j; // r31
    struct Point & p; // r27
    class Vector3 lastPos; // r1+0x70
    class Vector3 delta; // r1+0x60
    struct Point & lastP; // r26
    float l2; // f0
    float min2; // f3
    float v2; // f1
    float max2; // f2
    float v2; // f1
    class Matrix3 m; // r1+0x80
    float l; // f0
    float rat; // f28
    class Vector3 ideal; // r1+0x50
    class iterator it; // r1+0x18
    class CharCollide * coll; // r26
    class Vector3 delta; // r1+0x40
    float dot; // f0
    float radius; // f29
    float outerRadius; // f27
    float l2; // f0
    float l; // f0
    float frac; // f1
    float l; // f0
    float dot; // f0
    float radius; // f27
    float innerRadius; // f28
    float l2; // f0
    float l; // f0
    float frac; // f1
    class Vector3 friction; // r1+0x30
    class Vector3 delta; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
}

// Range: 0x8035FC8C -> 0x80360144
void CharHair::SimulateZeroTime(class CharHair * const this /* r30 */) {
    // Local variables
    int i; // r31
    class Transform t; // r1+0x70
    class ObjVector & ps; // r0
    int j; // r27
    class Matrix3 m; // r1+0x40
}

// Range: 0x80360144 -> 0x80360284
void CharHair::PollDeps(class CharHair * const this /* r28 */, class list & changedBy /* r29 */, class list & change /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CharCollide * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80360284 -> 0x80360BE0
void CharHair::Hookup(class CharHair * const this /* r24 */) {
    // Local variables
    class vector collides; // r1+0x60
    class ObjDirItr c; // r1+0x6C
    int i; // r28
    int j; // r27
    int k; // r27
    class CharCollide * c; // r26
    class Vector3 delta; // r1+0x50
    float rootDist; // f31
    class Vector3 d; // r1+0x40
    float length; // f30
    int j; // r25
    float maxRadius; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharCollide;
}

struct SortCollides {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class CharCollide * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class CharCollide * * _M_start; // offset 0x0, size 0x4
    class CharCollide * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
static int gRev; // size: 0x4, address: 0x80A50FA8
// Range: 0x80360BE0 -> 0x80360CC4
void __ls(class BinStream & d /* r30 */, const struct Point & p /* r31 */) {}

// Range: 0x80360CC4 -> 0x80361030
void __rs(class BinStream & d /* r29 */, struct Point & p /* r30 */) {
    // Local variables
    int tmp; // r1+0x18
    char buff[256]; // r1+0x120
    int count; // r1+0x14
    float offset; // r1+0x10
    char buff[256]; // r1+0x20
    float tmp; // r1+0xC
    unsigned char side; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gRev;
}

// Range: 0x80361030 -> 0x8036125C
void Strand::Save(const class Strand * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8036125C -> 0x80361400
void Strand::Load(class Strand * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> static int gRev;
}

// Range: 0x80361400 -> 0x80361410
void __ls(class BinStream & d /* r0 */) {}

// Range: 0x80361410 -> 0x80361420
void __rs(class BinStream & d /* r0 */) {}

// Range: 0x80361420 -> 0x8036155C
void CharHair::Save(class CharHair * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8036155C -> 0x803616E8
void CharHair::Load(class CharHair * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803616E8 -> 0x8036181C
void CharHair::Copy(class CharHair * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class CharHair * h; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharHair;
}

static class CharHair * gHair; // size: 0x4, address: 0x80A50FAC
static class Strand * gStrand; // size: 0x4, address: 0x80A50FB0
static class Symbol _s; // size: 0x4, address: 0x80A50FB8
static class Symbol _s; // size: 0x4, address: 0x80A50FC0
static class Symbol _s; // size: 0x4, address: 0x80A50FC8
static class Symbol _s; // size: 0x4, address: 0x80A50FD0
// Range: 0x8036181C -> 0x80362028
class DataNode CharHair::Handle(class CharHair * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80362028 -> 0x80362168
class DataNode CharHair::OnValidate(class CharHair * const this /* r30 */) {
    // Local variables
    int i; // r31
    class ObjVector & ps; // r0
    int j; // r27

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A50FD8
static class Symbol _s; // size: 0x4, address: 0x80A50FE0
static class Symbol _s; // size: 0x4, address: 0x80A50FE8
static class Symbol _s; // size: 0x4, address: 0x80A50FF0
static class Symbol _s; // size: 0x4, address: 0x80A50FF8
static class Symbol _s; // size: 0x4, address: 0x80A51000
// Range: 0x80362168 -> 0x8036263C
unsigned char PropSync(struct Point & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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

// Range: 0x8036263C -> 0x80362CF4
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class CharCollide * obj; // r31
    class CharCollide * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharCollide;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A51008
static class Symbol _s; // size: 0x4, address: 0x80A51010
static class Symbol _s; // size: 0x4, address: 0x80A51018
static class Symbol _s; // size: 0x4, address: 0x80A51020
static class Symbol _s; // size: 0x4, address: 0x80A51028
static class Symbol _s; // size: 0x4, address: 0x80A51030
static class Symbol _s; // size: 0x4, address: 0x80A51038
// Range: 0x80362CF4 -> 0x80363328
unsigned char PropSync(class Strand & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
    // -> static class Strand * gStrand;
}

static class Symbol _s; // size: 0x4, address: 0x80A51040
static class Symbol _s; // size: 0x4, address: 0x80A51048
static class Symbol _s; // size: 0x4, address: 0x80A51050
static class Symbol _s; // size: 0x4, address: 0x80A51058
static class Symbol _s; // size: 0x4, address: 0x80A51060
static class Symbol _s; // size: 0x4, address: 0x80A51068
static class Symbol _s; // size: 0x4, address: 0x80A51070
static class Symbol _s; // size: 0x4, address: 0x80A51078
static class Symbol _s; // size: 0x4, address: 0x80A51080
static class Symbol _s; // size: 0x4, address: 0x80A51088
// Range: 0x80363328 -> 0x80363C74
unsigned char CharHair::SyncProperty(class CharHair * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
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
    // -> static class CharHair * gHair;
}

struct {
    // total size: 0xBC
} __vt__8CharHair; // size: 0xBC, address: 0x808D7348
struct {
    // total size: 0x18
} __vt__36ObjPtrList<11CharCollide,9ObjectDir>; // size: 0x18, address: 0x808D7448
struct {
    // total size: 0x8
} __RTTI__36ObjPtrList<11CharCollide,9ObjectDir>; // size: 0x8, address: 0x808D7490
struct {
    // total size: 0x8
} __RTTI__PP11CharCollide; // size: 0x8, address: 0x808D7758
struct {
    // total size: 0x8
} __RTTI__PP8CharHair; // size: 0x8, address: 0x808D7770
struct {
    // total size: 0x8
} __RTTI__PQ28CharHair6Strand; // size: 0x8, address: 0x808D7790
// Range: 0x80363C74 -> 0x80363CA0
static void __sinit_\CharHair_cpp() {
    // References
    // -> static class vector gHairs;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class CharHair * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class CharHair * * _M_start; // offset 0x0, size 0x4
    class CharHair * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

