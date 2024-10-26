#ifndef NET_NETMESSAGE_H
#define NET_NETMESSAGE_H
#include <vector>
#include "system/utl/Str.h"

class NetMessage;

class NetMessageFactory {
public:
    ~NetMessageFactory();

    int GetNetMessageByteCode(String) const;
    void CreateNetMessage(unsigned char);
    void RegisterNetMessage(String, NetMessage* (*)(void));

    std::vector<String> unk_0x0;
};

extern NetMessageFactory TheNetMessageFactory;

#endif // NET_NETMESSAGE_H