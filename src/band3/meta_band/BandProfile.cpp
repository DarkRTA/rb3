#include "BandProfile.h"
#include "ProfileMgr.h"
#include "AccomplishmentManager.h"
#include "game/GameMessages.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/BandSongMgr.h"
#include "game/BandUserMgr.h"
#include "bandobj/PatchDir.h"
#include "os/ProfilePicture.h"
#include "tour/TourProgress.h"
#include "tour/TourBand.h"
#include "system/utl/Symbols.h"

BandProfile::BandProfile(int i) : Profile(i), unk18(0), mAccomplishmentProgress(this), unk740(0), unk744(-1), unk74c(-1), unk750(-1), unk784(-1), unk6f70(0), unk6f74(0), mProfileAssets(this), unk6fb4(0), unk6fb8(0) {
    mSaveSizeMethod = &SaveSize;
    LocalBandUser* user = GetAssociatedLocalBandUser();
    mScores = new SongStatusMgr(user, TheSongMgr);
    mProfilePicture = new ProfilePicture(GetPadNum(), this);
    for(int n = 0; n < 8; n++) mPatches.push_back(new PatchDir());
    for(int n = 0; n < 4; n++) mStandIns.push_back(StandIn());
    mTourProgress = new TourProgress();
    unk6fc0 = new TourBand(this);
}

BandProfile::~BandProfile() {
    DeleteAll();
    RELEASE(mScores);
    RELEASE(mProfilePicture);
    RELEASE(unk6fc0);
    RELEASE(mTourProgress);
}

void BandProfile::Poll() {
    mProfilePicture->Poll();
}

void BandProfile::GetAvailableStandins(int idx, std::vector<TourCharLocal*>& chars) const {
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal* pCharacter = mCharacters[i];
        MILO_ASSERT(pCharacter, 0x76);
        int charidx = GetCharacterStandinIndex(pCharacter);
        if(charidx == -1 || charidx == idx){
            chars.push_back(pCharacter);
        }
    }
}

void BandProfile::GetAllChars(std::vector<TourCharLocal*>& chars) const {
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal* tchar = mCharacters[i];
        chars.push_back(tchar);
    }
}

void BandProfile::GetAvailableCharacters(std::vector<TourCharLocal*>& chars) const {
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal* pCharacter = mCharacters[i];
        MILO_ASSERT(pCharacter, 0x90);
        if(TheBandUserMgr->IsCharAvailable(pCharacter)){
            chars.push_back(pCharacter);
        }
    }
}

CharData* BandProfile::GetCharFromGuid(const HxGuid& guid) {
    int size = mCharacters.size();
    for (int i = 0; i < size; i++) {
        if(mCharacters[i]->mGuid == guid) return mCharacters[i];
    }
    return 0;
}

int BandProfile::GetMaxChars() const {
    return 10;
}

void BandProfile::AddNewChar(TourCharLocal* pChar) {
    MILO_ASSERT(pChar, 0xaf);
    MILO_ASSERT(NumChars() < kMaxCharacters, 0xb0);
    mCharacters.push_back(pChar);
    mDirty = true;
}

void BandProfile::DeleteChar(TourCharLocal* pChar){
    MILO_ASSERT(pChar, 0xB9);
    for(std::vector<TourCharLocal*>::iterator it = mCharacters.begin(); it != mCharacters.end(); ++it){
        if(pChar == *it){
            PotentiallyDeleteStandin(pChar->mGuid);
            mCharacters.erase(it);
            delete pChar;
            mDirty = true;
            return;
        }
    }
}


void BandProfile::RenameCharacter(TourCharLocal* pChar, const char* name){
    MILO_ASSERT(pChar, 0xCC);
    for (int i = 0; i < mCharacters.size(); i++) {
        if(pChar == mCharacters[i]){
            mCharacters[i]->SetCharacterName(name);
            mDirty = true;
            break;
        }
    }
}

bool BandProfile::HasChar(const TourCharLocal* character) {
    for (std::vector<TourCharLocal*>::const_iterator it = mCharacters.begin(); it != mCharacters.end(); it++) {
        if (character == *it) {
            return true;
        }
    }
    return false;
}

void BandProfile::GetFirstEmptyPatch() {}
// void BandProfile::GetTexAtPatchIndex(int) const {}
void BandProfile::GetPatchIndex(const PatchDir*) const {}

// void BandProfile::PotentiallyDeleteStandin(HxGuid guid) {
//     for (std::vector<StandIn*>::iterator it = mStandIns.begin(); it != mStandIns.end(); it++) {
//         // standin guid is 0x1c
//         // it->SetNone();
//     }
// }

// void BandProfile::GetCharacterStandinIndex(CharData*) const {}
// StandIn* BandProfile::GetStandIn(int index) const {
//     MILO_ASSERT_RANGE(index, 0, mStandIns.size(), 0x14d);
//     return mStandIns[index];
// }

// StandIn* BandProfile::AccessStandIn(int index) {
//     MILO_ASSERT_RANGE(index, 0, mStandIns.size(), 0x14d);
//     return mStandIns[index];
// }

// int BandProfile::GetNumStandins() const {
//     int standIns = 0;
//     for (std::vector<StandIn*>::const_iterator it = mStandIns.begin(); it != mStandIns.end(); it++) {
//         StandIn* standIn = *it;
//         if (!standIn->IsNone()) {
//             standIns++;
//         }
//     }
//     return standIns;
// }

TourProgress* BandProfile::GetTourProgress() {
    return mTourProgress;
}

bool BandProfile::OwnsTourProgress(const TourProgress* tourProgress) {
    return mTourProgress == tourProgress;
}

void BandProfile::UpdateScore(int, const PerformerStatsInfo&, bool) {}
void BandProfile::UploadPerformance(PerformanceData*) {}
void BandProfile::GetNumDirtyPerformanceData() {}
void BandProfile::UploadDirtyPerformanceData() {}
void BandProfile::UploadDirtyAccomplishmentData() {}
void BandProfile::UploadDirtyScoreData() {}
void BandProfile::UploadDirtyData() {}
void BandProfile::SetSongReview(int, int) {}
// void BandProfile::GetSongReview(int) {}
// void BandProfile::GetSongStatusMgr() const {}
void BandProfile::GetSongHighScore(int, ScoreType) const {}
void BandProfile::GetSavedSetlists() const {}
void BandProfile::AddSavedSetlist(const char*, const char*, bool, const PatchDescriptor&, const std::vector<int>&) {}
void BandProfile::DeleteSavedSetlist(LocalSavedSetlist*) {}
void BandProfile::SetlistChanged(LocalSavedSetlist*) {}
void BandProfile::NumSavedSetlists() const {}

bool BandProfile::HasCheated() const {
}

void BandProfile::GetUploadFriendsToken() const {}
void BandProfile::SetUploadFriendsToken(int) {}
void BandProfile::SaveFixed(FixedSizeSaveableStream&) const {}
void BandProfile::PreLoad() {}

void BandProfile::LoadFixed(FixedSizeSaveableStream&, int) {

}

bool BandProfile::IsUnsaved() const {}
void BandProfile::SaveLoadComplete(ProfileSaveState) {}
bool BandProfile::HasSomethingToUpload() {}
void BandProfile::DeleteAll() {}

LocalBandUser* BandProfile::GetAssociatedLocalBandUser() const {
    int num = GetPadNum();
    // TheBandUserMgr->GetUserFromPad(num);
}

void BandProfile::CheckForFinishedTrainerAccomplishments() {
    bool validSaveData = HasValidSaveData();
    if (validSaveData) {
        LocalBandUser* pLocalUser = GetAssociatedLocalBandUser();
        MILO_ASSERT(pLocalUser, 0x3be);
        TheAccomplishmentMgr->CheckForFinishedTrainerAccomplishmentsForUser(pLocalUser);
    }
}

void BandProfile::SetProGuitarSongLessonComplete(int, Difficulty) {}
void BandProfile::SetProBassSongLessonComplete(int, Difficulty) {}
void BandProfile::SetProKeyboardSongLessonComplete(int, Difficulty) {}
void BandProfile::SetProGuitarSongLessonSectionComplete(int, Difficulty, int) {}
void BandProfile::SetProBassSongLessonSectionComplete(int, Difficulty, int) {}
void BandProfile::SetProKeyboardSongLessonSectionComplete(int, Difficulty, int) {}
void BandProfile::IsProGuitarSongLessonSectionComplete(int, Difficulty, int) const {}
void BandProfile::IsProBassSongLessonSectionComplete(int, Difficulty, int) const {}
void BandProfile::IsProKeyboardSongLessonSectionComplete(int, Difficulty, int) const {}

bool BandProfile::IsLessonComplete(const Symbol& symbol, float) const {
    GetLessonCompleteSpeed(symbol);
}

void BandProfile::GetLessonComplete(const Symbol&) const {}
void BandProfile::GetLessonCompleteSpeed(const Symbol&) const {}
void BandProfile::SetLessonComplete(const Symbol&, float) {}
void BandProfile::EarnAccomplishment(Symbol) {}
// void BandProfile::GetAccomplishmentProgress() const {}

// void BandProfile::AccessAccomplishmentProgress() {}

void BandProfile::GetHardcoreIconLevel() const {}

void BandProfile::SetHardcoreIconLevel(int) {}

void BandProfile::GetTourBand() {}

// void BandProfile::GetBandName() const {}

void BandProfile::HasBandNameBeenSet() const {

}
// void BandProfile::IsBandNameProfanityChecked() const {}

RndTex* BandProfile::GetBandLogoTex() {}

void BandProfile::SendBandLogo() {}

void BandProfile::GrantCampaignKey(Symbol) {}

bool BandProfile::HasCampaignKey(Symbol) {}

void BandProfile::UnlockModifier(Symbol) {}

bool BandProfile::HasUnlockedModifier(Symbol) {}
void BandProfile::HandlePerformanceDataUploadSuccess() {}
void BandProfile::UpdatePerformanceData(const Stats&, int, ScoreType, Difficulty, Symbol, int, int, bool) {}

LocalBandUser* BandProfile::GetLocalBandUser() const {
    return TheBandUserMgr->GetUserFromPad(GetPadNum());
}

void BandProfile::GetAssociatedUsers(std::vector<LocalBandUser*>&) const {}
void BandProfile::CheckWebLinkStatus() {}
void BandProfile::CheckWebSetlistStatus() {}
void BandProfile::HasSeenHint(Symbol) const {}
void BandProfile::SetHasSeenHint(Symbol) {}
// void BandProfile::GetLastCharUsed() const {}
void BandProfile::SetLastCharUsed(CharData*) {}
void BandProfile::SetLastPrefabCharUsed(Symbol) {}
void BandProfile::FakeProfileFill() {}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandProfile)
    HANDLE_ACTION(get_associated_user, GetAssociatedLocalBandUser())
    HANDLE_ACTION(is_lesson_complete, IsLessonComplete(_msg->Sym(2), _msg->Float(3)))
    HANDLE_ACTION(set_lesson_complete, SetLessonComplete(_msg->Sym(2), _msg->Float(3)))
    HANDLE_ACTION(unlock_modifier, UnlockModifier(_msg->Sym(2)))
    HANDLE_ACTION(has_unlocked_modifier, HasUnlockedModifier(_msg->Sym(2)))
    HANDLE_ACTION(get_accomplishment_progress, AccessAccomplishmentProgress())
    HANDLE_ACTION(get_hardcore_icon_level, GetHardcoreIconLevel())
    HANDLE_ACTION(set_hardcore_icon_level, SetHardcoreIconLevel(_msg->Int(2)))
    HANDLE_ACTION(set_song_review, SetSongReview(_msg->Int(2), _msg->Int(3)))
    // HANDLE_ACTION(setlist_changed, SetlistChanged(_msg->Obj<LocalSavedSetlist>(2)))
    HANDLE_ACTION(max_chars, GetMaxChars())
    HANDLE_ACTION(get_picture_tex, GetPictureTex())
    HANDLE_ACTION(get_band_logo_tex, GetBandLogoTex())
    HANDLE_ACTION(get_first_empty_patch, GetFirstEmptyPatch())
    HANDLE_ACTION(get_band_name, GetBandName())
    // HANDLE_ACTION(set_band_name, SetBandName(_msg->Str(2)))
    HANDLE_ACTION(has_band_name_been_set, HasBandNameBeenSet())
    HANDLE_ACTION(get_num_chars, NumChars())
    HANDLE_ACTION(has_seen_hint, HasSeenHint(_msg->Sym(2)))
    HANDLE_ACTION(set_has_seen_hint, SetHasSeenHint(_msg->Sym(2)))
    HANDLE_ACTION(access_accomplishment_progress, AccessAccomplishmentProgress())
    HANDLE_ACTION(auto_fake_fill, AutoFakeFill(_msg->Int(2)))
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_CHECK(0x67a)
END_HANDLERS
#pragma pop



//   local_d4 = RockCentralOpCompleteMsg::Type
//                        ((RockCentralOpCompleteMsg *)0x0 )
//   ;
//   iVar1 = Symbol::operator_==((Symbol *)local_b0,
//                               (Symbol *)&local_d4);
//   if (iVar1 != 0) {
//     RockCentralOpCompleteMsg::RockCentralOpCompleteMsg
//               (aRStack_7c,this_02);
//     OnMsg(aBStack_90,(RockCentralOpCompleteMsg *)this_ 03
//          );
//     RockCentralOpCompleteMsg::~RockCentralOpCompleteMsg
//               (aRStack_7c);
//     iVar1 = DataNode::Type((DataNode *)aBStack_90);
//     if (iVar1 != 0) {
//       DataNode::DataNode(this_00,(DataNode *)aBStack_90 )
//       ;
//       DataNode::~DataNode((DataNode *)aBStack_90);
//       MessageTimer::~MessageTimer(aMStack_58);
//       goto LAB_80268a74;
//     }
//     DataNode::~DataNode((DataNode *)aBStack_90);
//   }
//   piVar8 = (int *)(this_03 + 0xb8);
//   if (piVar8 != (int *)0x0) {
//     (**(code **)(*piVar8 + 0x14))
//               (aDStack_98,piVar8,this_02,0);
//     iVar1 = DataNode::Type(aDStack_98);
//     if (iVar1 != 0) {
//       DataNode::DataNode(this_00,aDStack_98);
//       DataNode::~DataNode(aDStack_98);
//       MessageTimer::~MessageTimer(aMStack_58);
//       goto LAB_80268a74;
//     }
//     DataNode::~DataNode(aDStack_98);
//   }
//   piVar8 = *(int **)(this_03 + 0x48);
//   if (piVar8 != (int *)0x0) {
//     (**(code **)(*piVar8 + 0x20))
//               (aDStack_a0,piVar8,this_02,0);
//     iVar1 = DataNode::Type(aDStack_a0);
//     if (iVar1 != 0) {
//       DataNode::DataNode(this_00,aDStack_a0);
//       DataNode::~DataNode(aDStack_a0);
//       MessageTimer::~MessageTimer(aMStack_58);
//       goto LAB_80268a74;
//     }
//     DataNode::~DataNode(aDStack_a0);
//   }
//   Profile::Handle(aPStack_a8,(DataArray *)this_03,
//                   SUB41(this_02,0));
//   iVar1 = DataNode::Type((DataNode *)aPStack_a8);
//   if (iVar1 == 0) {
//     DataNode::~DataNode((DataNode *)aPStack_a8);
//     if (in_r6 != 0) {
//       local_d8 = local_b0[0];
//       if (this_03 != (BandProfile *)0x0) {
//         this_03 = *(BandProfile **)(this_03 + 8);
//       }
//       pcVar6 = (char *)PathName((Object *)this_03);
//       pcVar6 = ::MakeString(
//       s_%s(%d):_%s_unhandled_msg:_%s_80b8d61f,
//       ::@stringBase0,0x67a,pcVar6,(Symbol)&local_d8);
//       DebugNotifier::operator_<<
//                 ((DebugNotifier *)&TheDebugNotifier,
//                  pcVar6);
//     }
//     DataNode::DataNode(this_00,0,0);
//     MessageTimer::~MessageTimer(aMStack_58);
//   }
//   else {
//     DataNode::DataNode(this_00,(DataNode *)aPStack_a8) ;
//     DataNode::~DataNode((DataNode *)aPStack_a8);
//     MessageTimer::~MessageTimer(aMStack_58);
//   }



void BandProfile::GetPictureTex() {}
void BandProfile::AutoFakeFill(int) {}
