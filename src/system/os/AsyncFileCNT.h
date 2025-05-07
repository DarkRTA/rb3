#pragma once

#include "os/AsyncFile.h"
#include "revolution/dvd/dvdfs.h"
#include "utl/MemMgr.h"
#include "sdk/RVL_SDK/revolution/cnt/cnt.h"

class AsyncFileCNT : public AsyncFile {
public:
    AsyncFileCNT(const char *, int);
    ~AsyncFileCNT();
    virtual int GetFileHandle(DVDFileInfo *&);
    virtual void _OpenAsync();
    virtual bool _OpenDone();
    virtual void _WriteAsync(const void *, int);
    virtual bool _WriteDone();
    virtual void _SeekToTell();
    virtual void _ReadAsync(void *, int);
    virtual bool _ReadDone();
    virtual void _Close();

    void *mTempBufferCNT; // 0x38
    int mReadSizeCNT; // 0x3c
    int mReadResultCNT; // 0x40
    int mOpenHandles; // 0x44 - name is a guess
    bool mReadInProgress; // 0x48
    bool mIsDLC; // 0x49
    char mContentName[0x10]; // 0x4a - name is a guess

    u8 mCNTThreadReadStack[0x2000] __attribute__((aligned(32)));
    u8 _padding1[0x80];
    OSThread mCNTReadThread;
    CNTFileInfo mCNTFileInfo;

    DELETE_OVERLOAD
};