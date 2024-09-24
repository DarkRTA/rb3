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

        MeshPair(Hmx::Object* o) : mesh(o, 0), mPatches(o) {}

        ObjPtr<RndMesh, ObjectDir> mesh; // 0x0
        ObjVector<PatchPair> mPatches; // 0xc
    };

    class MeshVert {
    public:
        void SetVert(const MeshVert*, const RndMesh::Vert*);
        void SetVert(const RndMesh::Vert*);
        void ZeroOut();
        void Normalize(int);

        const RndMesh::Vert* mVert; // 0x0
        Vector3 unk4; // 0x4
        Vector3 unk10; // 0x10
        Vector2 unk1c; // 0x1c
        bool unk24;
        bool unk25;
        unsigned char unk26;
    };

    BandPatchMesh(Hmx::Object*);
    BandPatchMesh& operator=(const BandPatchMesh&);

    static void SetRenderToVert(RndMesh::Vert&, const Vector2&, const Vector2&);
    DECLARE_REVS;

    ObjVector<MeshPair> mMeshes; // 0x0
    bool mRenderTo; // 0xc
    ObjPtr<RndTransformable, ObjectDir> mSrc; // 0x10
    int mCategory; // 0x1c
};

bool PropSync(BandPatchMesh&, DataNode&, DataArray*, int, PropOp);

BinStream& operator>>(BinStream& bs, BandPatchMesh& mesh);