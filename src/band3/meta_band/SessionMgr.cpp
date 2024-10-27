#include "meta_band/SessionMgr.h"
#include "BandMachineMgr.h"
#include "BandNetGameData.h"
#include "MetaMessages.h"
#include "game/BandUser.h"
#include "game/GameMessages.h"
#include "game/GameMode.h"
#include "math/Rand.h"
#include "meta_band/CriticalUserListener.h"
#include "net/NetSession.h"
#include "net/Synchronize.h"
#include "obj/Dir.h"
#include "os/User.h"

SessionMgr::SessionMgr(BandUserMgr* umgr, MatchMaker* mm) : Synchronizable("session_mgr"), mBandUserMgr(umgr), mMatchMaker(mm), mCritUserListener(0), mBandNetGameData(new BandNetGameData()), unk5c(0), unk70(0) {
    mMachineMgr = new BandMachineMgr(this, mBandUserMgr);
    mCritUserListener = new CriticalUserListener(this);
    unk40 = 0;
    unk44 = 5;
    unk48 = 0;
    SetName("session_mgr", ObjectDir::Main());
    mBandUserMgr->unk78 = this;
    mSession = TheNetSession;
    mSession->AddSink(this, SessionDisconnectedMsg::Type());
    mSession->AddSink(this, SessionBusyMsg::Type());
    mSession->AddSink(this, SigninChangedMsg::Type());
    mSession->AddSink(this, JoinResultMsg::Type());
    mSession->AddSink(this, ProcessedJoinRequestMsg::Type());
    mSession->AddSink(this, NewRemoteUserMsg::Type());
    mSession->AddSink(this, RemoteUserLeftMsg::Type());
    mSession->AddSink(this, LocalUserLeftMsg::Type());
    if(TheGameMode){
        TheGameMode->AddSink(this);
    }
    unk68 = false;
    mNetRandomSeed = RandomInt();
}

SessionMgr::~SessionMgr(){
    mSession->RemoveSink(this, SigninChangedMsg::Type());
    mSession->RemoveSink(this, SessionDisconnectedMsg::Type());
    mSession->RemoveSink(this, SessionBusyMsg::Type());
    mSession->RemoveSink(this, JoinResultMsg::Type());
    mSession->RemoveSink(this, ProcessedJoinRequestMsg::Type());
    mSession->RemoveSink(this, NewRemoteUserMsg::Type());
    mSession->RemoveSink(this, RemoteUserLeftMsg::Type());
    mSession->RemoveSink(this, LocalUserLeftMsg::Type());
    if(TheGameMode){
        TheGameMode->RemoveSink(this);
    }
    delete mMatchMaker;
    delete mBandNetGameData;
    delete mMachineMgr;
    delete mCritUserListener;
    SetName(0, ObjectDir::Main());
}