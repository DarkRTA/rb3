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

StorePurchaseable::StorePurchaseable() {
    mPacked.mPackedData = nullptr;
    unk20 = 0;
}

bool StorePurchaseable::Exists() const {
    return unk20;
}

const char* StorePurchaseable::CostStr() const {
    if(mPacked.mPackedData) return " ";
    else return "%i";
}

bool operator==(const StoreOffer* o, Symbol s){
    return o->ShortName() == s;
}

Symbol StoreOffer::Decade() const {
    int year = ((YearReleased() + 1900) / 10) * 10;
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
        else if(lang == fre){
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "par";
            BY = "par";
            AND = "et";
            SONG_CREDITS = "Rends-toi sur www.RockBand.com pour les crédits des musiques. (site en anglais)";
            ALBUM_INCLUDES = "Cet album comprend";
            PACK_INCLUDES = "Ce pack comprend";
        }
        else if(lang == ita){
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "di";
            AND = "e";
            SONG_CREDITS = "Per i riconoscimenti dei brani, visita il sito Web www.RockBand.com.";
            ALBUM_INCLUDES = "Questo album include";
            PACK_INCLUDES = "Questo pachetto include";
        }
        else if(lang == deu){
            LQUOTE = ",,";
            RQUOTE = "\"";
            RQUOTE_COMMA = "\",";
            BY_DASH = "--";
            BY = "von";
            AND = "und";
            SONG_CREDITS = "Songinfos gibt es unter www.RockBand.com.";
            ALBUM_INCLUDES = "Diese Album enthält";
            PACK_INCLUDES = "Diese Sammlung enthält";
        }
        else if(lang == esl){
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "de";
            AND = "y";
            SONG_CREDITS = "Para ver los créditos de la música, visita www.RockBand.com.";
            ALBUM_INCLUDES = "Este album incluye las canciones";
            PACK_INCLUDES = "Este paquete incluye las canciones";
        }
        gSetup = true;
    }
}

void UpdatePurchasable(StorePurchaseable* p){
    if(p->mPacked.mPackedData){
        int status = TheStoreMetadata.GetOfferStatus(p->mPacked.mPackedData);
        if(status != 0) p->unk20 = status;
    }
}

StoreOffer::StoreOffer(const StorePackedOfferBase* base, SongMgr* mgr, bool b) : unk74(mgr) {
    mPacked.mPackedData = base;
    UpdatePurchasable(this);
}

StoreOffer::~StoreOffer(){

}

Symbol StoreOffer::OfferType() const {
    switch(mPacked.mPackedData->OfferType()){
        case kStoreOfferAlbum: return "album";
        case kStoreOfferPack: return "pack";
        default: return "song";
    }
}

const char* StoreOffer::OfferName() const {
    return mPacked.mPackedData->GetName();
}

bool StoreOffer::IsNewRelease() const { return mPacked.mPackedData->mNewRelease; }

float StoreOffer::PartRank(Symbol s) const {
//   iVar1 = *(int *)param_1.mStr;
//   if (iVar1 == vocals) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x2b) >> 0xc & 0x3ff);
//   }
//   else if (iVar1 == guitar) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x2b) >> 2 & 0x3ff);
//   }
//   else if (iVar1 == bass) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x2f) >> 0x16);
//   }
//   else if (iVar1 == drum) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x2f) >> 0xc & 0x3ff);
//   }
//   else if (iVar1 == keys) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x2f) >> 2 & 0x3ff);
//   }
//   else if (iVar1 == real_guitar) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x33) >> 0x16);
//   }
//   else if (iVar1 == real_bass) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x33) >> 0xc & 0x3ff);
//   }
//   else if (iVar1 == real_keys) {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x33) >> 2 & 0x3ff);
//   }
//   else {
//     dVar2 = (double)(*(uint *)(*(int *)(this + 0x1c) + 0x2b) >> 0x16);
//   }
//   return dVar2;
}

Symbol StoreOffer::Genre() const {
    if(mPacked.mPackedData->OfferType() != kStoreOfferPack){
        return gGenreStrs[Clamp(0, 29, mPacked.mPackedData->Genre())];
    }
    else return gNullStr;
}

Symbol StoreOffer::RatingSym() const {
    return MakeString("rating_%i", mPacked.mPackedData->mRating);
}

Symbol StoreOffer::VocalPartsSym() const {
    return MakeString("vocal_parts_%i", mPacked.mPackedData->mVocalParts);
}

const char* StoreOffer::Artist() const {
    return mPacked.mPackedData->GetArtist();
}

const char* StoreOffer::AlbumName() const {
    return mPacked.mPackedData->GetAlbumName();
}

const char* StoreOffer::PreviewArt() const {
    if(IsRbn()) return mPacked.mPackedRbnOffer->GetArtPath();
    else return mPacked.mPackedOffer->GetArtPath();
}

const char* StoreOffer::PreviewAudio() const {
    if(IsRbn()) return mPacked.mPackedRbnOffer->GetPreviewPath();
    else return mPacked.mPackedOffer->GetPreviewPath();
}

bool StoreOffer::IsCover() const { return mPacked.mPackedData->mCover; }
int StoreOffer::Rating() const { return mPacked.mPackedData->mRating; }
int StoreOffer::VocalParts() const { return mPacked.mPackedData->mVocalParts; }

float StoreOffer::Review() const {
    MILO_ASSERT(IsRbn(), 0x4F3);
    // return mPacked.mPackedData->unk3b;
}

#pragma push
#pragma force_active on
inline int StoreOffer::YearReleased() const { return mPacked.mPackedData->mYearReleased + 1900; }
#pragma pop

bool StoreOffer::HasPreviewAudio() const { return mPacked.mPackedData->OfferType() == 0; }

bool StoreOffer::HasGenre() const { return mPacked.mPackedData->OfferType() != 2; }
bool StoreOffer::HasVocalParts() const { return mPacked.mPackedData->mVocalParts > 0; }
bool StoreOffer::HasPreviewArt() const { return true; }

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
    HANDLE_EXPR(pack_name, mPack.mPacked.mPackedData ? mPack.mPacked.mPackedData->GetName() : "")
    HANDLE_EXPR(album_name, mAlbum.mPacked.mPackedData ? mAlbum.mPacked.mPackedData->GetName() : "")
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