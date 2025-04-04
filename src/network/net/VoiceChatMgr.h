#pragma once
#include "Extensions/DemuxEventHandler.h"
#include "Extensions/SpeexCodec.h"
#include "game/BandUser.h"
#include "obj/Msg.h"
#include "os/User.h"

class VoiceChatMgr : public MsgSource {
public:
    VoiceChatMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~VoiceChatMgr();

    void ToggleMuteStatus(User *);
    bool IsMuted(User *) const;
    void Poll();
    void JoinVoiceChannel();
    void LeaveVoiceChannel();
    void SetMuteStatus(User *, bool);
    bool IsChatFriend(User *) const;
    void SetChatFriend(User *, bool);

    DataNode OnMsg(const RemoteUserLeftMsg &);

    Quazal::SpeexCodec *mCodec; // 0x1c
    Quazal::DemuxEventHandler *mReceiver; // 0x20
    int unk24;
    int unk28;
    bool unk2c;
    std::vector<User *> unk30; // 0x30
    std::vector<User *> unk38;
    bool unk40;
    bool unk41;
    bool unk42;
};

DECLARE_MESSAGE(VoiceChatDisabledMsg, "voice_chat_disabled")
END_MESSAGE

extern VoiceChatMgr *TheVoiceChatMgr;