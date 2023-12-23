#ifndef RB3_IDATACHUNK_HPP
#define RB3_IDATACHUNK_HPP
#include "binstream.hpp"

class IDataChunk : BinStream {
public:
    IDataChunk(bool); // fn_80349E80
    virtual ~IDataChunk(); // fn_8034A03C
    virtual void Flush(); // links to fn_80765F40, which returns void
    virtual int Tell(); // fn_8034A1C0
    virtual bool Eof(); // fn_8034A7CC
    virtual bool Fail(); // fn_8016829C

    virtual void ReadImpl(void *, int); // fn_8034A224
    virtual void WriteImpl(const void *, int); // links to fn_80765F40, which returns void
    virtual void SeekImpl(int, SeekType); // fn_8034A0C0

    // IListChunk* unkc;
};

#endif
