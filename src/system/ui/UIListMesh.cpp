#include "ui/UIListMesh.h"

UIListMesh::UIListMesh() : mMesh(this, 0), mDefaultMat(this, 0) {

}

RndMat* UIListMesh::DefaultMat() const { return mDefaultMat; }

UIListSlotElement* UIListMesh::CreateElement(UIList* uilist){
    MILO_ASSERT(mMesh, 0x5B);
    return new UIListMeshElement(this, 0);
}

RndTransformable* UIListMesh::RootTrans(){ return mMesh; }