#pragma once
#include "synth/FxSend.h"

/** "synapse effect" */
class FxSendSynapse : public FxSend {
public:
    FxSendSynapse();
    virtual ~FxSendSynapse(){}
    OBJ_CLASSNAME(FxSendSynapse);
    OBJ_SET_TYPE(FxSendSynapse);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void SetAttackSmoothing(float);
    void SetReleaseSmoothing(float);
    void SetAmount(float);
    void SetProximityEffect(float);
    void SetProximityFocus(float);

    DECLARE_REVS;

    /** "amount of correction". Ranges from 0 to 1. */
    float mAmount; // 0x48
    /** "amount of correction dependence on error". Ranges from 0 to 1. */
    float mProximityEffect; // 0x4c
    /** "focus for amount of correction dependence on error". Ranges from 0 to 1. */
    float mProximityFocus; // 0x50
    /** "target note 1 frequency". Ranges from 10 to 1000. */
    float mNote1Hz; // 0x54
    /** "target note 2 frequency". Ranges from 10 to 1000. */
    float mNote2Hz; // 0x58
    /** "target note 3 frequency". Ranges from 10 to 1000. */
    float mNote3Hz; // 0x5c
    /** "whether the three voices would sing in unison" */
    bool mUnisonTrio; // 0x60
    /** "attack time ms for correction". Ranges from 10 to 500. */
    float mAttackSmoothing; // 0x64
    /** "release time ms for correction". Ranges from 10 to 500. */
    float mReleaseSmoothing; // 0x68
};
