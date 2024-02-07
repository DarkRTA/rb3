/*
    Compile unit: C:\rockband2\system\src\net\Jobs_RV.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80522B0C -> 0x80524348
*/
class RVJob : public Job {
    // total size: 0xC
protected:
    class ProtocolCallContext * mAsync; // offset 0x8, size 0x4
};
// Range: 0x80522B0C -> 0x80522B60
void * RVJob::RVJob(class RVJob * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__5RVJob;
}

// Range: 0x80522B60 -> 0x80522BE0
void * RVJob::~RVJob(class RVJob * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__5RVJob;
}

// Range: 0x80522BE0 -> 0x80522C44
unsigned char RVJob::IsFinished(class RVJob * const this /* r31 */) {
    // References
    // -> class Net TheNet;
}

// Range: 0x80522C44 -> 0x80522C98
void RVJob::Cancel(class RVJob * const this /* r31 */) {}

class RVSessionData : public SessionData {
    // total size: 0xC
    unsigned int mGatheringID; // offset 0x4, size 0x4
    unsigned int mHostID; // offset 0x8, size 0x4
};
enum /* @enum$23092Jobs_RV_cpp */ {
    kRegister = 0,
    kParticipate = 1,
    kLaunch = 2,
    kSuccess = 3,
    kFail = 4,
};
class MakeSessionJob : public Job {
    // total size: 0x18
    class AnyObjectHolder * mGathering; // offset 0x8, size 0x4
    class RVSessionData * mData; // offset 0xC, size 0x4
    class ProtocolCallContext * mAsync; // offset 0x10, size 0x4
    enum /* @enum$23092Jobs_RV_cpp */ {
        kRegister = 0,
        kParticipate = 1,
        kLaunch = 2,
        kSuccess = 3,
        kFail = 4,
    } mState; // offset 0x14, size 0x4
};
// Range: 0x80522C98 -> 0x80522D14
void * MakeSessionJob::MakeSessionJob(class MakeSessionJob * const this /* r29 */, class AnyObjectHolder * gathering /* r30 */, class RVSessionData * data /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14MakeSessionJob;
}

// Range: 0x80522D14 -> 0x80522D94
void * MakeSessionJob::~MakeSessionJob(class MakeSessionJob * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__14MakeSessionJob;
}

// Range: 0x80522D94 -> 0x80522E54
void MakeSessionJob::Start(class MakeSessionJob * const this /* r30 */) {
    // Local variables
    unsigned char success; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

static class SessionReadyMsg msg; // size: 0x8, address: 0x80981B08
// Range: 0x80522E54 -> 0x80523050
void MakeSessionJob::Cancel(class MakeSessionJob * const this /* r31 */, class Object * callback /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SessionReadyMsg msg;
}

// Range: 0x80523050 -> 0x8052321C
void MakeSessionJob::OnCompletion(class Object * callback /* r31 */) {
    // Local variables
    class SessionReadyMsg msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

class MakeOfflineSessionJob : public Job {
    // total size: 0x8
};
// Range: 0x8052321C -> 0x80523224
unsigned char MakeOfflineSessionJob::IsFinished() {}

static class SessionReadyMsg msg; // size: 0x8, address: 0x80981B20
// Range: 0x80523224 -> 0x805233F4
void MakeOfflineSessionJob::Cancel(class Object * callback /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SessionReadyMsg msg;
}

static class SessionReadyMsg msg; // size: 0x8, address: 0x80981B38
// Range: 0x805233F4 -> 0x805235CC
void MakeOfflineSessionJob::OnCompletion(class Object * callback /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SessionReadyMsg msg;
}

enum /* @enum$23108Jobs_RV_cpp */ {
    kParticipate = 0,
    kRequestURLs = 1,
    kJoin = 2,
    kSuccess = 3,
    kFail = 4,
};
class JoinSessionJob : public Job {
    // total size: 0x14
    class RVSessionData * mData; // offset 0x8, size 0x4
    class ProtocolCallContext * mAsync; // offset 0xC, size 0x4
    enum /* @enum$23108Jobs_RV_cpp */ {
        kParticipate = 0,
        kRequestURLs = 1,
        kJoin = 2,
        kSuccess = 3,
        kFail = 4,
    } mState; // offset 0x10, size 0x4
};
// Range: 0x805235CC -> 0x80523638
void * JoinSessionJob::JoinSessionJob(class JoinSessionJob * const this /* r30 */, class RVSessionData * data /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14JoinSessionJob;
}

// Range: 0x80523638 -> 0x805236B8
void * JoinSessionJob::~JoinSessionJob(class JoinSessionJob * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__14JoinSessionJob;
}

// Range: 0x805236B8 -> 0x80523794
void JoinSessionJob::Start(class JoinSessionJob * const this /* r30 */) {
    // Local variables
    unsigned char success; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

static class qList urls; // size: 0x8, address: 0x80981B50
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
class Credentials : public RefCountedObject {
    // total size: 0x30
    unsigned int m_idPrincipal; // offset 0x8, size 0x4
    unsigned int m_idConnection; // offset 0xC, size 0x4
    class String m_strUserName; // offset 0x10, size 0x4
    class String m_strPassword; // offset 0x14, size 0x4
    class StreamManager * m_pStreamManager; // offset 0x18, size 0x4
    class EndPoint * m_pAuthenticationConnection; // offset 0x1C, size 0x4
    class EndPoint * m_pRegularSecureConnection; // offset 0x20, size 0x4
    class EndPoint * m_pSpecialSecureConnection; // offset 0x24, size 0x4
    class qList m_lstSpecialProtocols; // offset 0x28, size 0x8
};
class SecureConnectionProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class SecureConnectionClient : public ServiceClient {
    // total size: 0x54
    class SecureConnectionProtocolClient m_oProtocol; // offset 0x1C, size 0x38
};
// Range: 0x80523794 -> 0x80523970
unsigned char JoinSessionJob::IsFinished(class JoinSessionJob * const this /* r31 */) {
    // Local variables
    unsigned char callReturn; // r30
    class SecureConnectionClient * scClient; // r29

    // References
    // -> class Debug TheDebug;
    // -> static class qList urls;
    // -> class Net TheNet;
}

static class SessionReadyMsg msg; // size: 0x8, address: 0x80981B68
// Range: 0x80523970 -> 0x80523B8C
void JoinSessionJob::Cancel(class JoinSessionJob * const this /* r31 */, class Object * callback /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class SessionReadyMsg msg;
}

// Range: 0x80523B8C -> 0x80523D58
void JoinSessionJob::OnCompletion(class Object * callback /* r31 */) {
    // Local variables
    class SessionReadyMsg msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

class UpdateSettingsJob : public RVJob {
    // total size: 0x10
    class AnyObjectHolder * mGathering; // offset 0xC, size 0x4
};
// Range: 0x80523D58 -> 0x80523DA4
void * UpdateSettingsJob::UpdateSettingsJob(class UpdateSettingsJob * const this /* r30 */, class AnyObjectHolder * gathering /* r31 */) {
    // References
    // -> struct [anonymous] __vt__17UpdateSettingsJob;
}

// Range: 0x80523DA4 -> 0x80523E4C
void UpdateSettingsJob::Start(class UpdateSettingsJob * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

static class Message msg; // size: 0x8, address: 0x80981B80
// Range: 0x80523E4C -> 0x8052402C
void UpdateSettingsJob::Cancel(class UpdateSettingsJob * const this /* r30 */, class Object * callback /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80981B98
// Range: 0x8052402C -> 0x80524254
void UpdateSettingsJob::OnCompletion(class UpdateSettingsJob * const this /* r30 */, class Object * callback /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

class ChangeSessionStateJob : public RVJob {
    // total size: 0x14
    unsigned int mSessionID; // offset 0xC, size 0x4
    unsigned int mStateFlags; // offset 0x10, size 0x4
};
// Range: 0x80524254 -> 0x805242B0
void * ChangeSessionStateJob::ChangeSessionStateJob(class ChangeSessionStateJob * const this /* r29 */, unsigned int sessionID /* r30 */, unsigned int stateFlags /* r31 */) {
    // References
    // -> struct [anonymous] __vt__21ChangeSessionStateJob;
}

// Range: 0x805242B0 -> 0x80524348
void ChangeSessionStateJob::Start(class ChangeSessionStateJob * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

struct {
    // total size: 0x1C
} __vt__21ChangeSessionStateJob; // size: 0x1C, address: 0x80904DA0
struct {
    // total size: 0x8
} __RTTI__21ChangeSessionStateJob; // size: 0x8, address: 0x80904DE8
struct {
    // total size: 0x1C
} __vt__17UpdateSettingsJob; // size: 0x1C, address: 0x80904DF0
struct {
    // total size: 0x8
} __RTTI__17UpdateSettingsJob; // size: 0x8, address: 0x80904E38
struct {
    // total size: 0x1C
} __vt__14JoinSessionJob; // size: 0x1C, address: 0x80904E40
struct {
    // total size: 0x8
} __RTTI__14JoinSessionJob; // size: 0x8, address: 0x80904E78
struct {
    // total size: 0x1C
} __vt__21MakeOfflineSessionJob; // size: 0x1C, address: 0x80904E80
struct {
    // total size: 0x8
} __RTTI__21MakeOfflineSessionJob; // size: 0x8, address: 0x80904EC0
struct {
    // total size: 0x1C
} __vt__14MakeSessionJob; // size: 0x1C, address: 0x80904EC8
struct {
    // total size: 0x8
} __RTTI__14MakeSessionJob; // size: 0x8, address: 0x80904F00
struct {
    // total size: 0x1C
} __vt__5RVJob; // size: 0x1C, address: 0x80904F08
struct {
    // total size: 0x8
} __RTTI__5RVJob; // size: 0x8, address: 0x80904F38
class MatchMakingProtocolClient : public ClientProtocol {
    // total size: 0x38
};
class MatchMakingProtocolExtClient : public ClientProtocol {
    // total size: 0x38
};
class MatchMakingClient : public ServiceClient {
    // total size: 0x8C
    class MatchMakingProtocolClient m_oProtocol; // offset 0x1C, size 0x38
    class MatchMakingProtocolExtClient m_oProtocolExt; // offset 0x54, size 0x38
};

