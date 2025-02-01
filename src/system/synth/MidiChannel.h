#pragma once
#include "utl/Symbol.h"
#include <list>
#include <vector>

class MidiChannel {
public:
    // got this from DC1
    class DummySample {
    public:
        int unk0;
    };

    class Note {
    public:
        // todo: figure out what this is, it's not in the bank5/6 symbols anywhere
        int unk0;
        float unk4;
        std::vector<DummySample *> unk8;
        std::vector<float> unk10;
    };

    MidiChannel();
    int mInst; // 0x0
    int mBank; // 0x4
    float mVolume; // 0x8
    float mPan; // 0xc
    float mTranspose; // 0x10
    std::list<Note> mPlayingNotes; // 0x14
};
