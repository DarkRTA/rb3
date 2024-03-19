#include "rndobj/Console.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include <string.h>

static DataNode DataContinue(DataArray*) {
    gConsole->Continue();
    return DataNode(0);
}

static DataNode DataBreak(DataArray* da) {
    gConsole->Break(da);
    return DataNode(0);
}

static DataNode DataStep(DataArray*) {
    gConsole->Step(0);
    return DataNode(0);
}

static DataNode DataNext(DataArray*) {
    gConsole->Step(-1);
    return DataNode(0);
}

static DataNode DataFinish(DataArray*) {
    gConsole->Step(-2);
    return DataNode(0);
}

static DataNode DataList(DataArray*) {
    gConsole->List();
    return DataNode(0);
}

static DataNode DataWhere(DataArray*) {
    gConsole->Where();
    return DataNode(0);
}

static DataNode DataSetBreak(DataArray* da) {
    gConsole->SetBreak(da);
    return DataNode(0);
}

static DataNode DataBreakpoints(DataArray*) {
    gConsole->Breakpoints();
    return DataNode(0);
}

static DataNode DataClear(DataArray* da) {
    int clearInt;
    if(da->Size() < 2) clearInt = 0;
    else {
        bool b = ((const DataArray*)(da))->Node(1).Type() == kDataSymbol;
        if(b){
            clearInt = strcmp(da->Sym(1).Str(), "all");
            b = clearInt == 0;
        }
        clearInt = b ? -1 : da->Int(1);
    }
    gConsole->Clear(clearInt);
    return DataNode(0);
}

static DataNode DataNop(DataArray*) {
    return DataNode(0);
}

static DataNode DataUp(DataArray*) {
    gConsole->MoveLevel(-1);
    return DataNode(0);
}

static DataNode DataDown(DataArray*) {
    gConsole->MoveLevel(1);
    return DataNode(0);
}

void PlatformDebugBreak();

static DataNode DataCppBreak(DataArray*) {
    PlatformDebugBreak();
    return DataNode(0);
}

static DataNode DataHelp(DataArray* da) {
    gConsole->Help(da->Size() > 1 ? da->Sym(1) : "");
    return DataNode(0);
}

extern DataFunc* gPreExecuteFunc;
extern int gPreExecuteLevel;

void RndConsole::Step(int i) {
    if (mDebugging) {
        mDebugging = 0;
        gPreExecuteFunc = *DataBreak;

    } else MILO_FAIL("can't step unless debugging");
}

void RndConsole::Continue() {
    if (mDebugging) mDebugging = 0;
    else MILO_FAIL("Can't continue unless debugging");
}

RndConsole::RndConsole() : mShowing(0), mBuffer(),
  mTabLen(0), mCursor(0), mPumpMsgs(0), mDebugging(0), mLevel(0) {
    gConsole = this;
    mBufPtr = mBuffer.begin();
    mOutput = RndOverlay::Find("output", true);
    mInput = RndOverlay::Find("input", true);
    DataArray* rndCfg = SystemConfig("rnd");
    rndCfg->FindData("console_buffer", mMaxBuffer, true);
    DataRegisterFunc("break", DataBreak);
    DataRegisterFunc("continue", DataContinue);
    DataRegisterFunc("step", DataStep);
    DataRegisterFunc("next", DataNext);
    DataRegisterFunc("finish", DataFinish);
    DataRegisterFunc("list", DataList);
    DataRegisterFunc("where", DataWhere);
    DataRegisterFunc("set_break", DataSetBreak);
    DataRegisterFunc("clear", DataClear);
    DataRegisterFunc("breakpoints", DataBreakpoints);
    DataRegisterFunc("up", DataUp);
    DataRegisterFunc("down", DataDown);
    DataRegisterFunc("cpp_break", DataCppBreak);
    DataRegisterFunc("help", DataHelp);
}

RndConsole::~RndConsole(){
    
}
