#include "ui/UI.h"
#include "os/JoypadClient.h"
#include "ui/UIScreen.h"
#include "rndobj/Overlay.h"
#include "obj/MsgSource.h"
#include "obj/DataFile.h"
#include "utl/Symbols.h"

#include <algorithm>

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Automator)
    HANDLE_EXPR(toggle_auto, ToggleAuto())
    HANDLE_EXPR(auto_script, AutoScript())
    HANDLE_EXPR(toggle_record, ToggleRecord())
    HANDLE_EXPR(record_script, RecordScript())
    HANDLE_ACTION(set_auto_script, mAutoPath = _msg->Str(2))
    HANDLE_ACTION(set_record_script, mRecordPath = _msg->Str(2))
    HANDLE_ACTION(add_message_type, AddMessageType(_msg->Obj<MsgSource>(2), _msg->Sym(3)))
    HANDLE_CONDITION(!mScreenScripts && !mRecord, DataNode(kDataUnhandled, 0));
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(UIComponentSelectMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_MESSAGE(UIComponentFocusChangeMsg)
    HANDLE_MESSAGE(UIScreenChangeMsg)
    HANDLE(cheat_invoked, OnCheatInvoked)
    HANDLE_METHOD(OnCustomMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1B2)
END_HANDLERS
#pragma pop

inline void Automator::FinishRecord(){
    if(mRecord){
        MILO_ASSERT(!mRecordPath.empty(), 0x166);
        DataWriteFile(mRecordPath.c_str(), mRecord, 0);
    }
}

inline const char* Automator::ToggleAuto(){
    mCurScript = 0;
    if(mScreenScripts){
        mScreenScripts->Release();
        mScreenScripts = 0;
    }
    else {
        Loader* ldr = TheLoadMgr.AddLoader(FilePath(mAutoPath.c_str()), kLoadFront);
        DataLoader* dl = dynamic_cast<DataLoader*>(ldr);
        MILO_ASSERT(dl, 0x94);
        TheLoadMgr.PollUntilLoaded(dl, 0);
        mScreenScripts = dl->Data();
        mCurScreenIndex = 0;
        if(mScreenScripts){
            StartAuto(TheUI->CurrentScreen());
        }
    }
    return AutoScript();
}

inline void Automator::StartAuto(UIScreen* screen){
    MILO_ASSERT(mScreenScripts, 0xC4);
    mCurScript = 0;
    if(screen){
        mCurMsgIndex = 1;
        for(int i = mCurScreenIndex; i < mScreenScripts->Size(); i++){
            DataArray* arr = mScreenScripts->Array(i);
            if(arr->Sym(0) == screen->Name()){
                mCurScript = arr;
                mCurScreenIndex++;
                break;
            }
        }
    }
}

DataNode Automator::OnMsg(const UITransitionCompleteMsg& msg){
    if(mScreenScripts && !mRecord) StartAuto(msg.GetScreen1());
    return DataNode(kDataUnhandled, 0);
}

UIManager::UIManager() : mWentBack(0), mMaxPushDepth(100), mJoyClient(0), mSink(0), unk70(0), unk71(0), unk72(1), mOverlay(0), mRequireFixedText(0), unkb0(0), unkb5(0) {

}

UIManager::~UIManager(){

}

void UIManager::SendTransitionComplete(UIScreen* scr1, UIScreen* scr2){
    Handle(UITransitionCompleteMsg(scr1, scr2), false);
}

void UIManager::Draw(){
    for(std::vector<UIScreen*>::iterator it = mPushedScreens.begin(); it != mPushedScreens.end(); ++it){
        (*it)->Draw();
    }
    if(mCurrentScreen) mCurrentScreen->Draw();
}

void UIManager::GotoScreenImpl(UIScreen* scr, bool b1, bool b2){
    if(b1 || mTransitionState != kTransitionNone || mCurrentScreen != scr &&
        (mTransitionState != kTransitionTo && mTransitionState != kTransitionPop) ||
        mTransitionScreen != scr){
        CancelTransition();
        if(scr){
            for(std::vector<UIScreen*>::iterator it = mPushedScreens.begin(); it != mPushedScreens.end(); ++it){
                if(scr->SharesPanels(*it)){
                    MILO_FAIL("%s shares panels with %s", scr->Name(), (*it)->Name());
                }
            }
        }
        mWentBack = b2;
        UIScreenChangeMsg msg(scr, mCurrentScreen, b2);
        Handle(msg, false);
        mTransitionState = kTransitionTo;
        mTransitionScreen = scr;
        if(mCurrentScreen) mCurrentScreen->Exit(scr);
        else if(scr) scr->LoadPanels();
        if(mTransitionScreen){
            mOverlay->CurrentLine() = gNullStr;
            mLoadTimer.Restart();
        }
    }
}

UIResource* UIManager::FindResource(const DataArray* array) {
    if (!array) {
        return nullptr;
    }

    DataArray* fileArray = array->FindArray(resource_file, false);
    if (fileArray) {
        FilePath path(FileGetPath(fileArray->mFile.Str(), nullptr), fileArray->Str(1));

        std::pair<UIResource**, UIResource**> asdf = std::equal_range(
            mResources.begin(),
            mResources.end(),
            path.c_str(), UIResource::Compare()
        );

        if (asdf.first != asdf.second) {
            return *asdf.first;
        }
    }

    return nullptr;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(UIManager)
    HANDLE_CONDITION((InTransition() || InComponentSelect()) && BlockHandlerDuringTransition(sym, _msg), 0)
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
