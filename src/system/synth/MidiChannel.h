#ifndef SYNTH_MIDICHANNEL_H
#define SYNTH_MIDICHANNEL_H

#include <list>
#include "system/utl/Symbol.h"
#include <vector>

class MidiChannel {
public:

    class Note {
    public:
        // todo: figure out what this is, it's not in the bank5/6 symbols anywhere
    };

    MidiChannel();
    int mInst; // 0x0
    int mBank; // 0x4 
    float mVolume; // 0x8
    float mPan; // 0xc
    float mTranspose; // 0x10 
    std::list<Note> mPlayingNotes; // 0x14
};

#endif // SYNTH_MIDICHANNEL_H