#ifndef OS_BLOCKMGR_H
#define OS_BLOCKMGR_H

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
};

#endif
