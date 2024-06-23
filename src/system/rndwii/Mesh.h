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
    void Draw(u32, _GXVtxFmt) const;

    void* mData;
    int mSize;
    int unk_0x8;
};

class WiiMesh : public RndMesh { // 0x198
    WiiMesh();

    virtual void Copy(const Hmx::Object*, CopyType);
    OBJ_CLASSNAME(WiiMesh)
    OBJ_SET_TYPE(WiiMesh)

    static void Init();
    NEW_OBJ(WiiMesh)

    u16 mNumVerts, mNumFaces;
    DisplayList mDisplays; // 0x158
};

#endif // RNDWII_MESH_H
