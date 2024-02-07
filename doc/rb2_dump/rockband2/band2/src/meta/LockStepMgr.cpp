/*
    Compile unit: C:\rockband2\band2\src\meta\LockStepMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800FC5D0 -> 0x800FE02C
*/
class StartLockMsg : public NetMessage {
    // total size: 0x8
    int mLockUserID; // offset 0x4, size 0x4
};
class LockResponseMsg : public NetMessage {
    // total size: 0x14
    unsigned char mLocked; // offset 0x4, size 0x1
    class vector mLockedIDs; // offset 0x8, size 0xC
};
class EndLockMsg : public NetMessage {
    // total size: 0x4
};
class LockStepMgr * TheLockStepMgr; // size: 0x4, address: 0x80A4B2A0
class LockStepMgr : public Object {
    // total size: 0x3C
    class vector mWaitList; // offset 0x28, size 0xC
    unsigned char mLockSuccess; // offset 0x34, size 0x1
    class BandUser * mLockUser; // offset 0x38, size 0x4
};
// Range: 0x800FC5D0 -> 0x800FC74C
void * LockStepMgr::LockStepMgr(class LockStepMgr * const this /* r29 */) {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LockStepMgr * TheLockStepMgr;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__11LockStepMgr;
}

// Range: 0x800FC74C -> 0x800FC850
void * LockStepMgr::~LockStepMgr(class LockStepMgr * const this /* r29 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LockStepMgr * TheLockStepMgr;
    // -> struct [anonymous] __vt__11LockStepMgr;
}

// Range: 0x800FC850 -> 0x800FC884
unsigned char LockStepMgr::InLock() {}

// Range: 0x800FC884 -> 0x800FCABC
void LockStepMgr::StartLock(class LockStepMgr * const this /* r29 */) {
    // Local variables
    class vector & users; // r0
    int n; // r30
    class vector locals; // r1+0x18
    class StartLockMsg msg; // r1+0x10

    // References
    // -> class NetSession * TheNetSession;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class InputMgr * TheInputMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message ilsr; // size: 0x8, address: 0x80978C20
// Range: 0x800FCAFC -> 0x800FCE74
void LockStepMgr::OnStartLockMsg(class LockStepMgr * const this /* r30 */, class BandUser * lockUser /* r29 */) {
    // Local variables
    unsigned char ready; // r30
    class DataNode res; // r1+0x28
    class vector localUsers; // r1+0x30
    int n; // r28
    class LockResponseMsg msg; // r1+0x3C

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class NetSession * TheNetSession;
    // -> class InputMgr * TheInputMgr;
    // -> static class Message ilsr;
    // -> struct [anonymous] __vt__7Message;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800FCE74 -> 0x800FCEF8
void LockStepMgr::OnLockResponseMsg(class LockStepMgr * const this /* r29 */, class vector & users /* r30 */) {
    // Local variables
    int n; // r31
}

// Range: 0x800FCEF8 -> 0x800FD03C
void LockStepMgr::RemoveUserFromWaitList(class LockStepMgr * const this /* r31 */, class BandUser * user /* r29 */) {
    // Local variables
    unsigned char found; // r5
    int m; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message lsc; // size: 0x8, address: 0x80978C38
// Range: 0x800FD03C -> 0x800FD310
void LockStepMgr::ReleaseLock(class LockStepMgr * const this /* r30 */) {
    // Local variables
    class EndLockMsg msg; // r1+0x10

    // References
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __vt__10EndLockMsg;
    // -> class InputMgr * TheInputMgr;
    // -> static class Message lsc;
    // -> struct [anonymous] __vt__7Message;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800FD350 -> 0x800FD354
void LockStepMgr::OnEndLockMsg() {}

// Range: 0x800FD354 -> 0x800FD3D8
class DataNode LockStepMgr::OnMsg() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x800FD3D8 -> 0x800FD448
void LockStepMgr::ReleaseLockFromUser(class LockStepMgr * const this /* r31 */) {
    // References
    // -> class InputMgr * TheInputMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800FD448 -> 0x800FD4FC
class DataNode LockStepMgr::OnMsg(class LockStepMgr * const this /* r30 */) {
    // Local variables
    class BandUser * user; // r4

    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B2A8
static class Symbol _s; // size: 0x4, address: 0x80A4B2B0
// Range: 0x800FD4FC -> 0x800FDCB8
class DataNode LockStepMgr::Handle(class LockStepMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__19RemotePlayerLeftMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__18NewRemotePlayerMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x800FDCB8 -> 0x800FDCD0
void * StartLockMsg::StartLockMsg() {
    // References
    // -> struct [anonymous] __vt__12StartLockMsg;
}

// Range: 0x800FDCD0 -> 0x800FDD08
void StartLockMsg::Save(const class StartLockMsg * const this /* r5 */) {}

// Range: 0x800FDD08 -> 0x800FDD48
void StartLockMsg::Load(class StartLockMsg * const this /* r31 */) {
    // Local variables
    unsigned char id; // r1+0x8
}

// Range: 0x800FDD48 -> 0x800FDD80
void StartLockMsg::Dispatch(class StartLockMsg * const this /* r4 */) {
    // Local variables
    class BandUser * user; // r0

    // References
    // -> class LockStepMgr * TheLockStepMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800FDD80 -> 0x800FDE64
void * LockResponseMsg::LockResponseMsg(class LockResponseMsg * const this /* r29 */, class vector & users /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> struct [anonymous] __vt__15LockResponseMsg;
}

// Range: 0x800FDE64 -> 0x800FDEBC
void LockResponseMsg::Save(const class LockResponseMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x800FDEBC -> 0x800FDF20
void LockResponseMsg::Load(class LockResponseMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x800FDF20 -> 0x800FE024
void LockResponseMsg::Dispatch(class LockResponseMsg * const this /* r30 */) {
    // Local variables
    class vector users; // r1+0x14
    int n; // r31

    // References
    // -> class LockStepMgr * TheLockStepMgr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800FE024 -> 0x800FE02C
void EndLockMsg::Dispatch() {
    // References
    // -> class LockStepMgr * TheLockStepMgr;
}

struct {
    // total size: 0x28
} __vt__10EndLockMsg; // size: 0x28, address: 0x80889420
struct {
    // total size: 0x8
} __RTTI__10EndLockMsg; // size: 0x8, address: 0x80889460
struct {
    // total size: 0x28
} __vt__15LockResponseMsg; // size: 0x28, address: 0x80889468
struct {
    // total size: 0x8
} __RTTI__15LockResponseMsg; // size: 0x8, address: 0x808894B0
struct {
    // total size: 0x28
} __vt__12StartLockMsg; // size: 0x28, address: 0x808894B8
struct {
    // total size: 0x8
} __RTTI__12StartLockMsg; // size: 0x8, address: 0x80889500
struct {
    // total size: 0x54
} __vt__11LockStepMgr; // size: 0x54, address: 0x80889508
struct {
    // total size: 0x8
} __RTTI__11LockStepMgr; // size: 0x8, address: 0x80889580

