#include "game/UITransitionNetMsgs.h"
#include "meta_band/LockMessages.h"
#include "obj/Dir.h"
#include "ui/UIScreen.h"

StartTransitionMsg::StartTransitionMsg(UIScreen *screen) {
    if (screen)
        mScreenName = screen->Name();
}

UIScreen *StartTransitionMsg::GetScreen() const {
    if (mScreenName.empty())
        return nullptr;
    else
        return ObjectDir::Main()->Find<UIScreen>(mScreenName.c_str(), true);
}

void StartTransitionMsg::Save(BinStream &bs) const {
    StartLockMsg::Save(bs);
    bs << mScreenName;
}

void StartTransitionMsg::Load(BinStream &bs) {
    StartLockMsg::Load(bs);
    bs >> mScreenName;
}

LockData *StartTransitionMsg::GetLockData() { return this; }

NetGotoScreenMsg::NetGotoScreenMsg(UIScreen *screen, bool f, bool b)
    : StartTransitionMsg(screen), mForce(f), mBack(b) {}

void NetGotoScreenMsg::Save(BinStream &bs) const {
    StartTransitionMsg::Save(bs);
    bs << mForce;
    bs << mBack;
}

void NetGotoScreenMsg::Load(BinStream &bs) {
    StartTransitionMsg::Load(bs);
    bs >> mForce;
    bs >> mBack;
}

NetSyncScreenMsg::NetSyncScreenMsg(UIScreen *screen, int depth)
    : StartTransitionMsg(screen), mDepth(depth) {}

void NetSyncScreenMsg::Save(BinStream &bs) const {
    StartTransitionMsg::Save(bs);
    bs << mDepth;
}

void NetSyncScreenMsg::Load(BinStream &bs) {
    StartTransitionMsg::Load(bs);
    bs >> mDepth;
}