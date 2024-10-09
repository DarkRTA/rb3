#include "meta_band/BandSongMgr.h"
#include "meta_band/BandSongMetadata.h"
#include "obj/Dir.h"
#include "utl/FakeSongMgr.h"
#include "utl/Symbols.h"

BandSongMgr gSongMgr;
BandSongMgr* TheSongMgr = &gSongMgr;

BandSongMgr::BandSongMgr() : unkc0(0), unk124(1), mUpgradeMgr(0), mLicenseMgr(0), mMaxSongCount(-1), unk13c(0), unk140(0) {
    ClearAndShrink(unk130);
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

void BandSongMgr::Terminate(){
    RELEASE(unkc0);
    RELEASE(mLicenseMgr);
    RELEASE(mUpgradeMgr);
    ClearAndShrink(unk130);
    TheContentMgr->UnregisterCallback(this, false);
    unkc4.clear();
    unkdc.clear();
}

void BandSongMgr::ContentMounted(const char* c1, const char* c2){
    SongMgr::ContentMounted(c1, c2);
}

const char* BandSongMgr::ContentDir(){ return "songs"; }

Symbol BandSongMgr::GetShortNameFromSongID(int songID, bool fail) const {
    MILO_ASSERT(songID != kSongID_Invalid && songID != kSongID_Any && songID != kSongID_Random, 0x156);
    std::map<int, Symbol>::const_iterator it = unkc4.find(songID);
    if(it != unkc4.end()) return it->second;
    it = unkf4.find(songID);
    if(it != unkf4.end()) return it->second;
    if(fail){
        MILO_FAIL("Couldn't find song short name for SONG_ID %d", songID);
    }
    return gNullStr;
}

int BandSongMgr::GetSongIDFromShortName(Symbol shortName, bool fail) const {
    std::map<Symbol, int>::const_iterator it = unkdc.find(shortName);
    if(it != unkdc.end()){
        MILO_ASSERT(it->second != kSongID_Invalid, 0x16D);
        return it->second;
    }
    else {
        for(std::map<int, Symbol>::const_iterator it = unkf4.begin(); it != unkf4.end(); ++it){
            if(it->second == shortName){
                MILO_ASSERT(it->first != kSongID_Invalid, 0x176);
                return it->first;
            }
        }
        if(fail){
            MILO_FAIL("Couldn't find song ID for short name \"%s\", does song have a SONG_ID?", shortName.Str());
        }
        return 0;
    }
}

void BandSongMgr::GetContentNames(Symbol s, std::vector<Symbol>& vec) const {
    SongMgr::GetContentNames(s, vec);
    int songID = GetSongIDFromShortName(s, false);
    if(mUpgradeMgr->HasUpgrade(songID)){
        const char* contentName = mUpgradeMgr->ContentName(songID);
        MILO_ASSERT(contentName, 0x18C);
        if(!streq(contentName, ".")){
            vec.push_back(contentName);
        }
    }
}

SongMetadata* BandSongMgr::Data(int i) const {
    return SongMgr::Data(i);
}

SongInfo* BandSongMgr::SongAudioData(int i) const {
    SongMetadata* data = Data(i);
    if(!data) return 0;
    else {
        SongInfo* songInfo = data->SongBlock();
        MILO_ASSERT(songInfo, 0x1a0);
        RELEASE(unkc0);
        unkc0 = new DataArraySongInfo(songInfo);
        const char* update = ((BandSongMetadata*)data)->MidiUpdate(); // lol can you actually do this
        if(update) unkc0->AddExtraMidiFile(update, 0);
        if(mUpgradeMgr->HasUpgrade(i)){
            SongUpgradeData* upgrade = mUpgradeMgr->UpgradeData(i);
            MILO_ASSERT(upgrade, 0x1C3);
            unkc0->AddExtraMidiFile(UpgradeMidiFile(i), 0);
        }
        return unkc0;
    }
}

const char* BandSongMgr::SongName(int i) const {
    BandSongMetadata* data = (BandSongMetadata*)Data(i);
    if(data) return data->Title();
    else return gNullStr;
}

const char* BandSongMgr::SongName(Symbol s) const {
    return SongName(GetSongIDFromShortName(s, true));
}

const char* BandSongMgr::UpgradeMidiFile(int i) const {
    const char* file = gNullStr;
    if(mUpgradeMgr->HasUpgrade(i)){
        SongUpgradeData* upgrade = mUpgradeMgr->UpgradeData(i);
        MILO_ASSERT(upgrade, 0x20A);
        file = upgrade->MidiFile();
    }
    return file;
}

const char* BandSongMgr::MidiFile(Symbol s) const {
    SongInfo* info = SongMgr::SongAudioData(s);
    if(info) return FakeSongMgr::MidiFile(info);
    else return gNullStr;
}

const char* BandSongMgr::GetAlbumArtPath(Symbol s) const {
    if(HasSong(s, true)) return SongFilePath(s, "_keep.png", true);
    else return gNullStr;
}

const char* BandSongMgr::SongPath(Symbol s) const {
    return SongMgr::SongAudioData(s)->GetBaseFileName();
}

int BandSongMgr::NumRankTiers(Symbol s) const {
    std::list<SongRanking>::const_iterator r;
    for(r = mSongRankings.begin(); r != mSongRankings.end() && r->mInstrument != s; ++r);
    MILO_ASSERT(r != mSongRankings.end(), 0x289);
    return r->mTierRanges.size();
}

Symbol BandSongMgr::RankTierToken(int i) const {
    Symbol inst = band;
    return SystemConfig(song_groupings, rank)->Array(i + 1)->FindSym(inst);
}