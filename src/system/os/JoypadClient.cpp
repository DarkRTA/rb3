#include "os/JoypadClient.h"
#include "Joypad.h"
#include "JoypadClient.h"
#include "JoypadMsgs.h"
#include "os/Debug.h"
#include <algorithm>

bool gInited = false;
float gDefaultHoldMs = -1.0f;
float gDefaultRepeatMs = -1.0f;
std::vector<JoypadClient *> gClients;

namespace {
    JoypadButton LeftStickToDpad(JoypadButton btn){
        JoypadButton ret;
        switch(btn){
            case kPad_LStickUp: return kPad_DUp;
            case kPad_LStickDown: return kPad_DDown;
            case kPad_LStickLeft: return kPad_DLeft;
            case kPad_LStickRight: return kPad_DRight;
            default:
                MILO_FAIL("illegal button");
                return kPad_NumButtons;
        }
    }
}

JoypadRepeat::JoypadRepeat() : mLastBtn(kPad_NumButtons), mLastAction(kAction_None), mLastPad(-1) {
    
}

void JoypadRepeat::Start(JoypadButton btn, JoypadAction act, int pad){
    mHoldTimer.Reset();
    mRepeatTimer.Reset();
    mHoldTimer.Start();
    mLastBtn = btn;
    mLastAction = act;
    mLastPad = pad;
}

void JoypadRepeat::Reset(JoypadButton btn){
    if(mLastBtn == btn){
        mHoldTimer.Reset();
        mRepeatTimer.Reset();
    }
}

JoypadClient::JoypadClient(Hmx::Object *sink)
    : mUser(NULL), mSink(sink), mBtnMask(0), mHoldMs(-1.0f), mRepeatMs(-1.0f), mVirtualDpad(false), mFilterAllButStart(false) {
    MILO_ASSERT(sink, 148);
    Init();
}

JoypadClient::~JoypadClient() {
    JoypadUnsubscribe(this);
    gClients.erase(std::find(gClients.begin(), gClients.end(), this));
}

void JoypadClient::Init() {
    if (!gInited) {
        gClients.clear();

        gInited = true;
    }

    JoypadSubscribe(this);

    if (gDefaultHoldMs < 0.0f) {
        SystemConfig("joypad")->FindData("hold_ms", gDefaultHoldMs, true);
    }

    if (gDefaultRepeatMs < 0.0f) {
        SystemConfig("joypad")->FindData("repeat_ms", gDefaultRepeatMs, true);
    }

    mHoldMs = gDefaultHoldMs;
    mRepeatMs = gDefaultRepeatMs;

    gClients.push_back(this);
}

void JoypadClient::SetFilterAllButStart(bool ShouldWe) {
    if (mFilterAllButStart != ShouldWe) {
        if (ShouldWe) {
            for (int i = 0; i < 4; i++) {
                JoypadRepeat *Rep = &mRepeats[i];
                Rep->Reset(Rep->mLastBtn);
            }
        }
        mFilterAllButStart = ShouldWe;
    }
}

void JoypadClient::SetRepeatMask(int NewBtnMask) { mBtnMask = NewBtnMask; }
void JoypadClient::SetVirtualDpad(bool NewVirtualDpad) {
    mVirtualDpad = NewVirtualDpad;
}

void JoypadClient::Poll() {
    for (int i = 0; i < 4; i++) {
        mRepeats[i].Poll(mHoldMs, mRepeatMs, mSink, i);
    }
}

DataNode JoypadClient::OnMsg(const ButtonUpMsg &Msg) {}
DataNode JoypadClient::OnMsg(const ButtonDownMsg &Msg) {}

BEGIN_HANDLERS(JoypadClient)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x106)
END_HANDLERS

void JoypadClientPoll() {
    for (int i = 0; i < gClients.size(); i++) {
        gClients[i]->Poll();
    }
}
