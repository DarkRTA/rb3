#ifndef UTL_MEMSTREAM_H
#define UTL_MEMSTREAM_H

#include "utl/BinStream.h"
#include "utl/VectorSizeDefs.h"
#include <vector>

class MemStream : public BinStream {
public:
    MemStream(bool = false);
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
    int BufferSize() const { return mBuffer.size(); }
    int Resize(int size){ mBuffer.resize(size); }
    const char* Buffer() const { return mBuffer.begin(); }

    bool mFail; // 0xc
    int mTell; // 0x10
    std::vector<char VECTOR_SIZE_LARGE> mBuffer; // 0x14

};

#endif // UTL_MEMSTREAM_H
