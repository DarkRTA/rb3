#include "meta_band/UGCPurchasePanel.h"
#include "meta/Profile.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"

UGCPurchasePanel::UGCPurchasePanel()
    : mPurchaseState(0), mUser(0), mSong(gNullStr), mOfferID(0), mPurchaser(0), unk4c(0) {
}

void UGCPurchasePanel::Enter() {
    MILO_ASSERT(kUninitialized == mPurchaseState, 0x22);
    UIPanel::Enter();
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
    unk4c = false;
    mPurchaseState = 1;
}

void UGCPurchasePanel::Exit() { UIPanel::Exit(); }

void UGCPurchasePanel::Unload() {}