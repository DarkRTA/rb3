#include "meta_band/SongUpgradeMgr.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

String* gMidiFileResult;
bool gMidiFileFound;

void SongUpgradeData::InitSongUpgradeData(){
    mUpgradeVersion = -1;
    mRealGuitarRank = 0;
    mRealBassRank = 0;
    for(int i = 0; i < 6; i++){
        mRealGuitarTuning[i] = 0;
    }
    for(int i = 0; i < 4; i++){
        mRealBassTuning[i] = 0;
    }
}

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

void SongUpgradeData::Save(BinStream& bs){
    bs << sSaveVer;
    bs << mUpgradeVersion;
    bs << mMidiFile;
    bs << mRealGuitarRank;
    bs << mRealBassRank;
    for(int i = 0; i < 6; i++){
        bs << mRealGuitarTuning[i];
    }
    for(int i = 0; i < 4; i++){
        bs << mRealBassTuning[i];
    }
}

void SongUpgradeData::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev >= 1) bs >> mUpgradeVersion;
    else mUpgradeVersion = 0;
    bs >> mMidiFile;
    int idx = mMidiFile.find("songs_upgrades", 0);
    if(idx != String::npos){
        char& charAt = mMidiFile[idx + 14];
        if(charAt != '/' && charAt != '\\'){
            MILO_LOG("SongUpgradeData: correcting %s (insert / at %d)\n", mMidiFile, idx + 14);
            String substr30 = mMidiFile.substr(0, idx + 14);
            String substr3c = mMidiFile.substr(idx + 14);
            mMidiFile = substr30;
            mMidiFile += "/";
            mMidiFile += substr3c;
            MILO_LOG("SongUpgradeData: now        %s\n", mMidiFile);
        }
    }
    bs >> mRealGuitarRank;
    bs >> mRealBassRank;
    for(int i = 0; i < 6; i++){
        bs >> mRealGuitarTuning[i];
    }
    for(int i = 0; i < 4; i++){
        bs >> mRealBassTuning[i];
    }
}

const char* SongUpgradeData::MidiFile() const { return mMidiFile.c_str(); }

bool SongUpgradeData::HasPart(Symbol) const {
    return mRealGuitarRank != 0 || mRealBassRank != 0;
}

float SongUpgradeData::Rank(Symbol inst) const {
    if(inst == real_guitar) return mRealGuitarRank;
    else if(inst == real_bass) return mRealBassRank;
    else {
        MILO_FAIL("Asking a song upgrade for a part rank that's not real_guitar or real_bass!");
        return 0;
    }
}

int SongUpgradeData::RealGuitarTuning(int string) const {
    return mRealGuitarTuning[string];
}

int SongUpgradeData::RealBassTuning(int string) const {
    return mRealBassTuning[string];
}

void RecurseMidiFileCallback(const char* c1, const char* c2){
    gMidiFileFound = true;
    *gMidiFileResult = MakeString("%s/%s", c1, c2);
}

SongUpgradeMgr::SongUpgradeMgr() : unk64(0) {
    TheContentMgr->RegisterCallback(this, false);
}