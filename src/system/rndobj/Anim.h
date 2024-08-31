#ifndef RNDOBJ_ANIM_H
#define RNDOBJ_ANIM_H
#include "obj/Object.h"
#include "obj/Task.h"
#include "obj/ObjPtr_p.h"
#include <list>

class AnimTask;

class RndAnimatable : public virtual Hmx::Object {
public:
    enum Rate {
        k30_fps = 0,
        k480_fpb = 1,
        k30_fps_ui = 2,
        k1_fpb = 3,
        k30_fps_tutorial = 4,
    };

    RndAnimatable();
    OBJ_CLASSNAME(Anim);
    OBJ_SET_TYPE(Anim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndAnimatable(){}
    virtual bool Loop(){ return 0; }
    virtual void StartAnim(){}
    virtual void EndAnim(){}
    virtual void SetFrame(float frame, float blend){ mFrame = frame; }
    virtual float StartFrame(){ return 0.0f; }
    virtual float EndFrame(){ return 0.0f; }
    virtual Hmx::Object* AnimTarget(){ return this; }
    virtual void SetKey(float){}
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const {}

    DECLARE_REVS;
    DELETE_OVERLOAD;

    DataNode OnAnimate(DataArray*);
    void StopAnimation();
    bool IsAnimating();
    Rate GetRate(){ return mRate; }
    void SetRate(Rate r){ mRate = r; }
    float GetFrame() const { return mFrame; }
    DataNode OnConvertFrames(DataArray*);

    Task* Animate(float, bool, float);
    Task* Animate(float, bool, float, Rate, float, float, float, float, Symbol);
    Task* Animate(float, float, TaskUnits, float, float);

    static TaskUnits RateToTaskUnits(Rate);
    TaskUnits Units() const;
    float FramesPerUnit();
    bool ConvertFrames(float&);

    float mFrame; // 0x8
    Rate mRate; // 0xc
};

class AnimTask : public Task {
public:
    AnimTask(RndAnimatable*, float, float, float, bool, float);
    virtual ~AnimTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(AnimTask);
    virtual void Poll(float);

    float TimeUntilEnd();
    AnimTask* BlendTask() const { return mBlendTask; }
    RndAnimatable* Anim() const { return mAnim; }

    NEW_POOL_OVERLOAD(AnimTask);
    DELETE_POOL_OVERLOAD(AnimTask);

    ObjOwnerPtr<RndAnimatable, class ObjectDir> mAnim; // 0x1c
    ObjPtr<Hmx::Object, class ObjectDir> mAnimTarget; // 0x28
    ObjPtr<AnimTask, class ObjectDir> mBlendTask; // 0x34
    bool mBlending; // 0x40
    float mBlendTime; // 0x44
    float mBlendPeriod; // 0x48
    float mMin; // 0x4c
    float mMax; // 0x50
    float mScale; // 0x54
    float mOffset; // 0x58
    bool mLoop; // 0x5c
};

#endif
