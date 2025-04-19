#include "Platform/Socket.h"

typedef struct unkStruct {
    s32 unk8;
    char unkC[0x4];
    s32 unk10;
    s16 unk14;
} unkStruct;

namespace Quazal {
    IOResult g_oBerkeleySocketDriver;

    IOResult *Socket::s_pSocketDriver = &g_oBerkeleySocketDriver;

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

    s32 Socket::Send(
        u8 *arg0, unsigned int arg1, InetAddress *arg2, IOCompletionContext *arg3
    ) {
        unkStruct temp;
        u16 portNum;
        s32 var_r3;
        bool var_r4;

        arg3->unk1C = this;
        arg3->unk15 = 2;
        arg3->unk0 = arg0;
        arg3->unk4 = arg1;
        arg3->unk10 = arg2;
        arg3->unk8 = 0;
        if (this->unk98 != nullptr) {
            portNum = arg2->GetPortNumber();
            temp.unk10 = arg3->unk10->GetAddress();
            temp.unk14 = portNum;
            temp.unk8 = 0;
            if (this->unk88 != 0) {
                var_r3 = this->unk98->unk18(arg0, arg1, &temp.unk10, &temp.unk8);
            } else {
                var_r3 = this->unk98->unk24(arg0, arg1, &temp.unk8);
            }
            arg3->unk8 = temp.unk8;
            switch (var_r3) {
            case 2:
            case 3:
                arg3->unk14 = 1;
                var_r4 = 1;
                break;
            case 1:
                arg3->unkC = (IOResult *)-1;
                arg3->unk14 = 2;
                arg3->unk15 = 0;
                var_r4 = 0;
                break;
            case 0:
                arg3->unkC = 0;
                var_r4 = 1;
                arg3->unk14 = 2;
                arg3->unk15 = 0;
                break;
            default:
                var_r4 = 0;
                break;
            }
            return -(!var_r4);
        }
        return 0;
    }

    s32 Socket::Recv(
        u8 *arg0, unsigned int arg1, InetAddress *arg2, IOCompletionContext *arg3
    ) {
        unkStruct sp8;
        s32 var_r31;
        bool var_r4;
        u16 temp_r31;

        arg3->unk15 = 3;
        arg3->unk0 = arg0;
        arg3->unk4 = arg1;
        arg3->unk10 = arg2;
        arg3->unk8 = 0;
        arg3->unk1C = this;
        if (this->unk98 != NULL) {
            temp_r31 = arg2->GetPortNumber();
            sp8.unk10 = arg3->unk10->GetAddress();
            sp8.unk14 = temp_r31;
            sp8.unk8 = 0;
            if (this->unk88 != 0) {
                var_r31 = this->unk98->unk14(arg0, arg1, &sp8.unk10, &sp8.unk8);
            } else {
                var_r31 = this->unk98->unk20(arg0, arg1, &sp8.unk8);
            }
            arg3->unk8 = sp8.unk8;
            arg3->unk10->SetAddress(sp8.unk10);
            arg3->unk10->SetPortNumber(sp8.unk14);
            switch (var_r31) { /* irregular */
            case 2:
            case 3:
                arg3->unk14 = 1;
                var_r4 = 1;
                break;
            case 1:
                arg3->unkC = (IOResult *)-1;
                arg3->unk14 = 2;
                arg3->unk15 = 0;
                var_r4 = 0;
                break;
            case 0:
                arg3->unkC = 0;
                var_r4 = 1;
                arg3->unk14 = 2;
                arg3->unk15 = 0;
                break;
            default:
                var_r4 = 0;
                break;
            }
            return -!var_r4;
        }
        return 0;
    }

    IOResult *Socket::GetIOResult(IOCompletionContext *arg0) {
        if (this->unk98 != nullptr) {
            return arg0->unkC;
        } else {
            return nullptr;
        }
    }
}