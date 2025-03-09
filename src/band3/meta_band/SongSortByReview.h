#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols.h"

class ReviewCmp : public SongSortCmp {
public:
    ReviewCmp(int, const char *);
    virtual ~ReviewCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const ReviewCmp *GetReviewCmp() const { return this; }

    int mReview; // 0x4
    const char *mName; // 0x8
    Symbol mHeaderSym; // 0xc
};

class SongSortByReview : public SongSort {
public:
    SongSortByReview() { mShortName = by_review; }
    virtual ~SongSortByReview() {}
    virtual bool CustomForNode(ShortcutNode *, UIListCustom *, Hmx::Object *) const;
    virtual const char *TextForNode(ShortcutNode *, UIListLabel *, UILabel *) const;
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;
};
