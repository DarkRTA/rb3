#include "Award.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "decomp.h"

Award::Award(DataArray *cfg, int index)
    : mName(gNullStr), mIcon(gNullStr), mIsSecret(false), mIsBonus(false), mIndex(index) {
    Configure(cfg);
}

Award::~Award() { mAwardEntries.clear(); }

void Award::Configure(DataArray *i_pConfig) {
    MILO_ASSERT(i_pConfig, 0x25);

    mName = i_pConfig->Sym(0);
    i_pConfig->FindData(is_secret, mIsSecret, false);
    i_pConfig->FindData(is_bonus, mIsBonus, false);
    i_pConfig->FindData(icon, mIcon, false);
    DataArray *pAwardArray = i_pConfig->FindArray(awards, false);
    if (pAwardArray) {
        MILO_ASSERT(pAwardArray->Size() > 1, 0x39);
        int numAssets = 0;
        for (int i = 1; i < pAwardArray->Size(); i++) {
            DataArray *pAwardEntryArray = pAwardArray->Node(i).Array();
            MILO_ASSERT(pAwardEntryArray, 0x3F);
            MILO_ASSERT(pAwardEntryArray->Size() >= 1, 0x40);
            AwardEntry entry;
            entry.m_symAwardCategory = pAwardEntryArray->Node(0).Sym();
            if (pAwardEntryArray->Size() >= 2)
                entry.m_symAward = pAwardEntryArray->Node(1).Sym();
            else
                entry.m_symAward = gNullStr;
            if (entry.m_symAwardCategory == asset) {
                numAssets++;
                if (numAssets <= 8) {
                    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
                    MILO_ASSERT(pAssetMgr, 0x59);
                    Symbol curAsset = entry.m_symAward;
                    if (pAssetMgr->HasAsset(curAsset)) {
                        TheAccomplishmentMgr->AddAssetAward(entry.m_symAward, mName);
                        goto push;
                    }
                    MILO_WARN(
                        "Award: %s is granting unknown asset: %s\n",
                        mName.mStr,
                        curAsset.mStr
                    );
                }
            } else {
            push:
                mAwardEntries.push_back(entry);
            }
        }
        if (numAssets > 8) {
            MILO_WARN(
                "AWARD: %s is awarding too many assets!  count = %i\n",
                mName.mStr,
                numAssets
            );
        }
    }
}

Symbol Award::GetName() const { return mName; }

Symbol Award::GetDescription() const {
    if (HasAssets()) {
        return award_genericdesc;
    } else
        return MakeString("%s_desc", mName);
}

Symbol Award::GetDisplayName() const {
    if (HasAssets()) {
        return award_generic;
    } else
        return mName;
}

bool Award::HasIconArt() const { return mIcon != gNullStr; }
Symbol Award::GetIconArt() const { return mIcon; }
bool Award::IsBonus() const { return mIsBonus; }

DECOMP_FORCEACTIVE(Award, "%s_howto", "%s_gray")

void Award::GrantAward(const AwardEntry &awardEntry, BandProfile *i_pProfile) {
    MILO_ASSERT(i_pProfile, 0xbd);
    Symbol s1 = awardEntry.m_symAwardCategory;
    Symbol s2 = awardEntry.m_symAward;
    if (s1 == asset) {
        i_pProfile->mProfileAssets.AddAsset(s2);
    } else if (s1 == key) {
        i_pProfile->GrantCampaignKey(s2);
    } else if (s1 == vignette) {
        AccomplishmentProgress &prog = i_pProfile->AccessAccomplishmentProgress();
        prog.AddNewRewardVignette(s2);
    } else if (s1 == credits) {
        MetaPerformer *pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0xD7);
        pPerformer->SetCreditsPending();
    } else {
        MILO_WARN("Award Category is not currently supported: %s \n", s1);
    }
}

bool Award::InqAssets(std::vector<Symbol> &o_rAssets) {
    MILO_ASSERT(o_rAssets.empty(), 0xe5);
    FOREACH (it, mAwardEntries) {
        if (it->m_symAwardCategory == asset) {
            o_rAssets.push_back(it->m_symAward);
        }
    }
    return !o_rAssets.empty();
}

bool Award::HasAssets() const {
    FOREACH (it, mAwardEntries) {
        if (it->m_symAwardCategory == asset)
            return true;
    }
    return false;
}

void Award::GrantAwards(BandProfile *bandProfile) {
    FOREACH (it, mAwardEntries) {
        GrantAward(*it, bandProfile);
    }
}
