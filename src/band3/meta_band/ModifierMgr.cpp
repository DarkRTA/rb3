#include "meta_band/ModifierMgr.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

ModifierMgr* TheModifierMgr;

Modifier::Modifier(DataArray* da) : mData(da), mDefaultEnabled(0) {
    MILO_ASSERT(mData, 0x1B);
}

bool Modifier::IsHidden() const { return mData->Contains(hidden); }
bool Modifier::CustomLocation() const { return mData->Contains(custom_location); }
bool Modifier::SaveValue() const { return mData->Contains(save_value); }
bool Modifier::UseSaveValue() const { return mData->Contains(use_save_value); }
bool Modifier::DefaultEnabled() const { return mData->Contains(default_enabled); }
bool Modifier::DelayedEffect() const { return mData->Contains(delayed_effect); }

DECOMP_FORCEACTIVE(ModifierMgr, "!TheModifierMgr", "TheModifierMgr")

void ModifierMgr::Init(){
    MILO_ASSERT(!TheModifierMgr, 0x55);
    TheModifierMgr = new ModifierMgr();
}

ModifierMgr::ModifierMgr(){
    MILO_ASSERT(!TheModifierMgr, 100);
    SetName("modifier_mgr", ObjectDir::sMainDir);
    DataArray* allModifiersArray = SystemConfig(modifiers, modifiers);
    MILO_ASSERT(allModifiersArray, 0x6A);
    unk20.reserve(allModifiersArray->Size() - 1);
    for(int i = 1; i < allModifiersArray->Size(); i++){
        DataArray* modifierArray = allModifiersArray->Array(i);
        MILO_ASSERT(modifierArray, 0x75);
        Modifier* mod = new Modifier(modifierArray);
        unk20.push_back(mod);
        if(!mod->CustomLocation()){
            unk28.push_back(mod);
        }
        if(mod->DefaultEnabled()) mod->mDefaultEnabled = true;
    }
}

ModifierMgr::~ModifierMgr(){
    unk28.clear();
    unk20.clear();
}