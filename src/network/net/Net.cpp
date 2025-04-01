#include "net/Net.h"
#include "NetworkEmulator.h"
#include "Platform/SystemChecker.h"
#include "net/NetMessenger.h"
#include "net/NetLog.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/SessionSearcher.h"
#include "net/VoiceChatMgr.h"
#include "net/WiiFriendMgr.h"
#include "net/WiiMessenger.h"
#include "network/Core/Core.h"
#include "network/Platform/MemoryManager.h"
#include "meta_band/BandNetGameData.h"
#include "net/SyncStore.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/DiscErrorMgr_Wii.h"
#include "os/PlatformMgr.h"
#include "revolution/os/OSThread.h"
#include "rndobj/Overlay.h"
#include "utl/MemMgr.h"
#include "utl/PoolAlloc.h"
#include "utl/Symbols.h"

Net TheNet;
WiiDiscErrorSessionTerminatior TheWiiDiscErrorSessionTerminator;

void WiiDiscErrorSessionTerminatior::DiscErrorStart() {
    if (TheNetSession) {
        TheNetSession->Disconnect();
    }
}

void TerminateTheNet() { TheNet.Terminate(); }

Net::Net() : mGameData(0), mSession(0), mSearcher(0), mServer(0), mNetOverlay(0) {}

// these smell like fakematches
void *QuazalMemAlloc(unsigned long ul) {
    ul += 4;
    void *_dest = _MemOrPoolAlloc(ul, FastPool);
    memcpy(_dest, &ul, 4);
    void *ret = (char *)_dest + 4;
    return ret;
}

void QuazalMemFree(void *v) {
    void *mem = (char *)v - 4;
    int dest;
    memcpy(&dest, mem, 4);
    _MemOrPoolFree(dest, FastPool, mem);
}

void Net::Init() {
    SetName("net", ObjectDir::Main());
    if (ThePlatformMgr.GetDiscErrorMgrWii()) {
        ThePlatformMgr.GetDiscErrorMgrWii()->RegisterCallback(
            &TheWiiDiscErrorSessionTerminator
        );
    }
    Quazal::Core::s_bUsesThreads = false;
    Quazal::MemoryManager::s_fcnMalloc = QuazalMemAlloc;
    Quazal::MemoryManager::s_fcnFree = QuazalMemFree;
    Quazal::MemoryManager::s_bIsMemoryFunctionSet = true;
    mNetOverlay = RndOverlay::Find("network", false);
    Quazal::SystemChecker::s_pfGetSystemCheckInfo = SystemCheckCallback;
    mSyncStore = new SyncStore();
    mSession = NetSession::New();
    mSearcher = SessionSearcher::New();
    TheServer.Init();
    mServer = &TheServer;
    mEmulator = new NetworkEmulator();
    mVoiceChatMgr = new VoiceChatMgr();
    TheNetMessenger.Init();
    TheWiiFriendMgr.Init();
    TheDebug.AddExitCallback(TerminateTheNet);
    mThreadStack = (unsigned char *)_MemAlloc(0x8000, 0x20);
    OSCreateThread(
        &mThread, QuazalUserThread, nullptr, mThreadStack + 0x8000, 0x8000, 0xF, 0
    );
    mThread.specific[0] = (void *)"Quazal";
    OSResumeThread(&mThread);
}

void Net::Terminate() {
    if (ThePlatformMgr.GetDiscErrorMgrWii()) {
        ThePlatformMgr.GetDiscErrorMgrWii()->UnregisterCallback(
            &TheWiiDiscErrorSessionTerminator
        );
    }
    TheWiiFriendMgr.Terminate();
    OSCancelThread(&mThread);
    if (mThreadStack) {
        _MemFree(mThreadStack);
        mThreadStack = nullptr;
    }
    delete mVoiceChatMgr;
    delete mEmulator;
    TheServer.Terminate();
    delete mSearcher;
    delete mSession;
    delete mSyncStore;
    TheDebug.RemoveExitCallback(TerminateTheNet);
}

void Net::Poll() {
    TheNetMessenger.Poll();
    TheWiiFriendMgr.Poll();
    TheWiiMessenger.Poll();
    mVoiceChatMgr->Poll();
    mSyncStore->Poll();
    mSession->Poll();
    mSearcher->Poll();
    mServer->Poll();
    if (mNetOverlay && mNetOverlay->Showing()) {
        UpdateNetOverlay();
    }
}

NetGameData *Net::GetGameData() {
    MILO_ASSERT(mGameData, 0x130);
    return mGameData;
}

void Net::SetGameData(NetGameData *data) {
    mGameData = data;
    mSearcher->AllocateNetSearchResults();
}

void Net::ToggleLogging() { NetLog.SetActive(!NetLog.IsActive()); }

void Net::UpdateNetOverlay() {
    if (mNetOverlay) {
        mNetOverlay->Clear();
        *mNetOverlay << "STATION LIST\n";
        MILO_WARN("*  0x%08X");
        MILO_WARN("   0x%08X");
        MILO_WARN(" [MASTER]");
        MILO_WARN("\n");
        MILO_WARN("NetSession State: %s\n");
    }
}

void Net::SystemCheckCallback(const char *msg, const char *file, unsigned int line) {
    MILO_FAIL("Quazal failure: \"%s\" - Line: %d in file: %s", msg, line, file);
}

BEGIN_HANDLERS(Net)
    HANDLE_ACTION(toggle_logging, ToggleLogging())
    HANDLE_MEMBER_PTR(mSearcher)
    HANDLE_MEMBER_PTR(mSession)
    HANDLE_CHECK(0x17A)
END_HANDLERS