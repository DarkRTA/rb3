#ifndef RNDOBJ_MESH_H
#define RNDOBJ_MESH_H
#include "math/Bsp.h"
#include "math/strips/StdAfx.h"
#include "math/Vec.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/Trans.h"
#include "types.h"
#include <vector>

#define MAX_BONES 40

class RndMultiMesh;

class RndBone : public ObjPtr<RndTransformable, class ObjectDir> {
    public:
    RndBone(Hmx::Object* o) : ObjPtr<RndTransformable, class ObjectDir>(o, NULL) {}
    operator ObjPtr<RndTransformable, class ObjectDir>&() { return *this; } 
    void Load(BinStream&);

    Transform mOffset;
};

class RndMesh : public RndDrawable, public RndTransformable {
public:
    class Vert {
    public:
        Vert();
        Vector3 pos; // 0x0
        Vector3 norm; // 0xc
        Vector4_16_01 boneWeights; // 0x18 the hate format
        Hmx::Color32 color; // 0x20
        Vector2 uv; // 0x24
        short boneIndices[4]; // 0x28
    };

    class Face {
        public:
        u16 idx0, idx1, idx2;
    };

    enum Volume {
        kVolumeEmpty,
        kVolumeTriangles,
        kVolumeBSP,
        kVolumeBox
    };

    class VertVector { // more custom STL! woohoo!!!! i crave death
        public:
        VertVector() { mVerts = NULL; mSize = 0; mCapacity = 0;}
        ~VertVector() { mCapacity = 0; resize(0, true); }
        u32 size() const { return mSize; };
        void resize(int, bool);
        void reserve(int, bool);
        Vert* operator[](int);
        Vert* operator[](int) const;
        VertVector& operator=(const VertVector&);
        Vert* begin();
        Vert* end();
        unsigned short Capacity() const { return mCapacity; }

        Vert* mVerts;
        u32 mSize;
        u16 mCapacity;
    };

    RndMesh();
    OBJ_CLASSNAME(Mesh);
    OBJ_SET_TYPE(Mesh);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual RndDrawable* CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight() { RndDrawable::Highlight(); }
    virtual ~RndMesh();

    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void DrawFaces() {}
    virtual int NumFaces() const;
    virtual int NumVerts() const;
    virtual void Print();
    virtual void OnSync(int);

    RndMat* GetMat() const { return mMat; }
    VertVector& Verts(){ return mOwner->mVerts; }
    std::vector<Face>& Faces(){ return mOwner->mFaces; }
    const Vector3& VertPos(int idx) const {
        return mOwner->mVerts[idx]->pos;
    }

    // TODO: figure out what RndMesh's members do
    VertVector mVerts; // 0xB0
    std::vector<Face> mFaces; // 0xBC
    ObjPtr<RndMat, class ObjectDir> mMat; // 0xC4
    std::vector<u8, u16> unk_0xD0; // ???
    ObjOwnerPtr<RndMesh, class ObjectDir> mOwner; // 0xD8
    ObjVector<RndBone> mBones; // 0xe4
    int unk_0xF0, unk_0xF4;
    BSPNode* unk_0xF8;
    RndMultiMesh* unk_0xFC; // ...why?
    std::vector<STRIPERRESULT> unk_0x100;
    int unk_0x108, unk_0x10C;
    u8 unk_0x110;
    int* unk_0x114, unk_0x118;
    FileLoader* unk_0x11C;

    bool CacheStrips(BinStream&);
    void ClearCompressedVerts();
    void CopyBones(const RndMesh*);
    void CopyGeometryFromOwner();
    RndMultiMesh* CreateMultiMesh();
    void CreateStrip(int, int, Striper&, STRIPERRESULT&, bool);
    int EstimatedSizeKb() const;
    bool IsSkinned() const;
    int NumBones() const { return mBones.size(); }
    void PreLoadVertices(BinStream&);
    void PostLoadVertices(BinStream&);
    void RemoveInvalidBones();
    void ScaleBones(float);
    void SetMat(RndMat*);
    void SetGeomOwner(RndMesh*);
    void Sync(int);
    void SetBone(int, RndTransformable*, bool);
    bool KeepMeshData() const { return mKeepMeshData; }

    DECLARE_REVS
    NEW_OBJ(RndMesh)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMesh)
    }

    DataNode OnCompareEdgeVerts(const DataArray*);
    DataNode OnAttachMesh(const DataArray*);
    DataNode OnGetFace(const DataArray*);
    DataNode OnSetFace(const DataArray*);
    DataNode OnGetVertXYZ(const DataArray*);
    DataNode OnSetVertXYZ(const DataArray*);
    DataNode OnGetVertNorm(const DataArray*);
    DataNode OnSetVertNorm(const DataArray*);
    DataNode OnGetVertUV(const DataArray*);
    DataNode OnSetVertUV(const DataArray*);
    DataNode OnUnitizeNormals(const DataArray*);
    DataNode OnPointCollide(const DataArray*);
    DataNode OnConfigureMesh(const DataArray*);
    
    static int MaxBones();
};

BinStream& operator>>(BinStream&, RndMesh::Face&);
TextStream& operator<<(TextStream&, RndMesh::Volume);

class SyncMeshCB {
public:
    SyncMeshCB(){}
    virtual ~SyncMeshCB(){}
    virtual void SyncMesh(RndMesh*, int) = 0;
    virtual bool HasMesh(RndMesh*) = 0;
    virtual const std::vector<RndMesh::Vert>& GetVerts(RndMesh*) const = 0; // fix return type
};

#endif
