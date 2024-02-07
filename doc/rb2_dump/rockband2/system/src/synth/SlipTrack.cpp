/*
    Compile unit: C:\rockband2\system\src\synth\SlipTrack.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8058D224 -> 0x8058D5C0
*/
// Range: 0x8058D224 -> 0x8058D2C4
void * SlipTrack::SlipTrack(class SlipTrack * const this /* r30 */, class Stream * s /* r31 */, int channel /* r1+0x8 */) {}

// Range: 0x8058D2C4 -> 0x8058D340
void SlipTrack::PlayChunk(class SlipTrack * const this /* r31 */, float startMs /* f30 */, float endMs /* f31 */) {}

// Range: 0x8058D340 -> 0x8058D38C
void SlipTrack::ForceOn(class SlipTrack * const this /* r31 */) {}

// Range: 0x8058D38C -> 0x8058D3F4
void SlipTrack::Poll(class SlipTrack * const this /* r31 */) {}

// Range: 0x8058D3F4 -> 0x8058D458
void SlipTrack::VolumeOn(class SlipTrack * const this /* r31 */, float startMs /* f31 */) {
    // Local variables
    float offset; // f1
}

// Range: 0x8058D458 -> 0x8058D4C0
void SlipTrack::VolumeOff(class SlipTrack * const this /* r30 */) {
    // Local variables
    int * itr; // r31
}

// Range: 0x8058D4C0 -> 0x8058D530
void SlipTrack::SetSpeed(class SlipTrack * const this /* r30 */, float spd /* f31 */) {
    // Local variables
    int * itr; // r31
}

// Range: 0x8058D530 -> 0x8058D5A0
void SlipTrack::SetOffset(class SlipTrack * const this /* r30 */, float ms /* f31 */) {
    // Local variables
    int * itr; // r31
}

// Range: 0x8058D5A0 -> 0x8058D5C0
float SlipTrack::GetCurrentOffset(class SlipTrack * const this /* r4 */) {}


