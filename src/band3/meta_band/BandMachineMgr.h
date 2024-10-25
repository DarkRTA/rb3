#pragma once
#include "MetaMessages.h"
#include "game/BandUserMgr.h"
#include "obj/MsgSource.h"

class BandMachine;
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
    LocalBandMachine* GetLocalMachine() const;
    void GetMachines(std::vector<BandMachine*>&) const;
    RemoteBandMachine* GetRemoteMachine(unsigned int, bool) const;
    BandMachine* GetUserMachine(const User*) const;
    void AddRemoteMachine(unsigned int);

    DataNode OnMsg(const ConnectionStatusChangedMsg&);
    DataNode OnMsg(const NewRemoteUserMsg&);

    static void Init();

    SessionMgr* mSessionMgr; // 0x1c
    BandUserMgr* mUserMgr; // 0x20
    LocalBandMachine* mLocalMachine; // 0x24
    std::vector<RemoteBandMachine*> mRemoteMachines; // 0x28
};