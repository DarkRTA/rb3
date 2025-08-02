#include "meta_band/SongSortByRank.h"
#include "meta/Sorting.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SongSortNode.h"
#include "net_band/RockCentral.h"
#include "os/Debug.h"
#include "stl/pointers/_vector.h"

RankCmp::RankCmp(int val, const char *name, RankCmp::RankType ty)
    : mVal(val), mSongName(name), mType(ty) {}



int RankCmp::Compare(const SongSortCmp *s, SongNodeType nodeType) const {
    RankCmp *cmp = (RankCmp *)s;
    switch(nodeType) {
        case kNodeShortcut:
        case kNodeHeader:
        if(cmp->mType)
            if (mType == kPercentile){
                return (mType - mType % 10) - (cmp->mType % 10);
            }
            else return 0; 
        case kNodeSong:
        case kNodeStoreSong:
            if(mType == cmp->mType) {
                if (mType == kPercentile) {
                    if(cmp->mVal != mVal) {
                        return cmp->mVal - mVal;
                    }
                    return AlphaKeyStrCmp(mSongName, cmp->mSongName, true);
                }
                return mVal - cmp->mVal;
            }
        default:
        if(nodeType != kNodeSong && nodeType != kNodeStoreSong){
            MILO_FAIL("invalid type of node comparison.\n");
            return 0;
        }
    }
}

SongSortByRank::~SongSortByRank() {
    
}

void SongSortByRank::Clear() {
    mRankings.clear();
    mDataResults.Clear();
}

bool SongSortByRank::IsReady() const {
    return !mRankings.empty();
}

void SongSortByRank::MakeReady() {
    RequestSongRankingInfo();
}

void SongSortByRank::CancelMakeReady() {
    CancelSongRankingRequest();
    if(!mRankings.empty())
        mRankings.clear();
    mDataResults.Clear();
}

void SongSortByRank::RequestSongRankingInfo() {
    Profile *prof = TheProfileMgr.GetPrimaryProfile();
    if(prof) {
        stlpmtx_std::vector<int> something;
        ScoreType sType = TheMusicLibrary->ActiveScoreType();
        TheSongMgr.GetRankedSongs(something, true, true);
        TheRockCentral.GetMultipleRankingsForPlayer(prof, sType, something, mDataResults, this);
    }
}

void SongSortByRank::CancelSongRankingRequest() {
    TheRockCentral.CancelOutstandingCalls(this);
}

