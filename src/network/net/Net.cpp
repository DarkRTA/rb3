#include "net/Net.h"
#include "meta_band/BandNetGameData.h"
#include "net/SyncStore.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "rndobj/Overlay.h"

Net::Net() : mGameData(0), mSession(0), unk24(0), mServer(0), mNetOverlay(0) {

}

void Net::Init(){
    SetName("net", ObjectDir::Main());
    mNetOverlay = RndOverlay::Find("network", false);
    mSyncStore = new SyncStore();
}

NetGameData* Net::GetGameData(){
    MILO_ASSERT(mGameData, 0x130);
    return mGameData;
}