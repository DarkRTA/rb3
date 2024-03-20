#include "rndobj/MultiMesh.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

RndMultiMesh::Instance::Instance(){
    mXfm.Reset();
}

SAVE_OBJ(RndMultiMesh, 0x66)

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
    if(_warn) TheDebugNotifier << MakeString("%s(%d): %s unhandled msg: %s", __FILE__, 0x196, PathName(this), sym);
END_HANDLERS

BEGIN_PROPSYNCS(RndMultiMesh)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
