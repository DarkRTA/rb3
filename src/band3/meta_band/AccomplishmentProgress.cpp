#include "meta_band/AccomplishmentProgress.h"
#include "Accomplishment.h"
#include "game/BandUser.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/MetaPerformer.h"
#include "os/Debug.h"
#include "utl/Symbol.h"

GamerAwardStatus::GamerAwardStatus() : unk8(-1), unkc(0), unk10(0) {
    mSaveSizeMethod = &SaveSize;
}

GamerAwardStatus::~GamerAwardStatus(){

}

void GamerAwardStatus::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << unk8;
    stream << unkc;
}

int GamerAwardStatus::SaveSize(int){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "GamerpicAward", 8);
    }
    return 8;
}

void GamerAwardStatus::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    stream >> unk8;
    int iii = 0;
    stream >> iii;
    unkc = iii;
}

AccomplishmentProgress::AccomplishmentProgress(BandProfile* profile) : mParentProfile(profile), unk84(0), unk644(1), unk648(0) {
    Clear();
    mSaveSizeMethod = &SaveSize;
}

AccomplishmentProgress::~AccomplishmentProgress(){

}

bool AccomplishmentProgress::AddAccomplishment(Symbol s){
    if(!IsAccomplished(s)){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
        MILO_ASSERT(pAccomplishment, 0xC1);
        NotifyPlayerOfAccomplishment(s, pAccomplishment->GetIconArt());
        LocalBandUser* pUser = mParentProfile->GetAssociatedLocalBandUser();
        MILO_ASSERT(pUser, 199);
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0xCB);
        TheAccomplishmentMgr->AddGoalAcquisitionInfo(s, pUser->UserName(), pPerformer->Song());
        if(pAccomplishment->HasAward()){
            AddAward(pAccomplishment->GetAward(), s);
        }
        int lbhcstatus = TheAccomplishmentMgr->GetLeaderboardHardcoreStatus(unk4c.size());
        TheAccomplishmentMgr->GetIconHardCoreStatus(unk4c.size());
        unk4c.insert(s);
        unk64.insert(s);

        Symbol cat = pAccomplishment->GetCategory();
        AccomplishmentCategory* pCategory = TheAccomplishmentMgr->GetAccomplishmentCategory(cat);
        MILO_ASSERT(pCategory, 0xEC);
        if(TheAccomplishmentMgr->IsCategoryComplete(mParentProfile, cat)){
            NotifyPlayerOfCategoryComplete(cat);
            if(pCategory->HasAward()){
                AddAward(pCategory->GetAward(), cat);
            }
        }

        Symbol group = pCategory->GetGroup();
        AccomplishmentGroup* pGroup = TheAccomplishmentMgr->GetAccomplishmentGroup(group);
        MILO_ASSERT(pGroup, 0xFB);
        if(TheAccomplishmentMgr->IsGroupComplete(mParentProfile, group)){
            NotifyPlayerOfGroupComplete(group);
            if(pGroup->HasAward()){
                AddAward(pGroup->GetAward(), group);
            }
        }
    }
    else return false;
}

// undefined4 __thiscall
// AccomplishmentProgress::AddAccomplishment(AccomplishmentProgress *this,Symbol param_1)

// {
  
//   local_38[0] = *(undefined4 *)param_1.mStr;
//   iVar1 = IsAccomplished(this,(Symbol)local_38);
//   if (iVar1 == 0) {

//     this_00 = (Accomplishment *)
//               AccomplishmentManager::GetAccomplishment(TheAccomplishmentMgr,(Symbol)&local_3c); pAccomplishment=
//     iVar1 = BandProfile::GetAssociatedLocalBandUser(*(BandProfile **)(this + 0x3c)); pUser
//     this_01 = (MetaPerformer *)MetaPerformer::Current(); pPerformer

//     uVar3 = Accomplishment::GetCategory(this_00);
//     local_54 = uVar3;
//     this_02 = (AccomplishmentCategory *)
//               AccomplishmentManager::GetAccomplishmentCategory
//                         (TheAccomplishmentMgr,(Symbol)&local_54); pCategory

//     uVar3 = AccomplishmentCategory::GetGroup(this_02);
//     local_68 = uVar3;
//     this_03 = (AccomplishmentGroup *)
//               AccomplishmentManager::GetAccomplishmentGroup(TheAccomplishmentMgr,(Symbol)&local_68 ); pGroup

//     iVar4 = Campaign::GetCampaignLevelForMetaScore(TheCampaign,*(int *)(this + 0x84));
//     local_7c = Accomplishment::GetMetaScoreValue(this_00);
//     iVar5 = AccomplishmentManager::GetMetaScoreValue(TheAccomplishmentMgr,(Symbol)&local_7c);
//     SetMetaScore(this,*(int *)(this + 0x84) + iVar5);
//     iVar5 = Campaign::GetCampaignLevelForMetaScore(TheCampaign,*(int *)(this + 0x84));
//     if (iVar5 != iVar4) {
//       local_80 = iVar5;
//       this_04 = (CampaignLevel *)Campaign::GetCampaignLevel(TheCampaign,(Symbol)&local_80);
//       if (this_04 == (CampaignLevel *)0x0) {
//         pcVar2 = ::MakeString(kAssertStr,s_AccomplishmentProgress.cpp_80b891cd,0x112,
//                               s_pLevel_80b8921a);
//         Debug::Fail((Debug *)TheDebug,pcVar2);
//       }
//       local_84 = CampaignLevel::GetEarnedText(this_04);
//       NotifyPlayerOfCampaignLevel(this,(Symbol)&local_84);
//       if (*(int *)(this + 0x3c) == 0) {
//         pcVar2 = ::MakeString(kAssertStr,s_AccomplishmentProgress.cpp_80b891cd,0x11a,
//                               s_mParentProfile_80b89221);
//         Debug::Fail((Debug *)TheDebug,pcVar2);
//       }
//       uVar3 = Profile::GetPadNum(*(Profile **)(this + 0x3c));
//       local_8c = career_level;
//       local_88 = pid;
//       local_90 = iVar5;
//       iVar4 = (**(code **)(*(int *)(TheServer + 4) + 0x40))(TheServer,uVar3);
//       SendDataPoint(s_career/levelup_80b89230,(Symbol)&local_88,iVar4,(Symbol)&local_8c,
//                     (Symbol)&local_90);
//       iVar4 = CampaignLevel::HasAward(this_04);
//       if (iVar4 != 0) {
//         local_94 = CampaignLevel::GetAward(this_04);
//         local_98 = iVar5;
//         AddAward(this,(Symbol)&local_94,(Symbol)&local_98);
//       }
//     }
//     iVar4 = AccomplishmentManager::GetLeaderboardHardcoreStatus
//                       (TheAccomplishmentMgr,*(int *)(this + 0x5c));
//     if (iVar1 != iVar4) {
//       SendHardCoreStatusUpdateToRockCentral(this);
//     }
//     if (*(int *)(this + 0x3c) == 0) {
//       pcVar2 = ::MakeString(kAssertStr,s_AccomplishmentProgress.cpp_80b891cd,0x13e,
//                             s_mParentProfile_80b89221);
//       Debug::Fail((Debug *)TheDebug,pcVar2);
//     }
//     Profile::MakeDirty(*(Profile **)(this + 0x3c));
//     uVar3 = 1;
//   }
//   else {
//     uVar3 = 0;
//   }
//   return uVar3;
// }

bool AccomplishmentProgress::IsAccomplished(Symbol s) const {
    return unk4c.find(s) != unk4c.end();
}