#include "Award.h"
#include "os/Debug.h"
#include "system/utl/Symbols2.h"

Award::Award(DataArray* configure, int index) : mName(""), mIconArt(""), mIndex(index), mDescription("") {
    Configure(configure);
}

Award::~Award() {

}

void Award::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x1e);

    mName = i_pConfig->Sym(0);
}

Symbol Award::GetName() const{
    return mName;
}

Symbol Award::GetDescription() const{
    if(HasAssets()){
        return award_genericdesc;
    }
    return mDescription;
}

Symbol Award::GetDisplayName() const{
    bool hasAssets = HasAssets();
    if(hasAssets){
        return Symbol(award_generic);
    }
    return Symbol(award_generic);
}

bool Award::HasIconArt() const {
    bool noIcon;

    if (gNullStr) {
        noIcon = !strcmp(mIconArt.Str(), gNullStr);
    } else {
        noIcon = (mIconArt.Str() == gNullStr);
    }

    return !noIcon;
}

Symbol Award::GetIconArt() const{
    return mIconArt;
}

bool Award::IsBonus() const{
    return mIsBonus;
}

void Award::GrantAward(const AwardEntry& awardEntry, BandProfile* i_pProfile) {
    MILO_ASSERT(i_pProfile, 0x00);

    ProfileAssets::AddAsset(asset);
}

void Award::InqAssets(std::vector<Symbol>&) {

}

bool Award::HasAssets() const {
    if(asset == mPadding2){
        return true;
    }
    return false;
}

void Award::GrantAwards(BandProfile* bandProfile) {
    for (int i = 0; i < pAwardArray.size(); i++) {
        AwardEntry& entry = pAwardArray.at(i);
        GrantAward(entry, bandProfile);
    }
}


static const char* unusedAwardStrings[] = {
    "pAwardArray->Size() > 1", 
    "pAwardEntryArray", 
    "pAwardEntryArray->Size() >= 1", 
    "pAssetMgr", 
    "Award: %s is granting unknown asset: %s.", 
    "AWARD: %s is awarding too many assets! count = %i.", 
    "%s_desc", 
    "%s_howto", 
    "%s_gray", 
    "i_pProfile", 
    "pPerformer", 
    "Award Category is not currently supported: %s .", 
    "o_rAssets.empty()"
};