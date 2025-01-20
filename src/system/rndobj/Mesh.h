#pragma once
#include "math/Bsp.h"
#include "math/strips/StdAfx.h"
#include "math/Vec.h"
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "obj/Object.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/Trans.h"
#include "types.h"
#include "utl/MemMgr.h"
#include <vector>

#define MAX_BONES 40

class RndMultiMesh;

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

/** A bone to associate with a Mesh. */
class RndBone {
public:
    RndBone(Hmx::Object* o) : mBone(o, NULL) {}
    void Load(BinStream&);

    /** "Trans of the bone" */
    ObjPtr<RndTransformable, ObjectDir> mBone; // 0x0
    Transform mOffset;
};

inline BinStream& operator>>(BinStream& bs, RndBone& bone){
    bs >> bone.mBone >> bone.mOffset;
    return bs;
}

/**
 * @brief A mesh object, used to make models.
 * Original _objects description:
 * "A Mesh object is composed of triangle faces."
 */
class RndMesh : public RndDrawable, public RndTransformable {
public:
    /** A mesh vertex. */
    class Vert {
    public:
        Vert() : pos(0,0,0), norm(0,1,0), boneWeights(0,0,0,0), color(-1), uv(0,0) {
            for(int i = 0; i < 4; i++) boneIndices[i] = 0;
        }

        NEW_OVERLOAD;
        NEW_ARRAY_OVERLOAD;
        DELETE_OVERLOAD;
        DELETE_ARRAY_OVERLOAD;

        /** The vertex's position. */
        Vector3 pos; // 0x0
        /** The vertex's normal. */
        Vector3 norm; // 0xc
        /** The vertex's bone weight group. */
        Vector4_16_01 boneWeights; // 0x18 the hate format
        /** The vertex point's color. */
        Hmx::Color32 color; // 0x20
        /** The vertex's UV. */
        Vector2 uv; // 0x24
        /** The vertex's bone indices. */
        short boneIndices[4]; // 0x28
    };

    /** A triangle mesh face. */
    class Face {
    public:
        Face() : v1(0), v2(0), v3(0) {}
        unsigned short& operator[](int i){ return *(&v1 + i); }
        void Set(int i0, int i1, int i2){
            v1 = i0; v2 = i1; v3 = i2;
        }

        /** The three points that make up the face. */
        u16 v1, v2, v3;
    };

    enum Volume {
        kVolumeEmpty,
        kVolumeTriangles,
        kVolumeBSP,
        kVolumeBox
    };

    /** A specialized vector for RndMesh vertices. */
    class VertVector { // more custom STL! woohoo!!!! i crave death
    public:
        VertVector() { mVerts = NULL; mNumVerts = 0; mCapacity = 0;}
        ~VertVector() { mCapacity = 0; resize(0, true); }
        int size() const { return mNumVerts; }
        bool empty() const { return mNumVerts == 0; }
        void resize(int, bool);
        void reserve(int, bool);
        void realloc_perm();
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
    /** "Number of faces in the mesh" */
    virtual int NumFaces() const;
    /** "Number of verts in the mesh" */
    virtual int NumVerts() const;
#endif
    virtual void Print();
    virtual void OnSync(int);

    /** Set the number of vertices this Mesh should have.
     * @param [in] num The number to set.
     */
    void SetNumVerts(int num);
    /** Set the number of faces this Mesh should have.
     * @param [in] num The number to set.
     */
    void SetNumFaces(int num);
    bool CacheStrips(BinStream&);
    /** Clear the list of compressed vertices. */
    void ClearCompressedVerts();
    /** Copy the bones from the supplied Mesh. If the other Mesh is NULL, clear our current bone list.
     * @param [in] m The other Mesh.
     */
    void CopyBones(const RndMesh* m);
    void CopyGeometryFromOwner();
    /** Create a MultiMesh that will draw this Mesh multiple times.
     * @returns The newly created MultiMesh.
     */
    RndMultiMesh* CreateMultiMesh();
    void CreateStrip(int, int, Striper&, STRIPERRESULT&, bool);
    int EstimatedSizeKb() const;
    /** Routine to load any relevant vertex data from the BinStream before the main Load method executes. */
    void PreLoadVertices(BinStream&);
    /** Routine to load any relevant vertex data from the BinStream after the main Load method executes. */
    void PostLoadVertices(BinStream&);
    /** Remove all RndBones from our bone list that have NULL bone values. */
    void RemoveInvalidBones();
    /** Scale all our bones by a given value.
     * @param [in] val The scalar value.
     */
    void ScaleBones(float val);
    void Sync(int);
    /** Check if all our bones are valid (i.e. not NULL).
     * @param [out] idx The index of the first invalid bone, or the bone vector's size if everything is valid.
     * @returns True if all our bones are valid, false otherwise.
     */
    bool HasValidBones(unsigned int* idx) const;
    /** Set the bone at the given index.
     * @param [in] idx The index of the bone to set.
     * @param [in] bone The bone to set.
     * @param [in] calcOffset If true, calculate this bone's resulting offset.
     */
    void SetBone(int idx, RndTransformable* bone, bool calcOffset);
    void SetVolume(Volume);
    void SetKeepMeshData(bool);
    void SetZeroWeightBones();
    void CopyGeometry(const RndMesh*, bool);
    int CollidePlane(const RndMesh::Face&, const Plane&);
    Vector3 SkinVertex(const RndMesh::Vert&, Vector3*);
    void UpdateApproxLighting();

    bool PatchOkay(int i, int j){
        return i * 4.31 + j * 0.25 < 329.0;
    }

    // getters/setters
    void SetMat(RndMat*);
    void SetGeomOwner(RndMesh*);
    int NumBones() const { return mBones.size(); }
    RndMesh* GeometryOwner() const { return mGeomOwner; }
    bool KeepMeshData() const { return mKeepMeshData; }
    int GetMutable() const { return mGeomOwner->mMutable; }
    Volume GetVolume() const { return mGeomOwner->mVolume; }
    BSPNode* GetBSPTree() const { return mGeomOwner->mBSPTree; }
    RndMat* Mat() const { return mMat; }
    VertVector& Verts(){ return mGeomOwner->mVerts; }
    std::vector<Face>& Faces(){ return mGeomOwner->mFaces; }
    Vert& VertAt(int idx){ return mGeomOwner->mVerts[idx]; }
    Face& FaceAt(int idx){ return mGeomOwner->mFaces[idx]; }
    bool IsSkinned() const { return !mBones.empty(); }
    void SetMutable(int m){ mGeomOwner->mMutable = m; }
    bool HasAOCalc() const { return mHasAOCalc; }
    void SetHasAOCalc(bool b){ mHasAOCalc = b; }
    void SetForceNoQuantize(bool b){ mForceNoQuantize = b; }
    RndTransformable* BoneTransAt(int idx){ return mBones[idx].mBone; }
    Transform& BoneOffsetAt(int idx){ return mBones[idx].mOffset; }

    DECLARE_REVS
    NEW_OBJ(RndMesh)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMesh)
    }

    DataNode OnCompareEdgeVerts(const DataArray*);
    /** Handler to attach another Mesh's verts/faces to this one.
     * Note that the other Mesh will be deleted after the attaching is done.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the other RndMesh.
     * Example usage: {$this attach_mesh other_obj}
     */
    DataNode OnAttachMesh(const DataArray* arr);
    /** Handler to get the vertices of the Face at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-5: vars to house the Face's three vertices.
     * Example usage: {$this get_face 69 $v1 $v2 $v3}
     */
    DataNode OnGetFace(const DataArray* arr);
    /** Handler to set the vertices of the Face at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-5: the values of the Face's three vertices to set.
     * Example usage: {$this set_face 69 1 2 3}
     */
    DataNode OnSetFace(const DataArray* arr);
    /** Handler to get the positional coordinates of the Vert at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-5: vars to house the Vert's X/Y/Z pos coordinates.
     * Example usage: {$this get_vert_pos 69 $v1 $v2 $v3}
     */
    DataNode OnGetVertXYZ(const DataArray* arr);
    /** Handler to set the positional coordinates of the Vert at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-5: the values of the Vert's X/Y/Z pos coordinates to set.
     * Example usage: {$this set_vert_pos 69 1 2 3}
     */
    DataNode OnSetVertXYZ(const DataArray* arr);
    /** Handler to get the normal coordinates of the Vert at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-5: vars to house the Vert's X/Y/Z norm coordinates.
     * Example usage: {$this get_vert_norm 69 $v1 $v2 $v3}
     */
    DataNode OnGetVertNorm(const DataArray* arr);
    /** Handler to set the normal coordinates of the Vert at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-5: the values of the Vert's X/Y/Z norm coordinates to set.
     * Example usage: {$this set_vert_norm 69 1 2 3}
     */
    DataNode OnSetVertNorm(const DataArray* arr);
    /** Handler to get the UV coordinates of the Vert at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-4: vars to house the Vert's UV X/Y coordinates.
     * Example usage: {$this get_vert_uv 69 $v1 $v2}
     */
    DataNode OnGetVertUV(const DataArray* arr);
    /** Handler to set the UV coordinates of the Vert at the supplied index.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: the desired index.
     *     Nodes 3-4: the values of the Vert's X/Y UV coordinates to set.
     * Example usage: {$this set_vert_uv 69 1 2}
     */
    DataNode OnSetVertUV(const DataArray* arr);
    DataNode OnUnitizeNormals(const DataArray*);
    DataNode OnPointCollide(const DataArray*);
    DataNode OnConfigureMesh(const DataArray*);
    
    static int MaxBones();
    static int sLastCollide;
    static bool sRawCollide;
    static bool sUpdateApproxLight;
    static void SetRawCollide(bool b){ sRawCollide = b; }
    static void SetUpdateApproxLight(bool b){ sUpdateApproxLight = b; }

    /** This mesh's vertices. */
    VertVector mVerts; // 0xB0
    /** This mesh's faces. */
    std::vector<Face> mFaces; // 0xBC
    /** "Material used for rendering the Mesh" */
    ObjPtr<RndMat> mMat; // 0xC4
    std::vector<unsigned char> mPatches; // 0xd0
    /** "Geometry owner for the mesh" */
    ObjOwnerPtr<RndMesh> mGeomOwner; // 0xD8
    /** This mesh's bones. */
    ObjVector<RndBone> mBones; // 0xe4
    int mMutable; // 0xf0
    /** "Volume of the Mesh" */
    Volume mVolume; // 0xf4
    BSPNode* mBSPTree; // 0xf8
    /** The MultiMesh that will draw this Mesh multiple times. */
    RndMultiMesh* mMultiMesh; // 0xfc
    std::vector<STRIPERRESULT> mStriperResults; // 0x100
    MotionBlurCache mMotionCache; // 0x108
    unsigned char* mCompressedVerts; // 0x114
    unsigned int mNumCompressedVerts; // 0x118
    FileLoader* mFileLoader; // 0x11c
    GXColor mBoxLightColorsCached[6]; // 0x120
};

BinStream& operator>>(BinStream&, RndMesh::Vert&);
BinStream& operator>>(BinStream&, RndMesh::Face&);
TextStream& operator<<(TextStream&, RndMesh::Volume);

class SyncMeshCB {
public:
    class Vert {
    public:
        Vert(){}

        Vector3 pos; // 0x0
        Vector3 norm; // 0xc
    };

    SyncMeshCB(){}
    virtual ~SyncMeshCB(){}
    virtual void SyncMesh(RndMesh*, int) = 0;
    virtual bool HasMesh(RndMesh*) = 0;
    virtual const std::vector<SyncMeshCB::Vert>& GetVerts(RndMesh*) const = 0; // fix return type
};

class PatchVerts {
public:
    PatchVerts() : mCentroid(0,0,0) {}
    ~PatchVerts(){}

    int NumVerts() const { return mPatchVerts.size(); }

    void Add(int, RndMesh::VertVector&, Vector3&);

    void Clear(){
        mPatchVerts.clear();
        mCentroid.Set(0, 0, 0);
    }

    bool HasVert(int vert) const {
        int idx = GreaterEq(vert);
        if(idx < mPatchVerts.size()){
            return mPatchVerts[idx] == vert;
        }
        else return false;
    }

    int GreaterEq(int iii) const {
        if(!mPatchVerts.empty() && mPatchVerts.front() < iii){
            if(mPatchVerts.back() < iii){
                return mPatchVerts.size();
            }
            else {
                int u5 = 0;
                int u2 = mPatchVerts.size() - 1;
                if(u5 + 1 < u2){
                    int u4 = (u5 + u2) >> 1;
                    int curVert = mPatchVerts[u4];
                    if(curVert < iii){
                        u5 = u4;
                    }
                    if(iii <= curVert){
                        u2 = u4;
                    }
                }
                return u2;
            }
        }
        else return 0;
    }

    Vector3 mCentroid; // 0x0
    std::vector<int> mPatchVerts; // 0xc
};