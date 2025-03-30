#pragma once
#include "Core/CallContext.h"
#include "utl/JobMgr.h"

class QuazalSession {
public:
    QuazalSession(bool);
    ~QuazalSession();
    bool HasHostLeft();
    bool HaveClientsLeft(std::vector<int> &);

    int unk0; // Quazal::NetZ
    int unk4; // NetZCallback

    static void KillSession();
    static bool StillDeleting();
    static void Poll();
    static Quazal::CallContext *mTerminatingContext;
    // static NetZ* mTerminatingNetZ
};

class MakeQuazalSessionJob : public Job {
public:
    MakeQuazalSessionJob(QuazalSession **, bool);
    virtual ~MakeQuazalSessionJob() {}
    virtual void Start() {}
    virtual bool IsFinished();
    virtual void Cancel(Hmx::Object *);
    virtual void OnCompletion(Hmx::Object *);

    QuazalSession **mSessionAddress; // 0x8
    bool mHosting; // 0xc
};