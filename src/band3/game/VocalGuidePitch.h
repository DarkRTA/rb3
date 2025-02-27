#pragma once
#include "obj/Dir.h"
#include "synth/MidiInstrument.h"

class VocalGuidePitch {
public:
    VocalGuidePitch();
    virtual ~VocalGuidePitch();

    void Load();
    bool IsLoaded() const;
    void FinishLoad();
    void Unload();
    void Poll(float);
    void EnableGuideTrack(int);
    void Init();
    void Terminate();
    void SetSong(const Symbol &);
    void UpdateTuning(float);
    int GetGuideTrack() const;
    void SetVolume(float);
    void Pause(bool);
    bool IsPaused() const;

    int mGuideTrack; // 0x4
    int unk8; // 0x8 - VocalNote* mCurrNote?
    int mGuidePitch; // 0xc
    MidiInstrument *mInstrument; // 0x10
    ObjDirPtr<ObjectDir> mBank; // 0x14
    float mTuningOffset; // 0x20
    bool mPaused; // 0x24
    int mPitchModifier; // 0x28
};