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

const char* gGenreStrs[] = {
    "alternative", "blues", "classicrock", "country", "emo", "fusion", "glam",
    "grunge", "indierock", "jazz", "metal", "new_wave", "novelty", "numetal",
    "other", "poprock", "prog", "punk", "rock", "southernrock", "urban",
    "classical", "hiphoprap", "inspirational", "jrock", "latin", "popdanceelectronic",
    "rbsoulfunk", "reggaeska", "world"
};

const char* gSubGenreStrs[] = {
    "subgenre_acapella", "subgenre_acidjazz", "subgenre_acoustic", "subgenre_alternative", "subgenre_alternativerap",
    "subgenre_ambient", "subgenre_arena", "subgenre_black", "subgenre_bluegrass", "subgenre_blues",
    "subgenre_breakbeat", "subgenre_chicago", "subgenre_chiptune", "subgenre_classic", "subgenre_classicrock",
    "subgenre_classical", "subgenre_college", "subgenre_contemporary", "subgenre_contemporaryfolk", "subgenre_core",
    "subgenre_country", "subgenre_dance", "subgenre_dancepunk", "subgenre_darkwave", "subgenre_death",
    "subgenre_delta", "subgenre_disco", "subgenre_downtempo", "subgenre_drumandbass", "subgenre_dub",
    "subgenre_electric", "subgenre_electronica", "subgenre_electroclash", "subgenre_emo", "subgenre_experimental",
    "subgenre_folkrock", "subgenre_funk", "subgenre_fusion", "subgenre_gangsta", "subgenre_garage",
    "subgenre_glam", "subgenre_goth", "subgenre_grunge", "subgenre_hair", "subgenre_hardrock",
    "subgenre_hardcore", "subgenre_hardcoredance", "subgenre_hardcorerap", "subgenre_hiphop", "subgenre_honkytonk",
    "subgenre_house", "subgenre_indierock", "subgenre_industrial", "subgenre_lofi", "subgenre_mathrock",
    "subgenre_metal", "subgenre_motown", "subgenre_new_wave", "subgenre_noise", "subgenre_novelty",
    "subgenre_numetal", "subgenre_oldschoolhiphop", "subgenre_oldies", "subgenre_other", "subgenre_outlaw",
    "subgenre_pop", "subgenre_postrock", "subgenre_power", "subgenre_prog", "subgenre_progrock",
    "subgenre_psychadelic", "subgenre_reggae", "subgenre_ragtime", "subgenre_rap", "subgenre_rhythmandblues",
    "subgenre_rock", "subgenre_rockandroll", "subgenre_rockabilly", "subgenre_shoegazing", "subgenre_ska",
    "subgenre_smooth", "subgenre_softrock", "subgenre_soul", "subgenre_southernrock", "subgenre_speed",
    "subgenre_surf", "subgenre_synth", "subgenre_techno", "subgenre_teen", "subgenre_thrash",
    "subgenre_traditionalfolk", "subgenre_trance", "subgenre_triphop", "subgenre_undergroundrap"
};

StorePurchaseable::StorePurchaseable() {
    mPackedData = nullptr;
    mOfferState = 0;
}

bool StorePurchaseable::Exists() const {
    return mOfferState;
}

const char* StorePurchaseable::CostStr() const {
    if(mOfferState->unk0 == 9999) return " ";
    else return MakeString("%i", mOfferState->unk0);
}

void StorePurchaseable::GetContentIndexes(std::vector<unsigned short>& vec, bool b) const {
    vec.clear();
    vec.reserve(mPackedData->mNumSongs);
}

bool operator==(const StoreOffer* o, Symbol s){
    return o->ShortName() == s;
}

Symbol StoreOffer::Decade() const {
    int year = YearReleased();
    return MakeString("the%is", year - (year % 10));
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
            SONG_CREDITS = "Rends-toi sur www.RockBand.com pour les cr\xe9""dits des musiques. (site en anglais)";
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
            ALBUM_INCLUDES = "Diese Album enth\xe4""lt";
            PACK_INCLUDES = "Diese Sammlung enth\xe4""lt";
        }
        else if(lang == esl){
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "de";
            AND = "y";
            SONG_CREDITS = "Para ver los cr\xe9""ditos de la m\xfa""sica, visita www.RockBand.com.";
            ALBUM_INCLUDES = "Este album incluye las canciones";
            PACK_INCLUDES = "Este paquete incluye las canciones";
        }
        gSetup = true;
    }
}

void UpdatePurchasable(StorePurchaseable* p){
    if(p->mPackedData){
        StoreOfferState* status = TheStoreMetadata.GetOfferStatus(p->mPackedData);
        if(status != 0) p->mOfferState = status;
    }
}

StoreOffer::StoreOffer(const StorePackedOfferBase* base, SongMgr* mgr, bool b) : unk78(mgr) {
    mPackedData = base;
    UpdatePurchasable(this);
    SetupStoreOfferLocals();
}

StoreOffer::~StoreOffer(){

}

Symbol StoreOffer::OfferType() const {
    switch(mPackedData->OfferType()){
        case kStoreOfferAlbum: return "album";
        case kStoreOfferPack: return "pack";
        default: return "song";
    }
}

const char* StoreOffer::OfferName() const {
    return mPackedData->GetName();
}

bool StoreOffer::IsNewRelease() const { return mPackedData->mNewRelease; }

int StoreOffer::NumSongs() const { return mPackedData->mNumSongs; }

float StoreOffer::PartRank(Symbol part) const {
    if(part == vocals){
        return mPackedData->mRanks.mVocals;
    }
    else if(part == guitar){
        return mPackedData->mRanks.mGuitar;
    }
    else if(part == bass){
        return mPackedData->mRanks.mBass;
    }
    else if(part == drum){
        return mPackedData->mRanks.mDrums;
    }
    else if(part == keys){
        return mPackedData->mRanks.mKeys;
    }
    else if(part == real_guitar){
        return mPackedData->mRanks.mRealGuitar;
    }
    else if(part == real_bass){
        return mPackedData->mRanks.mRealBass;
    }
    else if(part == real_keys){
        return mPackedData->mRanks.mRealKeys;
    }
    else return mPackedData->mRanks.mBand;
}

Symbol StoreOffer::Genre() const {
    if(mPackedData->OfferType() != kStoreOfferPack){
        return gGenreStrs[Clamp(0, 29, mPackedData->Genre())];
    }
    else return gNullStr;
}

Symbol StoreOffer::SubGenre() const {
    return gSubGenreStrs[Clamp(0, 0x5D, (int)mPackedRbnOffer->mSubGenre)];
}

Symbol StoreOffer::RatingSym() const {
    return MakeString("rating_%i", (int)mPackedData->mRating);
}

Symbol StoreOffer::VocalPartsSym() const {
    return MakeString("vocal_parts_%i", (int)mPackedData->mVocalParts);
}

const char* StoreOffer::Artist() const {
    return mPackedData->GetArtist();
}

const char* StoreOffer::AlbumName() const {
    return mPackedData->GetAlbumName();
}

const char* StoreOffer::PreviewArt() const {
    if(IsRbn()) return mPackedRbnOffer->GetArtPath();
    else return mPackedOffer->GetArtPath();
}

const char* StoreOffer::PreviewAudio() const {
    if(IsRbn()) return mPackedRbnOffer->GetPreviewPath();
    else return mPackedOffer->GetPreviewPath();
}

bool StoreOffer::IsCover() const { return mPackedData->mCover; }
int StoreOffer::Rating() const { return mPackedData->mRating; }
int StoreOffer::VocalParts() const { return mPackedData->mVocalParts; }

float StoreOffer::Review() const {
    MILO_ASSERT(IsRbn(), 0x4F3);
    return mPackedData->mReview;
}

const char* StoreOffer::AlbumLink() const {
    return MakeString("%d", (int)mPackedData->mAlbumLink);
}

const char* StoreOffer::PackLink() const {
    return MakeString("%d", (int)mPackedData->mPackLink);
}

#pragma push
#pragma force_active on
inline int StoreOffer::YearReleased() const { return mPackedData->mYearReleased + 1900; }
#pragma pop

const char* StoreOffer::ReleaseDateStr() const { return unk6c.c_str(); }

bool StoreOffer::HasArtist() const {
    const char* artist = mPackedData->GetArtist();
    return artist && *artist;
}

bool StoreOffer::HasPreviewAudio() const { return mPackedData->OfferType() == 0; }

bool StoreOffer::HasGenre() const { return mPackedData->OfferType() != 2; }
bool StoreOffer::HasVocalParts() const { return mPackedData->mVocalParts > 0; }
bool StoreOffer::HasPreviewArt() const { return true; }

int StoreOffer::GetSingleSongID() const {
    MILO_ASSERT(mPackedData->mNumSongs == 1, 0x587);
}

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
    HANDLE_EXPR(subgenre, SubGenre())
    HANDLE_EXPR(cost_str, CostStr())
    HANDLE_EXPR(in_library, InLibrary())
    HANDLE_EXPR(is_available, IsAvailable())
    HANDLE_EXPR(is_purchased, IsPurchased())
    HANDLE_EXPR(has_available_pack, mPack.IsAvailable())
    HANDLE_EXPR(has_available_album, mAlbum.IsAvailable())
    HANDLE_EXPR(pack_name, mPack.mPackedData ? mPack.mPackedData->GetName() : "")
    HANDLE_EXPR(album_name, mAlbum.mPackedData ? mAlbum.mPackedData->GetName() : "")
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