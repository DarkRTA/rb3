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
