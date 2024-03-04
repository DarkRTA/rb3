#ifndef UTL_BUFSTREAM_H
#define UTL_BUFSTREAM_H
#include "utl/BinStream.h"
#include "math/StreamChecksum.h"

class BufStream : public BinStream {
public:
    BufStream(void*, int, bool);
    virtual ~BufStream();

    // weak
    virtual void Flush(){}
    virtual int Tell(){ return mTell; } 
    virtual bool Eof(){ return mSize - mTell == 0; }
    virtual bool Fail(){ return mFail; }

    virtual const char *Name() const;
    virtual void ReadImpl(void *, int);
    virtual void WriteImpl(const void *, int);
    virtual void SeekImpl(int, SeekType);

    void DeleteChecksum();
    void StartChecksum(const char*);
    bool ValidateChecksum();
    void SetName(const char*);

    char* mBuffer;
    bool mFail;
    int mTell;
    int mSize;
    StreamChecksumValidator* mChecksum;
    int mBytesChecksummed;
    String mName;
};

#endif
