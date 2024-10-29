#pragma once
#include "LockStepMgr.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandMachine.h"
#include "net/NetMessage.h"
#include "utl/MakeString.h"
#include "utl/Str.h"

class LockData : public virtual Hmx::Object {
public:
    LockData(){}
    virtual ~LockData(){}
};

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

class BasicStartLockMsg : public StartLockMsg {
public:
    BasicStartLockMsg(){}
    virtual ~BasicStartLockMsg(){}
    virtual unsigned char ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode(StaticByteCode()); }
    virtual const char* Name() const { return MakeString("BasicStartLockMsg"); }
    virtual LockData* GetLockData(){ return nullptr; }

    static const char* StaticByteCode(){ return "BasicStartLockMsg"; }
    static NetMessage* NewNetMessage();
    static void Register(){
        TheNetMessageFactory.RegisterNetMessage("BasicStartLockMsg", NewNetMessage);
    }
};

class LockResponseMsg : public NetMessage {
public:
    LockResponseMsg(){}
    LockResponseMsg(bool, LocalBandMachine*, const char*);
    virtual ~LockResponseMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual unsigned char ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode(StaticByteCode()); }
    virtual const char* Name() const { return MakeString("LockResponseMsg"); }

    static const char* StaticByteCode(){ return "LockResponseMsg"; }
    static NetMessage* NewNetMessage();
    static void Register(){
        TheNetMessageFactory.RegisterNetMessage("LockResponseMsg", NewNetMessage);
    }

    bool mLocked; // 0x4
    unsigned int mResponseMachineID; // 0x8
    String mLockStepName; // 0xc
};

class EndLockMsg : public NetMessage {
public:
    EndLockMsg(){}
    EndLockMsg(const char*, bool);
    virtual ~EndLockMsg(){}
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual void Dispatch();
    virtual unsigned char ByteCode() const { return TheNetMessageFactory.GetNetMessageByteCode(StaticByteCode()); }
    virtual const char* Name() const { return MakeString("EndLockMsg"); }

    static const char* StaticByteCode(){ return "EndLockMsg"; }
    static NetMessage* NewNetMessage();
    static void Register(){
        TheNetMessageFactory.RegisterNetMessage("EndLockMsg", NewNetMessage);
    }

    String mLockStepName; // 0x4
    bool mSuccess; // 0x10
};