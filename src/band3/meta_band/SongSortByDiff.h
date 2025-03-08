#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols2.h"

class DifficultyCmp : public SongSortCmp {
public:
    DifficultyCmp(int tier, float rank, const char *name)
        : mTier(tier), mRank(rank), mName(name) {}
    virtual ~DifficultyCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual DifficultyCmp *GetDifficultyCmp() const { return (DifficultyCmp *)this; }

    int mTier; // 0x4
    float mRank; // 0x8
    const char *mName; // 0xc
};

class SongSortByDiff : public SongSort {
    SongSortByDiff() { mShortName = by_difficulty; }
    virtual ~SongSortByDiff() {}
    virtual void Init();
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;

    Symbol mSortPart; // 0x3c
};