#include "os/AppChild.h"
#include "obj/Data.h"
#include "utl/Option.h"
#include "obj/DataFunc.h"
#include "os/NetStream.h"
#include "os/Debug.h"

AppChild* TheAppChild;

static DataNode EnableAppChild(DataArray* array){
    if(TheAppChild) TheAppChild->mEnabled = true;
    return DataNode(0);
}

static DataNode DisableAppChild(DataArray* array){
    if(TheAppChild) TheAppChild->mEnabled = false;
    return DataNode(0);
}

static DataNode SyncAppChild(DataArray* array){
    if(TheAppChild) TheAppChild->Sync();
    return DataNode(0);
}

void AppChild::Init(){
    bool appchildbool = OptionBool("app_child", false);
    if(appchildbool){
        MILO_ASSERT(!TheAppChild, 0x3B);
        TheAppChild = new AppChild(OptionStr("pipe_name", 0));
    }
    *DataVariable("app_child") = DataNode(appchildbool);
    DataRegisterFunc("enable_app_child", EnableAppChild);
    DataRegisterFunc("disable_app_child", DisableAppChild);
    DataRegisterFunc("sync_app_child", SyncAppChild);
}

void AppChild::Terminate(){
    delete TheAppChild;
    TheAppChild = 0;
}

extern unsigned int HolmesResolveIP();

AppChild::AppChild(const char* str) : mEnabled(1), mStream(0), mSync(0) {
    unsigned int theIP = HolmesResolveIP();
    NetAddress addr(theIP, 0x11BF);
    NetStream* net = new NetStream();
    net->ClientConnect(addr);
    mStream = net;
    TheDebug << MakeString("AppChild::Connect\n");
}

AppChild::~AppChild(){
    delete mStream;
}

void AppChild::Sync(){
    unsigned short lol = 1;
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
        cmd.mData->Load(*mStream);
        cmd.mData->Execute();
    }
    mSync = false;
}
