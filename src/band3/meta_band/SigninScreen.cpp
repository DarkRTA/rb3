#include "meta_band/SigninScreen.h"
#include "BandScreen.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta/Profile.h"
#include "meta_band/InputMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/User.h"
#include "ui/UIScreen.h"
#include "utl/Messages3.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

SigninScreen::SigninScreen()
    : mMustNotBeAGuest(0), mMustBeOnline(0), mMustBeMultiplayerCapable(0),
      mHandleSignOuts(0), mLimitUserSignin(0), unk41(0) {}

SigninScreen::~SigninScreen() {}

void SigninScreen::Poll() { UIScreen::Poll(); }

LocalBandUser *SigninScreen::GetUser() {
    LocalBandUser *user = nullptr;
    const DataNode *prop = Property(signing_in_user, false);
    if (prop) {
        user = prop->Obj<LocalBandUser>();
    }
    if (!user) {
        if (TheInputMgr->GetUser()) {
            user = TheInputMgr->GetUser()->GetLocalBandUser();
        } else
            user = nullptr;
    }
    return user;
}

void SigninScreen::Enter(UIScreen *screen) {
    BandScreen::Enter(screen);
    ThePlatformMgr.AddSink(this);
    mLimitUserSignin = Property(limit_user_signin)->Int();
    if (mLimitUserSignin) {
        BandUser *pUser = GetUser();
        if (!pUser) {
            MILO_FAIL("SigninScreen %s got NULL from GetUser()\n", Name());
        } else
            MILO_ASSERT(pUser->IsLocal(), 0x49);
    }
    mMustNotBeAGuest = Property(must_not_be_a_guest)->Int();
    mMustBeOnline = Property(must_be_online)->Int();
    mMustBeMultiplayerCapable = Property(must_be_multiplayer_capable)->Int();
    mHandleSignOuts = Property(handle_sign_outs)->Int();
}

void SigninScreen::Exit(UIScreen *s) {
    ThePlatformMgr.RemoveSink(this);
    BandScreen::Exit(s);
}

void SigninScreen::ReEvaluateState() {
    if (!GetUser())
        return;

    LocalBandUser *user = GetUser()->GetLocalBandUser();
    if ((mMustBeOnline && ThePlatformMgr.IsUserSignedIntoLive(user))
        || (mMustBeMultiplayerCapable && ThePlatformMgr.IsUserSignedIn(user)
            && ThePlatformMgr.UserHasOnlinePrivilege(user))) {
        bool b1 = true;
        if (mMustNotBeAGuest && ThePlatformMgr.IsUserAGuest(user))
            b1 = false;
        if (b1)
            Handle(on_signed_in_msg, true);
    }
}

DataNode SigninScreen::OnMsg(const SigninChangedMsg &msg) {
    std::vector<LocalBandUser *> &users = TheBandUserMgr->GetLocalBandUsers();
    FOREACH (it, users) {
        LocalBandUser *pUser = *it;
        MILO_ASSERT(pUser, 0xA4);
        if (!mLimitUserSignin || pUser == GetUser()) {
            bool isSignedIn = msg.GetMask() & (1 << pUser->GetPadNum());
            MILO_ASSERT(isSignedIn == ThePlatformMgr.IsUserSignedIn(pUser), 0xAE);
        }
    }
    return 0;
}

BEGIN_HANDLERS(SigninScreen)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(UIChangedMsg)
    HANDLE_SUPERCLASS(BandScreen)
    HANDLE_CHECK(0x11C)
END_HANDLERS