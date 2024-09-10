#ifndef BANDTRACK_NOWBAR_H
#define BANDTRACK_NOWBAR_H

#include "system/track/TrackDir.h"
#include "TrackConfig.h"
#include "GemSmasher.h"

class NowBar {
public:
    NowBar(TrackDir *, const TrackConfig &);

    void Poll(float, bool);
    void Reset(bool);
    void Hit(float, int, bool, int, bool);
    void Miss(float, int);
    void PopSmasher(int);
    void FillHit(int, int);
    void SetSmasherGlowing(int, bool);
    void StopBurning(unsigned int);

    GemSmasher *FindSmasher(int) const;

    bool HandleOutOfRangeKey(GemSmasher *, int, bool);

    std::vector<GemSmasher *> mSmashers;
    int unk_0x8;
    int unk_0xc;

    TrackDir *mTrackDir;
    const TrackConfig *mTrackConfig;
};

#endif // BANDTRACK_NOWBAR_H