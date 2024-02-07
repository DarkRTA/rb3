/*
    Compile unit: C:\rockband2\system\src\world\SpotlightDrawer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8045C868 -> 0x8045F23C
*/
class DataArray * types; // size: 0x4, address: 0x80A527D0
class Symbol name; // size: 0x4, address: 0x80A527D8
class RndEnviron * sEnviron; // size: 0x4, address: 0x80A527DC
class SpotlightDrawer * sCurrent; // size: 0x4, address: 0x80A527E0
class SpotlightDrawer * sDefault; // size: 0x4, address: 0x80A527E4
class vector sLights; // size: 0xC, address: 0x8097F0AC
class vector sCans; // size: 0xC, address: 0x8097F0C4
class vector sShadowSpots; // size: 0xC, address: 0x8097F0DC
class RndMultiMesh * sMultiMesh; // size: 0x4, address: 0x80A527E8
unsigned char sNeedDraw; // size: 0x1, address: 0x80A527EC
unsigned char sHaveAdditionals; // size: 0x1, address: 0x80A527ED
unsigned char sHaveLenses; // size: 0x1, address: 0x80A527EE
unsigned char sHaveFlares; // size: 0x1, address: 0x80A527EF
unsigned char sHaveFloorSpots; // size: 0x1, address: 0x80A527F0
unsigned char sNoBeams; // size: 0x1, address: 0x80A527F1
// Range: 0x8045C868 -> 0x8045C958
void * SpotlightDrawer::SpotlightDrawer(class SpotlightDrawer * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15SpotlightDrawer;
    // -> struct [anonymous] __vt__13PostProcessor;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8045C958 -> 0x8045CD0C
void * SpotlightDrawer::~SpotlightDrawer(class SpotlightDrawer * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
    // -> class Symbol name;
    // -> class RndMultiMesh * sMultiMesh;
    // -> class vector sCans;
    // -> class vector sShadowSpots;
    // -> class vector sLights;
    // -> struct [anonymous] __vt__15SpotlightDrawer;
}

// Range: 0x8045CD0C -> 0x8045CD80
void SpotlightDrawer::ListDrawChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8045CD80 -> 0x8045CE44
void SpotlightDrawer::SetAmbientColor() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndEnviron * sEnviron;
}

// Range: 0x8045CE44 -> 0x8045CEAC
void SpotlightDrawer::Select(class SpotlightDrawer * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
    // -> class SpotlightDrawer * sCurrent;
}

// Range: 0x8045CEAC -> 0x8045CED0
void SpotlightDrawer::DeSelect() {
    // References
    // -> class SpotlightDrawer * sDefault;
    // -> class SpotlightDrawer * sCurrent;
}

// Range: 0x8045CED0 -> 0x8045D0D0
void SpotlightDrawer::Init() {
    // References
    // -> class RndMultiMesh * sMultiMesh;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
    // -> class Symbol name;
    // -> class SpotlightDrawer * sDefault;
    // -> struct [anonymous] __RTTI__15SpotlightDrawer;
    // -> class Symbol name;
    // -> class RndEnviron * sEnviron;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Symbol name;
}

// Range: 0x8045D0D0 -> 0x8045D17C
void SpotlightDrawer::SortLights() {
    // References
    // -> class vector sCans;
    // -> class vector sLights;
}

class ByEnvMesh {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
class ByColor {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x8045D17C -> 0x8045D728
void SpotlightDrawer::DrawWorld(class SpotlightDrawer * const this /* r27 */) {
    // Local variables
    class SpotlightEntry * spotIter; // r29
    class SpotlightEntry * const spotEnd; // r28
    class SpotlightEntry * const colorBegin; // r1+0x24
    class Color envColor; // r1+0x30
    class SpotlightEntry * colorEnd; // r1+0x20

    // References
    // -> unsigned char sHaveFloorSpots;
    // -> unsigned char sHaveFlares;
    // -> class Rnd & TheRnd;
    // -> unsigned char sNoBeams;
    // -> class RndMultiMesh * sMultiMesh;
    // -> unsigned char sHaveLenses;
    // -> unsigned char sHaveAdditionals;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndEnviron * sEnviron;
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
    // -> class vector sCans;
    // -> class vector sLights;
}

// Range: 0x8045D728 -> 0x8045DB04
void DrawAccessories(class RndMultiMesh * multiMesh /* r23 */, class SpotlightEntry * const & spotBegin /* r22 */, class SpotlightEntry * const & spotEnd /* r24 */) {
    // Local variables
    class RndMat * currMat; // r28
    class RndMesh * currMesh; // r27
    class SpotlightEntry * spotIter; // r26
    unsigned char changeMesh; // r25
    unsigned char changeMat; // r22

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class RndCam * sCurrent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndMesh * sDiskMesh;
}

// Range: 0x8045DB04 -> 0x8045DEDC
void DrawAccessories(class RndMultiMesh * multiMesh /* r23 */, class SpotlightEntry * const & spotBegin /* r22 */, class SpotlightEntry * const & spotEnd /* r24 */) {
    // Local variables
    class RndMat * currMat; // r28
    class RndMesh * currMesh; // r27
    class SpotlightEntry * spotIter; // r26
    unsigned char changeMesh; // r25
    unsigned char changeMat; // r22

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class RndCam * sCurrent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndMesh * sDiskMesh;
}

// Range: 0x8045DEDC -> 0x8045E1BC
void SpotlightDrawer::DrawMeshVec(class vector & vec /* r28 */) {
    // Local variables
    class SpotMeshEntry * meshIter; // r31
    class RndMesh * currMesh; // r30
    class RndEnviron * currEnv; // r29
    class SpotMeshEntry * const meshEnd; // r28
    unsigned char changeEnv; // r27
    unsigned char changeMesh; // r26

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class RndMultiMesh * sMultiMesh;
}

// Range: 0x8045E1BC -> 0x8045E260
void SpotlightDrawer::DrawFlares(class SpotlightEntry * spotIter /* r30 */, class SpotlightEntry * const & spotEnd /* r31 */) {
    // Local variables
    class Spotlight * sl; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8045E260 -> 0x8045E288
void SpotlightDrawer::ClearPostDraw() {
    // References
    // -> unsigned char sNeedDraw;
}

// Range: 0x8045E288 -> 0x8045E578
void SpotlightDrawer::ClearLights() {
    // References
    // -> unsigned char sHaveFloorSpots;
    // -> unsigned char sHaveFlares;
    // -> unsigned char sHaveLenses;
    // -> unsigned char sHaveAdditionals;
    // -> class vector sCans;
    // -> class vector sShadowSpots;
    // -> class vector sLights;
}

// Range: 0x8045E578 -> 0x8045E5D4
class Vector2 SpotlightDrawer::NGRadii() {
    // Local variables
    float topRadius; // f3
    float botRadius; // f4
}

// Range: 0x8045E5D4 -> 0x8045E644
void SpotlightDrawer::Copy(class SpotlightDrawer * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class SpotlightDrawer * m; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15SpotlightDrawer;
}

// Range: 0x8045E644 -> 0x8045E740
class SpotDrawParams & SpotDrawParams::__as(class SpotDrawParams * const this /* r29 */, const class SpotDrawParams & rhs /* r30 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A527F4
static class Symbol _s; // size: 0x4, address: 0x80A527FC
// Range: 0x8045E740 -> 0x8045ECF4
class DataNode SpotlightDrawer::Handle(class SpotlightDrawer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52804
static class Symbol _s; // size: 0x4, address: 0x80A5280C
static class Symbol _s; // size: 0x4, address: 0x80A52814
static class Symbol _s; // size: 0x4, address: 0x80A5281C
static class Symbol _s; // size: 0x4, address: 0x80A52824
// Range: 0x8045ECF4 -> 0x8045F0D8
unsigned char SpotlightDrawer::SyncProperty(class SpotlightDrawer * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x10C
} __vt__15SpotlightDrawer; // size: 0x10C, address: 0x808EFC20
struct {
    // total size: 0x18
} __vt__13PostProcessor; // size: 0x18, address: 0x808EFEE0
struct {
    // total size: 0x8
} __RTTI__PQ215SpotlightDrawer13SpotMeshEntry; // size: 0x8, address: 0x808F0088
struct {
    // total size: 0x8
} __RTTI__PQ215SpotlightDrawer14SpotlightEntry; // size: 0x8, address: 0x808F00B8
// Range: 0x8045F0D8 -> 0x8045F170
static void __sinit_\SpotlightDrawer_cpp() {
    // References
    // -> class vector sShadowSpots;
    // -> class vector sCans;
    // -> class vector sLights;
}


