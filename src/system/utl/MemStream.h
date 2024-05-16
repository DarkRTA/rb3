#ifndef UTL_MEMSTREAM_H
#define UTL_MEMSTREAM_H

#include "utl/BinStream.h"
#include <vector>

class MemStream : public BinStream {
public:
    MemStream(bool);
    virtual ~MemStream(){}
    virtual void Flush();
    virtual int Tell();
    virtual EofType Eof();
    virtual bool Fail();
    virtual void ReadImpl(void*, int);
    virtual void WriteImpl(const void*, int);
    virtual void SeekImpl(int, SeekType);

    void WriteStream(BinStream&, int);
    void Compact();


    bool mFail;
    int mTell;
    std::vector<char, unsigned int> mBuffer;

};

#endif // UTL_MEMSTREAM_H
