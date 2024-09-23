#ifndef RNDOBJ_MULTIMESH_H
#define RNDOBJ_MULTIMESH_H
#include "math/Mtx.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Mesh.h"
#include "utl/BinStream.h"
#include "utl/TextStream.h"
#include <list>
#include <utility>

class RndMultiMesh : public RndDrawable {
public:
    struct Instance {
        Instance();
        Instance(Transform t) : mXfm(t) {}
        void LoadRev(BinStream&, int);
        void Load(BinStream&);
        Transform mXfm;
    };
    RndMultiMesh();
    OBJ_CLASSNAME(MultiMesh);
    OBJ_SET_TYPE(MultiMesh);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void DrawShowing();
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void CollideList(const Segment&, std::list<Collision>&);
    virtual ~RndMultiMesh() {InvalidateProxies();}
    virtual void Print();
    virtual void UpdateMesh(){}

    void SetMesh(RndMesh*);
    void InvalidateProxies();
    DataNode OnGetPos(const DataArray*);
    DataNode OnSetPos(const DataArray*);
    DataNode OnGetRot(const DataArray*);
    DataNode OnSetRot(const DataArray*);
    DataNode OnGetScale(const DataArray*);
    DataNode OnSetScale(const DataArray*);
    DataNode OnAddXfm(const DataArray*);
    DataNode OnAddXfms(const DataArray*);
    DataNode OnRemoveXfm(const DataArray*);
    DataNode OnNumXfms(const DataArray*);
    DataNode OnMesh(const DataArray*);
    DataNode OnMoveXfms(const DataArray*);
    DataNode OnScaleXfms(const DataArray*);
    DataNode OnSortXfms(const DataArray*);
    DataNode OnRandomXfms(const DataArray*);
    DataNode OnScrambleXfms(const DataArray*);
    DataNode OnDistribute(const DataArray*);

    RndMesh* GetMesh() const { return mMesh; }

    ObjPtr<RndMesh, class ObjectDir> mMesh; // 0x20
    std::list<RndMultiMesh::Instance> mInstances; // 0x2C

    static void Terminate();
    static std::list<std::pair<class RndMultiMeshProxy*, int> > sProxyPool;

    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS
    NEW_OBJ(RndMultiMesh)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMultiMesh)
    }
};

inline BinStream& operator>>(BinStream& bs, RndMultiMesh::Instance& i) {
    i.Load(bs);
    return bs;
}

TextStream& operator<<(TextStream& ts, const RndMultiMesh::Instance& i);

#endif
