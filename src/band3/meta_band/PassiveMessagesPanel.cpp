#include "meta_band/PassiveMessage.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "rndobj/Anim.h"
#include "rndobj/Rnd.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

PassiveMessagesPanel::PassiveMessagesPanel() : mShowMessages(0) {
    mMessenger = new PassiveMessenger();
    mMessageQueue = new PassiveMessageQueue(this);
}

PassiveMessagesPanel::~PassiveMessagesPanel() { delete mMessenger; }

void PassiveMessagesPanel::SetTypeDef(DataArray *a) {
    if (TypeDef() != a) {
        UIPanel::SetTypeDef(a);
        mMessageQueue->SetMessageDuration(a->FindFloat(msg_duration));
    }
}

void PassiveMessagesPanel::Poll() {
    if (TheRnd->ProcCmds() & 2) {
        mMessageQueue->Poll();
        mMessenger->Poll();
        UIPanel::Poll();
    }
}

void PassiveMessagesPanel::QueueMessage(
    DataArray *a, PassiveMessageType t, Symbol s, int i
) {
    mMessageQueue->AddMessage(
        new PassiveMessage(a, t, s, i, 0, 0, 0, -1, gNullStr, gNullStr, gNullStr, 0, 0)
    );
}

DataNode PassiveMessagesPanel::OnQueueMessage(DataArray *a) {
    if (a->Type(2) == kDataArray) {
        QueueMessage(a->Array(2), (PassiveMessageType)0, gNullStr, -1);
    } else {
        DataArrayPtr ptr(a->Sym(2));
        QueueMessage(ptr, (PassiveMessageType)0, gNullStr, -1);
    }
    return 1;
}

void PassiveMessagesPanel::PostSetup() {
    static RndAnimatable *anim = DataDir()->Find<RndAnimatable>("message_pos.tnm", false);
    if (anim) {
        bool b1 = false;
        UIScreen *screen = TheUI.CurrentScreen();
        if (screen) {
            FOREACH (it, screen->GetPanelRefs()) {
                if (game == it->mPanel->Name()) {
                    b1 = true;
                    break;
                }
            }
        }
        if (b1) {
            if (TheRnd->GetAspect() == Rnd::kRegular) {
                anim->SetFrame(2, 1);
            } else {
                anim->SetFrame(1, 1);
            }
        } else {
            anim->SetFrame(0, 1);
        }
    }
}

void PassiveMessagesPanel::SetShowMessages(bool show) { mShowMessages = show; }

BEGIN_HANDLERS(PassiveMessagesPanel)
    HANDLE(queue_message, OnQueueMessage)
    HANDLE_ACTION(set_show_messages, SetShowMessages(_msg->Int(2)))
    HANDLE_EXPR(is_message_hiding, Exiting())
    HANDLE_ACTION(post_setup, PostSetup())
    HANDLE_ACTION(show_message, Enter())
    HANDLE_ACTION(hide_message, Exit())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_MEMBER_PTR(mMessenger)
    HANDLE_CHECK(0x9A)
END_HANDLERS