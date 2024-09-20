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

class PatchVerts {
public:
    PatchVerts() : mCentroid(0,0,0) {}
    ~PatchVerts(){}
    Vector3 mCentroid; // 0x0
    std::vector<int> mPatchVerts; // 0xc
};

class MotionBlurCache {
public:
    MotionBlurCache(){
        mCacheKey[0] = 0;
        mCacheKey[1] = 0;
        mShouldCache = false;
    }
    unsigned int mCacheKey[2]; // 0x0, 0x4
    bool mShouldCache; // 0x8
};

class RndBone {
public:
    RndBone(Hmx::Object* o) : mBone(o, NULL) {}
    void Load(BinStream&);

    ObjPtr<RndTransformable, ObjectDir> mBone; // 0x0
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
        Face() : idx0(0), idx1(0), idx2(0) {}
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
        VertVector() { mVerts = NULL; mNumVerts = 0; mCapacity = 0;}
        ~VertVector() { mCapacity = 0; resize(0, true); }
        int size() const { return mNumVerts; }
        bool empty() const { return mNumVerts == 0; }
        void resize(int, bool);
        void reserve(int, bool);
        Vert& operator[](int i){ return mVerts[i]; }
        const Vert& operator[](int i) const { return mVerts[i]; }
        VertVector& operator=(const VertVector&);
        Vert* begin(){ return &mVerts[0]; }
        Vert* end(){ return &mVerts[mNumVerts]; }
        unsigned short capacity() const { return mCapacity; }
        void clear(){ resize(0, true); }

        Vert* mVerts;
        int mNumVerts;
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
#ifdef MILO_DEBUG
    virtual int NumFaces() const;
    virtual int NumVerts() const;
#endif
    virtual void Print();
    virtual void OnSync(int);

    void SetNumVerts(int);
    void SetNumFaces(int);
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
    bool HasValidBones(unsigned int*) const;
    void SetBone(int, RndTransformable*, bool);
    void SetVolume(Volume);
    void SetKeepMeshData(bool);

    bool KeepMeshData() const { return mKeepMeshData; }
    Volume GetVolume() const { return mGeomOwner->mVolume; }
    BSPNode* GetBSPTree() const { return mGeomOwner->mBSPTree; }
    RndMat* GetMat() const { return mMat; }
    VertVector& Verts(){ return mGeomOwner->mVerts; }
    std::vector<Face>& Faces(){ return mGeomOwner->mFaces; }
    const Vector3& VertPos(int idx) const {
        return mGeomOwner->mVerts[idx].pos;
    }

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

    // TODO: figure out what RndMesh's members do
    VertVector mVerts; // 0xB0
    std::vector<Face> mFaces; // 0xBC
    ObjPtr<RndMat, class ObjectDir> mMat; // 0xC4
    std::vector<u8, u16> unk_0xD0; // ???
    ObjOwnerPtr<RndMesh, class ObjectDir> mGeomOwner; // 0xD8
    ObjVector<RndBone> mBones; // 0xe4
    int mMutable; // 0xf0
    Volume mVolume; // 0xf4
    BSPNode* mBSPTree; // 0xf8
    RndMultiMesh* unk_0xFC; // ...why?
    std::vector<STRIPERRESULT> unk_0x100; // maybe some struct that has a STRIPERRESULT?
    MotionBlurCache mMotionCache; // 0x108
    int* unk_0x114, unk_0x118;
    FileLoader* unk_0x11C;
    int unk120;
    int unk124;
    int unk128;
    int unk12c;
    int unk130;
    int unk134;
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
