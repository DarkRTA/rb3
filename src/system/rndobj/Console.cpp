#include "Console.h"
#include "os/Debug.h"
#include "obj/Data.h"

DataNode DataContinue(DataArray*) {
    gConsole->Continue();
    return DataNode(0);
}

DataNode DataBreak(DataArray* da) {
    gConsole->Break(da);
    return DataNode(0);
}

DataNode DataStep(DataArray*) {
    gConsole->Step(0);
    return DataNode(0);
}

DataNode DataNext(DataArray*) {
    gConsole->Step(-1);
    return DataNode(0);
}

DataNode DataFinish(DataArray*) {
    gConsole->Step(-2);
    return DataNode(0);
}

DataNode DataList(DataArray*) {
    gConsole->List();
    return DataNode(0);
}

DataNode DataWhere(DataArray*) {
    gConsole->Where();
    return DataNode(0);
}

DataNode DataSetBreak(DataArray* da) {
    gConsole->SetBreak(da);
    return DataNode(0);
}

DataNode DataBreakpoints(DataArray*) {
    gConsole->Breakpoints();
    return DataNode(0);
}

DataNode DataClear(DataArray*) {

    return DataNode(0);
}

DataNode DataNop(DataArray*) {
    return DataNode(0);
}

DataNode DataUp(DataArray*) {
    gConsole->MoveLevel(-1);
    return DataNode(0);
}

DataNode DataDown(DataArray*) {
    gConsole->MoveLevel(1);
    return DataNode(0);
}

void PlatformDebugBreak();

DataNode DataCppBreak(DataArray*) {
    PlatformDebugBreak();
    return DataNode(0);
}
#pragma inline off
DataNode DataHelp(DataArray* da) {
    DataNode n = da->Node(1);
    Symbol s = n.Sym(da);
    gConsole->Help(s);
    return DataNode(0);
}
#pragma inline reset
extern DataFunc* gPreExecuteFunc;
extern int gPreExecuteLevel;

void RndConsole::Step(int i) {
    if (mDebugging) {
        mDebugging = 0;
        gPreExecuteFunc = *DataBreak;

    } else FAIL_NOARGS("can't step unless debugging");
}


void RndConsole::Continue() {
    if (mDebugging) mDebugging = 0;
    else FAIL_NOARGS("Can't continue unless debugging");
}

extern void DataRegisterFunc(Symbol, DataFunc);

RndConsole::RndConsole() : mShowing(0), /*mBuffer(0),*/
  mTabLen(0), mCursor(0), mPumpMsgs(0), mDebugging(0), mLevel(0) {
    gConsole = this;
    Symbol s1("break");
    DataRegisterFunc(s1, DataBreak);
    Symbol s2("continue");
    DataRegisterFunc(s2, DataContinue);
    Symbol s3("step");
    DataRegisterFunc(s3, DataStep);
    Symbol s4("next");
    DataRegisterFunc(s4, DataNext);
    Symbol s5("finish");
    DataRegisterFunc(s5, DataFinish);
    Symbol s6("list");
    DataRegisterFunc(s6, DataList);
    Symbol s7("set_break");
    DataRegisterFunc(s7, DataSetBreak);
    Symbol s8("clear");
    DataRegisterFunc(s8, DataClear);
    Symbol s9("breakpoints");
    DataRegisterFunc(s9, DataBreakpoints);
    Symbol s10("up");
    DataRegisterFunc(s10, DataUp);
    Symbol s11("down");
    DataRegisterFunc(s11, DataDown);
    Symbol s12("cpp_break");
    DataRegisterFunc(s12, DataCppBreak);
    Symbol s13("help");
    DataRegisterFunc(s13, DataHelp);
}
