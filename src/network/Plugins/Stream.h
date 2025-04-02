#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class Stream : public RootObject {
    public:
        enum Type {
        };
        Stream(Type);
        virtual ~Stream();
        virtual bool
        ReceiveIncomingPacket(unsigned short, unsigned char, class Packet *) = 0;
        virtual void DoWork() = 0;
        virtual void
        ReceiveIncomingMsg(class StationURL *, class Buffer *, unsigned short) = 0;

        Type mType; // 0x4
    };
}