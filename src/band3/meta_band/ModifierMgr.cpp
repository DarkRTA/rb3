#include "meta_band/ModifierMgr.h"
#include "os/Debug.h"
#include "meta_band/ProfileMgr.h"
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
    mModifiers.reserve(allModifiersArray->Size() - 1);
    for(int i = 1; i < allModifiersArray->Size(); i++){
        DataArray* modifierArray = allModifiersArray->Array(i);
        MILO_ASSERT(modifierArray, 0x75);
        Modifier* mod = new Modifier(modifierArray);
        mModifiers.push_back(mod);
        if(!mod->CustomLocation()){
            mModifiersList.push_back(mod);
        }
        if(mod->DefaultEnabled()) mod->mDefaultEnabled = true;
    }
}

ModifierMgr::~ModifierMgr(){
    mModifiersList.clear();
    DeleteAll(mModifiers);
}

Symbol ModifierMgr::DataSymbol(int idx) const {
    Modifier* pModifier = GetModifierAtListData(idx);
    MILO_ASSERT(pModifier, 0x95);
    return pModifier->mData->Sym(0);
}

int ModifierMgr::NumData() const { return mModifiersList.size(); }

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
        TheProfileMgr.mGlobalOptionsDirty = true;
    }
}

bool ModifierMgr::IsModifierActive(Symbol s) const {
    Modifier* mod = GetModifier(s, false);
    return mod && IsModifierActive(mod);
}

bool ModifierMgr::IsModifierDelayedEffect(Symbol s) const {
    return GetModifier(s, true)->DelayedEffect();
}

bool ModifierMgr::IsModifierActive(Modifier* mod) const {
    if(!mod || !mod->mDefaultEnabled) return false;
    else if(IsModifierUnlocked(mod)) return true;
    else {
        mod->mDefaultEnabled = false;
        return false;
    }
}

Modifier* ModifierMgr::GetModifier(Symbol s, bool fail) const {
    for(std::vector<Modifier*>::const_iterator it = mModifiers.begin(); it != mModifiers.end(); ++it){
        Modifier* ret = *it;
        if(ret->mData->Sym(0) == s) return ret;
    }
    if(fail) MILO_FAIL("Couldn't find Modifier for %s.", s);
    return 0;
}

Modifier* ModifierMgr::GetModifierAtListData(int data) const {
    MILO_ASSERT(data < mModifiersList.size(), 0x124);
    return mModifiersList[data];
}

void ModifierMgr::DisableAutoVocals() const {
    Modifier* mod = GetModifier(mod_auto_vocals, true);
    mod->mDefaultEnabled = false;
}

void ModifierMgr::Save(FixedSizeSaveableStream& bs){
    for(int i = 0; i < mModifiers.size(); i++){
        if(mModifiers[i]->SaveValue()){
            bs << mModifiers[i]->mDefaultEnabled;
        }
    }
}

void ModifierMgr::Load(FixedSizeSaveableStream& bs, int rev){
    bool b;
    for(int i = 0; i < mModifiers.size(); i++){
        if(mModifiers[i]->SaveValue()){
            bs >> b;
            if(mModifiers[i]->UseSaveValue()){
                mModifiers[i]->mDefaultEnabled = b;
            }
        }
    }
}

int ModifierMgr::SaveSize(int){
    int size = 0;
    for(int i = 0; i < mModifiers.size(); i++){
        if(mModifiers[i]->SaveValue()) size++;
    }
    return size;
}

BEGIN_HANDLERS(ModifierMgr)
    HANDLE_ACTION(toggle_modifier_enabled, ToggleModifierEnabled(_msg->Sym(2)))
    HANDLE_EXPR(is_modifier_active, IsModifierActive(_msg->Sym(2)))
    HANDLE_EXPR(is_modifier_delayed_effect, IsModifierDelayedEffect(_msg->Sym(2)))
    HANDLE_ACTION(enable_auto_vocals, Modifier* m = GetModifier("mod_auto_vocals", true); m->mDefaultEnabled = true;)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x162)
END_HANDLERS