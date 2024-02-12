#ifndef UTL_BUFSTREAM_H
#define UTL_BUFSTREAM_H
#include "BinStream.h"
#include "Str.h"
#include "streamchecksum.hpp"

class BufStream : public BinStream {
public:
    BufStream(void *, int, bool);
    virtual ~BufStream(); // fn_80343270

    // weak
    virtual void Flush(){}
    virtual int Tell(){ return mTell; } // fn_800A9C70
    virtual bool Eof(); // fn_80343710
    virtual bool Fail(){ return mFail; } // fn_800DB158

    virtual const char *Name() const; // fn_803436BC
    virtual void ReadImpl(void *, int); // fn_80343538
    virtual void WriteImpl(const void *, int); // fn_803435E4
    virtual void SeekImpl(int, SeekType); // fn_80343658

    void DeleteChecksum();
    void SetName(const char *);

    void *mBuffer;
    bool mFail;
    int mTell;
    int mSize;
    StreamChecksum* mChecksum;
    int mBytesChecksummed;
    String mName;
};

#endif
