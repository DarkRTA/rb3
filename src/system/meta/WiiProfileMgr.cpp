#include "meta/WiiProfileMgr.h"
#include "utl/Locale.h"

WiiProfileMgr TheWiiProfileMgr;
const int kWiiProfileNameBufferSize = 46;

int WiiProfileMgr::sSaveVersion = -1;
int WiiProfileMgr::sSaveVersionWii = -1;

WiiProfile::WiiProfile() : mSlot(-1), mId(0), mFlags(0), unk_0x28(0) {}

WiiProfile::~WiiProfile() {}

void WiiProfile::Clear(int Slot) {
    mSlot = Slot;
    mId = 0;
    mFlags = 0;
    unk_0x28 = 0;

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
    bs << unk_0x28;
    bs.Write(mProfileName, kWiiProfileNameBufferSize);
}

void WiiProfile::LoadFromStream(BinStream &bs) {
    bs >> mSlot;
    bs >> mId;

    uint NewFlags;
    bs >> NewFlags;
    mFlags |= NewFlags & 7;

    bs >> unk_0x28;
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

bool WiiProfile::IsFlag(uint Flag) const {
    return mFlags & Flag;
}

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

WiiProfileMgr::WiiProfileMgr() : unk1d0(0), mDirty(0) {
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
        unk1c0[i] = -1;
    }
}

void WiiProfileMgr::SetProfileDirty(int Slot) { mDirty = true; }
