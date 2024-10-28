#pragma once
#include "BandMachine.h"
#include "LockMessages.h"
#include "obj/Object.h"
#include "obj/Msg.h"

class LockStepMgr : public Hmx::Object {
public:
    class WaitList {
    public:
        class WaitingMachine {
        public:
            WaitingMachine(){}
            WaitingMachine(BandMachine* m) : mMachine(m), mResponded(0) {}

            BandMachine* mMachine; // 0x0
            bool mResponded; // 0x4
        };
        
        WaitList(){}

        void AddMachine(BandMachine*);
        void MarkMachineResponded(BandMachine*);
        bool HaveAllMachinesResponded() const;
        void Clear();
        void RemoveMachine(BandMachine*);
        const WaitingMachine* GetWaitingMachine(BandMachine*) const;

        std::vector<WaitingMachine> mList;
    };

    LockStepMgr(const char*, Hmx::Object*);
    virtual ~LockStepMgr();
    virtual DataNode Handle(DataArray*, bool);

    bool InLock() const;
    void RespondToLock(bool);
    void OnStartLockMsg(BandMachine*, LockData*);
    void StartLock();
    void StartLock(StartLockMsg&);
    void OnLockResponseMsg(bool, BandMachine*);
    void CheckAllMachinesResponded();
    void ReleaseLock(bool);
    void OnEndLockMsg(bool);
    bool HasResponded() const { return mHasResponded; }

    DataNode OnMsg(const RemoteMachineLeftMsg&);

    static void Init();

    BandMachine* mLockMachine; // 0x1c
    WaitList mWaitList; // 0x20
    bool mHasResponded; // 0x28
    bool mLockSuccess; // 0x29
    Hmx::Object* mCallback; // 0x2c
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
    LockStepCompleteMsg(bool b) : Message(Type(), b) {}
    LockStepCompleteMsg(DataArray *da) : Message(da) {}
    virtual ~LockStepCompleteMsg() {}
    static Symbol Type() {
        static Symbol t("lock_step_complete");
        return t;
    }
};

class ReleasingLockStepMsg : public Message {
public:
    ReleasingLockStepMsg(bool b) : Message(Type(), b) {}
    ReleasingLockStepMsg(DataArray *da) : Message(da) {}
    virtual ~ReleasingLockStepMsg() {}
    static Symbol Type() {
        static Symbol t("releasing_lock_step");
        return t;
    }
};