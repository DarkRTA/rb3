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

void GlitchFinder::PokeStart(const char* cc, unsigned int ui, float f1, float f2, GlitchAverager* avg){
    if(!mStartPoker && f1 < 0) return;
    else {
        if(mStop){
            mStop = false;
            mTime.Restart();
            Reset();
        }
        GlitchPoker* poker = NewPoker();
        strcpy(poker->mName, cc);
        poker->mTime = mTime.SplitMs();
        poker->mParent = mCurPoker;
        poker->mBudget = f1;
        poker->mAvg = avg;
        if(!mStartPoker){
            mCurPoker = poker;
            mStartPoker = poker;
            mLeafThreshold = f2;
            mOverheadCycles = 0;
        }
        else {
            mCurPoker->mChildren.push_back(poker);
            mCurPoker = poker;
            if(ui != 0){
                TIMER_GET_CYCLES(cycles);
                mOverheadCycles += cycles - ui;
            }
        }
    }
}

void GlitchFinder::PokeEnd(unsigned int ui){
    if(mCurPoker){
        mCurPoker->mTimeEnd = mTime.SplitMs();
        mCurPoker = mCurPoker->mParent;
        if(!mCurPoker) CheckDump();
    }
    if(ui){
        TIMER_GET_CYCLES(cycles);
        mOverheadCycles += cycles - ui;
    }
}

void GlitchFinder::CheckDump(){
    if(!mStop && mStartPoker){
        mStop = true;
        mCurPoker->mTimeEnd = mTime.SplitMs();
        static unsigned int sStart;
        if(sStart == 0){
            TIMER_GET_CYCLES(start_cycles);
            sStart = start_cycles;
        }
        bool b1 = mActive && mStartPoker->OverBudget();
        mStartPoker->PollAveragesRecurse(b1);
        if(b1){
            GlitchPoker::smThreshold = mLeafThreshold;
            GlitchPoker::smDumpLeaves = GlitchPoker::smThreshold > 0;
            GlitchPoker::smTotalLeafTime = 0;
            String str(0x2000, '\0');
            str << "-------- GLITCH #" << mGlitchCount << " -------- Frame " << mFrameCount << " -----\n";
            GlitchPoker::smLastDumpTime = mStartPoker->mTime;
            mStartPoker->Dump(str, 0);
            str << "Overhead: " << Timer::CyclesToMs(mOverheadCycles) << "\n";
            str << "-------- GLITCH END --------\n";
            int strLen = str.length();
            if(strLen > 0x400){
                char buf[1024];
                int i = 0;
                for(; i + 0x400 < strLen; i += 0x400){
                    strncpy(buf, str.c_str() + i, 0x400);
                    MILO_LOG(buf);
                }
                strncpy(buf, str.c_str() + i, strLen - i);
                buf[strLen - i] = '\0';
                MILO_LOG(buf);
            }
            else MILO_LOG(str.c_str());
            mGlitchCount++;
        }
        if(mActive) mFrameCount++;
    }
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

DataNode GlitchFindScriptImpl(DataArray* arr, int iii){
    TIMER_GET_CYCLES(cycles);
    if(arr->Node(2).NotNull()){
        switch(iii){
            case 3:
                TheGlitchFinder.PokeStart(arr->Str(1), cycles, -1.0f, 0.0f, 0);
                break;
            case 4:
                TheGlitchFinder.PokeStart(arr->Str(1), cycles, arr->Float(3), 0, 0);
                break;
            case 5:
                TheGlitchFinder.PokeStart(arr->Str(1), cycles, arr->Float(3), arr->Float(4), 0);
                break;
            default:
                MILO_FAIL("improper use of internal glitch finder code");
                break;
        }
        for(int i = iii; i < arr->Size(); i++){
            arr->Command(i)->Execute();
        }
        TIMER_GET_CYCLES(now_cycles);
        TheGlitchFinder.PokeEnd(now_cycles);
        return 0;
    }
    else {
        TIMER_GET_CYCLES(now_cycles);
        TheGlitchFinder.mOverheadCycles += now_cycles - cycles;
        for(int i = iii; i < arr->Size(); i++){
            arr->Command(i)->Execute();
        }
        return 0;
    }
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
    TIMER_GET_CYCLES(cycles);
    TheGlitchFinder.Poke(arr->Str(1), cycles);
    return DataNode(0);
}

void GlitchAverager::PushInstance(float f, bool b){
    mCount++;
    mAvg = mAvg + (f - mAvg) / (mCount);
    if(b){
        mGlitchCount++;
        mGlitchAvg = mGlitchAvg + (f - mGlitchAvg) / (mGlitchCount);
    }
    if(f > mMax) mMax = f;
}