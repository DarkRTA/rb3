/*
    Compile unit: C:\rockband2\system\src\net\MessageBrokerDDL.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805269F0 -> 0x80526E00
*/
class _DOC_MessageBroker : public DOClassTemplate {
    // total size: 0x2C
public:
    unsigned short m_midProcessMessage; // offset 0x2A, size 0x2
};
// Range: 0x805269F0 -> 0x80526A18
void _DOC_MessageBroker::Delete() {}

// Range: 0x80526A18 -> 0x80526A2C
unsigned char _DOC_MessageBroker::ApproveFaultRecovery() {}

// Range: 0x80526A2C -> 0x80526A44
unsigned char _DOC_MessageBroker::ApproveEmigration() {}

// Range: 0x80526A44 -> 0x80526A5C
void _DOC_MessageBroker::Trace() {}

class DOClassTemplate : public DOClass {
    // total size: 0x24
};
class _DOC_RootDO : public DOClassTemplate {
    // total size: 0x2C
public:
    unsigned short m_midAddDuplicaLocation; // offset 0x24, size 0x2
    unsigned short m_midDeleteDuplica; // offset 0x26, size 0x2
    unsigned short m_midRemoveFromCachedDuplicationSet; // offset 0x28, size 0x2
};
class DOClassTemplate : public _DOC_RootDO {
    // total size: 0x2C
};
// Range: 0x80526A5C -> 0x80526A78
unsigned char _DOC_MessageBroker::IsAKindOf() {
    // References
    // -> unsigned int s_uiClassID;
}

// Range: 0x80526A78 -> 0x80526A7C
void _DOC_MessageBroker::DataSetsOperation() {}

// Range: 0x80526A7C -> 0x80526A80
unsigned char _DOC_MessageBroker::FormatVariableValue() {}

// Range: 0x80526A80 -> 0x80526A84
unsigned char _DOC_MessageBroker::DispatchAction() {}

// Range: 0x80526A84 -> 0x80526AFC
void _DOC_MessageBroker::DispatchRMCCall(const class CallMethodOperation & refOp /* r31 */) {}

// Range: 0x80526AFC -> 0x80526B3C
unsigned char _DOC_MessageBroker::DispatchRMCResult() {}

// Range: 0x80526B3C -> 0x80526B40
void _DOC_MessageBroker::FillDupSpacesInfo() {}

// Range: 0x80526B40 -> 0x80526B44
char * _DOC_MessageBroker::GetDatasetNameString() {}

// Range: 0x80526B44 -> 0x80526B94
void * _DO_MessageBroker::_DO_MessageBroker(class _DO_MessageBroker * const this /* r31 */) {
    // References
    // -> unsigned int s_uiClassID;
    // -> struct [anonymous] __vt__Q26Quazal17_DO_MessageBroker;
}

// Range: 0x80526B94 -> 0x80526BE8
void _DO_MessageBroker::InitDOClass(unsigned int uiClassID /* r31 */) {
    // References
    // -> unsigned int s_uiClassID;
}

// Range: 0x80526BE8 -> 0x80526C48
class MessageBroker * _DO_MessageBroker::CreateWellKnown(class WKHandle & hWK /* r31 */) {
    // References
    // -> unsigned int s_uiClassID;
}

unsigned int s_uiClassID; // size: 0x4, address: 0x80A53CA0
// Range: 0x80526C48 -> 0x80526C4C
void _DO_MessageBroker::RegisterDatasets() {}

// Range: 0x80526C4C -> 0x80526C50
void _DO_MessageBroker::SpecificAddDSToDiscoveryMessage() {}

// Range: 0x80526C50 -> 0x80526C54
void _DO_MessageBroker::SpecificExtractDSFromDiscoveryMessage() {}

// Range: 0x80526C54 -> 0x80526C58
void _DO_MessageBroker::CallOperationOnDatasets() {}

// Range: 0x80526C58 -> 0x80526C5C
unsigned char _DO_MessageBroker::SpecificUpdate() {}

// Range: 0x80526C5C -> 0x80526C60
unsigned char _DO_MessageBroker::SpecificRefresh() {}

// Range: 0x80526C60 -> 0x80526C64
unsigned char _DO_MessageBroker::SpecificExtractADataset() {}

// Range: 0x80526C64 -> 0x80526D48
unsigned char _DO_MessageBroker::CallProcessMessage(class _DO_MessageBroker * const this /* r0 */, class RMCContext * pContext /* r27 */, const unsigned int & senderID /* r28 */, const class qBuffer & bufMessagePayload /* r29 */, const unsigned int & timeStamp /* r30 */) {
    // Local variables
    class Message * pMsg; // r31
}

// Range: 0x80526D48 -> 0x80526DFC
void _DO_MessageBroker::ProcessMessageWrapper(class _DO_MessageBroker * const this /* r29 */, const class CallMethodOperation & refOp /* r30 */) {
    // Local variables
    class Message * pMsg; // r31
    unsigned int senderID; // r1+0xC
    class qBuffer bufMessagePayload; // r1+0x10
    unsigned int timeStamp; // r1+0x8
}

// Range: 0x80526DFC -> 0x80526E00
void _DO_MessageBroker::ProcessMessageReturnStub() {}

struct {
    // total size: 0x68
} __vt__Q26Quazal18_DOC_MessageBroker; // size: 0x68, address: 0x809054A0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal18_DOC_MessageBroker; // size: 0x8, address: 0x80905550
struct {
    // total size: 0x8
} __RTTI__Q26Quazal68DOClassTemplate<Q26Quazal17_DO_MessageBroker,Q26Quazal11_DOC_RootDO>; // size: 0x8, address: 0x809055C8
struct {
    // total size: 0x50
} __vt__Q26Quazal17_DO_MessageBroker; // size: 0x50, address: 0x809055D0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal11_DOC_RootDO; // size: 0x8, address: 0x80905650
struct {
    // total size: 0x8
} __RTTI__Q26Quazal56DOClassTemplate<Q26Quazal10_DO_RootDO,Q26Quazal7DOClass>; // size: 0x8, address: 0x809056B0
struct {
    // total size: 0x8
} __RTTI__Q26Quazal7DOClass; // size: 0x8, address: 0x809056D8

