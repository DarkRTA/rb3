#include "meta_band/SongSortByArtist.h"
#include "SongSortNode.h"
#include "StoreSongSortNode.h"
#include "meta/Sorting.h"
#include "meta/StoreOffer.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/MemMgr.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

int ArtistCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    const ArtistCmp *cmp = (ArtistCmp *)s;
    switch (nodeType) {
    case kNodeShortcut:
        return strcmp(mShortcut.mStr, cmp->mShortcut.mStr);
    case kNodeHeader:
        int ret = AlphaKeyStrCmp(mArtist, cmp->mArtist, true);
        if (ret != 0)
            return ret;
        else if (mCover == cmp->mCover)
            return 0;
        else {
            ret = -1;
            if (mCover)
                ret = 1;
            return ret;
        }
    case kNodeSubheader:
        if (!HasSubheader()) {
            MILO_ASSERT(cmp->HasSubheader(), 0x32);
            return -1;
        } else if (!cmp->HasSubheader())
            return 1;
        else
            return AlphaKeyStrCmp(mAlbum, cmp->mAlbum, false);
    case kNodeSong:
    case kNodeStoreSong:
        if (mShortcut.Null()) {
            MILO_ASSERT(!cmp->mShortcut.Null(), 0x40);
            return 1;
        } else if (cmp->mShortcut.Null())
            return -1;
        else if (!HasSubheader()) {
            return AlphaKeyStrCmp(mSongName, cmp->mSongName, true);
        } else {
            if (mTrackNum < cmp->mTrackNum)
                return -1;
            else
                return mTrackNum > cmp->mTrackNum;
        }
    default:
        MILO_FAIL("invalid type of node comparison.\n");
        return 0;
    }
}

bool ArtistCmp::HasSubheader() const { return mTrackNum != -1 || mShortcut.Null(); }

void SongSortByArtist::Init() {
    DataArray *cfg = SystemConfig(song_select);
    DataArray *alphas = cfg->FindArray(alpha_shortcuts);
    for (int i = 1; i < alphas->Size(); i++) {
        MemDoTempAllocations m(true, false);
        Symbol curSym = alphas->Sym(i);
        ArtistCmp *cmp = new ArtistCmp(curSym, "", false, "", -1, "");
        mTree.push_back(new ShortcutNode(cmp, curSym, false));
    }
}

OwnedSongSortNode *SongSortByArtist::NewSongNode(SongRecord *record) const {
    MemDoTempAllocations m(true, false);
    const char *artist = record->Data()->Artist();
    Symbol firstChar = NodeSort::FirstChar(artist, true);
    const char *album = record->Data()->Album();
    int tracknum = record->Data()->AlbumTrackNum();
    const char *title = record->Data()->Title();
    ArtistCmp *cmp = new ArtistCmp(
        firstChar, artist, !record->Data()->IsMasterRecording(), album, tracknum, title
    );
    OwnedSongSortNode *node = new OwnedSongSortNode(cmp, record);
    return node;
}

StoreSongSortNode *SongSortByArtist::NewSongNode(StoreOffer *offer) const {
    MemDoTempAllocations m(true, false);
    const char *artist = offer->Artist();
    Symbol firstChar = NodeSort::FirstChar(artist, true);
    const char *album = offer->AlbumName();
    const char *title = offer->OfferName();
    bool cover = offer->IsCover();
    ArtistCmp *cmp = new ArtistCmp(firstChar, artist, cover, album, -1, title);
    StoreSongSortNode *node = new StoreSongSortNode(cmp, offer);
    return node;
}

ShortcutNode *SongSortByArtist::NewShortcutNode(SongSortNode *) const {
    MILO_FAIL("Couldn't find a letter ");
    return nullptr;
}

HeaderSortNode *SongSortByArtist::NewHeaderNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    const char *artist = node->GetArtist();
    ArtistCmp *cmp = new ArtistCmp(gNullStr, artist, node->GetIsCover(), "", -1, "");
    HeaderSortNode *headerNode = new HeaderSortNode(cmp, artist, false);
    headerNode->mCover = node->GetIsCover();
    return headerNode;
}

SubheaderSortNode *SongSortByArtist::NewSubheaderNode(SongSortNode *node) const {
    MemDoTempAllocations m(true, false);
    const char *album = node->GetAlbum();
    ArtistCmp *cmp = new ArtistCmp(gNullStr, "", node->GetIsCover(), album, -1, "");
    SubheaderSortNode *headerNode = new SubheaderSortNode(cmp, album, false);
    return headerNode;
}

void SongSortByArtist::ConfirmSubheaders(HeaderSortNode *node) {
    std::list<SortNode *> &children = node->mChildren;
    std::list<SortNode *> sortNodes;

    for (std::list<SortNode *>::iterator it = children.begin(); it != children.end();) {
        SortNode *cur = *it;
        if (cur->GetType() != kNodeSubheader)
            ++it;
        else {
            std::list<SortNode *> &curChildren = cur->mChildren;
            if (curChildren.size() < 3) {
                FOREACH (curIt, curChildren) {
                    sortNodes.push_back(*curIt);
                }
                it = curChildren.erase(it);
                delete cur;
            } else
                ++it;
        }
    }

    FOREACH_POST (it, sortNodes) {
        node->Insert((LeafSortNode *)*it, this, true);
    }
}