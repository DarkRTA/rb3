#include "meta/StoreOffer.h"
#include "meta/StorePackedMetadata.h"
#include "utl/Symbols.h"

namespace {
    bool gSetup;
    const char* LQUOTE = "\"";
    const char* RQUOTE = "\"";
    const char* RQUOTE_COMMA = ",\"";
    const char* BY_DASH = "--";
    const char* BY = "by";
    const char* AND = "and";
    const char* SONG_CREDITS = "Song credits at RockBand.com.";
    const char* ALBUM_INCLUDES = "Includes";
    const char* PACK_INCLUDES = "This pack includes";
}

const char* gGenreStrs[30] = {
    "alternative", "blues", "classicrock", "country", "emo", "fusion", "glam",
    "grunge", "indierock", "jazz", "metal", "new_wave", "novelty", "numetal",
    "other", "poprock", "prog", "punk", "rock", "southernrock", "urban",
    "classical", "hiphoprap", "inspirational", "jrock", "latin", "popdanceelectronic",
    "rbsoulfunk", "reggaeska", "world"
};

StorePurchaseable::StorePurchaseable() : unk1c(0), unk20(0) {

}

bool StorePurchaseable::Exists() const {
    return unk20;
}

const char* StorePurchaseable::CostStr() const {
    if(unk1c) return " ";
    else return "%i";
}

bool operator==(const StoreOffer* o, Symbol s){
    return o->ShortName() == s;
}

Symbol StoreOffer::Decade() const {
    int year = ((unk1c->mYearReleased + 1900) / 10) * 10;
    return MakeString("the%is", year);
}

Symbol StoreOffer::LengthSym() const {
    MILO_WARN("store metadata should have song length\n");
    return song_length_short;
}

void SetupStoreOfferLocals(){
    if(!gSetup){
        Symbol lang = SystemLanguage();
        if(lang == eng){
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "by";
            AND = "and";
            SONG_CREDITS = "Song credits at RockBand.com.";
            ALBUM_INCLUDES = "Includes";
            PACK_INCLUDES = "This pack includes";
        }
        gSetup = true;
    }
}

void UpdatePurchasable(StorePurchaseable* p){
    if(p->unk1c){
        int status = TheStoreMetadata.GetOfferStatus(p->unk1c);
        if(status != 0) p->unk20 = status;
    }
}

StoreOffer::StoreOffer(const StorePackedOfferBase* base, SongMgr* mgr, bool b) : unk74(mgr) {
    unk1c = base;
    UpdatePurchasable(this);
}

StoreOffer::~StoreOffer(){

}

Symbol StoreOffer::OfferType() const {
    StoreOfferType offerType = (StoreOfferType)unk1c->mOfferType;
    switch(offerType){
        case kStoreOfferAlbum: return "album";
        case kStoreOfferPack: return "pack";
        default: return "song";
    }
}

bool StoreOffer::IsNewRelease() const { return unk1c->mNewRelease; }

Symbol StoreOffer::Genre() const {
    StoreOfferType offerType = (StoreOfferType)unk1c->mOfferType;
    if(offerType != kStoreOfferPack){
        int idx = unk1c->mGenre;
        if(idx > 29) idx = 29;
        return gGenreStrs[idx];
    }
    else return gNullStr;
}

bool StoreOffer::IsCover() const { return unk1c->mCover; }
int StoreOffer::Rating() const { return unk1c->mRating; }
int StoreOffer::VocalParts() const { return unk1c->mVocalParts; }
bool StoreOffer::HasPreviewAudio() const { return unk1c->mOfferType == 0; }

bool StoreOffer::HasGenre() const { return unk1c->mOfferType != 2; }
bool StoreOffer::HasVocalParts() const { return unk1c->mVocalParts > 0; }

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(StoreOffer)
    HANDLE_EXPR(short_name, ShortName())
    HANDLE_EXPR(offer_type, OfferType())
    HANDLE_EXPR(offer_name, OfferName())
    HANDLE_EXPR(description, Description())
    HANDLE_EXPR(description_data, (DescriptionData(_msg->Obj<UILabel>(2)), kDataArray))
    HANDLE_EXPR(is_new_release, IsNewRelease())
    HANDLE_EXPR(year_released, YearReleased())
    HANDLE_EXPR(genre, Genre())
    HANDLE_EXPR(sub_genre, SubGenre())
    HANDLE_EXPR(cost_str, CostStr())
    HANDLE_EXPR(in_library, InLibrary())
    HANDLE_EXPR(is_available, IsAvailable())
    HANDLE_EXPR(is_purchased, IsPurchased())
    HANDLE_EXPR(has_available_pack, IsAvailable())
    HANDLE_EXPR(has_available_album, IsAvailable())
    HANDLE_EXPR(pack_name, mPack.unk1c ? mPack.unk1c->GetName() : "")
    HANDLE_EXPR(album_name, mAlbum.unk1c ? mAlbum.unk1c->GetName() : "")
    HANDLE_EXPR(is_completely_unavailable, IsCompletelyUnavailable())
    HANDLE_EXPR(is_test, IsTest())
    HANDLE_EXPR(pack_first_letter, PackFirstLetter())
    HANDLE_EXPR(release_date_str, ReleaseDateStr())
    HANDLE_EXPR(review, Review())
    HANDLE_EXPR(artist, Artist())
    HANDLE_EXPR(rank, PartRank(_msg->Sym(2)))
    HANDLE_EXPR(label, Label())
    HANDLE_EXPR(author, Author())
    HANDLE_EXPR(language, Language())
    HANDLE_EXPR(vocal_parts, VocalParts())
    HANDLE_EXPR(preview_audio, PreviewAudio())
    HANDLE_EXPR(preview_art, PreviewArt())
    HANDLE_EXPR(rating, RatingSym())
    HANDLE_EXPR(has_preview_audio, HasPreviewAudio())
    HANDLE_EXPR(has_genre, HasGenre())
    HANDLE_EXPR(has_vocal_parts, HasVocalParts())
    HANDLE_EXPR(has_preview_art, HasPreviewArt())
    HANDLE_EXPR(first_char_artist, FirstCharArtist(_msg->Int(2)))
    HANDLE_EXPR(first_char_name, FirstCharName(_msg->Int(2)))
    HANDLE_EXPR(album_link, AlbumLink())
    HANDLE_EXPR(pack_link, PackLink())
    HANDLE_EXPR(rating_num, Rating())
    HANDLE_EXPR(has_rating, Rating() != 0)
    // HANDLE_EXPR(price, )
    HANDLE_EXPR(is_downloaded, IsDownloaded())
    HANDLE_EXPR(is_partially_downloaded, IsPartiallyDownloaded())
    HANDLE_EXPR(is_partially_purchased, IsPartiallyPurchased())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x673)
END_HANDLERS
#pragma pop