#include "meta_band/PrefabMgr.h"
#include "bandobj/BandCharDesc.h"
#include "game/BandUserMgr.h"
#include "obj/DataFunc.h"
#include "obj/Dir.h"
#include "os/Debug.h"

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

    }
    
//   pOVar1 = (ObjectDir *)BandCharDesc::GetPrefabs(this_00);
//   ObjDirItr<>::ObjDirItr(aOStack_30,pOVar1,true);
//   do {
//     iVar6 = MergedGet0xC(aOStack_30);
//     if (iVar6 == 0) {
//       fn_8025EFF4(this);
//       (**(code **)(*(int *)this + 0x48))(this,s_prefab_mgr_80847b40,ObjectDir::sMainDir);
//       return this;
//     }
//     iVar6 = MergedGet0xC(aOStack_30);
//     pcVar2 = (char *)MergedGet0xC(*(void **)(iVar6 + 8));
//     String::String(aSStack_3c,pcVar2);
//     fn_801BCAF0(avStack_68,auStack_a8);
//     ~GenericDtor(auStack_a8,0xffffffff);
//     iVar6 = String::split(aSStack_3c,&lbl_80847AB8,avStack_68);
//     if (iVar6 < 1) {
//       String::String(aSStack_48,(String *)aSStack_3c);
//       RSONotifyModuleLoaded(s_Bad_prefab_name:_(%s)_80847aba,aSStack_48);
//       String::~String(aSStack_48);
//       fn_801BC7B8(avStack_68,0xffffffff);
//       String::~String(aSStack_3c);
//     }
//     else {
//       pvVar3 = (void *)stlpmtx_std::vector<><>::operator_[]((vector<><> *)avStack_68,0);
//       pcVar2 = (char *)MergedGet0x8(pvVar3);
//       iVar6 = strcmp(pcVar2,s_prefab_80847ad1);
//       if (iVar6 == 0) {
//         pJVar4 = (JsonObject *)operator_new(0x50);
//         if (pJVar4 != (JsonObject *)0x0) {
//           uVar5 = MergedGet0xC(aOStack_30);
//           pJVar4 = (JsonObject *)fn_801F14B4(pJVar4,1,uVar5);
//         }
//         stlpmtx_std::vector<><>::push_back((vector<><> *)(this + 0x1c),pJVar4);
//       }
//       else {
//         iVar6 = strcmp(pcVar2,s_charcreator_80847ad8);
//         if (iVar6 == 0) {
//           iVar6 = stlpmtx_std::vector<><>::size((vector<><> *)avStack_68);
//           if (iVar6 != 3) {
//             String::String(aSStack_54,(String *)aSStack_3c);
//             RSONotifyModuleLoaded(s_Bad_charcreator_prefab_name:_(%s_80847ae4,aSStack_54);
//             String::~String(aSStack_54);
//             fn_801BC7B8(avStack_68,0xffffffff);
//             String::~String(aSStack_3c);
//             goto LAB_8025eb2c;
//           }
//           pvVar3 = (void *)stlpmtx_std::vector<><>::operator_[]((vector<><> *)avStack_68,2);
//           pcVar2 = (char *)MergedGet0x8(pvVar3);
//           pcVar2 = ::MakeString(s_boutique_%s_80847b07,pcVar2);
//           Symbol::Symbol((Symbol *)local_78,pcVar2);
//           fn_8018F138(auStack_70,this + 0x44,local_78);
//           pvVar3 = (void *)MergedGet0xC(aOStack_30);
//           local_80 = MergedGet0x10(pvVar3);
//           Symbol::Symbol(aSStack_7c,(Symbol *)&local_80);
//           iVar6 = Symbol::operator_==(aSStack_7c,(Symbol *)&SymMale);
//           if (iVar6 == 0) {
//             iVar6 = Symbol::operator_==(aSStack_7c,(Symbol *)&female);
//             if (iVar6 != 0) {
//               pJVar4 = (JsonObject *)operator_new(8);
//               if (pJVar4 != (JsonObject *)0x0) {
//                 local_88 = local_78[0];
//                 uVar5 = MergedGet0xC(aOStack_30);
//                 pJVar4 = (JsonObject *)fn_802603F8(pJVar4,uVar5,&local_88);
//               }
//               stlpmtx_std::vector<><>::push_back((vector<><> *)(this + 0x2c),pJVar4);
//             }
//           }
//           else {
//             pJVar4 = (JsonObject *)operator_new(8);
//             if (pJVar4 != (JsonObject *)0x0) {
//               local_84 = local_78[0];
//               uVar5 = MergedGet0xC(aOStack_30);
//               pJVar4 = (JsonObject *)fn_802603F8(pJVar4,uVar5,&local_84);
//             }
//             stlpmtx_std::vector<><>::push_back((vector<><> *)(this + 0x24),pJVar4);
//           }
//         }
//         else {
//           iVar6 = strcmp(pcVar2,s_facetype_80847b13);
//           if (iVar6 == 0) {
//             iVar6 = stlpmtx_std::vector<><>::size((vector<><> *)avStack_68);
//             if (iVar6 != 3) {
//               String::String(aSStack_60,(String *)aSStack_3c);
//               RSONotifyModuleLoaded(s_Bad_facetype_prefab_name:_(%s)_80847b1c,aSStack_60);
//               String::~String(aSStack_60);
//               fn_801BC7B8(avStack_68,0xffffffff);
//               String::~String(aSStack_3c);
//               goto LAB_8025eb2c;
//             }
//             pJVar4 = (JsonObject *)MergedGet0xC(aOStack_30);
//             stlpmtx_std::vector<><>::push_back((vector<><> *)(this + 0x34),pJVar4);
//           }
//           else {
//             iVar6 = strcmp(pcVar2,&DAT_80847b3c);
//             if (iVar6 == 0) {
//               pJVar4 = (JsonObject *)operator_new(0x50);
//               if (pJVar4 != (JsonObject *)0x0) {
//                 uVar5 = MergedGet0xC(aOStack_30);
//                 pJVar4 = (JsonObject *)fn_801F14B4(pJVar4,1,uVar5);
//               }
//               stlpmtx_std::vector<><>::push_back((vector<><> *)(this + 0x1c),pJVar4);
//             }
//           }
//         }
//       }
//       fn_801BC7B8(avStack_68,0xffffffff);
//       String::~String(aSStack_3c);
//     }
// LAB_8025eb2c:
//     ObjDirItr<>::operator_++(aOStack_30);
//   } while( true );
}

PrefabMgr::~PrefabMgr(){
    
}