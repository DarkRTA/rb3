#pragma once
#include "system/track/TrackDir.h"
#include "TrackConfig.h"
#include "GemSmasher.h"

class NowBar {
public:
    NowBar(TrackDir *, const TrackConfig &);
    ~NowBar();
    void Poll(float, bool);
    void Reset(bool);
    void Hit(float, int, bool, int, bool);
    void Miss(float, int);
    void PopSmasher(int);
    void FillHit(int, int);
    void SetSmasherGlowing(int, bool);
    void StopBurning(unsigned int);
    void PartialHit(int, unsigned int, bool, int);

    GemSmasher *FindSmasher(int) const;

    bool HandleOutOfRangeKey(GemSmasher *, int, bool);

    std::vector<GemSmasher *> mSmashers; // 0x0
    int unk_0x8; // 0x8
    int unk_0xc; // 0xc
    TrackDir *mTrackDir; // 0x10
    const TrackConfig &mTrackConfig; // 0x14
};
