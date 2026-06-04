#include <ec/misc.h>
#include <MSL_Common/printf.h>
namespace {
    char *levelText[] = {"#####  EC ERR: ", "EC WARN: ", "EC INFO: ", "EC FINE: ", "EC FINER: ", "EC FINEST: "};
};

const char invalidLogLevelMsg[] = "Log level invalid %d\n";

namespace ec {
    long logLevel = ECLogLevel_Fine, logBufLevel = ECLogLevel_Fine;

    void (*logMsgToBuffer)(char *, __va_list_struct *);

    void logmsg(long level, const char *format, ...) {
        if (level != 0 && level <= logLevel || level <= logBufLevel) {
            char *buffer;
            int ret = snprintf(buffer, 0x100, "%s%s", levelText[level * 4], format);
            if (ret < 0 || ret == 0x100) {
                memcpy(buffer, format, 0x100);
                char b = 0; //? is this needed?
                printf("%s log format string exceeds %d: %s\n", levelText, 0xff, format);
            }
            if (level <= logLevel) {
                vprintf(buffer, (__va_list_struct *)0x2000000);
            }
            if (logMsgToBuffer != NULL && level <= logBufLevel) {
                logMsgToBuffer(buffer, (__va_list_struct *)0x2000000);
            }
        }
    }

    ECResult setLogLevel(long newLevel) {
        ECResult result = ECResult_Success;
        if (newLevel > 6) {
            result = ECResult_InvalidBufHeap;
        } else {
            if (newLevel < 0)
                result = ECResult_InvalidBufHeap;
            else 
                logLevel = newLevel;
        }
        if (result != ECResult_Success) {
            logmsg(ECLogLevel_Error, invalidLogLevelMsg, newLevel);
        } else {
            logmsg(ECLogLevel_Info, "logLevel argument %d, logLevel set to %d\n", newLevel, logLevel);
        }
        return result;
    }

    ECResult titleChannel(unsigned long long titleId) {
        return (ECResult)(titleId & 0xFFFF);
    }

    unsigned int isSubscription(unsigned long long p1) { return (unsigned int)__cntlzw(p1) >> 5; }

    ECResult getTmdSize(void *p1, unsigned long *p2) {
        ECResult status = ECResult_Success;
        if (!p1) status = ECResult_ECFail; 
        else *p2 = (unsigned int)*(unsigned short *)((int)p1 + 0x1de) * 0x24 + 0x1e4;
        return status;
    }

    bool isCidxMaskBitSet(const unsigned char *p1, unsigned long p2) {
        if (p2 >> 3 >= 0x40) return false;
        return (1 << (p2 & 7) & (unsigned int)p1[p2 >> 3]) != 0;
    }

    int isTicketForContent(const ESTicketView *p1, unsigned long p2, const ec::ECCmdView &p3) {
        int ret = 0;
        while (p2) {
            if (isCidxMaskBitSet(p1->cidxMask, p3.unk0x4) != 0) {
                ret = 1;
            } 
            break;
        }
        return ret;
    }

    ECResult reformatEcard(const ECString &p1, ECString &p2, ECString &p3, ECString &p4) {
        const char *__src = p1.data();
        const char *pcVar2 = __src;
        char acStack94 [8];
        char acStack82 [10];
        void *auStack8c;
        bool bVar1;
        ECResult status;
        ECString strStack;
        while (true) {
            if (pcVar2 == __src + 0x1c || *pcVar2 == '\0') break;
            pcVar2++;
        }
        if (pcVar2 - __src == 0x1a) {
            memcpy(acStack94, __src, 0x1c);
            bVar1 = true;
        } else if (pcVar2 - __src == 0x10) {
            memset(acStack94, 0, 4);
            memset(acStack94, 0x30, 0x12);
            strcpy(acStack82, __src + 8);
            memcpy(auStack8c, __src, 8);
            bVar1 = true;
        } else {
            logmsg(ECLogLevel_Error, "Invalid ECard len %d\n");
            bVar1 = false;
        }
        if (bVar1) {
            p2 = strStack.substr(0, 0);
            
            status = ECResult_Success;
        } else {
            pcVar2 = p1.data();
            logmsg(ECLogLevel_Info, "reformatEcard: invalid ecard %s\n", pcVar2);
            status = ECResult_InvalidECard;
        }
        return status;
    }

    
};