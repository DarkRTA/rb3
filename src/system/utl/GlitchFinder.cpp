#include "utl/GlitchFinder.h"

GlitchFinder TheGlitchFinder;
std::vector<float> GlitchPoker::smNestedStartTimes;

GlitchPoker::GlitchPoker(){

}

void GlitchPoker::ClearData(){
    mName[0] = 0;
    mTime = -1.0f;
    mTimeEnd = -1.0f;
    mChildren.clear();
    mParent = 0;
    mBudget = -1.0f;
    mAvg = 0;
}

bool GlitchPoker::OverBudget(){
    if(mBudget > 0.0f && (mTimeEnd - mTime > mBudget)) return true;
    else {
        for(int i = 0; i < mChildren.size(); i++){
            if(mParent->OverBudget()) return true;
        }
        return false;
    }
}

GlitchFinder::GlitchFinder(){

}

GlitchPoker::~GlitchPoker(){

}

GlitchFinder::~GlitchFinder(){
    
}
