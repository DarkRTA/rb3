#pragma once
#include "NetSession_RV.h"
#include "Platform/Holder.h"
#include "Platform/String.h"
#include "Services/Gathering.h"
#include "network/Protocol/ProtocolCallContext.h"
#include "utl/JobMgr.h"

class RVJob : public Job {
public:
    RVJob();
    virtual ~RVJob();
    virtual bool IsFinished();
    virtual void Cancel(Hmx::Object *);

    Quazal::ProtocolCallContext *mAsync; // 0x8
};

class MakeSessionJob : public Job {
public:
    MakeSessionJob(Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> *, RVSessionData *);
    virtual ~MakeSessionJob();
    virtual void Start();
    virtual bool IsFinished();
    virtual void Cancel(Hmx::Object *);
    virtual void OnCompletion(Hmx::Object *);

    Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> *mGathering; // 0x8
    RVSessionData *mData; // 0xc
    Quazal::ProtocolCallContext *mAsync; // 0x10
    int mState; // 0x14
};

class JoinSessionJob : public Job {
public:
    JoinSessionJob(RVSessionData *);
    virtual ~JoinSessionJob();
    virtual void Start();
    virtual bool IsFinished();
    virtual void Cancel(Hmx::Object *);
    virtual void OnCompletion(Hmx::Object *);

    RVSessionData *mData; // 0x8
    Quazal::ProtocolCallContext *mAsync; // 0xc
    int mState; // 0x10
};

class UpdateSettingsJob : public RVJob {
public:
    UpdateSettingsJob(Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> *);
    virtual ~UpdateSettingsJob();
    virtual void Start();
    virtual void Cancel(Hmx::Object *);
    virtual void OnCompletion(Hmx::Object *);

    Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> *mGathering; // 0xc
};

class ChangeSessionStateJob : public RVJob {
public:
    ChangeSessionStateJob(unsigned int, unsigned int);
    virtual ~ChangeSessionStateJob();
    virtual void Start();

    unsigned int mSessionID; // 0xc
    unsigned int mStateFlags; // 0x10
};