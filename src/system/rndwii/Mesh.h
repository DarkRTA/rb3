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
    OBJ_CLASSNAME(WiiMesh)
    OBJ_SET_TYPE(WiiMesh)

    static void Init();
    NEW_OBJ(WiiMesh)

    void ReleaseBuffers();

    u16 mNumVerts, mNumFaces;
    DisplayList mDisplays; // 0x158
};

#endif // RNDWII_MESH_H
