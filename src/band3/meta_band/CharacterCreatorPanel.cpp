#include "meta_band/CharacterCreatorPanel.h"
#include "utl/Symbol.h"

CharacterCreatorPanel::CharacterCreatorPanel() : unk4c(0), unk68(0), unk6c(0), unk70(0), unk74(0), unk78(0), unk7c(0), unk80(0), unk84(0), unk88(0), unk8c(0), unk90(gNullStr), unk94(gNullStr), unk98(0), unk99(0) {

}

CharacterCreatorPanel::~CharacterCreatorPanel(){
    unk50.clear();
}

void CharacterCreatorPanel::Load(){
//       this_00 = (ClosetMgr *)TexLoadPanel::Load((TexLoadPanel *)this);
//   iVar1 = ClosetMgr::GetClosetMgr(this_00);
//   *(int *)(this + 0x68) = iVar1;
//   pLVar6 = *(LocalUser **)(iVar1 + 0x1c);
//   pLVar5 = pLVar6;
//   if (pLVar6 != (LocalUser *)0x0) {
//     pLVar5 = *(LocalUser **)(pLVar6 + 4);
//   }
//   iVar1 = ProfileMgr::GetProfileForUser((ProfileMgr *)TheProfileMgr,pLVar5);
//   if ((((iVar1 != 0) && (pLVar6 != (LocalUser *)0x0)) && (*(int *)(this + 0x68) != 0)) &&
//      (iVar1 == *(int *)(*(int *)(this + 0x68) + 0x28))) {
//     CreateNewCharacter(this);
//     local_10[0] = male;
//     AddGridThumbnails(this,(Symbol)local_10);
//     local_14 = female;
//     AddGridThumbnails(this,(Symbol)&local_14);
//     local_18 = male;
//     SetGender(this,(Symbol)&local_18);
//     if (*(int *)(this + 0x78) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xa7,s_!mOutfitProvider_80b9158a);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     this_01 = (OutfitProvider *)operator_new(0x28);
//     if (this_01 != (OutfitProvider *)0x0) {
//       this_01 = (OutfitProvider *)OutfitProvider::OutfitProvider(this_01);
//     }
//     *(OutfitProvider **)(this + 0x78) = this_01;
//     if (*(int *)(this + 0x74) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xaa,s_!mFaceTypeProvider_80b9159b);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     this_02 = (FaceTypeProvider *)operator_new(0x28);
//     if (this_02 != (FaceTypeProvider *)0x0) {
//       this_02 = (FaceTypeProvider *)FaceTypeProvider::FaceTypeProvider(this_02);
//     }
//     *(FaceTypeProvider **)(this + 0x74) = this_02;
//     if (*(int *)(this + 0x7c) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xad,s_!mFaceHairProvider_80b915ae);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     this_03 = (FaceHairProvider *)operator_new(0x34);
//     if (this_03 != (FaceHairProvider *)0x0) {
//       this_03 = (FaceHairProvider *)FaceHairProvider::FaceHairProvider(this_03);
//     }
//     *(FaceHairProvider **)(this + 0x7c) = this_03;
//     if (*(int *)(this + 0x80) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xb0,s_!mFaceOptionsProvider_80b915c1);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     puVar3 = (undefined4 *)operator_new(0x38);
//     if (puVar3 != (undefined4 *)0x0) {
//       *puVar3 = &UIListProvider::__vt;
//       Hmx::Object::Object((Object *)(puVar3 + 1));
//       *puVar3 = FaceOptionsProvider::__vt;
//       puVar3[1] = 0x80b912e0;
//       puVar3[8] = this + 0x40;
//       Symbol::Symbol((Symbol *)(puVar3 + 9),gNullStr);
//       String::String((String *)(puVar3 + 10));
//       puVar3[0xd] = 0;
//     }
//     *(undefined4 **)(this + 0x80) = puVar3;
//     if (*(int *)(this + 0x84) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xb3,s_!mFaceOptionsGridProvider_80b915d7);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     pUVar4 = (UIGridProvider *)operator_new(0x14);
//     if (pUVar4 != (UIGridProvider *)0x0) {
//       pUVar4 = (UIGridProvider *)
//                UIGridProvider::UIGridProvider(pUVar4,*(UIListProvider **)(this + 0x80),3);
//     }
//     *(UIGridProvider **)(this + 0x84) = pUVar4;
//     if (*(int *)(this + 0x88) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xb6,s_!mEyebrowsProvider_80b915f1);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     this_04 = (EyebrowsProvider *)operator_new(0x30);
//     if (this_04 != (EyebrowsProvider *)0x0) {
//       this_04 = (EyebrowsProvider *)
//                 EyebrowsProvider::EyebrowsProvider(this_04,(vector<> *)(this + 0x40));
//     }
//     *(EyebrowsProvider **)(this + 0x88) = this_04;
//     if (*(int *)(this + 0x8c) != 0) {
//       pcVar2 = ::MakeString(kAssertStr,::@stringBase0,0xb9,s_!mEyebrowsGridProvider_80b91604);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     pUVar4 = (UIGridProvider *)operator_new(0x14);
//     if (pUVar4 != (UIGridProvider *)0x0) {
//       pUVar4 = (UIGridProvider *)
//                UIGridProvider::UIGridProvider(pUVar4,*(UIListProvider **)(this + 0x88),3);
//     }
//     *(UIGridProvider **)(this + 0x8c) = pUVar4;
//   }
//   return;
}