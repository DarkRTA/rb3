#pragma once
#include "net/NetMessage.h"
#include "net/NetSession.h"

class NetMessenger {
public:
    NetMessenger();
    ~NetMessenger();

    void DeliverMsg(const unsigned int&, const NetMessage&, PacketType);
    void FlushClientMessages(unsigned int);

    unsigned int mLastSender; // 0x0
};

extern NetMessenger TheNetMessenger;