#pragma once
#include "game/BandUser.h"
#include "meta/Profile.h"
#include "meta_band/BandScreen.h"

class SigninScreen : public BandScreen {
public:
    SigninScreen();
    virtual ~SigninScreen();
    OBJ_CLASSNAME(SigninScreen);
    OBJ_SET_TYPE(SigninScreen);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual void Enter(UIScreen *);
    virtual void Exit(UIScreen *);

    LocalBandUser *GetUser();
    void ReEvaluateState();

    DataNode OnMsg(const SigninChangedMsg &);
    DataNode OnMsg(const UIChangedMsg &);

    bool mMustNotBeAGuest; // 0x3c
    bool mMustBeOnline; // 0x3d
    bool mMustBeMultiplayerCapable; // 0x3e
    bool mHandleSignOuts; // 0x3f
    bool mLimitUserSignin; // 0x40
    bool unk41; // 0x41 - mSigninMsgDuringGuide?
};