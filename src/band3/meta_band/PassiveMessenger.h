#pragma once
#include "game/BandUser.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/Timer.h"
#include "ui/UIPanel.h"
#include "utl/Symbol.h"
#include <list>

enum PassiveMessageType {
};

class PassiveMessage {
public:
    PassiveMessage(
        DataArray *a,
        PassiveMessageType t,
        Symbol s,
        int i4,
        int i5,
        int i6,
        int i7,
        int i8,
        const char *c1,
        const char *c2,
        const char *c3,
        int i48,
        bool b4c
    )
        : mText(a), mType(t), mChannel(s), unk10(i4), unk14(i6), unk18(i7), unk1c(i8),
          unk20(i5), unk24(c1), unk30(c2), unk3c(c3), unk48(i48), unk4c(b4c) {
        mText->AddRef();
    }
    virtual ~PassiveMessage() { mText->Release(); }

    DataArray *mText; // 0x4
    PassiveMessageType mType; // 0x8
    Symbol mChannel; // 0xc
    int unk10; // 0x10
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    String unk24;
    String unk30;
    String unk3c;
    int unk48;
    bool unk4c;
};

class PassiveMessageQueue {
public:
    PassiveMessageQueue(Hmx::Object *o) : mMessageDuration(2000.0f), mCallback(o) {}
    virtual ~PassiveMessageQueue() {}
    virtual PassiveMessage *GetAndPreProcessFirstMessage();
    virtual void AddMessage(PassiveMessage *);

    void SetMessageDuration(float);
    void Poll();
    void HandlePassiveMessage(PassiveMessage *);
    void MakeIntoCoalescedGoalMessage(PassiveMessage *, int);
    bool RemoveLowerPriorityMessage(PassiveMessage *);

    float mMessageDuration; // 0x4
    std::list<PassiveMessage *> mQueue; // 0x8
    Hmx::Object *mCallback; // 0x10
    Timer mTimer; // 0x14
};

class PassiveMessagesPanel : public UIPanel {
public:
    PassiveMessagesPanel();
    OBJ_CLASSNAME(PassiveMessagesPanel);
    OBJ_SET_TYPE(PassiveMessagesPanel);
    virtual DataNode Handle(DataArray *, bool);
    virtual ~PassiveMessagesPanel();
    virtual void SetTypeDef(DataArray *);
    virtual void Poll();

    void QueueMessage(DataArray *, PassiveMessageType, Symbol, int);
    void PostSetup();
    void SetShowMessages(bool);
    PassiveMessageQueue *GetMessageQueue() const { return mMessageQueue; }

    DataNode OnQueueMessage(DataArray *);

    class PassiveMessenger *mMessenger; // 0x38
    PassiveMessageQueue *mMessageQueue; // 0x3c
    bool mShowMessages; // 0x40
};

class PassiveMessenger : public Hmx::Object {
public:
    PassiveMessenger();
    virtual ~PassiveMessenger();
    virtual DataNode Handle(DataArray *, bool);

    void Poll();
    void TriggerMessage(
        DataArray *,
        PassiveMessageType,
        LocalBandUser *,
        bool,
        Symbol,
        int,
        int,
        int,
        int,
        int,
        const char *,
        const char *,
        const char *,
        int
    );
    void TriggerSkipSongMsg();
    void TriggerInviteFailedMsg();
    void TriggerRemoteUserLeftMsg(const char *);

    DataNode OnMsg(const RemoteUserLeftMsg &);

    bool unk1c;
    Timer mTimer; // 0x20
};

extern PassiveMessenger *ThePassiveMessenger;