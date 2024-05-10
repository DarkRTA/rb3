#ifndef RNDOBJ_MESH_H
#define RNDOBJ_MESH_H
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "rndobj/Trans.h"
#include "types.h"

#define MAX_BONES 40

class RndMultiMesh;

class RndMesh : public RndDrawable, public RndTransformable {
public:
    class Vert {
        public:
        Vert();
        float x, y, z;
        float nx, ny, nz; // W component gets shadowrealmed on wii
    };

    class Face {
        public:
        u16 idx0, idx1, idx2;
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

    // TODO: figure out what RndMesh's members do
    std::vector<Vert, uint> mVerts; // 0xB0
    std::vector<Face> mFaces; // 0xBC
    ObjPtr<RndMat,ObjectDir> mMat; // 0xC4
    std::vector<int, u16> unk_0xD0;
    ObjOwnerPtr<RndMesh, ObjectDir> mOwner; // 0xD8
    ObjVector<Hmx::Object> mBones;
    int unk_0xF0, unk_0xF4, unk_0xF8;
    RndMultiMesh* unk_0xFC; // ...why?
    std::vector<int> unk_0x100;
    int unk_0x108, unk_0x10C;
    u8 unk_0x110;
    int unk_0x114, unk_0x118;
    FileLoader* unk_0x11C;

    int MaxBones();
    int NumBones() const;
    bool IsSkinned() const;
    int NumVerts() const;
    int NumFaces() const;
    int EstimatedSizeKb() const;
    void CopyBones(const RndMesh*);
    void CopyGeometryFromOwner();
    void PreLoadVertices(BinStream&);
    void PostLoadVertices(BinStream&);
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
};

BinStream& operator>>(BinStream&, RndMesh::Face&);

#endif
