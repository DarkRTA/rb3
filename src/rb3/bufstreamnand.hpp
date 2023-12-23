#ifndef RB3_BUFSTREAMNAND_HPP
#define RB3_BUFSTREAMNAND_HPP
#include "fixedsizesaveablestream.hpp"

class BufStreamNAND : FixedSizeSaveableStream {
public:
    BufStreamNAND(void *, int, int, char *, bool);
    virtual ~BufStreamNAND(); // fn_803437A8
    virtual void Flush(); // fn_8076F540, returns void
    virtual int Tell(); // fn_800BE7A8
    virtual bool Eof(); // fn_80344220
    virtual bool Fail(); // fn_802A27D4
    virtual const char *Name() const; // fn_803436BC

    virtual void ReadImpl(void *, int); // fn_80343B98
    virtual void WriteImpl(const void *, int); // fn_80343C9C
    virtual void SeekImpl(
        int,
        BinStream::SeekType
    ); // fn_80343D90 - the second int should actually be of type SeekType

    virtual void Unk11(); // fn_80343FD0
    virtual void Unk12(); // fn_803440EC
};

#endif
