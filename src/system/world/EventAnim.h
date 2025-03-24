#pragma once
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "obj/ObjList.h"

/** "Triggers events on proxy's along a timeline" */
class EventAnim : public RndAnimatable {
public:
    class EventCall {
    public:
        EventCall(Hmx::Object *);

        ObjPtr<ObjectDir> mDir; // 0x0
        ObjPtr<EventTrigger> mEvent; // 0xc
    };

    class KeyFrame {
    public:
        KeyFrame(Hmx::Object *);
        bool operator<(const KeyFrame &kf) const {
            return mTime < kf.mTime ? true : false;
        }

        /** "time for event" */
        float mTime; // 0x0
        ObjList<EventCall> mCalls; // 0x4
    };

    EventAnim();
    OBJ_CLASSNAME(EventAnim);
    OBJ_SET_TYPE(EventAnim);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~EventAnim() {}
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float frame, float blend);
    virtual float StartFrame() { return 0; }
    virtual float EndFrame();

    /** Sorts the key triggers by time. */
    void RefreshKeys();
    void SetResetStart(bool b) { mResetStart = b; }

    static void TriggerEvents(ObjList<EventCall> &);
    static void ResetEvents(ObjList<EventCall> &);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(EventAnim)
    static void Init() { REGISTER_OBJ_FACTORY(EventAnim) }

    /** "Triggers played first, during StartAnim" */
    ObjList<EventCall> mStart; // 0x10
    /** "Triggers played when done, during EndAnim" */
    ObjList<EventCall> mEnd; // 0x1c
    /** "Triggers played during a particular keyframe.  Do not set key to zero, hoping it
     * will always get fired on start, put them in start instead." */
    ObjList<KeyFrame> mKeys; // 0x28
    /** "Resets all start + keys events when done, during EndAnim, normally should be
     * checked" */
    bool mResetStart; // 0x34
    float mLastFrame; // 0x38
};

BinStream &operator>>(BinStream &bs, EventAnim::EventCall &e);
BinStream &operator>>(BinStream &bs, EventAnim::KeyFrame &k);
