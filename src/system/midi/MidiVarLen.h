#ifndef MIDI_MIDIVARLEN_H
#define MIDI_MIDIVARLEN_H

#include "utl/BinStream.h"

class MidiVarLenNumber {
    int mValue;

    MidiVarLenNumber(BinStream&);
    BinStream& Read(BinStream&);
};

#endif // MIDI_MIDIVARLEN_H
