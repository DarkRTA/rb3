#include "char/CharBonesMeshes.h"
#include "char/CharUtl.h"
#include "utl/Symbols.h"

CharBonesMeshes::CharBonesMeshes() : mMeshes(this), mDummyMesh(Hmx::Object::New<RndTransformable>()) {

}

CharBonesMeshes::~CharBonesMeshes(){
    mMeshes.clear();
    delete mDummyMesh;
}

void CharBonesMeshes::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(from != mDummyMesh){
        ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> >::iterator it = mMeshes.begin();
        ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> >::iterator itEnd = mMeshes.end();
        for(; it != itEnd; ++it){
            if(*it == from){
                *it = dynamic_cast<RndTransformable*>(to);
                if(!*it) *it = mDummyMesh;
                return;
            }
        }
    }
}

// fn_804B07F4
void CharBonesMeshes::ReallocateInternal(){
    CharBonesAlloc::ReallocateInternal();
    String str;
    // mMeshes = ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> >(this);
    mMeshes.resize(mBones.size());
    for(int i = 0; i < mMeshes.size(); i++){
        mMeshes[i] = CharUtlFindBoneTrans(mBones[i].name.Str(), Dir());
        if(!mMeshes[i]){
            if(strncmp("bone_facing", mBones[i].name.Str(), 0xB)){
                str += MakeString("%s, ", mBones[i].name);
            }
            mMeshes[i] = mDummyMesh;
        }
        
    }
    if(mMeshes.empty()) return;
    else AcquirePose();
}

// fn_804B0C60 - pose meshes
void CharBonesMeshes::PoseMeshes(){
    float angle;
    Hmx::Matrix3 m;
    m.RotateAboutY(angle);
    m.RotateAboutX(angle);
}

void CharBonesMeshes::StuffMeshes(std::list<Hmx::Object*>& oList){
    for(int i = 0; i < mMeshes.size(); i++){
        oList.push_back(mMeshes[i]);
    }
}

BEGIN_PROPSYNCS(CharBonesMeshes)
    SYNC_PROP(meshes, mMeshes)
    SYNC_SUPERCLASS(CharBonesObject)
END_PROPSYNCS