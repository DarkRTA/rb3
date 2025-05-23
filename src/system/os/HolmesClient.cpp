#include "HolmesClient.h"
#include "milo_types.h"
#include "obj/DataFunc.h"
#include "os/AsyncFileHolmes.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "os/HolmesKeyboard.h"
#include "os/NetStream.h"
#include "os/NetworkSocket.h"
#include "os/System.h"
#include "types.h"
#include "utl/BinStream.h"
#include "utl/TextFileStream.h"
#include <cstring>
#include <list>

#define NETBIOS_NAME_MAX 64

namespace {
    // get ready for some bullshit
    struct HolmesProfileData {
        Timer wait;
        Timer work;
        u32 count;
        u32 pad2;

        HolmesProfileData() {}
    };

    struct ReadRequest {
        File *mRequestor;
        void *mBuffer;
        int mBytes;
    };

    int gRealMaxBufferSize;
    HolmesProfileData gProfile[20];
    CriticalSection gCrit;
    NetStream *gHolmesStream;
    MemStream *gStreamBuffer;
    std::list<ReadRequest *> gRequests;

    char gMachineName[NETBIOS_NAME_MAX] = { 0 };
    char gShareName[NETBIOS_NAME_MAX] = { 0 };

    String gServerName;

    bool gStackTraced = false;

    int gActivePrintCount;
    HolmesInput gInput(NULL);
    String gHolmesTarget;
    bool gInputPolling;
    Holmes::Protocol gPendingResponse = Holmes::kInvalidOpcode;
    const Holmes::Protocol kAsyncOpcodes[5] = { Holmes::kReadFile,
                                                Holmes::kPollKeyboard,
                                                Holmes::kPollJoypad,
                                                Holmes::kPrint,
                                                Holmes::kInvalidOpcode };

    void BeginCmd(Holmes::Protocol prot, bool b) {
        if (b) {
            gProfile[prot].count += 1;
        }
        gProfile[prot].work.Start();
    }

    void EndCmd(Holmes::Protocol prot) {
        gProfile[prot].work.Stop();
        if (gRealMaxBufferSize != 0) {
            MILO_NOTIFY_ONCE(
                "HolmesClient buffer exceeded %d < %d", 0x2000d, gRealMaxBufferSize
            );
        }
    }

    bool CheckForResponse(Holmes::Protocol ptcl);

    u32 CheckReads() {
        ReadRequest *currentRequest;
        do {
            if (gRequests.empty()) {
                return false;
            }
            if (!CheckForResponse(Holmes::kReadFile)) {
                return false;
            }
            BeginCmd(Holmes::kReadFile, false);
            currentRequest = gRequests.front();
            int r =
                gHolmesStream->ReadAsync(currentRequest->mBuffer, currentRequest->mBytes);
            gRequests.pop_back();
            EndCmd(Holmes::kReadFile);
        } while (currentRequest != NULL);
    }

    void WaitForResponse(Holmes::Protocol ptcl);

#pragma optimization_level 3
    void WaitForReads() {
        CritSecTracker cst(&gCrit);
        for (std::list<ReadRequest *>::iterator it = gRequests.begin();
             it != gRequests.end();
             it++) {
            WaitForResponse(Holmes::kReadFile);
            CheckReads();
        }
    }

    void HolmesFlushStreamBuffer() {
        if (gStreamBuffer->mBuffer.size() > 0x2000d)
            gRealMaxBufferSize = gStreamBuffer->mBuffer.size();
        gHolmesStream->Write(&gStreamBuffer->mBuffer[0], gStreamBuffer->mBuffer.size());
        gStreamBuffer->Seek(0, BinStream::kSeekEnd);
        gStreamBuffer->Compact();
    }

    bool CheckForResponse(Holmes::Protocol ptcl) {
        if (gPendingResponse == Holmes::kInvalidOpcode
            && gHolmesStream->mSocket->CanRead()) {
            u8 res;
            *gHolmesStream >> res;
            gPendingResponse = (Holmes::Protocol)res;
            MILO_ASSERT(gPendingResponse != Holmes::kInvalidOpcode, 215);
        }
        MILO_FAIL("holmes closed");
        MILO_FAIL(
            "this shouldn't be happening %s %s\n",
            Holmes::ProtocolDebugString(gPendingResponse),
            Holmes::ProtocolDebugString(ptcl)
        );
        return gPendingResponse == ptcl;
    }

    void WaitForAnyResponse(Holmes::Protocol ptcl) {
        printf(Holmes::ProtocolDebugString(ptcl));
    }

    void FinishResponse();

    bool CheckPrints() {
        if (CheckForResponse(Holmes::kPrint) != 0) {
            BeginCmd(Holmes::kPrint, false);
            u8 read;
            *gHolmesStream >> read;
            gActivePrintCount--;

            FinishResponse();
            EndCmd(Holmes::kPrint);
            return true;
        }
        return false;
    }

    void CheckInput() {
        if (CheckForResponse(Holmes::kPollKeyboard) != 0) {
            BeginCmd(Holmes::kPollKeyboard, true);
            gInput.LoadKeyboard(*gHolmesStream);
            FinishResponse();
            EndCmd(Holmes::kPollKeyboard);
        }
        if (CheckForResponse(Holmes::kPollJoypad) != 0) {
            BeginCmd(Holmes::kPollJoypad, true);
            gInput.LoadJoypad(*gHolmesStream);
            FinishResponse();
            EndCmd(Holmes::kPollJoypad);
        }
    }

    void WaitForResponse(Holmes::Protocol ptcl) {
        while (!CheckForResponse(ptcl)) {
            WaitForAnyResponse(ptcl);
            if (CheckReads() && ptcl == Holmes::kReadFile)
                return;
            CheckInput();
            if (CheckPrints() && ptcl == Holmes::kPrint)
                return;
        }
    }
    void FinishResponse() { gPendingResponse = Holmes::kInvalidOpcode; }
}

String gLastCachedResource;
u32 gLastCacheResult;
extern bool gHostConfig;
extern bool gHostLogging;

bool UsingHolmes(int flags) {
    if (gHolmesStream == NULL)
        return false;
    else {
        if (!UsingCD())
            return true;
        else {
            if (gHostConfig == false || (flags & 2) == 0) {
                if (gHostLogging == false || (flags & 4) == 0) {
                    return false;
                } else {
                    return true;
                }
            } else {
                return true;
            }
        }
    }
}

void HolmesClientPollKeyboard() {
    HolmesClientPoll();
    if (!gInputPolling) {
        gInputPolling = true;
        gInput.SendKeyboardMessages();
        gInputPolling = false;
    }
}

bool HolmesClientPollJoypad() {
    HolmesClientPoll();
    if (gInputPolling)
        return false;
    else {
        gInputPolling = true;
        gInput.SendJoypadMessages();
        gInputPolling = false;
    }
}

void HolmesSetFileShare(const char *machine_name, const char *share_name) {
    strncpy(gMachineName, machine_name, NETBIOS_NAME_MAX);
    strncpy(gShareName, share_name, NETBIOS_NAME_MAX);
}

char *HolmesFileShare() { return gShareName; }

NetAddress HolmesResolveIP() {
    String name(gMachineName);
    NetAddress addr(0, 0);
    int off = name.find(':');
    if (off != String::npos) {
        String port_str = name.substr(off + 1);
        name = name.substr(0, off);
        addr.mPort = (ushort)strtol(port_str.c_str(), nullptr, 0);
    } else
        addr.mPort = DEFAULT_PORT;
    uint ip = NetworkSocket::IPStringToInt(name);
    if (ip + 0x10000 != 0xffff) {
        addr.mIP = ip;
    }
    if (addr.mIP == 0) {
        name += ".harmonixmusic.com";
        int x;
        addr.mIP = x = NetworkSocket::ResolveHostName(name);
        if (x == 0 && gHostLogging == false) {
            MILO_FAIL("Couldn\'t resolve holmes_host: %s", String(name));
        }
    }
    return addr;
}

bool HolmesClientInitOpcode(bool r3) {
    bool fail = false;
    *gStreamBuffer << (char)Holmes::kVersion;
    *gStreamBuffer << 0x18; // version
    *gStreamBuffer << NetworkSocket::GetHostName();
    *gStreamBuffer << gHolmesTarget;
    *gStreamBuffer << gShareName;
    *gStreamBuffer << FileSystemRoot();
    *gStreamBuffer << (char)TheLoadMgr.GetPlatform(); // gPlatform?
    *gStreamBuffer << (char)GetGfxMode();
    HolmesFlushStreamBuffer();
    if (r3 == false) {
        WaitForAnyResponse(Holmes::kVersion);
        uchar successByte;
        *gHolmesStream >> successByte;
        fail = successByte;
    } else {
        WaitForResponse(Holmes::kVersion);
    }
    int holmesVersion = -1;
    if (fail == false) {
        *gHolmesStream >> holmesVersion;
        fail = holmesVersion != 0x18;
    }
    if (fail != false) {
        delete gHolmesStream;
        gHolmesStream = NULL;
        delete gStreamBuffer;
        gStreamBuffer = NULL;
        if (gHostLogging) {
            FinishResponse();
            return fail;
        }
        if (holmesVersion >= 0) {
            MILO_FAIL(
                "Holmes version mismatch\nResync/rebuild both projects\nHolmes=%d Console=%d",
                holmesVersion,
                0x18
            );
        } else {
            MILO_FAIL("Holmes protocol mismatch\nCould not connect to console");
        }
    }
    if (fail == false) {
        *gHolmesStream << gServerName;
    }
    if (fail == false && gShareName[0] != 0) {
        String machineName = gMachineName;
        String fileRoot;
        *gHolmesStream >> fileRoot;
        if (strlen(fileRoot.c_str()) == 0) {
            MILO_FAIL("Holmes fileroot missing!");
        }
        HolmesSetFileShare(machineName.c_str(), fileRoot.c_str());
    }
    FinishResponse();
    return fail;
}

static DataNode DumpHolmesLog(DataArray *) {
    TextFileStream *tfs = new TextFileStream("holmes.csv", true);
    if (!tfs->mFile.Fail()) {
        u32 read = gHolmesStream->mBytesRead;
        u32 written = gHolmesStream->mBytesWritten;
        {
            String hostname = NetworkSocket::GetHostName();
            tfs->Print(hostname.c_str());
            *tfs << ", ";
        }
        *tfs << read << ", ";
        *tfs << written << ", ";
    }
}

void HolmesClientInit() { DataRegisterFunc("", DumpHolmesLog); }

void HolmesClientReInit() {
    CritSecTracker cst(&gCrit);
    if (gHolmesStream == NULL) {
        return;
    } else {
        BeginCmd(Holmes::kVersion, true);
        HolmesClientInitOpcode(true);
        EndCmd(Holmes::kVersion);
    }
}

void HolmesClientPoll() {
    CritSecTracker cst(&gCrit);
    static bool skipIt;
    skipIt = !skipIt;
    if (skipIt) {
        return;
    }
    if (gHolmesStream == NULL) {
        return;
    }
    CheckInput();
    CheckReads();
    CheckPrints();
}

u32 HolmesClientSysExec(const char *filename) {
    CritSecTracker cst(&gCrit);
    BeginCmd(Holmes::kSysExec, true);

    MILO_ASSERT(gHolmesStream, 820);

    u8 b = Holmes::kSysExec;
    BinStream *holmes_strm = gStreamBuffer;
    *holmes_strm << b;
    *holmes_strm << filename;

    HolmesFlushStreamBuffer();
    WaitForResponse(Holmes::kSysExec);

    unsigned int return_code;
    *gHolmesStream >> return_code;

    FinishResponse();
    EndCmd(Holmes::kSysExec);

    return return_code;
}

FileStat *HolmesClientGetStat(const char *cc, FileStat &fs) {
    CritSecTracker cst(&gCrit);
    BeginCmd(Holmes::kGetStat, true);
    MILO_ASSERT(gHolmesStream, 840);
    u8 type = Holmes::kGetStat;
    *gStreamBuffer << type;
    *gStreamBuffer << cc;
    HolmesFlushStreamBuffer();
    WaitForResponse(Holmes::kGetStat);
    u8 b;
    *gHolmesStream >> b;
    bool b2 = b;
    if (b2)
        gHolmesStream >> fs;
    FinishResponse();
    EndCmd(Holmes::kGetStat);
    if (b2)
        return nullptr;
    return (FileStat *)-1;
}

bool HolmesClientOpen(const char *filepath, int flags, uint &result, int &r6) {
    gCrit.Enter();
    if (gHostLogging) {
        if ((flags & 4) == 0) {
            if (gHostConfig == false) {
                MILO_FAIL("gHostLogging tried to read file: %s", filepath);
            }
        } else if (gHolmesStream == NULL) {
            gCrit.Exit();
            return false;
        }
    }
    MILO_ASSERT(gHolmesStream, 944);

    if (!gHolmesStream->Fail()) {
        BeginCmd(Holmes::kOpenFile, true);
        bool someFlagSet = (bool)(flags >> 1 & 1);
        *gStreamBuffer << (char)Holmes::kOpenFile;
        *gStreamBuffer << filepath;
        *gStreamBuffer << someFlagSet; // write?
        *gStreamBuffer << (bool)((flags >> 18) & 1);
        if (!someFlagSet) {
            *gStreamBuffer << (bool)((flags >> 9) & 1);
            *gStreamBuffer << (bool)((flags >> 11) & 1);
        }
        HolmesFlushStreamBuffer();
        WaitForResponse(Holmes::kOpenFile);
        uint returnCode;
        *gHolmesStream >> returnCode;
        if (returnCode != -1) {
            *gHolmesStream >> r6;
            result = returnCode;
        }
        FinishResponse();
        EndCmd(Holmes::kOpenFile);
        if (returnCode == -1) {
            gCrit.Exit();
            return false;
        } else {
            gCrit.Exit();
            return true;
        }
    }

    gCrit.Exit();
    return false;
}

void HolmesClientWrite(int file, int offset, int length, const void *data) {
    if (length == 0)
        return;
    gCrit.Enter();
    MILO_ASSERT(gHolmesStream, 944);

    if (!gHolmesStream->Fail() || gHostLogging == false) {
        BeginCmd(Holmes::kWriteFile, true);
        *gStreamBuffer << (char)Holmes::kWriteFile;
        *gStreamBuffer << file;
        *gStreamBuffer << offset; // write?
        *gStreamBuffer << length;
        gStreamBuffer->Write(data, length);
        HolmesFlushStreamBuffer();
        WaitForResponse(Holmes::kWriteFile);
        uint returnCode;
        *gHolmesStream >> returnCode;
        FinishResponse();
        EndCmd(Holmes::kWriteFile);
    }

    gCrit.Exit();
    return;
}

void HolmesClientTruncate(int a, int b) {
    CritSecTracker cst(&gCrit);
    MILO_ASSERT(gHolmesStream, 1011);
    if (gHolmesStream->Fail() && gHostLogging)
        return;
    BeginCmd(Holmes::kTruncateFile, 1);
    u8 type = (u8)Holmes::kTruncateFile;
    int one = a, two = b;
    BinStream &bs = *gStreamBuffer;
    bs << type;
    bs << one;
    bs << two;
    HolmesFlushStreamBuffer();
    WaitForResponse(Holmes::kTruncateFile);
    int x;
    *gHolmesStream >> x;
    FinishResponse();
    EndCmd(Holmes::kTruncateFile);
}

bool PendingRead(File *f) {
    for (std::list<ReadRequest *>::iterator it = gRequests.begin(); it != gRequests.end();
         it++) {
        if ((*it)->mRequestor == f)
            return true;
    }
    return false;
}

bool HolmesClientReadDone(File *f) {
    CritSecTracker cst(&gCrit);
    u32 ret = PendingRead(f);
    if (ret) {
        HolmesClientPoll();
        ret = PendingRead(f);
    }
    return !ret;
}

void HolmesClientClose(File *fi, int fd) {
    CriticalSection *cs = &gCrit;
    if (cs)
        cs->Enter();
    BeginCmd(Holmes::kCloseFile, true);
    MILO_ASSERT(gHolmesStream, 1081);
    if (PendingRead(fi))
        WaitForReads();
    *gStreamBuffer << u8(Holmes::kCloseFile) << fd;
    HolmesFlushStreamBuffer();
    EndCmd(Holmes::kCloseFile);
    if (cs)
        cs->Exit();
}

void HolmesClientPrint(const char *cc) {
    CritSecTracker cst(&gCrit);
    if (gHolmesStream == nullptr || gHolmesStream->Fail())
        return;

    BeginCmd(Holmes::kPrint, true);
    *gStreamBuffer << u8(Holmes::kPrint);
    *gStreamBuffer << cc;
    HolmesFlushStreamBuffer();
    gActivePrintCount++;
    if (gActivePrintCount > 2) {
        WaitForResponse(Holmes::kPrint);
        CheckPrints();
    }
    EndCmd(Holmes::kPrint);
}

void HolmesClientStackTrace(const char *cc, unsigned int *ui, int i, String &s) {
    s = "";
    CritSecTracker cst(&gCrit);
    if (gHolmesStream == nullptr || gHolmesStream->Fail())
        return;
    BeginCmd(Holmes::kStackTrace, true);
    u8 type = Holmes::kStackTrace;
    *gStreamBuffer << type;
    *gStreamBuffer << cc;
    *gStreamBuffer << i;
    int x = 0;
    while (x < i) {
        *gStreamBuffer << ui[x];
        x++;
    }

    HolmesFlushStreamBuffer();
    gStackTraced = true;
    WaitForResponse(Holmes::kStackTrace);
    *gHolmesStream >> s;
    FinishResponse();
    EndCmd(Holmes::kStackTrace);
}
