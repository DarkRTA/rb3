#pragma once
#include "beatmatch/VocalNote.h"
#include "game/Performer.h"
#include "game/Player.h"
#include "game/Singer.h"
#include "game/TambourineManager.h"
#include "obj/Data.h"
#include "rndobj/Overlay.h"
#include "game/VocalPart.h"
#include "synth/MicManagerInterface.h"
#include "utl/MakeString.h"
#include "utl/TextFileStream.h"

class VocalTrack;

class VocalFrameSpewData {
public:
    class VocalFrameSingerData {
    public:
        VocalFrameSingerData() : unk0(0), unk4(0), unk8(-1) {}
        float unk0;
        float unk4;
        int unk8;
    };
    class VocalFramePartData {
    public:
        VocalFramePartData()
            : unk0(0), unk4(0), unk8(0), unkc(0), unk10(0), unk14(0), unk18(0), unk1c(0) {
        }
        float unk0;
        float unk4;
        float unk8;
        float unkc;
        float unk10;
        float unk14;
        int unk18;
        int unk1c;
    };

    VocalFrameSpewData(int singers, int parts) : mMs(0), mCompMs(0) {
        mSingerData.resize(singers);
        mPartData.resize(parts);
    }
    ~VocalFrameSpewData() {}
    void OutputHeader(TextFileStream &ts) const {
        ts << "ms" << "\t";
        ts << "comp ms" << "\t";
        for (int i = 0; i < mSingerData.size(); i++) {
            String str(MakeString("s%d", i));
            ts.Print(str.c_str());
            ts << " pitch (n)" << "\t";
            ts.Print(str.c_str());
            ts << " energy (%)" << "\t";
            ts.Print(str.c_str());
            ts << " matched part" << "\t";
        }
        for (int i = 0; i < mPartData.size(); i++) {
            String str(MakeString("p%d", i));
            ts.Print(str.c_str());
            ts << " pitch (n)" << "\t";
            ts.Print(str.c_str());
            ts << " uncapped frame points (p)" << "\t";
            ts.Print(str.c_str());
            ts << " points cap (p)" << "\t";
            ts.Print(str.c_str());
            ts << " hit percentage (%)" << "\t";
            ts.Print(str.c_str());
            ts << " note weight slice" << "\t";
            ts.Print(str.c_str());
            ts << " note multiplier" << "\t";
            ts.Print(str.c_str());
            ts << " phrase points (p)" << "\t";
            ts.Print(str.c_str());
            ts << " phrase max points (p)" << "\t";
        }
        ts << "\n";
    }

    float mMs; // 0x0
    float mCompMs; // 0x4
    std::vector<VocalFrameSingerData> mSingerData; // 0x8
    std::vector<VocalFramePartData> mPartData; // 0x10
};

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
    virtual float UpdateOverlay(RndOverlay *, float);

    bool ShowPitchCorrectionNotice() const;
    int PhraseScore() const;
    bool CanDeployCoda() const;
    void SetDifficultyVariables(int);
    void RememberCurrentMics();
    float FramePhraseMeterFrac(int) const;
    int CalculatePhraseRating(float);
    VocalPhrase *CurrentPhrase() const;
    bool AtFirstPhrase() const;
    bool ScoringEnabled() const;
    void EnablePartScoring(int, bool);
    void HitCoda();
    void BuildPhrases(bool);
    bool ToggleFrameSpew();
    bool PressingToTalk();
    void SendCanChat(bool);
    void AddAccuracyStat(int);
    void AddScoreStreakStat(float);
    void AddBandContributionStat(float);
    void AddOverdriveStat(float);
    void AddTambourinePointsStat(float);
    void AddHarmonyStat(int);
    void AddTambourineSeen();
    void AddTambourineHit();
    void EndTambourineSection(int);
    void SwapAmbiguousPoints(float, int, int);

    int NumSingers() const { return mSingers.size(); }
    int NumParts() const { return mVocalParts.size(); }

    Performer *mBandPerformer; // 0x2cc
    bool unk2d0;
    VocalTrack *mTrack; // 0x2d4
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
    float mPitchMaximumDistance; // 0x30c
    float mSynapseProximitySolo; // 0x310
    float mSynapseFocusSolo; // 0x314
    float mSynapseProximityHarmony; // 0x318
    float mSynapseFocusHarmony; // 0x31c
    DataArray *unk320;
    DataArray *unk324;
    int unk328;
    int mPhraseValue; // 0x32c
    DataArray *unk330;
    DataArray *unk334;
    float unk338;
    bool unk33c;
    float mCodaEndMs; // 0x340
    bool unk344;
    float mTuningOffset; // 0x348
    float unk34c;
    std::vector<Singer *> mSingers; // 0x350
    std::vector<VocalPart *> mVocalParts; // 0x358
    std::vector<MicClientID> unk360;
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
    VocalFrameSpewData *mFrameSpewData; // 0x420
    TextFileStream *mFrameSpewStream; // 0x424
};