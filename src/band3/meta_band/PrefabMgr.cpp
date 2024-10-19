#include "meta_band/PrefabMgr.h"
#include "MSL_Common/extras.h"
#include "bandobj/BandCharDesc.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "math/Rand.h"
#include "meta_band/CharData.h"
#include "meta_band/OvershellSlot.h"
#include "obj/DataFunc.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "stl/_algo.h"
#include "utl/STLHelpers.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

namespace {
    bool gPrefabIsCustomizable;
    bool gPrefabUsesProfilePatches;
    PrefabMgr* ThePrefabMgr;
}

bool PrefabMgr::PrefabIsCustomizable(){ return gPrefabIsCustomizable; }

DataNode PrefabMgr::OnPrefabIsCustomizable(DataArray*){
    return gPrefabIsCustomizable;
}

DataNode PrefabMgr::OnPrefabToggleCustomizable(DataArray*){
    gPrefabIsCustomizable = gPrefabIsCustomizable == 0;
    return 0;
}

bool PrefabMgr::PrefabUsesProfilePatches(){
    return gPrefabUsesProfilePatches;
}

DataNode PrefabMgr::OnPrefabUsesProfilePatches(DataArray*){
    return gPrefabUsesProfilePatches;
}

DataNode PrefabMgr::OnPrefabToggleUsesProfilePatches(DataArray*){
    gPrefabUsesProfilePatches = gPrefabUsesProfilePatches == 0;
    return 0;
}

void PrefabMgr::Init(BandUserMgr* mgr){
    ThePrefabMgr = new PrefabMgr();
    if(mgr) ThePrefabMgr->unk5c = mgr;
    else {
        MILO_ASSERT(TheBandUserMgr, 0x4C);
        ThePrefabMgr->unk5c = TheBandUserMgr;
    }    
    DataRegisterFunc("prefab_is_customizable", OnPrefabIsCustomizable);
    DataRegisterFunc("prefab_toggle_customizable", OnPrefabToggleCustomizable);
    DataRegisterFunc("prefab_uses_profile_patches", OnPrefabUsesProfilePatches);
    DataRegisterFunc("prefab_toggle_uses_profile_patches", OnPrefabToggleUsesProfilePatches);
}

void PrefabMgr::Poll(){
    if(unk60) PollPortraits();
}

PrefabMgr* PrefabMgr::GetPrefabMgr(){ return ThePrefabMgr; }

PrefabMgr::PrefabMgr() : unk60(0) {
    for(ObjDirItr<BandCharDesc> it(BandCharDesc::GetPrefabs(), true); it != 0; ++it){
        String str(it->Name());
        std::vector<String> substrs;
        if(str.split("_", substrs) < 1){
            MILO_WARN("Bad prefab name: (%s)\n", str);
        }
        else {
            const char* substrname = substrs[0].c_str();
            if(strcmp(substrname, "prefab") == 0){
                mPrefabs.push_back(new PrefabChar(it));
            }
            else if(strcmp(substrname, "charcreator") == 0){
                if(substrs.size() != 3){
                    MILO_WARN("Bad charcreator prefab name: (%s)\n", str);
                    continue;
                }
                Symbol boutiqueSym = MakeString("boutique_%s", substrs[2].c_str());
                unk44.insert(boutiqueSym);
                Symbol genderSym = it->mGender;
                if(genderSym == male){
                    mCharCreatorMalePrefabs.push_back(new CharCreatorPrefab(it, genderSym));
                }
                else if(genderSym == female){
                    mCharCreatorFemalePrefabs.push_back(new CharCreatorPrefab(it, genderSym));
                }
                else MILO_WARN("Incorrect gender symbol %s\n", genderSym);
            }
            else if(strcmp(substrname, "facetype") == 0){
                if(substrs.size() != 3){
                    MILO_WARN("Bad facetype prefab name: (%s)\n", str);
                    continue;
                }
                unk34.push_back(it);
            }
            else if(strcmp(substrname, "BBE") == 0){
                mPrefabs.push_back(new PrefabChar(it));
            }
        }
    }
    AssignPrefabsToSlots();
    SetName("prefab_mgr", ObjectDir::Main());
}

PrefabMgr::~PrefabMgr(){
    DeleteAll(mPrefabs);
    DeleteAll(mCharCreatorMalePrefabs);
    DeleteAll(mCharCreatorFemalePrefabs);
}

#define kGameNumSlots 4

void PrefabMgr::AssignPrefabsToSlots(){
    MILO_ASSERT(mPrefabs.size() >= kGameNumSlots, 0xD6);
    MILO_ASSERT(mPrefabs.size() < 256, 0xDB);
}

DECOMP_FORCEACTIVE(PrefabMgr, "female", "male")

void PrefabMgr::GetPrefabs(std::vector<PrefabChar*>& prefabs) const {
    for(int i = 0; i < mPrefabs.size(); i++){
        prefabs.push_back(mPrefabs[i]);
    }
}

void PrefabMgr::GetAvailablePrefabs(std::vector<PrefabChar*>& prefabs) const {
    for(int i = 0; i < mPrefabs.size(); i++){
        if(unk5c->IsCharAvailable(mPrefabs[i])){
            prefabs.push_back(mPrefabs[i]);
        }
    }
}

PrefabChar* PrefabMgr::GetPrefab(Symbol s){
    for(int i = 0; i < mPrefabs.size(); i++){
        PrefabChar* pPrefabChar = mPrefabs[i];
        MILO_ASSERT(pPrefabChar, 0x10C);
        if(pPrefabChar->GetPrefabName() == s) return pPrefabChar;
    }
    return nullptr;
}

void PrefabMgr::EnableDebugPrefabs(){
    DeleteAll(mPrefabs);
    for(ObjDirItr<BandCharDesc> it(BandCharDesc::GetPrefabs(), true); it != 0; ++it){
        mPrefabs.push_back(new PrefabChar(it));
    }
}

PrefabChar* PrefabMgr::GetDefaultPrefab(int slotNum) const {
    MILO_ASSERT(( 0) <= (slotNum) && (slotNum) < ( mDefaultPrefabs.size()), 0x132);
    return mDefaultPrefabs[slotNum];
}

PrefabMgr::CharCreatorPrefab* PrefabMgr::GetCharCreatorPrefab(Symbol genderSym, Symbol outfitSym) const {
    if(genderSym == male){
        return GetCharCreatorPrefabFromOutfit(mCharCreatorMalePrefabs, outfitSym);
    }
    else if(genderSym == female){
        return GetCharCreatorPrefabFromOutfit(mCharCreatorFemalePrefabs, outfitSym);
    }
    else {
        MILO_FAIL("Incorrect gender symbol %s\n", genderSym);
        return nullptr;
    }
}

PrefabMgr::CharCreatorPrefab* PrefabMgr::GetRandomCharCreatorPrefab(Symbol genderSym) const {
    if(genderSym == male){
        return mCharCreatorMalePrefabs[RandomInt(0, mCharCreatorMalePrefabs.size())];
    }
    else if(genderSym == female){
        return mCharCreatorFemalePrefabs[RandomInt(0, mCharCreatorFemalePrefabs.size())];
    }
    else {
        MILO_FAIL("Incorrect gender symbol %s\n", genderSym);
        return nullptr;
    }
}

PrefabMgr::CharCreatorPrefab* PrefabMgr::GetCharCreatorPrefabFromOutfit(const std::vector<CharCreatorPrefab*>& prefabs, Symbol outfitSym) const {
    for(int i = 0; i < prefabs.size(); i++){
        CharCreatorPrefab* cur = prefabs[i];
        if(cur->unk4 == outfitSym) return cur;
    }
    MILO_FAIL("Incorrect outfit symbol %s\n", outfitSym);
    return nullptr;
}

void PrefabMgr::GetFaceTypes(std::vector<Symbol>& faceTypes, Symbol s) const {
    for(int i = 0; i < unk34.size(); i++){
        BandCharDesc* pBandCharDesc = unk34[i];
        MILO_ASSERT(pBandCharDesc, 0x177);
        if(pBandCharDesc->mGender == s){
            Symbol prefabSym = pBandCharDesc->Name();
            faceTypes.push_back(prefabSym);
        }
    }
}

BandCharDesc* PrefabMgr::GetFaceType(Symbol s){
    for(std::vector<BandCharDesc*>::iterator it = unk34.begin(); it != unk34.end(); ++it){
        BandCharDesc* pFaceTypeDesc = *it;
        MILO_ASSERT(pFaceTypeDesc, 0x188);
        Symbol name = pFaceTypeDesc->Name();
        if(name == s) return pFaceTypeDesc;
    }
    return nullptr;
}

struct SortPrefabByPortraitFileName {
    bool operator()(PrefabChar* c1, PrefabChar* c2){
        int cmp = stricmp(c1->unk24.c_str(), c2->unk24.c_str());
        return cmp < 0;
    }
};

void PrefabMgr::LoadPortraits(OvershellSlot* slot){
    unk6c.push_back(slot);
    if(!unk60 && unk6c.size() == 1){
        for(std::vector<PrefabChar*>::iterator it = mPrefabs.begin(); it != mPrefabs.end(); ++it){
            PrefabChar* cur = *it;
            unk64.push_back(cur);
        }
        std::sort(unk64.begin(), unk64.end(), SortPrefabByPortraitFileName());
        for(std::vector<PrefabChar*>::iterator it = unk64.begin(); it != unk64.end(); ++it){
            (*it)->LoadPortrait();
        }
        unk60 = true;
    }
}

void PrefabMgr::PollPortraits(){
    bool removed = false;
    for(std::vector<PrefabChar*>::iterator it = unk64.begin(); it != unk64.end(); it){
        PrefabChar* cur = *it;
        cur->PollLoadingPortrait();
        if(cur->IsPortraitLoaded()){
            it = unk64.erase(it);
            removed = true;
        }
        else ++it;
    }
    if(removed){
        for(std::vector<OvershellSlot*>::iterator it = unk6c.begin(); it != unk6c.end(); ++it){
            OvershellSlot* cur = *it;
            cur->UpdateView();
        }
    }
    if(unk64.empty()) unk60 = false;
}

void PrefabMgr::UnloadPortraits(OvershellSlot* slot){
    std::vector<OvershellSlot*>::iterator it;
    for(it = unk6c.begin(); it != unk6c.end() && *it != slot; ++it);
    if(it == unk6c.end()){
        MILO_WARN("ignored request from slot %d to unload portraits.\n", slot->GetSlotNum());
    }
    else {
        unk6c.erase(it);
        if(unk6c.empty()){
            unk64.clear();
            for(std::vector<PrefabChar*>::iterator it = mPrefabs.begin(); it != mPrefabs.end(); ++it){
                PrefabChar* cur = *it;
                cur->UnloadPortrait();
            }
        }
    }
}

PrefabMgr::CharCreatorPrefab::CharCreatorPrefab(BandCharDesc* pBandCharDesc, Symbol s) : unk0(0), unk4(s) {
    MILO_ASSERT(pBandCharDesc, 0x229);
    unk0 = new PrefabChar(pBandCharDesc);
}

PrefabMgr::CharCreatorPrefab::~CharCreatorPrefab(){
    RELEASE(unk0);
}

BEGIN_HANDLERS(PrefabMgr)
    HANDLE_ACTION(enable_debug_prefabs, EnableDebugPrefabs())
    HANDLE_ACTION(load_portraits, LoadPortraits(_msg->Obj<OvershellSlot>(2)))
    HANDLE_ACTION(unload_portraits, UnloadPortraits(_msg->Obj<OvershellSlot>(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x241)
END_HANDLERS