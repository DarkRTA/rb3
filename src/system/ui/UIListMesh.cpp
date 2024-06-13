#include "ui/UIListMesh.h"
#include "utl/Symbols.h"

INIT_REVS(UIListMesh)

UIListMesh::UIListMesh() : mMesh(this, 0), mDefaultMat(this, 0) {

}

RndMat* UIListMesh::DefaultMat() const { return mDefaultMat; }

UIListSlotElement* UIListMesh::CreateElement(UIList* uilist){
    MILO_ASSERT(mMesh, 0x5B);
    return new UIListMeshElement(this, 0);
}

RndTransformable* UIListMesh::RootTrans(){ return mMesh; }

SAVE_OBJ(UIListMesh, 0x8F)

BEGIN_LOADS(UIListMesh)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    LOAD_SUPERCLASS(UIListSlot)
    bs >> mMesh >> mDefaultMat;
END_LOADS

BEGIN_COPYS(UIListMesh)
    COPY_SUPERCLASS(UIListSlot)
    CREATE_COPY_AS(UIListMesh, m)
    MILO_ASSERT(m, 0x9F);
    COPY_MEMBER_FROM(m, mMesh)
    COPY_MEMBER_FROM(m, mDefaultMat)
END_COPYS

BEGIN_HANDLERS(UIListMesh)
    HANDLE_SUPERCLASS(UIListSlot)
    HANDLE_CHECK(0xAF)
END_HANDLERS

BEGIN_PROPSYNCS(UIListMesh)
    SYNC_PROP(mesh, mMesh)
    SYNC_PROP(default_mat, mDefaultMat)
    SYNC_SUPERCLASS(UIListSlot)
END_PROPSYNCS