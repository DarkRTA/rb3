/*
    Compile unit: C:\rockband2\system\src\rndobj\Lit.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804A8E2C -> 0x804AAC1C
*/
class DataArray * types; // size: 0x4, address: 0x80A53010
class Symbol name; // size: 0x4, address: 0x80A53018
// Range: 0x804A8E2C -> 0x804A8FC0
void * RndLight::RndLight(class RndLight * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8RndLight,9ObjectDir>;
    // -> struct [anonymous] __vt__8RndLight;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

static int LIGHT_REV; // size: 0x4, address: 0x80A47228
// Range: 0x804A8FC0 -> 0x804A9004
void RndLight::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804A9004 -> 0x804A95E4
void RndLight::Load(class RndLight * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x2C
    class Color ambient; // r1+0x50
    class Color specular; // r1+0x40
    float innerAng; // r1+0x28
    float outerAng; // r1+0x24
    float constAtten; // r1+0x20
    float linearAtten; // r1+0x1C
    float quadAtten; // r1+0x18
    unsigned char animate; // r0
    class ObjPtrList casters; // r1+0x60
    class ObjPtr caster; // r1+0x30

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int LIGHT_REV;
}

// Range: 0x804A95E4 -> 0x804A9828
void RndLight::Copy(class RndLight * const this /* r31 */, const class Object * o /* r29 */, enum CopyType type /* r28 */) {
    // Local variables
    const class RndLight * l; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndLight;
}

// Range: 0x804A9828 -> 0x804A9938
void RndLight::Replace(class RndLight * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {
    // Local variables
    class RndLight * toLight; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndLight;
}

// Range: 0x804A9938 -> 0x804A9A0C
void RndLight::SetPackedColor() {
    // Local variables
    class Color c; // r1+0x10
}

// Range: 0x804A9A0C -> 0x804A9B1C
int RndLight::PackedColor(const class RndLight * const this /* r31 */) {
    // Local variables
    class Color c; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A9B1C -> 0x804A9C00
float RndLight::Intensity(const class RndLight * const this /* r31 */) {
    // Local variables
    class Color col; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A9C00 -> 0x804A9C08
void RndLight::SetConeSoftness() {}

// Range: 0x804A9C08 -> 0x804A9C10
void RndLight::SetTopRadius() {}

// Range: 0x804A9C10 -> 0x804A9C18
void RndLight::SetBotRadius() {}

// Range: 0x804A9C18 -> 0x804A9C20
void RndLight::SetShadowCasters() {}

// Range: 0x804A9C20 -> 0x804A9C54
void RndLight::CalcCosines() {}

static class Symbol _s; // size: 0x4, address: 0x80A53020
// Range: 0x804A9C54 -> 0x804AA148
class DataNode RndLight::Handle(class RndLight * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A53028
static class Symbol _s; // size: 0x4, address: 0x80A53030
static class Symbol _s; // size: 0x4, address: 0x80A53038
static class Symbol _s; // size: 0x4, address: 0x80A53040
static class Symbol _s; // size: 0x4, address: 0x80A53048
static class Symbol _s; // size: 0x4, address: 0x80A53050
static class Symbol _s; // size: 0x4, address: 0x80A53058
static class Symbol _s; // size: 0x4, address: 0x80A53060
static class Symbol _s; // size: 0x4, address: 0x80A53068
static class Symbol _s; // size: 0x4, address: 0x80A53070
static class Symbol _s; // size: 0x4, address: 0x80A53078
static class Symbol _s; // size: 0x4, address: 0x80A53080
static class Symbol _s; // size: 0x4, address: 0x80A53088
// Range: 0x804AA148 -> 0x804AAAD0
unsigned char RndLight::SyncProperty(class RndLight * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x804AAAD0 -> 0x804AAC1C
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xAC
} __vt__8RndLight; // size: 0xAC, address: 0x808F8C90
struct {
    // total size: 0x18
} __vt__33ObjOwnerPtr<8RndLight,9ObjectDir>; // size: 0x18, address: 0x808F8DC0
struct {
    // total size: 0x8
} __RTTI__33ObjOwnerPtr<8RndLight,9ObjectDir>; // size: 0x8, address: 0x808F8E08

