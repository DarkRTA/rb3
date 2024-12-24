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
    for(std::list<Job*>::const_iterator it = mJobQueue.begin(); it != mJobQueue.end(); ++it){
        if((*it)->ID() == id) return true;
    }
    return false;
}

void JobMgr::CancelJob(int id){
    for(std::list<Job*>::iterator it = mJobQueue.begin(); it != mJobQueue.end(); ++it){
        if((*it)->ID() == id){
            Job* curJob = *it;
            int curID = curJob->ID();
            it = mJobQueue.erase(it);
            bool oldstart = mPreventStart;
            mPreventStart = true;
            curJob->Cancel(mCallback);
            mPreventStart = oldstart;
            if(curID == id && !oldstart){
                for(std::list<Job*>::iterator it2 = mJobQueue.begin(); it2 != it; ++it2){
                    (*it2)->Start();
                }
            }
            delete curJob;
            return;
        }
    }
    MILO_WARN("This job is not in the queue %i", id);
}

void JobMgr::CancelAllJobs(){
    std::list<Job*> dupeJobs = mJobQueue;
    mJobQueue.clear();
    for(std::list<Job*>::const_iterator it = dupeJobs.begin(); it != dupeJobs.end(); ++it){
        (*it)->Cancel(mCallback);
        delete *it;
        
    }
}
