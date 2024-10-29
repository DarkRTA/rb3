#ifndef NET_NETMESSAGE_H
#define NET_NETMESSAGE_H
#include <vector>
#include "system/utl/Str.h"

class NetMessage;

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