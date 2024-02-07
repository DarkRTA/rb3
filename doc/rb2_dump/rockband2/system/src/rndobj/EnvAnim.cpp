/*
    Compile unit: C:\rockband2\system\src\rndobj\EnvAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8048D638 -> 0x8048FE9C
*/
class DataArray * types; // size: 0x4, address: 0x80A52D20
class Symbol name; // size: 0x4, address: 0x80A52D28
class Keys : public vector {
    // total size: 0xC
};
class RndEnvAnim : public RndAnimatable {
    // total size: 0x78
protected:
    class ObjPtr mEnviron; // offset 0x10, size 0xC
    class Keys mFogColorKeys; // offset 0x1C, size 0xC
    class Keys mFogRangeKeys; // offset 0x28, size 0xC
    class Keys mAmbientColorKeys; // offset 0x34, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x40, size 0xC
};
// Range: 0x8048D638 -> 0x8048D740
void * RndEnvAnim::RndEnvAnim(class RndEnvAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10RndEnvAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__10RndEnvAnim;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Key * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Key * _M_start; // offset 0x0, size 0x4
    class Key * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndEnvAnim * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8048D740 -> 0x8048D828
void RndEnvAnim::Replace(class RndEnvAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnvAnim;
}

static int ENVANIM_REV; // size: 0x4, address: 0x80A471A0
// Range: 0x8048D828 -> 0x8048D86C
void RndEnvAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8048D86C -> 0x8048D9D8
void RndEnvAnim::Load(class RndEnvAnim * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int ENVANIM_REV;
}

// Range: 0x8048D9D8 -> 0x8048DC24
void RndEnvAnim::Copy(class RndEnvAnim * const this /* r28 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndEnvAnim * l; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnvAnim;
}

// Range: 0x8048DC24 -> 0x8048DD44
void RndEnvAnim::Print(class RndEnvAnim * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8048DD44 -> 0x8048DE18
class TextStream & __ls(class TextStream & d /* r30 */, const class vector & c /* r31 */) {
    // Local variables
    const class Key * t; // r29
}

// Range: 0x8048DE18 -> 0x8048DE80
class TextStream & __ls(class TextStream & d /* r30 */, const class Key & i /* r31 */) {}

// Range: 0x8048DE80 -> 0x8048DF9C
float RndEnvAnim::EndFrame(class RndEnvAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8048DF9C -> 0x8048EDFC
void RndEnvAnim::SetFrame(class RndEnvAnim * const this /* r31 */, float frame /* f29 */, float blend /* f28 */) {
    // Local variables
    class Color d; // r1+0x30
    class Color d; // r1+0x20
    class Vector2 v; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8048EDFC -> 0x8048FA04
void RndEnvAnim::SetKey(class RndEnvAnim * const this /* r24 */, float frame /* f31 */) {
    // Local variables
    class Vector2 v; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8048FA04 -> 0x8048FDF0
class DataNode RndEnvAnim::Handle(class RndEnvAnim * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

// Range: 0x8048FDF0 -> 0x8048FE70
unsigned char RndEnvAnim::SyncProperty(class RndEnvAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__10RndEnvAnim; // size: 0xA8, address: 0x808F5E20
struct {
    // total size: 0x8
} __RTTI__10RndEnvAnim; // size: 0x8, address: 0x808F5EF0
struct {
    // total size: 0x18
} __vt__36ObjOwnerPtr<10RndEnvAnim,9ObjectDir>; // size: 0x18, address: 0x808F5EF8
struct {
    // total size: 0x8
} __RTTI__36ObjOwnerPtr<10RndEnvAnim,9ObjectDir>; // size: 0x8, address: 0x808F5F40
// Range: 0x8048FE70 -> 0x8048FE9C
void _Vector_base::_M_throw_out_of_range() {}

struct {
    // total size: 0x8
} __RTTI__P13Key<7Vector2>; // size: 0x8, address: 0x808F6070
class Key {
    // total size: 0xC
public:
    class Vector2 value; // offset 0x0, size 0x8
    float frame; // offset 0x8, size 0x4
};

