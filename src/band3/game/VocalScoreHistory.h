#pragma once
#include <vector>

class VocalScoreCache {
public:
    VocalScoreCache()
        : unk0(0), unk4(0), unk8(0), unkc(0), unk10(0), unk14(0), unk1c(0), unk20(0),
          unk21(0), unk22(0), unk24(0) {}
    ~VocalScoreCache() {}

    float unk0;
    float unk4;
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
    int unk1c;
    bool unk20;
    bool unk21;
    bool unk22;
    float unk24;
};

class VocalScoreHistory {
public:
    VocalScoreHistory(int, int);
    ~VocalScoreHistory();

    void AddScore(float, float);
    void SetOctaveOffset(int);
    float CalculateSum(float) const;
    void Reset();
    void BiasLastScore(float);
    int GetOctaveOffset() const;

    float unk0;
    std::vector<float> mScores; // 0x4
    int unkc;
    int unk10;
    int unk14;
    float unk18;
    int mOctaveOffset; // 0x1c
    bool unk20;
};