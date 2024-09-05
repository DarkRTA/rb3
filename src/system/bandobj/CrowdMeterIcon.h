#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "bandobj/BandLabel.h"

enum CrowdMeterState {
    kCrowdMeterNormal = 0,
    kCrowdMeterWarning = 1,
    kCrowdMeterFailed = 2,
    kCrowdMeterInvalidState = 3
};

class CrowdMeterIcon : public RndDir {
public:
    CrowdMeterIcon();
    OBJ_CLASSNAME(CrowdMeterIcon)
    OBJ_SET_TYPE(CrowdMeterIcon)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object* o, Hmx::Object::CopyType ty){ COPY_SUPERCLASS(RndDir); }
    virtual ~CrowdMeterIcon(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream& bs){ RndDir::PostLoad(bs); }
    virtual void SyncObjects();

    void Deploy();
    void StopDeploy();
    void Reset();
    void SetQuarantined(bool);
    void DropIn();
    void DropOut();
    void SetState(CrowdMeterState, bool);
    void ArrowShow(bool);
    void SetGlowing(bool);
    void SetIcon(const char*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<EventTrigger, ObjectDir> mResetTrig; // 0x18c
    ObjPtr<EventTrigger, ObjectDir> mArrowHideTrig; // 0x198
    ObjPtr<EventTrigger, ObjectDir> mArrowShowTrig; // 0x1a4
    ObjPtr<EventTrigger, ObjectDir> mDeployTrig; // 0x1b0
    ObjPtr<EventTrigger, ObjectDir> mStopDeployTrig; // 0x1bc
    ObjPtr<EventTrigger, ObjectDir> mStateFailedTrig; // 0x1c8
    ObjPtr<EventTrigger, ObjectDir> mStateFailingTrig; // 0x1d4
    ObjPtr<EventTrigger, ObjectDir> mStateNormalTrig; // 0x1e0
    ObjPtr<EventTrigger, ObjectDir> mGlowTrig; // 0x1ec
    ObjPtr<EventTrigger, ObjectDir> mGlowStopTrig; // 0x1f8
    ObjPtr<EventTrigger, ObjectDir> mStateQuarantinedTrig; // 0x204
    ObjPtr<EventTrigger, ObjectDir> mDropInTrig; // 0x210
    ObjPtr<EventTrigger, ObjectDir> mDropOutTrig; // 0x21c
    ObjPtr<BandLabel, ObjectDir> mIconLabel; // 0x228
    ObjPtr<RndAnimatable, ObjectDir> mIconStateAnim; // 0x234
    int unk240; // 0x240
    CrowdMeterState mState; // 0x244
    bool mQuarantined; // 0x248
};