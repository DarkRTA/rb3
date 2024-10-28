#ifndef OS_BLOCKMGR_H
#define OS_BLOCKMGR_H
#include "os/AsyncTask.h"
#include "os/Timer.h"
#include "utl/PoolAlloc.h"
#include <vector>
#include <list>

class Block {
public:
    Block();
    void UpdateTimestamp();

    const char* mBuffer;
    int mArkfileNum;
    int mBlockNum;
    int mTimestamp;
    bool mWritten;
    const char* mDebugName;
    static int sCurrTimestamp;

    void* operator new(size_t siz) {
        return _PoolAlloc(siz, siz, FastPool);
    }
};

class BlockRequest {
public:
    int mArkfileNum;
    int mBlockNum;
    std::list<AsyncTask> mTasks;
};

class BlockMgr {
public:
    BlockMgr(){}
    ~BlockMgr(){}
    Block* FindBlock(int, int);
    const char* GetBlockData(int, int);
    void KillBlockRequests(ArkFile*);
    void WriteBlock();
    void ReadBlock();
    void Poll();
    void GetAssociatedBlocks(unsigned long long, int, int&, int&, int&);
    void AddTask(const AsyncTask&);
    bool SpinUp();
    Block* FindLRUBlock(bool); // Least Recently Updated
    Block* FindMRUBlock(); // Most Recently Updated
    void Init();
    void MarkDiscRead();


    std::list<BlockRequest> mRequests; // 0x0
    std::vector<Block*> mBlockCache; // 0x8
    Block* mReadingBlock; // 0x10
    Block* mWritingBlock; // 0x14
    Timer mSpinDownTimer; // 0x18
};

extern BlockMgr TheBlockMgr;

#endif