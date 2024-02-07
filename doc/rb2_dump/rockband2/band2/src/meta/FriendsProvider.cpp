/*
    Compile unit: C:\rockband2\band2\src\meta\FriendsProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800EB0B8 -> 0x800EC598
*/
class FriendsProvider * sFriendsProvider; // size: 0x4, address: 0x80A4B010
class FriendsProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mFriends; // offset 0x2C, size 0xC
};
// Range: 0x800EB0B8 -> 0x800EB0EC
void FriendsProvider::Init() {
    // References
    // -> class FriendsProvider * sFriendsProvider;
}

// Range: 0x800EB0EC -> 0x800EB170
void * FriendsProvider::FriendsProvider(class FriendsProvider * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__15FriendsProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800EB170 -> 0x800EB220
void * FriendsProvider::~FriendsProvider(class FriendsProvider * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15FriendsProvider;
}

// Range: 0x800EB220 -> 0x800EB2F4
void FriendsProvider::CleanUp(class FriendsProvider * const this /* r28 */) {
    // Local variables
    int n; // r29
}

// Range: 0x800EB2F4 -> 0x800EB344
void FriendsProvider::EnumerateFriends(class FriendsProvider * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x800EB344 -> 0x800EB398
void FriendsProvider::EnumeratePending(class FriendsProvider * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x800EB398 -> 0x800EB3EC
void FriendsProvider::EnumerateOnline(class FriendsProvider * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x800EB3EC -> 0x800EB538
void FriendsProvider::InviteFriend(class FriendsProvider * const this /* r29 */, int selectedPos /* r30 */) {
    // Local variables
    char subject[256]; // r1+0x128
    char body[256]; // r1+0x28

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800EB538 -> 0x800EB660
char * FriendsProvider::Text(const class FriendsProvider * const this /* r28 */, int data /* r29 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800EB660 -> 0x800EB668
class RndMat * FriendsProvider::Mat() {}

// Range: 0x800EB668 -> 0x800EB680
int FriendsProvider::NumData() {}

// Range: 0x800EB680 -> 0x800EB694
class DataNode FriendsProvider::OnMsg() {}

// Range: 0x800EB694 -> 0x800EB720
char * FriendsProvider::GetFriendNickname(class FriendsProvider * const this /* r30 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x800EB720 -> 0x800EB734
char * FriendsProvider::GetFriendId() {}

// Range: 0x800EB734 -> 0x800EB78C
unsigned char FriendsProvider::CanAddFriend() {}

// Range: 0x800EB78C -> 0x800EB818
unsigned char FriendsProvider::DoesFriendExist(class FriendsProvider * const this /* r29 */, const char * key /* r30 */) {
    // Local variables
    int i; // r31
}

static class Symbol _s; // size: 0x4, address: 0x80A4B018
static class Symbol _s; // size: 0x4, address: 0x80A4B020
static class Symbol _s; // size: 0x4, address: 0x80A4B028
static class Symbol _s; // size: 0x4, address: 0x80A4B030
static class Symbol _s; // size: 0x4, address: 0x80A4B038
static class Symbol _s; // size: 0x4, address: 0x80A4B040
static class Symbol _s; // size: 0x4, address: 0x80A4B048
static class Symbol _s; // size: 0x4, address: 0x80A4B050
static class Symbol _s; // size: 0x4, address: 0x80A4B058
static class Symbol _s; // size: 0x4, address: 0x80A4B060
// Range: 0x800EB818 -> 0x800EC598
class DataNode FriendsProvider::Handle(class FriendsProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x50
    class MessageTimer _mt; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__24PlatformMgrOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x9C
} __vt__15FriendsProvider; // size: 0x9C, address: 0x80886830
struct {
    // total size: 0x8
} __RTTI__15FriendsProvider; // size: 0x8, address: 0x80886900

