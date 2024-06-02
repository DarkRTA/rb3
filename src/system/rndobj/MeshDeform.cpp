#include "rndobj/MeshDeform.h"
#include "rndobj/Mesh.h"

RndMeshDeform::VertArray::VertArray(RndMeshDeform* md) : mSize(0), mData(0), mParent(md) {

}

RndMeshDeform::VertArray::~VertArray(){
    _MemFree(mData);
}

void RndMeshDeform::VertArray::Clear(){
    SetSize(0);
}

void RndMeshDeform::VertArray::SetSize(int i){
    if(mSize != i){
        mSize = i;
        _MemFree(mData);
        mData = _MemAlloc(mSize, 0);
    }
}

RndMeshDeform::RndMeshDeform() : mMesh(this, 0), mBones(this), mVerts(this), mSkipInverse(0), mDeformed(0) {

}

RndMeshDeform::~RndMeshDeform(){

}

void RndMeshDeform::SetMesh(RndMesh* mesh){
    mMesh = mesh;
    mVerts.Clear();
}

BEGIN_HANDLERS(RndMeshDeform)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x2A1)
END_HANDLERS