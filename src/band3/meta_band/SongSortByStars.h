#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols.h"

class StarsCmp : public SongSortCmp {
public:
    StarsCmp(int, float, const char *);
    virtual ~StarsCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const StarsCmp *GetStarsCmp() const { return this; }

    int mStars; // 0x4
    float mRank; // 0x8
    const char *mName; // 0xc
    Symbol mHeaderSym; // 0x10
};

class SongSortByStars : public SongSort {
    SongSortByStars() { mShortName = by_stars; }
    virtual ~SongSortByStars() {}
    virtual void Init();
    virtual bool CustomForNode(ShortcutNode *, UIListCustom *, Hmx::Object *) const;
    virtual const char *TextForNode(ShortcutNode *, UIListLabel *, UILabel *) const;
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;
};