#ifndef RB3_FIXEDSIZESAVEABLESTREAM_HPP
#define RB3_FIXEDSIZESAVEABLESTREAM_HPP
#include "BufStream.h"

class FixedSizeSaveableStream : public BufStream {
public:
    FixedSizeSaveableStream(void *, int, bool); // fn_8050FA30, vtable lbl_8088BE40
    virtual ~FixedSizeSaveableStream(); // fn_8050FA88

    virtual void Unk11(); // links to fn_8077BAA0, which returns 0
    virtual void unk12(); // links to fn_8077BAA0, which returns 0
};

#endif
