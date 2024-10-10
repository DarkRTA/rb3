#pragma once
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "meta_band/BandSongMgr.h"
#include "game/Defines.h"
#include "game/Performer.h"
#include "meta_band/BandProfile.h"
#include "meta_band/Instarank.h"
#include "net_band/DataResults.h"

class PerformerStatsInfo {
public:
    PerformerStatsInfo();
    virtual ~PerformerStatsInfo();

    void Clear();
    void Update(int, int, ScoreType, Difficulty, short, Performer*);

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
    int unk38;
    int mUnisonPhrasesHit; // 0x3c
};

class BandStatsInfo {
public:
    BandStatsInfo();
    virtual ~BandStatsInfo();

    void Clear();
    void UpdateBandStats(Difficulty, short, Performer*);
    const PerformerStatsInfo& GetBandStats() const;
    BandProfile* GetSoloProfile(int) const;
    const PerformerStatsInfo& GetSoloStats(int) const;

    PerformerStatsInfo mBandStats; // 0x4
    std::vector<std::pair<BandProfile*, PerformerStatsInfo> > mSoloStats; // 0x44
};

class PendingDataInfo {
public:
    PendingDataInfo(){}

    DataResultList ir_result; // 0x0
    bool friendMode; // 0x18
    BandStatsInfo stats; // 0x1c
    Symbol song; // 0x68
};

class MetaPerformerImpl : public Hmx::Object {
public:
    MetaPerformerImpl(){}
    virtual void CompleteSong(std::vector<BandUser*>&, const BandStatsInfo*, bool){}
    virtual bool IsRandomSetList() const = 0;
    virtual bool IsWinning() const { return false; }
    virtual void RestartLastSong(){}
    virtual bool HasSyncPermission() const = 0;
    virtual void OnSynchronized(unsigned int){}
    virtual void SyncSave(BinStream&, unsigned int) const {}
    virtual void SyncLoad(BinStream&, unsigned int){}
};

class QuickplayPerformerImpl : public MetaPerformerImpl {
public:
    QuickplayPerformerImpl();
    virtual ~QuickplayPerformerImpl(){}
    virtual bool IsRandomSetList() const;
    virtual bool HasSyncPermission() const;
};

class MetaPerformer : public Synchronizable, public MsgSource {
public:
    MetaPerformer(const BandSongMgr&, const char*);
    virtual ~MetaPerformer();
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);
    virtual DataNode Handle(DataArray*, bool);

    QuickplayPerformerImpl* CurrentImpl() const;
    Symbol GetVenue() const;
    Symbol GetVenueClass() const;
    Symbol GetLastVenueClass() const;
    bool SongEndsWithEndgameSequence() const;
    bool IsWinning() const;
    bool IsLastSong() const;
    int NumSongs() const { return mSongs.size(); }
    int NumCompleted() const { return unk78.size(); }
    Symbol Song() const;
    int SongsID() const;
    bool HasSong() const;
    const char* GetSetlistName() const;
    bool HasSetlist() const;
    void SetSongs(const std::vector<Symbol>&);
    void SetSongs(const std::vector<int>&);
    void SetSong(Symbol);
    void SetSongs(DataArray*);
    void ResetSongs();
    Symbol GetCompletedSong() const;
    const std::vector<Symbol>& GetSongs() const;
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
    ScoreType GetScoreTypeForUser(BandUser*);
    bool IsUsingRealDrums() const;
    bool IsNowUsingVocalHarmony() const;
    bool IsPlayingDemo() const;
    bool IsNoFailActive() const;
    bool IsBandNoFailSet() const;
    bool CanUpdateScoreLeaderboards();

    static void Init();
    static MetaPerformer* Current();
    static MetaPerformer* sMetaPerformer;

    bool unk38;
    QuickplayPerformerImpl* mQpPerformer; // 0x3c
    bool unk40;
    Symbol mVenue; // 0x44
    Symbol unk48; // 0x48
    Symbol unk4c;
    String unk50;
    bool unk5c;
    bool unk5d;
    int unk60;
    bool unk64;
    int unk68;
    int unk6c;
    std::vector<Symbol> mSongs; // 0x70
    std::vector<int> unk78;
    BandSongMgr* mSongMgr; // 0x80
    Instarank unk84;
    Instarank unkdc;
    Instarank unk134[4];
    int unk294;
    int unk298;
    int unk29c;
    int unk2a0;
    int unk2a4;
    int unk2a8;
    int unk2ac;
    int unk2b0;
    int unk2b4;
    int unk2b8;
    bool unk2bc;
    bool unk2bd;
    int unk2c0;
    bool unk2c4;
    bool unk2c5;
    PendingDataInfo unk2c8;
    bool unk334;
    int unk338;
    int unk33c;
    int unk340;
    DataResultList unk344;
    bool unk35c;
    bool unk35d;
    int unk360;
    Symbol mVenueOverride; // 0x364
};