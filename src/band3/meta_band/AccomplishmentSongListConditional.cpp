#include "meta_band/AccomplishmentSongListConditional.h"
#include "AccomplishmentSongConditional.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

AccomplishmentSongListConditional::AccomplishmentSongListConditional(DataArray* arr, int i) : AccomplishmentSongConditional(arr, i) {
    Configure(arr);
}

AccomplishmentSongListConditional::~AccomplishmentSongListConditional(){

}

void AccomplishmentSongListConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x1E);
    DataArray* pSongArray = i_pConfig->FindArray(songs, true);
    MILO_ASSERT(pSongArray->Size() > 1, 0x25);
    for(int i = 1; i < pSongArray->Size(); i++){
        Symbol cur = pSongArray->Node(i).Sym();
        unk7c.push_back(cur);
        unk84.insert(cur);
    }
}

AccomplishmentType AccomplishmentSongListConditional::GetType() const { return kAccomplishmentTypeSongListConditional; }

bool AccomplishmentSongListConditional::IsRelevantForSong(Symbol s) const {
    return unk84.find(s) != unk84.end();
}

bool AccomplishmentSongListConditional::IsFulfilled(BandProfile* profile) const {
    SongStatusMgr* mgr = profile->GetSongStatusMgr();
    for(std::vector<Symbol>::const_iterator it = unk7c.begin(); it != unk7c.end(); ++it){
        if(!CheckConditionsForSong(mgr, *it)) return false;
    }
    return true;
}

int AccomplishmentSongListConditional::GetNumCompletedSongs(BandProfile* profile) const {
    SongStatusMgr* mgr = profile->GetSongStatusMgr();
    int num = 0;
    for(std::vector<Symbol>::const_iterator it = unk7c.begin(); it != unk7c.end(); ++it){
        Symbol cur = *it;
        if(TheSongMgr->HasSong(cur, false)){
            if(CheckConditionsForSong(mgr, cur)){
                num++;
            }
        }
    }
    return num;
}

int AccomplishmentSongListConditional::GetTotalNumSongs() const { return unk7c.size(); }

bool AccomplishmentSongListConditional::InqIncrementalSymbols(BandProfile* profile, std::vector<Symbol>& syms) const {
    syms = unk7c;
    return true;
}

bool AccomplishmentSongListConditional::HasSpecificSongsToLaunch() const { return true; }