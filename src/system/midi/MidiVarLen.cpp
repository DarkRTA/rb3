#include "MidiVarLen.h"
#include "os/Debug.h"

MidiVarLenNumber::MidiVarLenNumber(BinStream& b) {
    Read(b);
}

BinStream& MidiVarLenNumber::Read(BinStream& b) {
    mValue = 0;
    unsigned char bVar3;
    do {
        bVar3 = 0;
        b >> bVar3;
        unsigned int test = mValue * 0x80 + (bVar3 & 0x7f);
        mValue = test;
        ASSERT(mValue < 0x0fffffff, 64);
    } while (bVar3 & 0x80);
    return b;
}
