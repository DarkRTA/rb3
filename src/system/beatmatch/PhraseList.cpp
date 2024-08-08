#include "beatmatch/Phrase.h"
#include "os/Debug.h"
#include "utl/STLHelpers.h"
#include <algorithm>

bool PhraseTickCmp(const Phrase& p, int i){
    return p.mTick + p.mDurationTicks < i;
}

void PhraseList::Clear(){
    mPhrases.clear();
}

void PhraseList::AddPhrase(float ms, int ticks, float dur_ms, int dur_ticks){
    // MILO_ASSERT(mPhrases.empty() || mPhrases.back().GetMs() < ms, 0x21);
    bool b = false;
    if (mPhrases.empty() || mPhrases.back().GetMs() < ms) b = true;
    if (!b) {
        TheDebugFailer << MakeString(kAssertStr, __FILE__, 0x21, "mPhrases.empty() || mPhrases.back().GetMs() < ms");
    }

    mPhrases.push_back(Phrase(ms, dur_ms, ticks, dur_ticks));
}

bool PhraseList::IsTickInPhrase(int tick) const {
    const Phrase* p = std::lower_bound(mPhrases.begin(), mPhrases.end(), tick, PhraseTickCmp);
    if(p == mPhrases.end()) return false;
    else return p->GetTick() <= tick && tick <= p->GetTick() + p->GetDurationTicks();
}

PhraseListCollection::PhraseListCollection(){
    for(int i = 0; i < 6; i++){
        mPhraseLists.push_back(new PhraseList());
    }
}

PhraseListCollection::~PhraseListCollection(){
    for(int i = 0; i < mPhraseLists.size(); i++){
        delete mPhraseLists[i];
    }
}

void PhraseListCollection::Clear(){
    for(int i = 0; i < mPhraseLists.size(); i++){
        mPhraseLists[i]->Clear();
    }
}

void PhraseListCollection::AddPhrase(BeatmatchPhraseType ty, float ms, int ticks, float dur_ms, int dur_ticks){
    mPhraseLists[ty]->AddPhrase(ms, ticks, dur_ms, dur_ticks);
}