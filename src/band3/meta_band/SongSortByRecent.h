#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols.h"

class RecentCmp : public SongSortCmp {
public:
    enum RecentType {
        kRecent = 0, // newly acquired
        kPrevious = 1, // previously acquired
        kPearljam = 2,
        kDisc = 3,
        kGreenday = 4,
        kLego = 5,
        kRB2 = 6,
        kRB1 = 7,
        kNotYet = 8,
        kDontHave = 9
    };
    RecentCmp(int, const char *, Symbol, bool);
    virtual ~RecentCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const RecentCmp *GetRecentCmp() const { return this; }

    static RecentType OriginToRecentType(Symbol);
    static Symbol RecentTypeToOrigin(RecentType);

    RecentType mType; // 0x4
    int mRecentPos; // 0x8
    const char *mSongName; // 0xc
};

class SongSortByRecent : public SongSort {
    SongSortByRecent() { mShortName = by_recent; }
    virtual ~SongSortByRecent() {}
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;
};