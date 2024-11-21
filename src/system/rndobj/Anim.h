#pragma once
#include "obj/Object.h"
#include "obj/Task.h"
#include "obj/ObjPtr_p.h"
#include <list>

class AnimTask;

/**
* @brief: An object that can be animated.
* Original _objects description:
* "Base class for animatable objects. Anim objects change
* their state or other objects."
*/
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
    /** Determine whether or not this animation should loop. */
    virtual bool Loop(){ return false; }
    /** Start the animation. */
    virtual void StartAnim(){}
    /** End the animation. */
    virtual void EndAnim(){}
    virtual void SetFrame(float frame, float blend){ mFrame = frame; }
    /** Get this animatable's first frame. */
    virtual float StartFrame(){ return 0; }
    /** Get this animatable's last frame. */
    virtual float EndFrame(){ return 0; }
    virtual Hmx::Object* AnimTarget(){ return this; }
    virtual void SetKey(float frame){}
    /** Get the list of this Object's children that are animatable. */
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const {}

    DECLARE_REVS;
    DELETE_OVERLOAD;

    /** Determine if this animatable has any active tasks associated with it. */
    bool IsAnimating();
    /** Kill any active tasks associated with this animatable. */
    void StopAnimation();
    /** Create a new task to animate this.
     * @param [in] blend The animatable's desired blend.
     * @param [in] wait If true, wait until blending finishes before animating.
     * @param [in] delay How long to wait before the task should begin.
     * @returns The newly created task.
     */
    Task* Animate(float blend, bool wait, float delay);
    /** Create a new task to animate this.
     * @param [in] blend The animatable's desired blend.
     * @param [in] wait If true, wait until blending finishes before animating.
     * @param [in] delay How long to wait before the task should begin.
     * @param [in] rate The rate to animate.
     * @param [in] start The first frame to animate.
     * @param [in] end The last frame to animate.
     * @param [in] period Alternative to scale, overridden period of animation.
     * @param [in] scale Multiplier to speed of animation.
     * @param [in] type How to treat the frame outside of start and end (range, loop, shuttle)
     * @returns The newly created task.
     */
    Task* Animate(float blend, bool wait, float delay, Rate rate, float start, float end, float period, float scale, Symbol type);
    /** Create a new task to animate this.
     * @param [in] start The first frame to animate.
     * @param [in] end The last frame to animate.
     * @param [in] units The rate at which this Task should run.
     * @param [in] period Alternative to scale, overridden period of animation.
     * @param [in] blend The animatable's desired blend.
     * @returns The newly created task.
     */
    Task* Animate(float start, float end, TaskUnits units, float period, float blend);
    TaskUnits Units() const;
    float FramesPerUnit();
    bool ConvertFrames(float& frames);

    /** Create a new AnimTask using the configuration in the supplied DataArray.
     * @returns A DataNode housing the newly created task.
     */
    DataNode OnAnimate(DataArray*);
    DataNode OnConvertFrames(DataArray*);

    // weak getters and setters
    Rate GetRate(){ return mRate; }
    void SetRate(Rate r){ mRate = r; }
    float GetFrame() const { return mFrame; }

    static TaskUnits RateToTaskUnits(Rate);

    /** "Frame of animation". It ranges from 0 to what EndFrame() returns. */
    float mFrame; // 0x8
    /** "Rate to animate" */
    Rate mRate; // 0xc
};

/** A task meant for animating. */
class AnimTask : public Task {
public:
    AnimTask(RndAnimatable* anim, float start, float end, float fpu, bool loop, float blend);
    virtual ~AnimTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(AnimTask);
    virtual void Poll(float);

    float TimeUntilEnd();
    AnimTask* BlendTask() const { return mBlendTask; }
    RndAnimatable* Anim() const { return mAnim; }

    NEW_POOL_OVERLOAD(AnimTask);
    DELETE_POOL_OVERLOAD(AnimTask);

    /** The animatable this task should be animating. */
    ObjOwnerPtr<RndAnimatable> mAnim; // 0x1c
    ObjPtr<Hmx::Object> mAnimTarget; // 0x28
    /** The anim task to blend into. */
    ObjPtr<AnimTask> mBlendTask; // 0x34
    /** Whether or not this animation should blend into another. */
    bool mBlending; // 0x40
    /** The time it takes to blend into mBlendTask. */
    float mBlendTime; // 0x44
    float mBlendPeriod; // 0x48
    /** Start animation frame. */
    float mMin; // 0x4c
    /** End animation frame. */
    float mMax; // 0x50
    /** Multiplier to speed of animation. */
    float mScale; // 0x54
    /** "Amount to offset frame for animation" */
    float mOffset; // 0x58
    /** Whether or not the animation should loop. */
    bool mLoop; // 0x5c
};