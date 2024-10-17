#include "meta_band/AccomplishmentDiscSongConditional.h"
#include "AccomplishmentManager.h"
#include "AccomplishmentSongConditional.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "meta_band/BandSongMgr.h"
#include "stl/_algo.h"
#include "utl/Symbols.h"
#include <vector>

AccomplishmentDiscSongConditional::AccomplishmentDiscSongConditional(DataArray* arr, int i) : AccomplishmentSongConditional(arr, i), mPartDifficultySym("") {
    Configure(arr);
}

AccomplishmentDiscSongConditional::~AccomplishmentDiscSongConditional(){

}

void AccomplishmentDiscSongConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x1F);
    i_pConfig->FindData(part_difficulty_sym, mPartDifficultySym, false);
    DataArray* pFilterArray = i_pConfig->FindArray(filter, false);
    if(pFilterArray){
        for(int i = 1; i < pFilterArray->Size(); i++){
            DataArray* pEntry = pFilterArray->Array(i);
            MILO_ASSERT(pEntry, 0x2C);
            MILO_ASSERT(pEntry->Size() == 2, 0x2D);
            FilterType ty = (FilterType)pEntry->Int(0);
            Symbol s = pEntry->Str(1);
            mFilter.AddFilter(ty, s);
        }
    }
}

AccomplishmentType AccomplishmentDiscSongConditional::GetType() const { return kAccomplishmentTypeDiscSongConditional; }

bool AccomplishmentDiscSongConditional::IsRelevantForSong(Symbol s) const {
    int id = TheSongMgr->GetSongIDFromShortName(s, true);
    SongMetadata* pData = TheSongMgr->Data(id);
    MILO_ASSERT(pData, 0x43);
    return pData->IsOnDisc();
}

bool AccomplishmentDiscSongConditional::IsFulfilled(BandProfile* profile) const {
    std::vector<Symbol> songs;
    InqSongs(songs, false);
    SongStatusMgr* mgr = profile->GetSongStatusMgr();
    for(std::vector<Symbol>::const_iterator it = songs.begin(); it != songs.end(); ++it){
        if(!CheckConditionsForSong(mgr, *it)) return false;
    }
    return true;
}

int AccomplishmentDiscSongConditional::GetNumCompletedSongs(BandProfile* profile) const {
    std::vector<Symbol> songs;
    InqSongs(songs, false);
    SongStatusMgr* mgr = profile->GetSongStatusMgr();
    int num = 0;
    for(std::vector<Symbol>::const_iterator it = songs.begin(); it != songs.end(); ++it){
        Symbol cur = *it;
        if(!TheSongMgr->HasSong(cur, false)) continue;
        if(!CheckConditionsForSong(mgr, cur)) continue;
        num++;
    }
    return num;
}

bool AccomplishmentDiscSongConditional::InqSongs(std::vector<Symbol>& o_rSymbols, bool shouldsort) const {
    MILO_ASSERT(o_rSymbols.empty(), 0x86);
    const std::vector<Symbol>& discsongs = TheAccomplishmentMgr->GetDiscSongs();
    for(std::vector<Symbol>::const_iterator it = discsongs.begin(); it != discsongs.end(); ++it){
        Symbol cur = *it;
        int songid = TheSongMgr->GetSongIDFromShortName(cur, true);
        if(TheSongSortMgr->DoesSongMatchFilter(songid, &mFilter, mPartDifficultySym)){
            o_rSymbols.push_back(cur);
        }
    }
    if(shouldsort){
        std::stable_sort(o_rSymbols.begin(), o_rSymbols.end(), SongDifficultyCmp(mPartDifficultySym));
    }
    return !o_rSymbols.empty();
}

int AccomplishmentDiscSongConditional::GetTotalNumSongs() const {
    std::vector<Symbol> songs;
    InqSongs(songs, false);
    return songs.size();
}

bool AccomplishmentDiscSongConditional::InqIncrementalSymbols(BandProfile*, std::vector<Symbol>& songs) const {
    return InqSongs(songs, true);
}

bool AccomplishmentDiscSongConditional::HasSpecificSongsToLaunch() const { return true; }

bool AccomplishmentDiscSongConditional::CanBeLaunched() const {
    return GetTotalNumSongs() > 0;
}