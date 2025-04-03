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