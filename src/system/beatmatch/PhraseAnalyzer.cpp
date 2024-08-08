#include "beatmatch/Phrase.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"

void PhraseAnalyzer::AddInfo(int track, TrackType ty, int start_tick, int end_tick, bool independent){
    MILO_ASSERT(!mPerformedAnalysis, 0x43);
    MemDoTempAllocations tmp(true, false);
    mRawPhrases.push_back(RawPhrase(track, ty, start_tick, end_tick, independent, -1));
}

int PhraseAnalyzer::NumPhrases() const {
    MILO_ASSERT(mPerformedAnalysis, 0xE6);
    return mPhrases.size();
}

