/*
    Compile unit: C:\rockband2\system\src\char\CharTaskMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803911D4 -> 0x8039122C
*/
unsigned char sShowGraph; // size: 0x1, address: 0x80A513D8
// Range: 0x803911D4 -> 0x803911F4
static class DataNode OnToggleCharTaskGraph() {
    // References
    // -> unsigned char sShowGraph;
}

class CharTaskMgr {
    // total size: 0x14
public:
    int mInstanceNum; // offset 0x0, size 0x4
protected:
    class vector mTasks; // offset 0x4, size 0xC
    class Task * mConflict; // offset 0x10, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Task * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Task * * _M_start; // offset 0x0, size 0x4
    class Task * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x803911F4 -> 0x8039122C
void CharTaskMgr::Init() {}

class Task {
    // total size: 0x18
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    float mStart; // offset 0x4, size 0x4
    float mEnd; // offset 0x8, size 0x4
    float mPriority; // offset 0xC, size 0x4
    int mConflictFlags; // offset 0x10, size 0x4
    unsigned char mStarted; // offset 0x14, size 0x1
};

