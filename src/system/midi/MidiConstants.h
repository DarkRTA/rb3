#ifndef MIDI_MIDICONSTANTS_H
#define MIDI_MIDICONSTANTS_H
#include "os/Debug.h"

unsigned char MidiGetStatus(unsigned char uc){
    
}

inline bool MidiIsStatus(unsigned char status){
    return status & 0x80;
}

inline unsigned char MidiGetType(unsigned char status){
    MILO_ASSERT(MidiIsStatus(status), 0x2f);
    return status & 0xF0;
}

inline bool MidiIsSystem(unsigned char uc){
    return MidiGetType(uc) == 0xF0;
}

inline unsigned char MidiGetChannel(unsigned char status){
    MILO_ASSERT(MidiIsStatus(status), 0x40);
    MILO_ASSERT(!MidiIsSystem(status), 0x41);
    return status & 0xF;
}

#endif