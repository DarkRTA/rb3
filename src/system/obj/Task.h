#ifndef OBJ_TASK_H
#define OBJ_TASK_H
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"
#include "utl/PoolAlloc.h"
#include "utl/SongPos.h"
#include <list>

enum TaskUnits {
    kTaskSeconds = 0,
    kTaskBeats = 1,
    kTaskUISeconds = 2,
    kTaskTutorialSeconds = 3,
    kTaskNumUnits = 4
};

/**
 * @brief Generic task type for simplistic multithreading.
 * Usually used for non-realtime tasks, such as scripting, message passing, etc
 */
class Task : public Hmx::Object {
public:
    Task() {}
    virtual ~Task() {}
    virtual void Poll(float) = 0;
};

class MessageTask : public Task {
public:
    MessageTask(Hmx::Object *, DataArray *);
    virtual ~MessageTask();
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Poll(float);

    ObjOwnerPtr<Hmx::Object, class ObjectDir> mObj;
    DataArray *mMsg;
};

class ScriptTask : public Task {
public:
    struct Var {
        Var(DataNode *np, const DataNode &n) : var(np), value(n) {}
        Var(DataNode *np) : var(np), value(*np) {}

        void Swap() {
            DataNode tmp = value;
            value = *var;
            *var = tmp;
        }

        DataNode *var; // 0x0
        DataNode value; // 0x4
    };

    ScriptTask(DataArray *, bool, DataArray *);
    virtual ~ScriptTask();
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Poll(float);

    void UpdateVarsObjects(DataArray *);
    void SwapVars();

    std::list<Var> mVars; // 0x1c
    std::list<Hmx::Object *> mObjects; // 0x24
    ObjOwnerPtr<Hmx::Object> mThis; // 0x2c
    DataArray *mScript; // 0x38
    bool mOnce; // 0x3c
};

class ThreadTask : public ScriptTask {
public:
    ThreadTask(DataArray *, DataArray *);
    virtual ~ThreadTask() {}
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll(float);

    DataNode OnWait(DataArray *);
    DataNode OnWaitTimeout(DataArray *);
    DataNode OnSleep(DataArray *);
    DataNode OnLoop(DataArray *);
    DataNode OnExit(DataArray *);
    DataNode OnCurrent(DataArray *);
    DataNode OnSetCurrent(DataArray *);

    bool mWait; // 0x3d
    int mCurrent; // 0x40
    float mTime; // 0x44
    bool mExecuting; // 0x48
    float mTimeout; // 0x4c
};

class TaskTimeline {
public:
    class TaskInfo {
    public:
        TaskInfo(Task *t, float f) : unk0(0, t), unkc(f) {}
        ObjPtr<Task> unk0;
        float unkc;
    };
    TaskTimeline();
    ~TaskTimeline();

    NEW_POOL_OVERLOAD(TaskTimeline);
    DELETE_POOL_OVERLOAD(TaskTimeline);
    void *operator new[](size_t t) { return _MemAlloc(t, 0); }
    void operator delete[](void *v) { _MemFree(v); }

    void SetTime(float f, bool b) {
        mLastTime = b ? f : mTime;
        mTime = f;
    }

    float GetTime() const { return mTime; }
    float DeltaTime() const { return mTime - mLastTime; }
    void Poll() {
        for (std::list<TaskInfo>::iterator it = mTasks.begin(); it != mTasks.end();) {
            if ((*it).unkc > mTime)
                break;
            float f1 = (*it).unkc;
            float f2 = mTime;
            float diff = f2 - f1;
            if ((*it).unk0) {
                mPollingTask = (*it).unk0;
                (*it).unk0->Poll(diff);
                ++it;
            } else {
                it = mTasks.erase(it);
            }
        }
        mPollingTask = nullptr;
        for (std::list<TaskInfo>::iterator it = mAddedTasks.begin();
             it != mAddedTasks.end();
             ++it) {
            AddTask(*it);
        }
        mAddedTasks.clear();
    }

    void ClearTasks() {
        for (std::list<TaskInfo>::iterator it = mTasks.begin(); it != mTasks.end();
             ++it) {
            if ((*it).unk0 != mPollingTask) {
                delete (*it).unk0;
            }
        }
    }

    void AddTask(Task *t, float f) { AddTask(TaskInfo(t, mTime + f)); }

    void AddTask(const TaskInfo &info) {
        if (!&info)
            MILO_FAIL("Null TaskInfo");
        else {
            if (mPollingTask) {
                mAddedTasks.push_back(info);
            } else {
                for (std::list<TaskInfo>::iterator it = mTasks.begin();
                     it != mTasks.end();
                     ++it) {
                    if (info.unkc < (*it).unkc) {
                        mTasks.insert(it, info);
                        return;
                    }
                }
                mTasks.push_back(info);
            }
        }
    }

    std::list<TaskInfo> mTasks; // 0x0
    std::list<TaskInfo> mAddedTasks; // 0x8
    float mTime; // 0x10
    float mLastTime; // 0x14
    Task *mPollingTask; // 0x18
};

class TaskMgr : public Hmx::Object {
public:
    enum TimeReference {
        kDelayedTime = 0,
        kRealTime = 1
    };

    TaskMgr() {}
    virtual ~TaskMgr() {}
    virtual DataNode Handle(DataArray *, bool);

    float UISeconds() const;
    float DeltaSeconds() const;
    float DeltaBeat() const;
    float DeltaUISeconds() const;
    float Beat() const;
    float Seconds(TimeReference) const;
    float TutorialSeconds() const;
    float DeltaTime(TaskUnits) const;
    void Start(Task *, TaskUnits, float);
    float Time(TaskUnits) const;
    const char *GetMBT();
    void ClearTasks();
    void SetSeconds(float, bool);
    void SetDeltaTime(TaskUnits, float);
    void SetTimeAndDelta(TaskUnits, float, float);
    void Poll();
    void Init();
    void Terminate();
    void SetUISeconds(float, bool);
    void SetSecondsAndBeat(float, float, bool);
    void SetAVOffset(float);
    float DeltaTutorialSeconds() const;
    void ClearTimelineTasks(TaskUnits);

    DataNode OnTimeTilNext(DataArray *);

    TaskTimeline *mTimelines; // 0x1c
    SongPos mSongPos; // 0x20
    bool mAutoSecondsBeats; // 0x34
    Timer mTime; // 0x38
    float mAVOffset; // 0x68
};

extern TaskMgr TheTaskMgr;

#endif
