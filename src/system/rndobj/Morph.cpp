#include "rndobj/Morph.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/Mesh.h"
#include "utl/BinStream.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/TextStream.h"

INIT_REVS(RndMorph)

RndMorph::RndMorph() : mPoses(this), mTarget(this, 0), mNormals(0), mSpline(0), mIntensity(1.0f) {

}

float RndMorph::EndFrame(){
    float end = 0;
    for(int i = 0; i < mPoses.size(); i++){
        float curLast = mPoses[i].weights.LastFrame();
        if(curLast > end){
            end = curLast;
        }
    }
    return end;
}

BEGIN_COPYS(RndMorph)
    CREATE_COPY_AS(RndMorph, f)
    MILO_ASSERT(f, 0xA8);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(f, mPoses)
    COPY_MEMBER_FROM(f, mTarget)
    COPY_MEMBER_FROM(f, mNormals)
    COPY_MEMBER_FROM(f, mSpline)
    COPY_MEMBER_FROM(f, mIntensity)
END_COPYS

TextStream& operator<<(TextStream& ts, const RndMorph::Pose& pose){
    ts << "mesh:" << pose.mesh << " weightKeys:" << pose.weights;
    return ts;
}

void RndMorph::Print(){
    TextStream& ts = TheDebug;
    ts << "   poses: " << mPoses << "\n";
    ts << "   target: " << mTarget << "\n";
    ts << "   normals: " << mNormals << "\n";
    ts << "   spline: " << mSpline << "\n";
    ts << "   intensity: " << mIntensity << "\n";
}

SAVE_OBJ(RndMorph, 0xCB);

BinStream& operator>>(BinStream& bs, RndMorph::Pose& pose){
    bs >> pose.mesh;
    if(RndMorph::gRev < 2){
        Keys<Weight, Weight> weightKeys;
        bs >> weightKeys;
        pose.weights.resize(weightKeys.size());
        Keys<Weight, Weight>::iterator it = weightKeys.begin();
        Keys<float, float>::iterator poseIt = pose.weights.begin();
        for(; it != weightKeys.end(); ++it, ++poseIt){
            Key<Weight>& curWeight = *it;
            Key<float>& curKey = *poseIt;
            curKey.frame = curWeight.frame;
            curKey.value = curWeight.value.weight;
        }
    }
    else bs >> pose.weights;
    return bs;
}

BEGIN_LOADS(RndMorph)
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    if(gRev > 3) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    bs >> mPoses >> mTarget;
    if(gRev != 0){
        bs >> mNormals;
        bs >> mSpline;
    }
    if(gRev > 2) bs >> mIntensity;
END_LOADS

BEGIN_HANDLERS(RndMorph)
    HANDLE(set_target, OnSetTarget)
    HANDLE(set_pose_weight, OnSetPoseWeight)
    HANDLE(set_pose_mesh, OnSetPoseMesh)
    HANDLE(set_intensity, OnSetIntensity)
    HANDLE_ACTION(set_num_poses, SetNumPoses(_msg->Int(2)))
    HANDLE(pose_mesh, OnPoseMesh)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x12C)
END_HANDLERS

DataNode RndMorph::OnSetIntensity(const DataArray* arr){
    SetIntensity(arr->Float(2));
    return 0;
}

DataNode RndMorph::OnSetTarget(const DataArray* arr){
    SetTarget(arr->Obj<RndMesh>(2));
    return 0;
}

DataNode RndMorph::OnSetPoseWeight(const DataArray* arr){
    Keys<float, float>& curWeights = PoseAt(arr->Int(2)).weights;
    float frame = arr->Float(3);
    float weightVal = arr->Float(4);
    Keys<float, float>::iterator it = curWeights.begin();
    for(; it != curWeights.end(); ++it){
        if(it->frame == frame){
            it->value = weightVal;
            break;
        }
    }
    if(it == curWeights.end()){
        curWeights.Add(weightVal, frame, false);
    }
    return 0;
}

DataNode RndMorph::OnPoseMesh(const DataArray* arr){
    return PoseAt(arr->Int(2)).mesh.Ptr();
}

DataNode RndMorph::OnSetPoseMesh(const DataArray* arr){
    PoseAt(arr->Int(2)).mesh = arr->Obj<RndMesh>(3);
    return 0;
}

BEGIN_PROPSYNCS(RndMorph)
    SYNC_PROP(target, mTarget)
    SYNC_PROP_SET(num_poses, NumPoses(), SetNumPoses(_val.Int()))
    SYNC_PROP(intensity, mIntensity)
    SYNC_PROP(normals, mNormals)
    SYNC_PROP(spline, mSpline)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS