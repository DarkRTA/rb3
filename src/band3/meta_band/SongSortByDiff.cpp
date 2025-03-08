#include "meta_band/SongSortByDiff.h"
#include "SongSortByDiff.h"
#include "SongSortNode.h"
#include "StoreSongSortNode.h"
#include "decomp.h"
#include "meta/Sorting.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/SongRecord.h"
#include "utl/MemMgr.h"
#include "utl/Symbols4.h"

int DifficultyCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    DifficultyCmp *cmp = (DifficultyCmp *)s;
    switch (nodeType) {
    case kNodeShortcut:
    case kNodeHeader:
        if (mTier == cmp->mTier) {
            return 0;
        } else if (cmp->mTier == -1)
            return -1;
        else if (mTier == -1)
            return 1;
        else
            return mTier < cmp->mTier ? -1 : 1;
    case kNodeSong:
    case kNodeStoreSong:
        float other = cmp->mRank;
        float mine = mRank;
        if (mine == other) {
            return AlphaKeyStrCmp(mName, cmp->mName, true);
        } else if (other == 0)
            return -1;
        else if (mine == 0)
            return 1;
        else if (mine < other)
            return -1;
        else
            return 1;
    default:
        MILO_FAIL("invalid type of node comparison.\n");
        return 0;
    }
}

void SongSortByDiff::Init() { mSortPart = TheMusicLibrary->DifficultySortPart(); }

OwnedSongSortNode *SongSortByDiff::NewSongNode(SongRecord *record) const {
    MemDoTempAllocations m(true, false);
    int tier = record->GetTier(mSortPart);
    float rank = record->Data()->Rank(mSortPart);
    if (rank == 0)
        tier = -1;
    const char *title = record->Data()->Title();
    DifficultyCmp *cmp = new DifficultyCmp(tier, rank, title);
    OwnedSongSortNode *node = new OwnedSongSortNode(cmp, record);
    return node;
}

StoreSongSortNode *SongSortByDiff::NewSongNode(StoreOffer *offer) const {
    MemDoTempAllocations m(true, false);
    float rank = offer->PartRank(mSortPart);
    int tier = TheSongMgr.RankTier(rank, mSortPart);
    if (rank == 0)
        tier = -1;
    const char *name = offer->OfferName();
    DifficultyCmp *cmp = new DifficultyCmp(tier, rank, name);
    StoreSongSortNode *node = new StoreSongSortNode(cmp, offer);
    return node;
}

ShortcutNode *SongSortByDiff::NewShortcutNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    DifficultyCmp *other = (DifficultyCmp *)node->Cmp();
    int tier = other->mTier;
    DifficultyCmp *cmp = new DifficultyCmp(tier, 0, "");
    Symbol sym = tier == -1 ? no_part : TheSongMgr.RankTierToken(tier);
    ShortcutNode *newNode = new ShortcutNode(cmp, sym, true);
    return newNode;
}

HeaderSortNode *SongSortByDiff::NewHeaderNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    DifficultyCmp *other = (DifficultyCmp *)node->Cmp();
    int tier = other->mTier;
    DifficultyCmp *cmp = new DifficultyCmp(tier, 0, "");
    Symbol sym = tier == -1 ? no_part : TheSongMgr.RankTierToken(tier);
    HeaderSortNode *newNode = new HeaderSortNode(cmp, sym, true);
    return newNode;
}

DECOMP_FORCEFUNC(SongSortByDiff, DifficultyCmp, GetDifficultyCmp())
DECOMP_FORCEDTOR(SongSortByDiff, DifficultyCmp)