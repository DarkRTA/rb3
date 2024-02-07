/*
    Compile unit: C:\rockband2\system\src\rndobj\PartAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804E0098 -> 0x804E1A38
*/
class DataArray * types; // size: 0x4, address: 0x80A535B0
class Symbol name; // size: 0x4, address: 0x80A535B8
class RndParticleSysAnim : public RndAnimatable {
    // total size: 0x9C
protected:
    class ObjPtr mParticleSys; // offset 0x10, size 0xC
    class Keys mStartColorKeys; // offset 0x1C, size 0xC
    class Keys mEndColorKeys; // offset 0x28, size 0xC
    class Keys mEmitRateKeys; // offset 0x34, size 0xC
    class Keys mSpeedKeys; // offset 0x40, size 0xC
    class Keys mLifeKeys; // offset 0x4C, size 0xC
    class Keys mStartSizeKeys; // offset 0x58, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x64, size 0xC
};
// Range: 0x804E0098 -> 0x804E01C4
void * RndParticleSysAnim::RndParticleSysAnim(class RndParticleSysAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__44ObjOwnerPtr<18RndParticleSysAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__35ObjPtr<14RndParticleSys,9ObjectDir>;
    // -> struct [anonymous] __vt__18RndParticleSysAnim;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndParticleSysAnim * mPtr; // offset 0x8, size 0x4
};
// Range: 0x804E01C4 -> 0x804E0230
void RndParticleSysAnim::SetParticleSys(class RndParticleSysAnim * const this /* r30 */, class RndParticleSys * o /* r31 */) {}

// Range: 0x804E0230 -> 0x804E0318
void RndParticleSysAnim::Replace(class RndParticleSysAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18RndParticleSysAnim;
}

static int PARTANIM_REV; // size: 0x4, address: 0x80A47360
// Range: 0x804E0318 -> 0x804E035C
void RndParticleSysAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804E035C -> 0x804E06EC
void RndParticleSysAnim::Load(class RndParticleSysAnim * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x3C
    class Keys emitRateKeys; // r1+0x54
    float emitRateRatio; // r1+0x38
    class Key * i; // r29
    class Key k; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static int PARTANIM_REV;
}

// Range: 0x804E06EC -> 0x804E0A28
void RndParticleSysAnim::Copy(class RndParticleSysAnim * const this /* r31 */, const class Object * o /* r29 */, enum CopyType type /* r28 */) {
    // Local variables
    const class RndParticleSysAnim * l; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18RndParticleSysAnim;
}

// Range: 0x804E0A28 -> 0x804E0BA8
void RndParticleSysAnim::Print(class RndParticleSysAnim * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804E0BA8 -> 0x804E0F14
float RndParticleSysAnim::EndFrame(class RndParticleSysAnim * const this /* r31 */) {
    // Local variables
    float frame; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804E0F14 -> 0x804E1350
void RndParticleSysAnim::SetFrame(class RndParticleSysAnim * const this /* r31 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    class Color low; // r1+0x60
    class Color high; // r1+0x50
    class Color low; // r1+0x40
    class Color high; // r1+0x30
    class Vector2 v; // r1+0x28
    class Vector2 v; // r1+0x20
    class Vector2 v; // r1+0x18
    class Vector2 v; // r1+0x10
}

// Range: 0x804E1350 -> 0x804E148C
void RndParticleSysAnim::SetKey(class RndParticleSysAnim * const this /* r30 */, float frame /* f31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A535C0
// Range: 0x804E148C -> 0x804E198C
class DataNode RndParticleSysAnim::Handle(class RndParticleSysAnim * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndParticleSys;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804E198C -> 0x804E1A0C
unsigned char RndParticleSysAnim::SyncProperty(class RndParticleSysAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__18RndParticleSysAnim; // size: 0xA8, address: 0x808FD7E0
struct {
    // total size: 0x8
} __RTTI__18RndParticleSysAnim; // size: 0x8, address: 0x808FD8B8
struct {
    // total size: 0x18
} __vt__44ObjOwnerPtr<18RndParticleSysAnim,9ObjectDir>; // size: 0x18, address: 0x808FD8C0
struct {
    // total size: 0x8
} __RTTI__44ObjOwnerPtr<18RndParticleSysAnim,9ObjectDir>; // size: 0x8, address: 0x808FD910
// Range: 0x804E1A0C -> 0x804E1A38
void _Vector_base::_M_throw_length_error() {}


