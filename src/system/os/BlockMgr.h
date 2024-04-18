#ifndef OS_BLOCKMGR_H
#define OS_BLOCKMGR_H
#include "os/AsyncTask.h"

class Block {
public:
    Block();

    const char* mBuffer;
    int mArkfileNum;
    int mBlockNum;
    int mTimestamp;
    bool mWritten;
    const char* mDebugName;
    static int sCurrTimeStamp;
};

class BlockMgr {
public:
    int dummy;
    const char* GetBlockData(int, int);
    void KillBlockRequests(ArkFile*);
    void Poll();
    void GetAssociatedBlocks(unsigned long long, int, int&, int&, int&);
    void AddTask(const AsyncTask&);
};

extern BlockMgr TheBlockMgr;

#endif