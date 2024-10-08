#include "game/GameConfig.h"

GameConfig* TheGameConfig;

GameConfig::GameConfig() : mPracticeSectionProvider(new PracticeSectionProvider()), mSongLimitMs(3.4028235E+38f), mPracticeSpeed(0), mPracticeMode(0) {
    MILO_ASSERT(!TheGameConfig, 0x38);
    TheGameConfig = this;
    mPlayerTrackConfigList = new PlayerTrackConfigList(4);
    unk2c = -1;
    unk28 = -1;
}

GameConfig::~GameConfig(){
    RELEASE(TheGameConfig);
}