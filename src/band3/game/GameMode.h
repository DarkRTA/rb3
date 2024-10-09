#pragma once
#include "obj/MsgSource.h"

class GameMode : public MsgSource {
public:
    GameMode();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~GameMode();

    void SetMode(Symbol);
    bool InMode(Symbol);
    DataNode OnSetMode(const DataArray*);

    Symbol mMode; // 0x1c
    int mOverdriveEnabled; // 0x20
    int unk24; // 0x24
    int unk28; // 0x28
    int mH2HArrangement; // 0x2c
    int mIsPractice; // 0x30
    int mCanLose; // 0x34
    int unk38; // 0x38
    int mCrowdReacts; // 0x3c
    int mIsSolo; // 0x40
    int mDisableGuitarFx; // 0x44
    int mIsDrumTrainer; // 0x48
    int unk4c; // 0x4c
    int mEnableStreak; // 0x50
    int unk54; // 0x54
    int mIsTutorial; // 0x58
    int mLoadChars; // 0x5c
    int mShowStars; // 0x60
    int mHasSongSections; // 0x64
    int mEnableWhammy; // 0x68
    int mEndWithSong; // 0x6c
    int mIsStory; // 0x70
};

void GameModeInit();

extern GameMode* TheGameMode;