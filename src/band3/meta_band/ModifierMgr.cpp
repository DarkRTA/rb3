#include "meta_band/ModifierMgr.h"
#include "os/Debug.h"
#include "ui/UIListLabel.h"
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

Symbol ModifierMgr::DataSymbol(int idx) const {
    Modifier* pModifier = GetModifierAtListData(idx);
    MILO_ASSERT(pModifier, 0x95);
    return pModifier->mData->Sym(0);
}

int ModifierMgr::NumData() const { return unk28.size(); }

void ModifierMgr::Text(int i1, int i2, UIListLabel* listlabel, UILabel* label) const {
    Modifier* mod = GetModifierAtListData(i2);
    if(listlabel->Matches("name")){
        if(IsModifierUnlocked(mod)){
            label->SetTextToken(mod->mData->Sym(0));
        }
        else label->SetTextToken(modifier_locked_name);
    }
    else if(listlabel->Matches("status")){
        if(IsModifierActive(mod)) label->SetIcon('+');
        else if(IsModifierUnlocked(mod)) label->SetIcon('i');
        else label->SetIcon('L');
    }
    else label->SetTextToken(gNullStr);
}

bool ModifierMgr::IsHidden(int idx) const {
    Modifier* pModifier = GetModifierAtListData(idx);
    MILO_ASSERT(pModifier, 0xC2);
    if(IsModifierUnlocked(pModifier)) return false;
    else return pModifier->IsHidden();
}

bool ModifierMgr::IsActive(int idx) const {
    if(idx == 0) return true;
    else {
        Modifier* pModifier = GetModifierAtListData(idx);
        MILO_ASSERT(pModifier, 0xD2);
        return IsModifierUnlocked(pModifier);
    }
}

bool ModifierMgr::HasModifier(Symbol s){
    return GetModifier(s, false);
}

bool ModifierMgr::IsModifierUnlocked(Modifier*) const { return true; }

void ModifierMgr::ToggleModifierEnabled(Symbol s){
    Modifier* mod = GetModifier(s, true);
    mod->mDefaultEnabled = mod->mDefaultEnabled == 0;
    if(mod->UseSaveValue()){
        // set profilemgr value
    }
}

bool ModifierMgr::IsModifierActive(Symbol s) const {
    Modifier* mod = GetModifier(s, false);
    return mod && IsModifierActive(mod);
}

bool ModifierMgr::IsModifierDelayedEffect(Symbol s) const {
    return GetModifier(s, true)->DelayedEffect();
}

// void __thiscall ModifierMgr::IsModifierDelayedEffect(ModifierMgr *this,Symbol param_1)

// {
//   Modifier *this_00;
//   undefined4 local_8 [2];
  
//   local_8[0] = *(undefined4 *)param_1.mStr;
//   this_00 = (Modifier *)GetModifier(this,(Symbol)local_8,true);
//   Modifier::DelayedEffect(this_00);
//   return;
// }