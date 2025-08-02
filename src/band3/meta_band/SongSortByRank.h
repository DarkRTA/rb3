#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "net_band/DataResults.h"
#include "utl/Symbols.h"

class RankCmp : public SongSortCmp {
public:
    enum RankType {
        kRank = 0,
        kPercentile = 1,
        kUnranked = 2,
        kNoData = 3
    };
    RankCmp(int, const char *, RankType);
    virtual ~RankCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const RankCmp *GetRankCmp() const { return this; }

    int mVal; // 0x4
    const char *mSongName; // 0x8
    RankType mType; // 0xc
};

class SongSortByRank : public SongSort {
public:
    SongSortByRank() { mShortName = by_rank; }
    virtual ~SongSortByRank();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Clear();
    virtual bool IsReady() const;
    virtual void MakeReady();
    virtual void CancelMakeReady();
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;

    void RequestSongRankingInfo();
    void CancelSongRankingRequest();

    std::map<int, bool> mRankings; // 0x3c
    DataResultList mDataResults; // 0x54
};
