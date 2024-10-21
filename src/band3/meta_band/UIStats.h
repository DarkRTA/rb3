#pragma once
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/JoypadMsgs.h"
#include "os/OnlineID.h"
#include "ui/UIMessages.h"
#include "ui/UIScreen.h"
#include "utl/Str.h"

class UIStats : public Hmx::Object {
public:
    UIStats();
    virtual ~UIStats(){}
    virtual DataNode Handle(DataArray*, bool);

    void Init();
    void Terminate();
    void Poll();
    void DropScreen(UIScreen*);
    void MaybePublish(UIScreen*);
    void EventLog(unsigned int, unsigned int, unsigned int);

    DataNode OnMsg(const ButtonDownMsg&);
    DataNode OnMsg(const ButtonUpMsg&);
    DataNode OnMsg(const JoypadConnectionMsg&);
    DataNode OnMsg(const UIComponentFocusChangeMsg&);
    DataNode OnMsg(const UIScreenChangeMsg&);

    bool unk1c; // 0x1c
    Symbol unk20; // 0x20
    int unk24; // 0x24
    OnlineID unk28[4]; // 0x28
    String unk48[4]; // 0x48
    OnlineID unk78[4]; // 0x78
    int unk98;
    int unk9c;
    int unka0;
    int unka4;
    int unka8;
    int unkac;
    void* unkb0;
    void* unkb4;
    int unkb8;
};

extern UIStats gUIStats;
extern UIStats* TheUIStats;