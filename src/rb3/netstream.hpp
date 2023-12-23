#ifndef RB3_NETSTREAM_HPP
#define RB3_NETSTREAM_HPP
#include "binstream.hpp"
#include "types.h"
class NetStream : public BinStream {
public:
    NetStream(); // not in the vtable? odd
    virtual ~NetStream();
    virtual void Flush(); // links to fn_8076F540, which returns nothing
    virtual int Tell(); // links to fn_8077BAA0, which returns 0
    virtual bool Eof();
    virtual bool Fail();
    virtual void ReadImpl(void *, int);
    virtual void WriteImpl(const void *, int);
    virtual void SeekImpl(int, SeekType); // links to fn_8076F540, which returns nothing

    u8 undef1[4];
    u8 aaaa;
    u8 undef2[3];
    BinStream *binstream_maybe; // ????
    u8 undef3[16];
};
#endif