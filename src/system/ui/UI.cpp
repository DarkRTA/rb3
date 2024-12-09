#include "ui/UI.h"
#include "CheatProvider.h"
#include "UIButton.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/DataUtl.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/JoypadClient.h"
#include "os/JoypadMsgs.h"
#include "os/Keyboard.h"
#include "os/System.h"
#include "rndobj/Cam.h"
#include "rndobj/Env.h"
#include "ui/LocalePanel.h"
#include "ui/UIGuide.h"
#include "ui/LabelNumberTicker.h"
#include "ui/LabelShrinkWrapper.h"
#include "ui/PanelDir.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "ui/UIPicture.h"
#include "ui/UIProxy.h"
#include "ui/UIScreen.h"
#include "ui/UISlider.h"
#include "ui/UITrigger.h"
#include "rndobj/Overlay.h"
#include "obj/Msg.h"
#include "obj/DataFile.h"
#include "utl/Loader.h"
#include "utl/Locale.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
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

inline Symbol Automator::CurScreenName(){
    UIScreen* curScreen = TheUI->CurrentScreen();
    if(curScreen){
        DataNode handled = curScreen->Handle(is_system_cheat_msg, false);
        if(handled == DataNode(kDataUnhandled, 0) || handled.Int() == 0){
            return curScreen->Name();
        }
    }
    return gNullStr;
}

inline void Automator::AddRecord(Symbol s, DataArray* arr){
    MILO_ASSERT(mRecord, 0x153);
    int recordSize = mRecord->Size();
    DataArray* addArr;
    if(CurRecordScreen() == s){
        addArr = mRecord->Array(recordSize - 1);
    }
    else {
        addArr = new DataArray(1);
        addArr->Node(0) = s;
        mRecord->Insert(recordSize, DataNode(addArr, kDataArray));
    }
    addArr->Insert(addArr->Size(), DataNode(arr, kDataArray));
}

inline DataNode Automator::OnMsg(const ButtonDownMsg& msg){
    Symbol screenName = CurScreenName();
    if(mRecord && !screenName.Null()){
        DataArrayPtr ptr(button_down, DataGetMacroByInt(msg.GetButton(), "kPad_"), DataGetMacroByInt(msg.GetAction(), "kAction_"), msg.GetPadNum());
        AddRecord(screenName, ptr);
    }
    return DataNode(kDataUnhandled, 0);
}

inline void Automator::HandleMessage(Symbol msgType){
    if(!TheUI->IsTransitioning()){
        if(mRecord){
            Symbol screenName = CurScreenName();
            if(!screenName.Null()){
                DataArrayPtr ptr(msgType);
                AddRecord(screenName, ptr);
            }
        }
        else if(mScreenScripts){
            AdvanceScript(msgType);
        }
    }
}

inline void Automator::AdvanceScript(Symbol msg){
    if(mCurScript){
        if(mCurScript->Array(mCurMsgIndex)->Sym(0) == msg){
            mFramesSinceAdvance = 0;
            mCurMsgIndex++;
            if(mCurMsgIndex >= mCurScript->Size()){
                mCurScript = 0;
                if(mCurScreenIndex == mScreenScripts->Size()){
                    TheUI->Handle(auto_script_done_msg, false);
                }
            }
        }
    }
}

DataNode Automator::OnMsg(const UIComponentSelectMsg& msg){
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnMsg(const UIComponentScrollMsg& msg){
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnMsg(const UIComponentFocusChangeMsg& msg){
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnMsg(const UIScreenChangeMsg& msg){
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnCheatInvoked(const DataArray* arr){
    if(!mRecord) goto ret;
    if(mSkipNextQuickCheat){
        mSkipNextQuickCheat = false;
        goto ret;
    }
    if(arr->Int(2) == 0) goto ret;
    Symbol screenName = CurScreenName();
    if(TheUI->CurrentScreen() && screenName.Null()){
        screenName = CurRecordScreen();
    }
    if(!screenName.Null()){
        DataArrayPtr ptr(quick_cheat, DataNode(arr->Array(3), kDataArray));
        AddRecord(screenName, ptr);      
    }
ret:
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnCustomMsg(const Message& msg){
    Symbol key = msg.Type();
    std::list<Symbol>::iterator it = mCustomMsgs.begin();
    for(; it != mCustomMsgs.end() && *it != key; ++it);
    if(it != mCustomMsgs.end()) HandleMessage(key);
    return DataNode(kDataUnhandled, 0);
}

UIManager::UIManager() : mWentBack(0), mMaxPushDepth(100), mJoyClient(0), mSink(0), unk70(0), unk71(0), unk72(1), mOverlay(0), mRequireFixedText(0), unkb0(0), unkb5(0) {

}

UIManager::~UIManager(){

}

void UITerminateCallback(){
    TheUI->Terminate();
}

void UIManager::Init(){
    unkb0 = new Automator();
    SetName("ui", ObjectDir::Main());
    DataArray* cfg = SystemConfig("ui");
    SetTypeDef(SystemConfig("ui"));
    UseJoypad(cfg->FindInt("use_joypad"), cfg->FindInt("enable_auto_repeat"));
    KeyboardSubscribe(this);
    mCurrentScreen = nullptr;
    mTransitionState = kTransitionNone;
    mTransitionScreen = nullptr;
    mWentBack = false;
    unk34 = ObjectDir::Main()->New<RndCam>("[ui.cam]");
    DataArray* camCfg = cfg->FindArray("cam", true);
    unk34->SetFrustum(camCfg->FindFloat("near"), camCfg->FindFloat("far"), camCfg->FindFloat("fov") * DEG2RAD, 1.0f);
    unk34->SetLocalPos(0, camCfg->FindFloat("y"), 0);
    DataArray* zArr = camCfg->FindArray("z-range", true);
    unk34->SetZRange(zArr->Float(1), zArr->Float(2));
    unk38 = Hmx::Object::New<RndEnviron>();
    Hmx::Color envAmbientColor;
    cfg->FindArray("env", true)->FindData("ambient", envAmbientColor, true);
    unk38->SetAmbientColor(envAmbientColor);
    cfg->FindData("max_push_depth", mMaxPushDepth, false);
    cfg->FindData("cancel_transition_notify", unk71, false);
    cfg->FindData("default_allow_edit_text", unk72, false);
    bool notify = false;
    cfg->FindData("verbose_locale_notifies", notify, false);
    SetLocaleVerboseNotify(notify);
    UIScreen::Init();
    UIPanel::Init();
    PanelDir::Init();
    UIComponent::Init();
    UIButton::Init();
    UIColor::Init();
    UILabel::Init();
    UIList::Init();
    UIPicture::Init();
    UIProxy::Init();
    UISlider::Init();
    UITrigger::Init();
    UIFontImporter::Init();
    UIGuide::Init();
    Screenshot::Init();
    LabelNumberTicker::Init();
    LabelShrinkWrapper::Init();
    TheDebug.AddExitCallback(UITerminateCallback);

    std::vector<ObjDirPtr<ObjectDir> > dirPtrs;
    DataArray* frontloadArr = cfg->FindArray("frontload_subdirs", false);
    if(frontloadArr){
        dirPtrs.resize(frontloadArr->Size() - 1);
        for(int i = 1; i < frontloadArr->Size(); i++){
            String curStr = frontloadArr->Str(i);
            dirPtrs[i - 1].LoadFile(curStr.c_str(), false, true, kLoadFront, false);
        }
    }
    
    CheatProvider::Init();
    LocalePanel::Init();
    Hmx::Object::Handle(cheat_init_msg, false);
    mOverlay = RndOverlay::Find("ui", true);
    mOverlay->SetOverlay(false);
    PreloadSharedSubdirs("ui");
    Hmx::Object::Handle(init_msg, false);
    mTimer.Restart();
    cfg->FindData("overload_horizontal_nav", unk70, false);
}

void UIManager::Terminate(){

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
    HANDLE_ACTION_IF_ELSE(pop_screen, _msg->Size() > 2,
        PopScreen(_msg->Obj<UIScreen>(2)),
        PopScreen(0)
    )
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
