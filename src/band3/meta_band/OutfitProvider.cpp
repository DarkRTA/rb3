#include "meta_band/OutfitProvider.h"
#include "meta_band/PrefabMgr.h"
#include "os/Debug.h"
#include "ui/UILabel.h"
#include "ui/UIListLabel.h"
#include "utl/Symbol.h"

OutfitProvider::OutfitProvider(){
    PrefabMgr* mgr = PrefabMgr::GetPrefabMgr();
    const std::set<Symbol>& symset = mgr->unk44;
    for(std::set<Symbol>::const_iterator it = symset.begin(); it != symset.end(); ++it){
        Symbol key = *it;
        unk20.push_back(key);
    }
}

void OutfitProvider::Text(int, int data, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x1D);
    MILO_ASSERT(label, 0x1E);
    if(slot->Matches("option")){
        label->SetTextToken(DataSymbol(data));
    }
    else label->SetTextToken(gNullStr);
}

Symbol OutfitProvider::DataSymbol(int data) const {
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x2C);
    return unk20[data];
}

int OutfitProvider::NumData() const { return unk20.size(); }
