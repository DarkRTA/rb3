#include "trainingmgr.hpp"

extern const char* gNullStr;

TrainingMgr::TrainingMgr() : 
    user(0), minDiff(0), retScreen(gNullStr), quitToken(gNullStr), curLesson(1) {
    SetName("training_mgr", ObjectDir::sMainDir);
}

TrainingMgr::~TrainingMgr(){
    
}