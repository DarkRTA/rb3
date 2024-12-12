#ifndef RNDWII_MESH_H
#define RNDWII_MESH_H

#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/Mesh.h"

class DisplayList { // 0xC
public:
    DisplayList();
    ~DisplayList();
    static void Init();
    void Clear();
    void Copy(const DisplayList &);
    void Begin(unsigned short);
    void Begin(_GXPrimitive, _GXVtxFmt, unsigned short, unsigned short);
    void Start(_GXPrimitive, _GXVtxFmt, unsigned short);
    void End();
    DisplayList &operator<<(unsigned short);
    void Draw(u32, _GXVtxFmt) const;

    inline GXAttrType GetIdxType() {
        GXAttrType x = GX_INDEX16;
        if (unk_0x8 < 0x100)
            x = GX_INDEX8;
        return x;
    }

    void *mData;
    int mSize;
    int unk_0x8;

    static void *sTemp;
    static void *sCurr;
};

/**
 * @brief Platform implementation of RndMesh.
 * WiiMesh uses DisplayList to drastically improve CPU-side draw timings,
 * as well as set things like reflections, buffers, and etc.
 */
class WiiMesh : public RndMesh { // 0x198
public:
    WiiMesh();
    ~WiiMesh();
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual int NumVerts() const { return mNumVerts; }
    virtual int NumFaces() const { return mNumFaces; }
    OBJ_CLASSNAME(WiiMesh)
    OBJ_SET_TYPE(WiiMesh)

    static void Init();
    REGISTER_OBJ_FACTORY_FUNC(WiiMesh)
    NEW_OBJ(WiiMesh)

    NEW_OVERLOAD

    void ReleaseBuffers();
    void CreateBuffers();
    void SetVertexDesc();
    void DrawFaces();
    void DrawReflection(bool);
    void RemoveVertData();
    void SetVertexBuffers(const void *);
    int GetSomeSizeFactor();

    void *mCTVtxs; // 0x138
    void *mPosNrmVtxs; // 0x13C
    void *mPosQ; // 0x140
    void *mNrmQ; // 0x144
    void *mBoneWeights; // 0x148
    void *mBoneIndices; // 0x14C
    void *unk_0x150;
    u16 mNumVerts; // 0x154
    u16 mNumFaces; // 0x156
    DisplayList mDisplays; // 0x158
    u16 unk_0x164; // 0x164
    u8 bitmask_0 : 1; // 0x166
    u8 bitmask_1 : 1;
    u8 bitmask_2 : 1;
    u8 bitmask_3 : 1;
    u8 bitmask_4 : 1;
    u8 bitmask_5 : 1;
    u8 bitmask_6 : 1;
    u8 bitmask_7 : 1;

    u32 unk_0x168;
};

#endif // RNDWII_MESH_H
