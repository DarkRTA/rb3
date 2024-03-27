#include "ui/UIScreen.h"

#include "os/Debug.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

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
    for (std::vector<PanelRef>::const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
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
    for (std::vector<PanelRef>::const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && it->mPanel->Exiting()) {
            return true;
        }
    }

    return false;
}

bool UIScreen::Unloading() const {
    for (std::vector<PanelRef>::const_iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->mLoaded && it->mPanel->Unloading()) {
            return true;
        }
    }

    return false;
}

void UIScreen::Poll() {
    HandleType(poll_msg);

    for (std::vector<PanelRef>::iterator it = mPanelList.begin(); it != mPanelList.end(); it++) {
        if (it->Active() && !it->mPanel->mPaused) {
            it->mPanel->Poll();
        }
    }
}
