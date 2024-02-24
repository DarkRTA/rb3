#ifndef OS_ASYNCTASK_H
#define OS_ASYNCTASK_H

class ArkFile;

class AsyncTask {
public:
    int mArkfileNum;
    int mBlockNum;
    int mOffsetStart;
    int mOffsetEnd;
    void* mBuffer;
    const char* mStr;
    ArkFile* mOwner;

    AsyncTask(ArkFile*, void*, int, int, int, int, const char*);
    AsyncTask(int, int);
    bool FillData();
};

#endif
