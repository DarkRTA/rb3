#include "os/AppChild.h"
#include "obj/Data.h"
#include "os/HolmesClient.h"
#include "utl/Option.h"
#include "obj/DataFunc.h"
#include "os/NetStream.h"
#include "os/Debug.h"

AppChild* TheAppChild;


static DataNode EnableAppChild(DataArray*){
    if(TheAppChild) TheAppChild->SetEnabled(true);
    return DataNode(0);
}

static DataNode DisableAppChild(DataArray*){
    if(TheAppChild) TheAppChild->SetEnabled(false);
    return DataNode(0);
}

static DataNode SyncAppChild(DataArray*){
    if(TheAppChild) TheAppChild->Sync();
    return DataNode(0);
}

void AppChild::Init(){
    bool appchildbool = OptionBool("app_child", false);
    if(appchildbool){
        MILO_ASSERT(!TheAppChild, 0x3B);
        TheAppChild = new AppChild(OptionStr("pipe_name", 0));
    }
    DataVariable("app_child") = DataNode(appchildbool);
    DataRegisterFunc("enable_app_child", EnableAppChild);
    DataRegisterFunc("disable_app_child", DisableAppChild);
    DataRegisterFunc("sync_app_child", SyncAppChild);
}

void AppChild::Terminate(){
    delete TheAppChild;
    TheAppChild = 0;
}

AppChild::AppChild(const char* str) : mEnabled(1), mStream(0), mSync(0) {
    NetAddress addr(HolmesResolveIP().mIP, 0x11BF);
    NetStream* net = new NetStream();
    net->ClientConnect(addr);
    mStream = net;
    MILO_LOG("AppChild::Connect\n");
}

#ifndef MILO_DEBUG
NetAddress HolmesResolveIP() { // why
    return NetAddress();
}
#endif

AppChild::~AppChild(){
    delete mStream;
}

void AppChild::Sync(){
    short lol = 1;
    *mStream << lol;
    mStream->Flush();
    mSync = true;
}

void AppChild::Sync(unsigned short sh){
    *mStream << sh;
    mStream->Flush();
    mSync = true;
}

void AppChild::Poll(){
    if(!mStream) return;
    while(mEnabled && !mSync){
        DataArrayPtr cmd;
        *mStream >> cmd;
        cmd.mData->Execute();
    }
    mSync = false;
}
