#pragma once
#include "beatmatch/VocalNote.h"
#include "game/Singer.h"

class VocalPlayer;

class VocalPart {
public:
    VocalPart(VocalPlayer *, int);
    ~VocalPart();

    void SetDifficultyVariables(int);
    void PostLoad();
    void CalcNoteWeights();
    void Start();
    void StartIntro();
    void UpdateSongMinMaxPitch();
    void Restart(bool);
    void UpdateMinMaxPitch(const VocalPhrase *const &);
    void SetPaused(bool);
    void Jump(float, bool);
    void LocalDeployBandEnergy();
    void EnableScoring(bool);
    bool ScoringEnabled() const;
    void SetRemotePhraseMeterFrac(float);
    bool InTambourinePhrase() const;
    void ForcePhrasePointDelta(float);
    float FramePhraseMeterFrac() const;
    int GetSpotlightPhrase() const;
    void SetPhraseScoreMultiplier(float);
    void SetPhraseRank(int);
    bool InEmptyPhrase() const;
    bool InPlayablePhrase() const;
    void HandlePhraseEnd(int &, float &, float &, int &, float);
    float GetOverallPartHitPercentage() const;
    int CurrentPhraseIndex() const;
    void OnGameOver();
    const VocalPhrase *GetFirstPhraseMarker() const;
    const VocalPhrase *GetNextPhraseMarker(const VocalPhrase *const &) const;
    bool IsPhraseMarkerAtEnd(const VocalPhrase *const &) const;
    bool IsEmptyPhrase(const VocalPhrase *const &) const;
    void Rollback(float, float);
    float GetPartHitPercentage(const std::vector<VocalPhrase> &, int, int) const;
    void ResetScoring();
    float CalcPhraseScoreMax(const VocalPhrase *const &) const;
    void AddScore(const VocalScoreCache &);
    void AddPhrasePoints(float);
    void SetFirstPhraseMsToScore(float);
    void SetVocalNoteList(VocalNoteList *);

    int PartIndex() const { return mPartIndex; }
    float MaxPhraseScore() const { return mPhraseScoreMax; }
    bool InFreestyleSection() const { return mInFreestyleSection; }

    static bool FramePhraseMeterFracSorter(const VocalPart *, const VocalPart *);

    VocalPlayer *mPlayer; // 0x0
    int mPartIndex; // 0x4
    VocalNoteList *mVocalNoteList; // 0x8
    std::pair<float, float> *mFreestyleSection; // 0xc
    std::vector<float> mNoteWeights; // 0x10
    int unk18;
    int unk1c;
    float unk20;
    int unk24;
    int unk28;
    float mRemotePhraseMeterFrac; // 0x2c
    float mPhraseScorePartMultiplier; // 0x30
    float mPhraseScoreMax; // 0x34
    int unk38;
    int unk3c;
    float mPhraseScore; // 0x40
    float unk44;
    float unk48;
    float unk4c;
    int unk50;
    float unk54;
    int unk58;
    const VocalPhrase *mThisPhrase; // 0x5c
    int mPhraseValue; // 0x60
    float mSlop; // 0x64
    float mPitchSigma; // 0x68
    float mPitchMaximumDistance; // 0x6c
    float mPitchHitMultiplier; // 0x70
    float mNonPitchHitMultiplier; // 0x74
    float mShortNoteThresh; // 0x78
    float mShortNoteMult; // 0x7c
    float mNoteLengthFactor; // 0x80
    float unk84;
    int unk88;
    int mSpotlightPhraseID; // 0x8c
    float mNonPitchEasyMultiplier; // 0x90
    float mPhraseScoreCapGrowth; // 0x94
    int unk98;
    float unk9c;
    float unka0;
    float unka4;
    float unka8;
    bool mInFreestyleSection; // 0xac
    bool unkad;
    float unkb0;
    bool unkb4;
    float mFirstPhraseMsToScore; // 0xb8
    float unkbc;
    Singer *mBestSinger; // 0xc0
    float mBestSingerPitchDistance; // 0xc4
    int unkc8;
    bool mScoringEnabled; // 0xcc
    int mPhraseRank; // 0xd0
    float mTalkyEnergyThreshold; // 0xd4
};