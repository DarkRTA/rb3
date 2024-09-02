#ifndef WORLD_EVENTANIM_H
#define WORLD_EVENTANIM_H
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "obj/ObjList.h"

class EventAnim : public RndAnimatable {
public:
    class EventCall {
    public:
        EventCall(Hmx::Object*);

        ObjPtr<ObjectDir, ObjectDir> mDir; // 0x0
        ObjPtr<EventTrigger, ObjectDir> mEvent; // 0xc
    };

    class KeyFrame {
    public:
        KeyFrame(Hmx::Object*);

        float mTime; // 0x0
        ObjList<EventCall> mCalls; // 0x4
    };

    EventAnim();
    OBJ_CLASSNAME(EventAnim);
    OBJ_SET_TYPE(EventAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~EventAnim(){}
    virtual void StartAnim();
    virtual void EndAnim();
    virtual void SetFrame(float frame, float blend);
    virtual float StartFrame(){ return 0; }
    virtual float EndFrame();

    void RefreshKeys();

    static void TriggerEvents(ObjList<EventCall>&);
    static void ResetEvents(ObjList<EventCall>&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(EventAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(EventAnim)
    }
    
    ObjList<EventCall> mStart; // 0x10
    ObjList<EventCall> mEnd; // 0x1c
    ObjList<KeyFrame> mKeys; // 0x28
    bool mResetStart; // 0x34
    float mLastFrame; // 0x38
};

BinStream& operator>>(BinStream& bs, EventAnim::EventCall& e);
BinStream& operator>>(BinStream& bs, EventAnim::KeyFrame& k);

#endif
