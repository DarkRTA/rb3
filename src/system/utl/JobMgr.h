#pragma once
#include "obj/Object.h"
#include <list>

class Job {
public:
    Job();
    virtual ~Job(){}
    virtual void Start() = 0;
    virtual bool IsFinished() = 0;
    virtual void Cancel(Hmx::Object*) = 0;
    virtual void OnCompletion(Hmx::Object*){}

    int ID() const { return mID; }
    
    int mID;
};

class JobMgr {
public:
    Hmx::Object* mCallback;
    std::list<Job*> mJobQueue;
    bool mPreventStart;

    JobMgr(Hmx::Object*);
    ~JobMgr();
    void Poll();
    void QueueJob(Job*);
    bool HasJob(int);
    void CancelJob(int);
    void CancelAllJobs();
};
