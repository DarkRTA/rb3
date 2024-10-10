#pragma once
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "meta_band/BandSongMgr.h"
#include "game/Defines.h"
#include "game/Performer.h"
#include "meta_band/BandProfile.h"

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
    virtual ~QuickplayPerformerImpl();
    virtual void CompleteSong(std::vector<BandUser*>&, const BandStatsInfo*, bool);
    virtual bool IsRandomSetList() const;
    virtual bool IsWinning() const;
    virtual void RestartLastSong();
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
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

    static void Init();
    static MetaPerformer* Current();
    static MetaPerformer* sMetaPerformer;
};