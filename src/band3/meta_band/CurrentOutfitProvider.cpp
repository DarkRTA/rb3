#include "meta_band/CurrentOutfitProvider.h"
#include "bandobj/BandCharDesc.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/ClosetMgr.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

CurrentOutfitProvider::CurrentOutfitProvider() { unk20.push_back(none); }
CurrentOutfitProvider::~CurrentOutfitProvider() {}

void CurrentOutfitProvider::Update() {
    unk20.clear();
    ClosetMgr *pClosetMgr = ClosetMgr::GetClosetMgr();
    MILO_ASSERT(pClosetMgr, 0x23);
    BandCharDesc *pPreviewDesc = pClosetMgr->GetPreviewDesc();
    MILO_ASSERT(pPreviewDesc, 0x28);
    BandCharDesc::InstrumentOutfit outfit = pPreviewDesc->mInstruments;
    unk20.push_back(pPreviewDesc->mOutfit.mTorso.mName);
    unk20.push_back(pPreviewDesc->mOutfit.mLegs.mName);
    unk20.push_back(pPreviewDesc->mOutfit.mFeet.mName);
}

RndMat *CurrentOutfitProvider::Mat(int, int data, UIListMesh *slot) const {
    MILO_ASSERT(data < NumData(), 0x35);
    if (slot->Matches("new_bg"))
        return nullptr;
    else
        return slot->DefaultMat();
}

void CurrentOutfitProvider::Text(int, int data, UIListLabel *slot, UILabel *label) const {
    MILO_ASSERT(slot, 0x42);
    MILO_ASSERT(label, 0x43);
    Symbol sym = DataSymbol(data);
    if (sym != none) {
        AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x4F);
        Asset *pAsset = pAssetMgr->GetAsset(sym);
        MILO_ASSERT(pAsset, 0x52);
        if (slot->Matches("name"))
            label->SetTextToken(pAsset->GetName());
        else
            label->SetTextToken(gNullStr);
    }
}

void CurrentOutfitProvider::UpdateExtendedText(int, int i_iData, UILabel *label) const {
    MILO_ASSERT(i_iData < NumData(), 0x61);
    Symbol sym = DataSymbol(i_iData);
    if (sym != none) {
        AssetMgr *pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x6D);
        Asset *pAsset = pAssetMgr->GetAsset(sym);
        MILO_ASSERT(pAsset, 0x70);
        if (strcmp(label->Name(), "asset_desc_current.lbl") == 0) {
            label->SetTextToken(pAsset->GetDescription());
        } else
            label->SetTextToken(gNullStr);
    }
}

Symbol CurrentOutfitProvider::DataSymbol(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x7F);
    return unk20[data];
}

int CurrentOutfitProvider::NumData() const { return unk20.size(); }