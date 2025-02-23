#pragma once

#include "synth/Faders.h"
#include "synth/Sfx.h"

class Metronome {
public:
    enum OverrideEnabled {
    };
    Metronome();
    virtual ~Metronome();

    void Enter(Sfx *, Sfx *);
    void Exit();
    void Poll(int, OverrideEnabled);
    void PlayBeat(int);
    bool Enabled() const;
    void Enable(bool);
    int GetVolume(int) const;
    void SetVolume(int, int);

    int mBeat; // 0x4
    bool mEnabled; // 0x8
    Sfx *mHiSfx; // 0xc
    Sfx *mLoSfx; // 0x10
    Fader *mFader; // 0x14
    int unk; // 0x18
};
