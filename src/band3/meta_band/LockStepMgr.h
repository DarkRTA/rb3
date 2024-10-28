#pragma once
#include "BandMachine.h"
#include "obj/Object.h"
#include "obj/Msg.h"

class LockData : public virtual Hmx::Object {
public:
    LockData(){}
    virtual ~LockData(){}
};

class LockStepMgr : public Hmx::Object {
public:
    class WaitList {
    public:
        WaitList(){}
        std::vector<int> mList;
    };

    LockStepMgr(const char*, Hmx::Object*);
    virtual ~LockStepMgr();
    virtual DataNode Handle(DataArray*, bool);

    bool InLock() const;
    void RespondToLock(bool);
    void OnStartLockMsg(BandMachine*, LockData*);

    static void Init();

    BandMachine* mLockMachine; // 0x1c
    WaitList unk20; // 0x20
    bool unk28; // 0x28
    Hmx::Object* unk2c; // 0x2c
};

class LockStepStartMsg : public Message {
public:
    LockStepStartMsg(LockData*);
    LockStepStartMsg(DataArray *da) : Message(da) {}
    virtual ~LockStepStartMsg() {}
    static Symbol Type() {
        static Symbol t("lock_step_start");
        return t;
    }
    LockData* GetLockData() const;
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