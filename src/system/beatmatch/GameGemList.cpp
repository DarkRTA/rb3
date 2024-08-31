#include "beatmatch/GameGemList.h"
#include <algorithm>

GameGemList::GameGemList(int thresh) : mHopoThreshold(thresh) {

}

void GameGemList::Clear(){
    mGems.clear();
}

void GameGemList::CopyFrom(const GameGemList* gList){
    mHopoThreshold = gList->mHopoThreshold;
    mGems.clear();
}

bool GameGemList::AddMultiGem(const MultiGemInfo& info){
    return AddGameGem(GameGem(info), info.no_strum);
}

bool GameGemList::AddRGGem(const RGGemInfo& info){
    return AddGameGem(GameGem(info), info.no_strum);
}

int GameGemList::ClosestMarkerIdx(float f) const {
    float theFloat = f;
    // GameGem* theGem = std::lower_bound(mGems.begin(), mGems.end(), theFloat, GameGemCmp, 0);
}

bool GameGemCmp(const GameGem& gem, float ms){
    return gem.mMs < ms;
}

bool GameGemTickCmp(const GameGem& gem, int tick){
    return gem.mTick < tick;
}

float GameGemList::TimeAt(int idx) const {
    MILO_ASSERT(idx < mGems.size(), 0xA5);
    return mGems[idx].mMs;
}

void GameGemList::RecalculateGemTimes(TempoMap* tmap){
    for(std::vector<GameGem>::iterator it = mGems.begin(); it != mGems.end(); it++){
        it->RecalculateTimes(tmap);
    }
    std::sort(mGems.begin(), mGems.end());
}

void GameGemList::Reset(){
    for(std::vector<GameGem>::iterator it = mGems.begin(); it != mGems.end(); it++){
        it->mPlayed = false;
        it->unk10b1 = false;
    }
}