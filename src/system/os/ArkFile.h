#ifndef OS_ARKFILE_H
#define OS_ARKFILE_H
#include "os/File.h"
#include <revolution/DVD.h>

class ArkFile : public File {
public:
    ArkFile(const char *, int);
    virtual ~ArkFile();
    virtual String Filename() const { return String(mFilename); }
    virtual int Read(void *, int);
    virtual bool ReadAsync(void *, int);
    virtual int Write(const void *, int);
    virtual int Seek(int, int);
    virtual int Tell();
    virtual void Flush(){}
    virtual bool Eof();
    virtual bool Fail();
    virtual int Size();
    virtual int UncompressedSize();
    virtual bool ReadDone(int &);
    virtual int GetFileHandle(DVDFileInfo*&);

    void TaskDone(int);

    void operator delete(void* v){
        _MemFree(v);
    }

    int mArkfileNum; // 0x4
    u64 mByteStart; // 0x8
    int mSize; // 0x10
    int mUCSize; // 0x14
    int mNumOutstandingTasks; // 0x18
    int mBytesRead; // 0x1C
    int mTell; // 0x20
    int mFail; // 0x24
    float mReadStartTime; // 0x28
    bool mReadAhead; // 0x2C
    String mFilename; // 0x30
};

#endif
