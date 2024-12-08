#pragma once
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/PartLauncher.h"
#include "synth/Sequence.h"
#include "obj/ObjVector.h"

/**
 * @brief An object that can trigger based on an in-game event.
 * Original _objects description:
 * "Triggers animations, sfx, and responses to game events"
 */
class EventTrigger : public virtual Hmx::Object, public RndAnimatable {
public:
    enum TriggerOrder {
        kTriggerRandom = 0,
        kTriggerSequence = 1
    };

    enum TriggerAnim {
        /** "Do not trigger based on any Anim call" */
        kTriggerAnimNone = 0,
        /** "Trigger when StartAnim gets called (e.g. very start of a CamShot), will be Reset when EndAnim gets called" */
        kTriggerAnimStart = 1,
        /** "Trigger when EndAnim gets called (e.g. very end of a CamShot)" */
        kTriggerAnimEnd = 2,
        /** "Trigger when frame crosses anim_frame (e.g. during a CamShot)" */
        kTriggerAnimFrame = 3
    };

    class Anim {
    public:
        Anim(Hmx::Object*);

        ObjOwnerPtr<RndAnimatable> mAnim; // 0x0
        float mBlend; // 0xc
        float mDelay; // 0x10
        bool mWait; // 0x14
        /** "Enable animation filtering" */
        bool mEnable; // 0x15
        /** "Rate to animate" */
        unsigned char mRate; // 0x16 - enum?
        /** "Start frame of animation" */
        float mStart; // 0x18
        /** "End frame of animation" */
        float mEnd; // 0x1c
        /** "Period of animation if non-zero" */
        float mPeriod; // 0x20
        /** "Scale of animation" */
        float mScale; // 0x24
        /** "Type of animation" */
        Symbol mType; // 0x28
    };

    class ProxyCall {
    public:
        ProxyCall(Hmx::Object*);

        ObjOwnerPtr<ObjectDir> mProxy; // 0x0
        Symbol mCall; // 0xc
        /** "event trigger to fire" */
        ObjOwnerPtr<EventTrigger> mEvent; // 0x10
    };

    class HideDelay {
    public:
        HideDelay(Hmx::Object*);

        /** "object to hide" */
        ObjOwnerPtr<RndDrawable> mHide; // 0x0
        /** "seconds to delay hiding" */
        float mDelay; // 0xc
        /** "rate by which to measure delay" */
        int mRate; // 0x10
    };

    EventTrigger();
    OBJ_CLASSNAME(EventTrigger);
    OBJ_SET_TYPE(EventTrigger);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~EventTrigger(){}
    virtual bool Loop();
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float, float);
    virtual void SetName(const char*, ObjectDir*);
    /** "Tries to trigger this EventTrigger, won't work if [enabled] is false" */
    virtual void Trigger(); // 0x50
    virtual void BasicReset();
    virtual DataArray* SupportedEvents();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void CheckAnims(){}

    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(EventTrigger)
    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(EventTrigger)
    }
    void SetEnabled(bool e){ mEnabled = e; }

    void RegisterEvents();
    void UnregisterEvents();
    void CleanupHideShow();
    void CleanupEventCase(std::vector<Symbol>&);
    void ConvertParticleTriggerType();
    void SetNextLink(EventTrigger*);
    void LoadOldAnim(BinStream&, RndAnimatable*);
    void LoadOldEvent(BinStream&, Hmx::Object*, const char*, ObjectDir*);
    void TriggerSelf();
    bool HasTriggerEvents() const { return !mTriggerEvents.empty(); }

    DataNode OnTrigger(DataArray*);
    static DataNode Cleanup(DataArray*);
    DataNode OnProxyCalls(DataArray*);

    ObjVector<Anim> mAnims; // 0x14
    ObjPtrList<Task> mSpawnedTasks; // 0x20
    ObjVector<ProxyCall> mProxyCalls; // 0x30
    ObjPtrList<Sequence> mSounds; // 0x3c
    /** "objects to show" */
    ObjPtrList<RndDrawable> mShows; // 0x4c
    /** "these triggers will be reset (i.e. hide its shows, etc.) when this trigger fires" */
    ObjPtrList<EventTrigger> mResetTriggers; // 0x5c
    ObjVector<HideDelay> mHideDelays; // 0x6c
    /** "Events which enable this trigger" */
    std::vector<Symbol> mTriggerEvents; // 0x78
    /** "event which enable this event trigger" */
    std::vector<Symbol> mEnableEvents; // 0x80
    /** "event which disable this event trigger" */
    std::vector<Symbol> mDisableEvents; // 0x88
    /** "When events are triggered, arm them, and delay fire until this handler is called" */
    std::vector<Symbol> mWaitForEvents; // 0x90
    ObjPtr<EventTrigger> mNextLink; // 0x98
    Symbol mHandler; // 0xa4
    ObjPtrList<RndPartLauncher> mPartLaunchers; // 0xa8
    /** "If anim_trigger is kAnimTrigger, then this is the frame we will trigger ourselves on" */
    float mAnimFrame; // 0xb8
    ObjPtrList<RndDrawable> mHidden; // 0xbc
    ObjPtrList<RndDrawable> mShown; // 0xcc
    /** "Order of triggering next_link" */
    unsigned char mTriggerOrder; // 0xdc
    /** "Sets whether and how this will trigger itself based on Anim calls to it" */
    unsigned char mAnimTrigger; // 0xdd
    unsigned char mLastTriggerIndex; // 0xde
    bool unkdf : 1; // 0xdf >> 7 & 1 - apparently can also be enabled? tf?
    /** "State of the event trigger. If TRUE, this EventTrigger can be triggered, if FALSE the EventTrigger can't be triggered. 
     *  This value is not saved, so feel free to change it for debugging" */
    bool mEnabled : 1; // 0xdf >> 6 & 1
    /** "Initial state of the EventTrigger. If TRUE, the EventTrigger will work initially,
     *  if FALSE the EventTrigger will not work until an enable_event happens." */
    bool mEnabledAtStart : 1; // 0xdf >> 5 & 1
    bool mWaiting : 1; // 0xdf >> 4 & 1
    bool mTriggered : 1; // 0xdf >> 3 & 1
};

BinStream& operator>>(BinStream&, EventTrigger::Anim&);
BinStream& operator>>(BinStream&, EventTrigger::ProxyCall&);
inline BinStream& operator>>(BinStream& bs, EventTrigger::HideDelay& hd){
    bs >> hd.mHide >> hd.mDelay >> hd.mRate;
    return bs;
}