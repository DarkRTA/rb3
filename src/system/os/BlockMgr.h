#ifndef OS_BLOCKMGR_H
#define OS_BLOCKMGR_H

class Block {
public:
    const char* mBuffer;
    int mArkfileNum;
    int mBlockNum;
    int mTimestamp;
};

class BlockMgr {
public:
    int dummy;
    const char* GetBlockData(int, int);
};

#endif
