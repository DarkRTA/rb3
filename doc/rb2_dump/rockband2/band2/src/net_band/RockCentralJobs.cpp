/*
    Compile unit: C:\rockband2\band2\src\net_band\RockCentralJobs.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8022C108 -> 0x8022CCB0
*/
class RockCentralJob : public Job {
    // total size: 0x8
};
// Range: 0x8022C108 -> 0x8022C120
class ContextWrapper * RockCentralJob::NewContextWrapper() {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x8022C120 -> 0x8022C130
class RBBotbClient * RockCentralJob::GetBotbClient() {
    // References
    // -> class RockCentralGateway RockCentral;
}

enum /* @enum$39147RockCentralJobs_cpp */ {
    kNone = 0,
    kEnumeratingFriends = 1,
    kUpdatingFriends = 2,
    kFinished = 3,
};
class UpdateFriendsListJob : public RockCentralJob, public Object {
    // total size: 0x50
    int mUserPadNum; // offset 0x30, size 0x4
    int mUploadFriendsToken; // offset 0x34, size 0x4
    class vector mFriends; // offset 0x38, size 0xC
    class qList mFriendsGuids; // offset 0x44, size 0x8
    enum /* @enum$39147RockCentralJobs_cpp */ {
        kNone = 0,
        kEnumeratingFriends = 1,
        kUpdatingFriends = 2,
        kFinished = 3,
    } mState; // offset 0x4C, size 0x4
};
// Range: 0x8022C130 -> 0x8022C1C8
void * UpdateFriendsListJob::UpdateFriendsListJob(class UpdateFriendsListJob * const this /* r30 */, int userPadNum /* r31 */) {
    // References
    // -> struct [anonymous] __vt__20UpdateFriendsListJob;
    // -> struct [anonymous] __vt__14RockCentralJob;
}

// Range: 0x8022C1C8 -> 0x8022C314
void * UpdateFriendsListJob::~UpdateFriendsListJob(class UpdateFriendsListJob * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__20UpdateFriendsListJob;
}

// Range: 0x8022C314 -> 0x8022C344
void UpdateFriendsListJob::Start(class UpdateFriendsListJob * const this /* r5 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

static unsigned char tempResult; // size: 0x1, address: 0x80A4EB20
// Range: 0x8022C344 -> 0x8022C5E4
class DataNode UpdateFriendsListJob::OnMsg(class UpdateFriendsListJob * const this /* r29 */, const class PlatformMgrOpCompleteMsg & msg /* r25 */) {
    // Local variables
    class RBBotbClient * client; // r31
    class Profile * profile; // r24
    int savedToken; // r0
    unsigned int principalID; // r1+0x10
    int n; // r30
    class RBPlatformGuid guid; // r1+0x18
    class ContextWrapper * wrapper; // r0

    // References
    // -> static unsigned char tempResult;
    // -> struct [anonymous] __vt__Q26Quazal14RBPlatformGuid;
    // -> struct [anonymous] __vt__Q26Quazal19_DDL_RBPlatformGuid;
    // -> class Net TheNet;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8022C5E4 -> 0x8022C6C0
class DataNode UpdateFriendsListJob::OnMsg(class UpdateFriendsListJob * const this /* r30 */, const class RockCentralOpCompleteMsg & msg /* r31 */) {
    // Local variables
    class Profile * profile; // r31

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8022C6C0 -> 0x8022C6D8
unsigned char UpdateFriendsListJob::IsFinished() {}

// Range: 0x8022C6D8 -> 0x8022C7BC
void UpdateFriendsListJob::GetFriendsListToken(class UpdateFriendsListJob * const this /* r28 */) {
    // Local variables
    int currentBlock; // r1+0x8
    int n; // r31
    const char * name; // r30
    int m; // r29
}

// Range: 0x8022C7BC -> 0x8022CCB0
class DataNode UpdateFriendsListJob::Handle(class UpdateFriendsListJob * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__24RockCentralOpCompleteMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__24PlatformMgrOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x74
} __vt__20UpdateFriendsListJob; // size: 0x74, address: 0x808AFA2C
struct {
    // total size: 0x8
} __RTTI__20UpdateFriendsListJob; // size: 0x8, address: 0x808AFAE0
struct {
    // total size: 0x1C
} __vt__14RockCentralJob; // size: 0x1C, address: 0x808AFAE8
struct {
    // total size: 0x8
} __RTTI__14RockCentralJob; // size: 0x8, address: 0x808AFB20
struct {
    // total size: 0x8
} __RTTI__3Job; // size: 0x8, address: 0x808AFBE8

