#include "decomp.h"
#include "game/BandUser.h"
#include "meta_band/PassiveMessenger.h"
#include "game/BandUserMgr.h"
#include "game/GameMode.h"
#include "meta_band/BandUI.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/OvershellSlot.h"
#include "meta_band/SessionMgr.h"
#include "net/NetSession.h"
#include "net/VoiceChatMgr.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "utl/Locale.h"
#include "utl/Messages.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

PassiveMessenger *ThePassiveMessenger;

void PassiveMessageQueue::Poll() {
    if (mTimer.Running()) {
        if (mTimer.SplitMs() >= mMessageDuration) {
            mTimer.Stop();
            mCallback->Handle(hide_message_msg, true);
        }
    }
    if (mTimer.Running()) {
        if (mCallback->Handle(is_message_hiding_msg, true).Int() == 0) {
            if (!mQueue.empty()) {
                PassiveMessage *message = GetAndPreProcessFirstMessage();
                MILO_ASSERT(message, 0x33);
                HandlePassiveMessage(message);
                mQueue.pop_front();
                delete message;
                mTimer.Restart();
                mCallback->Handle(show_message_msg, true);
            } else {
                mCallback->Handle(clear_pics_msg, true);
            }
        }
    }
}

UNPOOL_DATA
void PassiveMessageQueue::HandlePassiveMessage(PassiveMessage *msg) {
    switch (msg->mType) {
    case 0:
        static Message setupTextMsg("setup_message_text", 0, 0);
        setupTextMsg[0] = DataNode(msg->mText, kDataArray);
        setupTextMsg[1] = msg->unk4c;
        mCallback->Handle(setupTextMsg, true);
        break;
    case 1:
        static Message setupIconMsg("setup_message_icon", 0, 0);
        setupIconMsg[0] = DataNode(msg->mText, kDataArray);
        setupIconMsg[1] = msg->unk24.c_str();
        mCallback->Handle(setupIconMsg, true);
        break;
    case 3:
        static Message setupCareerGoalMsg(
            "setup_message_careergoal", 0, 0, 0, 0, 0, 0, 0, 0, 0
        );
        setupCareerGoalMsg[0] = DataNode(msg->mText, kDataArray);
        setupCareerGoalMsg[1] = msg->unk20;
        setupCareerGoalMsg[2] = msg->unk14;
        setupCareerGoalMsg[3] = msg->unk18;
        setupCareerGoalMsg[4] = msg->unk1c;
        setupCareerGoalMsg[5] = msg->unk24.c_str();
        setupCareerGoalMsg[6] = msg->unk30.c_str();
        setupCareerGoalMsg[7] = msg->unk3c.c_str();
        setupCareerGoalMsg[8] = msg->unk48;
        mCallback->Handle(setupCareerGoalMsg, true);
        break;
    case 2:
        static Message setupCareerStepMsg("setup_message_careerstep", 0, 0, 0, 0, 0);
        setupCareerStepMsg[0] = DataNode(msg->mText, kDataArray);
        setupCareerStepMsg[1] = msg->unk14;
        setupCareerStepMsg[2] = msg->unk18;
        setupCareerStepMsg[3] = msg->unk1c;
        setupCareerStepMsg[4] = msg->unk24.c_str();
        mCallback->Handle(setupCareerStepMsg, true);
        break;
    case 4:
        static Message setupCareerMultiGoalMsg(
            "setup_message_careermulti", 0, 0, 0, 0, 0, 0, 0, 0
        );
        setupCareerMultiGoalMsg[0] = DataNode(msg->mText, kDataArray);
        setupCareerMultiGoalMsg[1] = msg->unk20;
        setupCareerMultiGoalMsg[2] = msg->unk14;
        setupCareerMultiGoalMsg[3] = msg->unk18;
        setupCareerMultiGoalMsg[4] = msg->unk1c;
        setupCareerMultiGoalMsg[5] = msg->unk30.c_str();
        setupCareerMultiGoalMsg[6] = msg->unk3c.c_str();
        setupCareerMultiGoalMsg[7] = msg->unk48;
        mCallback->Handle(setupCareerMultiGoalMsg, true);
        break;
    default:
        MILO_ASSERT(false, 0x94);
        break;
    }
}
END_UNPOOL_DATA

PassiveMessage *PassiveMessageQueue::GetAndPreProcessFirstMessage() {}

void PassiveMessageQueue::MakeIntoCoalescedGoalMessage(PassiveMessage *msg, int i2) {
    msg->mText->Node(0) = passive_message_earned_accomplishments;
    msg->mText->Node(1) = i2;
    msg->unk24 = gNullStr;
    msg->mType = (PassiveMessageType)4;
}

bool PassiveMessageQueue::RemoveLowerPriorityMessage(PassiveMessage *msg) {
    Symbol symChannel = msg->mChannel;
    MILO_ASSERT(symChannel != gNullStr, 0x104);
    int i5 = msg->unk10;
    FOREACH (it, mQueue) {
        PassiveMessage *queueMessage = *it;
        MILO_ASSERT(queueMessage, 0x10D);
        if (queueMessage->mChannel == symChannel) {
            if (i5 >= queueMessage->unk10)
                return false;
            else {
                PassiveMessage *pMessage = *it;
                MILO_ASSERT(pMessage, 0x11C);
                delete pMessage;
                mQueue.erase(it);
                break;
            }
        }
    }
    return true;
}

void PassiveMessageQueue::AddMessage(PassiveMessage *msg) {
    Symbol symChannel = msg->mChannel;
    if (symChannel == gNullStr || RemoveLowerPriorityMessage(msg)) {
        mQueue.push_back(msg);
    }
}

void PassiveMessageQueue::SetMessageDuration(float f1) { mMessageDuration = f1; }

namespace {
    PassiveMessagesPanel *GetPMPanel() {
        return ObjectDir::Main()->Find<PassiveMessagesPanel>(
            "passive_messages_panel", false
        );
    }
}

PassiveMessenger::PassiveMessenger() : unk1c(0) {
    MILO_ASSERT(!ThePassiveMessenger, 0x159);
    ThePassiveMessenger = this;
    SetName("passive_messenger", ObjectDir::Main());
    TheVoiceChatMgr->AddSink(this, VoiceChatDisabledMsg::Type());
    ThePlatformMgr.AddSink(this, InviteSentMsg::Type());
    TheSessionMgr->AddSink(this, RemoteUserLeftMsg::Type());
    ThePlatformMgr.AddSink(this, InviteReceivedMsg::Type());
    TheSessionMgr->AddSink(this, SessionDisconnectedMsg::Type());
}

PassiveMessenger::~PassiveMessenger() {
    MILO_ASSERT(ThePassiveMessenger, 0x169);
    ThePassiveMessenger = nullptr;
    ThePlatformMgr.RemoveSink(this, InviteSentMsg::Type());
    TheVoiceChatMgr->RemoveSink(this);
    TheSessionMgr->RemoveSink(this, RemoteUserLeftMsg::Type());
    ThePlatformMgr.RemoveSink(this, InviteReceivedMsg::Type());
}

void PassiveMessenger::Poll() {
    if (mTimer.Running()) {
        if (mTimer.SplitMs() >= 6000.0f) {
            mTimer.Stop();
        }
    }
}

void PassiveMessenger::TriggerMessage(
    DataArray *a,
    PassiveMessageType t,
    LocalBandUser *u,
    bool b4,
    Symbol s,
    int i6,
    int i7,
    int i8,
    int i9,
    int i10,
    const char *c1,
    const char *c2,
    const char *c3,
    int i14
) {
    if (u) {
        OvershellSlot *slot = TheBandUI.GetOvershell()->GetSlot(u);
        if (slot) {
            if (!TheGameMode->InMode("trainer")) {
                int i4 = -1;
                if (i10 != 0)
                    i4 = i8 + i10;
                slot->GetMessageQueue()->AddMessage(
                    new PassiveMessage(a, t, s, i6, i8, i9, i4, i7, c1, c2, c3, i14, b4)
                );
                return;
            }
        }
    }
    PassiveMessagesPanel *pmPanel = GetPMPanel();
    if (pmPanel) {
        int i4 = -1;
        if (i10 != 0)
            i4 = i8 + i10;
        pmPanel->GetMessageQueue()->AddMessage(
            new PassiveMessage(a, t, s, i6, i8, i9, i4, i7, c1, c2, c3, i14, b4)
        );
    }
}

void PassiveMessenger::TriggerSkipSongMsg() {
    if (!mTimer.Running()) {
        TriggerMessage(
            DataArrayPtr(passive_message_preload_failed),
            (PassiveMessageType)0,
            nullptr,
            false,
            gNullStr
        );
        mTimer.Restart();
    }
}

void PassiveMessenger::TriggerInviteFailedMsg() {
    TriggerMessage(
        DataArrayPtr(passive_message_invite_failed),
        (PassiveMessageType)0,
        nullptr,
        false,
        gNullStr
    );
}

DataNode PassiveMessenger::OnMsg(const RemoteUserLeftMsg &msg) {
    TriggerRemoteUserLeftMsg(msg.GetUser()->UserName());
    return 1;
}

void PassiveMessenger::TriggerRemoteUserLeftMsg(const char *cc) {
    DataArrayPtr ptr(passive_message_remote_user_left, cc);
    if (TheBandUI.GetOvershell()->InSong()) {
        TriggerMessage(ptr, (PassiveMessageType)0, nullptr, false, gNullStr);
    } else {
        LocalBandUser *host = TheSessionMgr->GetLocalHost();
        if (!host) {
            BandUser *leader = TheSessionMgr->GetLeaderUser();
            if (leader && leader->IsLocal()) {
                host = leader->GetLocalBandUser();
            }
        }
        if (host) {
            TriggerMessage(ptr, (PassiveMessageType)0, host, false, gNullStr);
        }
    }
}

void PassiveMessenger::TriggerEarnedAccomplishmentMsg(
    LocalBandUser *u,
    Symbol s1,
    Symbol s2,
    int i4,
    int i5,
    int i6,
    int i7,
    int i8,
    const char *c1,
    const char *c2,
    const char *c3,
    int i12
) {
    DataArrayPtr ptr(passive_message_earned_accomplishment, Localize(s1, nullptr));
    TriggerMessage(
        ptr, (PassiveMessageType)3, u, false, s2, i4, i5, i6, i7, i8, c1, c2, c3, i12
    );
}

void PassiveMessenger::TriggerEarnedCampaignLevelMsg(LocalBandUser *u, Symbol s) {
    DataArrayPtr ptr(passive_message_earned_campaign_level, Localize(s, nullptr));
    TriggerMessage(ptr, (PassiveMessageType)0, u, true, gNullStr);
}

void PassiveMessenger::TriggerCompletedAccomplishmentCategoryMsg(
    LocalBandUser *u, Symbol s
) {
    DataArrayPtr ptr(
        passive_message_completed_accomplishment_category, Localize(s, nullptr)
    );
    TriggerMessage(ptr, (PassiveMessageType)0, u, false, gNullStr);
}

void PassiveMessenger::TriggerCompletedAccomplishmentGroupMsg(LocalBandUser *u, Symbol s) {
    DataArrayPtr ptr(passive_message_completed_accomplishment_group, Localize(s, nullptr));
    TriggerMessage(ptr, (PassiveMessageType)0, u, false, gNullStr);
}

void PassiveMessenger::TriggerVoiceChatDisabledMsg() {
    DataArrayPtr ptr(voice_chat_disabled);
    TriggerMessage(ptr, (PassiveMessageType)0, nullptr, false, gNullStr);
}

void PassiveMessenger::TriggerSetlistSongsRemovedMsg(int i1) {
    if (i1 == 1) {
        DataArrayPtr ptr(setlist_song_removed);
        TriggerMessage(ptr, (PassiveMessageType)0, nullptr, false, gNullStr);
    } else {
        DataArrayPtr ptr(setlist_songs_removed, i1);
        TriggerMessage(ptr, (PassiveMessageType)0, nullptr, false, gNullStr);
    }
}

DataNode PassiveMessenger::OnMsg(const VoiceChatDisabledMsg &) {
    if (!unk1c) {
        unk1c = true;
        TriggerVoiceChatDisabledMsg();
    }
    return 0;
}

DataNode PassiveMessenger::OnMsg(const SessionDisconnectedMsg &) {
    unk1c = false;
    return 0;
}

DataNode PassiveMessenger::OnMsg(const InviteSentMsg &msg) {
    if (msg->Int(2)) {
        DataArrayPtr ptr(passive_message_invite_sent_success);
        TriggerMessage(ptr, (PassiveMessageType)0, nullptr, false, gNullStr);
    } else {
        DataArrayPtr ptr(passive_message_invite_sent_fail);
        TriggerMessage(ptr, (PassiveMessageType)0, nullptr, false, gNullStr);
    }
    return 1;
}

bool PassiveMessenger::HasMessages() const {
    OvershellPanel *overshellPanel = TheBandUI.GetOvershell();
    MILO_ASSERT(overshellPanel, 0x28A);
    std::vector<LocalBandUser *> users;
    TheBandUserMgr->GetLocalParticipants(users);
    FOREACH (it, users) {
        LocalBandUser *localUser = *it;
        MILO_ASSERT(localUser, 0x293);
        OvershellSlot *slot = overshellPanel->GetSlot(localUser);
        if (slot) {
            PassiveMessageQueue *pQueue = slot->GetMessageQueue();
            MILO_ASSERT(pQueue, 0x299);
            if (pQueue->mQueue.size() > 0)
                return true;
            if (pQueue->mTimer.Running())
                return true;
        }
    }
    return false;
}

DataNode PassiveMessenger::OnMsg(const InviteReceivedMsg &) {
    TriggerMessage(
        DataArrayPtr(wii_friends_invite_received),
        (PassiveMessageType)0,
        nullptr,
        false,
        gNullStr
    );
    return 1;
}

BEGIN_HANDLERS(PassiveMessenger)
    HANDLE_ACTION(
        trigger_message,
        TriggerMessage(
            _msg->Array(2),
            (PassiveMessageType)0,
            _msg->Obj<LocalBandUser>(3),
            false,
            gNullStr
        )
    )
    HANDLE_ACTION(trigger_skip_song_msg, TriggerSkipSongMsg())
    HANDLE_EXPR(has_messages, HasMessages())
    HANDLE_MESSAGE(VoiceChatDisabledMsg)
    HANDLE_MESSAGE(InviteSentMsg)
    HANDLE_MESSAGE(RemoteUserLeftMsg)
    HANDLE_MESSAGE(SessionDisconnectedMsg)
    HANDLE_MESSAGE(InviteReceivedMsg)
    HANDLE_CHECK(0x2CB)
END_HANDLERS