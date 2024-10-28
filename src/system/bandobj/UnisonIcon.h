#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "bandobj/BandLabel.h"

class UnisonIcon : public RndDir {
public:
    UnisonIcon();
    OBJ_CLASSNAME(UnisonIcon)
    OBJ_SET_TYPE(UnisonIcon)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual ~UnisonIcon(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();

    void Reset();
    void SetProgress(float);
    void UnisonStart();
    void UnisonEnd();
    void Succeed();
    void Fail();
    void SetIcon(const char*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(UnisonIcon)
    static void Init() {
        Register();
    }
    REGISTER_OBJ_FACTORY_FUNC(UnisonIcon)

    float mProgress; // 0x18c
    EventTrigger* mStartTrig; // 0x190
    EventTrigger* mEndTrig; // 0x194
    EventTrigger* mSucceedTrig; // 0x198
    EventTrigger* mFailTrig; // 0x19c
    EventTrigger* mResetTrig; // 0x1a0
    RndAnimatable* mMeterWipeAnim; // 0x1a4
    BandLabel* mIconLabel; // 0x1a8
};