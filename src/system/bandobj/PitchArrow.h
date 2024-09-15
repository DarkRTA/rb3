#pragma once
#include "rndobj/Dir.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Group.h"
#include "rndobj/PropAnim.h"

class PitchArrow : public RndDir {
public:
    PitchArrow();
    OBJ_CLASSNAME(PitchArrowDir);
    OBJ_SET_TYPE(PitchArrowDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual ~PitchArrow(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void Poll();

    void SetArrowStyle(int);
    void Reset(RndGroup*);
    void SetPitched(bool);
    void SetSpotlight(bool);
    void SetDeploying(bool);
    void Clear();
    void ClearParticles();

    DataNode OnSyncColor(DataArray*);
    DataNode OnSetupFx(DataArray*);
    
    static bool NeedSort(PitchArrow*);

    bool unk18c; // 0x18c
    float mScore; // 0x190
    float mHarmonyFX; // 0x194
    float mVolume; // 0x198
    float mTilt; // 0x19c
    int unk1a0; // 0x1a0
    float mColorFade; // 0x1a4
    bool mSpotlight; // 0x1a8
    bool mDeploying; // 0x1a9
    bool mPitched; // 0x1aa
    bool unk1ab; // 0x1ab
    Symbol mTestColor; // 0x1ac
    int mArrowStyle; // 0x1b0
    ObjPtr<RndPropAnim, ObjectDir> mScoreAnim; // 0x1b4
    ObjPtr<RndPropAnim, ObjectDir> mHarmonyFXAnim; // 0x1c0
    ObjPtr<RndPropAnim, ObjectDir> mVolumeAnim; // 0x1cc
    ObjPtr<RndPropAnim, ObjectDir> mTiltAnim; // 0x1d8
    ObjPtr<RndPropAnim, ObjectDir> mColorAnim; // 0x1e4
    ObjPtr<RndPropAnim, ObjectDir> mColorFadeAnim; // 0x1f0
    ObjPtr<RndPropAnim, ObjectDir> mSplitAnim; // 0x1fc
    ObjPtr<RndPropAnim, ObjectDir> mArrowStyleAnim; // 0x208
    ObjPtr<EventTrigger, ObjectDir> mSetPitchedTrig; // 0x214
    ObjPtr<EventTrigger, ObjectDir> mSetUnpitchedTrig; // 0x220
    ObjPtr<EventTrigger, ObjectDir> mSpotlightStartTrig; // 0x22c
    ObjPtr<EventTrigger, ObjectDir> mSpotlightEndTrig; // 0x238
    ObjPtr<EventTrigger, ObjectDir> mDeployStartTrig; // 0x244
    ObjPtr<EventTrigger, ObjectDir> mDeployEndTrig; // 0x250
    ObjPtr<RndGroup, ObjectDir> mGhostGrp; // 0x25c
    ObjPtr<RndPropAnim, ObjectDir> mGhostFadeAnim; // 0x268
    ObjPtr<RndGroup, ObjectDir> mArrowFXGrp; // 0x274
    bool unk280; // 0x280
    float mSpinSpeed; // 0x284
    ObjPtr<RndPropAnim, ObjectDir> mSpinAnim; // 0x288
    float mSpinRestFrame; // 0x294
    float mSpinBeginFrame; // 0x298
    float mSpinEndFrame; // 0x29c
};