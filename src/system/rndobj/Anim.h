#ifndef RNDOBJ_ANIM_H
#define RNDOBJ_ANIM_H
#include "obj/Object.h"
#include "obj/Task.h"
#include "obj/ObjPtr_p.h"
#include <list>

enum TaskUnits {
    kTaskSeconds = 0,
    kTaskBeats = 1,
    kTaskUISeconds = 2,
    kTaskTutorialSeconds = 3,
    kTaskNumUnits = 4,
};

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
    virtual void SetFrame(float, float); // weak
    virtual float StartFrame(){ return 0.0f; }
    virtual float EndFrame(){ return 0.0f; }
    virtual Hmx::Object* AnimTarget(){ return this; }
    virtual void SetKey(float){}
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const {}

    DELETE_OVERLOAD;

    DataNode OnAnimate(DataArray*);
    void StopAnimation();
    bool IsAnimating();
    DataNode OnConvertFrames(DataArray*);

    void Animate(float, bool, float);
    void Animate(float, float, TaskUnits, float, float);

    static TaskUnits RateToTaskUnits(Rate);
    int Units() const;
    float FramesPerUnit();
    bool ConvertFrames(float&);

    float mFrame;
    Rate mRate;
};

class AnimTask : public Task {
public:
    AnimTask(RndAnimatable*, float, float, float, bool, float);
    virtual ~AnimTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(AnimTask);
    virtual void Poll(float);

    float TimeUntilEnd();

    void* operator new(size_t s){
        return _PoolAlloc(s, sizeof(AnimTask), FastPool);
    }

    void operator delete(void* v){
        _PoolFree(sizeof(AnimTask), FastPool, v);
    }

    ObjOwnerPtr<RndAnimatable, class ObjectDir> mAnim;
    ObjPtr<Hmx::Object, class ObjectDir> mAnimTarget;
    ObjPtr<AnimTask, class ObjectDir> mBlendTask;
    bool mBlending;
    float mBlendTime;
    float mBlendPeriod;
    float mMin;
    float mMax;
    float mScale;
    float mOffset;
    bool mLoop;
};

#endif
