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

const char* gGenreStrs[29] = {
    "alternative", "blues", "classicrock"
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

Symbol StoreOffer::Decade() const {
    return "the%is";
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
    int offerType = unk1c->mOfferType;
    switch(offerType){
        case 1: return "album";
        case 2: return "pack";
        default: return "song";
    }
}

bool StoreOffer::IsNewRelease() const { return unk1c->mNewRelease; }

Symbol StoreOffer::Genre() const {
    if(unk1c->mOfferType != 2){
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