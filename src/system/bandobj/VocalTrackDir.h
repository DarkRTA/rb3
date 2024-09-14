#pragma once
#include "bandobj/BandTrack.h"
#include "bandobj/PitchArrow.h"
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "rndobj/Text.h"

class VocalTrackDir : public RndDir, public BandTrack {
public:
    enum HarmonyShowingState {

    };

    VocalTrackDir();
    OBJ_CLASSNAME(VocalTrackDir)
    OBJ_SET_TYPE(VocalTrackDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~VocalTrackDir(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void TrackReset();
    virtual void ResetSmashers(bool);
    virtual void PlayIntro();
    virtual void Deploy();
    virtual void SetPlayerLocal(float);
    virtual ObjectDir* ThisDir(){}
    virtual ObjectDir* ThisDir() const {}
    virtual void SpotlightPhraseSuccess();
    virtual int AsVocalTrackDir(){}
    virtual int AsRndDir(){ return AsVocalTrackDir(); }
    virtual void Reset();
    virtual void Retract(bool);
    virtual void Extend(bool);
    virtual void RefreshCrowdRating(float, CrowdMeterState);
    virtual void SetPerformanceMode(bool);
    virtual void SetTambourine(bool);
    virtual void TutorialReset();

    void SetConfiguration(Hmx::Object*, HarmonyShowingState);
    void UpdateConfiguration();
    void ShowPhraseFeedback(int, int, int, bool);
    void SetStreakPct(float);
    void SetEnableVocalsOptions(bool);
    void ApplyFontStyle(Hmx::Object*);
    void ApplyArrowStyle(Hmx::Object*);
    void SetIsolatedPart(int);
    int NumVocalParts();
    void SetRange(float, float, int, bool);

    DataNode DataForEachConfigObj(DataArray*);
    DataNode OnGetDisplayMode(DataArray*);
    DataNode OnSetDisplayMode(DataArray*);
    DataNode OnSetLyricColor(const DataArray*);
    DataNode OnIsolatePart(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    float mHiddenPartAlpha; // 0x2a0
    bool unk2a4; // 0x2a4
    bool unk2a5; // 0x2a5
    bool mIsTop; // 0x2a6
    bool unk2a7; // 0x2a7
    int mFeedbackStateLead; // 0x2a8
    int mFeedbackStateHarm1; // 0x2ac
    int mFeedbackStateHarm2; // 0x2b0
    std::map<int, Hmx::Color> mLyricColorMap; // 0x2b4
    std::map<int, float> mLyricAlphaMap; // 0x2cc
    ObjPtr<RndDir, ObjectDir> unk2e4; // 0x2e4
    ObjPtr<RndDir, ObjectDir> unk2f0; // 0x2f0
    float mMinPitchRange; // 0x2fc
    float mPitchDisplayMargin; // 0x300
    float mArrowSmoothing; // 0x304
    ObjPtrList<RndTransformable, ObjectDir> mConfigurableObjects; // 0x308
    ObjPtr<Hmx::Object, ObjectDir> mVoxCfg; // 0x318
    ObjPtr<RndDir, ObjectDir> unk324; // 0x324
    ObjPtr<EventTrigger, ObjectDir> unk330; // 0x330
    ObjPtr<EventTrigger, ObjectDir> unk33c; // 0x33c
    ObjPtr<BandLabel, ObjectDir> unk348; // 0x348
    ObjPtr<EventTrigger, ObjectDir> mPhraseFeedbackTrig; // 0x354
    ObjPtr<EventTrigger, ObjectDir> mSpotlightSparklesOnlyTrig; // 0x360
    ObjPtr<EventTrigger, ObjectDir> mSpotlightPhraseSuccessTrig; // 0x36c
    ObjPtr<PitchArrow, ObjectDir> unk378; // 0x378
    ObjPtr<PitchArrow, ObjectDir> unk384; // 0x384
    ObjPtr<PitchArrow, ObjectDir> unk390; // 0x390
    bool mPitchWindow; // 0x39c
    float mPitchWindowHeight; // 0x3a0
    ObjPtr<RndMesh, ObjectDir> mPitchWindowMesh; // 0x3a4
    ObjPtr<RndMesh, ObjectDir> mPitchWindowOverlay; // 0x3b0
    bool mLeadLyrics; // 0x3bc
    float mLeadLyricHeight; // 0x3c0
    ObjPtr<RndMesh, ObjectDir> mLeadLyricMesh; // 0x3c4
    bool mHarmLyrics; // 0x3d0
    float mHarmLyricHeight; // 0x3d4
    ObjPtr<RndMesh, ObjectDir> mHarmLyricMesh; // 0x3d8
    ObjPtr<RndMesh, ObjectDir> mLeftDecoMesh; // 0x3e4
    ObjPtr<RndMesh, ObjectDir> mRightDecoMesh; // 0x3f0
    float mNowBarWidth; // 0x3fc
    ObjPtr<RndMesh, ObjectDir> mNowBarMesh; // 0x400
    bool mRemote; // 0x40c
    float mTrackLeft; // 0x410
    float mTrackRight; // 0x414
    float mTrackBottom; // 0x418
    float mTrackTop; // 0x41c
    float mPitchBottom; // 0x420
    float mPitchTop; // 0x424
    float mNowBar; // 0x428
    float unk42c; // 0x42c
    Symbol mPitchGuides; // 0x430
    ObjPtr<Hmx::Object, ObjectDir> mTubeStyle; // 0x434
    ObjPtr<Hmx::Object, ObjectDir> mArrowStyle; // 0x440
    ObjPtr<Hmx::Object, ObjectDir> mFontStyle; // 0x44c
    ObjPtr<RndText, ObjectDir> unk458; // 0x458
    ObjPtr<RndText, ObjectDir> unk464; // 0x464
    ObjPtr<RndText, ObjectDir> unk470; // 0x470
    ObjPtr<RndText, ObjectDir> unk47c; // 0x47c
    float mLastMin; // 0x488
    float mLastMax; // 0x48c
    float mMiddleCZPos; // 0x490
    int mTonic; // 0x494
    ObjPtr<RndAnimatable, ObjectDir> mRangeScaleAnim; // 0x498
    ObjPtr<RndAnimatable, ObjectDir> mRangeOffsetAnim; // 0x4a4
    bool unk4b0; // 0x4b0
    int unk4b4; // 0x4b4
    int unk4b8; // 0x4b8
    int unk4bc; // 0x4bc
    int unk4c0; // 0x4c0
    int unk4c4; // 0x4c4
    int unk4c8; // 0x4c8
    int unk4cc; // 0x4cc
    int unk4d0; // 0x4d0
    int unk4d4; // 0x4d4
    ObjPtr<RndGroup, ObjectDir> unk4d8; // 0x4d8
    ObjPtr<RndGroup, ObjectDir> unk4e4; // 0x4e4
    ObjPtr<RndGroup, ObjectDir> unk4f0; // 0x4f0
    ObjPtr<RndGroup, ObjectDir> unk4fc; // 0x4fc
    ObjPtr<RndGroup, ObjectDir> unk508; // 0x508
    ObjPtr<RndGroup, ObjectDir> unk514; // 0x514
    ObjPtr<RndGroup, ObjectDir> unk520; // 0x520
    ObjPtr<RndGroup, ObjectDir> unk52c; // 0x52c
    ObjPtr<RndGroup, ObjectDir> unk538; // 0x538
    ObjPtr<RndGroup, ObjectDir> unk544; // 0x544
    ObjPtr<RndGroup, ObjectDir> unk550; // 0x550
    ObjPtr<RndGroup, ObjectDir> unk55c; // 0x55c
    ObjPtr<RndGroup, ObjectDir> unk568; // 0x568
    ObjPtr<RndGroup, ObjectDir> unk574; // 0x574
    ObjPtr<RndMat, ObjectDir> unk580; // 0x580
    ObjPtr<RndMat, ObjectDir> unk58c; // 0x58c
    ObjPtr<RndMat, ObjectDir> unk598; // 0x598
    ObjPtr<RndMat, ObjectDir> unk5a4; // 0x5a4
    ObjPtr<RndMat, ObjectDir> unk5b0; // 0x5b0
    ObjPtr<RndMat, ObjectDir> unk5bc; // 0x5bc
    ObjPtr<RndMat, ObjectDir> unk5c8; // 0x5c8
    ObjPtr<RndMat, ObjectDir> unk5d4; // 0x5d4
    ObjPtr<RndMat, ObjectDir> unk5e0; // 0x5e0
    ObjPtr<RndMat, ObjectDir> unk5ec; // 0x5ec
    ObjPtr<RndMat, ObjectDir> unk5f8; // 0x5f8
    ObjPtr<RndMat, ObjectDir> unk604; // 0x604
    ObjPtr<RndMat, ObjectDir> unk610; // 0x610
    ObjPtr<RndGroup, ObjectDir> unk61c; // 0x61c
    ObjPtr<RndTransformable, ObjectDir> unk628; // 0x628
    ObjPtr<RndTransformable, ObjectDir> unk634; // 0x634
    ObjPtr<RndTransformable, ObjectDir> unk640; // 0x640
    ObjPtr<RndGroup, ObjectDir> unk64c; // 0x64c
    ObjPtr<RndGroup, ObjectDir> unk658; // 0x658
    ObjPtr<RndGroup, ObjectDir> unk664; // 0x664
    ObjPtr<RndGroup, ObjectDir> unk670; // 0x670
    ObjPtr<RndGroup, ObjectDir> unk67c; // 0x67c
    ObjPtr<RndGroup, ObjectDir> unk688; // 0x688
    float unk694; // 0x694
    float unk698; // 0x698
    float unk69c; // 0x69c
    float unk6a0; // 0x6a0
    ObjPtr<RndMat, ObjectDir> mLeadDeployMat; // 0x6a4
    ObjPtr<RndMat, ObjectDir> mHarmDeployMat; // 0x6b0
    float unk6bc; // 0x6bc
    float unk6c0; // 0x6c0
    int unk6c4; // 0x6c4
    bool unk6c8; // 0x6c8
    ObjPtr<RndGroup, ObjectDir> unk6cc; // 0x6cc
    float unk6d8; // 0x6d8
    float unk6dc; // 0x6dc
    bool unk6e0; // 0x6e0
};