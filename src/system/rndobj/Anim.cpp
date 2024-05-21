#include "rndobj/Anim.h"
#include "os/Debug.h"
#include "rndobj/AnimFilter.h"
#include "rndobj/Group.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

INIT_REVS(RndAnimatable)

static TaskUnits gRateUnits[5] = {
    kTaskSeconds,
    kTaskBeats,
    kTaskUISeconds,
    kTaskBeats,
    kTaskTutorialSeconds
};
static float gRateFpu[5] = {30.0f, 480.0f, 30.0f, 1.0f, 30.0f};

TaskUnits RndAnimatable::RateToTaskUnits(Rate myRate){
    return gRateUnits[myRate];
}

int RndAnimatable::Units() const {
    return gRateUnits[mRate];
}

float RndAnimatable::FramesPerUnit() {
    return gRateFpu[mRate];
}

bool RndAnimatable::ConvertFrames(float& f){
    f /= FramesPerUnit();
    return (Units() != 1);
}

RndAnimatable::RndAnimatable() : mFrame(0.0f), mRate(k30_fps) {
    
}

void RndAnimatable::Save(BinStream&){
    MILO_ASSERT(0, 0x7A);
}

BEGIN_LOADS(RndAnimatable)
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    if(gRev > 1) bs >> mFrame;
    if(gRev > 3){
        bs >> (int&)mRate;
    }
    else if(gRev > 2){
        unsigned char uc;
        bs >> uc;
        mRate = (Rate)(uc == 0);
    }
    if(gRev < 1){
        int count;
        bs >> count;
        bool theLoop = false;
        float theScale = 0.0f;
        float theOffset = 0.0f;
        float theMin = 0.0f;
        float theMax = 1.0f;
        int unused1, unused2, unused3, unused4, unused5, unused6, unused7;
        while(count-- != 0){
            int read;
            bs >> read;
            switch(read){
                case 0:
                    bs >> theMax >> theMin;
                    break;
                case 1:
                    bs >> theOffset >> theScale >> theLoop;
                    break;
                case 2:
                    bs >> unused1 >> unused2;
                    break;
                case 3:
                    bs >> unused3 >> unused4;
                    break;
                case 4:
                    bs >> unused5 >> unused6 >> unused7;
                    break;
                default: break;
            }
        }
        if(theMax != 1.0f || theMin != 0.0f || (theOffset != theScale)){
            const char* filt = MakeString("%s.filt", FileGetBase(Name(), 0));
            class ObjectDir* thisDir = mDir;
            RndAnimFilter* filtObj = Hmx::Object::New<RndAnimFilter>();
            if(filtObj) filtObj->SetName(filt, thisDir);
            filtObj->SetProperty("anim", DataNode(filtObj));
            filtObj->SetProperty("scale", DataNode(theMax));
            filtObj->SetProperty("offset", DataNode(theOffset));
            filtObj->SetProperty("min", DataNode(theMin));
            filtObj->SetProperty("max", DataNode(theMax));
            filtObj->SetProperty("loop", DataNode(theLoop));
        }
        ObjPtrList<RndAnimatable, class ObjectDir> animList(this, kObjListNoNull);
        bs >> animList;
        RndGroup* theGroup = dynamic_cast<RndGroup*>(this);
        for(ObjPtrList<RndAnimatable, class ObjectDir>::iterator it = animList.begin(); it != animList.end(); ++it){
            if(theGroup) theGroup->AddObject(*it, 0);
            else MILO_WARN("%s not in group", (*it)->Name());
        }
    }
END_LOADS

void RndAnimatable::Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){
    const RndAnimatable* c = dynamic_cast<const RndAnimatable*>(o);
    if(c){
        mFrame = c->mFrame;
        mRate = c->mRate;
    }
}

bool RndAnimatable::IsAnimating(){
    for(std::vector<ObjRef*>::reverse_iterator it = mRefs.rbegin(); it != mRefs.rend(); it++){
        Hmx::Object* owner = (*it)->RefOwner();
        if(dynamic_cast<AnimTask*>(owner)) return true;
    }
    return false;
}

void RndAnimatable::StopAnimation(){
    for(std::vector<ObjRef*>::reverse_iterator it = mRefs.rbegin(); it != mRefs.rend(); it++){
        AnimTask* task = dynamic_cast<AnimTask*>((*it)->RefOwner());
        if(task) delete task;
    }
}

BEGIN_HANDLERS(RndAnimatable);
    HANDLE_ACTION(set_frame, SetFrame(_msg->Float(2), 1.0f));
    HANDLE_EXPR(frame, mFrame);
    HANDLE_ACTION(set_key, SetKey(_msg->Float(2)));
    HANDLE_EXPR(end_frame, EndFrame());
    HANDLE_EXPR(start_frame, StartFrame());
    HANDLE(animate, OnAnimate);
    HANDLE_ACTION(stop_animation, StopAnimation());
    HANDLE_EXPR(is_animating, IsAnimating());
    HANDLE(convert_frames, OnConvertFrames);
    HANDLE_CHECK(0x16C);
END_HANDLERS;

DataNode RndAnimatable::OnConvertFrames(DataArray* arr){
    float f = arr->Float(2);
    bool conv = ConvertFrames(f);
    *arr->Var(2) = DataNode(f);
    return DataNode(conv);
}

BEGIN_PROPSYNCS(RndAnimatable);
    SYNC_PROP(rate, (int&)mRate);
    SYNC_PROP_ACTION(frame, mFrame, kPropGet|kPropSize, SetFrame(mFrame, 1.0f));
END_PROPSYNCS;

AnimTask::AnimTask(RndAnimatable* anim, float f1, float f2, float f3, bool b4, float f5) : 
    mAnim(this, 0), mAnimTarget(this, 0), mBlendTask(this, 0), mBlending(0), mBlendTime(0.0f), mBlendPeriod(f5), mLoop(b4) {
    MILO_ASSERT(anim, 0x1DF);
    mMin = (f2 < f1) ? f2 : f1;
    mMax = (f1 < f2) ? f2 : f1;
    if(f1 < f2){
        mScale = f3;
        mOffset = mMin;
    }
    else {
        mScale = -f3;
        mOffset = mMax;
    }
    Hmx::Object* target = anim->AnimTarget();
}

// float mBlendTime;
//     float mBlendPeriod;
//     float mMin;
//     float mMax;
//     float mScale;
//     float mOffset;
//     bool mLoop;

// AnimTask * __thiscall
// AnimTask::AnimTask(AnimTask *this,RndAnimatable *param_1,float param_2,float param_3,float param_ 4,
//                   bool param_5,float param_6)

// {
//   int iVar1;
//   uint uVar2;
//   Object *this_00;
//   char *pcVar3;
//   int iVar4;
//   int *this_01;
//   int iVar5;
//   int *this_02;
//   Object **ppOVar6;
//   Object *this_03;
//   int iVar7;

//   iVar4 = (**(code **)(*(int *)(param_1 + 4) + 0x40))(param_1);
//   if (iVar4 != 0) {
//     iVar7 = *(int *)(iVar4 + 0x14);
//     for (iVar4 = *(int *)(iVar4 + 0x14) + (uint)*(ushort *)(iVar4 + 0x18) * 4; iVar4 != iVar7;
//         iVar4 = iVar4 + -4) {
//       this_01 = (int *)(**(code **)(**(int **)(iVar4 + -4) + 0xc))();
//       uVar2 = -((int)(-(int)this_01 | (uint)this_01) >> 0x1f);
//       if (uVar2 != 0) {
//         if (@GUARD@StaticClassName__8AnimTaskFv@name == '\0') {
//           Symbol::Symbol((Symbol *)&@LOCAL@StaticClassName__8AnimTaskFv@name,
//                          @STRING@StaticClassName__8AnimTaskFv);
//           @GUARD@StaticClassName__8AnimTaskFv@name = '\x01';
//         }
//         iVar1 = @LOCAL@StaticClassName__8AnimTaskFv@name;
//         iVar5 = (**(code **)(*this_01 + 0x18))(this_01);
//         uVar2 = countLeadingZeros(iVar1 - iVar5);
//         uVar2 = uVar2 >> 5;
//       }
//       if (uVar2 != 0) {
//         this_02 = *(int **)(this + 0x3c);
//         if (this_01 != this_02) {
//           if (this_02 != (int *)0x0) {
//             Hmx::Object::Release((Object *)this_02,(ObjRef *)(this + 0x34));
//           }
//           *(int **)(this + 0x3c) = this_01;
//           if (this_01 != (int *)0x0) {
//             Hmx::Object::AddRef((Object *)this_01,(ObjRef *)(this + 0x34));
//           }
//         }
//         break;
//       }
//     }
//   }
//   if ((*(float *)(this + 0x48) != 0.0) && (*(int *)(this + 0x3c) != 0)) {
//     *(undefined *)(*(int *)(this + 0x3c) + 0x40) = 1;
//   }
//   ppOVar6 = *(Object ***)(this + 0x24);
//   if ((Object **)param_1 != ppOVar6) {
//     if (ppOVar6 != (Object **)0x0) {
//       Hmx::Object::Release(*ppOVar6,*(ObjRef **)(this + 0x20));
//     }
//     *(RndAnimatable **)(this + 0x24) = param_1;
//     if (param_1 != (RndAnimatable *)0x0) {
//       Hmx::Object::AddRef(*(Object **)param_1,*(ObjRef **)(this + 0x20));
//     }
//   }
//   this_03 = (Object *)(**(code **)(*(int *)(param_1 + 4) + 0x40))(param_1);
//   this_00 = *(Object **)(this + 0x30);
//   if (this_03 != this_00) {
//     if (this_00 != (Object *)0x0) {
//       Hmx::Object::Release(this_00,(ObjRef *)(this + 0x28));
//     }
//     *(Object **)(this + 0x30) = this_03;
//     if (this_03 != (Object *)0x0) {
//       Hmx::Object::AddRef(this_03,(ObjRef *)(this + 0x28));
//     }
//   }
//   if (*(int *)(this + 0x24) == 0) {
//     pcVar3 = ::MakeString(kAssertStr,
//                           @STRING@__rf__39ObjOwnerPtr<13RndAnimatable,9ObjectDir>CFv_80C17850,0xab ,
//                           @STRING@__rf__39ObjOwnerPtr<13RndAnimatable,9ObjectDir>CFv@0_80C17848);
//     Debug::Fail((Debug *)TheDebug,pcVar3);
//   }
//   (**(code **)(*(int *)(*(int *)(this + 0x24) + 4) + 0x2c))();
//   return this;
// }

float AnimTask::TimeUntilEnd(){
    float time;
    if(mScale > 0.0f){
        float fpu = mAnim->FramesPerUnit();
        time = (mMax - mAnim->mFrame) / fpu;
    }
    else {
        float fpu = mAnim->FramesPerUnit();
        time = (mAnim->mFrame - mMin) / fpu;
    }
    return time;
}

AnimTask::~AnimTask(){
    AnimTask* blendPtr = mBlendTask.Ptr();
    delete blendPtr;
}

void AnimTask::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(to == 0){
        RndAnimatable* animPtr = mAnim.Ptr();
        if(from == animPtr){
            AnimTask* taskPtr = mBlendTask.Ptr();
            if(taskPtr && (taskPtr->mAnim.Ptr() == animPtr)){
                mBlendTask = 0;
            }
            delete this;
        }
    }
}