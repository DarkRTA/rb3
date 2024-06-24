#pragma once

#include "synth/Faders.h"
#include "synth/Sfx.h"

class Metronome {
    enum OverrideEnabled {

    };
    Metronome();
    virtual ~Metronome();
    void Enter(Sfx*, Sfx*);
    void Exit();
    void Poll(int, OverrideEnabled);
    void PlayBeat(int);
    bool Enabled() const;
    void Enable(bool);
    int GetVolume(int) const;
    void SetVolume(int, int);

    int mBeat;
    bool mEnabled; // 0x8
    Sfx* mHiSfx;
    Sfx* mLoSfx;
    Fader* mFader;
};
