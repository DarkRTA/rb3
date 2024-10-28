#pragma once
#include "LockStepMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandMachine.h"
#include "utl/Str.h"

class StartLockMsg : public NetMessage {
public:
    StartLockMsg(){}
    virtual ~StartLockMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual LockData* GetLockData() = 0;

    void SetLockInfo(LocalBandMachine*, const char*);

    unsigned int mLockMachineID; // 0x4
    String mLockStepName; // 0x8
};

