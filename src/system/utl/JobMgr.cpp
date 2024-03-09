#include "utl/JobMgr.h"

namespace {
    int gJobIDCounter;
}

Job::Job(){
    mID = gJobIDCounter++;
}

JobMgr::JobMgr(Hmx::Object* o) : mCallback(o), mJobQueue(), mPreventStart(0) {
    
}

JobMgr::~JobMgr(){
    CancelAllJobs();
}

void JobMgr::QueueJob(Job* job){
    mJobQueue.push_back(job);
    if(mJobQueue.size() == 1 && !mPreventStart){
        mJobQueue.front()->Start();
    }
}

bool JobMgr::HasJob(int id){
    for(std::list<Job*>::iterator it = mJobQueue.begin(); it != mJobQueue.end(); it++){
        if((*it)->mID == id) return true;
    }
    return false;
}

void JobMgr::CancelJob(int id){
    for(std::list<Job*>::iterator it = mJobQueue.begin(); it != mJobQueue.end(); it++){
        if((*it)->mID == id){
            (*it)->Cancel(mCallback);
        }
    }
}

void JobMgr::CancelAllJobs(){
    while(!mJobQueue.empty()){
        mJobQueue.back()->Cancel(mCallback);
        mJobQueue.pop_back();
    }
    // for(std::list<Job*>::iterator it = mJobQueue.begin(); it != mJobQueue.end(); it++){
    //     (*it)->Cancel(mCallback);
    //     delete *it;
    // }
}
