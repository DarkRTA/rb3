/*
    Compile unit: C:\rockband2\system\src\rndobj\CamAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804761E8 -> 0x80477440
*/
class DataArray * types; // size: 0x4, address: 0x80A52A58
class Symbol name; // size: 0x4, address: 0x80A52A60
class RndCamAnim : public RndAnimatable {
    // total size: 0x60
protected:
    class ObjPtr mCam; // offset 0x10, size 0xC
    class Keys mFovKeys; // offset 0x1C, size 0xC
    class ObjOwnerPtr mKeysOwner; // offset 0x28, size 0xC
};
// Range: 0x804761E8 -> 0x80476394
void RndCamAnim::Copy(class RndCamAnim * const this /* r28 */, const class Object * o /* r30 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndCamAnim * l; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndCamAnim;
}

static int CAMANIM_REV; // size: 0x4, address: 0x80A47124
// Range: 0x80476394 -> 0x804763D8
void RndCamAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A52A64
// Range: 0x804763D8 -> 0x80476548
void RndCamAnim::Load(class RndCamAnim * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class Key * i; // r31

    // References
    // -> class Debug TheDebug;
    // -> static int CAMANIM_REV;
    // -> static int gRev;
}

// Range: 0x80476548 -> 0x80476630
void RndCamAnim::Replace(class RndCamAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndCamAnim;
}

// Range: 0x80476630 -> 0x80476984
void RndCamAnim::SetFrame(class RndCamAnim * const this /* r23 */, float frame /* f31 */, float blend /* f29 */) {
    // Local variables
    float fov; // f30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80476984 -> 0x80476A0C
float RndCamAnim::EndFrame(class RndCamAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80476A0C -> 0x80476D84
void RndCamAnim::SetKey(class RndCamAnim * const this /* r26 */, float frame /* f30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80476D84 -> 0x80476EE4
void * RndCamAnim::~RndCamAnim(class RndCamAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10RndCamAnim,9ObjectDir>;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndCamAnim * mPtr; // offset 0x8, size 0x4
};
// Range: 0x80476EE4 -> 0x80476FD4
void * RndCamAnim::RndCamAnim(class RndCamAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10RndCamAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__10RndCamAnim;
}

// Range: 0x80476FD4 -> 0x804773C0
class DataNode RndCamAnim::Handle(class RndCamAnim * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

// Range: 0x804773C0 -> 0x80477440
unsigned char RndCamAnim::SyncProperty(class RndCamAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__10RndCamAnim; // size: 0xA8, address: 0x808F28C0
struct {
    // total size: 0x8
} __RTTI__10RndCamAnim; // size: 0x8, address: 0x808F2990
struct {
    // total size: 0x18
} __vt__36ObjOwnerPtr<10RndCamAnim,9ObjectDir>; // size: 0x18, address: 0x808F2998
struct {
    // total size: 0x8
} __RTTI__36ObjOwnerPtr<10RndCamAnim,9ObjectDir>; // size: 0x8, address: 0x808F29E0

