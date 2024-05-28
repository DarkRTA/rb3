#include "rndobj/Console.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include <string.h>

static RndConsole* gConsole;

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
        if (b) {
            b = da->Sym(1) == "all"; // i'm just gonna hope that this isn't matching because dtk misreloc moment
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

static DataNode DataCppBreak(DataArray*) {
    PlatformDebugBreak();
    return DataNode(0);
}

static DataNode DataHelp(DataArray* da) {
    gConsole->Help(da->Size() > 1 ? da->Sym(1) : "");
    return DataNode(0);
}

RndConsole::Breakpoint::~Breakpoint(){
    if(parent){
        DataArray* cmd = parent->Command(index);
        cmd->Node(0) = DataNode(DataNop);
    }
}

void RndConsole::InsertBreak(DataArray* arr, int i){
    DataArray* localArr = new DataArray(1);
    localArr->Node(0) = DataNode(DataBreak);
    DataArray* cmd = arr->Command(i);
    localArr->SetFileLine(cmd->File(), cmd->Line());
    arr->Insert(i, DataNode(localArr, kDataCommand));
    localArr->Release();
    mBreakpoints.push_back(Breakpoint());
    mBreakpoints.back().parent = arr;
    mBreakpoints.back().index = i;
}


// // declared/defined in DataArray.cpp
extern DataArray* gCallStack[100];
extern DataArray** gCallStackPtr;

extern DataFunc* gPreExecuteFunc;
extern int gPreExecuteLevel;

void RndConsole::Where(){
    if(mDebugging){
        mOutput->Clear();
        for(DataArray** it = gCallStackPtr - 2 * sizeof(DataArray*); (int)it > gPreExecuteLevel + 3U; it--){
            if(*it != mDebugging){
                TheDebug << "  ";
            }
            TheDebug << MakeString("%s:%d\n", (*it)->mFile, (*it)->mLine);
        }
    }
    else MILO_FAIL("Can't where unless debugging");
}

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

void RndConsole::Help(Symbol sym){
    if(mDebugging){
        mOutput->Clear();
        if(sym == "step") *mOutput << "Step into command\n";
        else if(sym == "next") *mOutput << "Step over command\n";
        else if(sym == "finish") *mOutput << "Finish executing current scope\n";
        else if(sym == "continue") *mOutput << "Continue program execution\n";
        else if(sym == "list") *mOutput << "List file around current line\n";
        else if(sym == "where"){
            *mOutput << "List script stack\n\n";
            *mOutput << "The current line is outdented\n";
        }
        else if(sym == "up") *mOutput << "Move up script stack\n";
        else if(sym == "down") *mOutput << "Move down script stack\n";
        else if(sym == "set_break"){
            *mOutput << "Set dynamic breakpoint\n\n";
            *mOutput << "set_break - current line\n";
            *mOutput << "set_break <handler> - in current object\n";
            *mOutput << "set_break <obj> <handler> - in given object\n";
            *mOutput << "set_break <class> <type> <handler> - in given class and type\n";
        }
        else if(sym == "breakpoints") *mOutput << "List dynamic breakpoints\n";
        else if(sym == "clear"){
            *mOutput << "Clear dynamic breakpoint\n\n";
            *mOutput << "clear - current line\n";
            *mOutput << "clear <n> - numbered breakpoint\n";
            *mOutput << "clear all - all breakpoints\n";
        }
        else if(sym == "cppbreak") *mOutput << "Break into the C++ debugger.\n";
        else {
            *mOutput << "Help on debug commands:\n";
            *mOutput << "help step\n";
            *mOutput << "help next\n";
            *mOutput << "help finish\n";
            *mOutput << "help continue\n";
            *mOutput << "help list\n";
            *mOutput << "help where\n";
            *mOutput << "help up\n";
            *mOutput << "help down\n";
            *mOutput << "help set_break\n";
            *mOutput << "help breakpoints\n";
            *mOutput << "help clear\n\n";
            *mOutput << "help cppbreak\n\n";
            *mOutput << "eval <$var> - return variable value\n";
            *mOutput << "eval [<prop>] - return property value\n";
            *mOutput << "set <$var> <value> - set variable value\n";
            *mOutput << "set [<prop>] <value> - set property value\n";
            *mOutput << "<func> <args> - call script function\n";
            *mOutput << "<obj> <handler> <args> - call object handler\n";
        }
    }
    else MILO_FAIL("Can't help unless debugging");
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
    TheDebug.SetReflect(0);
}
