#include "NetMessage.h"

#include "os/Debug.h"

NetMessageFactory TheNetMessageFactory;

NetMessageFactory::~NetMessageFactory() {}

void NetMessageFactory::CreateNetMessage(unsigned char param1) {
    MILO_ASSERT(unk_0x0.size() < param1, 0x36);
}
