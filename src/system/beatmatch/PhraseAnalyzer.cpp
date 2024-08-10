#include "beatmatch/Phrase.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include <algorithm>

namespace {
    int sEquivalentTrackTypes[5] = { 1, 0xC2, 0x304, 0x30, 8 };
}

PhraseAnalyzer::PhraseData::PhraseData(int i, int j, int mask){
    unk2 = j;
    unk0 = i;
    unk4 = mask;
    mUnison = false;
    unsigned char num_instruments = mask & sEquivalentTrackTypes[0] != 0;
    if((bool)num_instruments) mask &= ~sEquivalentTrackTypes[0];
    if(mask & sEquivalentTrackTypes[1]){
        num_instruments++;
        mask & ~sEquivalentTrackTypes[1];
        if(num_instruments >= 2){
            mUnison = true;
        }
    }
    else if(mask & sEquivalentTrackTypes[2]){
        num_instruments++;
        mask & ~sEquivalentTrackTypes[2];
        if(num_instruments >= 2){
            mUnison = true;
        }
    }
    else if(mask & sEquivalentTrackTypes[3]){
        num_instruments++;
        mask & ~sEquivalentTrackTypes[3];
        if(num_instruments >= 2){
            mUnison = true;
        }
    }
    else if(mask & sEquivalentTrackTypes[4]){
        num_instruments++;
        mask & ~sEquivalentTrackTypes[4];
        if(num_instruments >= 2){
            mUnison = true;
        }
    }
    MILO_ASSERT(mUnison || num_instruments == 1, 0x33);
}

void PhraseAnalyzer::AddInfo(int track, TrackType ty, int start_tick, int end_tick, bool independent){
    MILO_ASSERT(!mPerformedAnalysis, 0x43);
    MemDoTempAllocations tmp(true, false);
    mRawPhrases.push_back(RawPhrase(track, ty, start_tick, end_tick, independent, -1));
}

void PhraseAnalyzer::Analyze(){
    MILO_ASSERT(!mPerformedAnalysis, 0x4B);
    std::sort(mRawPhrases.begin(), mRawPhrases.end(), RawPhraseCmp);
}

int PhraseAnalyzer::NumPhrases() const {
    MILO_ASSERT(mPerformedAnalysis, 0xE6);
    return mPhrases.size();
}

int PhraseAnalyzer::GetPhraseTracks(int idx) const {
    MILO_ASSERT(mPerformedAnalysis, 0xEC);
    return mPhrases[idx].unk2;
}

bool PhraseAnalyzer::IsUnisonPhrase(int idx) const {
    MILO_ASSERT(mPerformedAnalysis, 0xF2);
    bool ret;
    if(idx < 0 || idx > mPhrases.size()) ret = 0;
    else ret = mPhrases[idx].mUnison;
    return ret;
}

int PhraseAnalyzer::NumPhrases(int mask) const {
    MILO_ASSERT(mPerformedAnalysis, 0x104);
    int num = 0;
    for(int i = 0; i < mPhrases.size(); i++){
        if(mPhrases[i].unk2 & (1 << mask)) num++;
    }
    return num;
}

const std::vector<RawPhrase>& PhraseAnalyzer::GetRawPhrases() const {
    return mRawPhrases;
}

void PhraseAnalyzer::SetPhraseIDs(int i, int j, int k, int l){
    bool canpush = false;
    int i2 = j - i;
    if(i < j){
        for(int n = 0; n < i2; n++){
            if(mRawPhrases[n].id == -1){
                canpush = true;
                mRawPhrases[n].track = mPhrases.size();
            }
        }
    }
    if(canpush){
        mPhrases.push_back(PhraseData(i, k, l));
    }
}