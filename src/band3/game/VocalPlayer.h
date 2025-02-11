#pragma once
#include "beatmatch/VocalNote.h"
#include "game/Performer.h"
#include "game/Player.h"
#include "game/Singer.h"
#include "game/TambourineManager.h"
#include "obj/Data.h"
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
    void SetDifficultyVariables(int);
    void RememberCurrentMics();
    float FramePhraseMeterFrac(int) const;
    int CalculatePhraseRating(float);
    VocalPhrase *CurrentPhrase() const;
    bool AtFirstPhrase() const;

    int NumSingers() const { return mSingers.size(); }
    int NumParts() const { return unk358.size(); }

    Performer *unk2cc; // 0x2cc
    bool unk2d0;
    int unk2d4; // 0x2d4 - vocaltrack*?
    bool unk2d8;
    float unk2dc;
    int unk2e0;
    int unk2e4;
    int unk2e8;
    float unk2ec;
    float unk2f0;
    float unk2f4;
    float unk2f8;
    int unk2fc;
    float unk300;
    float unk304;
    float unk308;
    int unk30c;
    int unk310;
    int unk314;
    int unk318;
    int unk31c;
    DataArray *unk320;
    DataArray *unk324;
    int unk328;
    int unk32c;
    DataArray *unk330;
    DataArray *unk334;
    float unk338;
    bool unk33c;
    float unk340;
    bool unk344;
    float mTuningOffset; // 0x348
    float unk34c;
    std::vector<Singer *> mSingers; // 0x350
    std::vector<int> unk358; // should be vec of VocalPart*s
    std::vector<int> unk360;
    int unk368;
    int unk36c;
    int unk370;
    int unk374;
    float unk378;
    int unk37c;
    RndOverlay *mOverlay; // 0x380
    int unk384;
    bool unk388;
    TambourineManager mTambourineManager; // 0x38c
    float unk414;
    int unk418;
    float unk41c;
    int unk420;
    int unk424;
};