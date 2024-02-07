/*
    Compile unit: C:\rockband2\system\src\net\NetMessenger.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805283FC -> 0x80528C8C
*/
class NetMessenger TheNetMessenger; // size: 0x10, address: 0x80982000
// Range: 0x805283FC -> 0x80528408
void * NetMessenger::NetMessenger() {}

// Range: 0x80528408 -> 0x8052847C
void CreateMessageBroker() {
    // Local variables
    class MessageBroker * broker; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class WKHandle gMessageBroker;
}

// Range: 0x8052847C -> 0x80528594
void NetMessenger::Init(class NetMessenger * const this /* r28 */) {
    // Local variables
    class DataArray * config; // r29
}

// Range: 0x80528594 -> 0x80528610
void * NetMessenger::~NetMessenger(class NetMessenger * const this /* r30 */) {}

class NetworkSocket {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class SelectionIteratorTemplate : public IteratorOverDOs {
    // total size: 0x24
};
// Range: 0x80528610 -> 0x80528B98
void NetMessenger::DeliverMsg(const unsigned int & id /* r28 */, const class NetMessage & msg /* r29 */, enum PacketType isReliable /* r30 */) {
    // Local variables
    class MemStream packet; // r1+0x78
    class qBuffer buffer; // r1+0x58
    class SelectionIteratorTemplate stations; // r1+0x98
    unsigned char isVoiceData; // r27

    // References
    // -> unsigned char s_bNoOp;
    // -> class InstanceTable s_oInstanceTable;
    // -> unsigned int s_uiClassID;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class DOFilter : public RefCountedObject {
    // total size: 0x8
};
class IteratorOverDOs : public RootObject {
    // total size: 0x24
    const class Selection * m_pSelection; // offset 0x0, size 0x4
    class DORef m_refCurrentItem; // offset 0x4, size 0xC
    class DOFilter * m_pFilter; // offset 0x10, size 0x4
    class DOHandle m_hMinimumValidHandle; // offset 0x14, size 0x4
    class DOHandle m_hMaximumValidHandle; // offset 0x18, size 0x4
    unsigned char m_bMustBeInStore; // offset 0x1C, size 0x1
    void * m_pCreationContext; // offset 0x20, size 0x4
};
// Range: 0x80528B98 -> 0x80528C34
void NetMessenger::DispatchMsg(const unsigned int & id /* r7 */, class MemStream & buffer /* r30 */) {
    // Local variables
    class NetMessage * msg; // r31

    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

// Range: 0x80528C34 -> 0x80528C38
void NetMessenger::Poll() {}

// Range: 0x80528C38 -> 0x80528C3C
void NetMessenger::FlushMessages() {}

// Range: 0x80528C3C -> 0x80528C44
void NetMessenger::FlushClientMessages() {}

// Range: 0x80528C44 -> 0x80528C8C
static void __sinit_\NetMessenger_cpp() {
    // References
    // -> class NetMessenger TheNetMessenger;
}

unsigned int s_uiClassID; // size: 0x4, address: 0x80A55FE0

