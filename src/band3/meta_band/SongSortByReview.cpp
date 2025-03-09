#include "meta_band/SongSortByReview.h"
#include "SongSortNode.h"
#include "bandobj/ReviewDisplay.h"
#include "meta/Sorting.h"
#include "meta_band/StoreSongSortNode.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"

ReviewCmp::ReviewCmp(int review, const char *name) : mReview(review), mName(name) {
    mHeaderSym = ReviewDisplay::GetSymbolForReviewScore(review);
    MILO_ASSERT(!mHeaderSym.Null(), 0x19);
}

int ReviewCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    ReviewCmp *cmp = (ReviewCmp *)s;
    switch (nodeType) {
    case kNodeShortcut:
    case kNodeHeader:
        if (mReview == cmp->mReview)
            return 0;
        else if (mReview == 1)
            return 1;
        else if (cmp->mReview == 1)
            return -1;
        else
            return cmp->mReview - mReview > 0 ? 1 : -1;
    case kNodeSong:
    case kNodeStoreSong:
        if (mReview == cmp->mReview) {
            return AlphaKeyStrCmp(mName, cmp->mName, true);
        } else if (mReview == 1)
            return 1;
        else if (cmp->mReview == 1)
            return -1;
        else
            return cmp->mReview - mReview > 0 ? 1 : -1;
    default:
        MILO_FAIL("invalid type of node comparison.\n");
        return 0;
    }
}

OwnedSongSortNode *SongSortByReview::NewSongNode(SongRecord *record) const {
    MemDoTempAllocations m(true, false);
    const char *title = record->Data()->Title();
    ReviewCmp *cmp = new ReviewCmp(record->mReview, title);
    OwnedSongSortNode *node = new OwnedSongSortNode(cmp, record);
    return node;
}

StoreSongSortNode *SongSortByReview::NewSongNode(StoreOffer *offer) const {
    MemDoTempAllocations m(true, false);
    const char *name = offer->OfferName();
    ReviewCmp *cmp = new ReviewCmp(0, name);
    StoreSongSortNode *node = new StoreSongSortNode(cmp, offer);
    return node;
}