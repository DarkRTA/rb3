#include "meta_band/CymbalSelectionProvider.h"
#include "utl/Symbols.h"

CymbalSelectionProvider::CymbalSelectionProvider(OvershellSlot* slot) : mSlot(slot) {
    ReloadData();
}

static void CymbalSelectionPushBack(std::vector<Symbol>& s){
    s.push_back(gNullStr);
}

void CymbalSelectionProvider::ReloadData(){
    MILO_ASSERT(mSlot, 0x16);
    unk20.clear();
    unk20.push_back(overshell_lefty_flip);
    unk20.push_back(overshell_enable_hihat);
    unk20.push_back(overshell_yellow_cym);
    unk20.push_back(overshell_blue_cym);
    unk20.push_back(overshell_green_cym);
    if(mSlot->InOverrideFlow(kOverrideFlow_SongSettings)){
        unk20.push_back(overshell_cymbals_continue);
    }
}

bool CymbalSelectionProvider::IsActive(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x2C);
    if(unk20[data] == overshell_cymbals_continue && !mSlot->mCymbalConfiguration) return false;
    else return true;
}

void CymbalSelectionProvider::Text(int, int data, UIListLabel*, UILabel* label) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x36);
    label->SetTextToken(unk20[data]);
}

Symbol CymbalSelectionProvider::DataSymbol(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x3D);
    return unk20[data];
}

int CymbalSelectionProvider::NumData() const { return unk20.size(); }
