/*
    Compile unit: C:\rockband2\system\src\net\NetSession.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80529364 -> 0x8053163C
*/
class Symbol t; // size: 0x4, address: 0x80A53CC4
class Symbol t; // size: 0x4, address: 0x80A53CCC
class PseudoSingleton : public InstanceControl {
    // total size: 0x14
};
class ProductSpecifics {
    // total size: 0x0
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
class qList {
    // total size: 0x0
};
class SessionDescription : public RootObject {
    // total size: 0x44
protected:
    class String m_szSessionDiscoveryType; // offset 0x0, size 0x4
    class String m_szSessionDiscoveryContext; // offset 0x4, size 0x4
    class String m_szApplicationTitle; // offset 0x8, size 0x4
    unsigned int m_uiApplicationVersionNumber; // offset 0xC, size 0x4
    class String m_szStationURL; // offset 0x10, size 0x4
    unsigned int m_uiLibraryVersionNumber; // offset 0x14, size 0x4
    unsigned int m_uiLibraryBuildNumber; // offset 0x18, size 0x4
    class String m_szSessionName; // offset 0x1C, size 0x4
    unsigned int m_uiSessionID; // offset 0x20, size 0x4
    class qMap m_mapSessionAttributes; // offset 0x24, size 0x18
    void (* m_pfUpdateCallback)(); // offset 0x3C, size 0x4
    class SessionDiscoveryTable * m_pSessionDiscoveryTable; // offset 0x40, size 0x4
};
class SessionDiscoveryTable : public RootObject {
    // total size: 0x84
    class CriticalSection m_csSessionDiscovery; // offset 0x0, size 0x14
    class qList m_lstSessionDiscovery; // offset 0x14, size 0x8
    class SessionDiscoveryProtocol * m_pPrimarySessionDiscovery; // offset 0x1C, size 0x4
    class CriticalSection m_csSessionDescriptionList; // offset 0x20, size 0x14
    class qList * m_pSessionDescriptionList; // offset 0x34, size 0x4
    unsigned char (* m_pfSessionFilter)(class SessionDescription *); // offset 0x38, size 0x4
    class SessionDescription m_oLocalSession; // offset 0x3C, size 0x44
    unsigned char m_bSessionMaster; // offset 0x80, size 0x1
    unsigned char m_bReady; // offset 0x81, size 0x1
};
class SessionDiscoveryProtocol : public PluginObject {
    // total size: 0xC
protected:
    class SessionDiscoveryTable * m_pAssociatedSessionDiscoveryTable; // offset 0x8, size 0x4
};
class ChecksumAlgorithm : public PluginObject {
    // total size: 0xC
    unsigned char m_byTransmittedChecksumLength; // offset 0x8, size 0x1
};
class DiscoveryStream {
    // total size: 0x0
};
class LANSessionDiscovery : public SessionDiscoveryProtocol {
    // total size: 0x20
    class EncryptionAlgorithm * m_pEncryption; // offset 0xC, size 0x4
    class ChecksumAlgorithm * m_pChecksum; // offset 0x10, size 0x4
    class DiscoveryStream * m_pStream; // offset 0x14, size 0x4
    unsigned int m_uiLastNonce; // offset 0x18, size 0x4
    unsigned short m_ui16Port; // offset 0x1C, size 0x2
};
class UtilitySubsystem : public RootObject {
    // total size: 0x1
};
class ProductFacade : public PseudoSingleton {
    // total size: 0x20
protected:
    class ProductSpecifics * m_pProductSpecifics; // offset 0x14, size 0x4
    unsigned char m_bIsValid; // offset 0x18, size 0x1
    unsigned char m_bIsTerminated; // offset 0x19, size 0x1
    class LANSessionDiscovery * m_pLANSessionDiscovery; // offset 0x1C, size 0x4
};
class NetZ : public ProductFacade {
    // total size: 0x20
};
class QuazalSession {
    // total size: 0x8
    class NetZ * mNetZ; // offset 0x0, size 0x4
    class NetZCallback * mCallback; // offset 0x4, size 0x4
};
static class QuazalSession * gQNet; // size: 0x4, address: 0x80A53CD0
// Range: 0x80529364 -> 0x80529608
static void RegisterSessionMessages() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x80529608 -> 0x8052960C
static void DisconnectOnFail() {}

class NetSession * TheNetSession; // size: 0x4, address: 0x80A53CD4
// Range: 0x8052960C -> 0x80529998
void * NetSession::NetSession(class NetSession * const this /* r30 */) {
    // Local variables
    class DataArray * config; // r27

    // References
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> class PseudoGlobalVariable s_oStreamSettings[16];
    // -> unsigned int s_uiDefaultConnectionTimeout;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__10NetSession;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x80529998 -> 0x80529B60
void * NetSession::~NetSession(class NetSession * const this /* r30 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> static class QuazalSession * gQNet;
    // -> struct [anonymous] __vt__10NetSession;
}

// Range: 0x80529B60 -> 0x80529CB8
void NetSession::Reset(class NetSession * const this /* r29 */, int localHost /* r30 */, unsigned char async /* r31 */) {
    // References
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class AddPlayerResultMsg failureMsg; // size: 0x8, address: 0x80982020
static class Message disabledMsg; // size: 0x8, address: 0x80982038
// Range: 0x80529CB8 -> 0x8052A468
void NetSession::Clear(class NetSession * const this /* r28 */, unsigned char leavingEarly /* r29 */) {
    // Local variables
    class list locals; // r1+0xE0
    class list remotes; // r1+0xD8
    class list players; // r1+0xD0
    struct _List_iterator it; // r1+0x5C
    struct _List_iterator iter; // r1+0x58
    struct _List_iterator it; // r1+0x54
    class PlayerLeftMsg msg; // r1+0xC8
    struct _List_iterator it; // r1+0x50
    int n; // r29

    // References
    // -> static class Message disabledMsg;
    // -> class UserMgr * TheUserMgr;
    // -> class Net TheNet;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<P4User>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class QuazalSession * gQNet;
    // -> struct [anonymous] __vt__18AddPlayerResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class AddPlayerResultMsg failureMsg;
}

// Range: 0x8052A468 -> 0x8052A478
unsigned char NetSession::Disabled() {
    // References
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052A478 -> 0x8052A484
void NetSession::IgnoreRemoteMessages() {
    // References
    // -> class NetMessenger TheNetMessenger;
}

class SyncStartGameMsg : public Message {
    // total size: 0x8
};
static class SyncStartGameMsg start; // size: 0x8, address: 0x80982050
// Range: 0x8052A484 -> 0x8052A87C
void NetSession::Poll(class NetSession * const this /* r31 */) {
    // Local variables
    class JoinResponseMsg msg; // r1+0x44
    class vector clientsLeft; // r1+0x38
    int * it; // r29

    // References
    // -> static class QuazalSession * gQNet;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__16SyncStartGameMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SyncStartGameMsg start;
}

// Range: 0x8052A9C0 -> 0x8052AAC0
unsigned char NetSession::IsLocal(const class NetSession * const this /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x18

    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class QuazalSession * gQNet;
}

static class JoinResultMsg msg; // size: 0x8, address: 0x80982068
static class JoinResultMsg msg; // size: 0x8, address: 0x80982080
// Range: 0x8052AAC0 -> 0x8052B038
unsigned char NetSession::Join(class NetSession * const this /* r29 */, class NetSearchResult * result /* r28 */) {
    // References
    // -> static class JoinResultMsg msg;
    // -> struct [anonymous] __vt__13JoinResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class JoinResultMsg msg;
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052B038 -> 0x8052B418
class DataNode NetSession::OnMsg(class NetSession * const this /* r30 */, const class SessionReadyMsg & msg /* r28 */) {
    // Local variables
    class JoinResponseMsg response; // r1+0x90
    class list players; // r1+0x48
    class JoinRequestMsg request; // r1+0x50

    // References
    // -> class Net TheNet;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class NetMessenger TheNetMessenger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052B57C -> 0x8052B818
static void DenyRequest(unsigned int id /* r1+0x8 */, enum JoinResponseError err /* r30 */, int custom /* r31 */) {
    // Local variables
    class JoinResponseMsg failure; // r1+0x40
    class ProcessedJoinRequestMsg msg; // r1+0x38

    // References
    // -> class Net TheNet;
    // -> struct [anonymous] __vt__23ProcessedJoinRequestMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class NetMessenger TheNetMessenger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052B818 -> 0x8052B8F8
unsigned char NetSession::CheckJoinableHelper(class NetSession * const this /* r27 */, enum JoinResponseError & err /* r28 */, int & custom /* r29 */, int numPlayers /* r30 */, class BinStream & authData /* r31 */) {
    // Local variables
    int customError; // r1+0x8

    // References
    // -> class Net TheNet;
}

class SyncPlayerMsg : public NetMessage {
    // total size: 0x8
    int mPlayerNum; // offset 0x4, size 0x4
};
class SyncAllMsg : public NetMessage {
    // total size: 0x4
};
// Range: 0x8052B8F8 -> 0x8052B98C
void NetSession::UpdateSyncStore(class NetSession * const this /* r29 */) {
    // Local variables
    int machineID; // r30
    class SyncPlayerMsg syncPlayerMsg; // r1+0x10
    class SyncAllMsg syncAllMsg; // r1+0xC

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> struct [anonymous] __vt__10SyncAllMsg;
    // -> class SyncStore * TheSyncStore;
}

static class ProcessedJoinRequestMsg acceptedMsg; // size: 0x8, address: 0x80982098
// Range: 0x8052BA0C -> 0x8052C208
unsigned char NetSession::OnMsg(class NetSession * const this /* r28 */, const class JoinRequestMsg & msg /* r29 */) {
    // Local variables
    unsigned int machineID; // r1+0x54
    enum JoinResponseError err; // r1+0x50
    int custom; // r1+0x4C
    class MemStream authData; // r1+0xE0
    class JoinResponseMsg success; // r1+0x150
    class list joiners; // r1+0xB8
    int n; // r30
    int newID; // r27
    class User * newPlayer; // r26
    class MemStream playerData; // r1+0xC0
    class NewPlayerMsg playerMsg; // r1+0x128
    class NewRemotePlayerMsg newRemoteMsg; // r1+0xB0
    class list players; // r1+0xA8
    struct _List_iterator it; // r1+0x48
    class NewPlayerMsg playerMsg; // r1+0x100

    // References
    // -> struct [anonymous] __vt__23ProcessedJoinRequestMsg;
    // -> class Symbol t;
    // -> static class ProcessedJoinRequestMsg acceptedMsg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__18NewRemotePlayerMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<P4User>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Net TheNet;
    // -> class NetMessenger TheNetMessenger;
}

// Range: 0x8052C29C -> 0x8052C7D4
unsigned char NetSession::OnMsg(class NetSession * const this /* r30 */, class JoinResponseMsg & msg /* r31 */) {
    // Local variables
    class list locals; // r1+0x60
    struct _List_iterator it; // r1+0x24
    struct _List_iterator it; // r1+0x20
    int newID; // r28
    class MakeQuazalSessionJob * makeJob; // r28
    class JoinResultMsg resultMsg; // r1+0x58

    // References
    // -> struct [anonymous] __vt__13JoinResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class UserMgr * TheUserMgr;
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class MakeQuazalSessionJob : public Job {
    // total size: 0xC
    class QuazalSession * * mSessionAddress; // offset 0x8, size 0x4
};
static class AddPlayerResultMsg successMsg; // size: 0x8, address: 0x809820B0
// Range: 0x8052C7D4 -> 0x8052CD08
void NetSession::AddLocalPlayer(class NetSession * const this /* r29 */, int playerNum /* r30 */) {
    // Local variables
    class User * newPlayer; // r26
    class NewPlayerMsg addNew; // r1+0x50
    class AddPlayerRequestMsg requestMsg; // r1+0x78

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> struct [anonymous] __vt__18AddPlayerResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class AddPlayerResultMsg successMsg;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Net TheNet;
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052CDE0 -> 0x8052D1CC
unsigned char NetSession::OnMsg(class NetSession * const this /* r29 */, const class AddPlayerRequestMsg & msg /* r30 */) {
    // Local variables
    unsigned int machineID; // r1+0x28
    enum JoinResponseError err; // r1+0x24
    int custom; // r1+0x20
    class MemStream authData; // r1+0x90
    class AddPlayerResponseMsg denied; // r1+0x60
    int newID; // r31
    class User * newPlayer; // r28
    class MemStream playerData; // r1+0x70
    class NewPlayerMsg playerMsg; // r1+0xB0
    class NewRemotePlayerMsg newRemoteMsg; // r1+0x48
    class AddPlayerResponseMsg success; // r1+0x50

    // References
    // -> struct [anonymous] __vt__18NewRemotePlayerMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Net TheNet;
    // -> class NetMessenger TheNetMessenger;
}

static class AddPlayerResultMsg result; // size: 0x8, address: 0x809820C8
// Range: 0x8052D20C -> 0x8052D758
unsigned char NetSession::OnMsg(class NetSession * const this /* r29 */, const class AddPlayerResponseMsg & msg /* r30 */) {
    // Local variables
    class User * newUser; // r0

    // References
    // -> struct [anonymous] __vt__18AddPlayerResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class AddPlayerResultMsg result;
    // -> class Net TheNet;
    // -> class UserMgr * TheUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052D758 -> 0x8052DA6C
unsigned char NetSession::OnMsg(class NetSession * const this /* r31 */, const class NewPlayerMsg & msg /* r29 */) {
    // Local variables
    class User * newPlayer; // r30
    class MemStream playerData; // r1+0x38
    class NewRemotePlayerMsg newRemote; // r1+0x30

    // References
    // -> struct [anonymous] __vt__18NewRemotePlayerMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Net TheNet;
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052DA6C -> 0x8052DB98
void NetSession::RemoveLocalPlayer(class NetSession * const this /* r29 */, int id /* r30 */) {
    // Local variables
    class User * playerData; // r31
    class PlayerLeftMsg removeMsg; // r1+0x10

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> static class QuazalSession * gQNet;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052DB98 -> 0x8052DBF8
unsigned char NetSession::OnMsg(class NetSession * const this /* r31 */) {}

// Range: 0x8052DBF8 -> 0x8052DE54
void NetSession::ProcessPlayerLeftMsg(class NetSession * const this /* r31 */, const class PlayerLeftMsg & msg /* r29 */) {
    // Local variables
    class User * playerData; // r0
    class RemotePlayerLeftMsg remoteLeftMsg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__19RemotePlayerLeftMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StartLoadingMsg : public Message {
    // total size: 0x8
};
// Range: 0x8052DE54 -> 0x8052E108
void NetSession::CheckAllReady(class NetSession * const this /* r31 */) {
    // Local variables
    class list players; // r1+0x68
    struct _List_iterator it; // r1+0x38
    class BeginLoadingMsg msg; // r1+0x34
    class StartLoadingMsg startLoading; // r1+0x60

    // References
    // -> struct [anonymous] __vt__15StartLoadingMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__15BeginLoadingMsg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052E1CC -> 0x8052E328
void NetSession::PopulateLoadingList(class NetSession * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x24
    unsigned char found; // r30
    unsigned int * iter; // r29

    // References
    // -> class Net TheNet;
}

// Range: 0x8052E328 -> 0x8052E56C
unsigned char NetSession::OnMsg(class NetSession * const this /* r31 */) {
    // Local variables
    class StartLoadingMsg startLoading; // r1+0x20

    // References
    // -> struct [anonymous] __vt__15StartLoadingMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052E56C -> 0x8052E5E0
void NetSession::DoneLoading(class NetSession * const this /* r30 */) {
    // Local variables
    unsigned int myID; // r31
    class FinishedLoadingMsg msg; // r1+0x8

    // References
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052E620 -> 0x8052E648
unsigned char NetSession::OnMsg() {}

// Range: 0x8052E648 -> 0x8052E728
void NetSession::SetDoneLoading(class NetSession * const this /* r31 */) {
    // Local variables
    unsigned int * it; // r6

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052E728 -> 0x8052E864
void NetSession::CheckAllLoaded(class NetSession * const this /* r29 */) {
    // Local variables
    class StartGameOnTimeMsg msg; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052E8A4 -> 0x8052E9A0
unsigned char NetSession::OnMsg(class NetSession * const this /* r29 */, const class StartGameOnTimeMsg & msg /* r30 */) {
    // References
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052E9A0 -> 0x8052EAE4
class DataNode NetSession::OnEndGame(class NetSession * const this /* r28 */, class DataArray * msg /* r29 */) {}

// Range: 0x8052EAE4 -> 0x8052ED88
void NetSession::EndGame(class NetSession * const this /* r31 */, int result /* r28 */, unsigned char reportResult /* r29 */, unsigned char leavingEarly /* r30 */) {
    // Local variables
    class EndGameMsg msg; // r1+0x44
    class GameEndedMsg gameEnded; // r1+0x30
    class EndGameMsg msg; // r1+0x38

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> struct [anonymous] __vt__12GameEndedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052EDC8 -> 0x8052F010
unsigned char NetSession::OnMsg(class NetSession * const this /* r31 */, const class EndGameMsg & msg /* r30 */) {
    // Local variables
    class GameEndedMsg gameEnded; // r1+0x28

    // References
    // -> struct [anonymous] __vt__12GameEndedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052F010 -> 0x8052F074
int NetSession::GetLocalHost(const class NetSession * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052F074 -> 0x8052F08C
unsigned char NetSession::HasPlayer() {
    // References
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052F08C -> 0x8052F0EC
unsigned char NetSession::IsPlayerIdInList() {
    // Local variables
    struct _List_iterator it; // r1+0x18
}

// Range: 0x8052F0EC -> 0x8052F1E4
void NetSession::GetLocalPlayers(const class NetSession * const this /* r29 */, class list & locals /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<P4User>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Net TheNet;
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052F1E4 -> 0x8052F2C8
void NetSession::GetUserList(const class NetSession * const this /* r29 */, class list & players /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<P4User>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Net TheNet;
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052F2C8 -> 0x8052F3B0
unsigned char NetSession::IsLocalPlayer(const class NetSession * const this /* r29 */, int id /* r30 */) {
    // References
    // -> class Net TheNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052F3B0 -> 0x8052F44C
int NetSession::NumLocalPlayers() {
    // Local variables
    class list locals; // r1+0x30
}

// Range: 0x8052F44C -> 0x8052F4D8
int NetSession::NumOpenSlots() {
    // References
    // -> class Net TheNet;
}

static class SessionBusyMsg msg; // size: 0x8, address: 0x809820E0
// Range: 0x8052F4D8 -> 0x8052F65C
void NetSession::SetBusy(class NetSession * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14SessionBusyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SessionBusyMsg msg;
}

// Range: 0x8052F65C -> 0x8052F6FC
int NetSession::GetNewPlayerID(class NetSession * const this /* r30 */) {
    // Local variables
    int n; // r31

    // References
    // -> class Debug TheDebug;
    // -> class UserMgr * TheUserMgr;
}

// Range: 0x8052F6FC -> 0x8052F7B4
void NetSession::SetAllLocalReadyStatus(unsigned char bReady /* r31 */) {
    // Local variables
    class list locals; // r1+0x28
    struct _List_iterator it; // r1+0x10
    class User * pPlayer; // r3
}

// Range: 0x8052F7B4 -> 0x8052F938
void NetSession::UpdateUserData(class NetSession * const this /* r28 */, int userNum /* r29 */, unsigned int dirtyMask /* r30 */) {
    // Local variables
    class ChangePlayerMsg changePlayer; // r1+0x10

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> class Net TheNet;
    // -> static class QuazalSession * gQNet;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8052F9CC -> 0x8052FC60
unsigned char NetSession::OnMsg(class NetSession * const this /* r31 */, const class ChangePlayerMsg & msg /* r29 */) {
    // Local variables
    class User * updated; // r30
    class MemStream playerData; // r1+0x38

    // References
    // -> struct [anonymous] __vt__22RemotePlayerChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Net TheNet;
}

// Range: 0x8052FC60 -> 0x8052FD0C
void NetSession::SendMsg(class NetMessage & msg /* r30 */, enum PacketType isReliable /* r31 */) {
    // Local variables
    unsigned int destMachine; // r1+0x8

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052FD0C -> 0x8052FD24
void NetSession::SendMsgToAll() {
    // References
    // -> static class QuazalSession * gQNet;
}

// Range: 0x8052FD24 -> 0x8052FE00
class DataNode NetSession::OnSendMsg(class NetSession * const this /* r28 */, class DataArray * msg /* r29 */) {
    // Local variables
    class DataArrayMsg message; // r1+0xC
}

// Range: 0x8052FE00 -> 0x8052FED0
class DataNode NetSession::OnSendMsgToAll(class NetSession * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    class DataArrayMsg message; // r1+0xC
}

// Range: 0x8052FED0 -> 0x80530160
void NetSession::SendToAllClientsExcept(class NetSession * const this /* r28 */, const class NetMessage & msg /* r30 */, enum PacketType isReliable /* r31 */, unsigned int except /* r1+0x8 */) {
    // Local variables
    class vector sent; // r1+0x50
    class list players; // r1+0x48
    struct _List_iterator it; // r1+0x30
    unsigned char found; // r4
    unsigned int * iter; // r5

    // References
    // -> class NetMessenger TheNetMessenger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class QuazalSession * gQNet;
}

// Range: 0x80530160 -> 0x805301F4
void NetSession::AddLocalToSession(class NetSession * const this /* r30 */, class User * playerData /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x805301F4 -> 0x8053026C
void NetSession::AddRemoteToSession() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8053026C -> 0x80530300
void NetSession::RemoveLocalFromSession() {}

// Range: 0x80530300 -> 0x80530394
void NetSession::RemoveRemoteFromSession() {}

// Range: 0x80530394 -> 0x805303FC
void NetSession::StartSession(class NetSession * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805303FC -> 0x80530484
void NetSession::EndSession(class NetSession * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80530484 -> 0x805305D0
void NetSession::RemoveClient(class NetSession * const this /* r29 */, unsigned int machineID /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x20
    class PlayerLeftMsg msg; // r1+0x28

    // References
    // -> class Net TheNet;
    // -> class NetMessenger TheNetMessenger;
}

// Range: 0x805305D0 -> 0x80530614
unsigned char NetSession::IsHost() {
    // References
    // -> static class QuazalSession * gQNet;
}

// Range: 0x80530614 -> 0x80530B5C
void NetSession::HandleSessionMsg(class NetSession * const this /* r27 */, class SessionMsg * msg /* r28 */) {
    // Local variables
    int byteCode; // r29

    // References
    // -> struct [anonymous] __RTTI__12VoiceDataMsg;
    // -> struct [anonymous] __RTTI__10EndGameMsg;
    // -> struct [anonymous] __RTTI__18StartGameOnTimeMsg;
    // -> struct [anonymous] __RTTI__18FinishedLoadingMsg;
    // -> struct [anonymous] __RTTI__15BeginLoadingMsg;
    // -> struct [anonymous] __RTTI__15ChangePlayerMsg;
    // -> struct [anonymous] __RTTI__13PlayerLeftMsg;
    // -> struct [anonymous] __RTTI__20AddPlayerResponseMsg;
    // -> struct [anonymous] __RTTI__19AddPlayerRequestMsg;
    // -> struct [anonymous] __RTTI__12NewPlayerMsg;
    // -> struct [anonymous] __RTTI__15JoinResponseMsg;
    // -> struct [anonymous] __RTTI__10SessionMsg;
    // -> struct [anonymous] __RTTI__14JoinRequestMsg;
    // -> class NetMessageFactory TheNetMessageFactory;
}

static class Symbol _s; // size: 0x4, address: 0x80A53CE4
static class Symbol _s; // size: 0x4, address: 0x80A53CEC
static class Symbol _s; // size: 0x4, address: 0x80A53CF4
static class Symbol _s; // size: 0x4, address: 0x80A53CFC
static class Symbol _s; // size: 0x4, address: 0x80A53D04
static class Symbol _s; // size: 0x4, address: 0x80A53D0C
static class Symbol _s; // size: 0x4, address: 0x80A53D14
static class Symbol _s; // size: 0x4, address: 0x80A53D1C
static class Symbol _s; // size: 0x4, address: 0x80A53D24
static class Symbol _s; // size: 0x4, address: 0x80A53D2C
static class Symbol _s; // size: 0x4, address: 0x80A53D34
static class Symbol _s; // size: 0x4, address: 0x80A53D3C
static class Symbol _s; // size: 0x4, address: 0x80A53D44
static class Symbol _s; // size: 0x4, address: 0x80A53D4C
static class Symbol _s; // size: 0x4, address: 0x80A53D54
static class Symbol _s; // size: 0x4, address: 0x80A53D5C
static class Symbol _s; // size: 0x4, address: 0x80A53D64
static class Symbol _s; // size: 0x4, address: 0x80A53D6C
static class Symbol _s; // size: 0x4, address: 0x80A53D74
static class Symbol _s; // size: 0x4, address: 0x80A53D7C
// Range: 0x80530B5C -> 0x8053163C
class DataNode NetSession::Handle(class NetSession * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

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
}

struct {
    // total size: 0xBC
} __vt__10NetSession; // size: 0xBC, address: 0x80905FC4
struct {
    // total size: 0x8
} __RTTI__10NetSession; // size: 0x8, address: 0x809060A8
struct {
    // total size: 0x8
} __RTTI__12VoiceDataMsg; // size: 0x8, address: 0x809060D8
struct {
    // total size: 0x8
} __RTTI__10EndGameMsg; // size: 0x8, address: 0x80906100
struct {
    // total size: 0x8
} __RTTI__18StartGameOnTimeMsg; // size: 0x8, address: 0x80906130
struct {
    // total size: 0x8
} __RTTI__18FinishedLoadingMsg; // size: 0x8, address: 0x80906160
struct {
    // total size: 0x28
} __vt__15BeginLoadingMsg; // size: 0x28, address: 0x80906168
struct {
    // total size: 0x8
} __RTTI__15BeginLoadingMsg; // size: 0x8, address: 0x809061B8
struct {
    // total size: 0x8
} __RTTI__15ChangePlayerMsg; // size: 0x8, address: 0x809061E8
struct {
    // total size: 0x8
} __RTTI__20AddPlayerResponseMsg; // size: 0x8, address: 0x80906220
struct {
    // total size: 0x8
} __RTTI__19AddPlayerRequestMsg; // size: 0x8, address: 0x80906250
struct {
    // total size: 0x8
} __RTTI__13PlayerLeftMsg; // size: 0x8, address: 0x80906280
struct {
    // total size: 0x8
} __RTTI__12NewPlayerMsg; // size: 0x8, address: 0x809062B0
struct {
    // total size: 0x8
} __RTTI__15JoinResponseMsg; // size: 0x8, address: 0x809062E0
struct {
    // total size: 0x8
} __RTTI__14JoinRequestMsg; // size: 0x8, address: 0x80906310
struct {
    // total size: 0x8
} __RTTI__10SessionMsg; // size: 0x8, address: 0x80906330
struct {
    // total size: 0xC
} __vt__16SyncStartGameMsg; // size: 0xC, address: 0x809063A8
struct {
    // total size: 0x8
} __RTTI__16SyncStartGameMsg; // size: 0x8, address: 0x809063D8
struct {
    // total size: 0xC
} __vt__15StartLoadingMsg; // size: 0xC, address: 0x809063E0
struct {
    // total size: 0x8
} __RTTI__15StartLoadingMsg; // size: 0x8, address: 0x80906410
class PseudoGlobalVariable s_oStreamSettings[16]; // size: 0xB00, address: 0x80A44148
unsigned int s_uiDefaultConnectionTimeout; // size: 0x4, address: 0x80A487CC

