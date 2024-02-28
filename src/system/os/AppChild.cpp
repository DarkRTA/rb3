#include "os/AppChild.h"
#include "obj/Data.h"

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

void AppChild::Terminate(){
    delete TheAppChild;
    TheAppChild = 0;
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
