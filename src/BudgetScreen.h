#ifndef BUDGETSCREEN_H
#define BUDGETSCREEN_H

#include "system/obj/Data.h"
#include "system/obj/ObjMacros.h"
#include "system/ui/UIPanel.h"
#include "system/ui/UIScreen.h"
#include "system/utl/Str.h"
#include "system/utl/TextStream.h"
#include "system/utl/TextFileStream.h"

#include <vector>

class Distribution {
private:
    float mRes;
    float mMin;
    float mMax;
    float mTotal;
    int mCount;
    std::vector<int> mDist;

    void asdkjf(TextStream& stream, float min, float defaultMean, float max, const char* fmt);

public:
    Distribution(float res);

    void Reset();
    float Pctile(float pct);
    void Report(TextStream& stream, const char* tag);

    void operator<<(float value);
};

class BudgetScreen : public UIScreen {
public:
    BudgetScreen();
    virtual ~BudgetScreen() {}
    OBJ_CLASSNAME(BudgetScreen);
    OBJ_SET_TYPE(BudgetScreen);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    virtual void Poll();
    virtual void Enter(UIScreen *);

private:
    UIPanel* mTestPanel;

    float mNullCpu;
    float mNullGs;
    float mTime;
    float mEndTime;
    float mFrameInc;
    float mLastCpu;
    float mLastGpu;
    float mUnk1;

    TextFileStream* mLog;

    Distribution mPollDist;
    Distribution mCpuDist;
    Distribution mGsDist;
    Distribution mUnk2;

    int mRecordStartTick;
    int mRecordEndTick;

    DataArray* mTests;
    int mTestIdx;

    bool mWorstOnly;
    float mWorstCpuPctile;
    String mWorstCpuName;
    float mWorstGsPctile;
    String mWorstGsName;

    int mUnk3;
};

#endif
