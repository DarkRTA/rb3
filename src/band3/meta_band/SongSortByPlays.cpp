#include "meta_band/SongSortByPlays.h"
#include "SongSortNode.h"
#include "meta/Sorting.h"
#include "meta_band/StoreSongSortNode.h"
#include "utl/MemMgr.h"

PlaysCmp::PlaysCmp(int plays, const char *name) : mPlays(plays), mName(name) {}

int PlaysCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    PlaysCmp *cmp = (PlaysCmp *)s;
    switch (nodeType) {
    case kNodeShortcut:
    case kNodeHeader:
        return cmp->mPlays - mPlays;
    case kNodeSong:
    case kNodeStoreSong:
        if (mPlays == cmp->mPlays) {
            return AlphaKeyStrCmp(mName, cmp->mName, true);
        } else
            return cmp->mPlays - mPlays > 0 ? 1 : -1;
        break;
    default:
        MILO_FAIL("invalid type of node comparison.\n");
        return 0;
    }
}

OwnedSongSortNode *SongSortByPlays::NewSongNode(SongRecord *record) const {
    MemDoTempAllocations m(true, false);
    const char *title = record->Data()->Title();
    PlaysCmp *cmp = new PlaysCmp(record->mPlays, title);
    OwnedSongSortNode *node = new OwnedSongSortNode(cmp, record);
    return node;
}

StoreSongSortNode *SongSortByPlays::NewSongNode(StoreOffer *offer) const {
    MemDoTempAllocations m(true, false);
    const char *name = offer->OfferName();
    PlaysCmp *cmp = new PlaysCmp(0, name);
    StoreSongSortNode *node = new StoreSongSortNode(cmp, offer);
    return node;
}

ShortcutNode *SongSortByPlays::NewShortcutNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    PlaysCmp *other = (PlaysCmp *)node->Cmp();
    int plays = other->mPlays;
    PlaysCmp *cmp = new PlaysCmp(plays, "");
    ShortcutNode *newNode = new ShortcutNode(cmp, MakeString("%i", plays), false);
    return newNode;
}

HeaderSortNode *SongSortByPlays::NewHeaderNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    PlaysCmp *other = (PlaysCmp *)node->Cmp();
    int plays = other->mPlays;
    PlaysCmp *cmp = new PlaysCmp(plays, "");
    HeaderSortNode *newNode = new HeaderSortNode(cmp, MakeString("%i", plays), false);
    return newNode;
}

DECOMP_FORCEFUNC(SongSortByDiff, PlaysCmp, GetPlaysCmp())
DECOMP_FORCEDTOR(SongSortByDiff, PlaysCmp)