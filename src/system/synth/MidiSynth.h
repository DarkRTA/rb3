#pragma once
#include "synth/MidiChannel.h"

class MidiSynth {
public:
    MidiSynth();

    std::vector<MidiChannel> mChannels; // 0x0
};