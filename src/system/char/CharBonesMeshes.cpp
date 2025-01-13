#include "char/CharBonesMeshes.h"
#include "char/CharUtl.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "utl/Std.h"
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
        for(ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> >::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it){
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
#ifdef MILO_DEBUG
    ClearAndShrink(mMeshes);
#else
    mMeshes = ObjVector<ObjOwnerPtr<RndTransformable, ObjectDir> >(this); // ClearAndShrink?
#endif
    mMeshes.resize(mBones.size());
    for(int i = 0; i < mMeshes.size(); i++){
        mMeshes[i] = CharUtlFindBoneTrans(mBones[i].name.mStr, Dir());
        if(!mMeshes[i]){
            if(strncmp("bone_facing", mBones[i].name.mStr, 0xB)){
                str += MakeString("%s, ", mBones[i].name);
            }
            mMeshes[i] = mDummyMesh;
        }
        
    }
    if(mMeshes.empty()) return;
    else AcquirePose();
}

void CharBonesMeshes::AcquirePose(){
    ObjOwnerPtr<RndTransformable>* curMesh = &mMeshes[0];
    Vector3* end = (Vector3*)ScaleOffset();
    for(Vector3* p = (Vector3*)Start(); p < end; p++, curMesh++){
        *p = (*curMesh)->mLocalXfm.v;
    }
    Vector3* vEnd = (Vector3*)QuatOffset();
    for(Vector3* p = (Vector3*)ScaleOffset(); p < vEnd; p++, curMesh++){
        MakeScale((*curMesh)->mLocalXfm.m, *p);
    }
    Hmx::Quat* qEnd = (Hmx::Quat*)RotXOffset();
    for(Hmx::Quat* p = (Hmx::Quat*)QuatOffset(); p < qEnd; p++, curMesh++){
        p->Set((*curMesh)->mLocalXfm.m);
    }
    float* rotIt = (float*)RotXOffset();
    float* xEnd = (float*)RotYOffset();
    for(; rotIt < xEnd; rotIt++, curMesh++){
        *rotIt = GetXAngle((*curMesh)->mLocalXfm.m);
    }
    float* yEnd = (float*)RotZOffset();
    for(; rotIt < yEnd; rotIt++, curMesh++){
        *rotIt = GetYAngle((*curMesh)->mLocalXfm.m);
    }
    float* zEnd = (float*)EndOffset();
    for(; rotIt < zEnd; rotIt++, curMesh++){
        *rotIt = GetZAngle((*curMesh)->mLocalXfm.m);
    }
}

// fn_804B0C60 - pose meshes
void CharBonesMeshes::PoseMeshes(){
    ObjOwnerPtr<RndTransformable>* curMesh = &mMeshes[0];
    Vector3* end = (Vector3*)ScaleOffset();
    for(Vector3* p = (Vector3*)Start(); p < end; p++, curMesh++){
        (*curMesh)->SetLocalPos(*p);
    }
    if(mQuatCount < mMeshes.size()){
        curMesh = &mMeshes[mQuatCount];
        Hmx::Quat* qEnd = (Hmx::Quat*)RotXOffset();
        for(Hmx::Quat* p = (Hmx::Quat*)QuatOffset(); p < qEnd; p++, curMesh++){
            Normalize(*p, *p);
            MakeRotMatrix(*p, (*curMesh)->DirtyLocalXfm().m);
        }
        float* rotIt = (float*)RotXOffset();
        float* xEnd = (float*)RotYOffset();
        for(; rotIt < xEnd; rotIt++, curMesh++){
            (*curMesh)->DirtyLocalXfm().m.RotateAboutX(*rotIt);
        }
        float* yEnd = (float*)RotZOffset();
        for(; rotIt < yEnd; rotIt++, curMesh++){
            (*curMesh)->DirtyLocalXfm().m.RotateAboutY(*rotIt);
        }
        float* zEnd = (float*)EndOffset();
        for(; rotIt < zEnd; rotIt++, curMesh++){
            (*curMesh)->DirtyLocalXfm().m.RotateAboutZ(*rotIt);
        }
    }
    if(mScaleCount < mMeshes.size()){
        curMesh = &mMeshes[mScaleCount];
        Vector3* vEnd = (Vector3*)QuatOffset();
        for(Vector3* p = (Vector3*)ScaleOffset(); p < vEnd; p++, curMesh++){
            Transform& xfm = (*curMesh)->DirtyLocalXfm();
            Vector3 scale;
            MakeScale(xfm.m, scale);
            xfm.m.x *= p->x / scale.x;
            xfm.m.y *= p->y / scale.y;
            xfm.m.z *= p->z / scale.z;
        }
    }
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