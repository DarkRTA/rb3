#include "BandProfile.h"
#include "BandMachineMgr.h"
#include "ProfileMgr.h"
#include "AccomplishmentManager.h"
#include "SavedSetlist.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/GameMode.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/BandProfile.h"
#include "meta_band/Campaign.h"
#include "meta_band/CharData.h"
#include "meta_band/GameplayOptions.h"
#include "meta_band/LessonMgr.h"
#include "meta_band/MetaPanel.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/PerformanceData.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/BandSongMgr.h"
#include "game/BandUserMgr.h"
#include "bandobj/PatchDir.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentral.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/ObjMacros.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/OSFuncs.h"
#include "os/PlatformMgr.h"
#include "os/ProfilePicture.h"
#include "os/User.h"
#include "rndobj/Tex.h"
#include "tour/TourChar.h"
#include "tour/TourCharLocal.h"
#include "tour/TourProgress.h"
#include "tour/TourBand.h"
#include "system/utl/Symbols.h"
#include "utl/Locale.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"

BandProfile::BandProfile(int i)
    : Profile(i), unk18(0), mAccomplishmentProgress(this), unk740(0),
      mAccomplishmentDataUploadContextID(-1), unk74c(-1), unk750(-1),
      mPerformanceDataUploadContextID(-1), unk6f70(0), unk6f74(0), mProfileAssets(this),
      unk6fb4(0), unk6fb8(0) {
    mSaveSizeMethod = &SaveSize;
    LocalBandUser *user = GetAssociatedLocalBandUser();
    mScores = new SongStatusMgr(user, &TheSongMgr);
    mProfilePicture = new ProfilePicture(GetPadNum(), this);
    for (int n = 0; n < 8; n++)
        mPatches.push_back(new PatchDir());
    for (int n = 0; n < 4; n++)
        mStandIns.push_back(StandIn());
    mTourProgress = new TourProgress();
    mTourBand = new TourBand(this);
}

BandProfile::~BandProfile() {
    DeleteAll();
    RELEASE(mScores);
    RELEASE(mProfilePicture);
    RELEASE(mTourBand);
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

FORCE_LOCAL_INLINE
int BandProfile::NumChars() const { return mCharacters.size(); }
END_FORCE_LOCAL_INLINE

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

LocalSavedSetlist *BandProfile::AddSavedSetlist(
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
    SaveStdPtr(fsss, mSavedSetlists, kMaxSavedSetlists, LocalSavedSetlist::SaveSize(151));
    SaveStd(fsss, mLessonCompletions, 1000, 8);
    SaveStd(fsss, mCampaignKeys, 20);
    SaveStd(fsss, unk88, 20);
    SaveStd(fsss, mUnlockedModifiers, 15);
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
    fsss << *mTourBand;
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
    REPORT_SIZE("BandProfile", x);
}

void BandProfile::PreLoad() {
    if (!MainThread()) {
        MILO_WARN("BandProfile::PreLoad is unsafe to call in the main thread!\n");
    }
    DeleteAll();
}

void BandProfile::LoadFixed(FixedSizeSaveableStream &fs, int rev) {
    fs >> *mTourProgress;
    LoadStdPtr(fs, mCharacters, kMaxCharacters, TourChar::SaveSize(rev));
    MILO_ASSERT(mPatches.size() == kMaxPatchesPerProfile, 0x2BD);
    LoadStdPtrReplace(fs, mPatches, kMaxPatchesPerProfile, PatchDir::SaveSize(rev));
    if (rev >= 150)
        fs.EnableReadEncryption();
    fs >> *mScores;
    if (rev >= 150)
        fs.DisableEncryption();
    LoadStdPtr(fs, mSavedSetlists, kMaxSavedSetlists, LocalSavedSetlist::SaveSize(rev));
    FOREACH (it, mSavedSetlists) {
        (*it)->SetOwnerProfile(this);
    }
    LoadStd(fs, mLessonCompletions, 1000, 8);
    LoadStd(fs, mCampaignKeys, 20);
    LoadStd(fs, unk88, 20);
    LoadStd(fs, mUnlockedModifiers, 15);
    fs >> mAccomplishmentProgress;
    if (rev < 149) {
        std::list<PerformanceData *> datas;
        LoadStdPtr(fs, datas, 50, PerformanceData::SaveSize(rev));
    } else {
        for (int i = 0; i < 50; i++) {
            fs >> mPerformanceDataList[i];
        }
        fs >> unk6f70;
        fs >> unk6f74;
    }
    fs >> mProfileAssets;
    fs >> unk6fb8;
    fs >> unk6fb4;
    fs >> mGameplayOptions;
    fs >> *mTourBand;
    if (ThePlatformMgr.IsSignedIn(GetPadNum())) {
        mProfilePicture->Update();
    }
    for (int i = 0; i < mStandIns.size(); i++) {
        fs >> mStandIns[i];
    }
    if (rev >= 134)
        fs >> unk5c;

    BandMachineMgr *pMachineMgr = TheSessionMgr->GetMachineMgr();
    MILO_ASSERT(pMachineMgr, 0x303);
    pMachineMgr->RefreshPrimaryProfileInfo();
    mScores->SetLocalUser(GetAssociatedLocalBandUser());
    mDirty = false;
    if (unk18)
        FakeProfileFill();
}

bool BandProfile::IsUnsaved() const {
    if (Profile::IsUnsaved())
        return true;
    if (mGameplayOptions.mDirty)
        return true;
    if (mTourProgress->IsDirtySave())
        return true;
    if (mTourBand->IsDirtySave())
        return true;

    for (int i = 0; i < mPatches.size(); i++) {
        if (mPatches[i]->unk1c0)
            return true;
    }
    return false;
}

void BandProfile::SaveLoadComplete(ProfileSaveState state) {
    Profile::SaveLoadComplete(state);
    mTourProgress->SaveLoadComplete(state);
    mTourBand->SaveLoadComplete(state);
    static ProfileChangedMsg msg(this);
    msg[0] = this;
    TheProfileMgr.Handle(msg, false);
}

bool BandProfile::HasSomethingToUpload() {
    if (!ThePlatformMgr.IsSignedIntoLive(GetPadNum()))
        return false;
    else {
        FOREACH (it, mSavedSetlists) {
            if ((*it)->mNeedsUpload)
                return true;
        }
        FOREACH (it, mCharacters) {
            TourCharLocal *pTourCharLocal = *it;
            MILO_ASSERT(pTourCharLocal, 0x351);
            if (pTourCharLocal->IsDirtyUpload())
                return true;
        }
        return mTourBand->IsDirtyUpload();
    }
}

void BandProfile::DeleteAll() {
    FOREACH (it, mCharacters) {
        RELEASE(*it);
    }
    mCharacters.clear();
    FOREACH (it, mPatches) {
        (*it)->Clear();
    }
    mAccomplishmentProgress.Clear();
    mProfileAssets.Clear();
    mLessonCompletions.clear();
    if (mScores)
        mScores->Clear();
    mScores->SetLocalUser(GetAssociatedLocalBandUser());
    FOREACH (it, mSavedSetlists) {
        delete *it;
    }
    mSavedSetlists.clear();
    mAccomplishmentDataUploadContextID = -1;
    mPerformanceDataUploadContextID = -1;
    unk74c = -1;
    unk750 = -1;
    unk6fb8 = 0;
    unk740 = 0;
    unk6f70 = 0;
    unk6f74 = 0;
    mProfilePicture->mState = ProfilePicture::kIdle;
    mTourBand->SetBandName("");
    if (mTourBand->GetLogo()) {
        mTourBand->GetLogo()->patchIndex = 0;
        mTourBand->GetLogo()->patchType = 0;
    }
    for (int i = 0; i < mStandIns.size(); i++) {
        mStandIns[i].SetNone();
    }
    mTourProgress->ResetTourData();
    mCampaignKeys.clear();
    unk88.clear();
    unk5c.Clear();
    unk6c = gNullStr;
    mDirty = true;
}

LocalBandUser *BandProfile::GetAssociatedLocalBandUser() const {
    return TheBandUserMgr->GetUserFromPad(GetPadNum());
}

void BandProfile::CheckForFinishedTrainerAccomplishments() {
    if (HasValidSaveData()) {
        LocalBandUser *pLocalUser = GetAssociatedLocalBandUser();
        MILO_ASSERT(pLocalUser, 0x3be);
        TheAccomplishmentMgr->CheckForFinishedTrainerAccomplishmentsForUser(pLocalUser);
    }
}

void BandProfile::SetProGuitarSongLessonComplete(int i, Difficulty d) {
    mScores->SetProGuitarSongLessonComplete(i, d);
    CheckForFinishedTrainerAccomplishments();
    mDirty = true;
}

void BandProfile::SetProBassSongLessonComplete(int i, Difficulty d) {
    mScores->SetProBassSongLessonComplete(i, d);
    CheckForFinishedTrainerAccomplishments();
    mDirty = true;
}

void BandProfile::SetProKeyboardSongLessonComplete(int i, Difficulty d) {
    mScores->SetProKeyboardSongLessonComplete(i, d);
    CheckForFinishedTrainerAccomplishments();
    mDirty = true;
}

void BandProfile::SetProGuitarSongLessonSectionComplete(int i1, Difficulty d, int i2) {
    mScores->SetProGuitarSongLessonSectionComplete(i1, d, i2);
    mDirty = true;
}

void BandProfile::SetProBassSongLessonSectionComplete(int i1, Difficulty d, int i2) {
    mScores->SetProBassSongLessonSectionComplete(i1, d, i2);
    mDirty = true;
}

void BandProfile::SetProKeyboardSongLessonSectionComplete(int i1, Difficulty d, int i2) {
    mScores->SetProKeyboardSongLessonSectionComplete(i1, d, i2);
    mDirty = true;
}

bool BandProfile::IsProGuitarSongLessonSectionComplete(int i1, Difficulty d, int i2)
    const {
    return mScores->IsProGuitarSongLessonSectionComplete(i1, d, i2);
}

bool BandProfile::IsProBassSongLessonSectionComplete(int i1, Difficulty d, int i2) const {
    return mScores->IsProBassSongLessonSectionComplete(i1, d, i2);
}

bool BandProfile::IsProKeyboardSongLessonSectionComplete(int i1, Difficulty d, int i2)
    const {
    return mScores->IsProKeyboardSongLessonSectionComplete(i1, d, i2);
}

bool BandProfile::IsLessonComplete(const Symbol &symbol, float speed) const {
    return GetLessonCompleteSpeed(symbol) >= speed;
}

float BandProfile::GetLessonCompleteSpeed(const Symbol &sym) const {
    float ret = 0;
    std::map<Symbol, float>::const_iterator it = mLessonCompletions.find(sym);
    if (it != mLessonCompletions.end())
        ret = it->second;
    return ret;
}

void BandProfile::SetLessonComplete(const Symbol &s, float f2) {
    std::map<Symbol, float>::iterator it = mLessonCompletions.find(s);
    if (it == mLessonCompletions.end() || it->second < f2) {
        mLessonCompletions[s] = f2;
        CheckForFinishedTrainerAccomplishments();
        mDirty = true;
    }
}

void BandProfile::EarnAccomplishment(Symbol s) {
    if (mAccomplishmentProgress.AddAccomplishment(s)) {
        if (TheGameMode->InMode("campaign")) {
            LocalBandUser *pUser = GetAssociatedLocalBandUser();
            MILO_ASSERT(pUser, 0x42D);
            if (TheCampaign->GetUser() == pUser && TheCampaign->GetCurrentGoal() == s) {
                TheCampaign->HandleLaunchedGoalComplete();
            }
        }
        mDirty = true;
    }
}

const AccomplishmentProgress &BandProfile::GetAccomplishmentProgress() const {
    return mAccomplishmentProgress;
}

AccomplishmentProgress &BandProfile::AccessAccomplishmentProgress() {
    return mAccomplishmentProgress;
}

int BandProfile::GetHardcoreIconLevel() const { return unk6fb8; }

void BandProfile::SetHardcoreIconLevel(int level) {
    unk6fb8 = level;
    mDirty = true;
}

TourBand *BandProfile::GetTourBand() { return mTourBand; }

String BandProfile::GetBandName() const {
    if (strlen(mTourBand->GetName()) == 0) {
        String strName = GetName();
        return MakeString(Localize(band_default_name, nullptr), strName.c_str());
    } else
        return mTourBand->GetName();
}

bool BandProfile::HasBandNameBeenSet() const { return strlen(mTourBand->GetName()); }

bool BandProfile::IsBandNameProfanityChecked() const {
    return !mTourBand->IsNameUnchecked();
}

RndTex *BandProfile::GetBandLogoTex() {
    if (!mTourBand->GetLogo())
        return nullptr;
    else {
        RndTex *ret = nullptr;
        if (mTourBand->GetLogo()->patchType == 1) {
            ret = GetTexAtPatchIndex(mTourBand->GetLogo()->patchIndex);
        }
        return ret;
    }
}

void BandProfile::SendBandLogo() {
    if (mTourBand->IsDirtyUpload()) {
        TheRockCentral.UpdateBandLogo(
            mTourBand->GetBandID(), nullptr, mTourBand->unk30, this, -1
        );
    }
}

void BandProfile::GrantCampaignKey(Symbol key) {
    MILO_ASSERT(mCampaignKeys.size() < kMaxSymbols_CampaignKeys, 0x48F);
    if (!TheCampaign->HasCampaignKey(key)) {
        MILO_WARN("Trying to grant unknown key: %s", key.mStr);
    } else if (mCampaignKeys.insert(key).second) {
        mDirty = true;
    }
}

bool BandProfile::HasCampaignKey(Symbol key) {
    if (MetaPanel::sUnlockAll)
        return true;
    else
        return mCampaignKeys.find(key) != mCampaignKeys.end();
}

void BandProfile::UnlockModifier(Symbol mod) {
    MILO_ASSERT(mUnlockedModifiers.size() < kMaxSymbols_Modifiers, 0x4AF);
    if (!TheModifierMgr->HasModifier(mod)) {
        MILO_WARN("Trying to unlock unknown modifier: %s", mod.mStr);
    } else if (mUnlockedModifiers.insert(mod).second) {
        mDirty = true;
    }
}

bool BandProfile::HasUnlockedModifier(Symbol mod) {
    return mUnlockedModifiers.find(mod) != mUnlockedModifiers.end();
}

void BandProfile::HandlePerformanceDataUploadSuccess() {
    mPerformanceDataList[unk6f70].m0x28 = 0; // unk6f70 = mPerformanceDataUploadContextID
    unk6f70 = (unk6f70 + 1) % kMaxPerformances;
}

void BandProfile::UpdatePerformanceData(
    const Stats &stats,
    int i2,
    ScoreType ty,
    Difficulty diff,
    Symbol s,
    int i6,
    int i7,
    bool b8
) {
    MILO_ASSERT(( 0) <= ( GetNumDirtyPerformanceData()) && ( GetNumDirtyPerformanceData()) < ( kMaxPerformances), 0x4D7);
    mPerformanceDataList[unk6f74].Initialize(stats, i2, ty, diff, s, i6, i7, b8);
    unk6f74 = (unk6f74 + 1) % kMaxPerformances;
    if (unk6f74 == unk6f70) {
        mPerformanceDataList[unk6f70].m0x28 = 0;
        mPerformanceDataUploadContextID = -1;
        unk6f70 = (unk6f70 + 1) % kMaxPerformances;
    }
    mDirty = true;
}

DataNode BandProfile::OnMsg(const RockCentralOpCompleteMsg &msg) {
    bool b2 = msg.Success();
    int arg2 = msg.Arg2().Int();
    if (arg2 == mPerformanceDataUploadContextID) {
        mPerformanceDataUploadContextID = -1;
        if (b2) {
            HandlePerformanceDataUploadSuccess();
            UploadDirtyPerformanceData();
        }
    } else if (arg2 == mAccomplishmentDataUploadContextID) {
        mAccomplishmentProgress.mUploadDirty = !b2;
        mAccomplishmentDataUploadContextID = -1;
        if (b2) {
            mAccomplishmentProgress.HandleSuccessfulUpload();
        }
    } else if (arg2 == unk74c) {
        unk74c = -1;
        if (b2) {
            unk754.Update(nullptr);
            for (int i = 0; i < unk754.NumDataResults(); i++) {
                DataResult *res = unk754.GetDataResult(i);
                DataNode node;
                res->GetDataResultValue("linked", node);
                if (node.Int()) {
                    LocalBandUser *localUser = GetAssociatedLocalBandUser();
                    MILO_ASSERT(localUser, 0x518);
                    TheAccomplishmentMgr->EarnAccomplishment(localUser, acc_accountlink);
                }
            }
        }
    } else if (arg2 == unk750) {
        unk750 = -1;
        if (b2) {
            unk76c.Update(nullptr);
            if (unk76c.NumDataResults() > 0) {
                DataResult *res = unk76c.GetDataResult(0);
                DataNode node;
                res->GetDataResultValue("creator", node);
                if (node.Int()) {
                    LocalBandUser *localUser = GetAssociatedLocalBandUser();
                    MILO_ASSERT(localUser, 0x530);
                    TheAccomplishmentMgr->EarnAccomplishment(localUser, acc_createsetlist);
                }
            } else
                MILO_WARN("Empty result returned from Rock Central web setlist check\n");
        }
    }
    return 1;
}

LocalBandUser *BandProfile::GetLocalBandUser() const {
    return TheBandUserMgr->GetUserFromPad(GetPadNum());
}

void BandProfile::GetAssociatedUsers(std::vector<LocalBandUser *> &users) const {
    users.clear();
    LocalBandUser *user = TheBandUserMgr->GetUserFromPad(GetPadNum());
    MILO_ASSERT(user, 0x54E);
    if (user->CanSaveData()) {
        users.push_back(user);
    }
}

void BandProfile::CheckWebLinkStatus() {
    if (unk74c == -1) {
        unk74c = unk740;
        unk740++;
        unk754.Clear();
        TheRockCentral.GetWebLinkStatus(this, unk74c, unk754, this);
    }
}

void BandProfile::CheckWebSetlistStatus() {
    if (unk750 == -1) {
        unk750 = unk740;
        unk740++;
        unk76c.Clear();
        TheRockCentral.GetSetlistCreationStatus(this, unk750, unk76c, this);
    }
}

bool BandProfile::HasSeenHint(Symbol s) const { return unk88.find(s) != unk88.end(); }

void BandProfile::SetHasSeenHint(Symbol s) {
    unk88.insert(s);
    mDirty = true;
}

CharData *BandProfile::GetLastCharUsed() const {
    const StandIn &standin = GetStandIn(0);
    HxGuid theGuid = unk5c;
    if (theGuid.IsNull()) {
        if (unk6c.Null()) {
            theGuid = standin.mGuid;
        } else
            return PrefabMgr::GetPrefabMgr()->GetPrefab(unk6c);
    }
    for (int i = 0; i < mCharacters.size(); i++) {
        TourCharLocal *pCharacter = mCharacters[i];
        MILO_ASSERT(pCharacter, 0x58F);
        if (pCharacter->mGuid == theGuid)
            return pCharacter;
    }
    return standin.IsPrefabCharacter()
        ? PrefabMgr::GetPrefabMgr()->GetPrefab(standin.mName)
        : nullptr;
}

void BandProfile::SetLastCharUsed(CharData *cd) {
    if (cd) {
        unk5c = cd->mGuid;
    } else
        unk5c.Clear();
    mDirty = true;
}

void BandProfile::SetLastPrefabCharUsed(Symbol s) { unk6c = s; }

void BandProfile::FakeProfileFill() {
    std::vector<LocalBandUser *> lUsers;
    GetAssociatedUsers(lUsers);
    MILO_ASSERT(!lUsers.empty(), 0x5B6);
    LocalBandUser *pLocalUser = lUsers.front();
    MILO_ASSERT(pLocalUser, 0x5B8);
    MILO_ASSERT(mPatches.size() == kMaxPatchesPerProfile, 0x5BB);
    RndTex *tex;
    FOREACH (it, mPatches) {
        PatchDir *pPatchDir = *it;
        MILO_ASSERT(pPatchDir, 0x5C4);
        tex = pPatchDir->GetTex();
        if (tex && tex->Width() != 0 && tex->Height() != 0)
            break;
        else
            tex = nullptr;
    }
    if (!tex) {
        MILO_WARN(
            "This cheat will not completely fill the profile; finalize one patch in the art maker and try again."
        );
    }
    FOREACH (it, mPatches) {
        PatchDir *pPatchDir = *it;
        MILO_ASSERT(pPatchDir, 0x5D7);
        pPatchDir->FakeFill(tex);
    }

    for (int i = mCharacters.size(); i < 10; i++) {
        TourCharLocal *tcl = new TourCharLocal();
        tcl->GenerateGUID();
        tcl->SetCharacterName(MakeString("fake_char_%i", i));
        tcl->SetFinalized(true);
        tcl->GetPortraitTex()->SetBitmap(0x80, 0x100, 0x20, RndTex::kRendered, false, 0);
        tcl->GetPortraitTex()->Compress(false);
        mCharacters.push_back(tcl);
    }
    MILO_ASSERT(mTourProgress, 0x5EE);
    mTourProgress->FakeFill();
    LessonMgr *pLessonMgr = LessonMgr::GetLessonMgr();
    MILO_ASSERT(pLessonMgr, 0x5F3);
    const std::map<Symbol, Lesson *> &lessons = pLessonMgr->LessonsMap();
    FOREACH (it, lessons) {
        Symbol key = it->first;
        mLessonCompletions[key] = 1.0f;
    }
    MILO_ASSERT(mScores, 0x600);
    mScores->FakeFill();
    FOREACH (it, mSavedSetlists) {
        delete *it;
    }
    mSavedSetlists.clear();

    std::vector<int> ivec;
    for (int i = 0; i < 100; i++) {
        ivec.push_back(i);
    }

    for (int i = 0; i < 20; i++) {
        PatchDescriptor desc;
        AddSavedSetlist(
            MakeString("fake_setlist_%i", i),
            MakeString("fake_setlist_desc_%i", i),
            false,
            desc,
            ivec
        );
    }
    const std::map<Symbol, CampaignKey *> &keys = TheCampaign->CampaignKeys();
    FOREACH (it, keys) {
        Symbol key = it->first;
        mCampaignKeys.insert(key);
    }
    for (int i = mUnlockedModifiers.size(); i < 15; i++) {
        mUnlockedModifiers.insert(MakeString("fake_modifier_%i", i));
    }
    mAccomplishmentProgress.FakeFill();
    mProfileAssets.FakeFill();
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandProfile)
    HANDLE_EXPR(get_associated_user, GetAssociatedLocalBandUser())
    HANDLE_EXPR(is_lesson_complete, IsLessonComplete(_msg->Sym(2), _msg->Float(3)))
    HANDLE_ACTION(set_lesson_complete, SetLessonComplete(_msg->Sym(2), _msg->Float(3)))
    HANDLE_ACTION(unlock_modifier, UnlockModifier(_msg->Sym(2)))
    HANDLE_EXPR(has_unlocked_modifier, HasUnlockedModifier(_msg->Sym(2)))
    HANDLE_EXPR(get_accomplishment_progress, &AccessAccomplishmentProgress())
    HANDLE_EXPR(get_hardcore_icon_level, GetHardcoreIconLevel())
    HANDLE_ACTION(set_hardcore_icon_level, SetHardcoreIconLevel(_msg->Int(2)))
    HANDLE_ACTION(set_song_review, SetSongReview(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(setlist_changed, SetlistChanged(_msg->Obj<LocalSavedSetlist>(2)))
    HANDLE_EXPR(max_chars, GetMaxChars())
    HANDLE_EXPR(get_picture_tex, GetPictureTex())
    HANDLE_EXPR(get_band_logo_tex, GetBandLogoTex())
    HANDLE_EXPR(get_first_empty_patch, GetFirstEmptyPatch())
    HANDLE_EXPR(get_band_name, GetBandName())
    HANDLE_ACTION(set_band_name, mTourBand->SetBandName(_msg->Str(2)))
    HANDLE_EXPR(has_band_name_been_set, HasBandNameBeenSet())
    HANDLE_EXPR(get_num_chars, NumChars())
    HANDLE_EXPR(has_seen_hint, HasSeenHint(_msg->Sym(2)))
    HANDLE_ACTION(set_has_seen_hint, SetHasSeenHint(_msg->Sym(2)))
    HANDLE_EXPR(access_accomplishment_progress, &AccessAccomplishmentProgress())
    HANDLE_ACTION(auto_fake_fill, AutoFakeFill(_msg->Int(2)))
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_MEMBER_PTR((&mGameplayOptions))
    HANDLE_MEMBER_PTR(mScores)
    HANDLE_SUPERCLASS(Profile)
    HANDLE_CHECK(0x67a)
END_HANDLERS
#pragma pop

RndTex *BandProfile::GetPictureTex() { return mProfilePicture->mUserPicture; }
void BandProfile::AutoFakeFill(int n) { unk18 = n; }
