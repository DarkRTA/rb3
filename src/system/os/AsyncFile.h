#ifndef OS_ASYNCFILE_H
#define OS_ASYNCFILE_H
#include "os/File.h"

#define FILE_OPEN_READ 2

class AsyncFile : public File {
public:
    AsyncFile(const char *, int);
    virtual ~AsyncFile(){}
    virtual String Filename(){ return String(mFilename); }
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
    virtual bool WriteDone(int &);
    virtual int GetFileHandle(DVDFileInfo*&) = 0;

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

    static AsyncFile* New(const char *, int);
    void Init();

    int mMode;
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

// static int gBufferSize; // size: 0x4, address: 0x80A477A0
// class AsyncFile : public File {
//     // total size: 0x3C
// protected:
//     int mHandle; // offset 0x4, size 0x4
//     int mMode; // offset 0x8, size 0x4
//     unsigned char mFail; // offset 0xC, size 0x1
//     class String mFilename; // offset 0x10, size 0xC
//     unsigned int mTell; // offset 0x1C, size 0x4
//     int mOffset; // offset 0x20, size 0x4
// private:
//     unsigned int mSize; // offset 0x24, size 0x4
//     int mUCSize; // offset 0x28, size 0x4
//     char * mBuffer; // offset 0x2C, size 0x4
//     char * mData; // offset 0x30, size 0x4
//     int mBytesLeft; // offset 0x34, size 0x4
//     int mBytesRead; // offset 0x38, size 0x4
// };