#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols.h"

class PlaysCmp : public SongSortCmp {
public:
    PlaysCmp(int, const char *);
    virtual ~PlaysCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const PlaysCmp *GetPlaysCmp() const { return this; }

    int mPlays; // 0x4
    const char *mName; // 0x8
};

class SongSortByPlays : public SongSort {
    SongSortByPlays() { mShortName = by_plays; }
    virtual ~SongSortByPlays() {}
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;
};