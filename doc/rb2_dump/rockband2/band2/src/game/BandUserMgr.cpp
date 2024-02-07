/*
    Compile unit: C:\rockband2\band2\src\game\BandUserMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80046B6C -> 0x800482F0
*/
class BandUserMgr * TheBandUserMgr; // size: 0x4, address: 0x80A49310
// Range: 0x80046B6C -> 0x80046BA8
void BandUserMgrInit() {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80046BA8 -> 0x80046CFC
void * BandUserMgr::BandUserMgr(class BandUserMgr * const this /* r31 */, int num_users /* r29 */) {
    // Local variables
    int i; // r30
    int pad; // r5

    // References
    // -> struct [anonymous] __vt__11BandUserMgr;
}

// Range: 0x80046CFC -> 0x80046E84
void * BandUserMgr::~BandUserMgr(class BandUserMgr * const this /* r30 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> struct [anonymous] __vt__11BandUserMgr;
}

// Range: 0x80046E84 -> 0x80046E9C
int BandUserMgr::MaxUsers() {}

// Range: 0x80046E9C -> 0x80046FF4
void BandUserMgr::SwapUsers(class BandUserMgr * const this /* r29 */, int id1 /* r30 */, int id2 /* r31 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80046FF4 -> 0x8004702C
class User * BandUserMgr::GetUser() {}

// Range: 0x8004702C -> 0x80047064
class BandUser * BandUserMgr::GetBandUser() {}

// Range: 0x80047064 -> 0x8004706C
class vector & BandUserMgr::GetBandUsers() {}

// Range: 0x8004706C -> 0x800470A4
void BandUserMgr::ResetSlots() {
    // Local variables
    int i; // r6
}

// Range: 0x800470A4 -> 0x80047144
int BandUserMgr::GetSlot(const class BandUserMgr * const this /* r30 */, int id /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80047144 -> 0x800471F0
void BandUserMgr::SetSlot(class BandUserMgr * const this /* r29 */, int id /* r30 */, int slot /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800471F0 -> 0x800471F8
void BandUserMgr::ResetSlot() {}

// Range: 0x800471F8 -> 0x800472AC
unsigned char BandUserMgr::IsParticipating(const class BandUserMgr * const this /* r30 */, int id /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800472AC -> 0x800472F4
int BandUserMgr::GetPlayerFromSlot() {
    // Local variables
    int i; // r6
}

// Range: 0x800472F4 -> 0x80047344
class BandUser * BandUserMgr::GetUserFromSlot() {
    // Local variables
    int i; // r6
}

// Range: 0x80047344 -> 0x800473AC
int BandUserMgr::MaxSlot() {
    // Local variables
    int max; // r1+0x8
    int i; // r6
}

// Range: 0x800473AC -> 0x8004742C
int BandUserMgr::GetNumParticipants(const class BandUserMgr * const this /* r29 */) {
    // Local variables
    int num; // r31
    int i; // r30
}

// Range: 0x8004742C -> 0x80047464
unsigned char BandUserMgr::IsMultiplayerGame() {}

// Range: 0x80047464 -> 0x80047508
int BandUserMgr::GetNumLocalPlayers(const class BandUserMgr * const this /* r29 */) {
    // Local variables
    int num; // r31
    int i; // r30
}

// Range: 0x80047508 -> 0x80047510
int BandUserMgr::GetMaxNumUsers() {}

// Range: 0x80047510 -> 0x80047600
void BandUserMgr::ListParticipantConfigs(class BandUserMgr * const this /* r28 */, class list & configs /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8BandUser>;
    // -> unsigned char gStlAllocNameLookup;
}

struct BandUserSlotCmp {
    // total size: 0x4
    const class BandUserMgr & mUserMgr; // offset 0x0, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8BandUser>; // size: 0x8, address: 0x80872968
// Range: 0x80047600 -> 0x8004760C
int BandUserMgr::CountBandUsers() {}

// Range: 0x8004760C -> 0x80047614
void BandUserMgr::GetParticipatingBandUsers() {}

// Range: 0x80047614 -> 0x8004761C
void BandUserMgr::GetLocalParticipants() {}

// Range: 0x8004761C -> 0x80047624
void BandUserMgr::GetLocalBandUsers() {}

// Range: 0x80047624 -> 0x8004762C
void BandUserMgr::GetLocalNonParticipantsWithAnyController() {}

// Range: 0x8004762C -> 0x80047670
void BandUserMgr::GetLocalNonParticipantsWithControllerType() {}

// Range: 0x80047670 -> 0x800477D8
void BandUserMgr::GetLocalParticipantNums(class BandUserMgr * const this /* r30 */, class vector & user_nums /* r29 */) {
    // Local variables
    class vector users; // r1+0x20
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800477D8 -> 0x800478A4
class BandUser * BandUserMgr::DebugGetUserFromPad(class BandUserMgr * const this /* r28 */, int padNum /* r29 */) {
    // Local variables
    class BandUser * * it; // r31
    class BandUser * pUser; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A49318
static class Symbol _s; // size: 0x4, address: 0x80A49320
static class Symbol _s; // size: 0x4, address: 0x80A49328
static class Symbol _s; // size: 0x4, address: 0x80A49330
static class Symbol _s; // size: 0x4, address: 0x80A49338
static class Symbol _s; // size: 0x4, address: 0x80A49340
static class Symbol _s; // size: 0x4, address: 0x80A49348
static class Symbol _s; // size: 0x4, address: 0x80A49350
// Range: 0x800478A4 -> 0x800482F0
class DataNode BandUserMgr::Handle(class BandUserMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
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
    // total size: 0x60
} __vt__11BandUserMgr; // size: 0x60, address: 0x80872B28
struct {
    // total size: 0x8
} __RTTI__11BandUserMgr; // size: 0x8, address: 0x80872BB0
struct {
    // total size: 0x8
} __RTTI__7UserMgr; // size: 0x8, address: 0x80872BD8
struct {
    // total size: 0x8
} __RTTI__PP8BandUser; // size: 0x8, address: 0x80872C20

