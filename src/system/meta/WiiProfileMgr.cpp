#include "meta/WiiProfileMgr.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "utl/Locale.h"

WiiProfileMgr TheWiiProfileMgr;
const int kWiiProfileNameBufferSize = 46;

int WiiProfileMgr::sSaveVersion = -1;
int WiiProfileMgr::sSaveVersionWii = -1;

WiiProfile::WiiProfile() : mSlot(-1), mId(0), mFlags(0), mHasSeenFirstTimeInstrumentFlags(0) {}

WiiProfile::~WiiProfile() {}

void WiiProfile::Clear(int Slot) {
    mSlot = Slot;
    mId = 0;
    mFlags = 0;
    mHasSeenFirstTimeInstrumentFlags = 0;

    const char *NewProfileName = MakeString("%s %i", Localize("Profile", NULL), Slot + 1);
    strncpy(mProfileName, NewProfileName, kWiiProfileNameBufferSize);
}

int WiiProfile::SaveSize() {
    REPORT_SIZE("WiiProfile", 59);
}

void WiiProfile::SaveToStream(BinStream &bs) const {
    bs << mSlot;
    bs << mId;
    bs << (mFlags & 7);
    bs << mHasSeenFirstTimeInstrumentFlags;
    bs.Write(mProfileName, kWiiProfileNameBufferSize);
}

void WiiProfile::LoadFromStream(BinStream &bs) {
    bs >> mSlot;
    bs >> mId;

    uint NewFlags;
    bs >> NewFlags;
    mFlags |= NewFlags & 7;

    bs >> mHasSeenFirstTimeInstrumentFlags;
    bs.Read(mProfileName, kWiiProfileNameBufferSize);
}

void WiiProfile::SetId(uint NewId) {
    mId = NewId;
    TheWiiProfileMgr.SetProfileDirty(mSlot);
}

const char *WiiProfile::GetName() const {
    return mProfileName;
}

void WiiProfile::SetName(const char *NewName) {
    int len = strlen(NewName);
    MILO_ASSERT(len <= kWiiProfileNameBufferSize, 121);

    strncpy(mProfileName, NewName, kWiiProfileNameBufferSize);
    TheWiiProfileMgr.SetProfileDirty(mSlot);
}

#pragma push
#pragma force_active on
inline bool WiiProfile::IsFlag(uint Flag) const {
    return mFlags & Flag;
}
#pragma pop

void WiiProfile::SetFlag(uint Flag, bool Value) {
    if (Value) {
        mFlags |= Flag;
    } else {
        mFlags &= ~Flag;
    }

    if ((Flag & 7) == 0) {
        return;
	}

    TheWiiProfileMgr.SetProfileDirty(mSlot);
}

BEGIN_HANDLERS(WiiProfile)
    HANDLE_CHECK(0x98)
END_HANDLERS

WiiProfileMgr::WiiProfileMgr() : mHasLoaded(0), mDirty(0) {
    mSaveSizeMethod = &SaveSize;
}

WiiProfileMgr::~WiiProfileMgr(){

}

void WiiProfileMgr::Init(int rev, int revWii){
    Clear(rev, revWii);
}

void WiiProfileMgr::Clear(int rev, int revWii){
    sSaveVersion = rev;
    sSaveVersionWii = revWii;
    for(int i = 0; i < 4; i++){
        mWiiProfiles[i].Clear(i);
    }
    for(int i = 0; i < 4; i++){
        mPadProfileIndex[i] = -1;
    }
}

int WiiProfileMgr::Count(unsigned int flags) const {
    int count = 0;
    for(int i = 0; i < 4; i++){
        if((flags | 1) == ((flags | 1) & (mWiiProfiles[i].mFlags))){
            count++;
        }
    }
    return count;
}

int WiiProfileMgr::SaveSize(int){
    int size = WiiProfile::SaveSize() * 4;
    REPORT_SIZE("WiiProfileMgr", size + 0x34);
}

bool WiiProfileMgr::NeedsSave() const { return mDirty; }
bool WiiProfileMgr::NeedsLoading() const { return !mHasLoaded && !mDirty; }
void WiiProfileMgr::SetProfileDirty(int Slot) { mDirty = true; }

void WiiProfileMgr::SaveFixed(FixedSizeSaveableStream& fs) const {
    fs << sSaveVersion;
    fs << sSaveVersionWii;
    fs << unk4c;
    for(int i = 0; i < 4; i++){
        mWiiProfiles[i].SaveToStream(fs);
    }
    for(int i = 0; i < 10; i++){
        fs << mDeleteQueue[i];
    }
}

void WiiProfileMgr::PostSave(){ mDirty = false; }
void WiiProfileMgr::PreLoad(){}

void WiiProfileMgr::LoadFixed(FixedSizeSaveableStream& fs, int){
    int rev, revWii;
    fs >> rev;
    fs >> revWii;
    if(rev != sSaveVersion || revWii != sSaveVersionWii){
        MILO_WARN("**WiiProfileMgr::Tried to load a bad or out-of-date version (%d | %d) vs (%d | %d)!\n",
            rev, revWii, sSaveVersion, sSaveVersionWii);
        Clear(sSaveVersion, sSaveVersionWii);
        fs.Seek(SaveSize(revWii) - 8, BinStream::kSeekCur);
    }
    else {
        fs >> unk4c;
        for(int i = 0; i < 4; i++){
            mWiiProfiles[i].LoadFromStream(fs);
        }
        for(int i = 0; i < 10; i++){
            fs >> mDeleteQueue[i];
        }
    }
    mHasLoaded = true;
    mDirty = false;
}

bool WiiProfileMgr::IsPadAGuest(int padNum) const {
    MILO_ASSERT(padNum < kNumWiiPads, 0x140);
    return mPadProfileIndex[padNum] == -2;
}

void WiiProfileMgr::CreateProfile(int iii){
    SetIndexValid(iii, true);
    SetIndexSaved(iii, false);
}

bool WiiProfileMgr::DeleteProfile(int iii){
    if(iii <= 3U && IsIndexValid(iii)){
        if(IsIndexRegistered(iii)){
            if(!AddIdToDeleteQueue(GetIdForIndex(iii))) return false;
        }
        SetIndexValid(iii, false);
        mWiiProfiles[iii].Clear(iii);
        mDirty = true;
    }
    return true;
}

void WiiProfileMgr::RegisterProfile(int pad, unsigned int id){
    if(pad <= 3U){
        mWiiProfiles[pad].mId = id;
        SetIndexRegistered(pad, true);
    }
}

int WiiProfileMgr::GetNextEmptyIndex() const {
    for(int i = 0; i < 4; i++){
        if(!mWiiProfiles[i].IsFlag(1)) return i;
    }
    return -1;
}

int WiiProfileMgr::GetIndexForUser(const LocalUser* user) const {
    if(user && user->IsLocal()){
        return GetIndexForPad(user->GetPadNum());
    }
    else return -1;
}

int WiiProfileMgr::GetIndexForPad(int pad) const {
    if(pad <= 3U && mPadProfileIndex[pad] >= 0) return mPadProfileIndex[pad];
    else return -1;
}

int WiiProfileMgr::GetPadForIndex(int idx) const {
    for(int i = 0; i < 4; i++){
        if(idx == mPadProfileIndex[i]) return i;
    }
    return -1;
}

void WiiProfileMgr::SetPadToIndex(int padNum, int idx){
    MILO_ASSERT(padNum < kNumWiiPads, 0x1CE);
    if(idx == -2 || idx <= 3U){
        if(mPadProfileIndex[padNum] >= 0){
            mWiiProfiles[mPadProfileIndex[padNum]].SetFlag(0x4000U, false);
        }
        mPadProfileIndex[padNum] = idx;
        if(idx >= 0){
            mWiiProfiles[idx].SetFlag(0x8000, true);
        }
        ThePlatformMgr.SetUserSignedIn(padNum);
    }
}

void WiiProfileMgr::SetPadToGuest(int padNum){
    MILO_ASSERT(padNum < kNumWiiPads, 0x1EC);
    if(mPadProfileIndex[padNum] >= 0){
        mWiiProfiles[mPadProfileIndex[padNum]].SetFlag(0x4000U, false);
    }
    mPadProfileIndex[padNum] = -2;
    ThePlatformMgr.SetUserSignedIn(padNum);
}

void WiiProfileMgr::RemovePad(int padNum){
    MILO_ASSERT(padNum < kNumWiiPads, 0x1FB);
    if(mPadProfileIndex[padNum] >= 0){
        mWiiProfiles[mPadProfileIndex[padNum]].SetFlag(0x4000U, false);
    }
    ThePlatformMgr.SetUserSignedOut(padNum);
    mPadProfileIndex[padNum] = -1;
}

WiiProfile* WiiProfileMgr::GetProfileForIndex(int idx){
    if(idx <= 3U) return &mWiiProfiles[idx];
    else return nullptr;
}

#pragma push
#pragma force_active on
inline WiiProfile* WiiProfileMgr::GetProfileForPad(int pad){
    return GetProfileForIndex(GetIndexForPad(pad));
}
#pragma pop

int WiiProfileMgr::GetIdForIndex(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].mId;
    else return 0;
}

const char* WiiProfileMgr::GetNameForIndex(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].mProfileName;
    else return nullptr;
}

void WiiProfileMgr::SetIndexName(int idx, const char* name){
    if(idx <= 3U){
        mWiiProfiles[idx].SetName(name);
        mDirty = true;
    }
}

int WiiProfileMgr::GetIndexForName(const char* name, int idx) const {
    for(int i = 0; i < 4; i++){
        if(i != idx){
            const WiiProfile* curProfile = &mWiiProfiles[i];
            if(curProfile->IsFlag(1) && stricmp(curProfile->mProfileName, name) == 0){
                return i;
            }
        }
    }
    return -1;
}

const char* WiiProfileMgr::GetNameForPad(int pad) const {
    return GetNameForIndex(GetIndexForPad(pad));
}

bool WiiProfileMgr::IsSlotAvailable() const {
    for(int i = 0; i < 4; i++){
        if(!mWiiProfiles[i].IsFlag(1)) return true;
    }
    return false;
}

bool WiiProfileMgr::IsIndexValid(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].IsFlag(1);
    else return false;
}

void WiiProfileMgr::SetIndexValid(int idx, bool valid){
    if(idx <= 3U){
        mWiiProfiles[idx].SetFlag(1, valid);
        mDirty = true;
    }
}

bool WiiProfileMgr::IsIndexSaved(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].IsFlag(4);
    else return false;
}

void WiiProfileMgr::SetIndexSaved(int idx, bool saved){
    if(idx <= 3U){
        mWiiProfiles[idx].SetFlag(4, saved);
        mDirty = true;
    }
}

bool WiiProfileMgr::IsIndexRegistered(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].IsFlag(2);
    else return false;
}

bool WiiProfileMgr::IsPadRegistered(int pad) const {
    return IsIndexRegistered(GetIndexForPad(pad));
}

void WiiProfileMgr::SetIndexRegistered(int idx, bool regged){
    if(idx <= 3U){
        mWiiProfiles[idx].SetFlag(2, regged);
        mDirty = true;
    }
}

bool WiiProfileMgr::IsIndexLoaded(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].IsFlag(0x4000);
    else return false;
}

void WiiProfileMgr::SetIndexLoaded(int idx, bool loaded){
    if(idx <= 3U) mWiiProfiles[idx].SetFlag(0x4000, loaded);
}

bool WiiProfileMgr::IsIndexSwapping(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].IsFlag(0x2000);
    else return false;
}

bool WiiProfileMgr::IsIndexLocked(int idx) const {
    if(idx <= 3U) return mWiiProfiles[idx].IsFlag(0x8000);
    else return false;
}

void WiiProfileMgr::SetIndexLocked(int idx, bool locked){
    if(idx <= 3U) mWiiProfiles[idx].SetFlag(0x8000, locked);
}

void WiiProfileMgr::SetLocked(Profile* p, bool locked){
    if(p){
        WiiProfile* pwii = GetProfileForPad(p->GetPadNum());
        if(pwii) pwii->SetFlag(0x8000, locked);
    }
}

void WiiProfileMgr::DoSignin(LocalUser* u, int idx, int pad, int){
    SetPadToIndex(pad, idx);
    u->UpdateOnlineID();
}

bool WiiProfileMgr::AddIdToDeleteQueue(unsigned int id){

}

bool WiiProfileMgr::IsDeleteQueueFull() const {
    for(int i = 0; i < 10; i++){
        if(mDeleteQueue[i] == 0) return false;
    }
    return true;
}

int WiiProfileMgr::GetHasSeenFirstTimeInstrumentFlagsForUser(const LocalUser* user) const {
    int idx = GetIndexForUser(user);
    if(idx >= 0) return mWiiProfiles[idx].mHasSeenFirstTimeInstrumentFlags;
    else return 0;
}

void WiiProfileMgr::SetHasSeenFirstTimeInstrumentFlagsForUser(const LocalUser* user, int flags, bool on){
    int idx = GetIndexForUser(user);
    if(idx >= 0){
        if(on) mWiiProfiles[idx].mHasSeenFirstTimeInstrumentFlags |= flags;
        else mWiiProfiles[idx].mHasSeenFirstTimeInstrumentFlags &= ~flags;
    }
}