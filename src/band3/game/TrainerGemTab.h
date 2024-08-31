#ifndef GAME_TRAINERGEMTAB_H
#define GAME_TRAINERGEMTAB_H
#include "beatmatch/TrackType.h"
#include "beatmatch/GameGem.h"
#include "math/Mtx.h"

class BandLabel;
class RndDir;
class RndAnimatable;
class RndGroup;
class RndMesh;
class RndTransformable;

// size 0x13c
class TrainerGemTab {
public:
    // size 0x38
    class ExtraTail {
    public:
        char filler[0x38];
    };

    TrainerGemTab();
    ~TrainerGemTab();
    void Init(RndDir*, TrackType);

    RndDir* mGemTab; // 0x0
    TrackType mTrackType; // 0x4
    int mLanes; // 0x8
    RndAnimatable* mConfigAnim; // 0xc
    RndAnimatable* mVerticalTrans; // 0x10
    Transform mTrans; // 0x14
    RndGroup* mDrawOrderGroup; // 0x44
    int unk48;
    std::vector<GameGem> unk4c;
    int unk54;
    RndMesh* mGems[9]; // 0x58
    RndMesh* mTails[5]; // 0x7c
    int unk90;
    RndGroup* mTrackGroup; // 0x94
    RndTransformable* mInstLanes[25]; // 0x98 - 0xf8, inclusive
    RndMesh* mGemChord2Lane; // 0xfc
    RndMesh* mGemChord3Lane; // 0x100
    RndMesh* mGemChord4Lane; // 0x104
    RndMesh* mGemChord5Lane; // 0x108
    RndMesh* mGemChord6Lane; // 0x10c
    RndMesh* mGemSustainCyan; // 0x110
    BandLabel* mNumLabels[4]; // 0x114, 0x118, 0x11c, 0x120
    BandLabel* mStartLabel; // 0x124
    BandLabel* mFinishLabel; // 0x128
    float unk12c; // 0x12c
    std::vector<ExtraTail> unk130;
    bool mLefty; // 0x138
};

#endif