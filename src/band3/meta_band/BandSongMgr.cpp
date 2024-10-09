#include "meta_band/BandSongMgr.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

BandSongMgr gSongMgr;
BandSongMgr* TheSongMgr = &gSongMgr;

BandSongMgr::BandSongMgr() : unkc0(0), unk124(1), mUpgradeMgr(0), mLicenseMgr(0), mMaxSongCount(-1), unk13c(0), unk140(0) {
    // unk130 method...
    TheBaseSongManger = this;
}

void BandSongMgr::Init(){
    SongMgr::Init();
    SetName("song_mgr", ObjectDir::sMainDir);
    TheContentMgr->RegisterCallback(this, false);
    unkc4.clear();
    unkdc.clear();
    DataArray* cfg = SystemConfig(song_mgr);
    DataArray* altarr = cfg->FindArray(alt_dirs, false);
    if(altarr){
        for(int i = 1; i < altarr->Size(); i++){
            const char* str = altarr->Array(i)->Str(0);
            if(strlen(str) != 0){
                unk130.push_back(String(str));
            }
        }
    }
    mMaxSongCount = cfg->FindInt(max_song_count);
    mUpgradeMgr = new SongUpgradeMgr();
    mLicenseMgr = new LicenseMgr();
}