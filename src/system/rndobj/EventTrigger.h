#ifndef RNDOBJ_EVENTTRIGGER_H
#define RNDOBJ_EVENTTRIGGER_H
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/PartLauncher.h"
#include "synth/Sequence.h"
#include "obj/ObjVector.h"

class EventTrigger : public virtual Hmx::Object, public RndAnimatable {
public:

    class Anim {
    public:
        Anim(Hmx::Object*);

        ObjOwnerPtr<RndAnimatable, class ObjectDir> mAnim; // 0x0
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

        ObjOwnerPtr<class ObjectDir, class ObjectDir> mProxy; // 0x0
        Symbol mCall; // 0xc
        ObjOwnerPtr<EventTrigger, class ObjectDir> mEvent; // 0x10
    };

    class HideDelay {
    public:
        HideDelay(Hmx::Object*);

        ObjOwnerPtr<RndDrawable, class ObjectDir> mHide; // 0x0
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
    virtual void SetName(const char*, class ObjectDir*);
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

    void RegisterEvents();
    void UnregisterEvents();
    void CleanupHideShow();
    void CleanupEventCase(std::vector<Symbol>&);
    void ConvertParticleTriggerType();
    void SetNextLink(EventTrigger*);

    DataNode OnTrigger(DataArray*);
    DataNode Cleanup(DataArray*);
    DataNode OnProxyCalls(DataArray*);

    ObjVector<Anim> mAnims; // 0x14
    ObjPtrList<Task, class ObjectDir> mSpawnedTasks; // 0x20
    ObjVector<ProxyCall> mProxyCalls; // 0x30
    ObjPtrList<Sequence, class ObjectDir> mSounds; // 0x3c
    ObjPtrList<RndDrawable, class ObjectDir> mShows; // 0x4c
    ObjPtrList<EventTrigger, class ObjectDir> mResetTriggers; // 0x5c
    ObjVector<HideDelay> mHideDelays; // 0x6c
    std::vector<Symbol> mTriggerEvents; // 0x78
    std::vector<Symbol> mEnableEvents; // 0x80
    std::vector<Symbol> mDisableEvents; // 0x88
    std::vector<Symbol> mWaitForEvents; // 0x90
    ObjPtr<EventTrigger, class ObjectDir> mNextLink; // 0x98
    Symbol unka4;
    ObjPtrList<RndPartLauncher, class ObjectDir> mPartLaunchers; // 0xa8
    float mAnimFrame; // 0xb8
    ObjPtrList<RndDrawable, class ObjectDir> unkbc;
    ObjPtrList<RndDrawable, class ObjectDir> unkcc;
    unsigned char mTriggerOrder; // 0xdc
    unsigned char mAnimTrigger; // 0xdd
    unsigned char unkde; // 0xde
    bool unkdf : 1; // 0xdf >> 7 & 1
    bool mEnabled : 1; // 0xdf >> 6 & 1
    bool mEnabledAtStart : 1; // 0xdf >> 5 & 1
};

BinStream& operator>>(BinStream&, EventTrigger::Anim&);
BinStream& operator>>(BinStream&, EventTrigger::ProxyCall&);
inline BinStream& operator>>(BinStream& bs, EventTrigger::HideDelay& hd){
    bs >> hd.mHide >> hd.mDelay >> hd.mRate;
    return bs;
}

#endif // RNDOBJ_EVENTTRIGGER_H