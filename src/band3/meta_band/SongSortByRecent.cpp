#include "meta_band/SongSortByRecent.h"
#include "SongSortByRecent.h"
#include "SongSortNode.h"
#include "meta/Sorting.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/StoreSongSortNode.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include "utl/Symbol.h"
#include "utl/Symbols4.h"

RecentCmp::RecentCmp(int pos, const char *name, Symbol s, bool b)
    : mRecentPos(pos), mSongName(name) {
    RecentType ty = OriginToRecentType(s);
    if (ty != 9)
        mType = ty;
    else if (b)
        mType = (RecentType)8;
    else if (mRecentPos < 0)
        mType = (RecentType)1;
    else
        mType = (RecentType)0;
}

RecentCmp::RecentType RecentCmp::OriginToRecentType(Symbol origin) {
    if (origin == rb3)
        return kDisc;
    else if (origin == pearljam)
        return kPearljam;
    else if (origin == greenday)
        return kGreenday;
    else if (origin == lego)
        return kLego;
    else if (origin == rb2)
        return kRB2;
    else if (origin == rb1)
        return kRB1;
    else
        return kDontHave;
}

Symbol RecentCmp::RecentTypeToOrigin(RecentCmp::RecentType ty) {
    switch (ty) {
    case kDisc:
        return rb3;
    case kPearljam:
        return pearljam;
    case kGreenday:
        return greenday;
    case kLego:
        return lego;
    case kRB2:
        return rb2;
    case kRB1:
        return rb1;
    default:
        return gNullStr;
    }
}

int RecentCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    RecentCmp *cmp = (RecentCmp *)s;
    switch (nodeType) {
    case kNodeShortcut:
    case kNodeHeader:
        return mType - cmp->mType;
    case kNodeSong:
    case kNodeStoreSong:
        if (mType == cmp->mType) {
            if (mType == 0) {
                if (cmp->mRecentPos != mRecentPos) {
                    return cmp->mRecentPos - mRecentPos;
                }
            }
            return AlphaKeyStrCmp(mSongName, cmp->mSongName, true);
        }
        return mType - cmp->mType;
    default:
        MILO_FAIL("invalid type of node comparison.\n");
        return 0;
    }
}

OwnedSongSortNode *SongSortByRecent::NewSongNode(SongRecord *record) const {
    MemDoTempAllocations m(true, false);
    const BandSongMetadata *data = record->Data();
    int id = data->ID();
    int pos = TheSongMgr.GetPosInRecentList(id);
    const char *title = data->Title();
    RecentCmp *cmp = new RecentCmp(pos, title, data->GameOrigin(), false);
    OwnedSongSortNode *node = new OwnedSongSortNode(cmp, record);
    return node;
}

StoreSongSortNode *SongSortByRecent::NewSongNode(StoreOffer *offer) const {
    MemDoTempAllocations m(true, false);
    const char *name = offer->OfferName();
    RecentCmp *cmp = new RecentCmp(-1, name, gNullStr, true);
    StoreSongSortNode *node = new StoreSongSortNode(cmp, offer);
    return node;
}

ShortcutNode *SongSortByRecent::NewShortcutNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    RecentCmp *other = (RecentCmp *)node->Cmp();
    RecentCmp::RecentType ty = other->mType;
    Symbol origin = other->RecentTypeToOrigin(ty);
    RecentCmp *cmp = new RecentCmp(ty == 0, nullptr, origin, ty == 8);

    Symbol token;
    switch (ty) {
    case 0:
        token = recently_acquired;
        break;
    case 1:
        token = previously_acquired;
        break;
    case 8:
        token = not_yet_acquired;
        break;
    default:
        MILO_ASSERT(origin != gNullStr, 0xB1);
        token = gNullStr;
        break;
    }
    ShortcutNode *newNode = new ShortcutNode(cmp, token, true);
    return newNode;
}

HeaderSortNode *SongSortByRecent::NewHeaderNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    RecentCmp *other = (RecentCmp *)node->Cmp();
    RecentCmp::RecentType ty = other->mType;
    Symbol origin = other->RecentTypeToOrigin(ty);
    RecentCmp *cmp = new RecentCmp(ty == 0, nullptr, origin, ty == 8);

    Symbol token;
    switch (ty) {
    case 0:
        token = recently_acquired;
        break;
    case 1:
        token = previously_acquired;
        break;
    case 8:
        token = not_yet_acquired;
        break;
    default:
        MILO_ASSERT(origin != gNullStr, 0xB1);
        token = gNullStr;
        break;
    }
    HeaderSortNode *newNode = new HeaderSortNode(cmp, token, true);
    return newNode;
}