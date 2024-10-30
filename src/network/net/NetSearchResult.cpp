#include "net/NetSearchResult.h"
#include "MatchmakingSettings.h"
#include "NetSearchResult.h"
#include "NetSession.h"
#include "net/NetSession_RV.h"
#include "obj/ObjMacros.h"
#include "utl/BinStream.h"
#include "utl/MemStream.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

NetSearchResult* NetSearchResult::New(){ return new NetSearchResult(); }

NetSearchResult::NetSearchResult(){
    mSessionData = SessionData::New();
    mSettings = new MatchmakingSettings();
    MemStream stream(false);
    TheNetSession->mSettings->Save(stream);
    stream.Seek(0, BinStream::kSeekBegin);
    mSettings->Load(stream);
    mNumOpenSlots = TheNetSession->NumOpenSlots();
}

NetSearchResult::~NetSearchResult(){
    delete mSessionData;
    delete mSettings;
}

void NetSearchResult::Save(BinStream& bs) const {
    mSessionData->Save(bs);
    mSettings->Save(bs);
    bs << (unsigned char)mNumOpenSlots;
    bs << mHostName;
}

void NetSearchResult::Load(BinStream& bs){
    mSessionData->Load(bs);
    mSettings->Load(bs);
    unsigned char slots;
    bs >> slots;
    mNumOpenSlots = slots;
    bs >> mHostName;
}

bool NetSearchResult::Equals(const NetSearchResult* res) const {
    return mSessionData->Equals(res->mSessionData) &&
        mNumOpenSlots == res->mNumOpenSlots &&
        mHostName == res->mHostName;
}

BEGIN_HANDLERS(NetSearchResult)
    HANDLE_EXPR(get_mode_name, mSettings->mModeName)
    HANDLE_CHECK(0x4F)
END_HANDLERS