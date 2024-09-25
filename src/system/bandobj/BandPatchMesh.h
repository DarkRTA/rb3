#pragma once
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/MeshDeform.h"
#include "rndobj/Tex.h"
#include "rndobj/Trans.h"

class BandCharDesc;

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

        MeshPair(Hmx::Object* o) : mesh(o, 0), patches(o) {}
        void AddMappingPatch(RndMesh*);
        PatchPair& AddPatch(bool);
        RndTex* OutputTex() const;
        const char* PatchName() const;

        ObjPtr<RndMesh, ObjectDir> mesh; // 0x0
        ObjVector<PatchPair> patches; // 0xc
    };

    class MeshFace {
    public:
    };

    class MeshVert {
    public:
        int AddUV(const MeshVert*, const Vector2&, const Vector2*);
        void SetVert(const MeshVert*, const RndMesh::Vert*);
        void SetVert(const RndMesh::Vert*);
        void ZeroOut();
        void Normalize(int);

        const RndMesh::Vert* mVert; // 0x0
        Vector3 unk4; // 0x4
        Vector3 unk10; // 0x10
        Vector2 unk1c; // 0x1c
        unsigned short unk24; // 0x24
        unsigned char unk26;
        int unk28;
        int unk2c;
        unsigned short unk30;
    };

    class WorkVerts {
    public:
        WorkVerts(RndMesh*, const Vector2&);
        ~WorkVerts();

        void Project();
        void SetMeshVerts();
        void SpreadEdges(int);
        void AddEdge(MeshVert*, MeshVert*);
        void AddFace(int, MeshVert*);
        int AddUvs(MeshVert*, MeshVert*, const Vector2*);
        void SetMeshVertAndTwins(int, MeshVert*);
        void AddMeshVertAndTwins(int, MeshVert*);
        void TryAddFace(int, int);
        void SortWorkVertsByZ();
        void SetVertsAndFaces(RndMesh*, bool);
        void ExtendTwin(const MeshVert*, Vector2&, Vector2&);
        void CopyDeformWeights(RndMeshDeform*, RndMeshDeform*);

        int unk0;
        std::vector<MeshVert*> mMeshVerts; // 0x4
        void* unkc;
        std::vector<MeshVert*> unk10;
        std::vector<RndMesh::Vert*> unk18;
        std::vector<unsigned short> unk20;
        std::vector<char> unk28;
        RndMesh* mMesh; // 0x30
        Vector2 unk34;
        Vector2 unk3c;
        Vector2 unk44;
        Vector2 unk4c;
        Vector2 unk54;
        Vector2 unk5c;
    };

    BandPatchMesh(Hmx::Object*);
    BandPatchMesh& operator=(const BandPatchMesh&);
    void AddMappingPatch(MeshPair&, RndMesh*);
    void ConstructQuad(RndTex*);
    void Construct(MeshPair&, RndTex*, bool, bool, WorkVerts*);
    bool ReProject();
    void ProjectPatches(const Transform&, RndTex*, bool);
    void ListDrawChildren(std::list<RndDrawable*>&);
    void PreRender(BandCharDesc*, int);
    void PostRender();
    void Compress(BandCharDesc*);
    void Render(RndTex*, RndMat*);
    bool FindXfm(RndMesh*, const Vector2&, Transform&);

    static void SetRenderToVert(RndMesh::Vert&, const Vector2&, const Vector2&);
    DECLARE_REVS;

    ObjVector<MeshPair> mMeshes; // 0x0
    bool mRenderTo; // 0xc
    ObjPtr<RndTransformable, ObjectDir> mSrc; // 0x10
    int mCategory; // 0x1c
};

bool PropSync(BandPatchMesh&, DataNode&, DataArray*, int, PropOp);

BinStream& operator>>(BinStream& bs, BandPatchMesh& mesh);