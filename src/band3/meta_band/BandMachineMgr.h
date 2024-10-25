#pragma once
#include "game/BandUserMgr.h"
#include "obj/MsgSource.h"

class LocalBandMachine;
class RemoteBandMachine;
class SessionMgr;

class BandMachineMgr : public MsgSource {
public:
    BandMachineMgr(SessionMgr*, BandUserMgr*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~BandMachineMgr();

    void RefreshPrimaryProfileInfo();
    bool IsLeaderMachineLocal() const;
    void SyncLocalMachine(unsigned char);

    static void Init();

    SessionMgr* mSessionMgr; // 0x1c
    BandUserMgr* mUserMgr; // 0x20
    LocalBandMachine* mLocalMachine; // 0x24
    std::vector<RemoteBandMachine*> mRemoteMachines; // 0x28
};