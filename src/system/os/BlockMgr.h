#ifndef OS_BLOCKMGR_H
#define OS_BLOCKMGR_H
#include "os/AsyncTask.h"
#include "os/Timer.h"
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
    static int sCurrTimeStamp;
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
    const char* GetBlockData(int, int);
    void KillBlockRequests(ArkFile*);
    void Poll();
    void GetAssociatedBlocks(unsigned long long, int, int&, int&, int&);
    void AddTask(const AsyncTask&);
    bool SpinUp();

    std::list<BlockRequest> mRequests;
    std::vector<Block*> mBlockCache;
    Block* mReadingBlock;
    Block* mWritingBlock;
    Timer mSpinDownTimer;
};

extern BlockMgr TheBlockMgr;

#endif