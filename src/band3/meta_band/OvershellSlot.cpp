#include "meta_band/OvershellSlot.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/PassiveMessage.h"
#include "meta_band/SessionUsersProviders.h"
#include "meta_band/CharProvider.h"
#include "meta_band/OvershellProfileProvider.h"
#include "meta_band/OvershellPartSelectProvider.h"
#include "meta_band/CymbalSelectionProvider.h"
#include "game/GameMessages.h"
#include "meta_band/ModifierMgr.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

OvershellSlot::OvershellSlot(int i, OvershellPanel* panel, OvershellDir* dir, BandUserMgr* umgr, SessionMgr* smgr) : mStateMgr(new OvershellSlotStateMgr()), mState(0), unk24(5), unk28(0x82),
    mOvershell(panel), mBandUserMgr(umgr), mSessionMgr(smgr), mSlotNum(i), mOvershellDir(dir), unk54(0), unk55(0), unk58(gNullStr), unk5c(0), mInGame(0), unk5e(0), unk80(0), unk81(0), unk84(0), unk88(0), unk90(0) {
    mMessageQueue = new PassiveMessageQueue(this);
    unk98 = new SessionUsersProvider(false, true, false);
    unk9c = new SessionUsersProvider(true, true, false);
    mCharProvider = new CharProvider(0, true, false);
    mSwappableProfilesProvider = new OvershellProfileProvider(mBandUserMgr);
    mPartSelectProvider = new OvershellPartSelectProvider(mOvershell);
    mCymbalProvider = new CymbalSelectionProvider(this);
    mSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
    mOvershellDir->HandleType(init_msg);
    static Message setupProviders(9);
    setupProviders.SetType("setup_providers");
    setupProviders[0] = mCharProvider;
    setupProviders[1] = mSwappableProfilesProvider;
    setupProviders[2] = 0;
    setupProviders[3] = mPartSelectProvider;
    setupProviders[4] = mCymbalProvider;
    setupProviders[5] = TheModifierMgr;
    mOvershellDir->HandleType(setupProviders);
    unk2c = mOvershellDir->Find<BandLabel>("user_name.lbl", true);
}

OvershellSlot::~OvershellSlot(){

}