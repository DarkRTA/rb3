/*
    Compile unit: C:\rockband2\system\src\char\CharUtl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80396634 -> 0x80398F0C
*/
// Range: 0x80396634 -> 0x803966A8
static class DataNode OnValidateStops(class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
}

// Range: 0x803966A8 -> 0x8039671C
static class DataNode OnResetHair(class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Character;
}

// Range: 0x8039671C -> 0x803968B4
static class DataNode OnCharCompressClips(class DataArray * msg /* r29 */) {
    // Local variables
    class ClipCompressor comp; // r1+0x28

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11CharClipSet;
}

class MeshCacheMgr : public SyncMeshCB {
    // total size: 0x10
protected:
    class vector mCache; // offset 0x4, size 0xC
};
// Range: 0x803968B4 -> 0x803968D4
void * MeshCacheMgr::MeshCacheMgr() {
    // References
    // -> struct [anonymous] __vt__12MeshCacheMgr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class MeshCacher {
    // total size: 0x20
protected:
    class RndMesh * mMesh; // offset 0x0, size 0x4
    int mSyncFlags; // offset 0x4, size 0x4
    class vector mVerts; // offset 0x8, size 0xC
    class vector mFaces; // offset 0x14, size 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class MeshCacher * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class MeshCacher * * _M_start; // offset 0x0, size 0x4
    class MeshCacher * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x803968D4 -> 0x80396C58
void * MeshCacheMgr::~MeshCacheMgr(class MeshCacheMgr * const this /* r28 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12MeshCacheMgr;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Vert * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Vert * _M_start; // offset 0x0, size 0x4
    struct Vert * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
// Range: 0x80396C58 -> 0x80396CA4
unsigned char MeshCacheMgr::HasMesh() {
    // Local variables
    int i; // r6
}

// Range: 0x80396CA4 -> 0x803970CC
void MeshCacheMgr::SyncMesh(class MeshCacheMgr * const this /* r29 */, class RndMesh * mesh /* r27 */, int syncFlags /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803970CC -> 0x8039723C
void MeshCacheMgr::StuffMeshes(class MeshCacheMgr * const this /* r29 */, class ObjPtrList & meshes /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8039723C -> 0x8039737C
unsigned char CharUtlIsAnimatable(class RndTransformable * bone /* r29 */) {
    // Local variables
    class RndMesh * m; // r0

    // References
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __RTTI__8CharCuff;
    // -> struct [anonymous] __RTTI__11CharCollide;
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

// Range: 0x8039737C -> 0x803975C4
static void MoveToFacing(class Transform & t /* r29 */, float * rot /* r30 */, class Vector3 * pos /* r31 */) {}

// Range: 0x803975C4 -> 0x80397A48
void * CharUtlBoneSaver::~CharUtlBoneSaver(class CharUtlBoneSaver * const this /* r28 */) {
    // Local variables
    int i; // r30
    class ObjDirItr bone; // r1+0x2C

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80397A48 -> 0x80397DA4
void CharUtlResetTransform() {
    // Local variables
    class ObjDirItr t; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80397DA4 -> 0x80397DAC
class CharClip * ClipPredict::Clip() {}

// Range: 0x80397DAC -> 0x80397FE0
void ClipPredict::PredictNext(class ClipPredict * const this /* r31 */, float frame /* f29 */) {
    // Local variables
    class Vector3 pos; // r1+0x10
    float ang; // f31
    float dang; // f0
}

// Range: 0x80397FE0 -> 0x80398230
void ClipPredict::Predict(class ClipPredict * const this /* r31 */, float startFrame /* f31 */, float endFrame /* f30 */) {
    // Local variables
    class Vector3 pos; // r1+0x20
    float ang; // r1+0x10
    float dang; // f0
}

// Range: 0x80398230 -> 0x80398324
void ClipBonePredict::Predict(class ClipBonePredict * const this /* r30 */, class CharClip * clip /* r31 */, float frame /* f31 */) {}

// Range: 0x80398324 -> 0x80398B0C
void CharUtlValidateStops(class CharClipSet * clips /* r29 */) {
    // Local variables
    class ObjDirItr left; // r1+0x50
    const char * lf; // r0
    char buffer[256]; // r1+0xC0
    char * rf; // r30
    class CharClip * right; // r28
    class ClipPredict pred; // r1+0x70
    float stride; // f31
    float br; // f30
    float leftBlendStart; // f29
    class Vector3 leftBlend; // r1+0x40
    float rightStride; // f28
    float rightBlendStart; // f6
    class Vector3 rightBlend; // r1+0x30
    float dist; // f30
    float frac; // f28

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x80398B0C -> 0x80398C00
class RndTransformable * CharUtlFindBone(const char * prefix /* r0 */, class ObjectDir * parent /* r28 */) {
    // Local variables
    char buffer[256]; // r1+0x8
    char * c; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80398C00 -> 0x80398F0C
void CharUtlResetHair() {
    // Local variables
    class ObjDirItr hair; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharHair;
}

struct {
    // total size: 0x14
} __vt__12MeshCacheMgr; // size: 0x14, address: 0x808DCA58
struct {
    // total size: 0x8
} __RTTI__12MeshCacheMgr; // size: 0x8, address: 0x808DCA88
struct {
    // total size: 0x14
} __vt__10SyncMeshCB; // size: 0x14, address: 0x808DCA90
struct {
    // total size: 0x8
} __RTTI__10SyncMeshCB; // size: 0x8, address: 0x808DCAB0
struct {
    // total size: 0x8
} __RTTI__PP10MeshCacher; // size: 0x8, address: 0x808DCC00
struct {
    // total size: 0x8
} __RTTI__P9Transform; // size: 0x8, address: 0x808DCC18
struct {
    // total size: 0x8
} __RTTI__PP16RndTransformable; // size: 0x8, address: 0x808DCC38
struct _OKToMemCpy {
    // total size: 0x1
};
struct Vert {
    // total size: 0x20
    class Vector3 p; // offset 0x0, size 0x10
    class Vector3 n; // offset 0x10, size 0x10
};
struct {
    // total size: 0x8
} __RTTI__PQ210MeshCacher4Vert; // size: 0x8, address: 0x808DCC70

