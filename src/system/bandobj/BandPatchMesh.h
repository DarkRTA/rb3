#pragma once
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Tex.h"
#include "rndobj/Trans.h"

class BandPatchMesh {
public:
    class MeshPair {
    public:
        class PatchPair {
        public:
            PatchPair(Hmx::Object* o) : mPatch(o, 0), mTex(o, 0) {}

            ObjPtr<RndMesh, ObjectDir> mPatch; // 0x0
            ObjPtr<RndTex, ObjectDir> mTex; // 0xc
        };

        MeshPair(Hmx::Object* o) : mMesh(o, 0), mPatches(o) {}

        ObjPtr<RndMesh, ObjectDir> mMesh; // 0x0
        ObjVector<PatchPair> mPatches; // 0xc
    };

    BandPatchMesh(Hmx::Object*);

    ObjVector<MeshPair> mMeshes; // 0x0
    bool mRenderTo; // 0xc
    ObjPtr<RndTransformable, ObjectDir> mSrc; // 0x10
    int mCategory; // 0x1c
};

bool PropSync(BandPatchMesh&, DataNode&, DataArray*, int, PropOp);