#include "meta/WiiProfileMgr.h"
#include "utl/Locale.h"

WiiProfileMgr TheWiiProfileMgr;
const int kWiiProfileNameBufferSize = 46;

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
    if (FixedSizeSaveable::sPrintoutsEnabled) {
        MILO_LOG("* %s = %i\n", "WiiProfile", 59);
    }

    return 0x3b;
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

WiiProfileMgr::WiiProfileMgr() {}
WiiProfileMgr::~WiiProfileMgr() {}
void WiiProfileMgr::SetProfileDirty(int Slot) {}
