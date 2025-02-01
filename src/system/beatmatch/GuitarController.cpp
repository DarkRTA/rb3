#include "beatmatch/GuitarController.h"
#include "BeatMatchControllerSink.h"
#include "HitSink.h"
#include "beatmatch/BeatMatchControllerSink.h"
#include "beatmatch/HitSink.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/User.h"

GuitarController::GuitarController(
    User *user,
    const DataArray *cfg,
    BeatMatchControllerSink *bsink,
    bool disabled,
    bool lefty
)
    : BeatMatchController(user, cfg, lefty), mDisabled(disabled), mAutoSoloButtons(0),
      mFretMask(0), mShiftButtonMask(0), mSink(bsink), mControllerStyle(kPS2),
      mStrumBarButtons(), unk58(0) {
    JoypadSubscribe(this);
    Symbol cntType;
    if (cfg->FindData("controller_style", cntType, false)) {
        if (cntType == "ps2")
            mControllerStyle = kPS2;
        else if (cntType == "hx_ps3")
            mControllerStyle = kPS3;
        else if (cntType == "ro_ps3")
            mControllerStyle = kRoPS3;
        else if (cntType == "ro_xbox")
            mControllerStyle = kRoXbox;
        else if (cntType == "hx_xbox")
            mControllerStyle = kHxXbox;
        else if (cntType == "hx_wii")
            mControllerStyle = kHxWii;
        else
            MILO_FAIL("Bad controller style %s\n", cntType);
    }
    if (mControllerStyle == kHxXbox)
        unk58 = 3;
    if (mControllerStyle == kPS3)
        unk58 = 3;
    if (mControllerStyle == kHxWii)
        unk58 = 3;
    if (!disabled)
        ReconcileFretState();
    DataArray *strum_buttons = cfg->FindArray("strum_buttons", false);
    if (strum_buttons) {
        mStrumBarButtons.reserve(strum_buttons->Size() - 1);
        for (int i = 1; i < strum_buttons->Size(); i++) {
            mStrumBarButtons.push_back((JoypadButton)strum_buttons->Int(i));
        }
    } else {
        mStrumBarButtons.reserve(2);
        if (lefty) {
            mStrumBarButtons.push_back(kPad_DDown);
            mStrumBarButtons.push_back(kPad_DUp);
        } else {
            mStrumBarButtons.push_back(kPad_DUp);
            mStrumBarButtons.push_back(kPad_DDown);
        }
    }

    DataArray *shift_button_cfg = cfg->FindArray("shift_button", false);
    if (shift_button_cfg) {
        mShiftButtonMask = 1 << shift_button_cfg->Int(1);
    }
}

GuitarController::~GuitarController() { JoypadUnsubscribe(this); }

void GuitarController::Disable(bool b) {
    mDisabled = b;
    if (b) {
        for (int i = 0; i < 5; i++) {
            if (mFretMask & 1 << i) {
                mSink->FretButtonUp(i);
            }
        }
        mFretMask = 0;
    } else
        ReconcileFretState();
}

float guitarwhammyprobs = 0.0f;

float GuitarController::GetWhammyBar() const {
    if (!mUser->IsLocal())
        return 0;
    else {
        LocalUser *lUser = mUser->GetLocalUser();
        if (!UserHasController(lUser))
            return 0.0f;
        JoypadData *thePadData = JoypadGetPadData(lUser->GetPadNum());
        DataArray *controllerArr = SystemConfig("joypad")->FindArray(
            Symbol("controllers"), JoypadControllerTypePadNum(lUser->GetPadNum())
        );
        bool b38;
        float f18;
        if (controllerArr->FindData("ly_whammy", b38, false)) {
            f18 = thePadData->GetLY();
        } else if (controllerArr->FindData("negative_rx_whammy_val", b38, false)) {
            f18 = -thePadData->GetRX();
        } else if (controllerArr->FindData("traditional_whammy_val", b38, false)) {
            f18 = -(thePadData->GetRX() + 1.0f) / 2.0f;
        }
        return std::min(0.0f, f18);
    }
}

float GuitarController::GetCapStrip() const { return 0.0f; }

void GuitarController::Poll() {
    bool idk;
    if (!mUser->IsLocal())
        return;
    else {
        LocalUser *lUser = mUser->GetLocalUser();
        if (!UserHasController(lUser))
            return;
        if (mDisabled)
            return;
        JoypadData *thePadData = JoypadGetPadData(lUser->GetPadNum());
        DataArray *found = SystemConfig("joypad")->FindArray(
            Symbol("controllers"), JoypadControllerTypePadNum(lUser->GetPadNum())
        );
        if (found->FindData("xbox_mercury_switch", idk, false)) {
            mSink->MercurySwitch(-thePadData->GetRY());
        } else if (found->FindData("ps3_mercury_switch", idk, false)) {
            mSink->MercurySwitch(thePadData->GetSX() * -4.65f);
        }
    }
}

int GuitarController::OnMsg(const ButtonDownMsg &msg) {
    if (mDisabled)
        return 0;
    if (!mUser->IsLocal())
        return 0;
    LocalUser *lUser = mUser->GetLocalUser();
    if (msg.GetUser() != lUser)
        return 0;
    MILO_ASSERT(mSink, 0xDB);
    int btn = msg.GetButton();
    std::vector<int>::iterator btnIter =
        std::find(mStrumBarButtons.begin(), mStrumBarButtons.end(), btn);
    if (btnIter != mStrumBarButtons.end()) {
        int slot = GetCurrentSlot();
        bool b8 = btnIter != mStrumBarButtons.begin();
        bool b1 = b8;
        if (mLefty)
            b1 = !b8;
        mSink->Swing(
            slot, true, b8, false, true, IsShifted() ? kGemHitFlagSolo : kGemHitFlagNone
        );
        RegisterHit(b1 ? kHitDownstrum : kHitUpstrum);
    } else {
        if (btn == mForceMercuryBut) {
            mSink->ForceMercurySwitch(true);
            RegisterHit(kHitSelect);
        } else if (mControllerStyle != kRoXbox && btn == unk58) {
            mSink->MercurySwitch(1);
        } else {
            int slot = ButtonToSlot((JoypadButton)btn);
            if (slot != -1) {
                mFretMask |= 1 << slot;
                mSink->FretButtonDown(slot, -1);
                if (mDisabled)
                    return 0;
                else {
                    lUser->GetPadNum();
                    bool shifted = IsShifted();
                    switch (slot) {
                    case 0:
                        RegisterHit(shifted ? kHitHighGreenFret : kHitGreenFret);
                        break;
                    case 1:
                        RegisterHit(shifted ? kHitHighRedFret : kHitRedFret);
                        break;
                    case 2:
                        RegisterHit(shifted ? kHitHighYellowFret : kHitYellowFret);
                        break;
                    case 3:
                        RegisterHit(shifted ? kHitHighBlueFret : kHitBlueFret);
                        break;
                    case 4:
                        RegisterHit(shifted ? kHitHighOrangeFret : kHitOrangeFret);
                        break;
                    }
                    if (shifted
                        && mSink->Swing(slot, false, true, true, false, kGemHitFlagSolo))
                        return 0;
                    mSink->NonStrumSwing(slot, true, shifted);
                }
            }
        }
    }
    return 0;
}

int GuitarController::OnMsg(const ButtonUpMsg &msg) {
    if (mDisabled)
        return 0;
    if (!mUser->IsLocal())
        return 0;
    LocalUser *lUser = mUser->GetLocalUser();
    if (msg.GetUser() != lUser)
        return 0;
    int btn = msg.GetButton();
    std::vector<int>::iterator btnIter =
        std::find(mStrumBarButtons.begin(), mStrumBarButtons.end(), btn);
    if (btnIter != mStrumBarButtons.end()) {
        mSink->ReleaseSwing();
    } else if (mControllerStyle != kRoXbox && btn == unk58) {
        mSink->MercurySwitch(0);
    } else if (btn == mForceMercuryBut) {
        mSink->ForceMercurySwitch(false);
    } else {
        int slot = ButtonToSlot((JoypadButton)btn);
        if (slot != -1) {
            mFretMask &= ~(1 << slot);
            mSink->FretButtonUp(slot);
            if (mFretMask) {
                int curSlot = GetCurrentSlot();
                mSink->NonStrumSwing(curSlot, false, IsShifted());
            }
        }
    }
    return 0;
}

void GuitarController::ReconcileFretState() {
    if (!mUser->IsLocal())
        return;
    //       iVar3 = (**(**(this + 0x1c) + 100))();
    //   if (iVar3 != 0) {
    //     iVar3 = (**(**(this + 0x1c) + 0x68))();
    //     iVar4 = UserHasController();
    //     if (iVar4 != 0) {
    //       (**(*(iVar3 + 4) + 0x10))(iVar3);
    //       uVar5 = JoypadGetPadData();
    //       uVar9 = 0;
    //       uVar8 = 0;
    //       do {
    //         uVar10 = 1 << (uVar8 & 0x3f);
    //         uVar2 = *(this + 0x40);
    //         uVar6 = (**(*this + 0x60))(this,uVar8);
    //         uVar7 = JoypadData::IsButtonInMask(uVar5,uVar6);
    //         if (uVar7 != 0) {
    //           uVar9 = uVar9 | uVar10;
    //         }
    //         if (((uVar2 & uVar10) != 0) != uVar7) {
    //           if (uVar7 == 0) {
    //             (**(**(this + 0x48) + 0x24))(*(this + 0x48),uVar8);
    //           }
    //           else {
    //             (**(**(this + 0x48) + 0x20))(*(this + 0x48),uVar8,0xffffffff);
    //           }
    //         }
    //         uVar8 = uVar8 + 1;
    //       } while (uVar8 < 5);
    //       *(this + 0x40) = uVar9;
    //       uVar6 = JoypadData::IsButtonInMask(uVar5,*(this + 0x20));
    //       (**(**(this + 0x48) + 0x1c))(*(this + 0x48),uVar6);
    //       if (*(this + 0x4c) != 3) {
    //         iVar3 = JoypadData::IsButtonInMask(uVar5,*(this + 0x58));
    //         if (iVar3 == 0) {
    //           fVar1 = 0.0;
    //         }
    //         else {
    //           fVar1 = 1.0;
    //         }
    //         (**(**(this + 0x48) + 0x18))(fVar1);
    //       }
    //     }
    //   }
    //   return;
}

bool GuitarController::IsShifted() const {
    if (!mUser->IsLocal())
        return false;
    else if (mAutoSoloButtons)
        return true;
    else {
        JoypadData *thePadData = JoypadGetPadData(mUser->GetLocalUser()->GetPadNum());
        unsigned int btns = thePadData->mButtons;
        return btns & mShiftButtonMask;
    }
}

BEGIN_HANDLERS(GuitarController)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_CHECK(0x1BA)
END_HANDLERS