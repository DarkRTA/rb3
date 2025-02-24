#pragma once
#include "VocalScoreHistory.h"
#include "bandtrack/DelayLine.h"
#include "game/TambourineDetector.h"
#include "synth/MicManagerInterface.h"
#include "dsp/VibratoDetector.h"
#include "synth/VoiceBeat.h"
#include <vector>

class VocalPlayer;

class SingerResultsData {
public:
    SingerResultsData() { Reset(); }
    ~SingerResultsData() {}
    void Reset() {
        unk0 = 0;
        unk4 = 0;
        unk8 = 0;
        unkc = 0;
        unk10 = 0;
        unk18 = 0;
        unk14 = 0;
        unk1c = 0;
    }

    float unk0;
    float unk4;
    int unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
    int unk1c;
};

class Singer {
public:
    Singer(VocalPlayer *, int);
    ~Singer();

    void NoteTambourineSwing(float);
    void CreateMicClientID();
    void PostLoad();

    VocalPlayer *mPlayer; // 0x0
    MicClientID unk4;
    bool unkc;
    int unk10; // 0x10
    bool unk14;
    int unk18;
    int unk1c;
    int unk20;
    float unk24;
    float unk28;
    float unk2c;
    int unk30;
    int unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    float unk48;
    float unk4c;
    float unk50;
    int unk54;
    int unk58;
    float mFrameMicPitch; // 0x5c
    float unk60;
    float unk64;
    int unk68;
    float unk6c;
    int unk70;
    float unk74;
    int mOctaveOffset; // 0x78
    float unk7c;
    bool unk80;
    int unk84;
    float unk88;
    float mPitchHistory[5]; // 0x8c
    float unka0;
    int unka4;
    int unka8;
    DelayLine<int, 100> mPossibleVibratoPoints; // 0xac
    VibratoDetector *mVibrato; // 0x240
    float unk244;
    float unk248;
    float unk24c;
    int unk250;
    float unk254;
    float unk258;
    std::vector<VocalScoreHistory> mScoreHistories; // 0x25c
    std::vector<VocalScoreCache> mScoreCaches; // 0x264
    std::vector<SingerResultsData> mResultsData; // 0x26c
    std::vector<int> unk274;
    TambourineDetector mTambourineDetector; // 0x27c
    float unk29c;
    float unk2a0;
    int unk2a4;
    TalkyMatcher *mTalkyMatcher; // 0x2a8
};