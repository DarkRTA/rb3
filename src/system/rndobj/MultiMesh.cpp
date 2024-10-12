#include "rndobj/MultiMesh.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMeshProxy.h"
#include "rndobj/Utl.h"
#include "types.h"
#include "utl/BinStream.h"
#include "utl/Symbols.h"
#include "utl/TextStream.h"
#include <list>

INIT_REVS(RndMultiMesh)
std::list<std::pair<RndMultiMeshProxy*, int> > RndMultiMesh::sProxyPool;

void RndMultiMesh::Terminate() {
    for (std::list<std::pair<RndMultiMeshProxy*, int> >::iterator it = sProxyPool.begin(); it != sProxyPool.end(); it++)
        delete it->first;
}

BEGIN_COPYS(RndMultiMesh)
    CREATE_COPY_AS(RndMultiMesh, f)
    MILO_ASSERT(f, 38);
    Hmx::Object::Copy(o, ty);
    RndDrawable::Copy(o, ty);
    if (ty != kCopyFromMax)
        mMesh = f->mMesh;
    mInstances = f->mInstances; // uh oh this is broken
    UpdateMesh();
END_COPYS

void RndMultiMesh::Print() {
    TextStream& ts = TheDebug;
    ts << "   mesh: " << mMesh << "\n";
    ts << "   instances: " << mInstances << "\n";
}

RndMultiMesh::Instance::Instance(){
    mXfm.Reset();
}

void RndMultiMesh::Instance::LoadRev(BinStream& bs, int rev) {
    bs >> mXfm;
}

void RndMultiMesh::Instance::Load(BinStream& bs) { LoadRev(bs, RndMultiMesh::gRev); }

SAVE_OBJ(RndMultiMesh, 0x66)

BEGIN_LOADS(RndMultiMesh)
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    if (gRev != 0) Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mMesh;
    if (gRev < 2) {
        std::list<Transform> dump;
        bs >> dump;
        return;
    }
    bs >> mInstances;
    if (gRev < 4) {
        u8 dump; bs >> dump;
    }
END_LOADS

RndMultiMesh::RndMultiMesh() : mMesh(this, 0) {
    unk9p4 = 0;
}

void RndMultiMesh::SetMesh(RndMesh* mesh){
    mMesh = mesh;
    UpdateMesh();
}

// for whatever reason this isn't inlined
BEGIN_HANDLERS(RndMultiMesh)
    HANDLE(move_xfms, OnMoveXfms)
    HANDLE(scale_xfms, OnScaleXfms)
    HANDLE(sort_xfms, OnSortXfms)
    HANDLE(random_xfms, OnRandomXfms)
    HANDLE(scramble_xfms, OnScrambleXfms)
    HANDLE(distribute, OnDistribute)
    HANDLE(get_pos, OnGetPos)
    HANDLE(set_pos, OnSetPos)
    HANDLE(get_rot, OnGetRot)
    HANDLE(set_rot, OnSetRot)
    HANDLE(get_scale, OnGetScale)
    HANDLE(set_scale, OnSetScale)
    HANDLE(mesh, OnMesh)
    HANDLE(add_xfm, OnAddXfm)
    HANDLE(add_xfms, OnAddXfms)
    HANDLE(remove_xfm, OnRemoveXfm)
    HANDLE(num_xfms, OnNumXfms)
    HANDLE_ACTION(set_mesh, SetMesh(_msg->Obj<RndMesh>(2)))
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x196)
END_HANDLERS

DataNode RndMultiMesh::OnSetPos(const DataArray* da) {
    RndMultiMesh::Instance* inst;
    std::list<RndMultiMesh::Instance>::iterator it = mInstances.begin();
    for (int i = da->Int(2); i != 0; i--) {
        inst = &(*it);
        it++;
    }
    float nu_z = da->Float(5);
    float nu_y = da->Float(4);
    float nu_x = da->Float(3);
    inst->mXfm.v.x = nu_x; inst->mXfm.v.y = nu_y; inst->mXfm.v.z = nu_z;
    return DataNode();
}

DataNode RndMultiMesh::OnNumXfms(const DataArray*) {
    return DataNode(int(mInstances.size()));
}

DataNode RndMultiMesh::OnMesh(const DataArray*) { return DataNode(mMesh); }

DataNode RndMultiMesh::OnMoveXfms(const DataArray* da) {
    MoveXfms(this, Vector3(da->Float(2), da->Float(3), da->Float(4)));
    return DataNode();
}

DataNode RndMultiMesh::OnDistribute(const DataArray* da) {
    DistributeXfms(this, da->Int(2), da->Float(3));
    return DataNode();
}

BEGIN_PROPSYNCS(RndMultiMesh)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS

TextStream& operator<<(TextStream& ts, const RndMultiMesh::Instance& i) {
    ts << i.mXfm << "\n";
    return ts;
}
