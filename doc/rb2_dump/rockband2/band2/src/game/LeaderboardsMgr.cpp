/*
    Compile unit: C:\rockband2\band2\src\game\LeaderboardsMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800A97CC -> 0x800AB878
*/
class Symbol t; // size: 0x4, address: 0x80A4A3BC
class LeaderboardsMgr * TheLeaderboards; // size: 0x4, address: 0x80A4A3C0
// Range: 0x800A97CC -> 0x800A9904
void * LeaderboardsMgr::LeaderboardsMgr(class LeaderboardsMgr * const this /* r29 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> struct [anonymous] __vt__15LeaderboardsMgr;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800A9904 -> 0x800A9A28
void * LeaderboardsMgr::~LeaderboardsMgr(class LeaderboardsMgr * const this /* r30 */) {
    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> struct [anonymous] __vt__15LeaderboardsMgr;
}

// Range: 0x800A9A28 -> 0x800A9B70
void LeaderboardsMgr::Destroy(class LeaderboardsMgr * const this /* r27 */) {}

// Range: 0x800A9B70 -> 0x800A9BF8
unsigned char LeaderboardsMgr::CancelEnumerate(class LeaderboardsMgr * const this /* r31 */) {}

// Range: 0x800A9BF8 -> 0x800A9DB0
void LeaderboardsMgr::Enumerate(class LeaderboardsMgr * const this /* r31 */) {
    // Local variables
    class vector profiles; // r1+0x10
    class Profile * * it; // r29
    int player_num; // r0
    class User * user; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<P4User>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class UserMgr * TheUserMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std18_List_node<P4User>; // size: 0x8, address: 0x8087CB80
// Range: 0x800A9DB0 -> 0x800A9FB4
void LeaderboardsMgr::EnumMoreFriends(class LeaderboardsMgr * const this /* r31 */) {
    // Local variables
    class Friend * * it; // r30
    class Friend * newFriend; // r1+0x38

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

static class Symbol career; // size: 0x4, address: 0x80A4A3C8
// Range: 0x800A9FB4 -> 0x800AA320
void LeaderboardsMgr::CreateLocalBoard(class LeaderboardsMgr * const this /* r31 */) {
    // Local variables
    int padNum; // r0
    unsigned int playerId; // r0
    class LeaderboardData * pData; // r0
    int padNum; // r0
    unsigned int playerId; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol career;
    // -> class Net TheNet;
}

static class Message errorMsg; // size: 0x8, address: 0x80977B48
static class Symbol leaderboards_netwatcher_panel; // size: 0x4, address: 0x80A4A3D0
// Range: 0x800AA320 -> 0x800AA53C
void LeaderboardsMgr::HandleIOError() {
    // References
    // -> class UIManager TheUI;
    // -> static class Symbol leaderboards_netwatcher_panel;
    // -> static class Message errorMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800AA53C -> 0x800AA620
void LeaderboardsMgr::RotateFilter(class LeaderboardsMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x80977B60
// Range: 0x800AA620 -> 0x800AA820
void LeaderboardsMgr::UpdateFilter(class LeaderboardsMgr * const this /* r31 */) {
    // References
    // -> class UIManager TheUI;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800AA820 -> 0x800AA8B4
unsigned long long LeaderboardsMgr::GetLowScore(class LeaderboardsMgr * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800AA8B4 -> 0x800AA8BC
void LeaderboardsMgr::SetPlayerNum() {}

// Range: 0x800AA8BC -> 0x800AA930
void LeaderboardsMgr::SetBandFromTour(class LeaderboardsMgr * const this /* r31 */) {
    // Local variables
    class TourBand * band; // r0

    // References
    // -> class Tour * TheTour;
}

// Range: 0x800AA930 -> 0x800AA938
void LeaderboardsMgr::SetTrackType() {}

// Range: 0x800AA938 -> 0x800AA940
class Symbol LeaderboardsMgr::GetTrackTypeSym() {}

// Range: 0x800AA940 -> 0x800AA9DC
class Symbol LeaderboardsMgr::GetTrackTypeChar() {
    // References
    // -> class DataArray * sTrackIcons;
}

// Range: 0x800AA9DC -> 0x800AA9F4
void LeaderboardsMgr::SetHighlight() {}

// Range: 0x800AA9F4 -> 0x800AA9FC
class Element & LeaderboardsMgr::GetHighlight() {}

// Range: 0x800AA9FC -> 0x800AAA04
class Symbol LeaderboardsMgr::GetSongSym() {}

// Range: 0x800AAA04 -> 0x800AAA88
void LeaderboardsMgr::SetType(class LeaderboardsMgr * const this /* r30 */, enum Type type /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800AAA88 -> 0x800AAA90
enum Type LeaderboardsMgr::GetType() {}

// Range: 0x800AAA90 -> 0x800AAAE4
void LeaderboardsMgr::ClearType(class LeaderboardsMgr * const this /* r31 */) {}

// Range: 0x800AAAE4 -> 0x800AAB80
class Leaderboard * LeaderboardsMgr::GetCurrentBoard() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800AAB80 -> 0x800AABC0
int LeaderboardsMgr::NumData() {
    // Local variables
    class Leaderboard * board; // r0
}

// Range: 0x800AABC0 -> 0x800AAC38
char * LeaderboardsMgr::Text(int showing /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    class Leaderboard * board; // r0
}

// Range: 0x800AAC38 -> 0x800AACB0
class RndMat * LeaderboardsMgr::Mat(int showing /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    class Leaderboard * board; // r0
}

// Range: 0x800AACB0 -> 0x800AAD4C
void LeaderboardsMgr::SetSizeLimits(class LeaderboardsMgr * const this /* r28 */, class DataArray * limits /* r29 */) {
    // Local variables
    int size; // r31
    int i; // r30
}

static class Symbol career; // size: 0x4, address: 0x80A4A3D8
// Range: 0x800AAD4C -> 0x800AAE44
int LeaderboardsMgr::GetBoardLimit(class LeaderboardsMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol career;
}

// Range: 0x800AAE44 -> 0x800AAE4C
void LeaderboardsMgr::SetConnectionState() {}

static class Symbol _s; // size: 0x4, address: 0x80A4A3E0
static class Symbol _s; // size: 0x4, address: 0x80A4A3E8
static class Symbol _s; // size: 0x4, address: 0x80A4A3F0
static class Symbol _s; // size: 0x4, address: 0x80A4A3F8
static class Symbol _s; // size: 0x4, address: 0x80A4A400
static class Symbol _s; // size: 0x4, address: 0x80A4A408
static class Symbol _s; // size: 0x4, address: 0x80A4A410
static class Symbol _s; // size: 0x4, address: 0x80A4A418
static class Symbol _s; // size: 0x4, address: 0x80A4A420
static class Symbol _s; // size: 0x4, address: 0x80A4A428
static class Symbol _s; // size: 0x4, address: 0x80A4A430
static class Symbol _s; // size: 0x4, address: 0x80A4A438
static class Symbol _s; // size: 0x4, address: 0x80A4A440
static class Symbol _s; // size: 0x4, address: 0x80A4A448
static class Symbol _s; // size: 0x4, address: 0x80A4A450
static class Symbol _s; // size: 0x4, address: 0x80A4A458
static class Symbol _s; // size: 0x4, address: 0x80A4A460
static class Symbol _s; // size: 0x4, address: 0x80A4A468
static class Symbol _s; // size: 0x4, address: 0x80A4A470
static class Symbol _s; // size: 0x4, address: 0x80A4A478
static class Symbol _s; // size: 0x4, address: 0x80A4A480
// Range: 0x800AAE4C -> 0x800AB878
class DataNode LeaderboardsMgr::Handle(class LeaderboardsMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x9C
} __vt__15LeaderboardsMgr; // size: 0x9C, address: 0x8087CED0
struct {
    // total size: 0x8
} __RTTI__15LeaderboardsMgr; // size: 0x8, address: 0x8087CFA0
struct {
    // total size: 0xC
} __vt__24PlatformMgrOpCompleteMsg; // size: 0xC, address: 0x8087CFC0
struct {
    // total size: 0x8
} __RTTI__24PlatformMgrOpCompleteMsg; // size: 0x8, address: 0x8087CFF8
struct {
    // total size: 0x8
} __RTTI__PP6Friend; // size: 0x8, address: 0x8087D060
class ServerStatusChangedMsg : public Message {
    // total size: 0x8
};
class CriticalSection {
    // total size: 0x1C
    int mEntryCount; // offset 0x0, size 0x4
    struct OSMutex mCritSec; // offset 0x4, size 0x18
};
struct InternalData {
    // total size: 0xC
    void (* m_Callback)(class CallContext *, class UserContext *); // offset 0x0, size 0x4
    class UserContext m_oUserContext; // offset 0x4, size 0x4
    unsigned char m_bPreTerminateCallbackRegistered; // offset 0x8, size 0x1
};
enum _State {
    Uninitialized = 1,
    Initializing = 2,
    Ready = 4,
    ReadyInUse = 8,
    Terminating = 16,
    TerminatingInUse = 32,
    Terminated = 64,
    Faulty = 128,
    Unknown = 256,
    HighestState = 256,
};
class SystemComponent : public RefCountedObject {
    // total size: 0x18
    class String m_strName; // offset 0x8, size 0x4
    enum _State m_eState; // offset 0xC, size 0x4
    unsigned int m_uiInUseCount; // offset 0x10, size 0x4
    class SystemComponent * m_pParent; // offset 0x14, size 0x4
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class qMap : public map, public RootObject {
    // total size: 0x18
};
class BandwidthCounterMap : public RootObject {
    // total size: 0x1C
    class String m_name; // offset 0x0, size 0x4
    class qMap m_map; // offset 0x4, size 0x18
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class qMap : public map, public RootObject {
    // total size: 0x18
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class QEvent : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned char m_bRepeatEvent; // offset 0x4, size 0x1
};
class Operation : public QEvent {
    // total size: 0x10
    unsigned char m_bOperationAborted; // offset 0x5, size 0x1
    class UserContext m_uUserData; // offset 0x8, size 0x4
    unsigned int m_uiOrigin; // offset 0xC, size 0x4
};
class OperationCallback : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    int m_iPriority; // offset 0x4, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class OperationManager : public RootObject {
    // total size: 0x10
    class qList m_lstCallbacks; // offset 0x0, size 0x8
    class qList m_stackOperations; // offset 0x8, size 0x8
};
class CallPolicy : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class SingleThreadCallPolicy : public CallPolicy {
    // total size: 0x14
    unsigned int m_uiCurrentRecursionLevel; // offset 0x4, size 0x4
    unsigned int m_uiCurrentThread; // offset 0x8, size 0x4
    unsigned int m_uiMaximumRecursionLevel; // offset 0xC, size 0x4
    unsigned int m_uiValidThread; // offset 0x10, size 0x4
};
enum _Type {
    Client = 0,
    Server = 1,
};
class ClientProtocol : public Protocol {
    // total size: 0x38
};
class ProtocolRequestBroker : public RootObject {
    // total size: 0x64
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class BandwidthCounterMap m_bandwidthCounters; // offset 0x4, size 0x1C
    class qMap m_mProtocols; // offset 0x20, size 0x18
    class EndPoint * m_pCurrentEndPoint; // offset 0x38, size 0x4
    class ProtocolRequestBroker * m_pPrototypeBroker; // offset 0x3C, size 0x4
    class OperationManager m_oManager; // offset 0x40, size 0x10
    class SingleThreadCallPolicy m_oCallPolicy; // offset 0x50, size 0x14
};
class Protocol : public SystemComponent {
    // total size: 0x38
    unsigned char m_byProtocolID; // offset 0x18, size 0x1
    class EndPoint * m_pOutgoingConnection; // offset 0x1C, size 0x4
    class ProtocolRequestBroker * m_pAssociatedRequestBroker; // offset 0x20, size 0x4
    unsigned int m_uiFlags; // offset 0x24, size 0x4
    class EndPoint * m_pIncomingConnection; // offset 0x28, size 0x4
    unsigned char m_bUseLocalLoopback; // offset 0x2C, size 0x1
    unsigned int m_pidCaller; // offset 0x30, size 0x4
    unsigned int m_cidCaller; // offset 0x34, size 0x4
};
class ServerProtocol : public Protocol {
    // total size: 0x158
    class PerfCounter m_oProtocolCalls; // offset 0x38, size 0x60
    class PerfCounter m_oRequestTraffic; // offset 0x98, size 0x60
    class PerfCounter m_oResponseTraffic; // offset 0xF8, size 0x60
};
class _Proto_RemoteLogDeviceProtocolServer : public ServerProtocol {
    // total size: 0x158
};
class RemoteLogDeviceLogsCallback : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RemoteLogDeviceServer : public _Proto_RemoteLogDeviceProtocolServer {
    // total size: 0x160
    class ProtocolRequestBroker * m_pBroker; // offset 0x158, size 0x4
    class RemoteLogDeviceLogsCallback * m_pLogsCallback; // offset 0x15C, size 0x4
};
class NotificationEventManager {
    // total size: 0x0
};
class PRUDPStream {
    // total size: 0x0
};
class ComponentState : public SystemComponent {
    // total size: 0x18
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class StreamTable : public RootObject {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class qList m_oStreamList; // offset 0x4, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x60
public:
    class StationURL _M_data; // offset 0x8, size 0x58
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class ConnectionManager : public TransportEventHandler {
    // total size: 0xC0
protected:
    unsigned int m_icContext; // offset 0x4, size 0x4
private:
    class ComponentState m_oConnectionManagerState; // offset 0x8, size 0x18
    class InetAddress m_oRouterAddress; // offset 0x20, size 0x80
    unsigned char (* m_pfConnectionFilter)(class UserContext &, class Buffer *, class Buffer *, class EndPoint *); // offset 0xA0, size 0x4
    class UserContext m_oConnectionFilterContext; // offset 0xA4, size 0x4
    unsigned char m_bAcceptIncomingConnections; // offset 0xA8, size 0x1
    class EndPointEventHandler * m_pEndPointEventHandler; // offset 0xAC, size 0x4
    class StreamTable m_oStreams; // offset 0xB0, size 0xC
    unsigned char m_bDirectConnection; // offset 0xBC, size 0x1
    unsigned char m_bRoutedConnection; // offset 0xBD, size 0x1
};
class Links {
    // total size: 0x8
public:
    class SystemSetting * m_pNext; // offset 0x0, size 0x4
    class SystemSetting * m_pPrevious; // offset 0x4, size 0x4
};
class SystemSetting : public RootObject {
    // total size: 0x14
public:
    class Links m_oLinks; // offset 0x0, size 0x8
private:
    class String m_strName; // offset 0x8, size 0x4
    unsigned int m_uiValue; // offset 0xC, size 0x4
    unsigned char m_bIsImmutable; // offset 0x10, size 0x1
};
class StreamManager : public EndPointEventHandler {
    // total size: 0x24
    class PRUDPStream * m_pStream; // offset 0x4, size 0x4
    class ConnectionOrientedStream * m_pSecureStream; // offset 0x8, size 0x4
    class ProtocolRequestBroker * m_pBroker; // offset 0xC, size 0x4
    class ConnectionManager * m_pConnectionManager; // offset 0x10, size 0x4
    unsigned char m_bInitialized; // offset 0x14, size 0x1
    class RootTransport * m_pTransport; // offset 0x18, size 0x4
    enum Type m_oStreamType; // offset 0x1C, size 0x4
    unsigned short m_uiPort; // offset 0x20, size 0x2
};
class Links {
    // total size: 0x8
public:
    class Job * m_pNext; // offset 0x0, size 0x4
    class Job * m_pPrevious; // offset 0x4, size 0x4
};
class DebugString {
    // total size: 0x1
};
enum State {
    Initial = 0,
    Waiting = 1,
    Suspended = 2,
    Ready = 3,
    Running = 4,
    Complete = 5,
};
class Job : public RefCountedObject {
    // total size: 0x38
public:
    class Links m_oLinks; // offset 0x8, size 0x8
private:
    void (* m_pfCompletionCallback)(class Job *, class UserContext *); // offset 0x10, size 0x4
    class UserContext m_oContext; // offset 0x14, size 0x4
    class DebugString m_strJobDescription; // offset 0x18, size 0x1
    enum State m_eState; // offset 0x1C, size 0x4
    int m_tiWaitTime; // offset 0x20, size 0x4
    unsigned int m_uiNbExecutions; // offset 0x24, size 0x4
    class Time m_tDeadline; // offset 0x28, size 0x8
    unsigned char m_bUsesGlobalLock; // offset 0x30, size 0x1
    unsigned char m_bTraceState; // offset 0x31, size 0x1
};
class EffectiveLoginTimeout {
    // total size: 0x4
    int m_tiTimeout; // offset 0x0, size 0x4
};
class RendezVousProductInfo {
    // total size: 0x0
};
class BackEndServices : public RootObject {
    // total size: 0x90
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    struct InternalData m_PreTerminateCB; // offset 0x4, size 0xC
    class CallContext m_oContext; // offset 0x10, size 0x48
    class CallContext * m_pUserCallContext; // offset 0x58, size 0x4
    int m_tiLoginTimeout; // offset 0x5C, size 0x4
    class Credentials * m_pCurrentCredentials; // offset 0x60, size 0x4
    unsigned short m_uiPort; // offset 0x64, size 0x2
    unsigned char m_idStream; // offset 0x66, size 0x1
    unsigned int m_uiConnectionFlags; // offset 0x68, size 0x4
    class RemoteLogDeviceServer * m_pRemoteLogDeviceServer; // offset 0x6C, size 0x4
    class NotificationEventManager * m_pNotificationEventManager; // offset 0x70, size 0x4
    unsigned char m_bAcceptRemoteTraces; // offset 0x74, size 0x1
    class StreamManager * (* m_pfStreamManagerFactory)(); // offset 0x78, size 0x4
    class Job * m_pJobLogin; // offset 0x7C, size 0x4
    class Job * m_pJobLogout; // offset 0x80, size 0x4
    class Job * m_pJobTerminate; // offset 0x84, size 0x4
    class EffectiveLoginTimeout m_oEffectiveLoginTimeout; // offset 0x88, size 0x4
};
struct HostCredentials {
    // total size: 0x10
    class String m_strAddress; // offset 0x0, size 0x4
    unsigned short m_ui16Port; // offset 0x4, size 0x2
    class String m_strAccessKey; // offset 0x8, size 0x4
    class String m_strGuestAccountPassword; // offset 0xC, size 0x4
};
class SandboxConnectionInfo : public RootObject {
    // total size: 0x30
    struct HostCredentials m_hcDev; // offset 0x0, size 0x10
    struct HostCredentials m_hcCert; // offset 0x10, size 0x10
    struct HostCredentials m_hcProd; // offset 0x20, size 0x10
};
class NintendoClient : public BackEndServices {
    // total size: 0xC8
    class Job * m_pJobNintendoLogin; // offset 0x8C, size 0x4
    class Job * m_pJobNintendoTerminate; // offset 0x90, size 0x4
    class SandboxConnectionInfo m_sci; // offset 0x94, size 0x30
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class ServiceClient : public RootObject {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned int m_uiServiceID; // offset 0x4, size 0x4
    class StreamManager * m_pStreamManager; // offset 0x8, size 0x4
    class Credentials * m_pCredentials; // offset 0xC, size 0x4
    unsigned char m_bRegisteredProtocols; // offset 0x10, size 0x1
    unsigned char m_bUseLocalLoopback; // offset 0x11, size 0x1
    class qList m_lstRegisteredProtocols; // offset 0x14, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    unsigned int _M_data; // offset 0x8, size 0x4
};
class MemAllocator {
    // total size: 0x1
};
class _STLP_alloc_proxy : public MemAllocator {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class qList : public list, public RootObject {
    // total size: 0x8
};
class _DDL_ResultRange : public RootObject {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int m_uiOffset; // offset 0x4, size 0x4
    unsigned int m_uiSize; // offset 0x8, size 0x4
};
class ResultRange : public _DDL_ResultRange {
    // total size: 0xC
};
class MessagingProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class _Proto_MessageDeliveryProtocolServer : public ServerProtocol {
    // total size: 0x158
};
class MessageDeliveryServer : public _Proto_MessageDeliveryProtocolServer {
    // total size: 0x160
    class MessagingNotificationHandler * m_pMessagingNotificationHandler; // offset 0x158, size 0x4
};
class MessageDeliveryProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class CustomDataHolder : public AnyObjectHolder {
    // total size: 0x8
};
class MessagingClient : public ServiceClient {
    // total size: 0x1F8
    class MessagingProtocolClient m_oMessagingProtocolClient; // offset 0x1C, size 0x38
    class MessageDeliveryServer m_oMessageDeliveryServer; // offset 0x58, size 0x160
    class MessageDeliveryProtocolClient m_oMessageDeliveryClient; // offset 0x1B8, size 0x38
    unsigned char m_bClientUse; // offset 0x1F0, size 0x1
};
class Server : public MsgSource {
    // total size: 0xD4
    class String mAddress; // offset 0x1C, size 0xC
    int mPort; // offset 0x28, size 0x4
    unsigned char mLoggedIn; // offset 0x2C, size 0x1
    unsigned char mLoggingIn; // offset 0x2D, size 0x1
    const char * mKey; // offset 0x30, size 0x4
    class String mUsername; // offset 0x34, size 0xC
    unsigned char mDNSLookupComplete; // offset 0x40, size 0x1
    unsigned char mDoLogout; // offset 0x41, size 0x1
    class ProtocolCallContext * mExtraLoginCallback; // offset 0x44, size 0x4
    int mPadLoggingIn; // offset 0x48, size 0x4
    unsigned int mPlayerIDLoggingIn; // offset 0x4C, size 0x4
    unsigned int mPlayerIDs[4]; // offset 0x50, size 0x10
    class CriticalSection mLogoutCritSec; // offset 0x60, size 0x1C
    class NintendoClient * mBackEnd; // offset 0x7C, size 0x4
    class FriendsClient * mFriends; // offset 0x80, size 0x4
    class MessagingClient * mMessaging; // offset 0x84, size 0x4
    class Credentials * mClientCreds; // offset 0x88, size 0x4
    class ProtocolCallContext * mLoginCallback; // offset 0x8C, size 0x4
    class ProtocolCallContext * mLogoutCallback; // offset 0x90, size 0x4
    class MatchMakingClient * mMatchMaking; // offset 0x94, size 0x4
    class PersistentStoreClient * mPersistentStore; // offset 0x98, size 0x4
    class CompetitionClient * mCompetition; // offset 0x9C, size 0x4
    class CustomMatchMakingClient * mCustomMatchMaking; // offset 0xA0, size 0x4
    class NATTraversalClient * mNATTraversal; // offset 0xA4, size 0x4
};

