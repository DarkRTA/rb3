#pragma once
#include "obj/Object.h"
#include "obj/Msg.h"

class LockStepMgr : public Hmx::Object {
public:
    LockStepMgr(const char*, Hmx::Object*);
    virtual ~LockStepMgr();
    virtual DataNode Handle(DataArray*, bool);

    bool InLock() const;
    void RespondToLock(bool);

    int unk1c;
    std::vector<int> unk20;
    bool unk28;
    Hmx::Object* unk2c;
};

class LockStepStartMsg : public Message {
public:
    LockStepStartMsg() : Message(Type()) {}
    LockStepStartMsg(DataArray *da) : Message(da) {}
    virtual ~LockStepStartMsg() {}
    static Symbol Type() {
        static Symbol t("lock_step_start");
        return t;
    }
};

class LockStepCompleteMsg : public Message {
public:
    LockStepCompleteMsg() : Message(Type()) {}
    LockStepCompleteMsg(DataArray *da) : Message(da) {}
    virtual ~LockStepCompleteMsg() {}
    static Symbol Type() {
        static Symbol t("lock_step_complete");
        return t;
    }
};