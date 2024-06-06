#include "ui/UI.h"
#include "os/JoypadClient.h"
#include "ui/UIScreen.h"
#include "rndobj/Overlay.h"
#include "utl/Symbols.h"

UIManager::UIManager() : mWentBack(0), mMaxPushDepth(100), mJoyClient(0), mSink(0), unk70(0), unk71(0), unk72(1), mOverlay(0), mRequireFixedText(0), unkb0(0), unkb5(0) {

}

UIManager::~UIManager(){

}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(UIManager)
    bool transitioning = false;
    bool block = false;
    if(InTransition() || InComponentSelect()) transitioning = true;
    if(transitioning){
        if(BlockHandlerDuringTransition(sym, _msg)) block = true;
    }
    if(block) return DataNode(0);
    HANDLE_MEMBER_PTR(mSink);
    HANDLE_ACTION(use_joypad, UseJoypad(_msg->Int(2), true))
    HANDLE_ACTION(set_virtual_dpad, mJoyClient->SetVirtualDpad(_msg->Int(2)))
    HANDLE_ACTION(push_screen, PushScreen(_msg->Obj<UIScreen>(2)))
    HANDLE_ACTION(pop_screen, if(_msg->Size() > 2) PopScreen(_msg->Obj<UIScreen>(2)); else PopScreen(0); )
    HANDLE_EXPR(pushed_screens, (int)mPushedScreens.size())
    HANDLE(goto_screen, OnGotoScreen)
    HANDLE(go_back_screen, OnGoBackScreen)
    HANDLE_ACTION(reset_screen, ResetScreen(_msg->Obj<UIScreen>(2)))
    HANDLE_EXPR(focus_panel, FocusPanel())
    HANDLE_EXPR(current_screen, CurrentScreen())
    HANDLE_EXPR(transition_screen, TransitionScreen())
    HANDLE_EXPR(bottom_screen, BottomScreen())
    HANDLE_EXPR(in_transition, InTransition())
    HANDLE(is_resource, OnIsResource)
    HANDLE_ACTION(foreach_screen, ForeachScreen(_msg))
    HANDLE_EXPR(went_back, WentBack())
    HANDLE_ACTION(dump_loaded_dirs, PrintLoadedDirs(_msg->Size() > 2 ? _msg->Str(2) : 0))
    HANDLE_ACTION(toggle_load_times, ToggleLoadTimes())
    HANDLE_EXPR(showing_load_times, mOverlay->Showing())
    HANDLE_ACTION(set_require_fixed_text, SetRequireFixedText(_msg->Int(2)))
    HANDLE_MEMBER_PTR(unkb0)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(mCurrentScreen)
    HANDLE_CHECK(0x4FF)
END_HANDLERS
#pragma pop