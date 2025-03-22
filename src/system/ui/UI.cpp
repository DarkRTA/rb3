#include "ui/UI.h"
#include "CheatProvider.h"
#include "UI.h"
#include "UIButton.h"
#include "UILabel.h"
#include "math/Rot.h"
#include "obj/Data.h"
#include "obj/DataUtl.h"
#include "obj/Dir.h"
#include "obj/DirLoader.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/Joypad.h"
#include "os/JoypadClient.h"
#include "os/JoypadMsgs.h"
#include "os/Keyboard.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "os/Timer.h"
#include "os/UserMgr.h"
#include "rndobj/Cam.h"
#include "rndobj/Env.h"
#include "ui/LocalePanel.h"
#include "ui/UIComponent.h"
#include "ui/UIGuide.h"
#include "ui/LabelNumberTicker.h"
#include "ui/LabelShrinkWrapper.h"
#include "ui/PanelDir.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "ui/UIPicture.h"
#include "ui/UIProxy.h"
#include "ui/UIResource.h"
#include "ui/UIScreen.h"
#include "ui/UISlider.h"
#include "ui/UITrigger.h"
#include "rndobj/Overlay.h"
#include "obj/Msg.h"
#include "obj/DataFile.h"
#include "utl/Cheats.h"
#include "utl/Loader.h"
#include "utl/Locale.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"
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

inline void Automator::FillButtonMsg(ButtonDownMsg &msg, int idx) {
    MILO_ASSERT(mCurScript, 0x145);
    DataArray *b = mCurScript->Array(idx);
    MILO_ASSERT(b->Sym(0) == button_down, 0x148);
    int padnum = b->Int(3);
    msg[0] = TheUserMgr->GetLocalUserFromPadNum(padnum);
    msg[1] = b->Int(1);
    msg[2] = b->Int(2);
    msg[3] = padnum;
}

inline void Automator::Poll() {
    static ButtonDownMsg b_msg(nullptr, kPad_NumButtons, kAction_None, -1);
    if (mCurScript) {
        mFramesSinceAdvance++;
        Symbol sym = mCurScript->Array(mCurMsgIndex)->Sym(0);
        if (sym == button_down) {
            FillButtonMsg(b_msg, mCurMsgIndex);
            AdvanceScript(b_msg.Message::Type());
            TheUI.Handle(b_msg, false);
        } else if (sym == quick_cheat) {
            DataArray *cheatArr = mCurScript->Array(1);
            AdvanceScript(quick_cheat);
            CallQuickCheat(cheatArr, nullptr);
        } else if (mCurMsgIndex > 1 && mFramesSinceAdvance > 0x1e) {
            mCurMsgIndex--;
            if (mCurScript->Array(mCurMsgIndex)->Sym(0) == button_down) {
                FillButtonMsg(b_msg, mCurMsgIndex);
                TheUI.Handle(b_msg, false);
            }
        }
    }
}

inline void Automator::FinishRecord() {
    if (mRecord) {
        MILO_ASSERT(!mRecordPath.empty(), 0x166);
        DataWriteFile(mRecordPath.c_str(), mRecord, 0);
    }
}

inline const char *Automator::ToggleAuto() {
    mCurScript = 0;
    if (mScreenScripts) {
        mScreenScripts->Release();
        mScreenScripts = 0;
    } else {
        Loader *ldr = TheLoadMgr.AddLoader(FilePath(mAutoPath.c_str()), kLoadFront);
        DataLoader *dl = dynamic_cast<DataLoader *>(ldr);
        MILO_ASSERT(dl, 0x94);
        TheLoadMgr.PollUntilLoaded(dl, 0);
        mScreenScripts = dl->Data();
        mCurScreenIndex = 0;
        if (mScreenScripts) {
            StartAuto(TheUI.CurrentScreen());
        }
    }
    return AutoScript();
}

inline void Automator::StartAuto(UIScreen *screen) {
    MILO_ASSERT(mScreenScripts, 0xC4);
    mCurScript = 0;
    if (screen) {
        mCurMsgIndex = 1;
        for (int i = mCurScreenIndex; i < mScreenScripts->Size(); i++) {
            DataArray *arr = mScreenScripts->Array(i);
            if (arr->Sym(0) == screen->Name()) {
                mCurScript = arr;
                mCurScreenIndex++;
                break;
            }
        }
    }
}

DataNode Automator::OnMsg(const UITransitionCompleteMsg &msg) {
    if (mScreenScripts && !mRecord)
        StartAuto(msg.GetScreen1());
    return DataNode(kDataUnhandled, 0);
}

inline Symbol Automator::CurScreenName() {
    UIScreen *curScreen = TheUI.CurrentScreen();
    if (curScreen) {
        DataNode handled = curScreen->Handle(is_system_cheat_msg, false);
        if (handled == DataNode(kDataUnhandled, 0) || handled.Int() == 0) {
            return curScreen->Name();
        }
    }
    return gNullStr;
}

inline void Automator::AddRecord(Symbol s, DataArray *arr) {
    MILO_ASSERT(mRecord, 0x153);
    int recordSize = mRecord->Size();
    DataArray *addArr;
    if (CurRecordScreen() == s) {
        addArr = mRecord->Array(recordSize - 1);
    } else {
        addArr = new DataArray(1);
        addArr->Node(0) = s;
        mRecord->Insert(recordSize, DataNode(addArr, kDataArray));
    }
    addArr->Insert(addArr->Size(), DataNode(arr, kDataArray));
}

inline DataNode Automator::OnMsg(const ButtonDownMsg &msg) {
    Symbol screenName = CurScreenName();
    if (mRecord && !screenName.Null()) {
        DataArrayPtr ptr(
            button_down,
            DataGetMacroByInt(msg.GetButton(), "kPad_"),
            DataGetMacroByInt(msg.GetAction(), "kAction_"),
            msg.GetPadNum()
        );
        AddRecord(screenName, ptr);
    }
    return DataNode(kDataUnhandled, 0);
}

inline void Automator::HandleMessage(Symbol msgType) {
    if (!TheUI.InTransition()) {
        if (mRecord) {
            Symbol screenName = CurScreenName();
            if (!screenName.Null()) {
                DataArrayPtr ptr(msgType);
                AddRecord(screenName, ptr);
            }
        } else if (mScreenScripts) {
            AdvanceScript(msgType);
        }
    }
}

inline void Automator::AdvanceScript(Symbol msg) {
    if (mCurScript) {
        if (mCurScript->Array(mCurMsgIndex)->Sym(0) == msg) {
            mFramesSinceAdvance = 0;
            mCurMsgIndex++;
            if (mCurMsgIndex >= mCurScript->Size()) {
                mCurScript = 0;
                if (mCurScreenIndex == mScreenScripts->Size()) {
                    TheUI.Handle(auto_script_done_msg, false);
                }
            }
        }
    }
}

DataNode Automator::OnMsg(const UIComponentSelectMsg &msg) {
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnMsg(const UIComponentScrollMsg &msg) {
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnMsg(const UIComponentFocusChangeMsg &msg) {
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnMsg(const UIScreenChangeMsg &msg) {
    HandleMessage(msg.Message::Type());
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnCheatInvoked(const DataArray *arr) {
    if (!mRecord)
        goto ret;
    if (mSkipNextQuickCheat) {
        mSkipNextQuickCheat = false;
        goto ret;
    }
    if (arr->Int(2) == 0)
        goto ret;
    Symbol screenName = CurScreenName();
    if (TheUI.CurrentScreen() && screenName.Null()) {
        screenName = CurRecordScreen();
    }
    if (!screenName.Null()) {
        DataArrayPtr ptr(quick_cheat, DataNode(arr->Array(3), kDataArray));
        AddRecord(screenName, ptr);
    }
ret:
    return DataNode(kDataUnhandled, 0);
}

DataNode Automator::OnCustomMsg(const Message &msg) {
    Symbol key = msg.Type();
    std::list<Symbol>::iterator it = mCustomMsgs.begin();
    for (; it != mCustomMsgs.end() && *it != key; ++it)
        ;
    if (it != mCustomMsgs.end())
        HandleMessage(key);
    return DataNode(kDataUnhandled, 0);
}

UIManager::UIManager()
    : mWentBack(0), mMaxPushDepth(100), mJoyClient(0), mSink(0),
      mOverloadHorizontalNav(0), mCancelTransitionNotify(0), mDefaultAllowEditText(1),
      mOverlay(0), mRequireFixedText(0), mAutomator(0), unkb5(0) {}

UIManager::~UIManager() {}

void UITerminateCallback() { TheUI.Terminate(); }

void UIManager::Init() {
    mAutomator = new Automator();
    SetName("ui", ObjectDir::Main());
    DataArray *cfg = SystemConfig("ui");
    SetTypeDef(SystemConfig("ui"));
    UseJoypad(cfg->FindInt("use_joypad"), cfg->FindInt("enable_auto_repeat"));
    KeyboardSubscribe(this);
    mCurrentScreen = nullptr;
    mTransitionState = kTransitionNone;
    mTransitionScreen = nullptr;
    mWentBack = false;
    mCam = ObjectDir::Main()->New<RndCam>("[ui.cam]");
    DataArray *camCfg = cfg->FindArray("cam", true);
    mCam->SetFrustum(
        camCfg->FindFloat("near"),
        camCfg->FindFloat("far"),
        camCfg->FindFloat("fov") * DEG2RAD,
        1.0f
    );
    mCam->SetLocalPos(0, camCfg->FindFloat("y"), 0);
    DataArray *zArr = camCfg->FindArray("z-range", true);
    mCam->SetZRange(zArr->Float(1), zArr->Float(2));
    mEnv = Hmx::Object::New<RndEnviron>();
    Hmx::Color envAmbientColor;
    cfg->FindArray("env", true)->FindData("ambient", envAmbientColor, true);
    mEnv->SetAmbientColor(envAmbientColor);
    cfg->FindData("max_push_depth", mMaxPushDepth, false);
    cfg->FindData("cancel_transition_notify", mCancelTransitionNotify, false);
    cfg->FindData("default_allow_edit_text", mDefaultAllowEditText, false);
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
    DataArray *frontloadArr = cfg->FindArray("frontload_subdirs", false);
    if (frontloadArr) {
        dirPtrs.resize(frontloadArr->Size() - 1);
        for (int i = 1; i < frontloadArr->Size(); i++) {
            String curStr = frontloadArr->Str(i);
            dirPtrs[i - 1].LoadFile(curStr.c_str(), false, true, kLoadFront, false);
        }
    }

    CheatProvider::Init();
    LocalePanel::Init();
    Hmx::Object::Handle(cheat_init_msg, false);
    mOverlay = RndOverlay::Find("ui", true);
    mOverlay->SetShowing(false);
    PreloadSharedSubdirs("ui");
    Hmx::Object::Handle(init_msg, false);
    mTimer.Restart();
    cfg->FindData("overload_horizontal_nav", mOverloadHorizontalNav, false);
}

void UIManager::Terminate() {
    CheatProvider::Terminate();
    UILabel::Terminate();
    SetName(0, 0);
    KeyboardUnsubscribe(this);
    RELEASE(mCam);
    RELEASE(mEnv);
    RELEASE(mJoyClient);
    for (std::vector<UIResource *>::iterator it = mResources.begin();
         it != mResources.end();
         ++it) {
        (*it)->ForceRelease();
    }
    for (std::vector<UIResource *>::iterator it = mResources.begin();
         it != mResources.end();
         ++it) {
        delete *it;
    }
    TheDebug.RemoveExitCallback(UITerminateCallback);
    RELEASE(mAutomator);
}

void UIManager::Poll() {
    UIList::CollectGarbage();
    mAutomator->Poll();
    TheTaskMgr.SetUISeconds(mTimer.SplitMs() / 1000.0f, false);
    for (std::vector<UIScreen *>::iterator it = mPushedScreens.begin();
         it != mPushedScreens.end();
         ++it) {
        (*it)->Poll();
    }
    if (mCurrentScreen)
        mCurrentScreen->Poll();
    if (mTransitionState == kTransitionTo) {
        START_AUTO_TIMER("ui_transition_to_poll");
        if ((!mTransitionScreen || mTransitionScreen->CheckIsLoaded())
            && (!mCurrentScreen || !mCurrentScreen->Exiting())
            && !IsBlockingTransition()) {
            UIScreen *trans = mTransitionScreen;
            mTransitionState = kTransitionFrom;
            mTransitionScreen = mCurrentScreen;
            mCurrentScreen = trans;
            if (trans) {
                if (trans->AllPanelsDown() && mPushedScreens.empty()
                    && IsTimelineResetAllowed()) {
                    mTimer.Restart();
                    TheTaskMgr.SetUISeconds(0, true);
                }
                TheLoadMgr.SetLoaderPeriod(10.0f);
                mCurrentScreen->Enter(mTransitionScreen);
            }
        } else if ((mTransitionScreen && !mTransitionScreen->CheckIsLoaded())
                   && (!mCurrentScreen || !mCurrentScreen->Exiting())) {
            TheLoadMgr.SetLoaderPeriod(26.67f);
        }
    }
    if (mTransitionState == kTransitionPop) {
        START_AUTO_TIMER("ui_transition_pop_poll");
        if (!mCurrentScreen || !mCurrentScreen->Exiting()) {
            if (mCurrentScreen)
                mCurrentScreen->UnloadPanels();
            UIScreen *oldCurScreen = mCurrentScreen;
            MILO_ASSERT(!mPushedScreens.empty(), 0x2AF);
            mCurrentScreen = mPushedScreens.back();
            mPushedScreens.pop_back();
            mTransitionState = kTransitionNone;
            if (mTransitionScreen == mCurrentScreen) {
                SendTransitionComplete(mCurrentScreen, oldCurScreen);
            } else
                GotoScreenImpl(mTransitionScreen, false, false);
        }
    }
    if (mTransitionState == kTransitionFrom) {
        START_AUTO_TIMER("ui_transition_from_poll");
        if (!mCurrentScreen || !mCurrentScreen->Entering()) {
            if (mOverlay->Showing() && mLoadTimer.Running()) {
                if (mCurrentScreen) {
                    mOverlay->CurrentLine() = MakeString(
                        "%s entered in %f seconds",
                        mCurrentScreen->Name(),
                        mLoadTimer.SplitMs() / 1000.0f
                    );
                    MILO_LOG("%s\n", mOverlay->CurrentLine());
                }
            }
            UIScreen *oldTrans = mTransitionScreen;
            mTransitionState = kTransitionNone;
            mTransitionScreen = nullptr;
            SendTransitionComplete(mCurrentScreen, oldTrans);
        }
    }
}

void UIManager::SendTransitionComplete(UIScreen *scr1, UIScreen *scr2) {
    Handle(UITransitionCompleteMsg(scr1, scr2), false);
}

void UIManager::Draw() {
    for (std::vector<UIScreen *>::iterator it = mPushedScreens.begin();
         it != mPushedScreens.end();
         ++it) {
        (*it)->Draw();
    }
    if (mCurrentScreen)
        mCurrentScreen->Draw();
}

void UIManager::CancelTransition() {
    if (mCancelTransitionNotify && mTransitionState != kTransitionNone
        && mTransitionState != kTransitionFrom) {
        MILO_WARN("Cancelled transition");
    }
    TransitionState oldState = mTransitionState;
    UIScreen *oldScreen = mTransitionScreen;
    mTransitionState = kTransitionNone;
    mTransitionScreen = nullptr;
    if (oldState == kTransitionTo) {
        if (mCurrentScreen) {
            TheLoadMgr.SetLoaderPeriod(10.0f);
            mCurrentScreen->Enter(oldScreen);
        } else if (oldScreen)
            oldScreen->UnloadPanels();
    } else if (oldState == kTransitionPop && mCurrentScreen) {
        TheLoadMgr.SetLoaderPeriod(10.0f);
        mCurrentScreen->Enter(nullptr);
    }
}

void UIManager::GotoScreenImpl(UIScreen *scr, bool b1, bool b2) {
    if (b1 || mTransitionState != kTransitionNone
        || mCurrentScreen != scr
            && (mTransitionState != kTransitionTo && mTransitionState != kTransitionPop)
        || mTransitionScreen != scr) {
        CancelTransition();
#ifdef MILO_DEBUG
        if (scr) {
            for (std::vector<UIScreen *>::iterator it = mPushedScreens.begin();
                 it != mPushedScreens.end();
                 ++it) {
                if (scr->SharesPanels(*it)) {
                    MILO_FAIL("%s shares panels with %s", scr->Name(), (*it)->Name());
                }
            }
        }
#endif
        mWentBack = b2;
        UIScreenChangeMsg msg(scr, mCurrentScreen, mWentBack);
        Handle(msg, false);
        mTransitionState = kTransitionTo;
        mTransitionScreen = scr;
        if (mCurrentScreen)
            mCurrentScreen->Exit(scr);
        else if (scr)
            scr->LoadPanels();
#ifdef MILO_DEBUG
        if (mTransitionScreen) {
            mOverlay->CurrentLine() = gNullStr;
            mLoadTimer.Restart();
        }
#endif
    }
}

void UIManager::GotoScreen(const char *name, bool b2, bool b3) {
    UIScreen *screen = ObjectDir::Main()->Find<UIScreen>(name, true);
    MILO_ASSERT(screen, 0x348);
    GotoScreen(screen, b2, b3);
}

void UIManager::GotoScreen(UIScreen *scr, bool b1, bool b2) {
    GotoScreenImpl(scr, b1, b2);
}

void UIManager::PushScreen(UIScreen *screen) {
    CancelTransition();
    MILO_ASSERT(mCurrentScreen, 0x358);
    MILO_ASSERT(screen, 0x359);
    for (std::vector<UIScreen *>::iterator it = mPushedScreens.begin();
         it != mPushedScreens.end();
         ++it) {
        if (screen == *it) {
            MILO_WARN("Don't push %s, it is already there!\n", screen->Name());
        }
    }
    mPushedScreens.push_back(mCurrentScreen);
    if (mPushedScreens.size() >= mMaxPushDepth) {
        MILO_WARN(
            "Exceeded max push depth of %i, pushing %s", mMaxPushDepth, screen->Name()
        );
        MILO_LOG("mPushedScreens:\n");
        for (std::vector<UIScreen *>::iterator it = mPushedScreens.begin();
             it != mPushedScreens.end();
             ++it) {
            MILO_LOG("%s\n", (*it)->Name());
        }
    }
    mCurrentScreen = nullptr;
    GotoScreenImpl(screen, false, false);
}

void UIManager::PopScreen(UIScreen *screen) {
    if (mPushedScreens.empty()) {
        MILO_WARN("No screen to pop\n");
    } else {
        GotoScreenImpl(nullptr, false, false);
        mTransitionState = kTransitionPop;
        if (screen)
            mTransitionScreen = screen;
        else
            mTransitionScreen = mPushedScreens.back();
    }
}

void UIManager::ResetScreen(UIScreen *screen) {
    if (mTransitionState != kTransitionNone && mTransitionState != kTransitionFrom) {
        bool old = mCancelTransitionNotify;
        mCancelTransitionNotify = false;
        CancelTransition();
        mCancelTransitionNotify = old;
    }
    if (mPushedScreens.empty()) {
        GotoScreen(screen, false, false);
    } else {
        MILO_ASSERT(mPushedScreens.size() == 1, 0x3A7);
        PopScreen(screen);
    }
}

bool UIManager::InComponentSelect() {
    if (mCurrentScreen)
        return mCurrentScreen->InComponentSelect();
    else
        return false;
}

UIPanel *UIManager::FocusPanel() {
    if (mCurrentScreen)
        return mCurrentScreen->FocusPanel();
    else
        return nullptr;
}

UIComponent *UIManager::FocusComponent() {
    UIPanel *focusPanel = FocusPanel();
    if (focusPanel)
        return focusPanel->FocusComponent();
    else
        return nullptr;
}

UIResource *UIManager::Resource(const UIComponent *comp) {
    return FindResource(comp->TypeDef());
}

void UIManager::InitResources(Symbol s) {
    DataArray *cfg = SystemConfig("objects", s);
    DataArray *typesArr = cfg->FindArray(types, true);
    if (typesArr) {
        for (int i = 1; i < typesArr->Size(); i++) {
            DataArray *curArr = typesArr->Array(i);
            DataArray *rsrcsArr = curArr->FindArray(resource_file, false);
            if (rsrcsArr && !FindResource(curArr)) {
                FilePath fp(FileGetPath(rsrcsArr->File(), 0), rsrcsArr->Str(1));
                mResources.push_back(new UIResource(fp));
            }
        }
    }
    std::sort(mResources.begin(), mResources.end(), UIResource::Compare());
}

UIResource *UIManager::FindResource(const DataArray *array) {
    if (!array) {
        return nullptr;
    }

    DataArray *fileArray = array->FindArray(resource_file, false);
    if (fileArray) {
        FilePath path(FileGetPath(fileArray->mFile.Str(), nullptr), fileArray->Str(1));

        std::pair<UIResource **, UIResource **> asdf = std::equal_range(
            mResources.begin(), mResources.end(), path.c_str(), UIResource::Compare()
        );

        if (asdf.first != asdf.second) {
            return *asdf.first;
        }
    }

    return nullptr;
}

DataNode UIManager::OnIsResource(DataArray *arr) {
    FilePath fp(FileRoot(), arr->Str(2));
    Symbol sym = arr->Sym(3);
    DataArray *cfg = SystemConfig(objects, sym, types);
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *curArr = cfg->Array(i);
        DataArray *rsrcArr = curArr->FindArray(resource_file, false);
        if (rsrcArr) {
            if (FilePath(FileGetPath(rsrcArr->File(), 0), rsrcArr->Str(1)) == fp) {
                return 1;
            }
        }
    }
    return 0;
}

void UIManager::UseJoypad(bool useJoypad, bool enableAutoRepeat) {
    if (useJoypad && !mJoyClient) {
        mJoyClient = new JoypadClient(this);
        mJoyClient->SetVirtualDpad(true);
        if (enableAutoRepeat) {
            mJoyClient->SetRepeatMask(0xf000);
        }
    } else if (!useJoypad) {
        if (mJoyClient) {
            RELEASE(mJoyClient);
        }
    }
}

namespace {
    JoypadAction NavButtonToNavAction(JoypadButton btn) {
        switch (btn) {
        case kPad_DLeft:
            return kAction_Left;
        case kPad_DRight:
            return kAction_Right;
        case kPad_DDown:
            return kAction_Down;
        case kPad_DUp:
            return kAction_Up;
        default:
            return kAction_None;
        }
    }
}

bool UIManager::OverloadHorizontalNav(JoypadAction act, JoypadButton btn, Symbol s) const {
    bool ret = false;
    if (mOverloadHorizontalNav) {
        bool b2 = true;
        if (act == NavButtonToNavAction(btn)) {
            bool b1 = false;
            if (s != none) {
                if (JoypadTypeHasLeftyFlip(s))
                    b1 = true;
            }
            if (!b1)
                b2 = false;
        }
        if (b2)
            ret = true;
    }
    return ret;
}

bool UIManager::RequireFixedText() const { return mRequireFixedText; }
void UIManager::SetRequireFixedText(bool req) { mRequireFixedText = req; }

UIScreen *UIManager::BottomScreen() {
    if (mPushedScreens.empty())
        return mCurrentScreen;
    else
        return mPushedScreens.front();
}

int UIManager::PushDepth() const { return mPushedScreens.size(); }

UIScreen *UIManager::ScreenAtDepth(int depth) {
    MILO_ASSERT(depth < mPushedScreens.size(), 0x478);
    return mPushedScreens[depth];
}

void UIManager::ToggleLoadTimes() {
    mOverlay->CurrentLine() = gNullStr;
    mOverlay->SetShowing(!mOverlay->Showing());
}

bool UIManager::BlockHandlerDuringTransition(Symbol s, DataArray *da) {
    if (s == KeyboardKeyMsg::Type())
        return true;
    else if (ButtonDownMsg::Type() != s) {
        if (ButtonUpMsg::Type() == s) {
            UIPanel *focus = FocusPanel();
            if (focus) {
                DataArray *arr;
                const DataNode *prop = focus->Property(allowed_transition_actions, false);
                if (prop)
                    arr = prop->Array();
                else
                    arr = nullptr;
                if (arr) {
                    for (int i = 0; i < arr->Size(); i++) {
                        if (arr->Int(i) == da->Int(4))
                            return false;
                    }
                }
            }
            return true;
        } else
            return false;
    }
}

void UIManager::EnableInputPerformanceMode(bool b) {
    if (mJoyClient)
        mJoyClient->SetFilterAllButStart(b);
}

void UIManager::PrintLoadedDirs(const char *cc) { DirLoader::PrintLoaded(cc); }

void UIManager::ShowNetError() {
    Message msg("show_net_error", ThePlatformMgr.GetNetErrorString(false));
    Handle(msg, true);
    ThePlatformMgr.ClearNetError();
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(UIManager)
    HANDLE_CONDITION(
        (InTransition() || InComponentSelect())
            && BlockHandlerDuringTransition(sym, _msg),
        0
    )
    HANDLE_MEMBER_PTR(mSink);
    HANDLE_ACTION(use_joypad, UseJoypad(_msg->Int(2), true))
    HANDLE_ACTION(set_virtual_dpad, mJoyClient->SetVirtualDpad(_msg->Int(2)))
    HANDLE_ACTION(push_screen, PushScreen(_msg->Obj<UIScreen>(2)))
    HANDLE_ACTION_IF_ELSE(
        pop_screen, _msg->Size() > 2, PopScreen(_msg->Obj<UIScreen>(2)), PopScreen(0)
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
    HANDLE_MEMBER_PTR(mAutomator)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(mCurrentScreen)
    HANDLE_CHECK(0x4FF)
END_HANDLERS
#pragma pop

DataNode UIManager::OnGotoScreen(const DataArray *arr) {
    Hmx::Object *obj = arr->GetObj(2);
    UIScreen *screen = dynamic_cast<UIScreen *>(obj);
    bool isscreen = false;
    if (screen || !obj)
        isscreen = true;
    if (!isscreen) {
        MILO_FAIL("%s is not a screen", obj->Name());
    }
    if (arr->Size() > 4) {
        GotoScreen(screen, arr->Int(3), arr->Int(4));
    } else if (arr->Size() > 3) {
        GotoScreen(screen, arr->Int(3), false);
    } else {
        GotoScreen(screen, false, false);
    }
    return 0;
}

DataNode UIManager::OnGoBackScreen(const DataArray *arr) {
    Hmx::Object *obj = arr->GetObj(2);
    UIScreen *screen = dynamic_cast<UIScreen *>(obj);
    bool isscreen = false;
    if (screen || !obj)
        isscreen = true;
    if (!isscreen) {
        MILO_FAIL("%s is not a screen", obj->Name());
    }
    GotoScreen(screen, false, true);
    return DataNode(kDataUnhandled, 0);
}

DataNode UIManager::ForeachScreen(const DataArray *arr) {
    DataNode *var = arr->Var(2);
    DataNode node(*var);
    std::vector<UIScreen *> screens(mPushedScreens);
    if (mCurrentScreen)
        screens.push_back(mCurrentScreen);
    for (std::vector<UIScreen *>::iterator it = screens.begin(); it != screens.end();
         ++it) {
        *var = *it;
        for (int i = 3; i < arr->Size(); i++) {
            arr->Command(i)->Execute();
        }
    }
    *var = node;
    return 0;
}