#pragma once
#include "Platform/DateTime.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "utl/Str.h"
#include <vector>

enum _WiiMessageType {
};

class WiiMessage {
public:
    WiiMessage();
    ~WiiMessage();
    WiiMessage &operator=(const WiiMessage &);

    int unk0; // 0x0 - message id
    int unk4;
    String unk8;
    String unk14;
    Quazal::DateTime unk20;
};

class WiiMessageRecord {
public:
    int unk0; // 0x0
    String unk4;
    String unk10;
    int unk1c;
    Hmx::Object *unk20;
    WiiMessageRecord *unk24;
};

class WiiMessageList {
public:
    WiiMessageList();
    ~WiiMessageList();
    WiiMessageList &operator=(const WiiMessageList &);
    WiiMessage *GetMessageByIdx(int) const;
    WiiMessage *GetMessageByMessageID(int) const;
    WiiMessage *AddMessage(int, int, const char *, const char *, Quazal::DateTime);

    std::vector<WiiMessage *> mMessages; // 0x0
};

class WiiMessenger : public MsgSource {
public:
    WiiMessenger();
    virtual ~WiiMessenger();

    void EnumerateMessages(WiiMessageList *, Hmx::Object *);
    void SendMessage(int, const char *, const char *, Hmx::Object *, int);
    void Poll();

    int unk1c; // 0x1c - JobSendMessage*
    WiiMessageRecord *unk20; // 0x20
    int unk24;
    int unk28;
    int unk2c; // 0x2c - JobEnumerateMessages*
    Timer unk30;
    WiiMessageList *unk60;
    Hmx::Object *unk64;
    WiiMessageList unk68;
    int unk70; // 0x70 - quazal root object - its one member is a qList<unsigned int>
    int unk74; // 0x74 - some quazal root object - ditto
    int unk78; // 0x78 - ProtocolCallContext*
};

extern WiiMessenger TheWiiMessenger;