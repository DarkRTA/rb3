#ifndef NET_NETMESSAGE_H
#define NET_NETMESSAGE_H
#include <vector>
#include "utl/Str.h"
#include "utl/BinStream.h"

class NetMessage {
public:
    NetMessage(){}
    virtual ~NetMessage(){}
    virtual void Save(BinStream &) const = 0;
    virtual void Load(BinStream &) = 0;
    virtual void Dispatch() = 0;
    virtual bool VoiceData() const { return false; }
    virtual void Print(TextStream&) const {}
    virtual unsigned char ByteCode() const = 0;
    virtual const char* Name() const = 0;
};

typedef NetMessage* NetMessageFunc(void);

class NetMessageFactory {
public:
    struct TypeCreatorPair {
        String mType; // 0x0
        NetMessageFunc* mCreator; // 0x4
    };

    NetMessageFactory(){}
    ~NetMessageFactory(){}

    unsigned char GetNetMessageByteCode(String) const;
    NetMessage* CreateNetMessage(unsigned char);
    void RegisterNetMessage(String, NetMessage* (*)(void));

    std::vector<TypeCreatorPair> mFactoryList; // 0x0
};

extern NetMessageFactory TheNetMessageFactory;

#endif // NET_NETMESSAGE_H