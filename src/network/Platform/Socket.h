#pragma once

#include "types.h"

#include "Platform/InetAddress.h"

class SocketDriver {
public:
    virtual s32 unk8(bool);
    virtual SocketDriver *unkC();
    virtual s32 unk10(u32);
};

namespace Quazal {
    class Socket : RootObject {
        static SocketDriver *s_pSocketDriver;

        s32 unk0;
        InetAddress address;
        char unk8[0x7C];
        bool unk88;
        unsigned int unk8C;
        s32 unk90;
        u8 unk94;
        SocketDriver *unk98;

        Socket(unsigned int);
        ~Socket();
        s32 Open(bool);
        s32 Bind(InetAddress *);
        InetAddress *GetAddress();
        void Close();
    };
}