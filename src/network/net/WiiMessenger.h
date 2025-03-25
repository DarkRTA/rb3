#pragma once
#include "Platform/DateTime.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "utl/Str.h"
#include <vector>

class WiiMessage {
public:
    int unk0;
    int unk4;
    String unk8;
    String unk14;
    Quazal::DateTime unk20;
};

class WiiMessageList {
public:
    WiiMessageList();
    ~WiiMessageList();

    std::vector<WiiMessage> mMessages;
};

class WiiMessenger : public MsgSource {
public:
    void EnumerateMessages(WiiMessageList *, Hmx::Object *);
};

extern WiiMessenger TheWiiMessenger;