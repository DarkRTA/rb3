#include "meta_band/NetSync.h"
#include "LockStepMgr.h"
#include "obj/Dir.h"
#include "os/Debug.h"

NetSync* TheNetSync;

namespace {
    void RegisterNetMessages(){

    }
}

void NetSync::Init(){
    MILO_ASSERT(!TheNetSync, 0x37);
    TheNetSync = new NetSync();
    TheNetSync->SetName("net_sync", ObjectDir::Main());
    RegisterNetMessages();
}

void NetSync::Terminate(){
    MILO_ASSERT(TheNetSync, 0x40);
    RELEASE(TheNetSync);
}

NetSync::NetSync() : unk1c(1), unk20(0), unk24(-1), unk28(0), unk29(0), mUILockStep(new LockStepMgr("ui_lock_step", this)) {

}

NetSync::~NetSync(){
    delete mUILockStep;
}