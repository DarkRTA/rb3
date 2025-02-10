#pragma once
#include "bandobj/BandTrack.h"
#include "bandobj/PitchArrow.h"
#include "rndobj/Dir.h"
#include "rndobj/Group.h"
#include "rndobj/Text.h"

enum VocalHUDColor;

class VocalTrackDir : public RndDir, public BandTrack {
public:
    enum HarmonyShowingState {
    };

    VocalTrackDir();
    OBJ_CLASSNAME(VocalTrackDir)
    OBJ_SET_TYPE(VocalTrackDir)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~VocalTrackDir() {}
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);
    virtual void SyncObjects();
    virtual void TrackReset();
    virtual void ResetSmashers(bool);
    virtual void PlayIntro();
    virtual void Deploy();
    virtual void SetPlayerLocal(float);
    virtual ObjectDir *ThisDir() {}
    virtual ObjectDir *ThisDir() const {}
    virtual void SpotlightPhraseSuccess();
    virtual VocalTrackDir *AsVocalTrackDir() {}
    virtual RndDir *AsRndDir() { return AsVocalTrackDir(); }
    virtual void Reset();
    virtual void Retract(bool);
    virtual void Extend(bool);
    virtual void RefreshCrowdRating(float, CrowdMeterState);
    virtual void SetPerformanceMode(bool);
    virtual void SetTambourine(bool);
    virtual void TutorialReset();

    void SetConfiguration(Hmx::Object *, HarmonyShowingState);
    void UpdateConfiguration();
    void ShowPhraseFeedback(int, int, int, bool);
    void SetStreakPct(float);
    void SetEnableVocalsOptions(bool);
    void ApplyFontStyle(Hmx::Object *);
    void ApplyArrowStyle(Hmx::Object *);
    void SetIsolatedPart(int);
    int NumVocalParts();
    void SetRange(float, float, int, bool);
    void UpdateTubeStyle();
    void ConfigPanels();
    PitchArrow *GetPitchArrow(int);
    void Tambourine(Symbol);
    void TambourineNote();
    void SetVocalLineColors(VocalHUDColor *);
    void UpdateVocalMeters(bool, bool, bool, bool);
    void ShowMicDisplay(bool);
    void SetMicDisplayLabel(Symbol);
    void SetMissingMicsForDisplay(bool, bool, bool);
    void CanChat(bool);
    void RecalculateLyricZ(bool *, bool *);
    void SetupNetVocals();
    void UpdatePartIsolation();
    void SortArrowFx();

    DataNode DataForEachConfigObj(DataArray *);
    DataNode OnGetDisplayMode(DataArray *);
    DataNode OnSetDisplayMode(DataArray *);
    DataNode OnSetLyricColor(const DataArray *);
    DataNode OnIsolatePart(DataArray *);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(VocalTrackDir)
    static void Init() { Register(); }
    REGISTER_OBJ_FACTORY_FUNC(VocalTrackDir)

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
    ObjPtr<RndDir> mVocalMics; // 0x2e4
    ObjPtr<RndDir> unk2f0; // 0x2f0
    float mMinPitchRange; // 0x2fc
    float mPitchDisplayMargin; // 0x300
    float mArrowSmoothing; // 0x304
    ObjPtrList<RndTransformable> mConfigurableObjects; // 0x308
    ObjPtr<Hmx::Object> mVoxCfg; // 0x318
    ObjPtr<RndDir> mTambourineSmasher; // 0x324
    ObjPtr<EventTrigger> mTambourineNowShowTrig; // 0x330
    ObjPtr<EventTrigger> mTambourineNowHideTrig; // 0x33c
    ObjPtr<BandLabel> mLeadPhraseFeedbackBottomLbl; // 0x348
    ObjPtr<EventTrigger> mPhraseFeedbackTrig; // 0x354
    ObjPtr<EventTrigger> mSpotlightSparklesOnlyTrig; // 0x360
    ObjPtr<EventTrigger> mSpotlightPhraseSuccessTrig; // 0x36c
    ObjPtr<PitchArrow> mPitchArrow1; // 0x378
    ObjPtr<PitchArrow> mPitchArrow2; // 0x384
    ObjPtr<PitchArrow> mPitchArrow3; // 0x390
    bool mPitchWindow; // 0x39c
    float mPitchWindowHeight; // 0x3a0
    ObjPtr<RndMesh> mPitchWindowMesh; // 0x3a4
    ObjPtr<RndMesh> mPitchWindowOverlay; // 0x3b0
    bool mLeadLyrics; // 0x3bc
    float mLeadLyricHeight; // 0x3c0
    ObjPtr<RndMesh> mLeadLyricMesh; // 0x3c4
    bool mHarmLyrics; // 0x3d0
    float mHarmLyricHeight; // 0x3d4
    ObjPtr<RndMesh> mHarmLyricMesh; // 0x3d8
    ObjPtr<RndMesh> mLeftDecoMesh; // 0x3e4
    ObjPtr<RndMesh> mRightDecoMesh; // 0x3f0
    float mNowBarWidth; // 0x3fc
    ObjPtr<RndMesh> mNowBarMesh; // 0x400
    bool mRemoteVocals; // 0x40c
    float mTrackLeftX; // 0x410
    float mTrackRightX; // 0x414
    float mTrackBottomZ; // 0x418
    float mTrackTopZ; // 0x41c
    float mPitchBottomZ; // 0x420
    float mPitchTopZ; // 0x424
    float mNowBarX; // 0x428
    float unk42c; // 0x42c
    Symbol mPitchGuides; // 0x430
    ObjPtr<Hmx::Object> mTubeStyle; // 0x434
    ObjPtr<Hmx::Object> mArrowStyle; // 0x440
    ObjPtr<Hmx::Object> mFontStyle; // 0x44c
    ObjPtr<RndText> mLeadText; // 0x458
    ObjPtr<RndText> mHarmText; // 0x464
    ObjPtr<RndText> mLeadPhonemeText; // 0x470
    ObjPtr<RndText> mHarmPhonemeText; // 0x47c
    float mLastMin; // 0x488
    float mLastMax; // 0x48c
    float mMiddleCZPos; // 0x490
    int mTonic; // 0x494
    ObjPtr<RndAnimatable> mRangeScaleAnim; // 0x498
    ObjPtr<RndAnimatable> mRangeOffsetAnim; // 0x4a4
    bool unk4b0; // 0x4b0
    int unk4b4; // 0x4b4
    RndTransformable *mLeftTrans; // 0x4b8
    RndTransformable *mRightTrans; // 0x4bc
    RndTransformable *mBottomTrans; // 0x4c0
    RndTransformable *mTopTrans; // 0x4c4
    RndTransformable *mPitchBottomTrans; // 0x4c8
    RndTransformable *mPitchTopTrans; // 0x4cc
    RndTransformable *mPitchMidTrans; // 0x4d0
    RndTransformable *mNowTrans; // 0x4d4
    ObjPtr<RndGroup> mTubeRangeGrp; // 0x4d8
    ObjPtr<RndGroup> mTubeSpotlightGrp; // 0x4e4
    ObjPtr<RndGroup> mTubeBack0Grp; // 0x4f0
    ObjPtr<RndGroup> mTubeBack1Grp; // 0x4fc
    ObjPtr<RndGroup> mTubeBack2Grp; // 0x508
    ObjPtr<RndGroup> mTubeFront0Grp; // 0x514
    ObjPtr<RndGroup> mTubeFront1Grp; // 0x520
    ObjPtr<RndGroup> mTubeFront2Grp; // 0x52c
    ObjPtr<RndGroup> mTubeGlow0Grp; // 0x538
    ObjPtr<RndGroup> mTubeGlow1Grp; // 0x544
    ObjPtr<RndGroup> mTubeGlow2Grp; // 0x550
    ObjPtr<RndGroup> mTubePhoneme0Grp; // 0x55c
    ObjPtr<RndGroup> mTubePhoneme1Grp; // 0x568
    ObjPtr<RndGroup> mTubePhoneme2Grp; // 0x574
    ObjPtr<RndMat> mSpotlightMat; // 0x580
    ObjPtr<RndMat> mLeadBackMat; // 0x58c
    ObjPtr<RndMat> mHarm1BackMat; // 0x598
    ObjPtr<RndMat> mHarm2BackMat; // 0x5a4
    ObjPtr<RndMat> mLeadFrontMat; // 0x5b0
    ObjPtr<RndMat> mHarm1FrontMat; // 0x5bc
    ObjPtr<RndMat> mHarm2FrontMat; // 0x5c8
    ObjPtr<RndMat> mLeadGlowMat; // 0x5d4
    ObjPtr<RndMat> mHarm1GlowMat; // 0x5e0
    ObjPtr<RndMat> mHarm2GlowMat; // 0x5ec
    ObjPtr<RndMat> mLeadPhonemeMat; // 0x5f8
    ObjPtr<RndMat> mHarm1PhonemeMat; // 0x604
    ObjPtr<RndMat> mHarm2PhonemeMat; // 0x610
    ObjPtr<RndGroup> mVocalsGrp; // 0x61c
    ObjPtr<RndTransformable> mScroller; // 0x628
    ObjPtr<RndTransformable> mLeadLyricScroller; // 0x634
    ObjPtr<RndTransformable> mHarmonyLyricScroller; // 0x640
    ObjPtr<RndGroup> mBREGrp; // 0x64c
    ObjPtr<RndGroup> mLeadBREGrp; // 0x658
    ObjPtr<RndGroup> mHarmonyBREGrp; // 0x664
    ObjPtr<RndGroup> mPitchScrollGroup; // 0x670
    ObjPtr<RndGroup> mLeadLyricScrollGroup; // 0x67c
    ObjPtr<RndGroup> mHarmonyLyricScrollGroup; // 0x688
    float unk694; // 0x694
    float unk698; // 0x698
    float unk69c; // 0x69c
    float unk6a0; // 0x6a0
    ObjPtr<RndMat> mLeadDeployMat; // 0x6a4
    ObjPtr<RndMat> mHarmDeployMat; // 0x6b0
    float mGlowSize; // 0x6bc
    float mGlowAlpha; // 0x6c0
    int unk6c4; // 0x6c4
    bool unk6c8; // 0x6c8
    ObjPtr<RndGroup> mArrowFXDrawGrp; // 0x6cc
    float unk6d8; // 0x6d8
    float unk6dc; // 0x6dc
    bool unk6e0; // 0x6e0
};