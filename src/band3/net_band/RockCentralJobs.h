#pragma once
#include "net/WiiFriendMgr.h"
#include "net_band/DataResults.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Object.h"
#include "os/Friend.h"
#include "os/PlatformMgr.h"
#include "utl/JobMgr.h"

class RockCentralJob : public Job {
public:
    enum {
        kEnumeratingFriends = 1,
        kUpdatingFriends = 2
    };
    RockCentralJob() {}
    virtual ~RockCentralJob() {}
    virtual void Cancel(Hmx::Object *);
};

class UpdateFriendsListJob : public RockCentralJob, public Hmx::Object {
public:
    UpdateFriendsListJob(int);
    virtual ~UpdateFriendsListJob();
    virtual void Start();
    virtual bool IsFinished();
    virtual DataNode Handle(DataArray *, bool);

    void GetFriendsListToken();

    DataNode OnMsg(const PlatformMgrOpCompleteMsg &);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);

    int unk24;
    int unk28;
    std::vector<Friend *> mFriends; // 0x2c
    DataResultList unk34;
    int mState; // 0x4c
};

class UpdateMasterProfileFriendsListJob : public RockCentralJob, public Hmx::Object {
public:
    UpdateMasterProfileFriendsListJob();
    virtual ~UpdateMasterProfileFriendsListJob();
    virtual void Start();
    virtual bool IsFinished();
    virtual DataNode Handle(DataArray *, bool);

    DataNode OnMsg(const WiiFriendMgrOpCompleteMsg &);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);

    int unk24;
    WiiFriendList unk28; // 0x28
    std::vector<Friend *> mFriends; // 0x30
    DataResultList unk38;
    int mState; // 0x50
};