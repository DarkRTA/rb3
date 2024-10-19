#include "meta_band/PrefabMgr.h"
#include "bandobj/BandCharDesc.h"
#include "game/BandUserMgr.h"
#include "meta_band/CharData.h"
#include "obj/DataFunc.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "utl/STLHelpers.h"
#include "utl/Symbols.h"

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
    DataRegisterFunc("prefab_toggle_uses_profile_patch", OnPrefabToggleUsesProfilePatches);
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