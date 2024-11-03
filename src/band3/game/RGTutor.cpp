#include "game/RGTutor.h"
#include "game/GemTrainerPanel.h"

RGTutor::RGTutor() : mNumPlays(0) {

}

RGTutor::~RGTutor(){

}

void RGTutor::Clear(){
    mNumPlays = 0;
    unk4.clear();
}

void RGTutor::Hit(int i, const GameGem& gem){
    unk4[GetMapKey(i, gem)] = 0;
}

bool RGTutor::Miss(int i, const GameGem& gem, Difficulty diff){
    int key = GetMapKey(i, gem);
    unk4[key]++;
    if(mNumPlays == 0 || unk4[key] >= 2){
        unk4[key] = 0;
        return true;
    }
    else return false;
}

int RGTutor::GetMapKey(int i, const GameGem& gem) const {
    if(gem.IsRealGuitarChord()){
        return gem.GetRGChordID();
    }
    else {
        return i % TheGemTrainerPanel->GetPatternSize();
    }
}

void RGTutor::Loop(){ mNumPlays++; }