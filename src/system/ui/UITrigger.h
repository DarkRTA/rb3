#pragma once
#include "rndobj/EventTrigger.h"
#include "rndobj/Poll.h"

/** "Triggers anims based on UI events (enter, exit, etc.)" */
class UITrigger : public EventTrigger, public RndPollable {
public:
    UITrigger();
    OBJ_CLASSNAME(UITrigger);
    OBJ_SET_TYPE(UITrigger);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~UITrigger(){}
    virtual void Trigger();
    virtual DataArray* SupportedEvents();
    virtual void CheckAnims();
    virtual void Enter();
    virtual void Poll();

    void PlayStartOfAnims();
    void PlayEndOfAnims();
    void StopAnimations();
    bool IsBlocking() const;
    bool IsDone() const { return mEndTime <= TheTaskMgr.UISeconds(); }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD
    NEW_OBJ(UITrigger);
    static void Init(){
        REGISTER_OBJ_FACTORY(UITrigger);
    }

    ObjPtr<Hmx::Object> mCallbackObject; // 0xe8
    float mStartTime; // 0xf4
    float mEndTime; // 0xf8
    bool unkfc; // 0xfc
    /** "Block enter/exit transition during animation?" */
    bool mBlockTransition; // 0xfd
};

#include "obj/Msg.h"

DECLARE_MESSAGE(UITriggerCompleteMsg, "ui_trigger_complete");
    UITriggerCompleteMsg(UITrigger* trig) : 
        Message(Type(), trig){}
END_MESSAGE;
