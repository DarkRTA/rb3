/*
    Compile unit: C:\rockband2\system\src\net\QuazalSession.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8053D154 -> 0x8053DE44
*/
class NetZ * mTerminatingNetZ; // size: 0x4, address: 0x80A53E18
class CallContext * mTerminatingContext; // size: 0x4, address: 0x80A53E1C
// Range: 0x8053D154 -> 0x8053D310
void * QuazalSession::QuazalSession(class QuazalSession * const this /* r29 */, unsigned char hosting /* r30 */) {
    // Local variables
    unsigned char networked; // r0
    unsigned char success; // r3
    char strError[256]; // r1+0x8

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__12NetZCallback;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class CallContext * mTerminatingContext;
}

// Range: 0x8053D310 -> 0x8053D404
void * QuazalSession::~QuazalSession(class QuazalSession * const this /* r30 */) {
    // References
    // -> class NetMessenger TheNetMessenger;
    // -> class NetZ * mTerminatingNetZ;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class CallContext * mTerminatingContext;
}

// Range: 0x8053D49C -> 0x8053D520
void QuazalSession::Poll() {
    // References
    // -> class NetZ * mTerminatingNetZ;
    // -> class CallContext * mTerminatingContext;
}

// Range: 0x8053D520 -> 0x8053D534
unsigned char QuazalSession::StillDeleting() {
    // References
    // -> class CallContext * mTerminatingContext;
}

// Range: 0x8053D534 -> 0x8053D5A4
unsigned char QuazalSession::HasHostLeft(class QuazalSession * const this /* r30 */) {
    // Local variables
    unsigned char hostLeft; // r31
}

// Range: 0x8053D5A4 -> 0x8053D6C8
unsigned char QuazalSession::HaveClientsLeft(class QuazalSession * const this /* r30 */, class vector & clientsLeft /* r31 */) {
    // Local variables
    unsigned char empty; // r28
    int * it; // r27
}

// Range: 0x8053D6C8 -> 0x8053DA7C
void QuazalSession::CancelJoinSession() {
    // Local variables
    class ScopedCS oCS; // r1+0x38
    class SelectionIteratorTemplate itStations; // r1+0x40

    // References
    // -> unsigned int s_uiClassID;
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
}

// Range: 0x8053DA7C -> 0x8053DB78
void * MakeQuazalSessionJob::MakeQuazalSessionJob(class MakeQuazalSessionJob * const this /* r29 */, class QuazalSession * * address /* r30 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__20MakeQuazalSessionJob;
}

// Range: 0x8053DB78 -> 0x8053DC94
unsigned char MakeQuazalSessionJob::IsFinished(class MakeQuazalSessionJob * const this /* r31 */) {
    // Local variables
    class list users; // r1+0x28
    struct _List_iterator it; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
}

// Range: 0x8053DC94 -> 0x8053DCF8
void MakeQuazalSessionJob::Cancel() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
}

class NetZCallback : public OperationCallback {
    // total size: 0x34
public:
    unsigned char mHostLeft; // offset 0x8, size 0x1
    class vector mClientsLeft; // offset 0xC, size 0xC
    class CriticalSection mCritSection; // offset 0x18, size 0x1C
};
// Range: 0x8053DCF8 -> 0x8053DE44
void NetZCallback::CallMethod(class NetZCallback * const this /* r31 */, class Operation * pOperation /* r30 */) {
    // Local variables
    class ChangeMasterStationOperation * pOp; // r0
    class RemoveFromStoreOperation * pOp; // r0
    class Station * station; // r30

    // References
    // -> unsigned int s_uiClassID;
    // -> unsigned int s_uiClassID;
}

struct {
    // total size: 0x10
} __vt__12NetZCallback; // size: 0x10, address: 0x809085A0
struct {
    // total size: 0x8
} __RTTI__12NetZCallback; // size: 0x8, address: 0x809085D8
struct {
    // total size: 0x1C
} __vt__20MakeQuazalSessionJob; // size: 0x1C, address: 0x809085E0
struct {
    // total size: 0x8
} __RTTI__20MakeQuazalSessionJob; // size: 0x8, address: 0x80908620
struct {
    // total size: 0x10
} __vt__Q26Quazal17OperationCallback; // size: 0x10, address: 0x80908630
struct {
    // total size: 0x8
} __RTTI__Q26Quazal17OperationCallback; // size: 0x8, address: 0x80908668
unsigned int s_uiClassID; // size: 0x4, address: 0x80A55FE8

