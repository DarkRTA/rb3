/*
    Compile unit: C:\rockband2\system\src\net\NetSession_RV.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80531FDC -> 0x80532EAC
*/
// Range: 0x80531FDC -> 0x80532084
static void SerializeNetSearchResult(class Buffer & buffer /* r30 */, class NetSearchResult * result /* r31 */) {
    // Local variables
    class MemStream dataBuffer; // r1+0x10
}

// Range: 0x80532084 -> 0x805320BC
class NetSession * NetSession::New() {}

class RVSession : public NetSession {
    // total size: 0xF0
    class AnyObjectHolder mGathering; // offset 0xAC, size 0x8
    unsigned char mJoined; // offset 0xB4, size 0x1
    int mUpdateSettingsID; // offset 0xB8, size 0x4
    int mJoinSessionJobID; // offset 0xBC, size 0x4
};
// Range: 0x805320BC -> 0x80532160
void * RVSession::RVSession(class RVSession * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal53AnyObjectHolder<Q26Quazal9Gathering,Q26Quazal6String>;
    // -> struct [anonymous] __vt__9RVSession;
}

// Range: 0x80532160 -> 0x805322C8
void RVSession::DeleteSession(class RVSession * const this /* r30 */) {
    // Local variables
    int gathering_id; // r29

    // References
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

class HarmonixGathering : public _DDL_HarmonixGathering {
    // total size: 0x68
};
// Range: 0x805322C8 -> 0x80532364
unsigned char RVSession::Join(class RVSession * const this /* r30 */) {
    // Local variables
    class RVSessionData * data; // r31

    // References
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
}

// Range: 0x80532364 -> 0x805323AC
void RVSession::CancelJoin(class RVSession * const this /* r31 */) {}

// Range: 0x805323AC -> 0x80532460
void RVSession::FinishJoin(class RVSession * const this /* r30 */, const class JoinResponseMsg & msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
    // -> class Net TheNet;
}

// Range: 0x80532460 -> 0x805326A4
void RVSession::UpdateSettings(class RVSession * const this /* r29 */) {
    // Local variables
    class HarmonixGathering * gath; // r0
    class NetSearchResult * currentResult; // r30
    int n; // r30

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q26Quazal9Gathering;
    // -> struct [anonymous] __RTTI__Q26Quazal17HarmonixGathering;
}

// Range: 0x805326A4 -> 0x805326C0
class DataNode RVSession::OnUpdateFinished() {}

// Range: 0x805326C0 -> 0x80532738
void RVSession::StartSession(class RVSession * const this /* r31 */) {}

// Range: 0x80532738 -> 0x805327B4
void RVSession::EndSession(class RVSession * const this /* r31 */) {}

// Range: 0x805327B4 -> 0x805328C0
void RVSession::InviteFriend(class Friend * invitee /* r28 */, class String & subject /* r29 */, class String & body /* r30 */) {
    // Local variables
    class RVSessionData * data; // r0
    unsigned int id; // r31
    class MemStream inviteData; // r1+0x28

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
}

static class Symbol _s; // size: 0x4, address: 0x80A53D84
// Range: 0x805328C0 -> 0x80532CDC
class DataNode RVSession::Handle(class RVSession * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80532CDC -> 0x80532D0C
class SessionData * SessionData::New() {}

// Range: 0x80532D0C -> 0x80532D28
void * RVSessionData::RVSessionData() {
    // References
    // -> struct [anonymous] __vt__13RVSessionData;
}

// Range: 0x80532D28 -> 0x80532D80
void RVSessionData::CopyInto(class RVSessionData * const this /* r31 */) {
    // Local variables
    class RVSessionData * pcData; // r0

    // References
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
}

// Range: 0x80532D80 -> 0x80532DE4
void RVSessionData::Save(const class RVSessionData * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80532DE4 -> 0x80532E38
void RVSessionData::Load(class RVSessionData * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80532E38 -> 0x80532EAC
unsigned char RVSessionData::Equals(const class RVSessionData * const this /* r31 */) {
    // Local variables
    const class RVSessionData * rhs; // r0

    // References
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
}

struct {
    // total size: 0x1C
} __vt__13RVSessionData; // size: 0x1C, address: 0x80906A90
struct {
    // total size: 0x8
} __RTTI__13RVSessionData; // size: 0x8, address: 0x80906AC8
struct {
    // total size: 0xC0
} __vt__9RVSession; // size: 0xC0, address: 0x80906AD0
struct {
    // total size: 0x8
} __RTTI__9RVSession; // size: 0x8, address: 0x80906BC0
struct {
    // total size: 0x8
} __RTTI__11SessionData; // size: 0x8, address: 0x80906BD8

