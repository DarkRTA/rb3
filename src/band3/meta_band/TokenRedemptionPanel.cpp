#include "meta_band/TokenRedemptionPanel.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "meta_band/AppLabel.h"
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/JoypadMsgs.h"
#include "ui/UIListLabel.h"
#include "ui/UIPanel.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

TokenRedemptionPanel::TokenRedemptionPanel()
    : mRedemptionState(0), mListData(0, String()), mSelectedOfferIndex(0),
      mEnumeration(0), mPurchaser(0) {}

void TokenRedemptionPanel::Text(int, int data, UIListLabel *slot, UILabel *label) const {
    MILO_ASSERT(mListData.size() > data, 0x26);
    if (slot->Matches("name")) {
        AppLabel *appLabel = dynamic_cast<AppLabel *>(label);
        appLabel->SetTokenRedemptionString(this, data);
    } else
        label->SetTextToken(gNullStr);
}

int TokenRedemptionPanel::NumData() const { return mListData.size(); }
const char *TokenRedemptionPanel::GetListString(int i) const {
    return mListData[i].c_str();
}

void TokenRedemptionPanel::Enter() {
    UIPanel::Enter();
    mRedemptionState = 0;
}

UNPOOL_DATA
void TokenRedemptionPanel::Poll() {
    UIPanel::Poll();
    switch (mRedemptionState) {
    case 3:
    case 6:
        MILO_ASSERT(mEnumeration, 0x4A);
        mEnumeration->Poll();
        if (!mEnumeration->IsEnumerating()) {
            bool succ = mEnumeration->IsSuccess();
            if (!succ && mRedemptionState == 6) {
                succ = true;
            }
            if (succ) {
                if (mRedemptionState != 6) {
                    static Message token_msg("token_redemption_msg", gNullStr);
                    token_msg[0] = token_redemption_ready;
                    HandleType(token_msg);
                } else {
                    static Message offersReadyMsg("token_offers_ready");
                    HandleType(offersReadyMsg);
                }
            } else {
                static Message token_msg("token_redemption_msg", gNullStr);
                if (mRedemptionState == 6) {
                    token_msg[0] = token_error_no_previous_offers;
                } else {
                    token_msg[0] = token_redemption_error;
                }
                HandleType(token_msg);
            }
            mRedemptionState = 0;
            RELEASE(mEnumeration);
        }
        break;
    case 7:
        MILO_ASSERT(mPurchaser, 0xA8);
        mPurchaser->Poll();
        if (!mPurchaser->IsEnumerating()) {
            if (!mPurchaser->IsSuccess()) {
                mRedemptionState = 0;
                static Message token_msg("token_redemption_msg", gNullStr);
                token_msg[0] = token_redemption_error;
                HandleType(token_msg);
            } else {
                mPurchaser->Poll();
                mRedemptionState = 0;
                static Message checkout_msg("checkout_finished", 0);
                checkout_msg[0] = mPurchaser->IsSuccess();
                HandleType(checkout_msg);
            }
            MILO_ASSERT(mRedemptionState != kPurchasing, 0xCB);
            RELEASE(mPurchaser);
        }
        break;
    default:
        break;
    }
}
END_UNPOOL_DATA

void TokenRedemptionPanel::Unload() {
    TheRockCentral.CancelOutstandingCalls(this);
    mResultList.Clear();
    mListData.clear();
    RELEASE(mEnumeration);
    RELEASE(mPurchaser);
    UIPanel::Unload();
}

void TokenRedemptionPanel::GetOffersForToken(const char *token, LocalBandUser *user) {
    mActiveToken = token;
    mResultList.Clear();
    int id = TheServer->GetMasterProfileID();
    mRedemptionState = 2;
    TheRockCentral.RedeemToken(id, mActiveToken.c_str(), mResultList, this);
}

void TokenRedemptionPanel::GetPreviousOffersForUser(LocalBandUser *user) {
    mResultList.Clear();
    int id = TheServer->GetMasterProfileID();
    mRedemptionState = 5;
    TheRockCentral.GetRedeemedTokensByPlayer(id, mResultList, this);
}

void TokenRedemptionPanel::EnumerateOffers(LocalBandUser *user) { DataNode n38(0); }

BEGIN_HANDLERS(TokenRedemptionPanel)
    HANDLE_ACTION(
        get_offers_for_token, GetOffersForToken(_msg->Str(2), _msg->Obj<LocalBandUser>(3))
    )
    HANDLE_ACTION(
        get_previous_offers, GetPreviousOffersForUser(_msg->Obj<LocalBandUser>(2))
    )
    HANDLE_ACTION(
        show_purchase_ui_for_offer,
        ShowPurchaseUIForOffer(_msg->Int(2), _msg->Obj<LocalBandUser>(3))
    )
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x23C)
END_HANDLERS