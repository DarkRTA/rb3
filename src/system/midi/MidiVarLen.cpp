#include "MidiVarLen.h"
#include "os/Debug.h"

#include "decomp.h"

DECOMP_FORCEACTIVE(MidiVarLen,
    __FILE__,
    "mValue<0x0fffffff",
    "len < 5"
)

MidiVarLenNumber::MidiVarLenNumber(BinStream& b) {
    Read(b);
}

BinStream& MidiVarLenNumber::Read(BinStream& b) {
    mValue = 0;
    unsigned char bVar3;
    do {
        bVar3 = 0;
        b >> bVar3;
        unsigned int value = mValue * 0x80;
        mValue = value + (bVar3 & 0x7f);
        MILO_ASSERT(mValue < 0x0fffffff, 64);
    } while (bVar3 & 0x80);
    return b;
}
