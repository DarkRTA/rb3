/*
    Compile unit: C:\rockband2\system\src\rndobj\PostProcBlendTask.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804E729C -> 0x804E7F08
*/
class PostProcBlendTask : public Task {
    // total size: 0x5C
    class ObjOwnerPtr mObj; // offset 0x28, size 0xC
    float mPeriod; // offset 0x34, size 0x4
    class ObjPtr mTarget; // offset 0x38, size 0xC
    class ObjPtr mSource; // offset 0x44, size 0xC
    class ObjPtr mBlendTo; // offset 0x50, size 0xC
};
// Range: 0x804E729C -> 0x804E758C
void * PostProcBlendTask::PostProcBlendTask(class PostProcBlendTask * const this /* r29 */, class RndPostProc * target /* r30 */, class RndPostProc * blendto /* r31 */, float period /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPostProc;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPostProc,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__17PostProcBlendTask;
}

// Range: 0x804E758C -> 0x804E76B8
void * PostProcBlendTask::~PostProcBlendTask(class PostProcBlendTask * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11RndPostProc,9ObjectDir>;
    // -> struct [anonymous] __vt__17PostProcBlendTask;
}

// Range: 0x804E76B8 -> 0x804E76DC
void PostProcBlendTask::Replace() {}

// Range: 0x804E76DC -> 0x804E7814
static class DataNode OnPPBlendTask(class DataArray * data /* r27 */) {
    // Local variables
    enum TaskUnits u; // r28
    float bt; // f31
    float d; // f30

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPostProc;
}

// Range: 0x804E7814 -> 0x804E7F08
void PostProcBlendTask::Poll(class PostProcBlendTask * const this /* r31 */) {
    // Local variables
    float blend; // f31
    class Color c; // r1+0x30
    float f; // f0
    class Vector2 v2; // r1+0x10
    class Vector3 v3; // r1+0x20
}

struct {
    // total size: 0x58
} __vt__17PostProcBlendTask; // size: 0x58, address: 0x808FE3F0
struct {
    // total size: 0x8
} __RTTI__17PostProcBlendTask; // size: 0x8, address: 0x808FE478
struct {
    // total size: 0x18
} __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>; // size: 0x18, address: 0x808FE480
struct {
    // total size: 0x8
} __RTTI__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>; // size: 0x8, address: 0x808FE4C8

