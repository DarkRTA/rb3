#pragma once
#include "os/AsyncTask.h"
#include "os/Timer.h"
#include "utl/PoolAlloc.h"
#include <vector>
#include <list>

class Block {
public:
    Block();
    void UpdateTimestamp();

    const char* mBuffer; // 0x0
    int mArkfileNum; // 0x4
    int mBlockNum; // 0x8
    int mTimestamp; // 0xc
    bool mWritten; // 0x10
    const char* mDebugName; // 0x14

    bool CheckMetadata(int arknum, int blocknum) const {
        return mArkfileNum == arknum && mBlockNum == blocknum;
    }

    static int sCurrTimestamp;

    NEW_POOL_OVERLOAD(Block);
    DELETE_POOL_OVERLOAD(Block);
};

class BlockRequest {
public:
    BlockRequest(const AsyncTask&);

    int mArkfileNum; // 0x0
    int mBlockNum; // 0x4
    const char* mStr; // 0x8
    std::list<AsyncTask> mTasks; // 0xc
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
