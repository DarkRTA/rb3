#include "Platform/Socket.h"
#include "Platform/IOCompletionContext.h"

namespace Quazal {
    SocketDriver *g_oBerkeleySocketDriver;

    SocketDriver *Socket::s_pSocketDriver;

    Socket::Socket(unsigned int arg0) {
        this->unk0 = 3;
        this->unk90 = 0x3E8;
        this->unk94 = 0;
        this->unk88 = 1;
        this->unk8C = arg0;
        if (s_pSocketDriver) {
            this->unk98 = s_pSocketDriver->unkC();
        } else {
            this->unk98 = 0;
        }
    }

    Socket::~Socket() {
        if (this->unk0 != 3 && this->unk98 != nullptr) {
            this->unk98->unkC();
            this->unk0 = 3;
        }
        if (this->s_pSocketDriver != nullptr) {
            this->s_pSocketDriver->unk10((u32)this->unk98);
        }
    }

    s32 Socket::Open(bool arg0) {
        s32 var_r3;

        this->unk88 = arg0;
        var_r3 = 0;
        if (this->unk98 != nullptr) {
            var_r3 = this->unk98->unk8((u8)arg0 == 0);
        }
        if (var_r3 != 0) {
            this->unk0 = 0;
            return 1;
        }
        return 0;
    }

    s32 Socket::Bind(InetAddress *arg0) {
        s32 var_r31;
        u16 var_r30;
        u16 var_r29;

        var_r31 = 0;
        if (this->unk98 != NULL) {
            var_r30 = arg0->GetPortNumber();
            if (var_r30 == 0) {
                for (var_r29 = 0x2390; var_r31 == 0 && var_r29 < 0x23F0;) {
                    if (this->unk98->unk10(var_r29) != 0) {
                        var_r30 = var_r29;
                        var_r31 = 1;

                    } else {
                        var_r29 += 1;
                    }
                }
            } else {
                var_r31 = this->unk98->unk10(var_r30);
            }
            if (var_r31 != 0) {
                arg0->SetPortNumber(var_r30);
            }
        }
        if (var_r31 != 0) {
            this->unk0 = 1;
            this->address = *arg0;
            return 1;
        }
        return 0;
    }

    InetAddress *Socket::GetAddress() { return &this->address; }

    void Socket::Close() {
        if (this->unk0 != 3) {
            if (this->unk98 != nullptr) {
                this->unk98->unkC();
                this->unk0 = 3;
            }
        }
    }
}