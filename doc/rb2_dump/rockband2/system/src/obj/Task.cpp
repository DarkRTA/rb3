/*
    Compile unit: C:\rockband2\system\src\obj\Task.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805F6B60 -> 0x805FAB64
*/
class TaskMgr TheTaskMgr; // size: 0x88, address: 0x80989710
class MessageTask : public Task {
    // total size: 0x38
    class ObjOwnerPtr mObj; // offset 0x28, size 0xC
    class DataArray * mMsg; // offset 0x34, size 0x4
};
// Range: 0x805F6B60 -> 0x805F6C1C
void * MessageTask::MessageTask(class MessageTask * const this /* r29 */, class Object * obj /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__11MessageTask;
}

// Range: 0x805F6C1C -> 0x805F6CEC
void * MessageTask::~MessageTask(class MessageTask * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__11MessageTask;
}

// Range: 0x805F6CEC -> 0x805F6D8C
void MessageTask::Replace(class MessageTask * const this /* r30 */, class Object * to /* r31 */) {}

// Range: 0x805F6D8C -> 0x805F6E7C
void MessageTask::Poll(class MessageTask * const this /* r31 */) {
    // Local variables
    class DataNode r; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class DataNode & task; // size: 0x4, address: 0x80A55224
class ScriptTask : public Task {
    // total size: 0x4C
protected:
    class list mVars; // offset 0x28, size 0x8
    class list mObjects; // offset 0x30, size 0x8
    class ObjOwnerPtr mThis; // offset 0x38, size 0xC
    class DataArray * mScript; // offset 0x44, size 0x4
    unsigned char mOnce; // offset 0x48, size 0x1
};
// Range: 0x805F6E7C -> 0x805F70CC
void * ScriptTask::ScriptTask(class ScriptTask * const this /* r29 */, class DataArray * script /* r30 */, unsigned char once /* r28 */, class DataArray * updateVarsObjs /* r31 */) {
    // Local variables
    class DataNode oldTask; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std30_List_node<Q210ScriptTask3Var>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class DataNode & task;
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__10ScriptTask;
}

struct Var {
    // total size: 0xC
    class DataNode * var; // offset 0x0, size 0x4
    class DataNode value; // offset 0x4, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct Var _M_data; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std30_List_node<Q210ScriptTask3Var>; // size: 0x8, address: 0x8092A148
// Range: 0x805F70CC -> 0x805F71EC
void * ScriptTask::~ScriptTask(class ScriptTask * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__10ScriptTask;
}

// Range: 0x805F71EC -> 0x805F7264
void ScriptTask::Replace(class ScriptTask * const this /* r31 */, class Object * from /* r1+0x8 */) {}

static class Symbol script; // size: 0x4, address: 0x80A5522C
static class Symbol once; // size: 0x4, address: 0x80A55234
static class Symbol units; // size: 0x4, address: 0x80A5523C
static class Symbol delay; // size: 0x4, address: 0x80A55244
static class Symbol name; // size: 0x4, address: 0x80A5524C
static class Symbol preserve; // size: 0x4, address: 0x80A55254
// Range: 0x805F7264 -> 0x805F74EC
static class DataNode OnScriptTask(class DataArray * data /* r30 */) {
    // Local variables
    unsigned char o; // r1+0x8
    float d; // r1+0x2C
    enum TaskUnits u; // r1+0x28
    const char * n; // r1+0x24
    class Task * t; // r27

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol preserve;
    // -> static class Symbol name;
    // -> static class Symbol delay;
    // -> static class Symbol units;
    // -> static class Symbol once;
    // -> static class Symbol script;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805F74EC -> 0x805F77F0
void ScriptTask::UpdateVarsObjects(class ScriptTask * const this /* r28 */, class DataArray * d /* r29 */) {
    // Local variables
    int size; // r31
    int i; // r30
    enum DataType t; // r0
    class Object * o; // r1+0x1C
    class DataNode * var; // r4
    struct _List_iterator i; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std30_List_node<Q210ScriptTask3Var>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805F77F0 -> 0x805F78A8
void ScriptTask::SwapVars(class ScriptTask * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

static class DataArrayPtr args; // size: 0x8, address: 0x809897A8
// Range: 0x805F78A8 -> 0x805F7ABC
void ScriptTask::Poll(class ScriptTask * const this /* r31 */, float time /* f31 */) {
    // Local variables
    class DataNode ret; // r1+0x10

    // References
    // -> static class DataArrayPtr args;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class ThreadTask : public ScriptTask {
    // total size: 0x5C
    unsigned char mWait; // offset 0x49, size 0x1
    int mCurrent; // offset 0x4C, size 0x4
    float mTime; // offset 0x50, size 0x4
    unsigned char mExecuting; // offset 0x54, size 0x1
    unsigned char mAutoDelete; // offset 0x55, size 0x1
    float mTimeout; // offset 0x58, size 0x4
};
// Range: 0x805F7ABC -> 0x805F7B20
void * ThreadTask::ThreadTask(class ThreadTask * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10ThreadTask;
}

static class Symbol script; // size: 0x4, address: 0x80A5525C
static class Symbol delay; // size: 0x4, address: 0x80A55264
static class Symbol name; // size: 0x4, address: 0x80A5526C
static class Symbol preserve; // size: 0x4, address: 0x80A55274
// Range: 0x805F7B20 -> 0x805F7D24
static class DataNode OnThreadTask(class DataArray * data /* r30 */) {
    // Local variables
    float d; // r1+0x1C
    enum TaskUnits u; // r27
    const char * n; // r1+0x18
    class Task * t; // r26

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol preserve;
    // -> static class Symbol name;
    // -> static class Symbol delay;
    // -> static class Symbol script;
}

// Range: 0x805F7D24 -> 0x805F7D68
void ThreadTask::Replace() {}

// Range: 0x805F7D68 -> 0x805F7F1C
void ThreadTask::Poll(class ThreadTask * const this /* r31 */, float time /* f31 */) {
    // Local variables
    class Object * oldThis; // r29

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A5527C
static class Symbol _s; // size: 0x4, address: 0x80A55284
static class Symbol _s; // size: 0x4, address: 0x80A5528C
static class Symbol _s; // size: 0x4, address: 0x80A55294
static class Symbol _s; // size: 0x4, address: 0x80A5529C
static class Symbol _s; // size: 0x4, address: 0x80A552A4
static class Symbol _s; // size: 0x4, address: 0x80A552AC
// Range: 0x805F7F78 -> 0x805F8B70
class DataNode ThreadTask::Handle(class ThreadTask * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x805F8B70 -> 0x805F8BD4
class DataNode ThreadTask::OnSetCurrent(class ThreadTask * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x805F8BD4 -> 0x805F8BE8
class DataNode ThreadTask::OnCurrent() {}

// Range: 0x805F8BE8 -> 0x805F8C58
class DataNode ThreadTask::OnWait(class ThreadTask * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x805F8C58 -> 0x805F8DBC
class DataNode ThreadTask::OnWaitTimeout(class ThreadTask * const this /* r28 */, class DataArray * a /* r29 */) {
    // Local variables
    unsigned char timedOut; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805F8DBC -> 0x805F8E3C
class DataNode ThreadTask::OnSleep(class ThreadTask * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x805F8E3C -> 0x805F8E54
class DataNode ThreadTask::OnLoop() {}

// Range: 0x805F8E54 -> 0x805F8E78
class DataNode ThreadTask::OnExit() {}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std37_List_node<Q212TaskTimeline8TaskInfo>; // size: 0x8, address: 0x8092A290
class TaskTimeline {
    // total size: 0x1C
    class list mTasks; // offset 0x0, size 0x8
    class list mAddedTasks; // offset 0x8, size 0x8
    float mTime; // offset 0x10, size 0x4
    float mLastTime; // offset 0x14, size 0x4
    class Task * mPollingTask; // offset 0x18, size 0x4
};
// Range: 0x805F8E78 -> 0x805F8ECC
void * TaskTimeline::TaskTimeline() {}

struct TaskInfo {
    // total size: 0x10
    class ObjPtr task; // offset 0x0, size 0xC
    float start; // offset 0xC, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct TaskInfo _M_data; // offset 0x8, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x805F8ECC -> 0x805F8F24
void TaskMgr::Terminate(class TaskMgr * const this /* r31 */) {}

// Range: 0x805F8F24 -> 0x805F8F48
void TaskMgr::SetUISeconds() {}

// Range: 0x805F8F48 -> 0x805F8F54
float TaskMgr::UISeconds() {}

// Range: 0x805F8F54 -> 0x805F8F68
float TaskMgr::DeltaUISeconds() {}

// Range: 0x805F8F68 -> 0x805F8F84
float TaskMgr::DeltaTime() {}

// Range: 0x805F8F84 -> 0x805F8FA0
void TaskMgr::SetDeltaTime() {}

// Range: 0x805F8FA0 -> 0x805F8FEC
void TaskMgr::SetSecondsAndBeat() {}

// Range: 0x805F8FEC -> 0x805F9098
void TaskMgr::SetSeconds(class TaskMgr * const this /* r30 */, unsigned char reset /* r31 */) {
    // Local variables
    int tick; // r0
    float beat; // f1

    // References
    // -> class BeatMap * TheBeatMap;
    // -> class TempoMap * TheTempoMap;
}

// Range: 0x805F9098 -> 0x805F90AC
float TaskMgr::Time() {}

// Range: 0x805F90AC -> 0x805F90B4
void TaskMgr::SetAVOffset() {}

// Range: 0x805F90B4 -> 0x805F90D0
float TaskMgr::Seconds() {
    // Local variables
    float seconds; // f1
}

// Range: 0x805F90D0 -> 0x805F90E4
float TaskMgr::DeltaSeconds() {}

// Range: 0x805F90E4 -> 0x805F90F0
float TaskMgr::Beat() {}

// Range: 0x805F90F0 -> 0x805F9104
float TaskMgr::DeltaBeat() {}

// Range: 0x805F9104 -> 0x805F9128
void TaskMgr::SetTutorialSeconds() {}

// Range: 0x805F9128 -> 0x805F9134
float TaskMgr::TutorialSeconds() {}

// Range: 0x805F9134 -> 0x805F9148
float TaskMgr::DeltaTutorialSeconds() {}

static class Timer * _t; // size: 0x4, address: 0x80A552B0
static class Timer * _t; // size: 0x4, address: 0x80A552B8
// Range: 0x805F9148 -> 0x805F967C
void TaskMgr::Poll(class TaskMgr * const this /* r28 */) {
    // Local variables
    class AutoTimer _at; // r1+0x50
    class AutoTimer _at; // r1+0x4C
    float secs; // f1
    int i; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q212TaskTimeline8TaskInfo>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

// Range: 0x805F967C -> 0x805F9798
void TaskMgr::ClearTasks(class TaskMgr * const this /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__4Task;
    // -> struct [anonymous] __RTTI__10ScriptTask;
}

// Range: 0x805F9798 -> 0x805F9A14
void TaskMgr::Start() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q212TaskTimeline8TaskInfo>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__24ObjPtr<4Task,9ObjectDir>;
}

// Range: 0x805F9A14 -> 0x805F9A30
char * TaskMgr::GetMBT(class TaskMgr * const this /* r6 */) {}

// Range: 0x805F9A30 -> 0x805F9B80
void TaskMgr::ResetTaskTime() {}

static class Symbol _s; // size: 0x4, address: 0x80A552C0
static class Symbol _s; // size: 0x4, address: 0x80A552C8
static class Symbol _s; // size: 0x4, address: 0x80A552D0
static class Symbol _s; // size: 0x4, address: 0x80A552D8
static class Symbol _s; // size: 0x4, address: 0x80A552E0
static class Symbol _s; // size: 0x4, address: 0x80A552E8
static class Symbol _s; // size: 0x4, address: 0x80A552F0
static class Symbol _s; // size: 0x4, address: 0x80A552F8
static class Symbol _s; // size: 0x4, address: 0x80A55300
static class Symbol _s; // size: 0x4, address: 0x80A55308
static class Symbol _s; // size: 0x4, address: 0x80A55310
static class Symbol _s; // size: 0x4, address: 0x80A55318
static class Symbol _s; // size: 0x4, address: 0x80A55320
static class Symbol _s; // size: 0x4, address: 0x80A55328
// Range: 0x805F9B80 -> 0x805FA9F4
class DataNode TaskMgr::Handle(class TaskMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x54
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x805FA9F4 -> 0x805FAAEC
class DataNode TaskMgr::OnTimeTilNext(class TaskMgr * const this /* r30 */, class DataArray * args /* r31 */) {
    // Local variables
    float fraction; // f0
    float slop; // f0
    float bf; // f29
    float til; // f1
}

struct {
    // total size: 0x54
} __vt__7TaskMgr; // size: 0x54, address: 0x8092A3D0
struct {
    // total size: 0x8
} __RTTI__7TaskMgr; // size: 0x8, address: 0x8092A448
struct {
    // total size: 0x58
} __vt__10ThreadTask; // size: 0x58, address: 0x8092A450
struct {
    // total size: 0x8
} __RTTI__10ThreadTask; // size: 0x8, address: 0x8092A4D8
struct {
    // total size: 0x58
} __vt__10ScriptTask; // size: 0x58, address: 0x8092A4E0
struct {
    // total size: 0x8
} __RTTI__10ScriptTask; // size: 0x8, address: 0x8092A560
struct {
    // total size: 0x58
} __vt__11MessageTask; // size: 0x58, address: 0x8092A568
struct {
    // total size: 0x8
} __RTTI__11MessageTask; // size: 0x8, address: 0x8092A5E8
// Range: 0x805FAAEC -> 0x805FAB64
static void __sinit_\Task_cpp() {
    // References
    // -> struct [anonymous] __vt__7TaskMgr;
    // -> class TaskMgr TheTaskMgr;
}


