#ifndef OS_ASYNCFILE_H
#define OS_ASYNCFILE_H
#include "os/File.h"

class AsyncFile : public File {
public:
    AsyncFile(const char *, int);
    virtual ~AsyncFile();
    virtual String Filename();
    virtual int Read(void *, int);
    virtual bool ReadAsync(void *, int);
    virtual bool Write(const void *, int);
    virtual int Seek(int, int);
    virtual int Tell();
    virtual void Flush(){}
    virtual bool Eof();
    virtual bool Fail();
    virtual int Size();
    virtual int UncompressedSize();
    virtual bool ReadDone(int &);
    virtual bool WriteDone(int &);
    virtual void GetFileHandle(DVDFileInfo*&) = 0;

    virtual void _OpenAsync() = 0;
    virtual bool _OpenDone() = 0;
    virtual void _WriteAsync(const void*, int) = 0;
    virtual bool _WriteDone() = 0;
    virtual void _SeekToTell() = 0;
    virtual void _ReadAsync(void*, int) = 0;
    virtual bool _ReadDone() = 0;
    virtual void _Close() = 0;

    void FillBuffer();
    void Terminate();

    AsyncFile *New(const char *, int);
    void Init();

    int unk4;
    bool mFail;
    char unk9;
    String mFilename;
    unsigned int mTell;
    int mOffset;
    unsigned int mSize;
    unsigned int mUCSize;
    char *mBuffer;
    char *mData;
    int mBytesLeft;
    int mBytesRead;
};

#endif
