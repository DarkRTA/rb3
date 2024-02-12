#include "trainingmgr.hpp"
#include "obj/Dir.h"

extern const char* gNullStr;
TrainingMgr* TheTrainingMgr;

TrainingMgr::TrainingMgr() : 
    user(0), minDiff(0), retScreen(gNullStr), quitToken(gNullStr), curLesson(1) {
    SetName("training_mgr", ObjectDir::sMainDir);
}

TrainingMgr::~TrainingMgr(){

}

void TrainingMgr::Init(){
    TheTrainingMgr = new TrainingMgr();
}

TrainingMgr* GetTheTrainingMgr(){
    return TheTrainingMgr;
}

void TrainingMgr::SetMinimumDifficulty(int diff){
    minDiff = diff;
}

void TrainingMgr::SetReturnInfo(Symbol s1, Symbol s2){
    retScreen = s1;
    quitToken = s2;
}

void TrainingMgr::SetCurrentLesson(int i){
    curLesson = i;
}

void TrainingMgr::ClearCurrentLesson(){
    curLesson = 1;
}

// Handle work here: https://decomp.me/scratch/Z8d2I
