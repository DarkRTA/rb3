#include "meta_band/SongSortBySong.h"
#include "meta/Sorting.h"

int SongCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    SongCmp *cmp = (SongCmp *)s;
    switch (nodeType) {
    case kNodeShortcut:
    case kNodeHeader:
        return mHeaderSym.mStr == cmp->mHeaderSym.mStr
            ? 0
            : strcmp(mHeaderSym.mStr, cmp->mHeaderSym.mStr);
    case kNodeSong:
    case kNodeStoreSong:
        return AlphaKeyStrCmp(mName, cmp->mName, true);
    default:
        MILO_FAIL("invalid type of node comparison.\n");
        return 0;
    }
}