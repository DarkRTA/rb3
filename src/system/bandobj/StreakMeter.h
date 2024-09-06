#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PropAnim.h"
#include "rndobj/TransAnim.h"
#include "bandobj/BandLabel.h"

class StreakMeter : public RndDir {
public:
    StreakMeter();
    OBJ_CLASSNAME(StreakMeterDir);
    OBJ_SET_TYPE(StreakMeterDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~StreakMeter();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    
    void Reset();
    void SetBandMultiplier(int);
    void EndOverdrive() const;

    int mStreakMultiplier; // 0x18c
    int mBandMultiplier; // 0x190
    int mMaxMultiplier; // 0x194
    bool mShowBandMult; // 0x198
    ObjPtr<EventTrigger, ObjectDir> mNewStreakTrig; // 0x19c
    ObjPtr<EventTrigger, ObjectDir> mEndStreakTrig; // 0x1a8
    ObjPtr<EventTrigger, ObjectDir> mPeakStateTrig; // 0x1b4
    ObjPtr<EventTrigger, ObjectDir> mBreakOverdriveTrig; // 0x1c0
    ObjPtr<RndTransAnim, ObjectDir> mMultiMeterAnim; // 0x1cc
    ObjPtr<BandLabel, ObjectDir> mMultiplierLabel; // 0x1d8
    ObjPtr<BandLabel, ObjectDir> mXLabel; // 0x1e4
    ObjPtr<RndPropAnim, ObjectDir> mMeterWipeAnim; // 0x1f0
    ObjPtr<EventTrigger, ObjectDir> mStarDeployTrig; // 0x1fc
    ObjPtr<EventTrigger, ObjectDir> mEndOverdriveTrig; // 0x208
    ObjPtr<EventTrigger, ObjectDir> mStarDeployStopTrig; // 0x214
    ObjPtr<EventTrigger, ObjectDir> mStarDeployPauseTrig; // 0x220
    ObjPtr<EventTrigger, ObjectDir> mResetTrig; // 0x22c
    ObjPtr<EventTrigger, ObjectDir> mHideMultiplierTrig; // 0x238
    int unk244; // 0x244
    ObjPtr<EventTrigger, ObjectDir> unk248; // 0x248
    ObjPtr<EventTrigger, ObjectDir> unk254; // 0x254
    bool unk260; // 0x260
    ObjPtr<RndGroup, ObjectDir> mPartBarsGroup; // 0x264
    int unk270; // 0x270
    ObjVector<ObjPtr<RndPropAnim, ObjectDir> > mPartColorAnims; // 0x274
    ObjVector<ObjPtr<RndPropAnim, ObjectDir> > mPartFadeAnims; // 0x280
    ObjVector<ObjPtr<RndPropAnim, ObjectDir> > mPartWipeAnims; // 0x28c
    ObjVector<ObjPtr<RndPropAnim, ObjectDir> > mPartWipeResidualAnims; // 0x298
    ObjPtr<EventTrigger, ObjectDir> mResidueFadeTrig; // 0x2a4
    ObjPtr<RndPropAnim, ObjectDir> mNumPartsAnim; // 0x2b0
    ObjVector<ObjPtr<RndPartLauncher, ObjectDir> > mPartSparksLaunchers; // 0x2bc
    int unk2c8; // 0x2c8
    int unk2cc; // 0x2cc
    int unk2d0; // 0x2d0
    int unk2d4; // 0x2d4
};