#pragma once
#include "bandtrack/GemManager.h"
#include "bandtrack/GemTrack.h"
#include "beatmatch/BeatMatchController.h"
#include "beatmatch/BeatMatchSink.h"
#include "beatmatch/BeatMatcher.h"
#include "game/GuitarFx.h"
#include "game/HeldNote.h"
#include "game/KeysFx.h"
#include "game/Player.h"
#include "game/StatCollector.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "rndobj/Overlay.h"
#include "synth/FxSendPitchShift.h"

class BandPerformer;

class DeltaTracker {
public:
    DeltaTracker() : mCur(0) {}

    void PrintDeltas() {
        if (mCur > 0) {
            std::vector<float> fvec;
            int num = 999;
            if (mCur <= 999)
                num = mCur;
            fvec.resize(num);
            memcpy(fvec.begin(), mDeltas, num * sizeof(float));
            std::sort(fvec.begin(), fvec.begin() + num);
            for (int i = 0; i < num; i++) {
                MILO_LOG("%d %.3f\n", i, fvec[i]);
            }
            MILO_LOG("median is %.3f\n", fvec[num / 2]);
        } else
            MILO_LOG("No samples to be had\n");
        mCur = 0;
    }

    float mDeltas[1000];
    int mCur;
};

class GemStatus {
public:
    GemStatus() : mHits(0), mMisses(0) {}

    // is hit: 0x1
    // is cymbal: 0x20
    // is solo: 0x80

    // 0x40? 0xe?

    // from GDRB:
    // missed: 0x2
    // ignored: 0x8

    bool GetHit(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 1;
        }
        return mask;
    }

    bool Get0x4(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 4;
        }
        return mask;
    }

    bool GetEncountered(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 0xF;
        }
        return mask;
    }

    bool Get0xD(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 0xD;
        }
        return mask;
    }

    bool GetHopoed(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 0x10;
        }
        return mask;
    }

    bool GetIgnored(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 0x8;
        }
        return mask;
    }

    bool HasDealtWithGem(int idx) {
        int mask;
        if (idx == -1)
            mask = 0;
        else {
            mask = mGems[idx] & 0x9;
        }
        return mask;
    }

    void SetIgnored(int idx) {
        if (idx != -1) {
            mGems[idx] |= 8;
        }
    }

    void SetHit(int idx) {
        if (idx != -1) {
            mGems[idx] |= 1;
        }
    }

    void Set0x2(int idx) {
        if (idx != -1) {
            mGems[idx] |= 2;
        }
    }

    void Set0x40(int idx) {
        if (idx != -1) {
            mGems[idx] |= 0x40;
        }
    }

    void Clear() {
        for (int i = 0; i < mGems.size(); i++) {
            mGems[i] = 0;
        }
        mHits = 0;
        mMisses = 0;
    }

    float GetNotesHitFraction(bool *bptr) const {
        float total = mHits + mMisses;
        if (bptr)
            *bptr = total > 0;
        return total == 0 ? 0 : mHits / total;
    }

    void Resize(int num) { mGems.resize(num); }
    int NumHits() const { return mHits; }
    int NumMisses() const { return mMisses; }
    int GetSize() const { return mGems.size(); }

    std::vector<unsigned char> mGems; // 0x0
    int mHits; // 0x8
    int mMisses; // 0xc
};

class GemPlayer : public Player, public BeatMatchSink {
public:
    class UpcomingFretRelease {
    public:
        int unk0; // slot?
        float unk4; // ms?
    };
    GemPlayer(BandUser *, BeatMaster *, Band *, int, BandPerformer *);
    virtual ~GemPlayer();
    virtual DataNode Handle(DataArray *, bool);
    virtual int CodaScore() const { return mCodaPoints; }
    virtual Symbol GetStarRating() const;
    virtual int GetNumStars() const;
    virtual bool PastFinalNote() const;
    virtual void Poll(float, const SongPos &);
    virtual void Restart(bool);
    virtual float GetNotesHitFraction(bool *) const;
    virtual void FinalizeStats();

    virtual void DynamicAddBeatmatch();
    virtual void PostDynamicAdd();
    virtual void Leave();
    virtual void SetTrack(int);
    virtual void PostLoad(bool);
    virtual bool IsReady() const;
    virtual void Start();
    virtual void PollTrack();
    virtual void PollAudio();
    virtual void SetPaused(bool);
    virtual void SetRealtime(bool);
    virtual void SetMusicSpeed(float);
    virtual void Jump(float, bool);
    virtual void SetAutoplay(bool);
    virtual bool IsAutoplay() const;
    virtual void SetAutoOn(bool);
    virtual void HookupTrack();
    virtual void UnHookTrack();
    virtual void EnableFills(float, bool);
    virtual void DisableFills();
    virtual void EnableDrumFills(bool);
    virtual bool FillsEnabled(int);
    virtual bool AreFillsForced() const { return mForceFill; }
    virtual void EnterCoda();
    virtual void ResetCodaPoints();
    virtual void AddCodaPoints();
    virtual int GetCodaPoints() { return mCodaPoints; }
    virtual bool InFill() const { return mFill; }

    virtual void SetFillLogic(FillLogic);
    virtual bool DoneWithSong() const;
    virtual void Rollback(float, float);
    virtual void EnableController();
    virtual void DisableController();
    virtual void ConfigureBehavior();
    virtual int GetBaseMaxPoints() const;
    virtual int GetBaseMaxStreakPoints() const;
    virtual int GetBaseBonusPoints() const;
    virtual void SetSyncOffset(float);
    virtual int GetCodaFreestyleExtents(Extent &) const;
    virtual void EnterAnnoyingMode() { mAnnoyingMode = true; }
    virtual void ChangeDifficulty(Difficulty);
    virtual void HandleNewSection(const PracticeSection &, int, int);
    virtual void LocalSetEnabledState(EnabledState, int, BandUser *, bool);
    virtual void EnableSwings(bool);
    virtual void IgnoreUntilRollback(float);
    virtual void UpdateLeftyFlip();
    virtual void ResetController(bool);

    virtual void SeeGem(int, float, int);
    virtual void Swing(int, int, float, bool, bool);
    virtual void Hit(int, float, int, unsigned int, GemHitFlags);
    virtual void Miss(int, int, float, int, int, GemHitFlags);
    virtual void SpuriousMiss(int, int, float, int);
    virtual void Pass(int, float, int, bool);
    virtual void Ignore(int, float, int, const UserGuid &);
    virtual void ImplicitGem(int, float, int, const UserGuid &);

    virtual void SetTrack(const UserGuid &, int) {}
    virtual void FretButtonDown(int, float);
    virtual void FretButtonUp(int, float);
    virtual void MercurySwitch(bool, float);
    virtual void FilteredWhammyBar(float);
    virtual void SwingAtHopo(int, float, int);
    virtual void Hopo(int, float, int);
    virtual void ReleaseGem(int, float, int, float);
    virtual void SetCurrentPhrase(int, const PhraseInfo &) {}
    virtual void NoCurrentPhrase(int) {}
    virtual void FillSwing(int, int, int, int, bool);
    virtual void FillReset();
    virtual void FillComplete(int, int);
    virtual void NoteOn(int);
    virtual void NoteOff(int);
    virtual void PlayNote(int);
    virtual void OutOfRangeSwing();

    virtual int GetNumRolls() const;
    virtual void GetRollInfo(int, int &, int &) const;
    virtual int GetNumTrills() const;
    virtual void GetTrillInfo(int, int &, int &) const;
    virtual void FillInProgress(int, int);
    virtual int GetTrackSlot(int) const;
    virtual void SwingHook(int, int, float, bool, bool) {}
    virtual void HitHook(int, float, int, unsigned int, GemHitFlags) {}
    virtual void MissHook(int, int, float, int, int) {}
    virtual void PassHook(int, float, int, bool) {}
    virtual void SeeGemHook(int, float, int) {}

    int GetRGFret(int) const;
    int GetMaxSlots() const;
    void PrintAddHead(int, int, int, int, int);
    void PrintMsg(const char *);
    void SetGuitarFx();
    void SetDrumKitBank(ObjectDir *);
    void UpdateGameCymbalLanes();
    void IgnoreGemsUntil(int);
    void DropIn(int);
    void InputReceived();
    void FinaleSwing(int);
    void LocalFinaleSwing(int);
    bool CanFlail(float);
    bool HandleSpecialMissScenarios(int, float);
    void PlayDrum(int, int, float, int);
    void PlayMissSound(int);
    void ShowFillHit(int);
    void LocalShowFillHit(int, int, bool);
    void OnRemoteFillHit(int, int, bool);
    void IgnoreGem(int);
    void ForceFill(bool);
    HeldNote *FindHeldNoteFromSlot(int);
    void OnSetWhammyOverdriveEnabled(bool);
    void OnSetMercurySwitchEnabled(bool);
    void OnResetCodaPoints();
    int OnGetPercentHit() const;
    int OnGetGemResult(int);
    bool OnGetGemIsSustained(int);
    void OnGameOver();
    void OnDisableController();
    void OnRemoteHit(int, int, float);
    void OnRemotePenalize(int, int, float);
    void OnRemoteCodaHit(int, int);
    void OnRemoteWhammy(float);
    void OnRemoteFill(bool);
    void OnRemoteHitLastCodaGem(int);
    void OnRemoteBlowCoda();
    void LocalSoloStart();
    void LocalSoloHit(int);
    void LocalSoloEnd(int, int);
    void LocalSetGuitarFx(int);
    void OnStartOverdrive();
    void OnStopOverdrive();
    void OnRefreshTrackButtons();
    bool InFillNow();
    bool InTrill(int) const;
    bool InRGTrill(int) const;
    bool InRoll(int) const;
    bool InRGRoll(int) const;
    void PrintHopoStats();
    void SetFilling(bool, int);
    void HandleCommonPhraseNote(int, int);
    void JumpReset(float);
    float OnGetPercentHitGemsPractice(int, float, float) const;
    void FinishAllHeldNotes(float);
    void SetReverb(bool);
    FxSendPitchShift *GetPitchShift();
    void GetPlayerState(PlayerState &) const;
    void DisableFillsCompletely();
    void ResetGemStates(float);
    void SetPitchShiftRatio(float);
    float CycleAutoplayAccuracy();
    void SetAutoplayAccuracy(float);
    bool HasDealtWithGem(int);
    void RecordTrillStats();
    void UpdateSectionStats();
    void GetGemsHit(int, int, int &, int &);
    void HandleFirstGemAfterRollback(int);
    bool HasAnyActiveHeldNotes() const;
    bool InIgnorableFill(int);
    bool IgnoreGemsAt(int);
    void UpdateCrowdMeter(float, int);
    void SendPenalize();
    void Penalize(float, int, float);
    void HandleSoloGem(int, bool, float, bool);
    bool ShouldPenalizeGem(int) const;
    void CheckHeldNotes(float);
    void FinishHeldNote(float, HeldNote &);
    void PrintFinishHeldNote();
    HeldNote &GetUnusedHeldNote();
    HeldNote *FindHeldNoteFromGemID(int);
    HeldNote *FindFirstActiveHeldNote();
    void AddHeadPoints(float, int, int, GemHitFlags);
    bool ToggleNoFills();
    void GetSoloData(int, float &, float &, int &);
    void SoloEnd();
    void SendWhammyBar(float);
    bool AllCodaGemsHit() const;
    void CodaHit(float, int);
    void SetAnnoyingMode(bool);
    void SetRemoteAnnoyingMode(bool);
    void CheckFretReleases(float);
    void RemoveFretReleasesInSlot(int);
    GemStatus *GetGemStatus() const { return mGemStatus; }

    const SongPos &GetSongPos() const { return mMatcher->mSongPos; }

    Performer *mBandPerformer; // 0x2cc
    GemStatus *mGemStatus; // 0x2d0
    DataArray *mDrumSlotWeights; // 0x2d4
    Symbol mDrumSlotWeightMapping; // 0x2d8
    DataArray *mDrumCymbalPointBonus; // 0x2dc
    unsigned int mGameCymbalLanes; // 0x2e0
    std::vector<HeldNote> mHeldNotes; // 0x2e4
    bool mFill; // 0x2ec
    bool mForceFill; // 0x2ed
    int mLastFillHitTick; // 0x2f0
    int unk2f4;
    int mNumFillSwings; // 0x2f8
    int mNumCrashFillReadyHits; // 0x2fc
    bool mUseFills; // 0x300
    bool unk301;
    std::pair<int, int> mTrillSlots; // 0x304
    int unk30c;
    int unk310;
    bool unk314;
    bool unk315;
    bool unk316;
    int mCodaPoints; // 0x318
    float mLastCodaSwing[6]; // 0x31c
    float mCodaPointRate; // 0x334
    float mCodaMashPeriod; // 0x338
    bool mMercurySwitchEnabled; // 0x33c
    bool unk33d;
    bool mWhammyOverdriveEnabled; // 0x33e
    RndOverlay *mOverlay; // 0x340
    RndOverlay *mGuitarOverlay; // 0x344
    bool unk348;
    float mWhammySpeedThreshold; // 0x34c
    float mWhammySpeedTimeout; // 0x350
    float unk354;
    float unk358;
    float unk35c;
    float mLastTimeWhammyVelWasHigh; // 0x360
    float unk364;
    GemTrack *mTrack; // 0x368
    BeatMatchController *mController; // 0x36c
    Symbol mControllerType; // 0x370
    BeatMatcher *mMatcher; // 0x374
    float mSyncOffset; // 0x378
    GuitarFx *mGuitarFx; // 0x37c
    KeysFx *mKeysFx; // 0x380
    int mFxPos; // 0x384
    bool unk388;
    FxSendPitchShift *mPitchShift; // 0x38c
    float unk390;
    float unk394;
    int unk398;
    int unk39c;
    int unk3a0;
    bool unk3a4;
    bool unk3a5;
    bool unk3a6;
    bool unk3a7;
    bool unk3a8;
    float unk3ac;
    float mAutoMissSoundTimeoutMs; // 0x3b0
    float mFirstGemMs; // 0x3b4
    bool mAnnoyingMode; // 0x3b8
    bool unk3b9;
    int unk3bc;
    int unk3c0;
    int mAutoMissSoundTimeoutGems; // 0x3c4
    int mAutoMissSoundTimeoutGemsRemote; // 0x3c8
    StatCollector mStatCollector; // 0x3cc
    bool unk3d8;
    int unk3dc;
    bool unk3e0;
    bool unk3e1;
    int mSectionStartHitCount; // 0x3e4
    int mSectionStartMissCount; // 0x3e8
    float mSectionStartScore; // 0x3ec
    int mSustainsReleased; // 0x3f0
    int mSustainHeld; // 0x3f4
    int mSustainsReleasedBeforePopup; // 0x3f8
    std::vector<UpcomingFretRelease> mUpcomingFretReleases; // 0x3fc
    int unk404;
    bool unk408;
};