#pragma once

#include "types.h"

#include "Platform/InetAddress.h"

typedef struct unkStruct {
    char unk[0xC];
    void (*unkC)();
} unkStruct;

namespace Quazal {
    class Socket {
        static unsigned long long s_pSocketDriver;

        char unk[0x4];
        InetAddress unk4;
        char unk8[0x80];
        u8 unk88;
        unsigned int unk8C;
        s32 unk90;
        u8 unk94;

        Socket(unsigned int);
        ~Socket();
    };
}