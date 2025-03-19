#pragma once
#include "game/BandUser.h"
#include "game/GameMode.h"
#include "meta_band/SavedSetlist.h"
#include "net/Synchronize.h"
#include "obj/Msg.h"
#include "meta_band/BandSongMgr.h"
#include "game/Defines.h"
#include "game/Performer.h"
#include "meta_band/BandProfile.h"
#include "meta_band/Instarank.h"
#include "net_band/DataResults.h"
#include "ui/UILabel.h"

class PlayerScore;

class PerformerStatsInfo {
public:
    PerformerStatsInfo();
    virtual ~PerformerStatsInfo();

    void Clear();
    void Update(int, int, ScoreType, Difficulty, short, Performer *);

    short mInstrumentMask; // 0x4
    ScoreType mScoreType; // 0x8
    int unkc;
    int unk10;
    Difficulty mDifficulty; // 0x14
    int mScore; // 0x18
    int mStars; // 0x1c
    int mAccuracy; // 0x20
    int mStreak; // 0x24
    int mAwesomes; // 0x28
    int mDoubleAwesomes; // 0x2c
    int mTripleAwesomes; // 0x30
    int mSoloPercent; // 0x34
    int mHOPOPercent; // 0x38
    int mUnisonPhrasesHit; // 0x3c
};

class BandStatsInfo {
public:
    BandStatsInfo();
    virtual ~BandStatsInfo();

    void Clear();
    void UpdateBandStats(Difficulty, short, Performer *);
    const PerformerStatsInfo &GetBandStats() const;
    BandProfile *GetSoloProfile(int) const;
    const PerformerStatsInfo &GetSoloStats(int) const;
    void AddSoloStats(int, int, ScoreType, Difficulty, BandProfile *, Performer *);
    int NumSoloStats() const { return mSoloStats.size(); }

    PerformerStatsInfo mBandStats; // 0x4
    std::vector<std::pair<BandProfile *, PerformerStatsInfo> > mSoloStats; // 0x44
};

class MetaPerformerImpl : public Hmx::Object {
public:
    MetaPerformerImpl() {}
    virtual void CompleteSong(std::vector<BandUser *> &, const BandStatsInfo *, bool) {}
    virtual bool IsRandomSetList() const = 0;
    virtual bool IsWinning() const { return false; }
    virtual void RestartLastSong() {}
    virtual bool HasSyncPermission() const = 0;
    virtual void OnSynchronized(unsigned int) {}
    virtual void SyncSave(BinStream &, unsigned int) const {}
    virtual void SyncLoad(BinStream &, unsigned int) {}
};

class QuickplayPerformerImpl : public MetaPerformerImpl {
public:
    QuickplayPerformerImpl();
    virtual ~QuickplayPerformerImpl() {}
    virtual bool IsRandomSetList() const;
    virtual bool HasSyncPermission() const;
};

class MetaPerformer : public Synchronizable, public MsgSource {
public:
    class PendingDataInfo {
    public:
        PendingDataInfo() {}
        void Clear() {
            ir_result.Clear();
            friendMode = true;
            stats.Clear();
            song = "";
        }

        DataResultList ir_result; // 0x0
        bool friendMode; // 0x18
        BandStatsInfo stats; // 0x1c
        Symbol song; // 0x68
    };
    enum WiiPendingFlags {
    };

    MetaPerformer(const BandSongMgr &, const char *);
    virtual ~MetaPerformer();
    virtual void SyncSave(BinStream &, unsigned int) const;
    virtual void SyncLoad(BinStream &, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);
    virtual DataNode Handle(DataArray *, bool);

    MetaPerformerImpl *CurrentImpl() const;
    Symbol GetVenue() const;
    Symbol GetVenueClass() const;
    Symbol GetLastVenueClass() const;
    bool SongEndsWithEndgameSequence() const;
    bool IsWinning() const;
    bool IsLastSong() const;
    int NumSongs() const;
    int NumCompleted() const;
    Symbol Song() const;
    int SongsID() const;
    bool HasSong() const;
    const char *GetSetlistName() const;
    bool HasSetlist() const;
    void SetSongs(const std::vector<Symbol> &);
    void SetSongs(const std::vector<int> &);
    void SetSong(Symbol);
    void SetSongs(DataArray *);
    void ResetSongs();
    Symbol GetCompletedSong() const;
    const std::vector<Symbol> &GetSongs() const;
    bool IsFirstSong() const;
    bool IsSetComplete() const;
    bool PartPlaysInSet(Symbol) const;
    bool PartPlaysInSong(Symbol) const;
    bool VocalHarmonyInSong() const;
    int GetSetlistMaxVocalParts() const;
    bool SetlistHasVocalHarmony() const;
    bool SetHasMissingPart(Symbol) const;
    bool SetHasMissingVocalHarmony() const;
    bool SongAllowsVocalHarmony() const;
    ScoreType GetScoreTypeForUser(BandUser *);
    bool IsUsingRealDrums() const;
    bool IsNowUsingVocalHarmony() const;
    bool IsPlayingDemo() const;
    bool IsNoFailActive() const;
    bool IsBandNoFailSet() const;
    bool CanUpdateScoreLeaderboards();
    void SetSetlist(Symbol);
    void SelectRandomVenue();
    void SetVenue(Symbol);
    bool HasBattle() const;
    ScoreType GetBattleInstrument() const;
    void UnlockBandOrSolo();
    void SetCreditsPending();
    void SetBattle(const BattleSavedSetlist *);
    void SetSetlist(const SavedSetlist *);
    void SetSetlistImpl(const SavedSetlist *, bool);
    int GetBattleID() const;
    bool HasValidBattleInstarank() const;
    const char *GetBattleName();
    int GetBattleInstrumentMask();
    int GetBattleScore();
    void UpdateBattleTypeLabel(UILabel *);
    void LockBandOrSolo();
    int GetHighestDifficultyForPart(Symbol) const;
    void PopulatePlayerBandScores(const BandStatsInfo &, std::vector<PlayerScore> &);
    void
    PopulateSoloPlayerScore(const PerformerStatsInfo &, BandProfile *, PlayerScore &);
    void PopulatePlayerScores(const BandStatsInfo &, std::vector<PlayerScore> &);
    void UpdateScores(Symbol, const BandStatsInfo &, bool);
    void UpdateLastOfflineScores(Symbol, const BandStatsInfo &);
    void
    SaveAndUploadScores(std::vector<LocalBandUser *> &, Symbol, const BandStatsInfo &);
    void RecordBattleScore(const BandStatsInfo &, bool);
    ScoreType GetInstarankScoreTypeForSlot(int, const BandStatsInfo &);
    Instarank &GetInstarankForPlayerID(int);
    void UpdateInstarankData(DataResultList &, const BandStatsInfo &);
    void UpdateBattleInstarankData(DataResultList &);
    void ClearInstarankData();
    void ClearBattleInstarankData();
    Symbol GetVenueOverride();
    void SetBandNoFail(bool);
    void ExportUpdateMetaPerformer();
    void LoadFestival();
    void ClearVenues();
    void ResetCompletion();
    void HostRestartLastSong();
    void Restart();
    void TriggerSongCompletion();
    void CompleteSong(std::vector<BandUser *> &, const BandStatsInfo *, bool);
    void SetCheating(bool);
    void
    PotentiallyUpdateLeaderboards(std::vector<BandUser *> &, bool, Symbol, const BandStatsInfo &);
    void IncrementSongPlayCount(std::vector<BandUser *> &, Symbol);
    int TotalStars(bool) const;
    bool IsRandomSetList() const;
    void SkipSong();
    void AdvanceSong(int);
    bool HasBattleHighscore();
    bool HasHighscore();
    int GetLastOfflineScore();
    int GetLastOfflineSoloScore(BandUser *);
    bool HasSoloHighscore(BandUser *);
    bool HasValidBandScore();
    bool HasValidUserScore(BandUser *);
    bool HasValidInstarankData() const;
    void UpdateInstarankRankLabel(UILabel *);
    void UpdateInstarankHighscore1Label(UILabel *);
    void UpdateInstarankHighscore2Label(UILabel *);
    void UpdateBattleInstarankHighscore1Label(UILabel *);
    void UpdateBattleInstarankHighscore2Label(UILabel *);
    const char *GetSoloScoreTypeIcon(BandUser *);
    void UpdateSoloInstarankRankLabel(BandUser *, UILabel *);
    void UpdateSoloInstarankHighscore1Label(BandUser *, UILabel *);
    void UpdateSoloInstarankHighscore2Label(BandUser *, UILabel *);
    void UploadDebugStats();
    void ClearCreditsPending();
    bool AreCreditsPending() const;
    void SetWiiPending(WiiPendingFlags);
    void ClearWiiPending(WiiPendingFlags);
    bool IsWiiPending(WiiPendingFlags) const;
    short GetRecentInstrumentMask() const;
    bool CheatToggleFinale();
    Symbol GetSongSymbol(int idx) const { return mSongs[idx]; }
    int GetWinMetric() const { return 0; }
    int GetPersistentGameData() { return 0; }
    bool InFinale() const { return mCheatInFinale && IsLastSong(); }
    bool GetCheating() const { return mCheating; }

    DataNode OnMsg(const RockCentralOpCompleteMsg &);
    DataNode OnMsg(const ModeChangedMsg &);

    static void Init();
    static MetaPerformer *Current();
    static MetaPerformer *sMetaPerformer;

    unsigned char mWiiPending; // 0x38
    QuickplayPerformerImpl *mQpPerformer; // 0x3c
    bool mCreditsPending; // 0x40
    Symbol mVenue; // 0x44
    Symbol mLastVenue; // 0x48
    Symbol mSetlist; // 0x4c
    String mSetlistTitle; // 0x50
    bool mSetlistIsLocal; // 0x5c
    bool mSetlistIsHmx; // 0x5d
    int mSetlistBattleID; // 0x60
    bool mIsBattle; // 0x64
    int mBattleScore; // 0x68
    ScoreType mBattleScoreType; // 0x6c
    std::vector<Symbol> mSongs; // 0x70
    std::vector<int> mStars; // 0x78
    BandSongMgr *mSongMgr; // 0x80
    Instarank mBattleInstarank; // 0x84
    Instarank mBandInstarank; // 0xdc
    Instarank unk134[4]; // 0x134
    int mSongID; // 0x294
    int mSongHighscore; // 0x298
    int unk29c[4]; // 0x29c
    ScoreType unk2ac[4]; // 0x2ac
    bool unk2bc;
    bool unk2bd;
    int unk2c0;
    bool unk2c4;
    bool mCheatInFinale; // 0x2c5
    PendingDataInfo mPendingData; // 0x2c8
    bool mCheating; // 0x334
    int unk338;
    int unk33c;
    int mRecordBattleContextID; // 0x340
    DataResultList unk344;
    bool unk35c;
    bool unk35d;
    int unk360;
    Symbol mVenueOverride; // 0x364
};