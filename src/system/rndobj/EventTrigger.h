#pragma once
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/PartLauncher.h"
#include "synth/Sequence.h"
#include "obj/ObjVector.h"

class EventTrigger : public virtual Hmx::Object, public RndAnimatable {
public:
    enum TriggerOrder {
        kTriggerRandom = 0,
        kTriggerSequence = 1
    };

    enum TriggerAnim {
        kTriggerAnimNone = 0,
        kTriggerAnimStart = 1,
        kTriggerAnimEnd = 2,
        kTriggerAnimFrame = 3
    };

//     #define TRIGGER_ANIM_ENUM
// ((("kTriggerAnimNone"
//          "Do not trigger based on any Anim call")
//       ("kTriggerAnimStart"
//          "Trigger when StartAnim gets called (e.g. very start of a CamShot), will be Reset when EndAnim gets called")
//       ("kTriggerAnimEnd"
//          "Trigger when EndAnim gets called (e.g. very end of a CamShot)")
//       ("kTriggerAnimFrame"
//          "Trigger when frame crosses anim_frame (e.g. during a CamShot)")))

    class Anim {
    public:
        Anim(Hmx::Object*);

        ObjOwnerPtr<RndAnimatable> mAnim; // 0x0
        float mBlend; // 0xc
        float mDelay; // 0x10
        bool mWait; // 0x14
        bool mEnable; // 0x15
        unsigned char mRate; // 0x16 - enum?
        float mStart; // 0x18
        float mEnd; // 0x1c
        float mPeriod; // 0x20
        float mScale; // 0x24
        Symbol mType; // 0x28
    };

    class ProxyCall {
    public:
        ProxyCall(Hmx::Object*);

        ObjOwnerPtr<class ObjectDir> mProxy; // 0x0
        Symbol mCall; // 0xc
        ObjOwnerPtr<EventTrigger> mEvent; // 0x10
    };

    class HideDelay {
    public:
        HideDelay(Hmx::Object*);

        ObjOwnerPtr<RndDrawable> mHide; // 0x0
        float mDelay; // 0xc
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

    DataNode OnTrigger(DataArray*);
    static DataNode Cleanup(DataArray*);
    DataNode OnProxyCalls(DataArray*);

    ObjVector<Anim> mAnims; // 0x14
    ObjPtrList<Task> mSpawnedTasks; // 0x20
    ObjVector<ProxyCall> mProxyCalls; // 0x30
    ObjPtrList<Sequence> mSounds; // 0x3c
    ObjPtrList<RndDrawable> mShows; // 0x4c
    ObjPtrList<EventTrigger> mResetTriggers; // 0x5c
    ObjVector<HideDelay> mHideDelays; // 0x6c
    std::vector<Symbol> mTriggerEvents; // 0x78
    std::vector<Symbol> mEnableEvents; // 0x80
    std::vector<Symbol> mDisableEvents; // 0x88
    std::vector<Symbol> mWaitForEvents; // 0x90
    ObjPtr<EventTrigger> mNextLink; // 0x98
    Symbol unka4; // 0xa4 - handler?
    ObjPtrList<RndPartLauncher> mPartLaunchers; // 0xa8
    float mAnimFrame; // 0xb8
    ObjPtrList<RndDrawable> mHidden; // 0xbc
    ObjPtrList<RndDrawable> mShown; // 0xcc
    unsigned char mTriggerOrder; // 0xdc - represents the enum TriggerOrder
    unsigned char mAnimTrigger; // 0xdd
    unsigned char mLastTriggerIndex; // 0xde
    bool unkdf : 1; // 0xdf >> 7 & 1 - apparently can also be enabled? tf?
    bool mEnabled : 1; // 0xdf >> 6 & 1
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