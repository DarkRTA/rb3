#ifndef UTL_BUFSTREAM_H
#define UTL_BUFSTREAM_H
#include "BinStream.h"
#include "Str.h"

class BufStream : public BinStream {
public:
    BufStream(void *, int, bool);
    virtual ~BufStream(); // fn_80343270
    virtual void Flush(); // fn_8076F540, returns void
    virtual int Tell(); // fn_800A9C70
    virtual bool Eof(); // fn_80343710
    virtual bool Fail(); // fn_800DB158
    virtual const char *Name() const; // fn_803436BC

    virtual void ReadImpl(void *, int); // fn_80343538
    virtual void WriteImpl(const void *, int); // fn_803435E4
    virtual void SeekImpl(int, SeekType); // fn_80343658

    // RB2 methods
    // Flush, Tell, Eof, Fail, Name, ReadImpl, WriteImpl, SeekImpl

    void DeleteChecksum();
    void SetName(const char *);

    void *unkc;
    bool unk10;
    int fpos;
    int size;
    int *unk1c; // should be class StreamChecksum
    int *unk20; // probably a class
    String name;
};

#endif

// class BufStream : public BinStream {
//     // total size: 0x24
//     char * mBuffer; // offset 0xC, size 0x4
//     unsigned char mFail; // offset 0x10, size 0x1
//     int mTell; // offset 0x14, size 0x4
//     int mSize; // offset 0x18, size 0x4
//     class StreamChecksum * mChecksum; // offset 0x1C, size 0x4
//     int mBytesChecksummed; // offset 0x20, size 0x4
// };
