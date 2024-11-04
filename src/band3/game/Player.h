#pragma once
#include "PracticeSectionProvider.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/Performer.h"
#include "obj/MsgSource.h"

class BeatMaster;

enum FillLogic {

};

enum EnabledState {

};

class PersistentPlayerData {

};

class Extent {

};

class Player : public Performer, public MsgSource {
public:
    Player(BandUser*, Band*, int, BeatMaster*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~Player();
    virtual int GetAccumulatedScore() const;
    virtual int GetMultiplier(bool, int&, int&, int&) const;
    virtual bool IsNet() const;
    virtual int GetNumStars() const;
    virtual float GetNumStarsFloat() const;
    virtual float GetTotalStars() const;
    virtual bool PastFinalNote() const = 0;
    virtual void Poll(float, const SongPos&);
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
    virtual void SetTrack(int);
    virtual void PostLoad(bool);
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
    virtual void SetAutoOn(bool);
    virtual void HookupTrack() = 0;
    virtual void UnHookTrack() = 0;
    virtual void EnableFills(float, bool) = 0;
    virtual void DisableFills() = 0;
    virtual void EnableDrumFills(bool);
    virtual bool FillsEnabled(int) = 0;
    virtual bool AreFillsForced() const;
    virtual void EnterCoda();
    virtual void ResetCodaPoints();
    virtual void AddCodaPoints();
    virtual int GetCodaPoints();
    virtual bool InFill() const;
    virtual void SetFillLogic(FillLogic);
    virtual bool DoneWithSong() const = 0;
    virtual bool AllowWarningState() const;
    virtual bool RebuildPhrases();
    virtual void Rollback(float, float);
    virtual void EnableController();
    virtual void DisableController();
    virtual void ConfigureBehavior();
    virtual bool CanDeployOverdrive() const;
    virtual float GetOverdrive() const;
    virtual void CompleteCommonPhrase(bool, bool);
    virtual int GetIndividualMultiplier() const;
    virtual int GetMaxIndividualMultipler() const;
    virtual int GetBaseMaxPoints() const = 0;
    virtual int GetBaseMaxStreakPoints() const = 0;
    virtual int GetBaseBonusPoints() const = 0;
    virtual void SetSyncOffset(float);
    virtual void SavePersistentData(PersistentPlayerData&) const;
    virtual void LoadPersistentData(const PersistentPlayerData&);
    virtual int GetCodaFreestyleExtents(Extent&) const;
    virtual bool InTambourinePhrase() const;
    virtual bool InFreestyleSection() const;
    virtual void PopupHelp(Symbol, bool);
    virtual bool AutoplaysCoda() const;
    virtual void SetCodaEndMs(float);
    virtual bool NeedsToOverrideBasePoints() const;
    virtual bool NeedsToSetCodaEnd() const;
    virtual void EnterAnnoyingMode();
    virtual void ClearScoreHistories();
    virtual void ChangeDifficulty(Difficulty);
    virtual void HandleNewSection(const PracticeSection&, int, int) = 0;
    virtual void SetEnabledState(EnabledState, BandUser*, bool);
    virtual void LocalSetEnabledState(int, EnabledState, BandUser*, bool);
    virtual void EnableSwings(bool);
    virtual bool DeployBandEnergyIfPossible(bool);
    virtual int LocalDeployBandEnergy();
    virtual bool ShouldDrainEnergy() const;
    virtual void IgnoreUntilRollback(float);
    virtual void UpdateLeftyFlip();
    virtual void UpdateVocalStyle();
    virtual void ResetController(bool);

    void DeterminePerformanceAwards();
    TrackType GetTrackType() const { return unk_tracktype; }

    int unk_player;
    int unk22c;
    BandUser* unk230;
    int unk234;
    int unk238;
    int unk23c;
    int unk240;
    int unk244;
    int unk248;
    TrackType unk_tracktype;
};
