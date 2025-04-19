#pragma once

#include "types.h"
#include "decomp.h"
#include "Platform/RootObject.h"

namespace Quazal {
    class InetAddress : public RootObject {
    public:
        u8 unk0;
        u8 unk1;
        s16 port;
        s32 address;
        InetAddress();
        InetAddress(const InetAddress &);
        InetAddress(const char *, u16);
        ~InetAddress();

        void Init();

        s32 SetAddress(const char *);
        void SetAddress(unsigned int);
        void SetNetworkAddress(unsigned int);
        s32 GetAddress() const;
        s32 GetAddress(char *, unsigned int) const;

        void SetPortNumber(u16);
        u16 GetPortNumber() const;

        s32 operator<(const InetAddress &) const;
        bool operator==(const InetAddress &) const;
        InetAddress *operator=(const InetAddress &);
    };
}
