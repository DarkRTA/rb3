#include "net_band/RockCentralJobs.h"
#include "meta_band/ProfileMgr.h"
#include "net/WiiFriendMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "utl/Std.h"

void RockCentralJob::Cancel(Hmx::Object *) {
    MILO_FAIL("No support for cancelling a Rock Central Job");
}

UpdateFriendsListJob::UpdateFriendsListJob(int i) : unk24(i), mState(0) {}

UpdateFriendsListJob::~UpdateFriendsListJob() { DeleteAll(mFriends); }

void UpdateFriendsListJob::Start() {
    mState = 1;
    ThePlatformMgr.EnumerateFriends(unk24, mFriends, this);
}

DataNode UpdateFriendsListJob::OnMsg(const PlatformMgrOpCompleteMsg &msg) {
    MILO_ASSERT(mState == kEnumeratingFriends, 0x36);
}

DataNode UpdateFriendsListJob::OnMsg(const RockCentralOpCompleteMsg &msg) {
    MILO_ASSERT(mState == kUpdatingFriends, 0x54);
    if (msg.Success()) {
        BandProfile *profile = TheProfileMgr.GetProfileFromPad(unk24);
        if (profile->HasValidSaveData()) {
            profile->SetUploadFriendsToken(unk28);
        }
    }
    mState = 3;
    return 1;
}

bool UpdateFriendsListJob::IsFinished() { return mState == 3; }

BEGIN_HANDLERS(UpdateFriendsListJob)
    HANDLE_MESSAGE(PlatformMgrOpCompleteMsg)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_CHECK(0x7F)
END_HANDLERS

UpdateMasterProfileFriendsListJob::UpdateMasterProfileFriendsListJob() : mState(0) {}

UpdateMasterProfileFriendsListJob::~UpdateMasterProfileFriendsListJob() {}

void UpdateMasterProfileFriendsListJob::Start() {
    mState = 1;
    TheWiiFriendMgr.EnumerateFriends(&unk28, this);
}

bool UpdateMasterProfileFriendsListJob::IsFinished() { return mState == 3; }

BEGIN_HANDLERS(UpdateMasterProfileFriendsListJob)
    HANDLE_MESSAGE(WiiFriendMgrOpCompleteMsg)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_CHECK(0xED)
END_HANDLERS