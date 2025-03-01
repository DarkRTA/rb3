#include "BandProfile.h"
#include "ProfileMgr.h"
#include "AccomplishmentManager.h"
#include "SavedSetlist.h"
#include "game/BandUser.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/CharData.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/PerformanceData.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/BandSongMgr.h"
#include "game/BandUserMgr.h"
#include "bandobj/PatchDir.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentral.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/OSFuncs.h"
#include "os/ProfilePicture.h"
#include "os/User.h"
#include "tour/TourChar.h"
#include "tour/TourProgress.h"
#include "tour/TourBand.h"
#include "system/utl/Symbols.h"
#include "utl/Symbols2.h"

BandProfile::BandProfile(int i)
    : Profile(i), unk18(0), mAccomplishmentProgress(this), unk740(0),
      mAccomplishmentDataUploadContextID(-1), unk74c(-1), unk750(-1),
      mPerformanceDataUploadContextID(-1), unk6f70(0), unk6f74(0), mProfileAssets(this),
      unk6fb4(0), unk6fb8(0) {
    mSaveSizeMethod = &SaveSize;
    LocalBandUser *user = GetAssociatedLocalBandUser();
    mScores = new SongStatusMgr(user, TheSongMgr);
    mProfilePicture = new ProfilePicture(GetPadNum(), this);
    for (int n = 0; n < 8; n++)
        mPatches.push_back(new PatchDir());
    for (int n = 0; n < 4; n++)
        mStandIns.push_back(StandIn());
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

void BandProfile::Poll() { mProfilePicture->Poll(); }

void BandProfile::GetAvailableStandins(int idx, std::vector<TourCharLocal *> &chars)
    const {
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal *pCharacter = mCharacters[i];
        MILO_ASSERT(pCharacter, 0x76);
        int charidx = GetCharacterStandinIndex(pCharacter);
        if (charidx == -1 || charidx == idx) {
            chars.push_back(pCharacter);
        }
    }
}

void BandProfile::GetAllChars(std::vector<TourCharLocal *> &chars) const {
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal *tchar = mCharacters[i];
        chars.push_back(tchar);
    }
}

void BandProfile::GetAvailableCharacters(std::vector<TourCharLocal *> &chars) const {
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal *pCharacter = mCharacters[i];
        MILO_ASSERT(pCharacter, 0x90);
        if (TheBandUserMgr->IsCharAvailable(pCharacter)) {
            chars.push_back(pCharacter);
        }
    }
}

CharData *BandProfile::GetCharFromGuid(const HxGuid &guid) {
    int size = mCharacters.size();
    for (int i = 0; i < size; i++) {
        if (mCharacters[i]->mGuid == guid)
            return mCharacters[i];
    }
    return 0;
}

int BandProfile::GetMaxChars() const { return 10; }

void BandProfile::AddNewChar(TourCharLocal *pChar) {
    MILO_ASSERT(pChar, 0xaf);
    MILO_ASSERT(NumChars() < kMaxCharacters, 0xb0);
    mCharacters.push_back(pChar);
    mDirty = true;
}

void BandProfile::DeleteChar(TourCharLocal *pChar) {
    MILO_ASSERT(pChar, 0xB9);
    for (int i = 0; i < mCharacters.size(); i++) {
        if (pChar == mCharacters[i]) {
            PotentiallyDeleteStandin(pChar->GetGuid());
            mCharacters.erase(mCharacters.begin() + i);
            delete pChar;
            mDirty = true;
            return;
        }
    }
}

void BandProfile::RenameCharacter(TourCharLocal *pChar, const char *name) {
    MILO_ASSERT(pChar, 0xCC);
    for (int i = 0; i < mCharacters.size(); i++) {
        if (pChar == mCharacters[i]) {
            mCharacters[i]->SetCharacterName(name);
            mDirty = true;
            break;
        }
    }
}

bool BandProfile::HasChar(const TourCharLocal *character) {
    for (std::vector<TourCharLocal *>::const_iterator it = mCharacters.begin();
         it != mCharacters.end();
         it++) {
        if (character == *it) {
            return true;
        }
    }
    return false;
}

PatchDir *BandProfile::GetFirstEmptyPatch() {
    FOREACH (it, mPatches) {
        PatchDir *cur = *it;
        if (!cur->HasLayers())
            return cur;
    }
    return nullptr;
}

RndTex *BandProfile::GetTexAtPatchIndex(int ix) const {
    MILO_ASSERT(mPatches.size() >= ix, 0xF7);
    PatchDir *patch = mPatches[ix];
    MILO_ASSERT(patch, 0xF9);
    return patch->HasLayers() ? patch->GetTex() : nullptr;
}

int BandProfile::GetPatchIndex(const PatchDir *dir) const {
    FOREACH (it, mPatches) {
        if (*it == dir) {
            return it - mPatches.begin();
        }
    }
    return -1;
}

void BandProfile::PotentiallyDeleteStandin(HxGuid guid) {
    FOREACH (it, mStandIns) {
        if (it->mGuid == guid) {
            it->SetNone();
        }
    }
}

int BandProfile::GetCharacterStandinIndex(CharData *cd) const {
    int idx = 0;
    for (std::vector<StandIn>::const_iterator it = mStandIns.begin();
         it != mStandIns.end();
         ++it, ++idx) {
        if (it->IsCustomCharacter()) {
            if (it->mGuid == cd->GetGuid())
                return idx;
        } else if (it->IsPrefabCharacter() && !cd->IsCustomizable()) {
            PrefabChar *pPrefab = dynamic_cast<PrefabChar *>(cd);
            MILO_ASSERT(pPrefab, 0x131);
            if (it->mName == pPrefab->GetPrefabName()) {
                return idx;
            }
        }
    }
    return -1;
}

const StandIn &BandProfile::GetStandIn(int index) const {
    MILO_ASSERT_RANGE(index, 0, mStandIns.size(), 0x146);
    return mStandIns[index];
}

StandIn &BandProfile::AccessStandIn(int index) {
    MILO_ASSERT_RANGE(index, 0, mStandIns.size(), 0x14D);
    return mStandIns[index];
}

int BandProfile::GetNumStandins() const {
    int num = 0;
    FOREACH (it, mStandIns) {
        if (!it->IsNone()) {
            num++;
        }
    }
    return num;
}

TourProgress *BandProfile::GetTourProgress() { return mTourProgress; }

bool BandProfile::OwnsTourProgress(const TourProgress *tourProgress) {
    return mTourProgress == tourProgress;
}

void BandProfile::UpdateScore(int i1, const PerformerStatsInfo &info, bool b3) {
    if (mScores->UpdateSong(i1, info, b3)) {
        mDirty = true;
        if (!b3) {
            UploadDirtyScoreData();
        }
    }
}

void BandProfile::UploadPerformance(PerformanceData *data) {
    MILO_ASSERT(mPerformanceDataUploadContextID == -1, 0x183);
    mPerformanceDataUploadContextID = unk740;
    unk740++;
    static DataResultList tempResult;
    TheRockCentral.RecordPerformance(
        this, data, mPerformanceDataUploadContextID, this, tempResult
    );
}

int BandProfile::GetNumDirtyPerformanceData() {
    if (unk6f74 >= unk6f70) {
        return unk6f74 - unk6f70;
    } else
        return (unk6f74 + 50) - unk6f70;
}

void BandProfile::UploadDirtyPerformanceData() {
    if (mPerformanceDataUploadContextID < 0 && GetNumDirtyPerformanceData() > 0) {
        UploadPerformance(&mPerformanceDataList[unk6f70]);
    }
}

void BandProfile::UploadDirtyAccomplishmentData() {
    if (mAccomplishmentDataUploadContextID < 0
        && mAccomplishmentProgress.IsUploadDirty()) {
        MILO_ASSERT(mAccomplishmentDataUploadContextID == -1, 0x1AF);
        mAccomplishmentDataUploadContextID = unk740;
        unk740++;
        static DataResultList tempResult;
        TheRockCentral.RecordAccomplishmentData(
            this,
            &mAccomplishmentProgress,
            mAccomplishmentDataUploadContextID,
            this,
            tempResult
        );
        mAccomplishmentProgress.HandleUploadStarted();
    }
}

void BandProfile::UploadDirtyScoreData() { mScores->UploadDirtyScores(); }

void BandProfile::UploadDirtyData() {
    if (TheContentMgr->RefreshDone()) {
        UploadDirtyScoreData();
        UploadDirtyPerformanceData();
        UploadDirtyAccomplishmentData();
    }
}

void BandProfile::SetSongReview(int i1, int i2) {
    if (mScores->SetSongReview(i1, i2)) {
        mDirty = true;
    }
}

int BandProfile::GetSongReview(int i1) { return mScores->GetSongReview(i1); }
SongStatusMgr *BandProfile::GetSongStatusMgr() const { return mScores; }

int BandProfile::GetSongHighScore(int i, ScoreType s) const {
    return mScores->GetHighScore(i, s);
}

const std::vector<LocalSavedSetlist *> &BandProfile::GetSavedSetlists() const {
    return mSavedSetlists;
}

SavedSetlist *BandProfile::AddSavedSetlist(
    const char *c1,
    const char *c2,
    bool b3,
    const PatchDescriptor &desc,
    const std::vector<int> &vec
) {
    LocalBandUser *localUser = GetAssociatedLocalBandUser();
    MILO_ASSERT(localUser, 500);
    if (b3) {
        TheAccomplishmentMgr->EarnAccomplishment(localUser, acc_createsetlist);
    }
    MILO_ASSERT(mSavedSetlists.size() < kMaxSavedSetlists, 0x1FC);
    LocalSavedSetlist *setlist = new LocalSavedSetlist(this, c1, c2, b3);
    setlist->mArt = desc;
    setlist->SetSongs(vec);
    mSavedSetlists.push_back(setlist);
    mDirty = true;
    return mSavedSetlists.back();
}

void BandProfile::DeleteSavedSetlist(LocalSavedSetlist *setlist) {
    std::vector<LocalSavedSetlist *>::iterator it =
        std::find(mSavedSetlists.begin(), mSavedSetlists.end(), setlist);
    if (it != mSavedSetlists.end()) {
        mSavedSetlists.erase(it);
        mDirty = true;
    }
}

void BandProfile::SetlistChanged(LocalSavedSetlist *setlist) {
    std::vector<LocalSavedSetlist *>::iterator it =
        std::find(mSavedSetlists.begin(), mSavedSetlists.end(), setlist);
    if (it != mSavedSetlists.end()) {
        mDirty = true;
    }
}

int BandProfile::NumSavedSetlists() const { return mSavedSetlists.size(); }
bool BandProfile::HasCheated() const { return TheProfileMgr.mAllUnlocked; }
int BandProfile::GetUploadFriendsToken() const { return unk6fb4; }
void BandProfile::SetUploadFriendsToken(int i) { unk6fb4 = i; }

void BandProfile::SaveFixed(FixedSizeSaveableStream &fsss) const {
    MILO_ASSERT(!HasCheated(), 562);
    fsss << *mTourProgress;
    SaveStdPtr(fsss, mCharacters, kMaxCharacters, TourChar::SaveSize(151));
    MILO_ASSERT(mPatches.size() == kMaxPatchesPerProfile, 572);
    SaveStdPtr(fsss, mPatches, kMaxPatchesPerProfile, PatchDir::SaveSize(151));
    fsss.EnableWriteEncryption();
    fsss << *mScores;
    fsss.DisableEncryption();
    SaveStdPtr(fsss, mSavedSetlists, 20, LocalSavedSetlist::SaveSize(151));
    SaveStd(fsss, mLessonCompletions, 1000, 8);
    SaveStd(fsss, unk70, 20);
    SaveStd(fsss, unk88, 20);
    SaveStd(fsss, unka0, 15);
    fsss << mAccomplishmentProgress;
    for (int i = 0; i < 50; i++) {
        fsss << mPerformanceDataList[i];
    }
    fsss << unk6f70;
    fsss << unk6f74;
    fsss << mProfileAssets;
    fsss << unk6fb8;
    fsss << unk6fb4;
    fsss << mGameplayOptions;
    fsss << *unk6fc0;
    for (int i = 0; i < mStandIns.size(); i++) {
        fsss << mStandIns[i];
    }
    fsss << unk5c;
    mDirty = false;
}

int BandProfile::SaveSize(int i) {
    int x = TourProgress::SaveSize(i);
    x += TourChar::SaveSize(i) * 10 + 4;
    x += PatchDir::SaveSize(i) * 8 + 4;
    if (i >= 150)
        x += 4;
    x += SongStatusMgr::SaveSize(i);
    x += LocalSavedSetlist::SaveSize(i) * 20 + 0x2030;
    x += AccomplishmentProgress::SaveSize(i);
    if (i < 149) {
        x += PerformanceData::SaveSize(i) * 50 + 4;
    } else {
        x += PerformanceData::SaveSize(i) * 50;
        x += 8;
    }
    x += ProfileAssets::SaveSize(i);
    x += 8;
    x += GameplayOptions::SaveSize(i);
    x += TourBand::SaveSize(i);
    x += StandIn::SaveSize(i) * 4;
    if (i >= 134)
        x += HxGuid::SaveSize();
    if (FixedSizeSaveable::sPrintoutsEnabled) {
        MILO_LOG("* %s = %i\n", "BandProfile", x);
    }
    return x;
}

void BandProfile::PreLoad() {
    if (!MainThread()) {
        MILO_WARN("BandProfile::PreLoad is unsafe to call in the main thread!\n");
    }
    DeleteAll();
}

void BandProfile::LoadFixed(FixedSizeSaveableStream &, int) {}

bool BandProfile::IsUnsaved() const {}
void BandProfile::SaveLoadComplete(ProfileSaveState) {}
bool BandProfile::HasSomethingToUpload() {}
void BandProfile::DeleteAll() {}

LocalBandUser *BandProfile::GetAssociatedLocalBandUser() const {
    int num = GetPadNum();
    // TheBandUserMgr->GetUserFromPad(num);
}

void BandProfile::CheckForFinishedTrainerAccomplishments() {
    bool validSaveData = HasValidSaveData();
    if (validSaveData) {
        LocalBandUser *pLocalUser = GetAssociatedLocalBandUser();
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
bool BandProfile::IsProGuitarSongLessonSectionComplete(int, Difficulty, int) const {}
bool BandProfile::IsProBassSongLessonSectionComplete(int, Difficulty, int) const {}
bool BandProfile::IsProKeyboardSongLessonSectionComplete(int, Difficulty, int) const {}

bool BandProfile::IsLessonComplete(const Symbol &symbol, float speed) const {
    return GetLessonCompleteSpeed(symbol) >= speed;
}

void BandProfile::GetLessonComplete(const Symbol &) const {}
float BandProfile::GetLessonCompleteSpeed(const Symbol &sym) const {
    float ret = 0;
    std::map<Symbol, float>::const_iterator it = mLessonCompletions.find(sym);
    if (it != mLessonCompletions.end())
        ret = it->second;
    return ret;
}
void BandProfile::SetLessonComplete(const Symbol &, float) {}
void BandProfile::EarnAccomplishment(Symbol) {}
// void BandProfile::GetAccomplishmentProgress() const {}

// void BandProfile::AccessAccomplishmentProgress() {}

int BandProfile::GetHardcoreIconLevel() const {}

void BandProfile::SetHardcoreIconLevel(int) {}

void BandProfile::GetTourBand() {}

// void BandProfile::GetBandName() const {}

void BandProfile::HasBandNameBeenSet() const {}
// void BandProfile::IsBandNameProfanityChecked() const {}

RndTex *BandProfile::GetBandLogoTex() {}

void BandProfile::SendBandLogo() {}

void BandProfile::GrantCampaignKey(Symbol) {}

bool BandProfile::HasCampaignKey(Symbol) {}

void BandProfile::UnlockModifier(Symbol) {}

bool BandProfile::HasUnlockedModifier(Symbol) {}
void BandProfile::HandlePerformanceDataUploadSuccess() {}
void BandProfile::UpdatePerformanceData(
    const Stats &, int, ScoreType, Difficulty, Symbol, int, int, bool
) {}

LocalBandUser *BandProfile::GetLocalBandUser() const {
    return TheBandUserMgr->GetUserFromPad(GetPadNum());
}

void BandProfile::GetAssociatedUsers(std::vector<LocalBandUser *> &) const {}
void BandProfile::CheckWebLinkStatus() {}
void BandProfile::CheckWebSetlistStatus() {}
// void BandProfile::HasSeenHint(Symbol) const {}
void BandProfile::SetHasSeenHint(Symbol) {}
// void BandProfile::GetLastCharUsed() const {}
void BandProfile::SetLastCharUsed(CharData *) {}
void BandProfile::SetLastPrefabCharUsed(Symbol) {}
void BandProfile::FakeProfileFill() {}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandProfile)
    HANDLE_EXPR(get_associated_user, GetAssociatedLocalBandUser())
    HANDLE_EXPR(is_lesson_complete, IsLessonComplete(_msg->Sym(2), _msg->Float(3)))
    HANDLE_ACTION(set_lesson_complete, SetLessonComplete(_msg->Sym(2), _msg->Float(3)))
    HANDLE_ACTION(unlock_modifier, UnlockModifier(_msg->Sym(2)))
    HANDLE_EXPR(has_unlocked_modifier, HasUnlockedModifier(_msg->Sym(2)))
    HANDLE_EXPR(get_accomplishment_progress, AccessAccomplishmentProgress())
    HANDLE_EXPR(get_hardcore_icon_level, GetHardcoreIconLevel())
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
