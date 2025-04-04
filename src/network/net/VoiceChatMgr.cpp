#include "network/net/VoiceChatMgr.h"
#include "Extensions/CodecManager.h"
#include "Extensions/DemuxEventHandler.h"
#include "Extensions/SpeexCodec.h"
#include "ObjDup/Session.h"
#include "net/NetSession.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"

VoiceChatMgr *TheVoiceChatMgr;

namespace {
    class VoiceReceiver : public Quazal::DemuxEventHandler {
    public:
        VoiceReceiver() {}
        virtual ~VoiceReceiver() {}
        virtual bool StreamOpened(unsigned char c, Quazal::DOHandle h) {
            return Quazal::DemuxEventHandler::StreamOpened(c, h);
        }
        virtual bool StreamPacketReceived(
            unsigned char uc, Quazal::DOHandle h, unsigned char *ucp, unsigned int ui
        ) {
            return Quazal::DemuxEventHandler::StreamPacketReceived(uc, h, ucp, ui);
        }
        virtual bool StreamClosed(unsigned char c, Quazal::DOHandle h) {
            return Quazal::DemuxEventHandler::StreamClosed(c, h);
        }
    };

    void CreateVoiceChannel() {
        char *channel;
        MILO_ASSERT(channel != NULL, 0x0);
    }
}

VoiceChatMgr::VoiceChatMgr()
    : mCodec(new Quazal::SpeexCodec(0x50)), mReceiver(new VoiceReceiver()), unk24(0),
      unk28(0), unk2c(0), unk40(1), unk41(0), unk42(0) {
    MILO_ASSERT(!TheVoiceChatMgr, 0x75);
    TheVoiceChatMgr = this;
    Quazal::CodecManager::s_oInstance.RegisterCodec(0, mCodec);
    Quazal::Session::RegisterWellKnownDOsFactory(CreateVoiceChannel);
    MILO_ASSERT(TheNetSession, 0x7B);
    TheNetSession->AddSink(this, "remote_player_left");
}

VoiceChatMgr::~VoiceChatMgr() {
    TheNetSession->RemoveSink(this, "remote_player_left");
    delete mReceiver;
    // delete unk24;
    delete mCodec;
}

void VoiceChatMgr::JoinVoiceChannel() {}
void VoiceChatMgr::Poll() {}
void VoiceChatMgr::LeaveVoiceChannel() {}

void VoiceChatMgr::SetMuteStatus(User *user, bool mute) {
    std::vector<User *>::iterator it = std::find(unk30.begin(), unk30.end(), user);
    if (mute && it == unk30.end()) {
        unk30.push_back(user);
    }
    if (!mute && it != unk30.end()) {
        unk30.erase(it);
    }
}

void VoiceChatMgr::ToggleMuteStatus(User *user) {
    std::vector<User *>::iterator it = std::find(unk30.begin(), unk30.end(), user);
    if (it == unk30.end()) {
        unk30.push_back(user);
    } else {
        unk30.erase(it);
    }
}

bool VoiceChatMgr::IsChatFriend(User *user) const {
    if (ThePlatformMgr.unkce5a)
        return true;
    return std::find(unk38.begin(), unk38.end(), user) != unk38.end();
}

void VoiceChatMgr::SetChatFriend(User *user, bool isFriend) {
    std::vector<User *>::iterator it = std::find(unk38.begin(), unk38.end(), user);
    if (isFriend && it == unk38.end()) {
        unk38.push_back(user);
    }
    if (!isFriend && it != unk38.end()) {
        unk38.erase(it);
    }
}

bool VoiceChatMgr::IsMuted(User *user) const {
    if (unk41)
        return true;
    if (!IsChatFriend(user))
        return true;
    return std::find(unk30.begin(), unk30.end(), user) != unk30.end();
}

DataNode VoiceChatMgr::OnMsg(const RemoteUserLeftMsg &msg) {
    User *user = msg.GetUser();
    SetMuteStatus(user, false);
    SetChatFriend(user, false);
    return 1;
}

BEGIN_HANDLERS(VoiceChatMgr)
    HANDLE_MESSAGE(RemoteUserLeftMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x182)
END_HANDLERS