#include "Platform/Socket.h"

namespace Quazal {
    Socket::Socket(unsigned int arg0) {
        unkStruct *temp_r12;

        this->unk90 = 0x3E8;
        this->unk94 = 0;
        this->unk88 = 1;
        this->unk8C = arg0;
        if (s_pSocketDriver != 0) {
            temp_r12 = *(unkStruct **)(s_pSocketDriver);
            temp_r12->unkC();
        }
    }
}