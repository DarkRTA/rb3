#ifndef UTL_BUFSTREAMNAND_H
#define UTL_BUFSTREAMNAND_H
#include "fixedsizesaveablestream.hpp"

class BufStreamNAND : public FixedSizeSaveableStream {
public:
    BufStreamNAND(void *, int, int, char *, bool);
    virtual ~BufStreamNAND(); // fn_803437A8
    virtual void Flush(); // fn_8076F540, returns void
    virtual int Tell(); // fn_800BE7A8
    virtual bool Eof(); // fn_80344220
    virtual bool Fail(); // fn_802A27D4
    virtual const char *Name() const; // fn_803436BC

    virtual void ReadImpl(void *, int); // fn_80343B98
    virtual void WriteImpl(const void *, int); // fn_80343C9C
    virtual void SeekImpl(
        int,
        BinStream::SeekType
    ); // fn_80343D90 - the second int should actually be of type SeekType

    virtual void Unk11(); // fn_80343FD0
    virtual void Unk12(); // fn_803440EC
};

#endif

// class BufStreamNAND : public BinStream {
//     // total size: 0x100
//     char * mBuffer; // offset 0xC, size 0x4
//     unsigned char mFail; // offset 0x10, size 0x1
//     int mTell; // offset 0x14, size 0x4
//     int mSize; // offset 0x18, size 0x4
//     int mRunningTell; // offset 0x1C, size 0x4
//     int mChunkSize; // offset 0x20, size 0x4
//     unsigned char mTellReset; // offset 0x24, size 0x1
//     unsigned char mFileOpen; // offset 0x25, size 0x1
//     char mFilePath[64]; // offset 0x26, size 0x40
//     enum MCResult mResult; // offset 0x68, size 0x4
//     struct NANDFileInfo mFileInfo; // offset 0x6C, size 0x8C
//     class StreamChecksum * mChecksum; // offset 0xF8, size 0x4
//     int mBytesChecksummed; // offset 0xFC, size 0x4
// };
