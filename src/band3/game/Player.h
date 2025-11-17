#pragma once
#include "CommonPhraseCapturer.h"
#include "PlayerBehavior.h"
#include "PracticeSectionProvider.h"
#include "bandobj/BandTrack.h"
#include "os/Debug.h"
#include "utl/SongPos.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/Performer.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "utl/HxGuid.h"
#include "beatmatch/FillInfo.h"

class BeatMaster;
class CommonPhraseCapturer;

enum EnabledState {
    kPlayerEnabled = 0,
    kPlayerDisabled = 1,
    kPlayerBeingSaved = 2,
    kPlayerDroppingIn = 3,
    kPlayerDisconnected = 4
};

class PersistentPlayerData {
public:
    float unk0;
    float unk4;
    int unk8;
    int unkc;
};

class Extent {
public:
    Extent(int x, int y) : unk0(x), unk4(y) {}
    int unk0;
    int unk4;
};

class PlayerParams {
public:
    PlayerParams();
    void SetVocals();

    float mCrowdSaveLevel; // 0x0
    float mMsToReturnFromBrink; // 0x4
    float mCrowdLossPerMs; // 0x8
    // (unverified) How many beats OD lasts
    float mDeployBeats;
    float mDeployBonus;
    float mSpotlightPhrase;
    float mDeployThreshold;
    float mSaveEnergy;
    float unk20;
    float mPointBonus; // 0x24
};

class Player : public Performer, public MsgSource {
public:
    Player(BandUser *, Band *, int, BeatMaster *);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~Player();
    virtual int GetAccumulatedScore() const;
    virtual int GetMultiplier(bool, int &, int &, int &) const;
    virtual bool IsNet() const;
    virtual int GetNumStars() const;
    virtual float GetNumStarsFloat() const;
    virtual float GetTotalStars() const;
    virtual bool PastFinalNote() const = 0;
    virtual void Poll(float, const SongPos &);
    virtual void AddPoints(float, bool, bool);
    virtual void Hit();
    virtual void Restart(bool);
    virtual void SetMultiplierActive(bool);
    virtual void SetQuarantined(bool);
    virtual Symbol GetStreakType() const;
    virtual int GetScoreForStars(int) const;
    virtual void FinalizeStats();

    virtual void DynamicAddBeatmatch();
    virtual void PostDynamicAdd();
    virtual void Leave();
    virtual void SetTrack(int trk) { mTrackNum = trk; }
    virtual void PostLoad(bool) {}
    virtual bool IsReady() const = 0;
    virtual void Start() = 0;
    virtual void StartIntro();
    virtual float GetSongMs() const;
    virtual void PollTrack() = 0;
    virtual void PollAudio() = 0;
    virtual void SetPaused(bool) = 0;
    virtual void SetRealtime(bool) = 0;
    virtual void SetMusicSpeed(float) = 0;
    virtual void Jump(float, bool) = 0;
    virtual void SetAutoplay(bool) = 0;
    virtual bool IsAutoplay() const = 0;
    virtual void SetAutoOn(bool) {}
    virtual void HookupTrack() = 0;
    virtual void UnHookTrack() = 0;
    virtual void EnableFills(float, bool) = 0;
    virtual void DisableFills() = 0;
    virtual void EnableDrumFills(bool) {}
    virtual bool FillsEnabled(int) = 0;
    virtual bool AreFillsForced() const { return false; }
    virtual void EnterCoda();
    virtual void ResetCodaPoints() {}
    virtual void AddCodaPoints() {}
    virtual int GetCodaPoints() { return 0; }
    virtual bool InFill() const;
    virtual void SetFillLogic(FillLogic);
    virtual bool DoneWithSong() const = 0;
    virtual bool AllowWarningState() const;
    virtual bool RebuildPhrases();
    virtual void Rollback(float, float);
    virtual void EnableController() {}
    virtual void DisableController() {}
    virtual void ConfigureBehavior() {}
    virtual bool CanDeployOverdrive() const;
    virtual float GetOverdrive() const { return 0; }
    virtual void CompleteCommonPhrase(bool, bool);
    virtual int GetIndividualMultiplier() const;
    virtual int GetMaxIndividualMultipler() const;
    virtual int GetBaseMaxPoints() const = 0;
    virtual int GetBaseMaxStreakPoints() const = 0;
    virtual int GetBaseBonusPoints() const = 0;
    virtual void SetSyncOffset(float) {}
    virtual void SavePersistentData(PersistentPlayerData &) const;
    virtual void LoadPersistentData(const PersistentPlayerData &);
    virtual int GetCodaFreestyleExtents(Extent &) const { return 0; }
    virtual bool InTambourinePhrase() const;
    virtual bool InFreestyleSection() const;
    virtual void PopupHelp(Symbol, bool);
    virtual bool AutoplaysCoda() const { return false; }
    virtual void SetCodaEndMs(float) {}
    virtual bool NeedsToOverrideBasePoints() const { return false; }
    virtual bool NeedsToSetCodaEnd() const { return false; }
    virtual void EnterAnnoyingMode() {}
    virtual void ClearScoreHistories() {}
    virtual void ChangeDifficulty(Difficulty);
    virtual void HandleNewSection(const PracticeSection &, int, int) = 0;
    virtual void SetEnabledState(EnabledState, BandUser *, bool);
    virtual void LocalSetEnabledState(EnabledState, int, BandUser *, bool);
    virtual void EnableSwings(bool) {}
    virtual bool DeployBandEnergyIfPossible(bool);
    virtual int LocalDeployBandEnergy();
    virtual bool ShouldDrainEnergy() const;
    virtual void IgnoreUntilRollback(float);
    virtual void UpdateLeftyFlip() {}
    virtual void UpdateVocalStyle() {}
    virtual void ResetController(bool) {}

    void DeterminePerformanceAwards();
    void DisableOverdrivePhrases();
    BandTrack *GetBandTrack() const;
    void PollMultiplier();
    void PollEnabledState(float);
    void PollTalking(int);
    void UpdateEnergy(const SongPos &);
    void StopDeployingBandEnergy(bool);
    void BroadcastScore();
    void AddBonusPoints(int);
    EnabledState GetEnabledStateAt(float) const;
    void SetEnergy(float);
    void DelayReturn(bool);
    bool Saveable() const;
    void Save(BandUser *, bool);
    void DisablePlayer(int);
    const UserGuid &GetUserGuid() const;
    int GetSlot() const;
    bool IsDeployingBandEnergy() const;
    void SetEnergyAutomatically(float);
    void DisablePhraseBonus();
    void EnablePhraseBonus();
    void AddEnergy(float);
    void PerformDeployBandEnergy(int, bool);
    void SubtractEnergy(float);
    void Deploy();
    void RemoteAlreadySaved(int);
    void SetEnergyFromNet(float, bool);
    void SetFinishedCoda();
    void CheckCrowdFailure();
    void UnisonMiss(int) const;
    void UnisonHit();
    void UpdateSectionStats(float, float);
    bool InRollback() const;

    int GetTrackNum() const { return mTrackNum; }
    TrackType GetTrackType() const { return mTrackType; }
    BandUser *GetUser() const { return mUser; }
    float GetBandEnergy() const { return mBandEnergy; }
    EnabledState GetEnabledState() const { return mEnabledState; }
    void SetTrackNum(int num) { mTrackNum = num; }
    void SetBlownCoda(void) {
        MILO_ASSERT(!mHasFinishedCoda, 197);
        mHasBlownCoda = true;
    }

    DataNode OnGetOverdriveMeter(DataArray *);
    DataNode OnSendNetGameplayMsg(DataArray *);
    DataNode OnSendNetGameplayMsgToPlayer(DataArray *);

    PlayerParams *mParams; // 0x228
    PlayerBehavior *mBehavior; // 0x22c
    BandUser *mUser; // 0x230
    CommonPhraseCapturer *mCommonPhraseCapturer; // 0x234
    bool mRemote; // 0x238
    String mPlayerName; // 0x23c
    int mTrackNum; // 0x248
    TrackType mTrackType; // 0x24c
    EnabledState mEnabledState; // 0x250
    int mTimesFailed; // 0x254
    float mEnableMs; // 0x258
    float unk25c;
    std::vector<Extent> unk260;
    bool mIsInCoda;
    float mBandEnergy; // 0x26c
    bool mDeployingBandEnergy; // 0x270
    int unk274;
    int unk278;
    bool mPhraseBonus; // 0x27c
    BeatMaster *mBeatMaster; // 0x280
    float unk284;
    bool unk288;
    int unk28c;
    bool unk290;
    int unk294;
    int unk298;
    float unk29c;
    int unk2a0;
    float unk2a4;
    bool mDisconnectedAtStart; // 0x2a8
    bool unk2a9;
    int unk2ac;
    bool unk2b0;
    bool mPermanentOverdrive; // 0x2b1
    bool mHasFinishedCoda; // 0x2b2
    bool mHasBlownCoda; // 0x2b3
    int unk2b4;
    int unk2b8;
    int unk2bc;
    int unk2c0;
    bool unk2c4;
};