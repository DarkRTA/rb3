#pragma once
#include "obj/Msg.h"

class VoiceChatMgr : public MsgSource {
public:
    VoiceChatMgr();
};

DECLARE_MESSAGE(VoiceChatDisabledMsg, "voice_chat_disabled")
END_MESSAGE

extern VoiceChatMgr *TheVoiceChatMgr;