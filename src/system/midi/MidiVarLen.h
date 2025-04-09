#pragma once
#include "utl/BinStream.h"

class MidiVarLenNumber {
public:
    int mValue;

    MidiVarLenNumber(BinStream &);
    BinStream &Read(BinStream &);
};
