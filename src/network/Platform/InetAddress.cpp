#include "Platform/InetAddress.h"

#include "Platform/StringConversion.h"
#include "Platform/BadEvents.h"
#include <vector>
#include "revolution/rvl/so.h"

// uncompiled
extern "C" u32 SOGetHostID(void);
extern "C" so_ret_t SOGetHostByName(const char *addr);
extern "C" s32 SOInetPtoN(s32, char*, s32*);
extern "C" void SOInetNtoP(s32, const s32*, char*, s32);
extern s16 htons(u16 arg0);
extern s16 ntohs(u16 arg0);
extern s32 htonl(u32 arg0);
extern s32 ntohl(u32 arg0);

namespace Quazal {
    InetAddress::InetAddress() {
        memset(this, 0, 8);
        this->unk1 = 2;
    }

    InetAddress::InetAddress(const InetAddress& orig) {
        memcpy(this, &orig, 0x20);
    }

    InetAddress::InetAddress(const char* str, u16 arg1) {
        char sp110[0x100];
        char sp10[0x100];
        s32 spC;
        s32 sp8;
        u32 var_r3;
        const char* temp_r28;
        so_ret_t temp_r3;

        memset(this, 0, 8);
        this->unk1 = 2;
        if (strcmp(str, "255.255.255.255") == 0) {
            this->address = -1;
        } else if (strcmp(str, "localhost") == 0) {
            temp_r28 = "127.0.0.1";
            if (strcmp(temp_r28, "255.255.255.255") == 0) {
                this->address = -1;
            } else if (strcmp(temp_r28, "localhost") == 0) {
                SetAddress(temp_r28);
            } else {
                StringConversion::T2Char8(temp_r28, sp110, 0x100);
                if (SOInetPtoN(2, sp110, &sp8) > 0) {
                    var_r3 = sp8;
                } else {
                    var_r3 = -1;
                }
                this->address = var_r3;
                if (var_r3 == -1) {
                    BadEvents::Signal((BadEvents::_ID)7);
                    temp_r3 = SOGetHostByName(sp110);
                    if (temp_r3 != SO_OK) {
                        this->address = **(s32**)(((s32*)temp_r3)[3]);
                    }
                }
            }
        } else {
            StringConversion::T2Char8(temp_r28, sp10, 0x100);
            if (SOInetPtoN(2, sp10, &spC) > 0) {
                var_r3 = spC;
            } else {
                var_r3 = -1;
            }
            this->address = var_r3;
            if (var_r3 == -1) {
                BadEvents::Signal((BadEvents::_ID)7);
                temp_r3 = SOGetHostByName(sp10);
                if (temp_r3 != SO_OK) {
                    this->address = **(s32**)(((s32*)temp_r3)[3]);
                }
            }
        }
        this->port = htons(arg1);
    }

    InetAddress::~InetAddress() {}

    void InetAddress::Init() {
        memset(this, 0, 8);
        this->unk1 = 2;
    }

    s32 InetAddress::SetAddress(const char* arg0) {
        char sp110[0x100];
        char sp10[0x100];
        s32 spC;
        s32 sp8;
        u32 var_r3;
        char* temp_r30;
        so_ret_t temp_r3;
    
        if (strcmp(arg0, "255.255.255.255") == 0) {
            this->address = -1;
            return 1;
        }
        if (strcmp(arg0, "localhost") == 0) {
            temp_r30 = "127.0.0.1";
            if (strcmp(temp_r30, "255.255.255.255") == 0) {
                this->address = -1;
                return 1;
            }
            if (strcmp(temp_r30, "localhost") == 0) {
                return this->SetAddress(temp_r30);
            }
            StringConversion::T2Char8(temp_r30, sp10, 0x100);
            if (SOInetPtoN(2, sp10, &spC) > 0) {
                var_r3 = spC;
            } else {
                var_r3 = -1;
            }
            this->address = var_r3;
            if (var_r3 == -1) {
                BadEvents::Signal((Quazal::BadEvents::_ID)7);
                temp_r3 = SOGetHostByName(sp10);
                if (temp_r3 != SO_OK) {
                    this->address = **(s32**)(((s32*)temp_r3)[3]);
                } else {
                    return 0;
                }
            }
            return 1;
        }
        StringConversion::T2Char8(arg0, sp110, 0x100);
        if (SOInetPtoN(2, sp110, &sp8) > 0) {
            var_r3 = sp8;
        } else {
            var_r3 = -1;
        }
        this->address = var_r3;
        if (var_r3 == -1) {
            BadEvents::Signal((Quazal::BadEvents::_ID)7);
            temp_r3 = SOGetHostByName(sp110);
            if (temp_r3 != SO_OK) {
                this->address = **(s32**)(((s32*)temp_r3)[3]);
            } else {
                return 0;
            }
        }
        return 1;
    }

    void InetAddress::SetAddress(unsigned int addr) {
        this->address = htonl(addr);
    }

    void InetAddress::SetNetworkAddress(unsigned int addr) {
        this->address = addr;
    }

    s32 InetAddress::GetAddress() const {
        return ntohl(this->address);
    }

    s32 InetAddress::GetAddress(char* arg0, unsigned int arg1) const {
        char sp8[0x20];
    
        if (arg1 < 0x10) {
            return 0;
        }
        SOInetNtoP(2, &this->address, &sp8[0], 0x14);
        StringConversion::Char8_2T(&sp8[0], arg0, arg1);
        return 1;
    }

    void InetAddress::SetPortNumber(u16 port) {
        this->port = htons(port);
    }

    s16 InetAddress::GetPortNumber() const {
        return ntohs(this->port);
    }

    bool InetAddress::operator==(const InetAddress& b) const {
        s32 temp_r31;
        u16 temp_r30;
        s32 temp_r29;

        s32 temp;
        s32 temp2;
    
        temp_r29 = b.address;
        temp_r30 = ntohs(b.port);
        temp_r31 = this->address;
        temp = ((u16)ntohs(this->port));
        
        return ((temp ^ temp_r30) | (temp_r31 ^ temp_r29)) == 0;
    }
    
    InetAddress* InetAddress::operator=(const InetAddress& b) {
        memcpy(this, &b, 0x20);
        return this;
    }
}

DECOMP_FORCEACTIVE(str, "%d", ":")