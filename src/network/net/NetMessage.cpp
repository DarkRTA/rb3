#include "NetMessage.h"
#include "os/Debug.h"

NetMessageFactory TheNetMessageFactory;

void NetMessageFactory::RegisterNetMessage(String type, NetMessageFunc* creator){
    for(int n = 0; n < mFactoryList.size(); n++){
        MILO_ASSERT(mFactoryList[n].mType != type, 0x16);
    }
    TypeCreatorPair tcPair;
    tcPair.mType = type;
    tcPair.mCreator = creator;
    mFactoryList.push_back(tcPair);
    MILO_ASSERT(mFactoryList.size() < 256, 0x23);
}

unsigned char NetMessageFactory::GetNetMessageByteCode(String type) const {
    for(int i = 0; i < mFactoryList.size(); i++){
        if(mFactoryList[i].mType == type) return i;
    }
    MILO_FAIL("No Registered NetMessage by this name %s", type);
    return 0;
}

NetMessage* NetMessageFactory::CreateNetMessage(unsigned char byteCode){
    MILO_ASSERT(byteCode < mFactoryList.size(), 0x36);
    return mFactoryList[byteCode].mCreator();
}