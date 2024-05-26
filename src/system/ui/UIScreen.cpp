#include "ui/UIScreen.h"

#include "os/Debug.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

typedef std::vector<PanelRef>::iterator iterator;
typedef std::vector<PanelRef>::const_iterator const_iterator;
typedef std::vector<PanelRef>::reverse_iterator reverse_iterator;
typedef std::vector<PanelRef>::const_reverse_iterator const_reverse_iterator;

UIScreen *UIScreen::sUnloadingScreen;
int UIScreen::sMaxScreenId;

UIScreen::UIScreen()
    : mFocusPanel(NULL), mBack(NULL), mClearVram(false), mShowing(true),
      mScreenId(sMaxScreenId++) {
    MILO_ASSERT(sMaxScreenId < 0x8000, 0x1C);
}

void UIScreen::SetTypeDef(DataArray* data) {
    if (TypeDef() == data) {
        return;
    }

    Hmx::Object::SetTypeDef(data);
    mFocusPanel = NULL;
    mPanelList.clear();

    DataArray* panelsArr = data->FindArray(panels, false);
    if (panelsArr != NULL) {
        for (int i = 1; i < panelsArr->Size(); i++) {
            PanelRef pr;
            pr.mActive = true;
            pr.mAlwaysLoad = true;

            if (panelsArr->Node(i).Type() == kDataArray) {
                DataArray* panelArray = panelsArr->Array(i);
                pr.mPanel = panelArray->Obj<class UIPanel>(0);
                MILO_ASSERT(pr.mPanel, 0x3E);
                panelArray->FindData(active, pr.mActive, false);
                panelArray->FindData(always_load, pr.mAlwaysLoad, false);
            } else {
                pr.mPanel = panelsArr->Obj<class UIPanel>(i);
                MILO_ASSERT(pr.mPanel, 0x45);
            }

            mPanelList.push_back(pr);
        }
    }

    DataArray* focusArr = data->FindArray(focus, false);
    if (focusArr != NULL) {
        SetFocusPanel(focusArr->Obj<class UIPanel>(1));
    }

    if (mFocusPanel == NULL && !mPanelList.empty()) {
        SetFocusPanel(mPanelList[0].mPanel);
    }

    mBack = data->FindArray("back", false);
    mClearVram = false;
    data->FindData(clear_vram, mClearVram, false);
}

BEGIN_HANDLERS(UIScreen)
    HANDLE_EXPR(focus_panel, mFocusPanel)
    HANDLE_ACTION(set_focus_panel, SetFocusPanel(_msg->Obj<class UIPanel>(2)))
    HANDLE_ACTION(print, Print(TheDebug))
    HANDLE_ACTION(reenter_screen, ReenterScreen())
    HANDLE_ACTION(set_panel_active, SetPanelActive(_msg->Obj<class UIPanel>(2), _msg->Int(3)))
    HANDLE_ACTION(set_showing, SetShowing(_msg->Int(2)))
    HANDLE_EXPR(has_panel, HasPanel(_msg->Obj<class UIPanel>(2)))
    HANDLE_EXPR(add_panel, AddPanel(_msg->Obj<class UIPanel>(2), _msg->Int(3)))
    HANDLE_ACTION(foreach_panel, ForeachPanel(_msg))
    HANDLE_EXPR(exiting, Exiting())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(mFocusPanel)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_CHECK(0x75)
END_HANDLERS

bool UIScreen::Entering() const {
    for (const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->Entering()) {
            return true;
        }
    }

    if (sUnloadingScreen != NULL && sUnloadingScreen->Unloading()) {
        return true;
    }

    sUnloadingScreen = NULL;
    return false;
}

bool UIScreen::Exiting() const {
    for (const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->Exiting()) {
            return true;
        }
    }

    return false;
}

bool UIScreen::Unloading() const {
    for (const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->mLoaded && it->mPanel->Unloading()) {
            return true;
        }
    }

    return false;
}

void UIScreen::Poll() {
    HandleType(poll_msg);

    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && !it->mPanel->mPaused) {
            it->mPanel->Poll();
        }
    }
}

#pragma push
#pragma pool_data off
// Likely weak based on how bss gets used
void UIScreen::Enter(UIScreen* from) {
    if (from != NULL) {
        sUnloadingScreen = from;
        from->UnloadPanels();
    }

    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->mState == UIPanel::kDown) {
            it->mPanel->Enter();
        }
    }

    static Message msg("enter", 0);
    msg.mData->Node(2) = from;
    HandleType(msg);
    Poll();
}
#pragma pop

void UIScreen::Draw() {
    if (!mShowing) {
        return;
    }

    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->mShowing) {
            it->mPanel->Draw();
        }
    }
}

void UIScreen::SetFocusPanel(class UIPanel* panel) {
    if (panel == mFocusPanel) {
        return;
    }

    if (mFocusPanel != NULL) mFocusPanel->FocusIn();
    mFocusPanel = panel;
    if (mFocusPanel != NULL) mFocusPanel->FocusOut();
}

bool UIScreen::InComponentSelect() const {
    UIComponent* component = TheUI->FocusComponent();
    if (component != NULL) {
        return component->mState == UIComponent::kSelecting;
    }

    return false;
}

bool UIScreen::SharesPanels(UIScreen* screen) {
    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (screen->HasPanel(it->mPanel)) {
            return true;
        }
    }

    return false;
}

bool UIScreen::HasPanel(class UIPanel* panel) {
    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->mPanel == panel && it->mActive) {
            return true;
        }
    }

    return false;
}

bool UIScreen::AddPanel(class UIPanel* panel, bool alwaysLoad) {
    if (HasPanel(panel)) {
        return false;
    }

    PanelRef ref;
    ref.mActive = true;
    ref.mAlwaysLoad = alwaysLoad;
    ref.mLoaded = panel->IsLoaded();
    ref.mPanel = panel;

    mPanelList.push_back(ref);
    return true;
}

void UIScreen::Exit(UIScreen* to) {
    static Message msg("exit", 0);
    msg.mData->Node(2) = to;
    HandleType(msg);

    if (to != NULL) {
        to->LoadPanels();
    }

    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (!it->mLoaded) {
            continue;
        }

        if ((it->mPanel->mForceExit || to == NULL || !to->HasPanel(it->mPanel))
            && it->mPanel->mState == UIPanel::kUp) {
            it->mPanel->Exit();
        }
    }
}

void UIScreen::ReenterScreen() {
    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active()) {
            it->mPanel->Exit();
        }
    }

    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active()) {
            it->mPanel->Enter();
        }
    }
}

void UIScreen::SetPanelActive(class UIPanel* panel, bool active) {
    bool found = false;
    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->mPanel == panel) {
            it->mActive = active;
            found = true;
        }
    }

    if (!found) {
        MILO_WARN("UIScreen::SetPanelActive: not found\nscreen %s\npanel %s\n", PathName(this), PathName(panel));
    }
}

void UIScreen::SetShowing(bool show) {
    mShowing = show;
}

void UIScreen::LoadPanels() {
    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->mAlwaysLoad || it->mPanel->mLoadRefs != 0) {
            it->mPanel->CheckLoad();
            it->mLoaded = true;
        } else {
            it->mLoaded = false;
        }
    }

    HandleType(load_panels_msg);
}

void UIScreen::UnloadPanels() {
    for (reverse_iterator it = mPanelList.rbegin(); it != mPanelList.rend(); it++) {
        if (it->mLoaded) {
            it->mPanel->CheckUnload();
        }
    }
}

bool UIScreen::CheckIsLoaded() {
    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && !it->mPanel->CheckIsLoaded()) {
            return false;
        }
    }

    return true;
}

bool UIScreen::IsLoaded() const {
    for (const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->mState == UIPanel::kUnloaded) {
            return false;
        }
    }

    // please don't tell me const_cast is what they did lol
    DataNode result = const_cast<UIScreen*>(this)->HandleType(is_loaded_msg);
    if (result.Type() != kDataUnhandled) {
        return result.Int(NULL);
    }

    return true;
}

bool UIScreen::AllPanelsDown() {
    for (const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->mState != UIPanel::kDown) {
            return false;
        }
    }

    return true;
}

void UIScreen::Print(TextStream& s) {
    s << "{UIScreen " << Name() << "\n";

    if (mPanelList.size() != 0) {
        s << "   Panels:\n";
        for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
            s << "      " << it->mPanel->Name() << " ";
            if (!it->mActive) {
                s << "(active " << it->mActive << ") ";
            }
            if (!it->mAlwaysLoad) {
                s << "(always_load " << it->mAlwaysLoad << ") ";
            }

            const DataArray* typeDef = it->mPanel->TypeDef();
            if (typeDef != NULL) {
                DataArray* fileArray = typeDef->FindArray(file, false);
                if (fileArray != NULL) {
                    DataNode type = fileArray->Node(1);
                    if (type.Type() == kDataString || type.Type() == kDataSymbol) {
                        s << "(" << type.LiteralStr(NULL) << ") ";
                    } else {
                        s << "(dynamic) ";
                    }
                }
            } else {
                s << " ";
            }

            if (it->mPanel == mFocusPanel) {
                s << "(focus)";
            }

            s << "\n";
        }
    }

    s << "}\n";
}

DataNode UIScreen::OnMsg(const ButtonDownMsg& msg) {
    if (mBack != NULL && msg.GetAction() == kAction_Cancel) {
        DataNode n = mBack->Evaluate(1);
        if (n.Type() != kDataUnhandled) {
            Message m(go_back_screen, n.Str(NULL), msg.GetUser());
            TheUI->Handle(m, true);
        }
    }

    return DataNode(kDataUnhandled, 0);
}

DataNode UIScreen::ForeachPanel(const DataArray* da) {
    // {$screen foreach_panel $panel ...}

    DataNode* var = da->Var(2);
    DataNode tmp = *var;

    for (iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (!it->mActive) {
            continue;
        }

        *var = it->mPanel;
        for (int i = 3; i < da->Size(); i++) {
            da->Command(i)->Execute();
        }
    }

    *var = tmp;
    return 0;
}

// void UIScreen::SetType(Symbol) {}
// void UIScreen::ClassName() const {}
