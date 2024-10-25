#include "meta_band/InstrumentFinishProvider.h"
#include "meta_band/AssetMgr.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
#include "utl/Symbol.h"

InstrumentFinishProvider::InstrumentFinishProvider(){

}

void InstrumentFinishProvider::Update(Symbol s){
    mFinishes.clear();
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x18);
    Asset* pAsset = pAssetMgr->GetAsset(s);
    MILO_ASSERT(pAsset, 0x1B);
    pAsset->GetFinishes(mFinishes);
}

void InstrumentFinishProvider::Text(int, int data, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x22);
    MILO_ASSERT(label, 0x23);
    if(slot->Matches("option")){
        label->SetTextToken(DataSymbol(data));
    }
    else label->SetTextToken(gNullStr);
}

Symbol InstrumentFinishProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x31);
    return mFinishes.at(data);
}

int InstrumentFinishProvider::NumData() const { return mFinishes.empty() ? 0 : mFinishes.size(); }