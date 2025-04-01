#include "network/net/WiiMessenger.h"
#include "Platform/DateTime.h"
#include "utl/Std.h"

WiiMessenger TheWiiMessenger;
WiiMessageRecord g_Messages[20];

WiiMessage::WiiMessage() {}
WiiMessage::~WiiMessage() {}

WiiMessage &WiiMessage::operator=(const WiiMessage &msg) {
    unk0 = msg.unk0;
    unk4 = msg.unk4;
    unk8 = msg.unk8;
    unk14 = msg.unk14;
    return *this;
}

WiiMessageList::WiiMessageList() {}
WiiMessageList::~WiiMessageList() { DeleteAll(mMessages); }

WiiMessageList &WiiMessageList::operator=(const WiiMessageList &list) {
    int numMsgs = list.mMessages.size();
    DeleteAll(mMessages);
    for (int i = 0; i < numMsgs; i++) {
        WiiMessage *idxMsg = list.GetMessageByIdx(i);
        WiiMessage *msg = new WiiMessage();
        *msg = *idxMsg;
        mMessages.push_back(msg);
    }
    return *this;
}

WiiMessage *WiiMessageList::GetMessageByIdx(int idx) const {
    if (idx >= 0 && idx < mMessages.size()) {
        return mMessages[idx];
    } else
        return nullptr;
}

WiiMessage *WiiMessageList::GetMessageByMessageID(int id) const {
    int numMsgs = mMessages.size();
    for (int i = 0; i < numMsgs; i++) {
        WiiMessage *msg = GetMessageByIdx(i);
        if (msg->unk0 == id)
            return msg;
    }
    return nullptr;
}

WiiMessage *WiiMessageList::AddMessage(
    int i1, int i2, const char *c3, const char *c4, Quazal::DateTime dt
) {
    WiiMessage *msg = new WiiMessage();
    msg->unk0 = i1;
    msg->unk4 = i2;
    msg->unk8 = c3;
    msg->unk14 = c4;
    Quazal::DateTime msgDt = dt;
    msg->unk20 = msgDt;
    mMessages.push_back(msg);
    return msg;
}

WiiMessenger::WiiMessenger()
    : unk1c(0), unk24(0), unk28(0), unk2c(0), unk60(0), unk64(0), unk78(0) {
    int i;
    for (i = 0; i < 19; i++) {
        g_Messages[i].unk24 = &g_Messages[i + 1];
    }
    g_Messages[i].unk24 = nullptr;
    unk20 = g_Messages;
}

WiiMessenger::~WiiMessenger() {}