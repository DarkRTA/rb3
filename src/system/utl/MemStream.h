#ifndef UTL_MEMSTREAM_H
#define UTL_MEMSTREAM_H

#include "utl/BinStream.h"
#include <vector>

class MemStream : public BinStream {
public:
    MemStream(bool);
    virtual ~MemStream();
    virtual void ReadImpl(void*, int);
    virtual void WriteImpl(const void*, int);
    void WriteStream(BinStream&, int);
    virtual void SeekImpl(int, SeekType);
    void Compact();
    virtual bool Fail();
    virtual void Flush();

    bool mFail;
    int a;
    std::vector<char> mem;
    int b;
    int c;

};

#endif // UTL_MEMSTREAM_H
