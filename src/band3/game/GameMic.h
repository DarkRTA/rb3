#pragma once
#include "dsp/PitchDetector.h"
#include "obj/Msg.h"
#include "synth/Mic.h"
#include "utl/MemStream.h"

class GameMic {
public:
    GameMic(int);
    ~GameMic();

    void SetInputFile(const char *);
    void SetEnablePitchDetection(bool);
    void AccessContinuousSamples(const short *&, int &) const;
    void ThreadProcessOneFrame();
    void Update();
    int GetDataSampleRate();
    Mic *GetMyMic();

    int mMicID; // 0x0
    int mFonixIdx; // 0x4
    bool unk8;
    bool unk9;
    bool mWriteWav; // 0xa
    int unkc;
    MemStream *mStoredAudio; // 0x10
    PitchDetector *mDetector; // 0x14
    Mic *mNullMic; // 0x18
    float unk1c;
    float unk20;
    float unk24;
    float unk28;
    float unk2c;
    short mSamplesRecent[8192]; // 0x30
    short mSamplesContinuous[8192]; // 0x4030
    int unk8030;
    int unk8034;
    bool unk8038;
};

DECLARE_MESSAGE(GameMicsChangedMsg, "game_mics_changed");
GameMicsChangedMsg() : Message(Type()) {}
END_MESSAGE