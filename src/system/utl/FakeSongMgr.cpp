#include "utl/FakeSongMgr.h"
#include "utl/MakeString.h"
#include "os/File.h"
#include "os/System.h"
#include "utl/SongInfoCopy.h"

FakeSongMgr* TheFakeSongMgr = 0;
DataArray* gSongs = 0;

static const char* const unusedFakeSongMgrStrings[] = {
    "fake_song_mgr_init",
    "%s/songs/song*.dt?",
    "%s/songs_download/song*.dt?",
    "%s/songs_download_rb3/song*.dt?",
    "fake_songmgr"
};

DataArray* FakeSongMgr::GetSongConfig(Symbol sym){
    return gSongs->FindArray(sym, true)->FindArray("song", true);
}

static const char* const unusedFakeSongMgrNameStr = "name";

const char* FakeSongMgr::GetPath(const SongInfo* sinfo, const char* cc){
    const char* sname = sinfo->GetBaseFileName();
    if(*cc == '\0' || *cc == '.')
        return MakeString("%s%s", sname, cc);
    else {
        return MakeString("%s/%s", FileGetPath(sname, 0), cc);
    }
}

const char* FakeSongMgr::MidiFullPath(const SongInfo* sinfo){
    return FileMakePath(FileRoot(), GetPath(sinfo, ".mid"), 0);
}

const char* FakeSongMgr::MidiFile(const SongInfo* sinfo){
    return GetPath(sinfo, ".mid");
}

static const char* const unusedFakeSongMgrStrings2[] = {
    "",
    "%s(%d): %s unhandled msg: %s",
    __FILE__
};
