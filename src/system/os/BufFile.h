#pragma once
#include "os/File.h"
#include "os/Debug.h"

class BufFile : public File {
public:
    BufFile(const void *buf, int size)
        : mBuf((unsigned char *)buf), mSize(size), mPos((unsigned char *)buf),
          mBytesRead(0) {
        MILO_ASSERT(buf, 0x20);
    }
    virtual ~BufFile();
    virtual class String Filename() const;
    virtual int Read(void *, int);
    virtual bool ReadAsync(void *, int);
    virtual int Write(const void *, int);
    virtual int Seek(int, int);
    virtual int Tell();
    virtual void Flush();
    virtual bool Eof();
    virtual bool Fail();
    virtual int Size();
    virtual int UncompressedSize();
    virtual bool ReadDone(int &);
    virtual int GetFileHandle(DVDFileInfo *&);

    unsigned char *mBuf; // 0x4
    int mSize; // 0x8
    unsigned char *mPos; // 0xc
    int mBytesRead; // 0x10
};