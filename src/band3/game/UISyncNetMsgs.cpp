#include "game/UISyncNetMsgs.h"
#include "decomp.h"
#include "meta_band/NetSync.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/UserMgr.h"
#include "ui/PanelDir.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "ui/UISlider.h"

ComponentFocusNetMsg::ComponentFocusNetMsg(User *user, UIComponent *c) {
    MILO_ASSERT(user, 0x1B);
    MILO_ASSERT(c, 0x1C);
    mUserGuid = user->GetUserGuid();
    mComponentName = c->Name();
}

void ComponentFocusNetMsg::Save(BinStream &bs) const {
    bs << mUserGuid;
    bs << mComponentName;
}

void ComponentFocusNetMsg::Load(BinStream &bs) {
    bs >> mUserGuid;
    bs >> mComponentName;
}

void ComponentFocusNetMsg::Dispatch() {
    if (TheNetSync->IsEnabled()) {
        UIScreen *screen = TheUI.CurrentScreen();
        if (screen) {
            UIPanel *panel = screen->FocusPanel();
            if (panel) {
                UIComponent *c =
                    panel->DataDir()->Find<UIComponent>(mComponentName.c_str(), false);
                if (c)
                    panel->SetFocusComponent(c);
            }
        }
    }
}

ComponentSelectNetMsg::ComponentSelectNetMsg(User *user, UIComponent *c, bool b) {
    MILO_ASSERT(user, 0x45);
    MILO_ASSERT(c, 0x46);
    mUserGuid = user->GetUserGuid();
    mComponentName = c->Name();
    mShowSelect = b;
}

void ComponentSelectNetMsg::Save(BinStream &bs) const {
    bs << mUserGuid;
    bs << mComponentName;
    bs << mShowSelect;
}

void ComponentSelectNetMsg::Load(BinStream &bs) {
    bs >> mUserGuid;
    bs >> mComponentName;
    bs >> mShowSelect;
}

void ComponentSelectNetMsg::Dispatch() {
    if (TheNetSync->IsEnabled()) {
        static NetComponentSelectMsg msg(nullptr, "");
        User *user = TheUserMgr->GetUser(mUserGuid, true);
        MILO_ASSERT(user, 0x61);
        msg[0] = user;
        msg[1] = mComponentName;
        DataNode handled = TheUI.Handle(msg, false);
        if (mShowSelect && handled == DataNode(kDataUnhandled, 0)) {
            UIScreen *screen = TheUI.CurrentScreen();
            if (screen) {
                PanelDir *dir = screen->FocusPanel()->LoadedDir();
                if (dir) {
                    UIComponent *c = dir->FindComponent(mComponentName.c_str());
                    if (c)
                        c->MockSelect();
                }
            }
        }
    }
}

ComponentScrollNetMsg::ComponentScrollNetMsg(User *user, UIComponent *c) {
    mUserGuid = user->GetUserGuid();
    MILO_ASSERT(c, 0x7E);
    mComponentName = c->Name();
    UIList *list = dynamic_cast<UIList *>(c);
    if (list) {
        mPosition = list->Selected();
        mFirstShowing = list->FirstShowing();
    } else {
        UISlider *slider = dynamic_cast<UISlider *>(c);
        mPosition = slider->Current();
        mFirstShowing = -1;
    }
}

void ComponentScrollNetMsg::Save(BinStream &bs) const {
    bs << mUserGuid;
    bs << mComponentName;
    bs << mPosition;
    bs << mFirstShowing;
}

void ComponentScrollNetMsg::Load(BinStream &bs) {
    bs >> mUserGuid;
    bs >> mComponentName;
    bs >> mPosition;
    bs >> mFirstShowing;
}

#pragma push
#pragma pool_data off
void ComponentScrollNetMsg::Dispatch() {
    static NetComponentScrollMsg scrollMsg(nullptr, "", -1, -1);
    User *user = TheUserMgr->GetUser(mUserGuid, true);
    scrollMsg[0] = user;
    scrollMsg[1] = mComponentName;
    scrollMsg[2] = mPosition;
    scrollMsg[3] = mFirstShowing;
    DataNode handleScrollMsg = TheUI.Handle(scrollMsg, false);
    if (handleScrollMsg == DataNode(kDataUnhandled, 0)) {
        UIScreen *screen = TheUI.CurrentScreen();
        if (screen) {
            UIPanel *panel = screen->FocusPanel();
            if (panel) {
                PanelDir *dir = screen->FocusPanel()->LoadedDir();
                if (dir) {
                    UIComponent *c = dir->FindComponent(mComponentName.c_str());
                    if (c) {
                        UIList *list = dynamic_cast<UIList *>(c);
                        if (list) {
                            list->SetSelected(mPosition, mFirstShowing);
                        } else {
                            UISlider *slider = dynamic_cast<UISlider *>(c);
                            slider->SetCurrent(mPosition);
                        }
                    }
                }
            }
        }
    }

    static NetComponentPostScrollMsg postScrollMsg(nullptr, "", -1, -1);
    User *user2 = TheUserMgr->GetUser(mUserGuid, true);
    postScrollMsg[0] = user2;
    postScrollMsg[1] = mComponentName;
    postScrollMsg[2] = mPosition;
    postScrollMsg[3] = mFirstShowing;
    TheUI.Handle(postScrollMsg, false);
}
#pragma pop

DECOMP_FORCEFUNC(UISyncNetMsgs, ComponentScrollNetMsg, Name())
DECOMP_FORCEFUNC(UISyncNetMsgs, ComponentScrollNetMsg, ByteCode())
DECOMP_FORCEFUNC(UISyncNetMsgs, ComponentSelectNetMsg, Name())
DECOMP_FORCEFUNC(UISyncNetMsgs, ComponentSelectNetMsg, ByteCode())
DECOMP_FORCEFUNC(UISyncNetMsgs, ComponentFocusNetMsg, Name())
DECOMP_FORCEFUNC(UISyncNetMsgs, ComponentFocusNetMsg, ByteCode())
DECOMP_FORCEDTOR(UISyncNetMsgs, ComponentFocusNetMsg)
DECOMP_FORCEDTOR(UISyncNetMsgs, ComponentScrollNetMsg)
DECOMP_FORCEDTOR(UISyncNetMsgs, ComponentSelectNetMsg)