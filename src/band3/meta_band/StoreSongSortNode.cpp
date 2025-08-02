#include "StoreSongSortNode.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/SongSortNode.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "utl/Symbols2.h"

StoreSongSortNode::StoreSongSortNode(SongSortCmp *cmp, StoreOffer* off) : SongSortNode(cmp) {
    
    unk34 = off->ShortName();
}

StoreSongSortNode::~StoreSongSortNode(){

}

bool StoreSongSortNode::IsEnabled() const {
    return IsActive();
}

const char *StoreSongSortNode::GetAlbumArtPath() {
    return "ui/image/song_select_random_keep.png";
}

const char *StoreSongSortNode::GetTitle() const {
    return unk38->OfferName();
}

const char *StoreSongSortNode::GetArtist() const {
    return unk38->Artist();
}

bool StoreSongSortNode::GetIsCover() const {
    return unk38->IsCover();
}

const char *StoreSongSortNode::GetAlbum() const {
    return unk38->AlbumName();
}

int StoreSongSortNode::GetTotalMs() const {
    return 0;
}

int StoreSongSortNode::GetTier(Symbol sym) const {
    float f1 = unk38->PartRank(sym);
    return TheSongMgr.RankTier(f1, sym);
}

SongNodeType StoreSongSortNode::GetType() const {
    return kNodeStoreSong;
}

Symbol StoreSongSortNode::GetToken() const {
    return unk34;
}

BEGIN_HANDLERS(StoreSongSortNode)

HANDLE_SUPERCLASS(SongSortNode)
HANDLE_CHECK(76)
END_HANDLERS