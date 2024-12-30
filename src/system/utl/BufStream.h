#pragma once
#include "utl/BinStream.h"
#include "math/StreamChecksum.h"

class BufStream : public BinStream {
public:
    BufStream(void* buffer, int size, bool littleEndian);
    virtual ~BufStream();
    virtual void Flush(){}
    virtual int Tell(){ return mTell; } 
    virtual EofType Eof(){ return (EofType)(mSize - mTell == 0); }
    virtual bool Fail(){ return mFail; }
    virtual const char *Name() const;
    virtual void ReadImpl(void *, int);
    virtual void WriteImpl(const void *, int);
    virtual void SeekImpl(int, SeekType);

    void DeleteChecksum();
    void StartChecksum(const char*);
    bool ValidateChecksum();
    void SetName(const char*);

    char* mBuffer; // 0xc
    bool mFail; // 0x10
    int mTell; // 0x14
    int mSize; // 0x18
    StreamChecksumValidator* mChecksum; // 0x1c
    int mBytesChecksummed; // 0x20
    class String mName; // 0x24
};
