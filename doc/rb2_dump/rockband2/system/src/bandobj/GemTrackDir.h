/*
    Compile unit: C:\rockband2\system\src\bandobj\GemTrackDir.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802A8940 -> 0x802A99FC
*/
// Range: 0x802A8940 -> 0x802A8984
void GemTrackDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802A8984 -> 0x802A8D10
void GemTrackDir::PreLoad(class GemTrackDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x14
    class ObjPtr tmp; // r1+0x18
    int ii; // r29
    int ii; // r29
    int ii; // r29
    float unused; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Debug TheDebug;
}

// Range: 0x802A8D10 -> 0x802A8D54
class Symbol GemTrackDir::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x802A8D54 -> 0x802A8FC0
void GemTrackDir::SetPitch(class GemTrackDir * const this /* r31 */, float pitch /* f31 */) {
    // Local variables
    class Vector3 e; // r1+0x20
    class Matrix3 m; // r1+0x30
    float theta; // f31
    float newY; // f3
    class Vector3 streakPos; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x802A8FC0 -> 0x802A9004
class RndDir * GemTrackDir::GetObj() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x802A9004 -> 0x802A9048
class RndPropAnim * GemTrackDir::GetObj() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
}

// Range: 0x802A9048 -> 0x802A908C
class TrackWidget * GemTrackDir::GetObj() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
}

// Range: 0x802A908C -> 0x802A90D0
class RndGroup * GemTrackDir::GetObj() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x802A90D0 -> 0x802A9114
class EventTrigger * GemTrackDir::GetObj() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802A9114 -> 0x802A985C
void * GemTrackDir::~GemTrackDir(class GemTrackDir * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPropAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11TrackWidget,9ObjectDir>;
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
}

// Range: 0x802A985C -> 0x802A9860
class RndDir * GemTrackDir::ThisDir() {}

// Range: 0x802A9860 -> 0x802A9864
class RndDir * GemTrackDir::ThisDir() {}

// Range: 0x802A9864 -> 0x802A9868
class GemTrackDir * GemTrackDir::AsGemTrackDir() {}

// Range: 0x802A9868 -> 0x802A99FC
void GemTrackDir::SetType(class GemTrackDir * const this /* r29 */, class Symbol & GemTrackDir /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}


