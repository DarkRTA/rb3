#pragma once
#include "game/Player.h"
#include "rndobj/Overlay.h"

class VocalPlayer : public Player, public RndOverlay::Callback {
public:
    VocalPlayer(BandUser *, BeatMaster *, Band *, int, Performer *, int);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~VocalPlayer();
    virtual Symbol GetStarRating() const;
    virtual bool PastFinalNote() const;
    virtual void Poll(float, const SongPos &);
    virtual void Restart(bool);
    virtual float GetNotesHitFraction(bool *) const;
    virtual void RemoteUpdateCrowd(float);
    virtual void DynamicAddBeatmatch();
    virtual void PostDynamicAdd();
    virtual void Leave();
    virtual void SetTrack(int);
    virtual void PostLoad(bool);
    virtual bool IsReady() const;
    virtual void Start();
    virtual void StartIntro();
    virtual void PollTrack();
    virtual void PollAudio();
    virtual void SetPaused(bool);
    virtual void SetRealtime(bool);
    virtual void SetMusicSpeed(float);
    virtual void Jump(float, bool);
    virtual void SetAutoplay(bool);
    virtual bool IsAutoplay() const;
    virtual void HookupTrack();
    virtual void UnHookTrack();
    virtual void EnableFills(float, bool);
    virtual void DisableFills();
    virtual bool FillsEnabled(int);
    virtual bool DoneWithSong() const;
    virtual bool AllowWarningState() const;
    virtual bool RebuildPhrases();
    virtual void Rollback(float, float);
    virtual void EnableController();
    virtual void DisableController();
    virtual void ConfigureBehavior();
    virtual int GetBaseMaxPoints() const;
    virtual int GetBaseMaxStreakPoints() const;
    virtual int GetBaseBonusPoints() const;
    virtual bool InTambourinePhrase() const;
    virtual bool InFreestyleSection() const;
    virtual bool AutoplaysCoda() const;
    virtual void SetCodaEndMs(float);
    virtual bool NeedsToOverrideBasePoints() const;
    virtual bool NeedsToSetCodaEnd() const;
    virtual void ClearScoreHistories();
    virtual void ChangeDifficulty(Difficulty);
    virtual void HandleNewSection(const PracticeSection &, int, int);
    virtual void LocalSetEnabledState(EnabledState, int, BandUser *, bool);
    virtual int LocalDeployBandEnergy();
    virtual bool ShouldDrainEnergy() const;
    virtual void UpdateVocalStyle();

    bool ShowPitchCorrectionNotice() const;
    int PhraseScore() const;
    bool CanDeployCoda() const;
};