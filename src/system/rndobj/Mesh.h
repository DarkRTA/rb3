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

inline BinStream& operator>>(BinStream& bs, RndBone& bone){
    bs >> bone.mBone >> bone.mOffset;
    return bs;
}

class RndMesh : public RndDrawable, public RndTransformable {
public:
    class Vert {
    public:
        Vert() : pos(0,0,0), norm(0,1,0), boneWeights(0,0,0,0), color(-1), uv(0,0) {
            for(int i = 0; i < 4; i++) boneIndices[i] = 0;
        }

        NEW_OVERLOAD;
        DELETE_OVERLOAD;

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
        unsigned short& operator[](int i){ return *(&idx0 + i); }
        void Set(u16 i0, u16 i1, u16 i2){
            idx0 = i0; idx1 = i1; idx2 = i2;
        }

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

        Vert* mVerts; // 0x0
        int mNumVerts; // 0x4
        unsigned short mCapacity; // 0x8
        unsigned short unka; // 0xa
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
    void SetZeroWeightBones();
    void CopyGeometry(const RndMesh*, bool);
    Vector3 SkinVertex(const RndMesh::Vert&, Vector3*);

    RndMesh* GeometryOwner() const { return mGeomOwner; }
    bool KeepMeshData() const { return mKeepMeshData; }
    int GetMutable() const { return mGeomOwner->mMutable; }
    Volume GetVolume() const { return mGeomOwner->mVolume; }
    BSPNode* GetBSPTree() const { return mGeomOwner->mBSPTree; }
    RndMat* Mat() const { return mMat; }
    VertVector& Verts(){ return mGeomOwner->mVerts; }
    std::vector<Face>& Faces(){ return mGeomOwner->mFaces; }
    Vert& VertAt(int idx){ return mGeomOwner->mVerts[idx]; }
    bool IsSkinned() const { return !mBones.empty(); }
    void SetMutable(int m){ mGeomOwner->mMutable = m; }
    bool HasAOCalc() const { return mHasAOCalc; }
    void SetHasAOCalc(bool b){ mHasAOCalc = b; }

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
    static int sLastCollide;
    static bool sRawCollide;
    static void SetRawCollide(bool b){ sRawCollide = b; }

    // TODO: figure out what RndMesh's members do
    VertVector mVerts; // 0xB0
    std::vector<Face> mFaces; // 0xBC
    ObjPtr<RndMat, class ObjectDir> mMat; // 0xC4
    std::vector<unsigned char> mPatches; // 0xd0
    ObjOwnerPtr<RndMesh, class ObjectDir> mGeomOwner; // 0xD8
    ObjVector<RndBone> mBones; // 0xe4
    int mMutable; // 0xf0
    Volume mVolume; // 0xf4
    BSPNode* mBSPTree; // 0xf8
    RndMultiMesh* mMultiMesh; // 0xfc
    std::vector<STRIPERRESULT> mStriperResults; // 0x100
    MotionBlurCache mMotionCache; // 0x108
    unsigned char* mCompressedVerts; // 0x114
    unsigned int mNumCompressedVerts; // 0x118
    FileLoader* mFileLoader; // 0x11c
    int mBoxLightColorsCached[6]; // 0x120 - apparently these are _GXColors instead of ints
};

BinStream& operator>>(BinStream&, RndMesh::Vert&);
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
