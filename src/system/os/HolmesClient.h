#ifndef OS_HOLMESCLIENT_H
#define OS_HOLMESCLIENT_H

#include "os/File.h"
#include "types.h"
#include "utl/Str.h"

namespace Holmes {
    enum Protocol {
        kVersion,       // 0x0
        kSysExec,       // 0x1
        kGetStat,       // 0x2
        kOpenFile,      // 0x3
        kWriteFile,     // 0x4
        kReadFile,      // 0x5
        kCloseFile,     // 0x6
        kPrint,         // 0x7
        kMkDir,         // 0x8
        kDelete,        // 0x9
        kEnumerate,     // 0xa
        kCacheFile,     // 0xb
        kCompareFileTimes, // 0xc
        kTerminate,     // 0xd
        kCacheResource, // 0xe
        kPollKeyboard,  // 0xf
        kPollJoypad,    // 0x10
        kStackTrace,    // 0x11
        kSendMessage,   // 0x12
        kTruncateFile,  // 0x13
        kInvalidOpcode, // 0x14
    };

    inline const char* ProtocolDebugString(u8 c) {
        switch (c) {
            case 0:
                return "kVersion";
            case 1:
                return "kSysExec";
            case 2:
                return "kGetStat";
            case 3:
                return "kOpenFile";
            case 4:
                return "kWriteFile";
            case 5:
                return "kReadFile";
            case 6:
                return "kCloseFile";
            case 7:
                return "kPrint";
            case 8:
                return "kMkDir";
            case 9:
                return "kDelete";
            case 10:
                return "kEnumerate";
            case 11:
                return "kCacheFile";
            case 12:
                return "kCompareFileTimes";
            case 13:
                return "kTerminate";
            case 14:
                return "kCacheResource";
            case 15:
                return "kPollKeyboard";
            case 16:
                return "kPollJoypad";
            case 17:
                return "kStackTrace";
            case 18:
                return "kSendMessage";
            case 19:
                return "kTruncateFile";
            default:
                return "Unknown";
        }
    }
}

void HolmesClientInit();
void HolmesClientReInit();
void HolmesClientInitOpcode(bool);
void HolmesClientTerminate();
void HolmesClientEnumerate(const char*, void (*)(const char*, const char*), bool, const char*, bool);
bool HolmesClientOpen(const char*, int, uint&, int&);
void HolmesClientRead(int, int, int, void*, File*);
bool HolmesClientReadDone(File*);
void HolmesClientPrint(const char*);
void HolmesClientWrite(int, int, int, const void*);
void HolmesClientClose(File*, int);
void HolmesClientTruncate(int, int);

FileStat* HolmesClientGetStat(const char*, FileStat&);

bool UsingHolmes(int);
bool PendingRead(File*);

char* HolmesFileShare();

void HolmesClientPoll();
bool HolmesClientPollJoypad();
void HolmesClientPollKeyboard();

unsigned int HolmesResolveIP();

#endif
