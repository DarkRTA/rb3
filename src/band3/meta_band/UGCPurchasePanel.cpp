#include "meta_band/UGCPurchasePanel.h"
#include "meta/Profile.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentral.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
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

void UGCPurchasePanel::Unload() {
    mUser = nullptr;
    mPurchaseState = 0;
    ThePlatformMgr.RemoveSink(this, SigninChangedMsg::Type());
    mResultList.Clear();
    RELEASE(mPurchaser);
    UIPanel::Unload();
}

void UGCPurchasePanel::Poll() {
    UIPanel::Poll();
    switch (mPurchaseState) {
    case 1:
        if (!ThePlatformMgr.IsGuideShowing()) {
            mPurchaseState = 2;
            mResultList.Clear();
            TheRockCentral.GetSongFullOffer(
                TheSongMgr.GetSongIDFromShortName(mSong, true), mResultList, this
            );
        }
        break;
    case 2:
        break;
    case 3:
        mPurchaseState = 5;
        break;
    case 4:
        MILO_ASSERT(mPurchaser, 0x71);
        // more stuff happens here
        break;
    case 5:
        mPurchaseState = 0;
        Handle(checkout_failed_msg, false);
        break;
    case 6:
        mPurchaseState = 0;
        static Message msg("checkout_finished", 0);
        msg[0] = unk4c;
        Handle(msg, false);
        break;
    case 0:
        break;
    default:
        MILO_ASSERT(0, 0xA1);
        break;
    }
}

DataNode UGCPurchasePanel::OnMsg(const SigninChangedMsg &) {
    if (!ThePlatformMgr.IsUserSignedIn(mUser)) {
        if (TheUIEventMgr->CurrentTransitionEvent() != sign_out) {
            static Message init("init", 0);
            init[0] = 0;
            TheUIEventMgr->TriggerEvent(sign_out, init);
        }
        return 1;
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode UGCPurchasePanel::OnMsg(const RockCentralOpCompleteMsg &msg) {
    if (mPurchaseState == 2) {
        if (msg.Arg0()) {
            mResultList.Update(nullptr);
            DataNode n28;
            DataResult *res = mResultList.GetDataResult(0);
            res->GetDataResultValue("offer_id", n28);
            if (n28.Type() == kDataString) {
                mOfferID = n28.Str();
                mPurchaseState = 3;
                return 1;
            }
        }
    }
    mPurchaseState = 5;
    return 1;
}

BEGIN_HANDLERS(UGCPurchasePanel)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xD6)
END_HANDLERS

BEGIN_PROPSYNCS(UGCPurchasePanel)
    SYNC_PROP(song, mSong)
    SYNC_PROP(user, mUser)
END_PROPSYNCS