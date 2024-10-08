#pragma once
#include "net/Synchronize.h"
#include "obj/MsgSource.h"
#include "game/BandUser.h"

class BandUserMgr;
class MatchMaker;

class SessionMgr : public MsgSource, public Synchronizable {
public:
    SessionMgr(BandUserMgr*, MatchMaker*);
    virtual DataNode Handle(DataArray*, bool);
    virtual ~SessionMgr();
    virtual void RegisterOnline();
    virtual void Disconnect();
    virtual bool IsOnlineEnabled() const;
    virtual bool IsLocal() const;
    virtual bool HasRemoteUsers() const;
    virtual LocalBandUser* GetLocalHost() const;
    virtual bool HasUser(const User*) const;
    virtual bool IsBusy() const;
    virtual int NumOpenSlots() const;
    virtual bool AreInvitesAllowed() const;
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);
    virtual void AddLocalUserImpl(LocalBandUser*);
    virtual void RemoveLocalUserImpl(LocalBandUser*);
    virtual void GetLocalUserListImpl(std::vector<LocalUser*>&) const;
};

extern SessionMgr* TheSessionMgr;