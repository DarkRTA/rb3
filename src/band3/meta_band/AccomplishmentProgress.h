#pragma once
#include "obj/Object.h"
#include "meta/FixedSizeSaveable.h"
#include "tour/TourGameRules.h"
#include "game/Defines.h"
#include "game/GameMessages.h"

class BandProfile;

class GamerAwardStatus : public FixedSizeSaveable {
public:
    GamerAwardStatus();
    virtual ~GamerAwardStatus();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    static int SaveSize(int);

    int unk8; // 0x8
    int unkc; // 0xc
    bool unk10; // 0x10
};

class AccomplishmentProgress : public Hmx::Object, public FixedSizeSaveable {
public:
    AccomplishmentProgress(BandProfile*);
    virtual ~AccomplishmentProgress();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void Clear();
    int GetToursPlayed(Symbol) const;
    void UpdateTourPlayedForAllParticipants(Symbol);
    int GetToursGotAllStars(Symbol) const;
    void SetToursGotAllStars(Symbol, int);
    int GetQuestCompletedCount(TourGameType) const;
    void SetQuestCompletedCount(TourGameType, int);
    bool AddAccomplishment(Symbol);
    bool IsAccomplished(Symbol) const;
    void NotifyPlayerOfAccomplishment(Symbol, const char*);
    void NotifyPlayerOfCategoryComplete(Symbol);
    void NotifyPlayerOfGroupComplete(Symbol);
    bool AddAward(Symbol, Symbol);
    void Poll();
    void UpdateTourPlayed(Symbol);
    void UpdateMostStars(Symbol, int);
    int GetCurrentValue(Symbol);
    void ClearStepTrackingMap();
    void SetCurrentValue(Symbol, int);
    int GetNumCompleted() const;
    bool HasNewAwards() const;
    Symbol GetFirstNewAwardReason() const;
    Symbol GetFirstNewAward() const;
    void ClearFirstNewAward();
    bool HasNewRewardVignettes() const;
    Symbol GetFirstNewRewardVignette() const;
    void ClearFirstNewRewardVignette();
    bool HasNewRewardVignetteFestival() const;
    void ClearNewRewardVignetteFestival();
    int GetNumCompletedInCategory(Symbol) const;
    int GetNumCompletedInGroup(Symbol) const;
    void SetMetaScore(int);
    void AddNewRewardVignette(Symbol);
    bool IsUploadDirty() const;
    bool HasAward(Symbol) const;
    void SetHardCoreStatusUpdatePending(bool);
    bool IsHardCoreStatusUpdatePending();
    void SendHardCoreStatusUpdateToRockCentral();
    void HandlePendingGamerRewards();
    int GetMetaScore() const;
    int GetTotalGemsSmashed() const;
    int GetTotalGuitarHopos() const;
    int GetTotalBassHopos() const;
    int GetTotalUpstrums() const;
    int GetTotalTimesRevived() const;
    int GetTotalSaves() const;
    int GetTotalAwesomes() const;
    int GetTotalDoubleAwesomes() const;
    int GetTotalTripleAwesomes() const;
    int GetCareerFills() const;
    int GetBestStars(ScoreType, Difficulty) const;
    int GetBestStarsAtMinDifficulty(ScoreType, Difficulty) const;
    int GetBestSolo(ScoreType, Difficulty) const;
    int GetBestSoloAtMinDifficulty(ScoreType, Difficulty) const;
    int GetBestAccuracy(ScoreType, Difficulty) const;
    int GetBestAccuracyAtMinDifficulty(ScoreType, Difficulty) const;
    int GetBestHoposPercent(ScoreType, Difficulty) const;
    int GetBestHoposPercentAtMinDifficulty(ScoreType, Difficulty) const;
    int GetBestStreak(ScoreType) const;
    int GetBestScore(ScoreType) const;
    int GetBestBandScore() const;
    int GetTotalOverdriveDeploys(ScoreType) const;
    int GetTotalOverdriveTime(ScoreType) const;
    int GetTotalOverdrivePhrases(ScoreType) const;
    int GetTotalUnisonPhrases(ScoreType) const;
    int GetMostOverdriveDeploys(ScoreType) const;
    int GetMostOverdriveTime(ScoreType) const;
    int GetMostUnisonPhrases(ScoreType) const;
    int GetTotalBREsHit(ScoreType) const;
    int GetBestPercussionPercent(Difficulty) const;
    int GetBestPercussionPercentAtMinDifficulty(Difficulty) const;
    int GetTotalDrumRollCount(Difficulty) const;
    int GetTotalDrumRollCountAtMinDifficulty(Difficulty) const;
    int GetTotalProDrumRollCount(Difficulty) const;
    int GetTotalProDrumRollCountAtMinDifficulty(Difficulty) const;
    int GetBestKickPercent(Difficulty) const;
    int GetBestKickPercentAtMinDifficulty(Difficulty) const;
    int GetBestProKickPercent(Difficulty) const;
    int GetBestProKickPercentAtMinDifficulty(Difficulty) const;
    int GetBestDrumRollPercent(Difficulty) const;
    int GetBestDrumRollPercentAtMinDifficulty(Difficulty) const;
    int GetBestSoloButtonPercent(Difficulty) const;
    int GetBestSoloButtonPercentAtMinDifficulty(Difficulty) const;
    int GetTotalSongsPlayed() const;
    int GetTourTotalSongsPlayed() const;
    int GetToursPlayed() const;
    int GetTourMostStars(Symbol) const;
    int GetToursGotAllStars() const;
    int GetQuestCompletedCount() const;
    void SetTotalSongsPlayed(int);
    void SetTourTotalSongsPlayed(int);
    void SetToursPlayed(Symbol, int);
    void SetMostStars(Symbol, int);
    bool InqGoalLeaderboardData(std::map<Symbol, int>&) const;
    void HandleUploadStarted();
    // // int GetTotalGemsSmashed() const;
    // // int GetTotalGuitarHopos() const;
    // // int GetTotalBassHopos() const;
    // // int GetTotalUpstrums() const;
    // // int GetTotalTimesRevived() const;
    // // int GetTotalSaves() const;
    // // int GetTotalAwesomes() const;
    // // int GetTotalDoubleAwesomes() const;
    // // int GetTotalTripleAwesomes() const;
    // // int GetBestStarsAtMinDifficulty(ScoreType, Difficulty) const;
    // // int GetBestSoloAtMinDifficulty(ScoreType, Difficulty) const;
    // // int GetBestAccuracyAtMinDifficulty(ScoreType, Difficulty) const;
    // // int GetBestStreak(ScoreType) const;
    // // int GetTotalOverdriveDeploys(ScoreType) const;
    // // int GetTotalOverdriveTime(ScoreType) const;
    // // int GetTotalOverdrivePhrases(ScoreType) const;
    // // int GetTotalUnisonPhrases(ScoreType) const;
    // // int GetMostOverdriveDeploys(ScoreType) const;
    // // int GetMostOverdriveTime(ScoreType) const;
    // int GetMostUnisonPhrases(ScoreType) const;
    // int GetTotalBREsHit(ScoreType) const;
    // int GetTotalSongsPlayed() const;
    // int GetTourTotalSongsPlayed() const;
    // int GetBestPercussionPercentAtMinDifficulty(Difficulty) const;
    // int GetTotalDrumRollCountAtMinDifficulty(Difficulty) const;
    // int GetTotalProDrumRollCountAtMinDifficulty(Difficulty) const;
    // int GetBestKickPercentAtMinDifficulty(Difficulty) const;
    // int GetBestProKickPercentAtMinDifficulty(Difficulty) const;
    // int GetBestDrumRollPercentAtMinDifficulty(Difficulty) const;
    // int GetBestSoloButtonPercentAtMinDifficulty(Difficulty) const;
    // int GetBestHoposPercentAtMinDifficulty(ScoreType, Difficulty) const;
    // int GetCareerFills() const;
    // int GetBestScore(ScoreType) const;
    // int GetBestBandScore() const;

    DataNode OnMsg(const RockCentralOpCompleteMsg&);

    static int SaveSize(int);

    std::map<Symbol, int> mStepTrackingMap; // 0x24
    BandProfile* mParentProfile; // 0x3c
    bool mHardCoreStatusUpdatePending; // 0x40
    std::list<GamerAwardStatus*> mGamerAwardStatusList; // 0x44
    std::set<Symbol> mAccomplishments; // 0x4c
    std::set<Symbol> unk64; // 0x64
    std::vector<Symbol> unk7c; // 0x7c
    int mMetaScore; // 0x84
    std::set<Symbol> mAwards; // 0x88
    std::list<std::pair<Symbol, Symbol> > mNewAwards; // 0xa0
    std::list<Symbol> mNewRewardVignettes; // 0xa8
    std::set<Symbol> unkb0; // 0xb0
    int mTotalGemsSmashed; // 0xc8
    int mTotalBassHopos; // 0xcc
    int mTotalGuitarHopos; // 0xd0
    int mTotalUpstrums; // 0xd4
    int mTotalTimesRevived; // 0xd8
    int mTotalSaves; // 0xdc
    int mTotalAwesomes; // 0xe0
    int mTotalDoubleAwesomes; // 0xe4
    int mTotalTripleAwesomes; // 0xe8
    int mCareerFills; // 0xec
    int mBestStars[kNumScoreTypes][kNumDifficulties]; // 0xf0
    int mBestSolo[kNumScoreTypes][kNumDifficulties]; // 0x1a0
    int mBestAccuracy[kNumScoreTypes][kNumDifficulties]; // 0x250
    int mBestHoposPercent[kNumScoreTypes][kNumDifficulties]; // 0x300
    int mBestScore[kNumScoreTypes]; // 0x3b0
    int mBestBandScore; // 0x3dc
    int mBestStreak[kNumScoreTypes]; // 0x3e0
    int mTotalOverdriveDeploys[kNumScoreTypes]; // 0x40c
    int mTotalOverdriveTime[kNumScoreTypes]; // 0x438
    int mTotalOverdrivePhrases[kNumScoreTypes]; // 0x464
    int mTotalUnisonPhrases[kNumScoreTypes]; // 0x490
    int mMostOverdriveDeploys[kNumScoreTypes]; // 0x4bc
    int mMostOverdriveTime[kNumScoreTypes]; // 0x4e8
    int mMostUnisonPhrases[kNumScoreTypes]; // 0x514
    int mTotalBREsHit[kNumScoreTypes]; // 0x540
    int mBestPercussionPercent[kNumDifficulties]; // 0x56c
    int mBestKickPercent[kNumDifficulties]; // 0x57c
    int mBestProKickPercent[kNumDifficulties]; // 0x58c
    int mTotalDrumRollCount[kNumDifficulties]; // 0x59c
    int mTotalProDrumRollCount[kNumDifficulties]; // 0x5ac
    int mBestSoloButtonPercent[kNumDifficulties]; // 0x5bc
    int mBestDrumRollPercent[kNumDifficulties]; // 0x5cc
    int mTotalSongsPlayed; // 0x5dc
    int mTourTotalSongsPlayed; // 0x5e0
    std::map<Symbol, int> mToursPlayedMap; // 0x5e4
    std::map<Symbol, int> mTourMostStarsMap; // 0x5fc
    std::map<Symbol, int> mToursGotAllStarsMap; // 0x614
    std::map<int, int> mGigTypeCompletedMap; // 0x62c
    bool mUploadDirty; // 0x644
    bool unk645; // 0x645
    int unk648; // 0x648
};