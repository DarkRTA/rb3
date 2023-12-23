#ifndef RB3_MEMSTREAM_HPP
#define RB3_MEMSTREAM_HPP
#include "binstream.hpp"
#include "string.hpp"
#include "file.hpp"
#include "streamchecksum.hpp"

class MemStream : BinStream {
public:
    MemStream(bool); // fn_80354E6C
    virtual ~MemStream(); // fn_800A9EDC
    virtual void Flush(); // fn_8076F540 - returns void
    virtual int Tell(); // fn_800BB518
    virtual bool Eof(); // fn_802CCBB8
    virtual bool Fail(); // fn_800A7DE8

    virtual int V_Unk6(); // fn_8077BAA0 - returns 0
    virtual int V_Unk7(); // fn_8077BAA0 - returns 0
    virtual void ReadImpl(void *, int); // fn_80354F78
    virtual void WriteImpl(const void *, int); // fn_80355004
    virtual void SeekImpl(int, SeekType); // fn_803550B0

    bool failed;
    int pos;
    void *unk14;

    void Compact();
};

#endif
