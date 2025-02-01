#include "meta/StoreOffer.h"
#include "meta/StorePackedMetadata.h"
#include "meta/Sorting.h"
#include "os/CommerceMgr_Wii.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

DataArray *gStoreOfferDescriptionArray;

namespace {
    bool gSetup;
    const char *LQUOTE = "\"";
    const char *RQUOTE = "\"";
    const char *RQUOTE_COMMA = ",\"";
    const char *BY_DASH = "--";
    const char *BY = "by";
    const char *AND = "and";
    const char *SONG_CREDITS = "Song credits at RockBand.com.";
    const char *ALBUM_INCLUDES = "Includes";
    const char *PACK_INCLUDES = "This pack includes";
}

const char *gGenreStrs[] = { "alternative", "blues",        "classicrock",
                             "country",     "emo",          "fusion",
                             "glam",        "grunge",       "indierock",
                             "jazz",        "metal",        "new_wave",
                             "novelty",     "numetal",      "other",
                             "poprock",     "prog",         "punk",
                             "rock",        "southernrock", "urban",
                             "classical",   "hiphoprap",    "inspirational",
                             "jrock",       "latin",        "popdanceelectronic",
                             "rbsoulfunk",  "reggaeska",    "world" };

const char *gSubGenreStrs[] = { "subgenre_acapella",
                                "subgenre_acidjazz",
                                "subgenre_acoustic",
                                "subgenre_alternative",
                                "subgenre_alternativerap",
                                "subgenre_ambient",
                                "subgenre_arena",
                                "subgenre_black",
                                "subgenre_bluegrass",
                                "subgenre_blues",
                                "subgenre_breakbeat",
                                "subgenre_chicago",
                                "subgenre_chiptune",
                                "subgenre_classic",
                                "subgenre_classicrock",
                                "subgenre_classical",
                                "subgenre_college",
                                "subgenre_contemporary",
                                "subgenre_contemporaryfolk",
                                "subgenre_core",
                                "subgenre_country",
                                "subgenre_dance",
                                "subgenre_dancepunk",
                                "subgenre_darkwave",
                                "subgenre_death",
                                "subgenre_delta",
                                "subgenre_disco",
                                "subgenre_downtempo",
                                "subgenre_drumandbass",
                                "subgenre_dub",
                                "subgenre_electric",
                                "subgenre_electronica",
                                "subgenre_electroclash",
                                "subgenre_emo",
                                "subgenre_experimental",
                                "subgenre_folkrock",
                                "subgenre_funk",
                                "subgenre_fusion",
                                "subgenre_gangsta",
                                "subgenre_garage",
                                "subgenre_glam",
                                "subgenre_goth",
                                "subgenre_grunge",
                                "subgenre_hair",
                                "subgenre_hardrock",
                                "subgenre_hardcore",
                                "subgenre_hardcoredance",
                                "subgenre_hardcorerap",
                                "subgenre_hiphop",
                                "subgenre_honkytonk",
                                "subgenre_house",
                                "subgenre_indierock",
                                "subgenre_industrial",
                                "subgenre_lofi",
                                "subgenre_mathrock",
                                "subgenre_metal",
                                "subgenre_motown",
                                "subgenre_new_wave",
                                "subgenre_noise",
                                "subgenre_novelty",
                                "subgenre_numetal",
                                "subgenre_oldschoolhiphop",
                                "subgenre_oldies",
                                "subgenre_other",
                                "subgenre_outlaw",
                                "subgenre_pop",
                                "subgenre_postrock",
                                "subgenre_power",
                                "subgenre_prog",
                                "subgenre_progrock",
                                "subgenre_psychadelic",
                                "subgenre_reggae",
                                "subgenre_ragtime",
                                "subgenre_rap",
                                "subgenre_rhythmandblues",
                                "subgenre_rock",
                                "subgenre_rockandroll",
                                "subgenre_rockabilly",
                                "subgenre_shoegazing",
                                "subgenre_ska",
                                "subgenre_smooth",
                                "subgenre_softrock",
                                "subgenre_soul",
                                "subgenre_southernrock",
                                "subgenre_speed",
                                "subgenre_surf",
                                "subgenre_synth",
                                "subgenre_techno",
                                "subgenre_teen",
                                "subgenre_thrash",
                                "subgenre_traditionalfolk",
                                "subgenre_trance",
                                "subgenre_triphop",
                                "subgenre_undergroundrap" };

inline StorePackedSong *StorePackedOffer::GetPackedSong(int idx) const {
    return &TheStoreMetadata.mSongTable->mSongs[mSongs[idx]];
}

inline StorePackedSong *StorePackedRBNOffer::GetPackedSong(int idx) const {
    return &TheStoreMetadata.mSongTable->mSongs[mSongs[idx]];
}

StorePurchaseable::StorePurchaseable() {
    mPackedData = nullptr;
    mOfferState = 0;
}

bool StorePurchaseable::Exists() const { return mOfferState; }

const char *StorePurchaseable::CostStr() const {
    if (mOfferState->mPrice == 9999)
        return " ";
    else
        return MakeString("%i", mOfferState->mPrice);
}

unsigned long long StorePurchaseable::GetTitleId() const {
    return WiiCommerceMgr::MakeDataTitleId(GetPackedSong(0)->GetDataTitle());
}

unsigned long long StorePurchaseable::GetUpgradeTitleId() const {
    return WiiCommerceMgr::MakeDataTitleId(GetPackedSong(0)->GetUpgradeDataTitle());
}

void StorePurchaseable::GetContentIndexes(std::vector<unsigned short> &vec, bool b) const {
    vec.clear();
    vec.reserve(mPackedData->mNumSongs);
    for (int i = 0; i < mPackedData->mNumSongs; i++) {
        StorePackedSong *song = GetPackedSong(i);
        if (b) {
            unsigned short push = song->unk10;
            if (push != 0)
                vec.push_back(push);
        } else {
            unsigned short push = song->unka;
            vec.push_back(push);
            vec.push_back(push + 1);
        }
    }
}

bool operator==(const StoreOffer *o, Symbol s) { return o->ShortName() == s; }

Symbol StoreOffer::Decade() const {
    int year = YearReleased();
    return MakeString("the%is", year - (year % 10));
}

Symbol StoreOffer::LengthSym() const {
    MILO_WARN("store metadata should have song length\n");
    return song_length_short;
}

void SetupStoreOfferLocals() {
    if (!gSetup) {
        Symbol lang = SystemLanguage();
        if (lang == eng) {
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "by";
            AND = "and";
            SONG_CREDITS = "Song credits at RockBand.com.";
            ALBUM_INCLUDES = "Includes";
            PACK_INCLUDES = "This pack includes";
        } else if (lang == fre) {
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "par";
            BY = "par";
            AND = "et";
            SONG_CREDITS = "Rends-toi sur www.RockBand.com pour les cr\xe9"
                           "dits des musiques. (site en anglais)";
            ALBUM_INCLUDES = "Cet album comprend";
            PACK_INCLUDES = "Ce pack comprend";
        } else if (lang == ita) {
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "di";
            AND = "e";
            SONG_CREDITS =
                "Per i riconoscimenti dei brani, visita il sito Web www.RockBand.com.";
            ALBUM_INCLUDES = "Questo album include";
            PACK_INCLUDES = "Questo pachetto include";
        } else if (lang == deu) {
            LQUOTE = ",,";
            RQUOTE = "\"";
            RQUOTE_COMMA = "\",";
            BY_DASH = "--";
            BY = "von";
            AND = "und";
            SONG_CREDITS = "Songinfos gibt es unter www.RockBand.com.";
            ALBUM_INCLUDES = "Diese Album enth\xe4"
                             "lt";
            PACK_INCLUDES = "Diese Sammlung enth\xe4"
                            "lt";
        } else if (lang == esl) {
            LQUOTE = "\"";
            RQUOTE = "\"";
            RQUOTE_COMMA = ",\"";
            BY_DASH = "--";
            BY = "de";
            AND = "y";
            SONG_CREDITS = "Para ver los cr\xe9"
                           "ditos de la m\xfa"
                           "sica, visita www.RockBand.com.";
            ALBUM_INCLUDES = "Este album incluye las canciones";
            PACK_INCLUDES = "Este paquete incluye las canciones";
        }
        gSetup = true;
    }
}

void UpdatePurchasable(StorePurchaseable *p) {
    if (p->mPackedData) {
        StoreOfferState *status = TheStoreMetadata.GetOfferStatus(p->mPackedData);
        if (status != 0)
            p->mOfferState = status;
    }
}

StoreOffer::StoreOffer(const StorePackedOfferBase *base, SongMgr *mgr, bool b)
    : mSongMgr(mgr) {
    mPackedData = base;
    UpdatePurchasable(this);
    StoreOfferType ty = mPackedData->OfferType();
    SetupStoreOfferLocals();
    mAlbum.mPackedData = nullptr;
    if (mPackedData->mAlbumLink && ty == kStoreOfferSong) {
        StorePage *page = TheStoreMetadata.LoadPage(mPackedData->mAlbumLink);
        if (!page) {
            MILO_WARN(
                "Offer %s has pack link, but page not found.\n", mPackedData->GetName()
            );
        } else {
            UpdatePurchasable(&mAlbum);
        }
        //     iVar3 = StoreMetadataManager::LoadPage(TheStoreMetadata);
        //     if (iVar3 == 0) {
        //       StorePackedOfferBase::GetName(*(undefined4 *)(this + 0x1c));
        //     }
        //     else {
        //       iVar4 = fn_8028F9C4();
        //       if ((iVar4 != 0) && (iVar4 = fn_80290204(iVar3), iVar4 != 0)) {
        //         iVar4 = fn_8051A1E4(iVar3,0);
        //         if (iVar4 == 0) {
        //           uVar5 = StorePage::Offer(iVar3,0);
        //         }
        //         else {
        //           uVar5 = StorePage::RbnOffer(iVar3,0);
        //         }
        //         *(undefined4 *)(this + 0x40) = uVar5;
        //         UpdatePurchasable(this + 0x24);
        //       }
        //     }
    }
    mPack.mPackedData = nullptr;
    if (mPackedData->mPackLink && ty == kStoreOfferSong) {
        //     iVar2 = StoreMetadataManager::LoadPage(TheStoreMetadata);
        //     if (iVar2 == 0) {
        //       StorePackedOfferBase::GetName(*(undefined4 *)(this + 0x1c));
        //     }
        //     else {
        //       iVar3 = fn_8028F9C4();
        //       if ((iVar3 != 0) && (iVar3 = fn_80290204(iVar2), iVar3 != 0)) {
        //         iVar3 = fn_8051A1E4(iVar2,0);
        //         if (iVar3 == 0) {
        //           uVar5 = StorePage::Offer(iVar2,0);
        //         }
        //         else {
        //           uVar5 = StorePage::RbnOffer(iVar2,0);
        //         }
        //         *(undefined4 *)(this + 100) = uVar5;
        //         UpdatePurchasable(this + 0x48);
        //       }
        //     }
    }
    DateTime dt(0, 0, 0, 0, 0, 0);
    unk6c = Localize(store_release_date_format, 0);
    dt.Format(unk6c);
    if (mPackedData->mNumSongs == 0) {
        MILO_WARN("%s does not have song_ids", OfferName());
    }
}

StoreOffer::~StoreOffer() {}

Symbol StoreOffer::ShortName() const {
    if (mPackedData->OfferType() == kStoreOfferSong) {
        return GetPackedSong(0)->GetShortName();
    } else {
        return mPackedData->GetOfferId().c_str();
    }
}

Symbol StoreOffer::OfferType() const {
    switch (mPackedData->OfferType()) {
    case kStoreOfferAlbum:
        return "album";
    case kStoreOfferPack:
        return "pack";
    default:
        return "song";
    }
}

#pragma push
#pragma force_active on
inline const char *StoreOffer::OfferName() const { return mPackedData->GetName(); }
#pragma pop

bool StoreOffer::IsNewRelease() const { return mPackedData->mNewRelease; }

const char *StoreOffer::Description() const {
    StoreOfferType ty = mPackedData->OfferType();
    String str;
    int numSongs = mPackedData->mNumSongs;
    if (ty == kStoreOfferAlbum) {
        str = ALBUM_INCLUDES;
        str += " ";
    } else {
        if (ty != kStoreOfferPack) {
            return MakeString(
                "%s%s%s %s %s. %s",
                LQUOTE,
                mPackedData->GetName(),
                RQUOTE,
                BY_DASH,
                mPackedData->GetArtist(),
                SONG_CREDITS
            );
        }
        str = PACK_INCLUDES;
        str += " ";
        if (mPackedData->IsVariousArtist()) {
            int i = 0;
            for (; i < numSongs - 1; i++) {
                StorePackedSong *song = GetPackedSong(i);
                str += LQUOTE;
                str += song->GetName();
                str += RQUOTE;
                str += " ";
                str += BY;
                str += " ";
                str += song->GetArtist();
                str += ", ";
            }
            str += AND;
            str += " ";
            StorePackedSong *song = GetPackedSong(i);
            str += LQUOTE;
            str += song->GetName();
            str += RQUOTE;
            str += " ";
            str += BY;
            str += " ";
            str += song->GetArtist();
            str += ". ";
            str += SONG_CREDITS;
            return MakeString("%s", str.c_str());
        }
    }

    int i = 0;
    for (; i < numSongs - 1; i++) {
        StorePackedSong *song = GetPackedSong(i);
        str += LQUOTE;
        str += song->GetName();
        str += RQUOTE_COMMA;
        str += " ";
    }
    StorePackedSong *song = GetPackedSong(i);
    str += AND;
    str += " ";
    str += LQUOTE;
    str += song->GetName();
    str += RQUOTE;
    str += " ";
    str += BY;
    str += " ";
    str += mPackedData->GetArtist();
    str += ". ";
    str += SONG_CREDITS;
    return MakeString("%s", str.c_str());
}

bool StoreOffer::IsTest() const { return true; }
int StoreOffer::NumSongs() const { return mPackedData->mNumSongs; }

bool StoreOffer::HasSong(const StoreOffer *offer) const {
    if (IsRbn() && offer->IsRbn()) {
        StorePackedSong *otherSong = offer->mPackedRbnOffer->GetPackedSong(0);
        for (int i = 0; i < mPackedRbnOffer->mNumSongs; i++) {
            if (mPackedRbnOffer->GetPackedSong(i) == otherSong)
                return true;
        }
    } else if (!IsRbn() && !offer->IsRbn()) {
        StorePackedSong *otherSong = offer->mPackedOffer->GetPackedSong(0);
        for (int i = 0; i < mPackedData->mNumSongs; i++) {
            if (mPackedOffer->GetPackedSong(i) == otherSong)
                return true;
        }
    }
    return false;
}

float StoreOffer::PartRank(Symbol part) const {
    if (part == vocals) {
        return mPackedData->mRanks.mVocals;
    } else if (part == guitar) {
        return mPackedData->mRanks.mGuitar;
    } else if (part == bass) {
        return mPackedData->mRanks.mBass;
    } else if (part == drum) {
        return mPackedData->mRanks.mDrums;
    } else if (part == keys) {
        return mPackedData->mRanks.mKeys;
    } else if (part == real_guitar) {
        return mPackedData->mRanks.mRealGuitar;
    } else if (part == real_bass) {
        return mPackedData->mRanks.mRealBass;
    } else if (part == real_keys) {
        return mPackedData->mRanks.mRealKeys;
    } else
        return mPackedData->mRanks.mBand;
}

Symbol StoreOffer::Genre() const {
    if (mPackedData->OfferType() != kStoreOfferPack) {
        return gGenreStrs[Clamp(0, 29, mPackedData->Genre())];
    } else
        return gNullStr;
}

Symbol StoreOffer::SubGenre() const {
    return gSubGenreStrs[Clamp(0, 0x5D, mPackedRbnOffer->SubGenre())];
}

Symbol StoreOffer::RatingSym() const {
    return MakeString("rating_%i", (int)mPackedData->mRating);
}

Symbol StoreOffer::VocalPartsSym() const {
    return MakeString("vocal_parts_%i", (int)mPackedData->mVocalParts);
}

#pragma push
#pragma force_active on
inline const char *StoreOffer::Artist() const { return mPackedData->GetArtist(); }
#pragma pop

const char *StoreOffer::AlbumName() const { return mPackedData->GetAlbumName(); }

const char *StoreOffer::PreviewArt() const {
    if (IsRbn())
        return mPackedRbnOffer->GetArtPath();
    else
        return mPackedOffer->GetArtPath();
}

const char *StoreOffer::PreviewAudio() const {
    if (IsRbn())
        return mPackedRbnOffer->GetPreviewPath();
    else
        return mPackedOffer->GetPreviewPath();
}

bool StoreOffer::IsCover() const { return mPackedData->mCover; }
int StoreOffer::Rating() const { return mPackedData->mRating; }
int StoreOffer::VocalParts() const { return mPackedData->mVocalParts; }

float StoreOffer::Review() const {
    MILO_ASSERT(IsRbn(), 0x4F3);
    return mPackedData->mReview;
}

inline const char *StorePackedRBNOffer::LabelStr() const {
    return TheStoreMetadata.GetString(mLabelIndex);
}

Symbol StoreOffer::Label() const {
    MILO_ASSERT(IsRbn(), 0x4FA);
    return mPackedRbnOffer->LabelStr();
}

inline const char *StorePackedRBNOffer::AuthorStr() const {
    return TheStoreMetadata.GetString(mAuthorIndex);
}

Symbol StoreOffer::Author() const {
    MILO_ASSERT(IsRbn(), 0x501);
    return mPackedRbnOffer->AuthorStr();
}

Symbol StoreOffer::Language() const {
    MILO_ASSERT(IsRbn(), 0x508);
    Symbol ret = eng;
    switch (mPackedRbnOffer->Language()) {
    case 1:
        ret = fre;
        break;
    case 2:
        ret = ita;
        break;
    case 3:
        ret = esl;
        break;
    case 4:
        ret = deu;
        break;
    }
    return ret;
}

const char *StoreOffer::AlbumLink() const {
    return MakeString("%d", (int)mPackedData->mAlbumLink);
}

const char *StoreOffer::PackLink() const {
    return MakeString("%d", (int)mPackedData->mPackLink);
}

#pragma push
#pragma force_active on
inline int StoreOffer::YearReleased() const { return mPackedData->mYearReleased + 1900; }
#pragma pop

const char *StoreOffer::ReleaseDateStr() const { return unk6c.c_str(); }

bool StoreOffer::HasArtist() const {
    const char *artist = mPackedData->GetArtist();
    return artist && *artist;
}

bool StoreOffer::HasPreviewAudio() const { return mPackedData->OfferType() == 0; }

bool StoreOffer::HasGenre() const { return mPackedData->OfferType() != 2; }
bool StoreOffer::HasVocalParts() const { return mPackedData->mVocalParts > 0; }
bool StoreOffer::HasPreviewArt() const { return true; }

Symbol StoreOffer::FirstCharName(bool b) const {
    return FirstSortChar(mPackedData->GetName(), b);
}

Symbol StoreOffer::FirstCharArtist(bool b) const {
    return FirstSortChar(mPackedData->GetArtist(), b);
}

Symbol StoreOffer::PackFirstLetter() const {
    if (mPackedData->OfferType() == kStoreOfferPack) {
        return FirstCharName(true);
    } else
        return gNullStr;
}

bool StoreOffer::InLibrary() const {
    bool hasSongs = mPackedData->mNumSongs != 0;
    for (int i = 0; i < mPackedData->mNumSongs; i++) {
        StorePackedSong *song = GetPackedSong(i);
        int songID = song->mSongID;
        if (!mSongMgr || !mSongMgr->HasSong(songID)) {
            hasSongs = false;
            break;
        }
    }
    return hasSongs;
}

unsigned int StoreOffer::GetSingleSongID() const {
    MILO_ASSERT(mPackedData->mNumSongs == 1, 0x587);
    return GetPackedSong(0)->mSongID;
}

bool StoreOffer::HasSolo() const {
    MILO_WARN("store metadata should have solo inclusion\n");
    return false;
}

bool StoreOffer::IsCompletelyUnavailable() const {
    return !IsAvailable() && !mPack.IsAvailable() && !mAlbum.IsAvailable();
}

DataArray *StoreOffer::DescriptionData(UILabel *label) const {
    RndText *text = label->TextObj();
    text->SetFont(label->Font());
    String str(Description());
    std::vector<RndText::Line> lines;
    float f44, f48;
    const char *c28;
    text->GetStringDimensions(f44, f48, lines, c28, text->Size());
    if (!gStoreOfferDescriptionArray) {
        gStoreOfferDescriptionArray = new DataArray(lines.size());
    } else
        gStoreOfferDescriptionArray->Resize(lines.size());
    for (std::vector<RndText::Line>::iterator it = lines.begin(); it != lines.end();
         ++it) {
        MILO_WARN("line: %d - %d: %s\n"); // just here for the stringbase
    }
    return gStoreOfferDescriptionArray;
}

void MakeOfferSortString(char *cc, const StoreOffer *offer) {
    CalculateAlphaKey(cc, offer->Artist(), true);
    int cclen = strlen(cc);
    cc[cclen] = ' ';
    char *cc_offset = &cc[cclen + 1];
    *cc_offset = '\0';
    const char *cc5 = "";
    if (offer->mPackedData->OfferType() == kStoreOfferAlbum) {
        cc5 = offer->OfferName();
    } else if (offer->mAlbum.mPackedData && offer->mAlbum.IsPurchased()) {
        cc5 = offer->mAlbum.mPackedData->GetName();
    } else if (offer->mPackedData->OfferType() == kStoreOfferPack) {
        cc5 = offer->OfferName();
    } else if (offer->mPack.mPackedData && offer->mPack.IsPurchased()) {
        cc5 = offer->mPack.mPackedData->GetName();
    }
    CalculateAlphaKey(cc_offset, cc5, true);
    cc_offset += strlen(cc_offset);
    cc_offset[0] = ' ';
    cc_offset[1] = '\0';
    if (offer->mPackedData->OfferType() == kStoreOfferSong) {
        CalculateAlphaKey(cc_offset, offer->mPackedData->GetName(), true);
    }
}

#pragma push
#pragma force_active on
inline bool StorePurchaseable::IsPurchased() const {
    return mOfferState && mOfferState->mFlags & 1;
}
#pragma pop

bool StoreOfferSort(const StoreOffer *o1, const StoreOffer *o2) {
    char buf1[1024];
    char buf2[1024];
    MakeOfferSortString(buf1, o1);
    MakeOfferSortString(buf2, o2);
    return strcmp(buf1, buf2) < 0;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(StoreOffer)
    HANDLE_EXPR(short_name, ShortName())
    HANDLE_EXPR(offer_type, OfferType())
    HANDLE_EXPR(offer_name, OfferName())
    HANDLE_EXPR(description, Description())
    HANDLE_EXPR(
        description_data, DataNode(DescriptionData(_msg->Obj<UILabel>(2)), kDataArray)
    )
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
    HANDLE_EXPR(price, mOfferState->mPrice)
    HANDLE_EXPR(is_downloaded, IsDownloaded())
    HANDLE_EXPR(is_partially_downloaded, IsPartiallyDownloaded())
    HANDLE_EXPR(is_partially_purchased, IsPartiallyPurchased())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x673)
END_HANDLERS
#pragma pop