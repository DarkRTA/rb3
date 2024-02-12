#ifndef OS_ASYNCTASK_H
#define OS_ASYNCTASK_H
#include "os/ArkFile.h"

class AsyncTask {
public:
    int mArkfileNum;
    int mBlockNum;
    int mOffsetStart;
    int mOffsetEnd;
    void *mBuffer;
    char *unk14;
    ArkFile *mOwner;

    AsyncTask(ArkFile *, void *, int, int, int, int, const char *);
    bool FillData();
};

#endif
