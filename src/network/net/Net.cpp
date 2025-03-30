#include "net/Net.h"
#include "NetworkEmulator.h"
#include "Platform/SystemChecker.h"
#include "net/NetMessenger.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/SessionSearcher.h"
#include "net/VoiceChatMgr.h"
#include "net/WiiFriendMgr.h"
#include "network/Core/Core.h"
#include "network/Platform/MemoryManager.h"
#include "meta_band/BandNetGameData.h"
#include "net/SyncStore.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/DiscErrorMgr_Wii.h"
#include "os/PlatformMgr.h"
#include "revolution/os/OSThread.h"
#include "rndobj/Overlay.h"
#include "utl/MemMgr.h"

Net TheNet;
WiiDiscErrorSessionTerminatior TheWiiDiscErrorSessionTerminator;

void TerminateTheNet() { TheNet.Terminate(); }

Net::Net() : mGameData(0), mSession(0), mSearcher(0), mServer(0), mNetOverlay(0) {}

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
    TheServer->Init();
    mServer = TheServer;
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

void Net::Terminate() {}

NetGameData *Net::GetGameData() {
    MILO_ASSERT(mGameData, 0x130);
    return mGameData;
}