#include "beatmatch/GameGemDB.h"

GameGemDB::GameGemDB(int count, int thresh) : mHopoThreshold(thresh) {
    mGameGemLists.reserve(count);
    for(int i = 0; i < count; i++){
        mGameGemLists.push_back(new GameGemList(thresh));
    }
}

GameGemDB::~GameGemDB(){
    for(int i = 0; i < mGameGemLists.size(); i++){
        for(std::vector<GameGem>::iterator it = mGameGemLists[i]->mGems.begin(); it != mGameGemLists[i]->mGems.end(); it++){
            delete it;
        }
    }
}

void GameGemDB::Clear(){
    for(int i = 0; i < mGameGemLists.size(); i++){
        mGameGemLists[i]->Clear();
    }
}

bool GameGemDB::AddMultiGem(int diff, const MultiGemInfo& info){
    MILO_ASSERT(0 <= diff && diff < mGameGemLists.size() && mGameGemLists[ diff], 0x34);
    return mGameGemLists[diff]->AddMultiGem(info);
}

bool GameGemDB::AddRGGem(int diff, const RGGemInfo& info){
    MILO_ASSERT(0 <= diff && diff < mGameGemLists.size() && mGameGemLists[ diff], 0x3A);
    return mGameGemLists[diff]->AddRGGem(info);
}

void GameGemDB::MergeChordGems(){
    for(int i = 0; i < mGameGemLists.size(); i++){
        mGameGemLists[i]->MergeChordGems();
    }
}

const GameGemList* GameGemDB::GetDiffGemList(int diff) const {
    MILO_ASSERT(0 <= diff && diff < mGameGemLists.size() && mGameGemLists[ diff], 0x48);
    return mGameGemLists[diff];
}

GameGemList* GameGemDB::GetDiffGemList(int diff) {
    MILO_ASSERT(0 <= diff && diff < mGameGemLists.size() && mGameGemLists[ diff], 0x4E);
    return mGameGemLists[diff];
}

void GameGemDB::Finalize(){
    for(int i = 0; i < mGameGemLists.size(); i++){
        mGameGemLists[i]->Finalize();
    }
}

GameGemDB* GameGemDB::Duplicate() const {
    GameGemDB* duped = new GameGemDB(mGameGemLists.size(), mHopoThreshold);
    for(int i = 0; i < mGameGemLists.size(); i++){
        duped->mGameGemLists[i]->CopyFrom(mGameGemLists[i]);
    }
}
