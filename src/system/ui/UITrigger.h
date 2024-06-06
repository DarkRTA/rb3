#ifndef UI_UITRIGGER_H
#define UI_UITRIGGER_H
#include "rndobj/EventTrigger.h"
#include "rndobj/Poll.h"

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

    DECLARE_REVS;

    ObjPtr<Hmx::Object, ObjectDir> mCallbackObject; // 0xe8
    float mStartTime; // 0xf4
    float mEndTime; // 0xf8
    bool unkfc; // 0xfc
    bool mBlockTransition; // 0xfd
};

#endif