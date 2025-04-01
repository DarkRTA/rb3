#pragma once
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
};

DECLARE_MESSAGE(VoiceChatDisabledMsg, "voice_chat_disabled")
END_MESSAGE

extern VoiceChatMgr *TheVoiceChatMgr;