#pragma once
#include "MetaMessages.h"
#include "game/BandUserMgr.h"
#include "game/GameMessages.h"
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
    void RemoveRemoteMachine(unsigned int);
    bool IsSongShared(int) const;
    bool IsSongAllowedToHavePart(int, Symbol) const;
    bool AllMachinesHaveSameNetUIState() const;
    BandMachine* GetLeaderMachine() const;
    String GetLeaderPrimaryProfileName() const;
    String GetLeaderPrimaryBandName() const;
    int GetLeaderPrimaryMetaScore() const;

    DataNode OnMsg(const ConnectionStatusChangedMsg&);
    DataNode OnMsg(const NewRemoteUserMsg&);
    DataNode OnMsg(const RemoteUserLeftMsg&);
    DataNode OnMsg(const ProcessedJoinRequestMsg&);
    DataNode ForEachMachine(const DataArray*);

    static void Init();

    SessionMgr* mSessionMgr; // 0x1c
    BandUserMgr* mUserMgr; // 0x20
    LocalBandMachine* mLocalMachine; // 0x24
    std::vector<RemoteBandMachine*> mRemoteMachines; // 0x28
};