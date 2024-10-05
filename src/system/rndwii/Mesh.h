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
    void Copy(const DisplayList&);
    void Begin(unsigned short);
    void Begin(_GXPrimitive, _GXVtxFmt, unsigned short, unsigned short);
    void Start(_GXPrimitive, _GXVtxFmt, unsigned short);
    void End();
    DisplayList& operator<<(unsigned short);
    void Draw(u32, _GXVtxFmt) const;

    void* mData;
    int mSize;
    int unk_0x8;

    static void* sTemp;
    static void* sCurr;
};

class WiiMesh : public RndMesh { // 0x198
    WiiMesh();
    ~WiiMesh();
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual int NumVerts() const { return mNumVerts; }
    virtual int NumFaces() const { return mNumFaces; }
    OBJ_CLASSNAME(WiiMesh)
    OBJ_SET_TYPE(WiiMesh)

    static void Init();
    NEW_OBJ(WiiMesh)

    void ReleaseBuffers();
    void CreateBuffers();
    void SetVertexDesc();
    void DrawFaces();
    void DrawReflection(bool);
    void RemoveVertData();
    void SetVertexBuffers(const void*);

    void* unk_0x138;
    void* unk_0x13C;
    void* unk_0x140;
    void* unk_0x144;
    void* unk_0x148;
    void* unk_0x14C;
    void* unk_0x150;
    u16 mNumVerts; // 0x154
    u16 mNumFaces; // 0x156
    DisplayList mDisplays; // 0x158
    u8 pad[2];
    u8 bitmask_0 : 1;
    u8 bitmask_1 : 1;
    u8 bitmask_2 : 1;
    u8 bitmask_3 : 1;
    u8 bitmask_4 : 1;
    u8 bitmask_5 : 1;
    u8 bitmask_6 : 1;
    u8 bitmask_7 : 1;
};

#endif // RNDWII_MESH_H
