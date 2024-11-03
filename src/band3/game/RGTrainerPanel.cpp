#include "game/RGTrainerPanel.h"
#include "game/GemTrainerPanel.h"
#include "game/ProTrainerPanel.h"

void ProTrainerPanel::Enter(){
    GemTrainerPanel::Enter();
    if(mGemPlayer){
        
    }
//       GemTrainerPanel::Enter((GemTrainerPanel *)this);
//   if (*(int *)(this + 0x5c) != 0) {
//     pLVar1 = (LocalUser *)
//              (**(code **)(*(int *)(*(int *)(*(int *)(this + 0x5c) + 0x230) + 4) + 0x28))();
//     pLVar11 = pLVar1;
//     if (pLVar1 != (LocalUser *)0x0) {
//       pLVar11 = *(LocalUser **)(pLVar1 + 4);
//     }
//     iVar2 = ProfileMgr::GetProfileForUser((ProfileMgr *)TheProfileMgr,pLVar11);
//     if (iVar2 == 0) {
//       return;
//     }
//     this_00 = (MetaPerformer *)MetaPerformer::Current();
//     local_58[0] = MetaPerformer::Song(this_00);
//     uVar3 = (**(code **)(*(int *)(TheSongMgr + 4) + 0xa8))(TheSongMgr,local_58,1);
//     uVar4 = BandUser::GetDifficulty(*(BandUser **)pLVar1);
//     uVar5 = TrainerPanel::GetNumSections((TrainerPanel *)this);
//     if (uVar5 < *(ushort *)(this + 0xd8)) {
//       iVar6 = *(int *)(this + 0xd4) + uVar5 * 4;
//       if (iVar6 != *(int *)(this + 0xd4) + (uint)*(ushort *)(this + 0xd8) * 4) {
//         uVar5 = iVar6 - *(int *)(this + 0xd4);
//         uVar13 = ((int)uVar5 >> 2) + (uint)((int)uVar5 < 0 && (uVar5 & 3) != 0);
//         std_vec_range_assert(uVar13,0xffff,__FUNCTION__$50680);
//         *(short *)(this + 0xd8) = (short)uVar13;
//       }
//     }
//     else {
//       stlpmtx_std::_Vector_impl<><>::_M_fill_insert
//                 ((_Vector_impl<><> *)(this + 0xd4),
//                  (float *)(*(int *)(this + 0xd4) + (uint)*(ushort *)(this + 0xd8) * 4),
//                  uVar5 - *(ushort *)(this + 0xd8),(float *)&@50533);
//     }
//     iVar14 = 0;
//     for (iVar6 = 0; iVar7 = TrainerPanel::GetNumSections((TrainerPanel *)this), iVar6 < iVar7;
//         iVar6 = iVar6 + 1) {
//       iVar7 = (**(code **)(*(int *)(this + 4) + 0x74))(this,iVar2,uVar3,uVar4,iVar6);
//       if (iVar7 == 0) {
//         *(float *)(*(int *)(this + 0xd4) + iVar14) = 0.0;
//       }
//       else {
//         *(float *)(*(int *)(this + 0xd4) + iVar14) = 1.0;
//       }
//       iVar14 = iVar14 + 4;
//     }
//   }
//   pOVar12 = *(Object **)(this + 8);
//   uVar3 = ObjectDir::FindObject((ObjectDir *)pOVar12,::@stringBase0,false);
//   this_01 = (Object *)__dynamic_cast(uVar3,0,&RndDir::__RTTI,&Hmx::Object::__RTTI,0);
//   if (this_01 == (Object *)0x0) {
//     pOVar8 = pOVar12;
//     if (pOVar12 != (Object *)0x0) {
//       pOVar8 = (Object *)pOVar12->vptr;
//     }
//     iVar2 = PathName(pOVar8);
//     if (iVar2 == 0) {
//       pcVar9 = @STRING@Find<6RndDir>__9ObjectDirFPCcb_P6RndDir_80B75F2C;
//     }
//     else {
//       if (pOVar12 != (Object *)0x0) {
//         pOVar12 = (Object *)pOVar12->vptr;
//       }
//       pcVar9 = (char *)PathName(pOVar12);
//     }
//     pcVar9 = ::MakeString(kNotObjectMsg,::@stringBase0,pcVar9);
//     Debug::Fail((Debug *)TheDebug,pcVar9);
//   }
//   iVar2 = 1;
//   do {
//     pcVar9 = ::MakeString(s_fret_%02d.lbl_80b8182d,iVar2);
//     uVar3 = ObjectDir::FindObject((ObjectDir *)this_01,pcVar9,false);
//     this_02 = (UILabel *)__dynamic_cast(uVar3,0,&BandLabel::__RTTI,&Hmx::Object::__RTTI,0);
//     if (this_02 == (UILabel *)0x0) {
//       pOVar12 = this_01;
//       if (this_01 != (Object *)0x0) {
//         pOVar12 = (Object *)this_01->vptr;
//       }
//       iVar6 = PathName(pOVar12);
//       if (iVar6 == 0) {
//         pcVar10 = @STRING@Find<9BandLabel>__9ObjectDirFPCcb_P9BandLabel_80B77FE0;
//       }
//       else {
//         pOVar12 = this_01;
//         if (this_01 != (Object *)0x0) {
//           pOVar12 = (Object *)this_01->vptr;
//         }
//         pcVar10 = (char *)PathName(pOVar12);
//       }
//       pcVar9 = ::MakeString(kNotObjectMsg,pcVar9,pcVar10);
//       Debug::Fail((Debug *)TheDebug,pcVar9);
//     }
//     UILabel::SetInt(this_02,iVar2,false);
//     iVar2 = iVar2 + 1;
//   } while (iVar2 < 0x17);
//   iVar2 = 0;
//   do {
//     pcVar9 = ::MakeString(s_string_%02d.lbl_80b8183b,iVar2 + 1);
//     uVar3 = ObjectDir::FindObject((ObjectDir *)this_01,pcVar9,false);
//     this_03 = (AppLabel *)__dynamic_cast(uVar3,0,&AppLabel::__RTTI,&Hmx::Object::__RTTI,0);
//     if (this_03 == (AppLabel *)0x0) {
//       pOVar12 = this_01;
//       if (this_01 != (Object *)0x0) {
//         pOVar12 = (Object *)this_01->vptr;
//       }
//       iVar6 = PathName(pOVar12);
//       if (iVar6 == 0) {
//         pcVar10 = @STRING@Find<8AppLabel>__9ObjectDirFPCcb_P8AppLabel_80B7B12C;
//       }
//       else {
//         pOVar12 = this_01;
//         if (this_01 != (Object *)0x0) {
//           pOVar12 = (Object *)this_01->vptr;
//         }
//         pcVar10 = (char *)PathName(pOVar12);
//       }
//       pcVar9 = ::MakeString(kNotObjectMsg,pcVar9,pcVar10);
//       Debug::Fail((Debug *)TheDebug,pcVar9);
//     }
//     uVar5 = RGGetTuning(iVar2);
//     AppLabel::SetPitch(this_03,uVar5 & 0xff,0);
//     iVar2 = iVar2 + 1;
//   } while (iVar2 < 6);
//   return;
}

RGTrainerPanel::RGTrainerPanel(){

}