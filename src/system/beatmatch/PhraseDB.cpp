#include "beatmatch/Phrase.h"
#include "os/Debug.h"

PhraseDB::PhraseDB(int num){
    mPhraseListCollections.reserve(num);
    for(int i = 0; i < num; i++){
        mPhraseListCollections.push_back(new PhraseListCollection());
    }
}

PhraseDB::~PhraseDB(){
    for(int i = 0; i < mPhraseListCollections.size(); i++){
        delete mPhraseListCollections[i];
        mPhraseListCollections[i] = 0;
    }
}

void PhraseDB::Clear(){
    for(int i = 0; i < mPhraseListCollections.size(); i++){
        mPhraseListCollections[i]->Clear();
    }
}

void PhraseDB::AddPhrase(BeatmatchPhraseType ty, int diff, float ms, int ticks, float dur_ms, int dur_ticks){
    MILO_ASSERT(0 <= diff && diff < mPhraseListCollections.size(), 0x32);
    mPhraseListCollections[diff]->AddPhrase(ty, ms, ticks, dur_ms, dur_ticks);
}

const PhraseList& PhraseDB::GetPhraseList(int diff, BeatmatchPhraseType ty) const {
    MILO_ASSERT(0 <= diff && diff < mPhraseListCollections.size(), 0x3A);
    return *mPhraseListCollections[diff]->mPhraseLists[ty];
}