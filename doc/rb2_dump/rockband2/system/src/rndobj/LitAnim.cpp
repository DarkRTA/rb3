/*
    Compile unit: C:\rockband2\system\src\rndobj\LitAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804AB274 -> 0x804AC93C
*/
class DataArray * types; // size: 0x4, address: 0x80A53090
class Symbol name; // size: 0x4, address: 0x80A53098
class RndLightAnim : public RndAnimatable {
    // total size: 0x60
protected:
    class ObjPtr mLight; // offset 0x10, size 0xC
    class Keys mColorKeys; // offset 0x1C, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x28, size 0xC
};
// Range: 0x804AB274 -> 0x804AB364
void * RndLightAnim::RndLightAnim(class RndLightAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__38ObjOwnerPtr<12RndLightAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndLight,9ObjectDir>;
    // -> struct [anonymous] __vt__12RndLightAnim;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndLight * mPtr; // offset 0x8, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndLightAnim * mPtr; // offset 0x8, size 0x4
};
// Range: 0x804AB364 -> 0x804AB44C
void RndLightAnim::Replace(class RndLightAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndLightAnim;
}

static int LIGHTANIM_REV; // size: 0x4, address: 0x80A4723C
// Range: 0x804AB44C -> 0x804AB490
void RndLightAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804AB490 -> 0x804AB6E4
void RndLightAnim::Load(class RndLightAnim * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x34
    class Keys ambientKeys; // r1+0x44
    class Keys specularKeys; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static int LIGHTANIM_REV;
}

// Range: 0x804AB6E4 -> 0x804AB8C0
void RndLightAnim::Copy(class RndLightAnim * const this /* r28 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndLightAnim * l; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndLightAnim;
}

// Range: 0x804AB8C0 -> 0x804AB9B8
void RndLightAnim::Print(class RndLightAnim * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804AB9B8 -> 0x804ABA40
float RndLightAnim::EndFrame(class RndLightAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804ABA40 -> 0x804ABE58
void RndLightAnim::SetFrame(class RndLightAnim * const this /* r23 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    class Color d; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804ABE58 -> 0x804AC244
void RndLightAnim::SetKey(class RndLightAnim * const this /* r27 */, float frame /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A530A0
// Range: 0x804AC244 -> 0x804AC788
class DataNode RndLightAnim::Handle(class RndLightAnim * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804AC788 -> 0x804AC8BC
class DataNode RndLightAnim::OnCopyKeys(class RndLightAnim * const this /* r29 */, class DataArray * d /* r30 */) {
    // Local variables
    float r; // f0
    class Key * i; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndLightAnim;
}

// Range: 0x804AC8BC -> 0x804AC93C
unsigned char RndLightAnim::SyncProperty(class RndLightAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__12RndLightAnim; // size: 0xA8, address: 0x808F9240
struct {
    // total size: 0x8
} __RTTI__12RndLightAnim; // size: 0x8, address: 0x808F9318
struct {
    // total size: 0x18
} __vt__38ObjOwnerPtr<12RndLightAnim,9ObjectDir>; // size: 0x18, address: 0x808F9320
struct {
    // total size: 0x8
} __RTTI__38ObjOwnerPtr<12RndLightAnim,9ObjectDir>; // size: 0x8, address: 0x808F9370
struct {
    // total size: 0x18
} __vt__28ObjPtr<8RndLight,9ObjectDir>; // size: 0x18, address: 0x808F9378
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8RndLight,9ObjectDir>; // size: 0x8, address: 0x808F93B8

