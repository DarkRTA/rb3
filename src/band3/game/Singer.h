#pragma once
#include "VocalScoreHistory.h"
#include "bandtrack/DelayLine.h"
#include "game/GameMic.h"
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
    class AmbiguousData {
    public:
        int unk0;
        int unk4;
        bool unk8;
        int unkc;
        float unk10;
    };
    Singer(VocalPlayer *, int);
    ~Singer();

    void NoteTambourineSwing(float);
    void CreateMicClientID();
    void PostLoad();
    GameMic *GetGameMic() const;
    MicClientID GetMicClientID() const;
    void SetMicProcessing(bool, bool);
    void Start();
    void StartIntro();
    void Restart(bool);
    void CancelScream();
    void ClearFreestyleDeployment();
    void ClearScoreHistories();
    void SetPaused(bool);
    void Jump(float, bool);
    void Rollback(float, float);
    void ProcessTalkyData();
    void DetectScream(float, float, float);
    void SetIsSinging(bool);
    void Detune(float);
    void SetFrameMicPitch(float);
    void EnableController();
    void DisableController();
    void SetOctaveOffset(int);
    void AppendToScoreHistory(float, int, float, int);
    float GetHistoricalScore(float, int) const;
    VocalScoreHistory &AccessScoreHistory(int);
    VocalScoreCache &AccessScoreCache(int);
    const VocalScoreCache &AccessScoreCache(int) const;
    void AllScoresAreIn(const std::vector<int> &);
    void SetAutoplayToPart(int);
    int GetAutoplayToPart() const;
    void SetAutoplayVariationMagnitude(float);
    float GetAutoplayVariationMagnitude() const;
    void SetAutoplayOffset(float);
    float GetAutoplayOffset() const;
    void HandlePhraseEnd(float, const std::vector<float> &);
    float GetPartPercentage(int) const;
    void GetPitchDeviation(float &, float &) const;

    float GetFrameMicPitch() const { return mFrameMicPitch; }
    float GetFrameTargetPitch() const { return mFrameTargetPitch; }
    int GetSingerIndex() const { return mSingerIndex; }

    VocalPlayer *mPlayer; // 0x0
    MicClientID mMicClientID; // 0x4
    bool unkc;
    int mSingerIndex; // 0x10
    bool unk14;
    int unk18; // 0x18 - ptr to something
    int unk1c;
    int mIsSinging; // 0x20
    float mDetune; // 0x24
    float mMaxDetune; // 0x28
    float unk2c;
    int unk30;
    int unk34;
    float unk38;
    float unk3c;
    float unk40;
    float unk44;
    float unk48;
    float mScreamEnergyThreshold; // 0x4c
    float unk50;
    int unk54;
    int unk58;
    float mFrameMicPitch; // 0x5c
    float unk60;
    float unk64;
    float mFrameTargetPitch; // 0x68
    float unk6c;
    int mFrameAssignedPart; // 0x70
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
    float mVibratoFrameBonus; // 0x248
    float unk24c;
    int mAutoplayPart; // 0x250
    float mAutoplayVariationMagnitude; // 0x254
    float mAutoplayOffset; // 0x258
    std::vector<VocalScoreHistory> mScoreHistories; // 0x25c
    std::vector<VocalScoreCache> mScoreCaches; // 0x264
    std::vector<SingerResultsData> mResultsData; // 0x26c
    std::vector<AmbiguousData> mAmbiguousData; // 0x274
    TambourineDetector mTambourineDetector; // 0x27c
    float unk29c;
    float unk2a0;
    int unk2a4;
    TalkyMatcher *mTalkyMatcher; // 0x2a8
};