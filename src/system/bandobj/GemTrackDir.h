#pragma once
#include "track/TrackDir.h"
#include "bandobj/BandTrack.h"
#include "rndobj/Group.h"
#include "rndobj/Tex.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Env.h"
#include "rndobj/Cam.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/PropAnim.h"
#include "track/TrackWidget.h"
#include "obj/Task.h"
#include "bandobj/ChordShapeGenerator.h"
#include "beatmatch/RGState.h"
#include "bandobj/FingerShape.h"
#include "bandobj/ArpeggioShape.h"

class GemTrackDir : public TrackDir, public BandTrack {
public:
    GemTrackDir();
    OBJ_CLASSNAME(GemTrackDir)
    OBJ_SET_TYPE(GemTrackDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~GemTrackDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void Poll();
    virtual void SyncFingerFeedback();
    virtual void SetDisplayRange(float);
    virtual void SetDisplayOffset(float, bool);
    virtual RndDir* SmasherPlate(){ return mSmasherPlate; }
    virtual float GetFretPosOffset(int) const;
    virtual int GetNumFretPosOffsets() const { return mFretPosOffsets.size(); }
    virtual float GetCurrentChordLabelPosOffset() const;
    virtual int PrepareChordMesh(unsigned int);
    virtual int GetChordMesh(unsigned int, bool);
    virtual void SetUnisonProgress(float);
    virtual void ClearChordMeshRefCounts();
    virtual void DeleteUnusedChordMeshes();
    virtual void AddChordImpl(RndMesh*, TrackWidget*, TrackWidget*, TrackWidget*, float, const std::vector<int>&, class String);
    virtual ArpeggioShapePool* GetArpeggioShapePool(){ return mArpShapePool; }
    virtual bool IsBlackKey(int) const;
    virtual void KeyMissLeft();
    virtual void KeyMissRight();
    virtual bool IsActiveInSession() const;
    virtual void PlayIntro();
    virtual void TrackReset();
    virtual void ResetSmashers(bool);
    virtual void GameWon();
    virtual void Retract(bool);
    virtual void Extend(bool);
    virtual void SetStreak(int, int, int, bool);
    virtual void PeakState(bool, bool);
    virtual void SuperStreak(bool, bool);
    virtual void Deploy();
    virtual void EnterCoda();
    virtual void DisablePlayer(int);
    virtual void SetPlayerLocal(float);
    virtual ObjectDir* ThisDir(){}
    virtual ObjectDir* ThisDir() const {}
    virtual void RefreshStreakMeter(int, int, int);
    virtual void SpotlightPhraseSuccess();
    virtual int AsGemTrackDir(){}
    virtual int AsRndDir(){ return AsGemTrackDir(); }
    virtual void SetPerformanceMode(bool);
    virtual void SetInstrument(TrackInstrument);
    virtual void SetupInstrument();
    virtual void ResetEffectSelector();
    virtual void SetupSmasherPlate();
    virtual void ReleaseSmasherPlate();

    void SetPitch(float);
    void SetFade(float, float);
    void SetFOV(float);
    void SetCamPos(float, float, float);
    void SetScreenRectX(float);
    void SetTrackOffset(float);
    void SetSideAngle(float);
    void Mash(int);
    void CrashFill();
    bool ToggleKeyShifting();
    void UpdateSurfaceTexture();
    void OnUpdateFx(int);
    void GemPass(int, int);
    void GemHit(int);
    void SeeKick();
    void KickSwing();
    void FillMash(int);
    void FillHit(int);
    void ResetDrumFill();
    void ResetCoda();
    float GetKeyRange();
    float GetKeyOffset();
    void UpdateFingerFeedback(const RGState&);
    void UpdateLeftyFlip(bool);
    bool KeyShifting();
    void AddChordRepImpl(RndMesh*, TrackWidget*, TrackWidget*, TrackWidget*, float, const std::vector<int>&, String);

    DataNode OnDrawSampleChord(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int mNumTracks; // 0x484
    int unk488; // 0x488
    int mGemTrackDirID; // 0x48c
    int mKickPassCounter; // 0x490
    int unk494; // 0x494
    float mStreakMeterOffset; // 0x498
    float mStreakMeterTilt; // 0x49c
    float mTrackPitch; // 0x4a0
    ObjPtr<RndDir, ObjectDir> mEffectSelector; // 0x4a4
    ObjPtr<RndGroup, ObjectDir> mRotater; // 0x4b0
    ObjPtr<RndTex, ObjectDir> mSurfaceTexture; // 0x4bc
    ObjPtr<RndMesh, ObjectDir> mSurfaceMesh; // 0x4c8
    ObjPtr<RndMat, ObjectDir> mSurfaceMat; // 0x4d4
    ObjPtr<RndEnviron, ObjectDir> mTrackEnv; // 0x4e0
    ObjPtr<RndEnviron, ObjectDir> mTrackMissGemsEnv; // 0x4ec
    ObjPtr<RndCam, ObjectDir> mGameCam; // 0x4f8
    ObjPtr<EventTrigger, ObjectDir> mPeakStateOnTrig; // 0x504
    ObjPtr<EventTrigger, ObjectDir> mPeakStateOffTrig; // 0x510
    ObjPtr<EventTrigger, ObjectDir> mPeakStopImmediateTrig; // 0x51c
    ObjPtr<EventTrigger, ObjectDir> mBassSuperStreakOnTrig; // 0x528
    ObjPtr<EventTrigger, ObjectDir> mBassSuperStreakOffTrig; // 0x534
    ObjPtr<EventTrigger, ObjectDir> mBassSSOffImmediateTrig; // 0x540
    ObjPtr<EventTrigger, ObjectDir> mKickDrummerTrig; // 0x54c
    ObjPtr<EventTrigger, ObjectDir> mKickDrummerResetTrig; // 0x558
    ObjPtr<EventTrigger, ObjectDir> mSpotlightPhraseSuccessTrig; // 0x564
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > mGemMashAnims; // 0x570
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > mDrumMashAnims; // 0x578
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > mFillLaneAnims; // 0x580
    std::vector<ObjPtr<RndPropAnim, ObjectDir> > mRealGuitarMashAnims; // 0x588
    std::vector<std::pair<ObjPtr<EventTrigger, ObjectDir>, ObjPtr<EventTrigger, ObjectDir> > > mDrumRollTrigs; // 0x590
    std::vector<std::pair<ObjPtr<EventTrigger, ObjectDir>, ObjPtr<EventTrigger, ObjectDir> > > mTrillTrigs; // 0x598
    std::vector<ObjPtr<EventTrigger, ObjectDir> > mFillHitTrigs; // 0x5a0
    ObjPtr<EventTrigger, ObjectDir> mDrumFillResetTrig; // 0x5a8
    ObjPtr<RndPropAnim, ObjectDir> mDrumMash2ndPassActivateAnim; // 0x5b4
    ObjPtr<RndGroup, ObjectDir> mDrumMashHitAnimGrp; // 0x5c0
    ObjPtr<RndGroup, ObjectDir> mFillColorsGrp; // 0x5cc
    ObjPtr<RndPropAnim, ObjectDir> mLodAnim; // 0x5d8
    ObjPtr<RndDir, ObjectDir> mSmasherPlate; // 0x5e4
    ObjPtrList<TrackWidget, ObjectDir> mGlowWidgets; // 0x5f0
    ObjPtr<Task, ObjectDir> unk600; // 0x600
    ObjPtr<Task, ObjectDir> unk60c; // 0x60c
    ObjPtr<Task, ObjectDir> unk618; // 0x618
    ObjPtr<Task, ObjectDir> unk624; // 0x624
    ObjPtr<RndMesh, ObjectDir> mGemWhiteMesh; // 0x630
    ObjPtr<EventTrigger, ObjectDir> mMissOutofRangeRightTrig; // 0x63c
    ObjPtr<EventTrigger, ObjectDir> mMissOutofRangeLeftTrig; // 0x648
    ObjPtr<RndAnimatable, ObjectDir> unk654; // 0x654
    ObjPtr<RndAnimatable, ObjectDir> mKeysShiftAnim; // 0x660
    ObjPtr<RndPropAnim, ObjectDir> mKeysMashAnim; // 0x66c
    float mKeyRange; // 0x678
    float mKeyOffset; // 0x67c
    std::vector<RndDir*> unk680; // 0x680
    std::vector<EventTrigger*> unk688; // 0x688
    std::vector<EventTrigger*> unk690; // 0x690
    FingerShape* mFingerShape; // 0x698
    std::vector<float> mFretPosOffsets; // 0x69c
    float mChordLabelPosOffset; // 0x6a4
    ObjPtr<ChordShapeGenerator, ObjectDir> mChordShapeGen; // 0x6a8
    std::map<unsigned int, std::pair<int, RndMesh*> > unk6b4; // 0x6b4
    std::map<unsigned int, std::pair<int, RndMesh*> > unk6cc; // 0x6cc
    ArpeggioShapePool* mArpShapePool; // 0x6e4
    bool unk6e8; // 0x6e8
#ifdef MILO_DEBUG
    bool mFakeFingerShape; // 0x6e9
    bool mCycleFakeFingerShapes; // 0x6ea
    int mRandomShapeFrameCount; // 0x6ec
    RGState mRGState; // 0x6f0
#endif
};