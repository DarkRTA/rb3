#pragma once

#include "types.h"

#include "Platform/InetAddress.h"
#include "Platform/IOCompletionContext.h"

namespace Quazal {
    class Socket : public RootObject {
        static IOResult *s_pSocketDriver;

        s32 unk0;
        InetAddress address;
        char unk8[0x7C];
        bool unk88;
        unsigned int unk8C;
        s32 unk90;
        u8 unk94;
        IOResult *unk98;

        Socket(unsigned int);
        ~Socket();
        s32 Open(bool);
        s32 Bind(InetAddress *);
        InetAddress *GetAddress();
        void Close();
        s32
        Send(u8 *arg0, unsigned int arg1, InetAddress *arg2, IOCompletionContext *arg3);
        s32
        Recv(u8 *arg0, unsigned int arg1, InetAddress *arg2, IOCompletionContext *arg3);
        IOResult *GetIOResult(IOCompletionContext *);
    };
}