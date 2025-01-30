#include "beatmatch/PhraseAnalyzer.h"
#include "beatmatch/Phrase.h"
#include "beatmatch/SongData.h"
#include "beatmatch/TrackType.h"
#include "os/Debug.h"
#include "utl/MBT.h"
#include "utl/MemMgr.h"
#include "utl/Std.h"
#include <algorithm>

namespace {
    int sEquivalentTrackTypes[5] = { 1, 0xC2, 0x304, 0x30, 8 };
}

PhraseAnalyzer::PhraseData::PhraseData(int i, int j, int mask) : unk0(i), unk2(j), unk4(mask), mUnison(false) {
    int num_instruments = 0;
    for(int i = 0; i < 5; i++){
        if(mask & sEquivalentTrackTypes[i]){
            num_instruments++;
            mask &= ~sEquivalentTrackTypes[i];
            if(num_instruments >= 2){
                mUnison = true;
                break;
            }
        }
    }
    MILO_ASSERT(mUnison || num_instruments == 1, 0x33);
}

void PhraseAnalyzer::AddInfo(int track, TrackType ty, int start_tick, int end_tick, bool independent){
    MILO_ASSERT(!mPerformedAnalysis, 0x43);
    MemDoTempAllocations tmp(true, false);
    mRawPhrases.push_back(RawPhrase(track, ty, start_tick, end_tick, independent));
}

void PhraseAnalyzer::Analyze(){
    MILO_ASSERT(!mPerformedAnalysis, 0x4B);
    std::sort(mRawPhrases.begin(), mRawPhrases.end(), RawPhraseCmp);
    RawPhrase rawPhrase(-1, kTrackNone, -1000, -1000, 0);
    int i8 = 0;
    int i7 = 0;
    int i6 = 0;
    for(int i = 0; i < mRawPhrases.size(); i++){
        if(mRawPhrases[i].independent){
            SetPhraseIDs(i, i + 1, 1 << mRawPhrases[i].track, 1 << mRawPhrases[i].track_type);
        }
        else {
            if(abs(mRawPhrases[i].start_tick - rawPhrase.start_tick) < mPhraseStartWindow){
                if(abs(mRawPhrases[i].end_tick - rawPhrase.end_tick) >= mPhraseStartWindow){
                    const char* msg = MakeString("%s: Phrases don't quite coincide at %s, %s and %s", 
                        mSongData->SongFullPath(), TickFormat(rawPhrase.start_tick, *mSongData->GetMeasureMap()),
                        mSongData->TrackName(rawPhrase.track), mSongData->TrackName(mRawPhrases[i].track));
                    if(mNotify) MILO_WARN(msg);
                    else MILO_LOG("%s\n", msg);
                }                
                i8 |= 1 << mRawPhrases[i].track;
                i7 |= 1 << mRawPhrases[i].track_type;
            }
            else {
                if(i8 != 0){
                    SetPhraseIDs(i6, i, i8, i7);
                }
                rawPhrase = mRawPhrases[i];
                i8 = 1 << mRawPhrases[i].track;
                i7 = 1 << mRawPhrases[i].track_type;
                i6 = i;
            }
        }
    }
    if(!mRawPhrases.empty()){
        SetPhraseIDs(i6, mRawPhrases.size(), i8, i7);
    }
    for(int i = 0; i < mRawPhrases.size(); i++);
    TrimExcess(mRawPhrases);
    mPerformedAnalysis = true;
    Verify();
}

void PhraseAnalyzer::Verify() const {
    int trackTypes = mSongData->GetTrackTypes();
    for(int i = 0; i < mPhrases.size(); i++){
        int mask = mPhrases[i].unk4;
        for(int j = 0; j < 5U; j++){
            int i10 = mask & sEquivalentTrackTypes[j];
            if(i10){
                int i3 = trackTypes & sEquivalentTrackTypes[j];
                if(i10 != i3){
                    i3 -= i10;
                    String str54;
                    String str60;
                    for(int bit = 0; i10 != 0; bit++){
                        int i11 = 1 << bit;
                        if(i10 & i11){
                            str54 += TrackTypeToSym((TrackType)bit);
                            str54 += " ";
                            i10 -= i11;
                        }
                    }
                    for(int bit = 0; i3 != 0; bit++){
                        i10 = 1 << bit;
                        if(i3 & i10){
                            str54 += TrackTypeToSym((TrackType)bit);
                            str54 += " ";
                            i3 -= i10;
                        }
                    }
                    MILO_WARN("%s: %s Overdrive phrase for %sbut not %s", mSongData->SongFullPath(), 
                        TickFormat(mRawPhrases[mPhrases[i].unk0].start_tick, *mSongData->GetMeasureMap()),
                        str54.c_str(), str60.c_str());
                }
            }
        }
    }
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
    for(int n = i; n < j; n++){
        if(mRawPhrases[n].id == -1){
            canpush = true;
            mRawPhrases[n].id = mPhrases.size();
        }
    }
    if(canpush){
        mPhrases.push_back(PhraseData(i, k, l));
    }
}