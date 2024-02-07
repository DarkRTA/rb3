/*
    Compile unit: C:\rockband2\system\src\net\Server.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80534400 -> 0x80536C94
*/
const char * kGuestPassword; // size: 0x4, address: 0x80A474F0
const char * kPassword; // size: 0x4, address: 0x80A474F4
static class Symbol signin_changed; // size: 0x4, address: 0x80A53DBC
class FriendsProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class FriendsClient : public ServiceClient {
    // total size: 0x54
    class FriendsProtocolClient m_oProtocol; // offset 0x1C, size 0x38
};
class _Proto_NATTraversalProtocolServer : public ServerProtocol {
    // total size: 0x158
};
class NATTraversalProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class NATTraversalRelayProtocol : public _Proto_NATTraversalProtocolServer {
    // total size: 0x160
    class NATTraversalProtocolClient * m_pClient; // offset 0x158, size 0x4
};
class NATTraversalEngine {
    // total size: 0x0
};
class NATRelayInterface : public RootObject {
    // total size: 0x8
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    class NATTraversalEngine * m_pEngine; // offset 0x4, size 0x4
};
class RVNATRelay : public NATRelayInterface {
    // total size: 0xC
    class NATTraversalRelayClient * m_pClient; // offset 0x8, size 0x4
};
class NATTraversalRelayClient : public NATTraversalRelayProtocol {
    // total size: 0x168
    class RVNATRelay m_oRelayInterface; // offset 0x15C, size 0xC
};
class NATEchoInterface : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RVNATEcho : public NATEchoInterface {
    // total size: 0x5C
    class StationURL m_oStreamURL; // offset 0x4, size 0x58
};
class ConnectivityTester : public RootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class RVConnectivityTester : public ConnectivityTester {
    // total size: 0x4
};
class NATTraversalClient : public ServiceClient {
    // total size: 0x1E8
    class NATTraversalRelayClient m_oRelayClient; // offset 0x20, size 0x168
    class RVNATEcho m_oEcho; // offset 0x188, size 0x5C
    class RVConnectivityTester m_oTester; // offset 0x1E4, size 0x4
};
// Range: 0x80534400 -> 0x805347BC
void * Server::Server(class Server * const this /* r30 */) {
    // Local variables
    class DataArray * config; // r28
    int n; // r5

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> static class Symbol signin_changed;
    // -> const char * kGuestPassword;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__6Server;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x805347BC -> 0x8053493C
void * Server::~Server(class Server * const this /* r29 */) {
    // Local variables
    class ProtocolCallContext context; // r1+0x10

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__6Server;
}

static class ServerStatusChangedMsg ServerStatusMsg; // size: 0x8, address: 0x809820F8
static class UserLoginMsg loginMsg; // size: 0x8, address: 0x80982110
static class ServerStatusChangedMsg msg; // size: 0x8, address: 0x80982128
static class UserLoginMsg loginMsg; // size: 0x8, address: 0x80982140
class StringStream : public RootObject {
    // total size: 0x110
    char * m_szBuffer; // offset 0x0, size 0x4
    unsigned int m_uiSize; // offset 0x4, size 0x4
    char * m_szCurrentPosition; // offset 0x8, size 0x4
    char m_szInitialBuffer[256]; // offset 0xC, size 0x100
    unsigned char m_bHex; // offset 0x10C, size 0x1
    unsigned char m_bShowBase; // offset 0x10D, size 0x1
    unsigned char m_bBoolAlpha; // offset 0x10E, size 0x1
};
// Range: 0x8053493C -> 0x80535868
void Server::Poll(class Server * const this /* r29 */) {
    // Local variables
    class StringStream __ss; // r1+0x190
    class qResult err; // r1+0xF0
    class ProtocolCallContext context; // r1+0x130
    unsigned char success; // r27
    class String result; // r1+0xE4
    unsigned char ret; // r0

    // References
    // -> static class UserLoginMsg loginMsg;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class ServerStatusChangedMsg msg;
    // -> const char * kPassword;
    // -> const char * kGuestPassword;
    // -> struct [anonymous] __vt__12UserLoginMsg;
    // -> class Symbol t;
    // -> static class UserLoginMsg loginMsg;
    // -> struct [anonymous] __vt__22ServerStatusChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ServerStatusChangedMsg ServerStatusMsg;
    // -> struct [anonymous] __vt__Q26Quazal17HarmonixGathering;
    // -> struct [anonymous] __vt__Q26Quazal22_DDL_HarmonixGathering;
    // -> struct [anonymous] __vt__Q26Quazal23CustomMatchMakingClient;
    // -> class Debug TheDebug;
}

enum NWC24Err {
    NWC24_OK = 0,
    NWC24_ERR_FATAL = -1,
    NWC24_ERR_FAILED = -2,
    NWC24_ERR_INVALID_VALUE = -3,
    NWC24_ERR_NOT_SUPPORTED = -4,
    NWC24_ERR_NULL = -5,
    NWC24_ERR_FULL = -6,
    NWC24_ERR_PROTECTED = -7,
    NWC24_ERR_OVERFLOW = -8,
    NWC24_ERR_LIB_NOT_OPENED = -9,
    NWC24_ERR_LIB_OPENED = -10,
    NWC24_ERR_NOMEM = -11,
    NWC24_ERR_CONFIG = -12,
    NWC24_ERR_NOT_FOUND = -13,
    NWC24_ERR_BROKEN = -14,
    NWC24_ERR_DONE = -15,
    NWC24_ERR_FILE_OPEN = -16,
    NWC24_ERR_FILE_CLOSE = -17,
    NWC24_ERR_FILE_READ = -18,
    NWC24_ERR_FILE_WRITE = -19,
    NWC24_ERR_FILE_NOEXISTS = -20,
    NWC24_ERR_FILE_OTHER = -21,
    NWC24_ERR_MUTEX = -22,
    NWC24_ERR_ALIGNMENT = -23,
    NWC24_ERR_FORMAT = -24,
    NWC24_ERR_STRING_END = -25,
    NWC24_ERR_BUSY = -26,
    NWC24_ERR_VER_MISMATCH = -27,
    NWC24_ERR_HIDDEN = -28,
    NWC24_ERR_INPROGRESS = -29,
    NWC24_ERR_NOT_READY = -30,
    NWC24_ERR_NETWORK = -31,
    NWC24_ERR_SERVER = -32,
    NWC24_ERR_CONFIG_NETWORK = -33,
    NWC24_ERR_ID_NOEXISTS = -34,
    NWC24_ERR_ID_GENERATED = -35,
    NWC24_ERR_ID_REGISTERED = -36,
    NWC24_ERR_ID_CRC = -37,
    NWC24_ERR_NAND_CORRUPT = -38,
    NWC24_ERR_DISABLED = -39,
    NWC24_ERR_INVALID_OPERATION = -40,
    NWC24_ERR_FILE_EXISTS = -41,
    NWC24_ERR_INTERNAL_IPC = -42,
    NWC24_ERR_INTERNAL_VF = -43,
    NWC24_ERR_ID_NOT_REGISTERED = -44,
    NWC24_ERR_VERIFY_SIGNATURE = -45,
    NWC24_ERR_FILE_BROKEN = -46,
    NWC24_ERR_INVALID_CHAR = -47,
    NWC24_ERR_CANCELLED = -48,
    NWC24_ERR_OLD_SYSTEM = -49,
    NWC24_ERR_SCRIPT_VERSION = -50,
    NWC24_ERR_GIVE_UP = -51,
};
// Range: 0x80535868 -> 0x80535DFC
void Server::Login(class Server * const this /* r31 */) {
    // Local variables
    unsigned long long wiiNumber; // r1+0x60
    enum NWC24Err nwc24Err; // r4
    class StringStream strUserName; // r1+0x68
    unsigned char success; // r27

    // References
    // -> const char * kGuestPassword;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__22ServerStatusChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

// Range: 0x80535DFC -> 0x80535E20
void Server::Logout() {}

static class ServerStatusChangedMsg msg; // size: 0x8, address: 0x80982158
// Range: 0x80535E20 -> 0x80536290
void Server::LogoutImpl(class Server * const this /* r29 */, unsigned char sendMsg /* r30 */) {
    // Local variables
    int n; // r5

    // References
    // -> struct [anonymous] __vt__22ServerStatusChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ServerStatusChangedMsg msg;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80536290 -> 0x80536298
unsigned char Server::IsConnected() {}

// Range: 0x80536298 -> 0x805362DC
unsigned int Server::GetPlayerID(class Server * const this /* r31 */) {}

// Range: 0x805362DC -> 0x80536320
char * Server::GetUsername() {}

// Range: 0x80536320 -> 0x8053640C
void Server::GetAllPlayerIDs(class Server * const this /* r29 */, class vector & ids /* r30 */) {
    // Local variables
    unsigned int id; // r1+0x18
}

// Range: 0x8053640C -> 0x80536474
class SecureConnectionClient * Server::GetSecureConnectionClient(class Server * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80536474 -> 0x805364B0
void Server::DoAdditionalLogin(class Server * const this /* r31 */) {}

// Range: 0x805364B0 -> 0x80536584
class DataNode Server::OnMsg(class Server * const this /* r28 */, const class SigninChangedMsg & msg /* r29 */) {
    // Local variables
    int n; // r30

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80536584 -> 0x8053658C
void Server::SetUsername() {}

static class Symbol _s; // size: 0x4, address: 0x80A53DC8
static class Symbol _s; // size: 0x4, address: 0x80A53DD0
static class Symbol _s; // size: 0x4, address: 0x80A53DD8
// Range: 0x8053658C -> 0x80536C94
class DataNode Server::Handle(class Server * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__16SigninChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x6C
} __vt__6Server; // size: 0x6C, address: 0x809073A8
struct {
    // total size: 0x8
} __RTTI__6Server; // size: 0x8, address: 0x80907438

