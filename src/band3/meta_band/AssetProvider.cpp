#include "AssetProvider.h"

#include "bandobj/BandCharDesc.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AssetTypes.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/ProfileAssets.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "AssetMgr.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"
#include <algorithm>
#include "system/rndwii/Rnd.h"
#include "AccomplishmentManager.h"
#include "system/ui/UIComponent.h"

AssetProvider::AssetProvider(BandProfile *profile, AssetGender gender)
    : mProfile(profile), mGender(gender) {
    MILO_ASSERT(mProfile, 0x1d);
    mAssets.push_back(none);
}

AssetProvider::~AssetProvider() {}

bool AssetProvider::SortAssetsByIndex(Symbol s1, Symbol s2) {
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x2D);

    Asset *pAsset1 = pAssetMgr->GetAsset(s1);
    MILO_ASSERT(pAsset1, 0x30);

    Asset *pAsset2 = pAssetMgr->GetAsset(s2);
    MILO_ASSERT(pAsset2, 0x32);

    if (pAsset1->GetIndex() < pAsset2->GetIndex()) {
        return true;
    }
    return false;
}

void AssetProvider::Update(AssetType assetType, AssetBoutique assetBoutique) {
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x3d);
    std::vector<Symbol> syms;
    FOREACH_POST (it, pAssetMgr->GetAssets()) {
        Asset *pAsset = it->second;
        MILO_ASSERT(pAsset, 0x46);
        Symbol name = pAsset->GetName();
        AssetType curType = pAsset->GetType();
        AssetGender curGender = pAsset->GetGender();
        AssetBoutique curBoutique = pAsset->GetBoutique();
        bool curHidden = pAsset->IsHidden();
        if (curType == assetType && curBoutique == assetBoutique
            && (curGender == mGender || curGender == 0)) {
            if (curHidden) {
                ProfileAssets *assets = &mProfile->mProfileAssets;
                if (assets->HasAsset(name)) {
                    syms.push_back(name);
                }
            } else
                syms.push_back(name);
        }
    }
    std::sort(syms.begin(), syms.end(), SortAssetsByIndex);
    mAssets.clear();
    if (assetType != kAssetType_Gloves) {
        ClosetMgr *pClosetMgr = ClosetMgr::GetClosetMgr();
        MILO_ASSERT(pClosetMgr, 0x7A);
        BandCharDesc *pPreviewDesc = pClosetMgr->GetPreviewDesc();
        MILO_ASSERT(pPreviewDesc, 0x7C);
        AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x80);
        if (assetType == kAssetType_Hat) {
            Symbol name = pPreviewDesc->mOutfit.mHair.mName;
            if (name != gNullStr) {
                if (pAssetMgr->GetTypeFromName(name) == kAssetType_Hair) {
                    mAssets.push_back(name);
                } else
                    mAssets.push_back(none_hat);
            } else
                mAssets.push_back(none_hat);
        } else if (assetType == kAssetType_Bandana) {
            Symbol name = pPreviewDesc->mOutfit.mFaceHair.mName;
            if (name != gNullStr) {
                if (pAssetMgr->GetTypeFromName(name) == kAssetType_FaceHair) {
                    mAssets.push_back(name);
                } else
                    mAssets.push_back(none_bandana);
            } else
                mAssets.push_back(none_bandana);
        } else {
            Symbol theAsset = GetDefaultAssetFromAssetType(assetType, mGender);
            if (theAsset != gNullStr) {
                mAssets.push_back(theAsset);
            }
        }
    }

    for (int i = 0; i < syms.size(); i++) {
        Symbol s = syms[i];
        mAssets.push_back(s);
    }
}

UIComponent::State
AssetProvider::ComponentStateOverride(int, int idx, UIComponent::State state) const {
    if (!mProfile->mProfileAssets.HasAsset(mAssets[idx])) {
        state = UIComponent::kDisabled;
    }
    return state;
}

void AssetProvider::Text(int, int idx, UIListLabel *slot, UILabel *label) const {
    MILO_ASSERT(slot, 200);
    MILO_ASSERT(label, 0xc9);
    ProfileAssets *assets = &mProfile->mProfileAssets;
    Symbol sym = DataSymbol(idx);
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0xD0);
    if (pAssetMgr->HasAsset(sym)) {
        Asset *pAsset = pAssetMgr->GetAsset(sym);
        MILO_ASSERT(pAsset, 0xD5);
        if (slot->Matches("name")) {
            label->SetTextToken(pAsset->GetName());
        } else if (slot->Matches("new")) {
            if (assets->HasAsset(sym) && assets->IsNew(sym)) {
                label->SetTextToken(customize_new);
            } else
                label->SetTextToken(gNullStr);
        } else if (slot->Matches("icon")) {
            if (!assets->HasAsset(sym)) {
                label->SetIcon('L');
            } else
                label->SetIcon('\0');
        } else
            label->SetTextToken(gNullStr);
    } else if (slot->Matches("name")) {
        label->SetTextToken(sym);
    } else
        label->SetTextToken(gNullStr);
}

RndMat *AssetProvider::Mat(int, int data, UIListMesh *slot) const {
    MILO_ASSERT(data < NumData(), 0x109);
    const ProfileAssets &assets = mProfile->mProfileAssets;
    Symbol sym = DataSymbol(data);
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x10F);
    if (pAssetMgr->HasAsset(sym)) {
        if (slot->Matches("new_bg")) {
            if (assets.HasAsset(sym) && assets.IsNew(sym)) {
                return slot->DefaultMat();
            }
            return nullptr;
        }
    } else if (slot->Matches("new_bg"))
        return nullptr;
    return slot->DefaultMat();
}

void AssetProvider::UpdateExtendedText(int, int i_iData, UILabel *label) const {
    MILO_ASSERT(i_iData < NumData(), 300);

    const ProfileAssets &assets = mProfile->mProfileAssets;
    Symbol sym = DataSymbol(i_iData);
    AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x132);
    if (strcmp(label->Name(), "asset_desc.lbl") == 0) {
        if (pAssetMgr->HasAsset(sym)) {
            Asset *pAsset = pAssetMgr->GetAsset(sym);
            MILO_ASSERT(pAsset, 0x139);
            if (WiiRnd::mShowAssetName) {
                label->SetTextToken(pAsset->GetHint());
            } else if (assets.HasAsset(sym)) {
                label->SetTextToken(pAsset->GetHint());
            } else {
                MILO_ASSERT(TheAccomplishmentMgr, 0x14B);
                TheAccomplishmentMgr->UpdateAssetHintLabel(pAsset->GetName(), label);
            }
        } else
            label->SetTextToken(gNullStr);
    } else if (strcmp(label->Name(), "asset_progress.lbl") == 0) {
        label->SetTokenFmt(customize_asset_progress, i_iData + 1, NumData());
    } else
        label->SetTextToken(gNullStr);
}

Symbol AssetProvider::DataSymbol(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x165);
    return mAssets[data];
}

int AssetProvider::NumData() const { return mAssets.size(); }

bool AssetProvider::HasAsset(Symbol s) {
    for (int i = 0; i < mAssets.size(); i++) {
        if (mAssets[i] == s) {
            return true;
        }
    }
    return false;
}
