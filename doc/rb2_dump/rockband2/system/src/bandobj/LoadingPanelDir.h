/*
    Compile unit: C:\rockband2\system\src\bandobj\LoadingPanelDir.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8028C4D0 -> 0x8028DAD4
*/
// Range: 0x8028C4D0 -> 0x8028C840
void * LoadingPanelDir::LoadingPanelDir(class LoadingPanelDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__24ObjDirPtr<11CharClipSet>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11CharClipSet,9ObjectDir>;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__15LoadingPanelDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8028C840 -> 0x8028C884
void LoadingPanelDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8028C884 -> 0x8028CC70
void LoadingPanelDir::Enter(class LoadingPanelDir * const this /* r31 */) {
    // Local variables
    class Object * milo; // r30

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x8028CC70 -> 0x8028CF88
void LoadingPanelDir::RestoreClips(class LoadingPanelDir * const this /* r24 */) {
    // Local variables
    class CompositeCharacter * vocalist; // r30
    class CompositeCharacter * guitarist; // r29
    class CompositeCharacter * bassist; // r28
    class CompositeCharacter * drummer; // r27
    class String t1; // r1+0x74
    class CompositeCharacter * h2h0; // r26
    class String t2; // r1+0x68
    class CompositeCharacter * h2h1; // r25
}

// Range: 0x8028CF88 -> 0x8028D484
class DataNode LoadingPanelDir::OnImportClip(class LoadingPanelDir * const this /* r30 */) {
    // Local variables
    class CharClip * clip; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11CharClipSet;
    // -> class FilePath sNull;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8028D484 -> 0x8028D8FC
void LoadingPanelDir::SetBonesFromClip(class LoadingPanelDir * const this /* r30 */, class CharClip * clip /* r31 */) {
    // Local variables
    class CharBonesMeshes bones; // r1+0x50
    class list boneList; // r1+0x30
    class ObjDirItr bone; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x8028D8FC -> 0x8028D940
class Symbol LoadingPanelDir::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x8028D940 -> 0x8028DAD4
void LoadingPanelDir::SetType(class LoadingPanelDir * const this /* r29 */, class Symbol & LoadingPanelDir /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}


