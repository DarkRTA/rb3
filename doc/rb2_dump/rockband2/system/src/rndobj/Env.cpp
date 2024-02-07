/*
    Compile unit: C:\rockband2\system\src\rndobj\Env.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80489480 -> 0x8048D084
*/
class DataArray * types; // size: 0x4, address: 0x80A52BF0
class RndEnviron * sCurrent; // size: 0x4, address: 0x80A52BF8
const class Vector3 * sCurrentPos; // size: 0x4, address: 0x80A52BFC
// Range: 0x80489480 -> 0x8048948C
void RndEnviron::Select() {
    // References
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
}

// Range: 0x8048948C -> 0x804895AC
void * RndEnviron::RndEnviron(class RndEnviron * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtrList<8RndLight,9ObjectDir>;
    // -> struct [anonymous] __vt__10RndEnviron;
}

// Range: 0x804895AC -> 0x804897E0
void * RndEnviron::~RndEnviron(class RndEnviron * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__32ObjPtrList<8RndLight,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
}

// Range: 0x804897E0 -> 0x8048983C
class RndLight * RndEnviron::FirstPointLight() {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x8048983C -> 0x804898A0
int RndEnviron::NumProjLights() {
    // Local variables
    int count; // r4
    class iterator it; // r1+0x18
}

static int ENVIRON_REV; // size: 0x4, address: 0x80A47198
// Range: 0x804898A0 -> 0x804898E4
void RndEnviron::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804898E4 -> 0x80489C28
void RndEnviron::Load(class RndEnviron * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static int ENVIRON_REV;
}

// Range: 0x80489C28 -> 0x8048A374
void RndEnviron::Copy(class RndEnviron * const this /* r28 */, const class Object * o /* r26 */, enum CopyType type /* r29 */) {
    // Local variables
    const class RndEnviron * e; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
}

// Range: 0x8048A374 -> 0x8048A448
void RndEnviron::Replace(class RndEnviron * const this /* r30 */) {
    // Local variables
    class RndEnviron * toEnv; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
}

// Range: 0x8048A448 -> 0x8048A630
void RndEnviron::AddLight(class RndEnviron * const this /* r31 */, class RndLight * l /* r29 */) {
    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x8048A630 -> 0x8048A798
void RndEnviron::RemoveLight(class RndEnviron * const this /* r28 */, class RndLight * l /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A52C04
static class Symbol _s; // size: 0x4, address: 0x80A52C0C
static class Symbol _s; // size: 0x4, address: 0x80A52C14
static class Symbol _s; // size: 0x4, address: 0x80A52C1C
static class Symbol _s; // size: 0x4, address: 0x80A52C24
static class Symbol _s; // size: 0x4, address: 0x80A52C2C
static class Symbol _s; // size: 0x4, address: 0x80A52C34
// Range: 0x8048A798 -> 0x8048B26C
class DataNode RndEnviron::Handle(class RndEnviron * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class DataNode & milo_prop_path; // size: 0x4, address: 0x80A52C3C
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndLight * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8048B26C -> 0x8048B7D0
class DataNode RndEnviron::OnAllowableLights(class RndEnviron * const this /* r31 */) {
    // Local variables
    class DataArrayPtr allow; // r1+0x50
    class ObjDirItr i; // r1+0x58

    // References
    // -> static class DataNode & milo_prop_path;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

static class Symbol _s; // size: 0x4, address: 0x80A52C44
static class Symbol _s; // size: 0x4, address: 0x80A52C4C
static class Symbol _s; // size: 0x4, address: 0x80A52C54
static class Symbol _s; // size: 0x4, address: 0x80A52C5C
static class Symbol _s; // size: 0x4, address: 0x80A52C64
static class Symbol _s; // size: 0x4, address: 0x80A52C6C
static class Symbol _s; // size: 0x4, address: 0x80A52C74
static class Symbol _s; // size: 0x4, address: 0x80A52C7C
static class Symbol _s; // size: 0x4, address: 0x80A52C84
static class Symbol _s; // size: 0x4, address: 0x80A52C8C
static class Symbol _s; // size: 0x4, address: 0x80A52C94
static class Symbol _s; // size: 0x4, address: 0x80A52C9C
static class Symbol _s; // size: 0x4, address: 0x80A52CA4
static class Symbol _s; // size: 0x4, address: 0x80A52CAC
static class Symbol _s; // size: 0x4, address: 0x80A52CB4
static class Symbol _s; // size: 0x4, address: 0x80A52CBC
static class Symbol _s; // size: 0x4, address: 0x80A52CC4
static class Symbol _s; // size: 0x4, address: 0x80A52CCC
static class Symbol _s; // size: 0x4, address: 0x80A52CD4
static class Symbol _s; // size: 0x4, address: 0x80A52CDC
static class Symbol _s; // size: 0x4, address: 0x80A52CE4
static class Symbol _s; // size: 0x4, address: 0x80A52CEC
static class Symbol _s; // size: 0x4, address: 0x80A52CF4
static class Symbol _s; // size: 0x4, address: 0x80A52CFC
static class Symbol _s; // size: 0x4, address: 0x80A52D04
static class Symbol _s; // size: 0x4, address: 0x80A52D0C
static class Symbol _s; // size: 0x4, address: 0x80A52D14
static class Symbol _s; // size: 0x4, address: 0x80A52D1C
// Range: 0x8048B7D0 -> 0x8048CF50
unsigned char RndEnviron::SyncProperty(class RndEnviron * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8048CF50 -> 0x8048D084
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x64
} __vt__10RndEnviron; // size: 0x64, address: 0x808F58C4
struct {
    // total size: 0x18
} __vt__36ObjOwnerPtr<10RndEnviron,9ObjectDir>; // size: 0x18, address: 0x808F5950
struct {
    // total size: 0x8
} __RTTI__36ObjOwnerPtr<10RndEnviron,9ObjectDir>; // size: 0x8, address: 0x808F5998

