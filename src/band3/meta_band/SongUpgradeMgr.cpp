#include "meta_band/SongUpgradeMgr.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

SongUpgradeData::SongUpgradeData(){
    InitSongUpgradeData();
}

SongUpgradeData::SongUpgradeData(DataArray* da){
    InitSongUpgradeData();
    DataArray* upgradearr = da->FindArray(upgrade_version, false);
    if(upgradearr) mUpgradeVersion = upgradearr->Int(1);
    DataArray* midifilearr = da->FindArray(midi_file, false);
    if(midifilearr) mMidiFile = midifilearr->Str(1);
    MILO_LOG("SongUpgradeData: MIDI file: %s\n", mMidiFile.c_str());
    DataArray* rankarr = da->FindArray(rank, false);
    if(rankarr){
        DataArray* garr = rankarr->FindArray(real_guitar, false);
        if(garr) mRealGuitarRank = garr->Float(1);
        DataArray* barr = rankarr->FindArray(real_bass, false);
        if(barr) mRealBassRank = barr->Float(1);
    }
    DataArray* rgtuningarr = da->FindArray(real_guitar_tuning, false);
    if(rgtuningarr){
        for(int i = 0; i < 6; i++){
            mRealGuitarTuning[i] = rgtuningarr->Array(1)->Int(i);
        }
    }
    DataArray* rbtuningarr = da->FindArray(real_bass_tuning, false);
    if(rbtuningarr){
        for(int i = 0; i < 4; i++){
            mRealBassTuning[i] = rbtuningarr->Array(1)->Int(i);
        }
    }
}

SongUpgradeMgr::SongUpgradeMgr() : unk64(0) {
    TheContentMgr->RegisterCallback(this, false);
}