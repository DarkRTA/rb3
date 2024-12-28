#include "os/JoypadClient.h"
#include "Joypad.h"
#include "JoypadClient.h"
#include "JoypadMsgs.h"
#include "os/Debug.h"
#include "os/UserMgr.h"
#include <algorithm>

float gDefaultHoldMs = -1.0f;
float gDefaultRepeatMs = -1.0f;
std::vector<JoypadClient *> gClients;

namespace {
    bool gInited = false;

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

    // Timer mHoldTimer; // 0x10
    // Timer mRepeatTimer; // 0x40

void JoypadRepeat::Poll(float f1, float f2, Hmx::Object* o, int i4){
    mHoldTimer.Pause();
    mRepeatTimer.Pause();
    float holdMs = mHoldTimer.Ms();
    float repeatMs = mRepeatTimer.Ms();
    mHoldTimer.Resume();
    mRepeatTimer.Resume();
    if(holdMs >= f1){
        SendRepeat(o, i4);
        mHoldTimer.Reset();
        mRepeatTimer.Start();
    }
    else if(repeatMs >= f2){
        SendRepeat(o, i4);
        mRepeatTimer.Reset();
        mRepeatTimer.Start();
    }
}

void JoypadRepeat::SendRepeat(Hmx::Object* o, int i){
    LocalUser* user = TheUserMgr ? TheUserMgr->GetLocalUserFromPadNum(i) : nullptr;
    o->Handle(ButtonDownMsg(user, mLastBtn, mLastAction, mLastPad), false);
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

static inline void InitClients(){
    if (!gInited) {
        gClients.clear();
        gInited = true;
    }
}

void JoypadClient::Init() {
    InitClients();
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

void JoypadClientPoll() {
    for (int i = 0; i < gClients.size(); i++) {
        gClients[i]->Poll();
    }
}

BEGIN_HANDLERS(JoypadClient)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_MEMBER_PTR(mSink)
    HANDLE_CHECK(0x106)
END_HANDLERS

bool JoypadClient::OnMsg(const ButtonDownMsg& msg){
    if(mFilterAllButStart && msg.GetAction() != kAction_Start) return 0;
    LocalUser* btnUser = msg.GetUser();
    if(mUser && btnUser != mUser) return 0;

    JoypadButton btn = msg.GetButton();
    if(mVirtualDpad && MovedLeftStick(btn)){
        JoypadButton dpadbtn = LeftStickToDpad(btn);
        mSink->Handle(ButtonDownMsg(btnUser, dpadbtn, msg.GetAction(), msg.GetPadNum()), false);
    }
    else {
        mSink->Handle(msg, false);
    }
    if(!btnUser) return 0;
    if(((1 << btn) & mBtnMask)){
        mRepeats[btnUser->GetPadNum()].Start(btn, msg.GetAction(), msg.GetPadNum());
        if(msg.GetAction() - 6U <= 3){
            for(int i = 0; i < 4; i++){
                if(i != btnUser->GetPadNum()){
                    if(ButtonToAction(mRepeats[i].mLastBtn, JoypadControllerTypePadNum(i)) - 6U <= 3){
                        mRepeats[i].mHoldTimer.Reset();
                        mRepeats[i].mRepeatTimer.Reset();
                    }
                }
            }
        }
    }
    return 0;
}

bool JoypadClient::OnMsg(const ButtonUpMsg& msg){
    if(mFilterAllButStart && msg.GetAction() != kAction_Start) return 0;
    if(msg.GetUser()){
        LocalUser* btnUser = msg.GetUser();
        if(mUser && btnUser != mUser) return 0;
        JoypadButton btn = msg.GetButton();
        if(mVirtualDpad && MovedLeftStick(btn)){
            JoypadButton dpadbtn = LeftStickToDpad(btn);
            mSink->Handle(ButtonUpMsg(btnUser, dpadbtn, msg.GetAction(), msg.GetPadNum()), false);
        }
        else {
            mSink->Handle(msg, false);
        }
        if(!btnUser) return 0;
        if(((1 << btn) & mBtnMask)){
            mRepeats[btnUser->GetPadNum()].Reset(btn);
        }
    }
    return 0;
}