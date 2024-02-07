/*
    Compile unit: C:\rockband2\system\src\net\JobMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805224B0 -> 0x80522944
*/
static int gJobIDCounter; // size: 0x4, address: 0x80A53C68
// Range: 0x805224B0 -> 0x805224D0
void * Job::Job() {
    // References
    // -> static int gJobIDCounter;
    // -> struct [anonymous] __vt__3Job;
}

// Range: 0x805224D0 -> 0x80522504
void * JobMgr::JobMgr() {}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Job * _M_data; // offset 0x8, size 0x4
};
// Range: 0x80522504 -> 0x80522568
void * JobMgr::~JobMgr(class JobMgr * const this /* r30 */) {}

// Range: 0x80522568 -> 0x80522670
void JobMgr::Poll(class JobMgr * const this /* r29 */) {
    // Local variables
    class Job * finishedJob; // r30
}

// Range: 0x80522670 -> 0x80522768
void JobMgr::QueueJob(class JobMgr * const this /* r30 */, class Job * job /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<P3Job>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std17_List_node<P3Job>; // size: 0x8, address: 0x80904D28
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80522768 -> 0x805227C8
unsigned char JobMgr::HasJob() {
    // Local variables
    struct _List_iterator it; // r1+0x14
}

// Range: 0x805227C8 -> 0x80522944
void JobMgr::CancelAllJobs(class JobMgr * const this /* r31 */) {
    // Local variables
    class list toBeCancelled; // r1+0x50
    struct _List_iterator it; // r1+0x3C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<P3Job>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x1C
} __vt__3Job; // size: 0x1C, address: 0x80904D50

