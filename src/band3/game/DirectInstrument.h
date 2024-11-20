#pragma once
#include "obj/Dir.h"
#include "synth/Faders.h"
#include "synth/MidiInstrument.h"

class DirectInstrument {
    DirectInstrument();
    ~DirectInstrument();

    bool IsLoaded();
    void PostLoad();
    void Enable();
    void Disable();
    bool Enabled() const;
    void SetVolume(int);
    void NoteOn(int);
    void NoteOff(int);
    void PlayNote(int, int);

    int mVolume;
    ObjDirPtr<ObjectDir> mDir;
    MidiInstrument* mInstrument;
    Fader* mFader;
};
