#pragma once
#include "net/WiiFriendMgr.h"
#include "net_band/DataResults.h"
#include "obj/Object.h"
#include "utl/JobMgr.h"

class RockCentralJob : public Job {
public:
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

    int unk24;
    int unk28;
    std::vector<int> unk2c;
    DataResultList unk34;
    int unk4c;
};

class UpdateMasterProfileFriendsListJob : public RockCentralJob, public Hmx::Object {
public:
    UpdateMasterProfileFriendsListJob();
    virtual ~UpdateMasterProfileFriendsListJob();
    virtual void Start();
    virtual bool IsFinished();
    virtual DataNode Handle(DataArray *, bool);

    int unk24;
    WiiFriendList unk28; // 0x28
    std::vector<int> unk30; // 0x30
    DataResultList unk38;
    int unk50;
};