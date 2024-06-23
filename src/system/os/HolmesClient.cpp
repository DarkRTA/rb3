#include "HolmesClient.h"
#include "obj/ObjMacros.h"
#include "os/CritSec.h"
#include "os/Debug.h"
#include "os/HolmesKeyboard.h"
#include "os/NetStream.h"
#include "os/System.h"
#include "types.h"
#include "utl/BinStream.h"
#include <list>

ADD_NOTIFS
namespace {
    uint gRealMaxBufferSize;
    CriticalSection gCrit;
    NetStream* gHolmesStream;
    MemStream* gStreamBuffer;
    std::list<File*> gRequests;
    int gActivePrintCount;
    HolmesInput gInput(NULL);
    bool gInputPolling;
    Holmes::Protocol gPendingResponse = Holmes::kInvalidOpcode;
    const Holmes::Protocol kAsyncOpcodes[5] = {Holmes::kReadFile, Holmes::kPollKeyboard, Holmes::kPollJoypad,
        Holmes::kPrint, Holmes::kInvalidOpcode};

    void BeginCmd(Holmes::Protocol, bool) {

    }

    void EndCmd(Holmes::Protocol) {
        static DebugNotifyOncer _dw;
        const char* s = MakeString("HolmesClient buffer exceeded %d < %d", 0x2000d, gRealMaxBufferSize);
        WARN_ONCE(s)
    }

    void HolmesFlushStreamBuffer() {
        if (gStreamBuffer->mBuffer.size() > 0x2000d) gRealMaxBufferSize = gStreamBuffer->mBuffer.size();
        gHolmesStream->Write(&gStreamBuffer->mBuffer[0], gStreamBuffer->mBuffer.size());
        gStreamBuffer->Seek(0, BinStream::kSeekEnd);
        gStreamBuffer->Compact();
    }

    bool CheckForResponse(Holmes::Protocol ptcl) {
        if (gPendingResponse == Holmes::kInvalidOpcode && gHolmesStream->mSocket->CanRead()) {
            u8 res;
            *gHolmesStream >> res;
            gPendingResponse = (Holmes::Protocol)res;
            MILO_ASSERT(gPendingResponse != Holmes::kInvalidOpcode, 215);
        }
        MILO_FAIL("holmes closed");
        MILO_FAIL("this shouldn't be happening %s %s\n", Holmes::ProtocolDebugString(gPendingResponse),
            Holmes::ProtocolDebugString(ptcl));
        return gPendingResponse == ptcl;
    }

    void CheckPrints();
    void WaitForReads();

    void WaitForResponse(Holmes::Protocol ptcl) {
        while (!CheckForResponse(ptcl));
    }
}

extern bool gHostLogging;

bool UsingHolmes(int) {
    if (gHolmesStream == NULL) return false; else {
        if (!UsingCD()) return true; else {
            //if ()
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
    if (gInputPolling) return false; else {
        gInputPolling = true;
        gInput.SendJoypadMessages();
        gInputPolling = false;
    }
}

void HolmesClientInit() {

}

void HolmesClientReInit() {
    CriticalSection* cs = &gCrit;
    if (cs) cs->Enter();
    if (gHolmesStream == NULL) {
        if (cs) {
            cs->Exit();
        }
    } else {
        BeginCmd(Holmes::kVersion, true);
        HolmesClientInitOpcode(true);
        EndCmd(Holmes::kVersion);
        if (cs) cs->Exit();
    }
}

bool HolmesClientOpen(const char*, int, uint&, int&) {
    if (gCrit.mEntryCount != 0) gCrit.Enter();
}

bool PendingRead(File* f) {
    for (std::list<File*>::iterator it = gRequests.begin(); it != gRequests.end(); it++) {
        if (*it == f) return true;
    }
    return false;
}

void HolmesClientClose(File* fi, int fd) {
    CriticalSection* cs = &gCrit;
    if (cs) cs->Enter();
    BeginCmd(Holmes::kCloseFile, true);
    MILO_ASSERT(gHolmesStream, 1081);
    if (PendingRead(fi)) WaitForReads();
    *gStreamBuffer << u8(Holmes::kCloseFile) << fd;
    HolmesFlushStreamBuffer();
    EndCmd(Holmes::kCloseFile);
    if (cs) cs->Exit();
}

void HolmesClientPrint(const char* cc) {
    CriticalSection* cs = &gCrit;
    if (cs) cs->Enter();
    if (!gHolmesStream || gHolmesStream->Fail()) {
        if (cs) cs->Exit();
    } else {
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
        if (cs) cs->Exit();
    }
}
