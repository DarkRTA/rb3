/*
    Compile unit: C:\rockband2\system\src\net\SessionSearcher_RV.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8053853C -> 0x80539388
*/
// Range: 0x8053853C -> 0x80538574
class SessionSearcher * SessionSearcher::New() {}

class RVSessionSearcher : public SessionSearcher {
    // total size: 0x78
    class ProtocolCallContext * mSearchCallback; // offset 0x34, size 0x4
    class qList mResultsList; // offset 0x38, size 0x8
    class ProtocolCallContext * mInviteCallback; // offset 0x40, size 0x4
    class AnyObjectHolder mInviteResult; // offset 0x44, size 0x8
};
// Range: 0x80538574 -> 0x8053862C
void * RVSessionSearcher::RVSessionSearcher(class RVSessionSearcher * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__Q26Quazal53AnyObjectHolder<Q26Quazal9Gathering,Q26Quazal6String>;
    // -> struct [anonymous] __vt__17RVSessionSearcher;
}

// Range: 0x8053862C -> 0x8053873C
void * RVSessionSearcher::~RVSessionSearcher(class RVSessionSearcher * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__17RVSessionSearcher;
}

static class InviteAcceptedMsg inviteMsg; // size: 0x8, address: 0x80982188
static class InviteAcceptedMsg inviteMsg; // size: 0x8, address: 0x809821A0
// Range: 0x8053873C -> 0x80538F18
void RVSessionSearcher::Poll(class RVSessionSearcher * const this /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0x38
    class HarmonixGathering * gath; // r0
    int size; // r27
    class MemStream resultData; // r1+0xB0
    class NetSearchResult * result; // r27
    class RVSessionData * data; // r0
    class HarmonixGathering * gath; // r0
    int size; // r27
    class MemStream resultData; // r1+0x90
    class RVSessionData * data; // r0

    // References
    // -> static class InviteAcceptedMsg inviteMsg;
    // -> struct [anonymous] __vt__17InviteAcceptedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class InviteAcceptedMsg inviteMsg;
    // -> struct [anonymous] __RTTI__11SessionData;
    // -> struct [anonymous] __RTTI__13RVSessionData;
    // -> struct [anonymous] __RTTI__Q26Quazal9Gathering;
    // -> struct [anonymous] __RTTI__Q26Quazal17HarmonixGathering;
}

static class ResultRange range; // size: 0xC, address: 0x809821B4
static unsigned char ranked; // size: 0x1, address: 0x80A53E03
static int gameMode; // size: 0x4, address: 0x80A53E04
static class qList props; // size: 0x8, address: 0x809821D0
static int queryID; // size: 0x4, address: 0x80A53E0C
// Range: 0x80538F18 -> 0x80539188
void RVSessionSearcher::StartSearching(class RVSessionSearcher * const this /* r29 */, const class SearchSettings & settings /* r30 */) {
    // Local variables
    int n; // r27
    struct _List_iterator it; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LogFile NetLog;
    // -> static int gameMode;
    // -> static unsigned char ranked;
    // -> static int queryID;
    // -> static class qList props;
    // -> static class ResultRange range;
    // -> struct [anonymous] __vt__Q26Quazal11ResultRange;
    // -> class Net TheNet;
}

// Range: 0x80539188 -> 0x805391E0
void RVSessionSearcher::StopSearching(class RVSessionSearcher * const this /* r31 */) {}

// Range: 0x805391E0 -> 0x80539388
unsigned char RVSessionSearcher::OnMsg(class RVSessionSearcher * const this /* r28 */, const class InviteAcceptedMsg & msg /* r29 */) {
    // Local variables
    unsigned char success; // r0

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> class Net TheNet;
}

struct {
    // total size: 0x7C
} __vt__17RVSessionSearcher; // size: 0x7C, address: 0x80907980
struct {
    // total size: 0x8
} __RTTI__17RVSessionSearcher; // size: 0x8, address: 0x80907A38

