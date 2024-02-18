#ifndef UTL_BINSTREAM_H
#define UTL_BINSTREAM_H
#include "math/Rand2.h"
#include "utl/Str.h"
#include "utl/Symbol.h"

class BinStream {
public:
    enum SeekType {
        kSeekBegin = 0,
        kSeekCur = 1,
        kSeekEnd = 2,
    };

    BinStream(bool);
    virtual ~BinStream();
    virtual void Flush() = 0;
    virtual int Tell() = 0;
    virtual bool Eof() = 0;
    virtual bool Fail() = 0;
    virtual const char* Name() const;
    virtual int Cached(); // weak
    virtual int GetPlatform(); // weak
    virtual void ReadImpl(void*, int) = 0;
    virtual void WriteImpl(const void*, int) = 0;
    virtual void SeekImpl(int, SeekType) = 0;

    bool mLittleEndian;
    Rand2* mCrypto;
};

#endif
