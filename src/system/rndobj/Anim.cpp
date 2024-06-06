#include "rndobj/Anim.h"
#include "os/Debug.h"
#include "rndobj/AnimFilter.h"
#include "rndobj/Group.h"
#include "obj/DataUtl.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"

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

#pragma push
#pragma force_active on
inline TaskUnits RndAnimatable::Units() const {
    return gRateUnits[mRate];
}

inline float RndAnimatable::FramesPerUnit() {
    return gRateFpu[mRate];
}
#pragma pop

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
        float theScale = 1.0f;
        float theOffset = 0.0f;
        float theMin = 0.0f;
        float theMax = 0.0f;
        int read;
        int unused1, unused2, unused3, unused4, unused5, unused6, unused7;
        while(count-- != 0){
            bs >> read;
            switch(read){
                case 0:
                    bs >> theScale >> theOffset;
                    break;
                case 1:
                    bs >> theMin >> theMax >> theLoop;
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
        if(theScale != 1.0f || theOffset != 0.0f || (theMin != theMax)){
            const char* filt = MakeString("%s.filt", FileGetBase(Name(), 0));
            class ObjectDir* thisDir = Dir();
            RndAnimFilter* filtObj = Hmx::Object::New<RndAnimFilter>();
            if(filtObj) filtObj->SetName(filt, thisDir);
            filtObj->SetProperty("anim", DataNode(filtObj));
            filtObj->SetProperty("scale", DataNode(theScale));
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
    std::vector<ObjRef*>::const_reverse_iterator rit = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator ritEnd = Refs().rend();
    for(; rit != ritEnd; ++rit){
        Hmx::Object* owner = (*rit)->RefOwner();
        if(dynamic_cast<AnimTask*>(owner)) return true;
    }
    return false;
}

void RndAnimatable::StopAnimation(){
    std::vector<ObjRef*>::reverse_iterator rit = mRefs.rbegin();
    std::vector<ObjRef*>::reverse_iterator ritEnd = mRefs.rend();
    while(rit != ritEnd){
        AnimTask* task = dynamic_cast<AnimTask*>((*rit++)->RefOwner());
        if(task){
            delete task;
            rit = mRefs.rbegin();
            ritEnd = mRefs.rend();
        }
    }
}

Task* RndAnimatable::Animate(float blend, bool wait, float delay){
    AnimTask* task = new AnimTask(this, StartFrame(), EndFrame(), FramesPerUnit(), Loop(), blend);
    if(wait && task->mBlendTask){
        delay += task->mBlendTask->TimeUntilEnd();
    }
    TheTaskMgr.Start(task, Units(), delay);
    return task;
}

Task* RndAnimatable::Animate(float blend, bool wait, float delay, Rate rate, float start, float end, float period, float scale, Symbol type){
    float taskStart = start;
    if(type == dest) taskStart = mFrame;
    float fpu;
    if(period){
        fpu = __fabs(end - start);
        fpu = fpu / period;
    }
    else fpu = scale * gRateFpu[rate];
    AnimTask* task = new AnimTask(this, taskStart, end, fpu, loop == type, blend);
    if(wait){
        AnimTask* blendTask = task->mBlendTask;
        if(blendTask){
            delay += blendTask->TimeUntilEnd();
        }
    }
    TheTaskMgr.Start(task, gRateUnits[rate], delay);
    return task;
}

Task* RndAnimatable::Animate(float start, float end, TaskUnits units, float period, float blend){
    float fpu;
    if(period){
        fpu = __fabs(end - start);
        fpu = fpu / period;
    }
    else {
        const float fpus[3] = { 30.0f, 480.0f, 30.0f };
        fpu = fpus[units];
    }
    AnimTask* task = new AnimTask(this, start, end, fpu, false, blend);
    TheTaskMgr.Start(task, units, 0.0f);
    return task;
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

DataNode RndAnimatable::OnAnimate(DataArray* arr){
    float local_blend = 0.0f;
    float animTaskStart = StartFrame();
    float animTaskEnd = EndFrame();
    bool animTaskLoop = Loop();
    TaskUnits local_units = Units();
    float p = FramesPerUnit();
    float local_delay = 0.0f;
    const char* local_name = 0;
    bool local_wait = false;

    arr->FindData(blend, local_blend, false);
    arr->FindData(delay, local_delay, false);
    arr->FindData(units, (int&)local_units, false);
    arr->FindData(name, local_name, false);
    arr->FindData(wait, local_wait, false);

    DataArray* rangeArr = arr->FindArray(range, false);
    if(rangeArr){
        animTaskStart = rangeArr->Float(1);
        animTaskEnd = rangeArr->Float(2);
        animTaskLoop = false;
    }

    DataArray* loopArr = arr->FindArray(loop, false);
    if(loopArr){
        if(loopArr->Size() > 1) animTaskStart = loopArr->Float(1);
        else animTaskStart = StartFrame();
        if(loopArr->Size() > 2) animTaskEnd = loopArr->Float(2);
        else animTaskEnd = EndFrame();
        animTaskLoop = true;
    }

    DataArray* destArr = arr->FindArray(dest, false);
    if(destArr){
        animTaskStart = mFrame;
        animTaskEnd = destArr->Float(1);
        animTaskLoop = false;
    }

    DataArray* periodArr = arr->FindArray(period, false);
    if(periodArr){
        p = periodArr->Float(1);
        MILO_ASSERT(p, 0x1A9);
        p = __fabs((animTaskEnd - animTaskStart)) / p;
    }

    AnimTask* theTask = new AnimTask(this, animTaskStart, animTaskEnd, p, animTaskLoop, local_blend);
    if(local_name){
        MILO_ASSERT(DataThis(), 0x1B1);
        theTask->SetName(local_name, DataThis()->DataDir());
    }
    if(local_wait){
        AnimTask* blendtask = theTask->mBlendTask;
        if(blendtask){
            RndAnimatable* blendtaskanim = blendtask->mAnim;
            if(blendtaskanim->GetRate() != mRate) MILO_WARN("%s: need same rate to wait", Name());
            else local_delay = blendtask->TimeUntilEnd();
        }
    }
    TheTaskMgr.Start(theTask, local_units, local_delay);
    return DataNode(theTask);
}

DataNode RndAnimatable::OnConvertFrames(DataArray* arr){
    float f = arr->Float(2);
    bool conv = ConvertFrames(f);
    *arr->Var(2) = DataNode(f);
    return DataNode(conv);
}

BEGIN_PROPSYNCS(RndAnimatable);
    SYNC_PROP(rate, (int&)mRate);
    SYNC_PROP_MODIFY(frame, mFrame, SetFrame(mFrame, 1.0f));
END_PROPSYNCS;

AnimTask::AnimTask(RndAnimatable* anim, float start, float end, float fpu, bool loop, float blend) : 
    mAnim(this, 0), mAnimTarget(this, 0), mBlendTask(this, 0), mBlending(0), mBlendTime(0.0f), mBlendPeriod(blend), mLoop(loop) {
    MILO_ASSERT(anim, 0x1DF);
    mMin = (end < start) ? end : start;
    mMax = (start < end) ? end : start;
    if(start < end){
        mScale = fpu;
        mOffset = mMin;
    }
    else {
        mScale = -fpu;
        mOffset = mMax;
    }
    Hmx::Object* target = anim->AnimTarget();
    if(target){
        std::vector<ObjRef*>::const_reverse_iterator rit = target->Refs().rbegin();
        std::vector<ObjRef*>::const_reverse_iterator ritEnd = target->Refs().rend();
        for(; rit != ritEnd; ++rit){
            Hmx::Object* owner = (*rit)->RefOwner();
            if(owner){
                bool isananimtask = owner->ClassName() == AnimTask::StaticClassName();
                if(isananimtask){
                    mAnimTarget = owner;
                    break;
                }
            }
        }
    }
    if(mBlendPeriod != 0.0f && mBlendTask){
        mBlendTask->mBlending = true;
    }
    mAnim = anim;
    mAnimTarget = anim->AnimTarget();
    mAnim->StartAnim();
}

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

void AnimTask::Poll(float time){
    
}