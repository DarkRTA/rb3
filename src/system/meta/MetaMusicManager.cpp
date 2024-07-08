#include "meta/MetaMusicManager.h"
#include "obj/Dir.h"

MetaMusicManager* TheMetaMusicManager;

MetaMusicManager::MetaMusicManager(DataArray* da){
    MILO_ASSERT(!TheMetaMusicManager, 0x13);
    TheMetaMusicManager = this;
    SetName("metamusic_mgr", ObjectDir::Main());
    Init(da);
}

MetaMusicManager::~MetaMusicManager(){
    TheMetaMusicManager = 0;
    Cleanup();
}