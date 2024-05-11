#ifndef RNDOBJ_MESH_H
#define RNDOBJ_MESH_H
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/Trans.h"
#include "types.h"
#include <vector>

#define MAX_BONES 40

class RndMultiMesh;

class RndBone : public ObjPtr<RndTransformable, ObjectDir> {
    public:
    RndBone() : ObjPtr<RndTransformable, ObjectDir>(NULL, NULL) {}
    void Load(BinStream&);

    Transform mXfm;
};

class RndMesh : public RndDrawable, public RndTransformable {
public:
    class Vert {
        public:
        Vert();
        float x, y, z; // 0x0, 0x4, 0x8
        float nx, ny, nz; // 0xC, 0x10, 0x14 W component gets shadowrealmed on wii
        u16 unk_0x18, unk_0x1A, unk_0x1C, unk_0x1E;
        int unk_0x20; // ????
        float u, v; // 0x24, 0x28 WHY ARE THEY OUT HERE
        u16 unk_0x2C, unk_0x2E, unk_0x30, unk_0x32;
    };

    class Face {
        public:
        u16 idx0, idx1, idx2;
    };

    class VertVector : public std::vector<Vert, u32> {
        public:
        std::vector<Vert>::iterator begin() { return std::vector<Vert, u32>::begin(); }
        std::vector<Vert>::iterator end() { return std::vector<Vert, u32>::end(); }
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
    virtual int MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual int CollideShowing(const Segment&, float&, Plane&);
    virtual int CollidePlane(const Plane&);
    virtual void Highlight();
    virtual ~RndMesh();

    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    // TODO: figure out what RndMesh's members do
    VertVector mVerts; // 0xB0
    std::vector<Face> mFaces; // 0xBC
    ObjPtr<RndMat,ObjectDir> mMat; // 0xC4
    std::vector<u8, u16> unk_0xD0; // ???
    ObjOwnerPtr<RndMesh, ObjectDir> mOwner; // 0xD8
    ObjVector<RndBone> mBones;
    int unk_0xF0, unk_0xF4, unk_0xF8;
    RndMultiMesh* unk_0xFC; // ...why?
    std::vector<int> unk_0x100;
    int unk_0x108, unk_0x10C;
    u8 unk_0x110;
    int unk_0x114, unk_0x118;
    FileLoader* unk_0x11C;

    int NumBones() const;
    bool IsSkinned() const;
    int NumVerts() const;
    int NumFaces() const;
    void SetMat(RndMat*);
    int EstimatedSizeKb() const;
    void CopyBones(const RndMesh*);
    void CopyGeometryFromOwner();
    void PreLoadVertices(BinStream&);
    void PostLoadVertices(BinStream&);
    void RemoveInvalidBones();
    void Sync(int);
    RndMultiMesh* CreateMultiMesh();

    DECLARE_REVS

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

#endif
