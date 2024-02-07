/*
    Compile unit: C:\rockband2\system\src\net\MessageBroker.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805255B0 -> 0x8052642C
*/
static class CriticalSection gMessageLock; // size: 0x1C, address: 0x80981BC4
static unsigned char gRefuseMessages; // size: 0x1, address: 0x80A474B9
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gMessages; // size: 0xC, address: 0x80981BEC
static unsigned char gLogging; // size: 0x1, address: 0x80A53C88
static class Timer gTime; // size: 0x38, address: 0x80981BF8
static float gIncomingBytes; // size: 0x4, address: 0x80A53C8C
static float gOutgoingBytes; // size: 0x4, address: 0x80A53C90
static float gLastPing; // size: 0x4, address: 0x80A53C94
// Range: 0x805255B0 -> 0x80525614
static class DataNode SetBandwidthLogging(class DataArray * msg /* r31 */) {
    // References
    // -> static unsigned char gLogging;
}

static class MessageBroker * TheBroker; // size: 0x4, address: 0x80A53C98
class MessageBroker : public _DO_MessageBroker {
    // total size: 0x8C
    class vector mClientStampMap; // offset 0x74, size 0xC
    class vector mLeft; // offset 0x80, size 0xC
};
// Range: 0x80525614 -> 0x80525878
void * MessageBroker::MessageBroker(class MessageBroker * const this /* r31 */) {
    // References
    // -> static class Timer gTime;
    // -> static float gIncomingBytes;
    // -> static float gOutgoingBytes;
    // -> static float gLastPing;
    // -> static unsigned char gRefuseMessages;
    // -> static class vector gMessages;
    // -> static class MessageBroker * TheBroker;
    // -> struct [anonymous] __vt__13MessageBroker;
}

class _DO_RootDO : public DuplicatedObject {
    // total size: 0x74
};
class RootDO : public _DO_RootDO {
    // total size: 0x74
};
class _DO_MessageBroker : public RootDO {
    // total size: 0x74
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ClientStampPair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ClientStampPair * _M_start; // offset 0x0, size 0x4
    struct ClientStampPair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80525878 -> 0x80525990
void * MessageBroker::~MessageBroker(class MessageBroker * const this /* r30 */) {
    // References
    // -> static class MessageBroker * TheBroker;
}

// Range: 0x80525990 -> 0x805259C8
void MessageBroker::Init() {}

struct ClientStampPair {
    // total size: 0x8
    unsigned int mClientID; // offset 0x0, size 0x4
    unsigned int mLastStamp; // offset 0x4, size 0x4
};
// Range: 0x805259C8 -> 0x80525B7C
void MessageBroker::ProcessMessage(unsigned int senderID /* r30 */, class qBuffer & message /* r31 */) {
    // Local variables
    unsigned char found; // r5
    struct ClientStampPair * it; // r8
    struct ClientStampPair clientStamp; // r1+0x18

    // References
    // -> static class vector gMessages;
    // -> static class CriticalSection gMessageLock;
}

struct iterator {
    // total size: 0x1
};
class iterator : public iterator {
    // total size: 0x4
    unsigned char * m_ptr; // offset 0x0, size 0x4
};
class qBuffer : public RefCountedObject {
    // total size: 0x1C
    class iterator m_itFirst; // offset 0x8, size 0x4
    class iterator m_itBegin; // offset 0xC, size 0x4
    class iterator m_itEnd; // offset 0x10, size 0x4
    class iterator m_itLast; // offset 0x14, size 0x4
    unsigned int m_uiBeginOffset; // offset 0x18, size 0x4
};
struct MessagePair {
    // total size: 0x20
    unsigned int mSenderID; // offset 0x0, size 0x4
    class qBuffer mBuffer; // offset 0x4, size 0x1C
};
// Range: 0x80525B7C -> 0x80525BBC
static void * MessagePair::MessagePair(struct MessagePair * const this /* r31 */, unsigned int senderID /* r0 */) {}

static unsigned int stamp; // size: 0x4, address: 0x80A474BC
class RefTemplate : public DORef {
    // total size: 0xC
};
// Range: 0x80525BBC -> 0x80525DF4
void MessageBroker::Send(class DOHandle & station /* r28 */, class qBuffer & message /* r31 */, unsigned char reliable /* r27 */, unsigned char voice /* r29 */) {
    // Local variables
    int timeStamp; // r0
    class RefTemplate refMessageBroker; // r1+0x1C

    // References
    // -> unsigned int s_uiClassID;
    // -> class WKHandle gMessageBroker;
    // -> static unsigned int stamp;
    // -> static float gOutgoingBytes;
    // -> static unsigned char gLogging;
}

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
enum Category {
    Static = 0,
    Dynamic = 1,
    Unknown = 2,
};
class DOClass : public RootObject {
    // total size: 0x24
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned int m_uiClassID; // offset 0x4, size 0x4
    int m_iBootstrapID; // offset 0x8, size 0x4
    class qMap m_mapUpdatePolicy; // offset 0xC, size 0x18
};
// Range: 0x80525E34 -> 0x80526330
void MessageBroker::DispatchReceivedMessages() {
    // Local variables
    class vector toBeDispatched; // r1+0x48
    struct MessagePair * it; // r26
    struct MessagePair * it; // r29
    unsigned char found; // r5
    int * left; // r6
    unsigned char byteCode; // r28
    class MemStream buffer; // r1+0x58
    float current; // f0
    float duration; // f2

    // References
    // -> static float gOutgoingBytes;
    // -> static float gLastPing;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Timer gTime;
    // -> class NetMessenger TheNetMessenger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class MessageBroker * TheBroker;
    // -> static unsigned char gRefuseMessages;
    // -> static float gIncomingBytes;
    // -> static unsigned char gLogging;
    // -> static class vector gMessages;
    // -> static class CriticalSection gMessageLock;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct MessagePair * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct MessagePair * _M_start; // offset 0x0, size 0x4
    struct MessagePair * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x80526330 -> 0x805263AC
void MessageBroker::FlushClient(int stationNum /* r1+0x8 */) {
    // References
    // -> static class MessageBroker * TheBroker;
}

// Range: 0x805263AC -> 0x805263B8
void MessageBroker::FlushMessages() {
    // References
    // -> static unsigned char gRefuseMessages;
}

class VirtualRootObject {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class StateMachine : public VirtualRootObject {
    // total size: 0x1C
    void (StateMachine::* (StateMachine::* m_pfCurrentState)(void *, void *, class QEvent &))(void *, void *, class QEvent &); // offset 0x4, size 0x4
    void (StateMachine::* (StateMachine::* m_pfSourceState)(void *, void *, class QEvent &))(void *, void *, class QEvent &); // offset 0x10, size 0x4
};
class DORef : public RootObject {
    // total size: 0xC
    class DuplicatedObject * m_poReferencedDO; // offset 0x0, size 0x4
    class DOHandle m_hReferencedDO; // offset 0x4, size 0x4
    unsigned char m_bLockRelevance; // offset 0x8, size 0x1
};
class LogicalClockTmpl : public RootObject {
    // total size: 0x1
    unsigned char m_Value; // offset 0x0, size 0x1
};
class RefTemplate : public DORef {
    // total size: 0xC
};
class DOOperation : public Operation {
    // total size: 0x1C
protected:
    class RefTemplate m_refAssociatedDO; // offset 0x10, size 0xC
};
class DataSet : public RootObject {
    // total size: 0x1
};
class _DS_ConnectionInfo : public DataSet {
    // total size: 0x28
public:
    unsigned char m_bURLInitialized; // offset 0x0, size 0x1
    class String m_strStationURL1; // offset 0x4, size 0x4
    class String m_strStationURL2; // offset 0x8, size 0x4
    class String m_strStationURL3; // offset 0xC, size 0x4
    class String m_strStationURL4; // offset 0x10, size 0x4
    class String m_strStationURL5; // offset 0x14, size 0x4
    unsigned int m_uiInputBandwidth; // offset 0x18, size 0x4
    unsigned int m_uiInputLatency; // offset 0x1C, size 0x4
    unsigned int m_uiOutputBandwidth; // offset 0x20, size 0x4
    unsigned int m_uiOutputLatency; // offset 0x24, size 0x4
};
class ConnectionInfo : public _DS_ConnectionInfo {
    // total size: 0x28
};
class _DS_StationIdentification : public DataSet {
    // total size: 0x10
public:
    class String m_strIdentificationToken; // offset 0x0, size 0x4
    class String m_strProcessName; // offset 0x4, size 0x4
    unsigned int m_uiProcessType; // offset 0x8, size 0x4
    unsigned int m_uiProductVersion; // offset 0xC, size 0x4
};
class StationIdentification : public _DS_StationIdentification {
    // total size: 0x10
};
class _DS_StationInfo : public DataSet {
    // total size: 0x8
public:
    class DOHandle m_hObserver; // offset 0x0, size 0x4
    unsigned int m_uiMachineUID; // offset 0x4, size 0x4
};
class StationInfo : public _DS_StationInfo {
    // total size: 0x8
};
class _DS_StationState : public DataSet {
    // total size: 0x2
public:
    unsigned short m_ui16State; // offset 0x0, size 0x2
};
class StationState : public _DS_StationState {
    // total size: 0x8
    class Station * m_pAssociatedStation; // offset 0x4, size 0x4
};
class Attributes {
    // total size: 0x0
};
class Event : public RootObject {
    // total size: 0x10
protected:
    class EventHandler * m_pEventHandler; // offset 0x0, size 0x4
    unsigned int m_uiEventType; // offset 0x4, size 0x4
    unsigned int m_uiContext; // offset 0x8, size 0x4
    unsigned char m_bIsSet; // offset 0xC, size 0x1
};
class EventHandler : public RootObject {
    // total size: 0x24
    class CriticalSection m_csEventTable; // offset 0x0, size 0x14
    class Attributes * m_pAttributes; // offset 0x14, size 0x4
    class Event * * m_apEvents; // offset 0x18, size 0x4
    unsigned int m_uiNbEventsCreated; // offset 0x1C, size 0x4
    unsigned short m_ui16MaxNbEvents; // offset 0x20, size 0x2
};
class DOCallContext : public CallContext {
    // total size: 0x90
    unsigned short m_idRMCCall; // offset 0x48, size 0x2
    class DOHandle m_hSourceStation; // offset 0x4C, size 0x4
protected:
    class DORef m_refTargetStation; // offset 0x50, size 0xC
    class DORef m_refTargetObject; // offset 0x5C, size 0xC
    class EventHandler m_oEventHandler; // offset 0x68, size 0x24
    class Event * m_pResponseEvent; // offset 0x8C, size 0x4
};
class ActiveDOCallContext : public DOCallContext {
    // total size: 0x98
protected:
    class Message * m_pCallMessage; // offset 0x90, size 0x4
};
class RMCContext : public ActiveDOCallContext {
    // total size: 0xB0
    unsigned short m_idTargetMethod; // offset 0x94, size 0x2
    class qVector m_vReturnValuePtr; // offset 0x98, size 0xC
    unsigned char * m_pucDummyBuffer; // offset 0xA4, size 0x4
    class Message * m_pResponseMessage; // offset 0xA8, size 0x4
};
class CallMethodOperation : public DOOperation {
    // total size: 0x48
    unsigned int m_uiAttemptNumber; // offset 0x1C, size 0x4
    unsigned char m_bPostponed; // offset 0x20, size 0x1
    class UserContext m_oDelayContext; // offset 0x24, size 0x4
    int m_tiPostponeDelay; // offset 0x28, size 0x4
    unsigned short m_idRMC; // offset 0x2C, size 0x2
    unsigned short m_idTargetMethod; // offset 0x2E, size 0x2
    class Message * m_pCallMessage; // offset 0x30, size 0x4
    unsigned int m_uiFlags; // offset 0x34, size 0x4
    class Message * m_pResponseMessage; // offset 0x38, size 0x4
    class qResult m_rOutcome; // offset 0x3C, size 0xC
};
class _DO_Station : public RootDO {
    // total size: 0xBC
public:
    class ConnectionInfo m_dsConnectionInfo; // offset 0x74, size 0x28
    class StationIdentification m_dsIdentification; // offset 0x9C, size 0x10
    class StationInfo m_dsInfo; // offset 0xAC, size 0x8
    class StationState m_dsStationState; // offset 0xB4, size 0x8
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
class UpdateContextMap : public RootObject {
    // total size: 0x18
    class qMap m_mapUC; // offset 0x0, size 0x18
};
class DistanceComputationCache : public RootObject {
    // total size: 0x18
    float m_dDistance; // offset 0x0, size 0x4
    class DOHandle m_hA; // offset 0x4, size 0x4
    class DOHandle m_hB; // offset 0x8, size 0x4
    class Time m_tUpdateTime; // offset 0x10, size 0x8
};
class AtomicValue : public RootObject {
    // total size: 0x18
    unsigned int m_uiValue; // offset 0x0, size 0x4
    class CriticalSection m_cs; // offset 0x4, size 0x14
};
class MessageBundle : public RootObject {
    // total size: 0x40
    class Message m_oMessage; // offset 0x0, size 0x30
    class Time m_tiFirstAddedMsg; // offset 0x30, size 0x8
    unsigned int m_uiSendingFlags; // offset 0x38, size 0x4
};
class PseudoGlobalVariable {
    // total size: 0x0
};
class Station : public _DO_Station {
    // total size: 0x198
    class EndPoint * m_poEndPoint; // offset 0xBC, size 0x4
    class UpdateContextMap m_mapUpdateContext; // offset 0xC0, size 0x18
    class DistanceComputationCache m_oDistanceComputation; // offset 0xD8, size 0x18
    unsigned char m_bAtEOS; // offset 0xF0, size 0x1
    class AtomicValue m_bFaulty; // offset 0xF4, size 0x18
    class MessageBundle m_oSharedMessageBundle; // offset 0x110, size 0x40
    class MessageBundle m_oUnreliableMessageBundle; // offset 0x150, size 0x40
    unsigned int m_uiLastConnectionAttempt; // offset 0x190, size 0x4
};
class MasterStationRef : public DORef {
    // total size: 0xC
    class LogicalClockTmpl m_lcVersion; // offset 0x9, size 0x1
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
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
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
class Selection : public RootObject {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class qMap m_map; // offset 0x4, size 0x18
    unsigned char m_byFlags; // offset 0x1C, size 0x1
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
class RefTemplate : public DORef {
    // total size: 0xC
};
class RemoveFromStoreOperation : public DOOperation {
    // total size: 0x20
    unsigned char m_bDeleted; // offset 0x1C, size 0x1
    unsigned char m_bRemoveDuplicas; // offset 0x1D, size 0x1
};
enum Context {
    FaultRecovery = 0,
    MigrationOnTermination = 1,
    LoadBalancing = 2,
    UserRequest = 3,
    Unknown = 4,
};
class ChangeMasterStationOperation : public DOOperation {
    // total size: 0x3C
    class RefTemplate m_refOldMaster; // offset 0x1C, size 0xC
    class MasterStationRef m_refNewMaster; // offset 0x28, size 0xC
    const class qList * m_plstDupSet; // offset 0x34, size 0x4
    enum Context m_oContext; // offset 0x38, size 0x4
};
class DuplicatedObject : public StateMachine {
    // total size: 0x74
    unsigned short m_uiRefCount; // offset 0x1C, size 0x2
    unsigned short m_uiRelevanceCount; // offset 0x1E, size 0x2
    class MasterStationRef m_refMasterStation; // offset 0x20, size 0xC
    unsigned short m_uiFlags; // offset 0x2C, size 0x2
    class Selection m_setDuplicationSet; // offset 0x30, size 0x20
    class DOHandle m_dohMyself; // offset 0x50, size 0x4
    class Selection m_setCachedDuplicationSet; // offset 0x54, size 0x20
};
struct {
    // total size: 0x50
} __vt__13MessageBroker; // size: 0x50, address: 0x809051E8
struct {
    // total size: 0x8
} __RTTI__13MessageBroker; // size: 0x8, address: 0x80905280
struct {
    // total size: 0x8
} __RTTI__Q26Quazal17_DO_MessageBroker; // size: 0x8, address: 0x809052D0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal6RootDO; // size: 0x8, address: 0x80905310
struct {
    // total size: 0x8
} __RTTI__Q26Quazal10_DO_RootDO; // size: 0x8, address: 0x80905348
struct {
    // total size: 0x8
} __RTTI__Q26Quazal16DuplicatedObject; // size: 0x8, address: 0x80905380
struct {
    // total size: 0x8
} __RTTI__Q26Quazal12StateMachine; // size: 0x8, address: 0x809053B0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal17VirtualRootObject; // size: 0x8, address: 0x809053D8
struct {
    // total size: 0x8
} __RTTI__PQ227@unnamed@MessageBroker_cpp@11MessagePair; // size: 0x8, address: 0x80905410
struct {
    // total size: 0x8
} __RTTI__PQ213MessageBroker15ClientStampPair; // size: 0x8, address: 0x80905440
// Range: 0x805263B8 -> 0x8052642C
static void __sinit_\MessageBroker_cpp() {
    // References
    // -> static class Timer gTime;
    // -> static class vector gMessages;
    // -> static class CriticalSection gMessageLock;
}

class NetMessenger {
    // total size: 0x10
    unsigned int mLastSender; // offset 0x0, size 0x4
    class NetworkSocket * mUDPSocket; // offset 0x4, size 0x4
    unsigned short mUDPPort; // offset 0x8, size 0x2
    unsigned int mAppSignature; // offset 0xC, size 0x4
};

