#pragma once 

#include "math/StreamChecksum.h"
#include "meta/FixedSizeSaveableStream.h"
#include "os/Memcard.h"
#include "revolution/nand/nand.h"
#include "stdint.h"
#include "utl/BinStream.h"

class BufStreamNAND : public FixedSizeSaveableStream {
public:
    BufStreamNAND(void*, int, char*, bool);
    ~BufStreamNAND();
    int Tell();
    void SetResult(MCResult);
    int GetResult();
    bool Fail();
    EofType Eof();
    void ReadImpl(void*, int);
    int LoadBufferFromNAND();
    void Clear();
    int Open();
    MCResult HandleResultNAND(s32);
    bool FinishStream();
    int Close();
    void DeleteChecksum();
    int Pad(int);
    int PadToEnd();
    int SaveBufferToNAND(bool);
    int DoSeek(int, BinStream::SeekType);
    bool FinishWrite();

    char *mBuffer; // 0x68
    int mTell; // 0x70
    int mSize; // 0x74
    int mRunningTell; // 0x78
    MCResult mResult; // 0xC4
    NANDFileInfo *mFileInfo; // 0xC8
    bool mFail; // 0x6C
    int mChunkSize; // 0x7C
    StreamChecksum *mChecksum; // 0x154
    int mBytesChecksummed; // 0x158
    bool unk80; // 0x80;
    bool mFileOpen; // 0x81
    char mFilePath[64]; // 0x82
};