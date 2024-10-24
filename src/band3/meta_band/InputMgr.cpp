#include "meta_band/InputMgr.h"
#include "game/BandUserMgr.h"
#include "meta_band/NetSync.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Dir.h"
#include "os/Debug.h"

InputMgr* TheInputMgr;

void InputMgr::Init(){
    MILO_ASSERT(!TheInputMgr, 0x28);
    TheInputMgr = new InputMgr(TheBandUserMgr, TheUIEventMgr, TheNetSync, TheSessionMgr);
    TheInputMgr->SetName("input_mgr", ObjectDir::Main());
}

void InputMgr::Terminate(){
    RELEASE(TheInputMgr);
}

InputMgr::InputMgr(BandUserMgr* umgr, UIEventMgr* emgr, NetSync* sync, SessionMgr* smgr) : mBandUserMgr(umgr), mEventMgr(emgr), mNetSync(sync), mSessionMgr(smgr), unk2c(0), unk2d(0), mUser(0) {

}