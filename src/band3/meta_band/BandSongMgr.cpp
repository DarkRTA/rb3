#include "meta_band/BandSongMgr.h"
#include "meta_band/BandSongMetadata.h"
#include "obj/Dir.h"
#include "game/GameMode.h"
#include "utl/FakeSongMgr.h"
#include "utl/Symbols.h"

BandSongMgr gSongMgr;
BandSongMgr* TheSongMgr = &gSongMgr;

bool BandSongMgr::sFakeSongsAllowed;

BandSongMgr::BandSongMgr() : unkc0(0), unk124(1), mUpgradeMgr(0), mLicenseMgr(0), mMaxSongCount(-1), unk13c(0), unk140(0) {
    ClearAndShrink(mContentAltDirs);
    TheBaseSongManger = this;
}

void BandSongMgr::Init(){
    SongMgr::Init();
    SetName("song_mgr", ObjectDir::sMainDir);
    TheContentMgr->RegisterCallback(this, false);
    mSongNameLookup.clear();
    mSongIDLookup.clear();
    DataArray* cfg = SystemConfig(song_mgr);
    DataArray* altarr = cfg->FindArray(alt_dirs, false);
    if(altarr){
        for(int i = 1; i < altarr->Size(); i++){
            const char* str = altarr->Array(i)->Str(0);
            if(strlen(str) != 0){
                mContentAltDirs.push_back(String(str));
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
    ClearAndShrink(mContentAltDirs);
    TheContentMgr->UnregisterCallback(this, false);
    mSongNameLookup.clear();
    mSongIDLookup.clear();
}

void BandSongMgr::ContentMounted(const char* c1, const char* c2){
    SongMgr::ContentMounted(c1, c2);
}

const char* BandSongMgr::ContentDir(){ return "songs"; }

Symbol BandSongMgr::GetShortNameFromSongID(int songID, bool fail) const {
    MILO_ASSERT(songID != kSongID_Invalid && songID != kSongID_Any && songID != kSongID_Random, 0x156);
    std::map<int, Symbol>::const_iterator it = mSongNameLookup.find(songID);
    if(it != mSongNameLookup.end()) return it->second;
    it = mExtraSongIDMap.find(songID);
    if(it != mExtraSongIDMap.end()) return it->second;
    if(fail){
        MILO_FAIL("Couldn't find song short name for SONG_ID %d", songID);
    }
    return gNullStr;
}

int BandSongMgr::GetSongIDFromShortName(Symbol shortName, bool fail) const {
    std::map<Symbol, int>::const_iterator it = mSongIDLookup.find(shortName);
    if(it != mSongIDLookup.end()){
        MILO_ASSERT(it->second != kSongID_Invalid, 0x16D);
        return it->second;
    }
    else {
        for(std::map<int, Symbol>::const_iterator it = mExtraSongIDMap.begin(); it != mExtraSongIDMap.end(); ++it){
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

void BandSongMgr::GetRankedSongs(std::vector<int>& vec, bool b1, bool b2) const {
    if(b1){
        TheGameMode->Property("demos_allowed", true)->Int();
    }
    vec.clear();
    for(std::set<int>::const_iterator it = mAvailableSongs.begin(); it != mAvailableSongs.end(); ++it){
        int cur = *it;
        BandSongMetadata* data = (BandSongMetadata*)Data(cur);
        if(data->IsRanked() && !data->IsPrivate() && (b2 || !IsRestricted(cur))){
            vec.push_back(*it);
        }
    }
}

int BandSongMgr::GetValidSongCount(const std::map<int, SongMetadata*>& songs) const {
    int count = 0;
    for(std::map<int, SongMetadata*>::const_iterator it = songs.begin(); it != songs.end(); ++it){
        BandSongMetadata* data = (BandSongMetadata*)it->second;
        if(data && data->IsRanked() && !data->IsPrivate()) count++;
    }
    return count;
}

bool BandSongMgr::GetFakeSongsAllowed(){ return sFakeSongsAllowed; }
void BandSongMgr::SetFakeSongsAllowed(bool b){ sFakeSongsAllowed = b; }

void BandSongMgr::CheatToggleMaxSongCount(){
    DataArray* cfg = SystemConfig(song_mgr);
    int max = cfg->FindInt(max_song_count);
    int max_debug = cfg->FindInt(max_song_count_debug);
    if(mMaxSongCount == max) max = max_debug;
    mMaxSongCount = max;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandSongMgr)
    HANDLE_EXPR(has_song, HasSong(_msg->Sym(2), true))
    HANDLE_EXPR(song_path, SongPath(_msg->Sym(2)))
    HANDLE_EXPR(song_file_path, SongFilePath(_msg->Sym(2), _msg->Str(3), false))
    HANDLE_EXPR(song_name, SongName(_msg->Sym(2)))
    HANDLE_EXPR(upgrade_midi_file, UpgradeMidiFile(GetSongIDFromShortName(_msg->Sym(2), true)))
    HANDLE_EXPR(get_meta_data, Data(GetSongIDFromShortName(_msg->Sym(2), true)))
    HANDLE_EXPR(rank_tier, RankTier(_msg->Float(2), _msg->Sym(3)))
    HANDLE_EXPR(rank_tier_for_song, RankTier(((BandSongMetadata*)Data(GetSongIDFromShortName(_msg->Sym(2), true)))->Rank(_msg->Sym(3)), _msg->Sym(3)))
    HANDLE_EXPR(num_rank_tiers, NumRankTiers(_msg->Sym(2)))
    HANDLE_EXPR(rank_tier_token, RankTierToken(_msg->Int(2)))
    HANDLE_EXPR(num_vocal_parts, GetNumVocalParts(_msg->Sym(2)))
    HANDLE_ACTION(add_recent_song, AddRecentSong(GetSongIDFromShortName(_msg->Sym(2), true)))
    HANDLE_EXPR(part_plays_in_song, ((BandSongMetadata*)Data(GetSongIDFromShortName(_msg->Sym(2), true)))->HasPart(_msg->Sym(3), false))
    HANDLE_EXPR(mute_win_cues, ((BandSongMetadata*)Data(GetSongIDFromShortName(_msg->Sym(2), true)))->MuteWinCues())
    HANDLE_EXPR(midi_file, MidiFile(_msg->Sym(2)))
    HANDLE_EXPR(is_demo, IsDemo(_msg->Int(2)))
    HANDLE_EXPR(has_upgrade, GetUpgradeData(GetSongIDFromShortName(_msg->Sym(2), true)) != 0)
    HANDLE_EXPR(has_license, HasLicense(_msg->Sym(2)))
    HANDLE_EXPR(get_fake_songs_allowed, GetFakeSongsAllowed())
    HANDLE_ACTION(set_fake_songs_allowed, SetFakeSongsAllowed(_msg->Int(2)))
    HANDLE_ACTION(sync_shared_songs, SyncSharedSongs())
    HANDLE_EXPR(get_max_song_count, GetMaxSongCount())
    HANDLE_ACTION(cheat_toggle_max_song_count, CheatToggleMaxSongCount())
    HANDLE_SUPERCLASS(SongMgr)
    HANDLE_CHECK(0x6DF)
END_HANDLERS
#pragma pop
