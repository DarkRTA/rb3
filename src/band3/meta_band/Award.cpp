#include "Award.h"
#include "os/Debug.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols2.h"
#include "AccomplishmentManager.h"

#include "decomp.h"

Award::Award(DataArray* configure, int index) : mName(gNullStr), mIcon(gNullStr), mIsSecret(false), mIsBonus(false), mIndex(index) {

}

Award::~Award() {

}

class AssetMgr{};

void Award::Configure(DataArray* i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x25);

    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(is_secret, mIsSecret, false);
    i_pConfig->FindData(is_bonus, mIsBonus, false);
    i_pConfig->FindData(icon, mIcon, false);
    DataArray* pAwardArray = i_pConfig->FindArray(awards, false);

    MILO_ASSERT(pAwardArray->Size() > 1, 0x39);

    int i;
    for (i = 0; i < pAwardArray->Size(); i++) {
        DataNode node = pAwardArray->Node(i);
        DataArray* pAwardEntryArray  = node.Array(0);

        MILO_ASSERT(pAwardEntryArray, 0x3f);
        MILO_ASSERT(pAwardEntryArray->Size() >= 1, 0x40);
        DataNode assetMgr = pAwardEntryArray->Node(0);
    }

    // TODO: Temporary to match string pool
    void* pAssetMgr;
    MILO_ASSERT(pAssetMgr, 0);
    TheDebug.Notify("Award: %s is granting unknown asset: %s\n");

    if (i > 8) {
        TheDebug.Notify(MakeString("AWARD: %s is awarding too many assets!  count = %i\n", mName, i));
    }
}

Symbol Award::GetName() const{
    return mName;
}

Symbol Award::GetDescription() const{
    if (HasAssets()) {
        return award_genericdesc;
    }
    return MakeString("%s_desc", mName);
}

Symbol Award::GetDisplayName() const{
    if (HasAssets()) {
        return award_generic;
    }
    return mName;
}

bool Award::HasIconArt() const {
    bool noIcon;

    if (gNullStr) {
        noIcon = !strcmp(mIcon.Str(), gNullStr);
    } else {
        noIcon = (mIcon.Str() == gNullStr);
    }

    return !noIcon;
}

Symbol Award::GetIconArt() const{
    return mIcon;
}

bool Award::IsBonus() const{
    return mIsBonus;
}

DECOMP_FORCEACTIVE(Award,
    "%s_howto",
    "%s_gray"
)

void Award::GrantAward(const AwardEntry& awardEntry, BandProfile* i_pProfile) {
    MILO_ASSERT(i_pProfile, 0xbd);

    // TODO: Temporary to match string pool
    // Requires BandProfile and ProfileAssets
    void* pPerformer;
    MILO_ASSERT(pPerformer, 0);

    if(mIndex){
        TheDebug.Fail("Award Category is not currently supported: %s \n");
    }
}

void Award::InqAssets(std::vector<Symbol>& o_rAssets) {
    MILO_ASSERT(o_rAssets.empty(), 0xe5);
}

bool Award::HasAssets() const {
    return 0;
}

void Award::GrantAwards(BandProfile* bandProfile) {
    for (std::vector<AwardEntry>::iterator it = mAwardEntries.begin(); it != mAwardEntries.end(); it++) {
        GrantAward(*it, bandProfile);
    }
}
