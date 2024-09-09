#pragma once
#include "obj/Object.h"
#include "rndobj/Trans.h"

class BandPatchMesh {
public:
    class MeshPair {
    public:
    };

    BandPatchMesh();

    ObjVector<MeshPair> mMeshes; // 0x0
    bool mRenderTo; // 0xc
    ObjPtr<RndTransformable, ObjectDir> mSrc; // 0x10
    int mCategory; // 0x1c
};