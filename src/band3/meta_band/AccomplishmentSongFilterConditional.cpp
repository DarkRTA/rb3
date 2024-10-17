#include "meta_band/AccomplishmentSongFilterConditional.h"
#include "AccomplishmentSongConditional.h"
#include "game/Defines.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

AccomplishmentSongFilterConditional::AccomplishmentSongFilterConditional(DataArray* arr, int i) : AccomplishmentSongConditional(arr, i), mNumSongs(0), mPartDifficultySym("") {
    Configure(arr);
}

AccomplishmentSongFilterConditional::~AccomplishmentSongFilterConditional(){

}

void AccomplishmentSongFilterConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x22);
    i_pConfig->FindData(num_songs, mNumSongs, false);
    i_pConfig->FindData(part_difficulty_sym, mPartDifficultySym, false);
    DataArray* pFilterArray = i_pConfig->FindArray(filter, false);
    if(pFilterArray){
        for(int i = 1; i < pFilterArray->Size(); i++){
            DataArray* pEntry = pFilterArray->Array(i);
            MILO_ASSERT(pEntry, 0x32);
            MILO_ASSERT(pEntry->Size() == 2, 0x33);
            FilterType ty = (FilterType)pEntry->Int(0);
            Symbol sym = pEntry->Str(1);
            mFilter.AddFilter(ty, sym);
        }
    }
    mFilter.requiredTrackType = ScoreTypeToTrackType(GetRequiredScoreType());
}

AccomplishmentType AccomplishmentSongFilterConditional::GetType() const { return kAccomplishmentTypeSongFilterConditional; }

bool AccomplishmentSongFilterConditional::IsRelevantForSong(Symbol s) const {
    int songid = TheSongMgr->GetSongIDFromShortName(s, true);
    return TheSongSortMgr->DoesSongMatchFilter(songid, &mFilter, mPartDifficultySym);
}

bool AccomplishmentSongFilterConditional::IsFulfilled(BandProfile* profile) const {
    return mNumSongs <= GetNumCompletedSongs(profile);
}

int AccomplishmentSongFilterConditional::GetNumCompletedSongs(BandProfile* profile) const {
    std::vector<int> songs;
    InqCompletedSongs(profile, songs);
    int ret = songs.size();
    if(ret >= mNumSongs) ret = mNumSongs;
    return ret;
}

int AccomplishmentSongFilterConditional::GetTotalNumSongs() const { return mNumSongs; }

bool AccomplishmentSongFilterConditional::InqIncrementalSymbols(BandProfile* i_pProfile, std::vector<Symbol>& o_rSymbols) const {
    MILO_ASSERT(TheSongSortMgr, 0x70);
    MILO_ASSERT(i_pProfile, 0x71);
    MILO_ASSERT(o_rSymbols.empty(), 0x72);
    SongStatusMgr* pSongStatusMgr = i_pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0x75);
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int curID = *it;
        if(TheSongSortMgr->DoesSongMatchFilter(curID, &mFilter, mPartDifficultySym)){
            Symbol shortname = TheSongMgr->GetShortNameFromSongID(curID, true);
            if(CheckConditionsForSong(pSongStatusMgr, shortname)){
                o_rSymbols.push_back(shortname);
            }
            if(o_rSymbols.size() >= mNumSongs) break;
        }
    }
    return !o_rSymbols.empty();
}

Symbol AccomplishmentSongFilterConditional::GetFirstUnfinishedAccomplishmentEntry(BandProfile* i_pProfile) const {
    MILO_ASSERT(TheSongSortMgr, 0x99);
    MILO_ASSERT(i_pProfile, 0x9A);
    SongStatusMgr* pSongStatusMgr = i_pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0x9D);
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    
    Symbol symFirst = gNullStr;
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int curID = *it;
        if(TheSongSortMgr->DoesSongMatchFilter(curID, &mFilter, mPartDifficultySym)){
            Symbol shortname = TheSongMgr->GetShortNameFromSongID(curID, true);
            if(!CheckConditionsForSong(pSongStatusMgr, shortname)){
                symFirst = shortname;
                break;
            }
        }
    }
    MILO_ASSERT(symFirst != gNullStr, 0xB8);
    return symFirst;
}

const SongSortMgr::SongFilter& AccomplishmentSongFilterConditional::GetFilter() const { return mFilter; }
Symbol AccomplishmentSongFilterConditional::GetFilteredPartSym() const { return mPartDifficultySym; }

bool AccomplishmentSongFilterConditional::InqCompletedSongs(BandProfile* i_pProfile, std::vector<int>& vec) const {
    MILO_ASSERT(i_pProfile, 0xCB);
    SongStatusMgr* pSongStatusMgr = i_pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0xCE);
    std::vector<int> songs;
    TheSongMgr->GetRankedSongs(songs, false, false);
    for(std::vector<int>::iterator it = songs.begin(); it != songs.end(); ++it){
        int curID = *it;
        if(TheSongSortMgr->DoesSongMatchFilter(curID, &mFilter, mPartDifficultySym)){
            Symbol shortname = TheSongMgr->GetShortNameFromSongID(curID, true);
            if(CheckConditionsForSong(pSongStatusMgr, shortname)){
                vec.push_back(curID);
            }
        }
    }
    return true;
}

void AccomplishmentSongFilterConditional::UpdateIncrementalEntryName(UILabel* label, Symbol s){
    if(s == goal_filtersong_unknown){
        label->SetTextToken(goal_filtersong_unknown);
    }
    else AccomplishmentSongConditional::UpdateIncrementalEntryName(label, s);
}

bool AccomplishmentSongFilterConditional::IsSymbolEntryFulfilled(BandProfile* profile, Symbol s) const {
    if(s == goal_filtersong_unknown) return false;
    else return AccomplishmentSongConditional::IsSymbolEntryFulfilled(profile, s);
}