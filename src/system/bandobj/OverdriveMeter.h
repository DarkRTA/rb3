#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Group.h"

class OverdriveMeter : public RndDir {
public:
    enum State {

    };

    OverdriveMeter();
    OBJ_CLASSNAME(OverdriveMeterDir);
    OBJ_SET_TYPE(OverdriveMeterDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~OverdriveMeter();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();

    void Reset();
    void SetEnergy(float, State, Symbol, float, bool);
    void MiloReset();
    void EnergyReady(Symbol, bool, float);
    void Deploy();
    void StopDeploy();
    void SetNoOverdrive();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(OverdriveMeter)
    static void Init() {
        Register();
    }
    REGISTER_OBJ_FACTORY_FUNC(OverdriveMeter)

    State mState; // 0x18c
    ObjPtr<EventTrigger, ObjectDir> mResetTrig; // 0x190
    ObjPtr<EventTrigger, ObjectDir> mSpotlightPhraseSuccessTrig; // 0x19c
    ObjPtr<EventTrigger, ObjectDir> mBeDeployingTrig; // 0x1a8
    ObjPtr<EventTrigger, ObjectDir> mBeFillingTrig; // 0x1b4
    ObjPtr<EventTrigger, ObjectDir> mBeReadyTrig; // 0x1c0
    ObjPtr<EventTrigger, ObjectDir> mPulseMiloTrig; // 0x1cc
    ObjPtr<EventTrigger, ObjectDir> mNoOverdriveTrig; // 0x1d8
    ObjPtr<RndGroup, ObjectDir> mExtendAnimGroup; // 0x1e4
    ObjPtr<RndGroup, ObjectDir> mPulseAnimGroup; // 0x1f0
    float mTestEnergy; // 0x1fc
};