#pragma once
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

    void
    asdkjf(TextStream &stream, float min, float defaultMean, float max, const char *fmt);

public:
    Distribution(float res);

    void Reset();
    float Pctile(float pct);
    void Report(TextStream &stream, const char *tag);

    void operator<<(float value);
};

class BudgetScreen : public UIScreen {
public:
    BudgetScreen();
    virtual ~BudgetScreen() {}
    OBJ_CLASSNAME(BudgetScreen);
    OBJ_SET_TYPE(BudgetScreen);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);

    virtual void Poll();
    virtual void Enter(UIScreen *screen);

    int HeapFreeSize(const char *);

    void NextTest();
    void EndTest();

    NEW_OBJ(BudgetScreen)
    REGISTER_OBJ_FACTORY_FUNC(BudgetScreen)

private:
    UIPanel *mTestPanel;

    float mNullCpu;
    float mNullGs;
    float mTime;
    float mEndTime;

    float mLastCpu; // TODO: was mFrameInc, but Poll indicates otherwise
    float mLastGpu;
    float mLastHud;
    float mLastEtc;

    TextFileStream *mLog;

    Distribution mCpuDist;
    Distribution mGsDist;
    Distribution mHudDist;
    Distribution mEtcDist;

    int mRecordStartTick;
    int mRecordEndTick;

    DataArray *mTests;
    int mTestIdx;

    bool mWorstOnly;
    float mWorstCpuPctile;
    String mWorstCpuName;
    float mWorstGsPctile;
    String mWorstGsName;

    int mSampleCount;
};
