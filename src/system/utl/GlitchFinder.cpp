#include "utl/GlitchFinder.h"
#include "obj/DataFunc.h"

GlitchFinder TheGlitchFinder;
float GlitchPoker::smLastDumpTime = 0.0f;
std::vector<float> GlitchPoker::smNestedStartTimes;
float GlitchPoker::smThreshold = 0.0f;
float GlitchPoker::smTotalLeafTime = 0.0f;
bool GlitchPoker::smDumpLeaves = false;

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

void GlitchPoker::PrintNestedStartTimes(TextStream& ts, float f){
    if(!smDumpLeaves){
        ts << f << " ";
        if(smNestedStartTimes.size() != 0){
            for(int i = 0; i < smNestedStartTimes.size(); i++){
                ts << " " << f - smNestedStartTimes[i] << " ";
            }
        }
    }
}

void GlitchPoker::PrintResult(TextStream& ts){
    float timeDiff = mTimeEnd - mTime;
    if(mChildren.size() == 0 && (timeDiff < 0.005f)){
        ts << "[ " << mName << " ] ";
    }
    else {
        ts << "{ " << mName << " (" << timeDiff << ") ";
    }
    if(mAvg){
        ts << "<" << mAvg->mAvg << " avg, " << mAvg->mGlitchAvg << " glitch avg, " << mAvg->mMax << " max> ";
    }
}

void GlitchPoker::Dump(TextStream& ts, int theInt){
    if(mTime > smLastDumpTime + 0.005f){
        PrintNestedStartTimes(ts, smLastDumpTime);
        if(!smDumpLeaves){
            ts << "TIME GAP (" << mTime - smLastDumpTime << ")\n";
        }
        else {
            float timeDiff = mTime - smLastDumpTime;
            if(timeDiff > smThreshold){
                ts << "   TIME GAP (" << timeDiff;
                ts << ") before " << mName;
                for(GlitchPoker* p = mParent; p != 0; p = p->mParent){
                    ts << " : " << p->mName;
                }
                ts << "\n";
                smTotalLeafTime += mTime - smLastDumpTime;
            }
        }
    }
    PrintNestedStartTimes(ts, mTime);
    if(!smDumpLeaves && !mChildren.size() && mTimeEnd - mTime < 0.005f){
        ts << "[ " << mName << " ]";
        if(mAvg){
            ts << " (" << mAvg->mAvg << " avg)";
        }
        ts << "\n";
        smLastDumpTime = mTimeEnd;
    }
    else {
        //         if (((s32) smDumpLeaves__11GlitchPoker.unk0 != 0) && ((u8* ) temp_r3->unk50 != NULL)) {
        if(smDumpLeaves && mParent){
            if(mTimeEnd - mTime > smThreshold){
                if(mChildren.size() != 0){
                    float tmpdumptime = smLastDumpTime;
                    smLastDumpTime = mTime;
                    for(int i = 0; i < mChildren.size(); i++){
                        mChildren[i]->Dump(ts, theInt + 1);
                    }
                    float timediff = mTimeEnd - smLastDumpTime;
                    if(timediff > smThreshold){
                        ts << "   TIME GAP (" << timediff;
                        ts << ") at end of " << mName;
                        for(GlitchPoker* p = mParent; p != 0; p = p->mParent){
                            ts << " : " << p->mName;
                        }
                        ts << "\n";
                        smTotalLeafTime += mTimeEnd - smLastDumpTime;
                    }
                    smLastDumpTime = tmpdumptime;
                }
                else {
                    ts << "   ";
                    PrintResult(ts);
                    ts << "}";
                    for(GlitchPoker* p = mParent; p != 0; p = p->mParent){
                        ts << " : " << p->mName;
                    }
                    ts << "\n";
                    smTotalLeafTime += mTimeEnd - mTime;                 
                }           
            }     
        }
        else {
            PrintResult(ts);
            if(mChildren.size() != 0){
                ts << "\n";
                float tmpdumptime = smLastDumpTime;
                smLastDumpTime = mTime;
                smNestedStartTimes.push_back(mTime);
                for(int i = 0; i < mChildren.size(); i++){
                    mChildren[i]->Dump(ts, i + 1);
                }
                if(mTimeEnd > smLastDumpTime + 0.005f){
                    PrintNestedStartTimes(ts, smLastDumpTime);
                    if(!smDumpLeaves){
                        ts << "TIME GAP (" << mTimeEnd - smLastDumpTime << ")\n";
                    }
                    else {
                        float timediff = mTime - smLastDumpTime;
                        if(timediff > smThreshold){
                            ts << "TIME GAP (" << timediff;
                            ts << ") at end of " << mName;
                            for(GlitchPoker* p = mParent; p != 0; p = p->mParent){
                                ts << " : " << p->mName;
                            }
                            ts << "\n";
                        }
                    }
                }
                smNestedStartTimes.pop_back();
                smLastDumpTime = tmpdumptime;
                PrintNestedStartTimes(ts, mTimeEnd);
            }
            if(smDumpLeaves){
                float leafTime = smTotalLeafTime;
                ts << "} total leaf time: " << leafTime << " (" << (leafTime * 100.0f) / (mTimeEnd - mTime) << "pct)";
            }
            else if(mChildren.size() || (mTimeEnd - mTime >= 0.005f)){
                ts << "}";
            }
            ts << "\n";
        }
        smLastDumpTime = mTimeEnd;
    }
}

bool GlitchPoker::OverBudget(){
    if(mBudget > 0.0f && (mTimeEnd - mTime > mBudget)) return true;
    else {
        for(int i = 0; i < mChildren.size(); i++){
            if(mChildren[i]->OverBudget()) return true;
        }
        return false;
    }
}

void GlitchPoker::PollAveragesRecurse(bool b){
    if(mAvg) mAvg->PushInstance(mTimeEnd - mTime, b);
    for(int i = 0; i < mChildren.size(); i++){
        mChildren[i]->PollAveragesRecurse(b);
    }
}

GlitchFinder::GlitchFinder() : mFrameCount(0), mGlitchCount(0), mStop(true), mTime(), mLastTime(0.0f), mStartPoker(0), mCurPoker(0), 
    mActive(true), mDumpLeavesOnly(false), mLeafThreshold(0.0f), mOverheadCycles(0) {
    mTime.Start();
}

GlitchFinder::~GlitchFinder(){
    
}

void GlitchFinder::Init(){
    DataRegisterFunc("glitch_find", OnGlitchFind);
    DataRegisterFunc("glitch_find_budget", OnGlitchFindBudget);
    DataRegisterFunc("glitch_find_leaves", OnGlitchFindLeaves);
    DataRegisterFunc("glitch_find_poke", OnGlitchFindPoke);    
}

void GlitchFinder::Poke(const char* cc, unsigned int ui){
    PokeStart(cc, 0, -1.0f, 0.0f, 0);
    PokeEnd(ui);
}

GlitchPoker* GlitchFinder::NewPoker(){
    if(8 <= mPokerIndex) MILO_FAIL("too many glitch pokers : %d\n", mPokerIndex);
    GlitchPoker* thePoker = &mPokerPool[mPokerIndex++];
    thePoker->ClearData();
    return thePoker;
}

void GlitchFinder::Reset(){
    mPokerIndex = 0;
    mCurPoker = 0;
    mStartPoker = 0;
}

DataNode GlitchFindScriptImpl(DataArray*, int){

}

DataNode GlitchFinder::OnGlitchFind(DataArray* arr){
    return GlitchFindScriptImpl(arr, 3);
}

DataNode GlitchFinder::OnGlitchFindBudget(DataArray* arr){
    return GlitchFindScriptImpl(arr, 4);
}

DataNode GlitchFinder::OnGlitchFindLeaves(DataArray* arr){
    return GlitchFindScriptImpl(arr, 5);
}

DataNode GlitchFinder::OnGlitchFindPoke(DataArray* arr){
    TheGlitchFinder.Poke(arr->Str(1), 0);
    return DataNode(0);
}