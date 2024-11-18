#ifndef OBJ_TASK_H
#define OBJ_TASK_H
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"
#include "utl/SongPos.h"
#include <list>

enum TaskUnits {
    kTaskSeconds,
    kTaskBeats,
    kTaskUISeconds,
    kTaskTutorialSeconds,
    kTaskNumUnits
};

/**
 * @brief Generic task type for simplistic multithreading.
 * Usually used for non-realtime tasks, such as scripting, message passing, etc
 */
class Task : public Hmx::Object {
public:
    Task(){}
    virtual ~Task(){}
    virtual void Poll(float) = 0;
};

class MessageTask : public Task {
public:
    MessageTask(Hmx::Object*, DataArray*);
    virtual ~MessageTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Poll(float);

    ObjOwnerPtr<Hmx::Object, class ObjectDir> mObj;
    DataArray* mMsg;
};

class ScriptTask : public Task {
public:
    struct Var {
        Var(DataNode* np, const DataNode& n) : var(np), value(n) {}
        Var(DataNode* np) : var(np), value(*np) {}

        void Swap(){
            DataNode tmp = value;
            value = *var;
            *var = tmp;
        }

        DataNode* var; // 0x0
        DataNode value; // 0x4
    };

    ScriptTask(DataArray*, bool, DataArray*);
    virtual ~ScriptTask();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Poll(float);

    void UpdateVarsObjects(DataArray*);
    void SwapVars();

    std::list<Var> mVars; // 0x1c
    std::list<Hmx::Object*> mObjects; // 0x24
    ObjOwnerPtr<Hmx::Object> mThis; // 0x2c
    DataArray* mScript; // 0x38
    bool mOnce; // 0x3c
};

class ThreadTask : public ScriptTask {
public:
    ThreadTask(DataArray*, DataArray*);
    virtual ~ThreadTask(){}
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll(float);

    DataNode OnWait(DataArray*);
    DataNode OnWaitTimeout(DataArray*);
    DataNode OnSleep(DataArray*);
    DataNode OnLoop(DataArray*);
    DataNode OnExit(DataArray*);
    DataNode OnCurrent(DataArray*);
    DataNode OnSetCurrent(DataArray*);

    bool mWait; // 0x3d
    int mCurrent; // 0x40
    float mTime; // 0x44
    bool mExecuting; // 0x48
    float mTimeout; // 0x4c
};

class TaskTimeline {
public:
    TaskTimeline();
    ~TaskTimeline();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
};

class TaskMgr : public Hmx::Object {
public:

    enum TimeReference {
        a, b, c
    };

    TaskMgr(){}
    virtual ~TaskMgr();
    virtual DataNode Handle(DataArray*, bool);

    float UISeconds() const;
    float DeltaSeconds() const;
    float DeltaBeat() const;
    float Beat() const;
    float Seconds(TimeReference) const;
    float TutorialSeconds() const;
    float DeltaTime(TaskUnits) const;
    void Start(Task*, TaskUnits, float);
    float Time(TaskUnits) const;
    const char* GetMBT();
    void Init();
    void ClearTasks();
    void SetSeconds(float, bool);
    void SetDeltaTime(TaskUnits, float);
    void SetTimeAndDelta(TaskUnits, float, float);
    void Poll();

    TaskTimeline* mTimelines; // 0x1c
    SongPos mSongPos; // 0x20
    bool unk34;
    Timer unk38;
};

extern TaskMgr TheTaskMgr;

#endif
