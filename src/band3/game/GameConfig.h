#pragma once
#include "obj/Object.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "game/PracticeSectionProvider.h"
#include "game/Defines.h"

class GameConfig : public Hmx::Object {
public:
    GameConfig();
    virtual ~GameConfig();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    Difficulty GetAverageDifficulty() const;
    bool CanEndGame() const;

    PlayerTrackConfigList* mPlayerTrackConfigList; // 0x1c
    PracticeSectionProvider* mPracticeSectionProvider; // 0x20
    float mSongLimitMs; // 0x24
    // 0x28 and 0x2c - int[2] mPracticeSections?
    int unk28; // 0x28
    int unk2c; // 0x2c
    int mPracticeSpeed; // 0x30
    bool mPracticeMode; // 0x34
};

extern GameConfig* TheGameConfig;