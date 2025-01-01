#pragma once

class ArkFile;

class AsyncTask {
public:
    int mArkfileNum; // 0x0
    int mBlockNum; // 0x4
    int mOffsetStart; // 0x8
    int mOffsetEnd; // 0xc
    void* mBuffer; // 0x10
    const char* mStr; // 0x14
    ArkFile* mOwner; // 0x18

    AsyncTask(ArkFile*, void*, int, int, int, int, const char*);
    AsyncTask(int, int);
    bool FillData();
    int GetBlockNum() const { return mBlockNum; }
    const char* GetStr() const { return mStr; }
};
