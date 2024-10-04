#pragma once
#include "obj/Object.h"
#include "bandobj/CrowdMeterIcon.h"
#include "bandobj/TrackPanelDirBase.h"
#include "rndobj/Dir.h"
#include "bandobj/OverdriveMeter.h"
#include "bandobj/StreakMeter.h"
#include "bandobj/UnisonIcon.h"
#include "bandobj/TrackInterface.h"
#include "bandobj/BandCrowdMeter.h"

class BandTrack : public virtual Hmx::Object {
public:
    BandTrack(Hmx::Object*);
    OBJ_CLASSNAME(BandTrack);
    OBJ_SET_TYPE(BandTrack);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Reset();
    virtual void TrackReset(){}
    virtual void ResetSmashers(bool);
    virtual void Retract(bool);
    virtual void Extend(bool){}
    virtual void SpotlightPhraseSuccess();
    virtual void SetStreak(int, int, int, bool);
    virtual void Deploy();
    virtual void StopDeploy();
    virtual void EnterCoda();
    virtual void PlayIntro();
    virtual void DisablePlayer(int);
    virtual void SavePlayer();
    virtual void SuperStreak(bool, bool);
    virtual void PeakState(bool, bool);
    virtual void SetTambourine(bool);
    virtual void SetPlayerLocal(float){}
    virtual void SetHasTrackerFocus(bool);
    virtual ObjectDir* ThisDir(){ MILO_ASSERT(0, 0x8A); return 0; }
    virtual ObjectDir* ThisDir() const; // fix ptr
    virtual int AsGemTrackDir(){ return 0; }
    virtual int AsVocalTrackDir(){ return 0; }
    virtual int AsRndDir();
    virtual void RefreshStreakMeter(int, int, int);
    virtual void RefreshOverdrive(float, bool);
    virtual void RefreshCrowdRating(float, CrowdMeterState){}
    virtual void StartPulseAnims(float);
    virtual void SetupInstrument(){}
    virtual void SetPerformanceMode(bool);
    virtual void SetUsed(bool b){ mInUse = b; }
    virtual void SetInstrument(TrackInstrument);
    virtual void ResetEffectSelector(){}
    virtual void SetupSmasherPlate(){}
    virtual void ReleaseSmasherPlate(){}
    virtual void TutorialReset(){}
    virtual ~BandTrack(){}

    void Init(Hmx::Object*);
    void LoadTrack(BinStream&, bool, bool, bool);
    void CopyTrack(const BandTrack*);
    void ResetStreakMeter();
    void SendTrackerDisplayMessage(const Message&) const;
    void ClearFinaleHelp();
    void FillReset();
    void ResetPopup();
    void SetupPlayerIntro();
    void SetupCrowdMeter();
    void PracticeReset();
    void ShowOverdriveMeter(bool);
    void SetMaxMultiplier(int);
    BandCrowdMeter* GetCrowdMeter();
    void StartFinale(unsigned int);
    void GameWon();
    void GameOver();
    void SpotlightFail(bool);
    void SyncInstrument();
    void EnablePlayer();
    void SetMultiplier(int);
    void CodaFail(bool);
    void CodaSuccess();
    void PopupHelp(Symbol, bool);
    void PlayerDisabled();
    void PlayerSaved();
    void FailedTask(bool, int);
    bool HasNetPlayer() const;
    bool HasLocalPlayer() const;
    int GetPlayerDifficulty() const;
    void SetCrowdRating(float, CrowdMeterState);
    void SetSuppressSoloDisplay(bool);
    void DropIn();
    void DropOut();
    void SoloHide();
    void UnisonEnd();
    void UnisonStart();
    TrackPanelDirBase* MyTrackPanelDir();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    bool mDisabled; // 0x8
    bool mSimulatedNet; // 0x9
    Symbol mInstrument; // 0xc
    TrackInstrument mTrackInstrument; // 0x10
    int unk14; // 0x14
    bool unk18; // 0x18
    bool unk19; // 0x19
    bool unk1a; // 0x1a
    bool unk1b; // 0x1b
    bool unk1c; // 0x1c
    bool mInUse; // 0x1d
    bool unk1e; // 0x1e
    bool mSoloDisplay; // 0x1f
    ObjPtr<RndDir, ObjectDir> mPlayerIntro; // 0x20
    ObjPtr<OverdriveMeter, ObjectDir> mStarPowerMeter; // 0x2c
    ObjPtr<StreakMeter, ObjectDir> mStreakMeter; // 0x38
    ObjPtr<RndDir, ObjectDir> mPopupObject; // 0x44
    ObjPtr<RndDir, ObjectDir> mPlayerFeedback; // 0x50
    ObjPtr<RndDir, ObjectDir> mFailedFeedback; // 0x5c
    ObjPtr<UnisonIcon, ObjectDir> mUnisonIcon; // 0x68
    Symbol unk74; // 0x74
    bool unk78; // 0x78
    ObjPtr<RndDir, ObjectDir> mEndgameFeedback; // 0x7c
    unsigned int unk88; // 0x88
    bool unk8c; // 0x8c
    ObjPtr<TrackInterface, ObjectDir> mParent; // 0x90
    ObjPtr<EventTrigger, ObjectDir> mRetractTrig; // 0x9c
    ObjPtr<EventTrigger, ObjectDir> mResetTrig; // 0xa8
    ObjPtr<EventTrigger, ObjectDir> mDeployTrig; // 0xb4
    ObjPtr<EventTrigger, ObjectDir> mStopDeployTrig; // 0xc0
    ObjPtr<EventTrigger, ObjectDir> mIntroTrig; // 0xcc
    ObjPtr<Task, ObjectDir> unkd8; // 0xd8
    ObjPtr<Task, ObjectDir> unke4; // 0xe4
    ObjPtr<Task, ObjectDir> unkf0; // 0xf0
    ObjPtr<RndGroup, ObjectDir> mBeatAnimsGrp; // 0xfc
    bool mShowOverDriveMeter; // 0x108
    bool mShowCrowdMeter; // 0x109
    int mTrackIdx; // 0x10c
    Symbol unk110; // 0x110
};