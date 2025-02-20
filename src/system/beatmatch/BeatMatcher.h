#pragma once
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/DrumPlayer.h"
#include "beatmatch/MasterAudio.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/TrackWatcher.h"
#include "beatmatch/TrackWatcherParent.h"
#include "game/Player.h"
#include "utl/HxGuid.h"
#include "utl/SongPos.h"
#include "utl/Symbol.h"
#include "utl/SongInfoCopy.h"

// forward decs
class SongData;
class DataArray;
class BeatMaster;
class MercurySwitchFilter;

class BeatMatcher : public TrackWatcherParent, public BeatMatchControllerSink {
public:
    BeatMatcher(const UserGuid &, int, int, Symbol, SongData *, SongInfo &, DataArray *, BeatMaster *);
    virtual ~BeatMatcher();
    virtual float GetNow() const { return mNow; }
    virtual int GetTick() const { return mTick; }
    virtual float GetWhammyBar() const;
    virtual int GetMaxSlots() const;
    virtual void SetPitchBend(int, float, bool);
    virtual void ResetPitchBend(int);
    virtual bool InFillNow();
    virtual bool InFill(int, bool);
    virtual bool FillsEnabled(int);
    virtual FillLogic GetFillLogic() const;
    virtual bool InSolo(int);
    virtual bool InCoda(int);
    virtual bool InCodaFreestyle(int, bool);
    virtual void SetButtonMashingMode(bool);
    virtual int GetVelocityBucket(int);
    virtual int GetVirtualSlot(int);
    virtual void PlayDrum(int, bool, float);

    virtual void FretButtonDown(int, int);
    virtual void FretButtonUp(int);
    virtual void RGFretButtonDown(int);
    virtual bool Swing(int, bool, bool, bool, bool, GemHitFlags);
    virtual void ReleaseSwing();
    virtual void NonStrumSwing(int, bool, bool);
    virtual void MercurySwitch(float);
    virtual void ForceMercurySwitch(bool);
    virtual void SetController(class BeatMatchController *);
    virtual void NoteOn(int);
    virtual void NoteOff(int);
    virtual void PlayNote(int);
    virtual void OutOfRangeSwing();

    virtual void SetTrack(int);
    virtual float GetCapStrip() const;

    void SetFillLogic(FillLogic);
    bool IsAutoplay();
    void SetAutoplay(bool);
    void PostLoad();
    void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool);
    void PostDynamicAdd(int, float);
    void ResetGemStates(float);
    void Leave();
    bool IsReady();
    void Start();
    void RegisterSink(BeatMatchSink &);
    void Poll(float);
    void SetNow(float);
    void CheckMercurySwitch(float);
    void Jump(float);
    void Restart();
    void UpdateMercurySwitch();
    void SetDrumKitBank(ObjectDir *);
    TrackType GetTrackType(int) const;
    void AutoplayCoda(bool);
    void SetAutoplayError(int);
    void SetAutoOn(bool);
    float CycleAutoplayAccuracy();
    void SetAutoplayAccuracy(float);
    void DrivePitchBendExternally(bool);
    void SetCodaStartTick(int);
    void EnterCoda();
    void SetFillsEnabled(bool);
    void Enable(bool);
    void EnableController(bool);
    void DisableFillsCompletely();
    void SetFillsEnabled(int, bool);
    void ForceFill(bool);
    void SetSyncOffset(float);
    void SetControllerType(Symbol);
    bool UsingAlternateButtons() const;
    void EnableWhammy(bool);
    void EnableCapStrip(bool);
    void E3CheatIncSlop();
    void E3CheatDecSlop();
    bool IsFillCompletion(int);
    unsigned int GetRGRollSlots(int) const;
    void SetFillAudio(bool audio) { mFillAudio = audio; }
    int GetFillStartTick() const { return mFillStartTick; }

    bool mWaitingForAudio; // 0x8
    UserGuid mUserGuid; // 0xc
    int unk1c; // 0x1c
    int unk20; // 0x20
    Symbol mControllerType; // 0x24
    SongData *mSongData; // 0x28
    DataArray *mCfg; // 0x2c
    int unk30; // 0x30
    BeatMatchSink *mSink; // 0x34
    MasterAudio *mAudio; // 0x38
    BeatMatchController *mController; // 0x3c
    MercurySwitchFilter *mMercurySwitchFilter; // 0x40
    TrackWatcher *mWatcher; // 0x44
    std::vector<TrackType> mTrackTypes; // 0x48
    std::vector<float> unk50; // 0x50
    DrumPlayer *mDrumPlayer; // 0x58
    int mCurTrack; // 0x5c
    bool unk60; // 0x60
    SongPos mSongPos; // 0x64
    float mNow; // 0x78
    int mTick; // 0x7c
    float mLastSwing; // 0x80
    float mLastReleaseSwing; // 0x84
    bool unk88; // 0x88
    int mLastVelocityBucket; // 0x8c
    float mRawMercurySwitchState; // 0x90
    bool mMercurySwitchState; // 0x94
    bool mForceMercurySwitch; // 0x95
    float mSyncOffset; // 0x98
    bool mDrivingPitchBendExternally; // 0x9c
    int mFillStartTick; // 0xa0
    int mLastFillEndTick; // 0xa4
    int mCodaStartTick; // 0xa8
    bool unkac; // 0xac
    bool mAutoplay; // 0xad
    bool mForceFill; // 0xae
    bool mNoFills; // 0xaf
    bool mFillAudio; // 0xb0
    FillLogic mFillLogic; // 0xb4
    bool mEnableWhammy; // 0xb8
    bool mEnableCapStrip; // 0xb9
};
