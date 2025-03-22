#include "obj/Task.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/DataUtl.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/Timer.h"
#include "utl/BeatMap.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"
#include "utl/TempoMap.h"

TaskMgr TheTaskMgr;

MessageTask::MessageTask(Hmx::Object *o, DataArray *msg) : mObj(this, o), mMsg(msg) {
    MILO_ASSERT(msg, 0x1D);
    msg->AddRef();
}

MessageTask::~MessageTask() {
    if (mMsg) {
        mMsg->Release();
        mMsg = 0;
    }
}

void MessageTask::Replace(Hmx::Object *from, Hmx::Object *to) {
    Hmx::Object::Replace(from, to);
    if (from == mObj) {
        if (!to)
            delete this;
        else
            mObj = to;
    }
}

void MessageTask::Poll(float f) {
    if (mObj && mMsg) {
        DataNode r = mObj->Handle(mMsg, false);
        if (r.Type() != kDataUnhandled)
            delete this;
    }
}

ScriptTask::ScriptTask(DataArray *script, bool once, DataArray *updateVarsObjs)
    : mThis(this, DataThis()), mScript(script), mOnce(once) {
    script->AddRef();
    static DataNode &task = DataVariable("task");
    DataNode taskNode = task;
    task = this;
    mVars.push_back(Var(&task));
    if (!updateVarsObjs)
        updateVarsObjs = script;
    UpdateVarsObjects(updateVarsObjs);
    task = taskNode;
}

ScriptTask::~ScriptTask() {
    for (std::list<Hmx::Object *>::iterator it = mObjects.begin(); it != mObjects.end();
         it++) {
        (*it)->Release(this);
    }
    mScript->Release();
}

void ScriptTask::Replace(Hmx::Object *from, Hmx::Object *to) {
    Hmx::Object::Replace(from, to);
    if (!to) {
        if (from != mThis && !ListFind(mObjects, from)) {
            return;
        }
        delete this;
    }
}

DataNode OnScriptTask(DataArray *arr) {
    bool local_once = true;
    float local_delay = 0;
    int local_units = arr->Int(1);
    const char *local_name = nullptr;
    arr->FindData(once, local_once, false);
    arr->FindData(delay, local_delay, false);
    arr->FindData(units, local_units, false);
    arr->FindData(name, local_name, false);
    ScriptTask *task = new ScriptTask(
        arr->FindArray(script), local_once, arr->FindArray(preserve, false)
    );
    if (local_name) {
        MILO_ASSERT(DataThis(), 0x8A);
        task->SetName(local_name, DataThis()->DataDir());
    }
    TheTaskMgr.Start(task, (TaskUnits)local_units, local_delay);
    return task;
}

void ScriptTask::UpdateVarsObjects(DataArray *d) {
    MILO_ASSERT(d, 0x94);
    int size = d->Size();
    for (int i = 0; i < size; i++) {
        DataType curType = d->Type(i);
        Hmx::Object *obj = nullptr;
        if (curType == kDataObject) {
            obj = d->UncheckedObj(i);
        } else if (curType == kDataSymbol || curType == kDataString) {
            const char *name = d->LiteralStr(i);
            ObjectDir *search = mThis ? mThis->DataDir() : ObjectDir::sMainDir;
            obj = search->FindObject(name, true);
        } else if (curType == kDataVar) {
            DataNode *var = d->UncheckedVar(i);
            for (std::list<Var>::iterator it = mVars.begin(); it != mVars.end(); ++it) {
                if ((*it).var == var) {
                    var = nullptr;
                    break;
                }
            }
            if (var) {
                mVars.push_back(Var(var));
            }
        } else if (curType - 0x10U <= 1) {
            UpdateVarsObjects(d->UncheckedArray(i));
        }

        if (obj && obj != mThis && !ListFind(mObjects, obj)) {
            mObjects.push_back(obj);
            obj->AddRef(this);
        }
    }
}

void ScriptTask::SwapVars() {
    for (std::list<Var>::iterator it = mVars.begin(); it != mVars.end(); ++it) {
        it->Swap();
    }
}

void ScriptTask::Poll(float f) {
    MILO_ASSERT(mScript, 200);
    SwapVars();
    static DataArrayPtr args(new DataArray(1));
    args->Node(0) = f;
    DataNode handled = mScript->ExecuteScript(1, mThis, args, 0);
    SwapVars();
    if (mOnce || !handled.Int()) {
        delete this;
    }
}

ThreadTask::ThreadTask(DataArray *script, DataArray *updateVarsObjs)
    : ScriptTask(script, false, updateVarsObjs), mCurrent(1), mTime(0), mExecuting(0),
      mTimeout(-1) {}

DataNode OnThreadTask(DataArray *arr) {
    float local_delay = 0;
    int units = arr->Int(1);
    const char *local_name = nullptr;
    arr->FindData(delay, local_delay, false);
    arr->FindData(name, local_name, false);
    ThreadTask *task =
        new ThreadTask(arr->FindArray(script), arr->FindArray(preserve, false));
    if (local_name) {
        MILO_ASSERT(DataThis(), 0xF7);
        task->SetName(local_name, DataThis()->DataDir());
    }
    TheTaskMgr.Start(task, (TaskUnits)units, local_delay);
    return task;
}

void ThreadTask::Replace(Hmx::Object *from, Hmx::Object *to) {
    if (!mExecuting) {
        ScriptTask::Replace(from, to);
    } else {
        Hmx::Object::Replace(from, to);
        // mObjects.remove_if(ObjMatchPr());
    }
}

void ThreadTask::Poll(float f) {
    if (mExecuting)
        MILO_FAIL("Can't re-enter ThreadTask::Poll");
    MILO_ASSERT(mScript, 0x10F);
    if (f < mTime)
        return;
    else {
        mTime = f;
        mWait = false;
        mExecuting = true;
        SwapVars();
        Hmx::Object *old_this = DataSetThis(mThis);
        for (; mCurrent < mScript->Size(); mCurrent++) {
            mScript->Command(mCurrent)->Execute();
            if (mWait)
                break;
        }
        DataSetThis(old_this);
        SwapVars();
        mExecuting = false;
        if (mCurrent == mScript->Size()) {
            delete this;
        }
    }
}

BEGIN_HANDLERS(ThreadTask)
    HANDLE(wait, OnWait)
    HANDLE(wait_timeout, OnWaitTimeout)
    HANDLE(sleep, OnSleep)
    HANDLE(loop, OnLoop)
    HANDLE_STATIC(exit, OnExit)
    HANDLE(current, OnCurrent)
    HANDLE(set_current, OnSetCurrent)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x141)
END_HANDLERS

DataNode ThreadTask::OnSetCurrent(DataArray *arr) {
    mCurrent = arr->Int(2);
    return 0;
}

DataNode ThreadTask::OnCurrent(DataArray *) { return mCurrent; }

DataNode ThreadTask::OnWait(DataArray *arr) {
    mWait = arr->Int(2);
    return 0;
}

DataNode ThreadTask::OnWaitTimeout(DataArray *a) {
    MILO_ASSERT(a->Size() > 2, 0x156);
    if (mTimeout == -1.0f) {
        mTimeout = mTime + a->Float(3);
    }
    bool d1 = mTime >= mTimeout;
    bool wait = false;
    if (!d1) {
        if (a->Int(2))
            wait = true;
    }
    mWait = wait;
    if (!wait) {
        mTimeout = -1.0f;
        if (a->Size() > 3) {
            *a->Var(4) = d1;
        }
    }
    return 0;
}

DataNode ThreadTask::OnSleep(DataArray *arr) {
    mWait = true;
    mTime += arr->Float(2);
    mCurrent++;
    return 0;
}

DataNode ThreadTask::OnLoop(DataArray *arr) {
    mCurrent = 1;
    return 0;
}

DataNode ThreadTask::OnExit(DataArray *arr) {
    mWait = true;
    mCurrent = mScript->Size();
    return 0;
}

void TaskMgr::Init() {
    SetName("taskmgr", ObjectDir::Main());
    mTime.Restart();
    mTimelines = new TaskTimeline[kTaskNumUnits];
    mAutoSecondsBeats = true;
    DataRegisterFunc("script_task", OnScriptTask);
    DataRegisterFunc("thread_task", OnThreadTask);
}

TaskTimeline::TaskTimeline() : mTime(0), mLastTime(0), mPollingTask(0) {}

TaskTimeline::~TaskTimeline() {}

void TaskMgr::Terminate() {
    SetName(0, 0);
    delete[] mTimelines;
    mTimelines = nullptr;
}

void TaskMgr::SetUISeconds(float f, bool b) { mTimelines[kTaskUISeconds].SetTime(f, b); }

float TaskMgr::UISeconds() const { return mTimelines[kTaskUISeconds].GetTime(); }
float TaskMgr::DeltaUISeconds() const { return mTimelines[kTaskUISeconds].DeltaTime(); }
float TaskMgr::DeltaTime(TaskUnits u) const { return mTimelines[u].DeltaTime(); }

void TaskMgr::SetDeltaTime(TaskUnits u, float delta) {
    TaskTimeline &timeline = mTimelines[u];
    timeline.mLastTime = timeline.mTime - delta;
}

void TaskMgr::SetTimeAndDelta(TaskUnits u, float time, float delta) {
    TaskTimeline &timeline = mTimelines[u];
    timeline.mTime = time;
    timeline.mLastTime = time - delta;
}

void TaskMgr::SetSecondsAndBeat(float f1, float f2, bool b) {
    mAutoSecondsBeats = false;
    mTimelines[kTaskSeconds].SetTime(f1, b);
    mTimelines[kTaskBeats].SetTime(f2, b);
}

void TaskMgr::SetSeconds(float f, bool b) {
    mAutoSecondsBeats = false;
    mTimelines[kTaskSeconds].SetTime(f, b);
    mTimelines[kTaskBeats].SetTime(
        TheBeatMap->Beat(TheTempoMap->TimeToTick(f * 1000.0f)), b
    );
}

float TaskMgr::Time(TaskUnits u) const { return mTimelines[u].GetTime(); }

void TaskMgr::SetAVOffset(float offset) { mAVOffset = offset; }

float TaskMgr::Seconds(TimeReference ref) const {
    float time = mTimelines[kTaskSeconds].GetTime();
    if (ref == 0) {
        time -= mAVOffset;
    }
    return time;
}

float TaskMgr::DeltaSeconds() const { return mTimelines[kTaskSeconds].DeltaTime(); }
float TaskMgr::Beat() const { return mTimelines[kTaskBeats].GetTime(); }
float TaskMgr::DeltaBeat() const { return mTimelines[kTaskBeats].DeltaTime(); }
float TaskMgr::TutorialSeconds() const {
    return mTimelines[kTaskTutorialSeconds].GetTime();
}
float TaskMgr::DeltaTutorialSeconds() const {
    return mTimelines[kTaskTutorialSeconds].DeltaTime();
}

void TaskMgr::Poll() {
    START_AUTO_TIMER("anim");
    mTime.Split();
    TaskTimeline::TaskInfo *info;
    if (mAutoSecondsBeats) {
        float secs = mTime.Ms() / 1000.0f;
        mTimelines[kTaskSeconds].SetTime(secs, false);
        mTimelines[kTaskBeats].SetTime(secs * 2.0f, false);
    }
    for (int i = 0; i < kTaskNumUnits; i++) {
        mTimelines[i].Poll();
    }
}

void TaskMgr::ClearTasks() {
    for (int i = 0; i < kTaskNumUnits; i++) {
        mTimelines[i].ClearTasks();
    }
}

void TaskMgr::ClearTimelineTasks(TaskUnits u) { mTimelines[u].ClearTasks(); }

void TaskMgr::Start(Task *t, TaskUnits u, float f) { mTimelines[u].AddTask(t, f); }

const char *TaskMgr::GetMBT() {
    return MakeString(
        "%d:%d:%03d", mSongPos.GetMeasure(), mSongPos.GetBeat(), mSongPos.GetTick()
    );
}

BEGIN_HANDLERS(TaskMgr)
    HANDLE_ACTION(clear_tasks, ClearTasks())
    HANDLE_EXPR(seconds, Seconds(kRealTime))
    HANDLE_EXPR(ms, Seconds(kRealTime) * 1000.0f)
    HANDLE_EXPR(delta_seconds, mTimelines[kTaskSeconds].DeltaTime())
    HANDLE_EXPR(beat, mTimelines[kTaskBeats].GetTime())
    HANDLE_EXPR(delta_beat, mTimelines[kTaskBeats].DeltaTime())
    HANDLE_EXPR(ui_seconds, mTimelines[kTaskUISeconds].GetTime())
    HANDLE_EXPR(ui_delta_seconds, mTimelines[kTaskUISeconds].DeltaTime())
    HANDLE_EXPR(tutorial_seconds, mTimelines[kTaskTutorialSeconds].GetTime())
    HANDLE_EXPR(delta_tutorial_seconds, mTimelines[kTaskTutorialSeconds].DeltaTime())
    HANDLE_EXPR(
        mbt, MakeString("%d:%d:%03d", mSongPos.mMeasure, mSongPos.mBeat, mSongPos.mTick)
    )
    HANDLE_EXPR(total_tick, mSongPos.GetTotalTick())
    HANDLE(time_til_next, OnTimeTilNext)
    HANDLE_ACTION(set_seconds, SetSeconds(_msg->Float(2), _msg->Int(3)))
    HANDLE_CHECK(0x2D9)
END_HANDLERS

DataNode TaskMgr::OnTimeTilNext(DataArray *arr) {
    float f2 = arr->Float(2);
    float f3 = arr->Float(3);
    float beat = Beat();
    float floored = floor(beat / f2);
    float f1 = f3 * (1.0f - (beat / f2 - floored));
    if (f3 >= f2 - f1) {
        return 0.0f;
    } else
        return f1;
}