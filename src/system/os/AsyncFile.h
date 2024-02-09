#ifndef OS_ASYNCFILE_H
#define OS_ASYNCFILE_H
#include "file.hpp"
#include "Str.h"

class AsyncFile : public File {
public:
    AsyncFile(const char *, int);
    virtual ~AsyncFile();
    virtual String Filename();
    virtual int Read(void *, int); // fn_802E7E8C
    virtual bool ReadAsync(void *, int); // fn_802E7F7C
    virtual int V_Unk5(void *, int); // fn_802E7F00
    virtual bool Write(const void *, int); // fn_802E81D4
    virtual unsigned int Seek(int, int); // fn_802E8300
    virtual unsigned int Tell(); // fn_802E84AC
    virtual void Flush(); // fn_802E84B4
    virtual bool Eof(); // fn_802E85E0
    virtual bool Fail(); // fn_802E85F8
    virtual unsigned int Size(); // fn_802E8600
    virtual unsigned int UncompressedSize(); // fn_802E8608
    virtual int ReadDone(int &); // fn_802E8030
    virtual int V_Unk15(int *); // fn_802E81AC
    virtual int V_Unk16(int *) = 0;

    virtual void _Open() = 0;
    virtual int V_Unk19() = 0;
    virtual int _Write(const void *, int) = 0;
    virtual int V_Unk21() = 0;
    virtual void _SeekToTell() = 0;
    virtual void _ReadAsync(void *, int) = 0;
    virtual int _ReadDone() = 0;
    virtual void _Close() = 0;

    void FillBuffer(); // fn_802E8530
    void Terminate(); // fn_802E7E2C

    AsyncFile *New(const char *, int); // fn_802E7AA8
    void Init(); // fn_802E7BE4

    int unk4;
    bool failed;
    char unk9;
    String fname;
    unsigned int fpos;
    int unk1c;
    unsigned int size;
    unsigned int size_uncompressed;
    char *unk28;
    char *unk2c;
    int unk30;
    int unk34;
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
