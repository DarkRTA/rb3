/*
    Compile unit: C:\rockband2\band2\src\game\SongMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8008E84C -> 0x80094E00
*/
static class SongMgr gSongMgr; // size: 0x80, address: 0x809777E8
class SongMgr & TheSongMgr; // size: 0x4, address: 0x80A49E68
static char * gPartSyms[4]; // size: 0x10, address: 0x808799F8
static const char * const OLD_DLC_DIR; // size: 0x4, address: 0x80A56390
// Range: 0x8008E84C -> 0x8008E91C
void * SongMgr::SongMgr(class SongMgr * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7SongMgr;
}

struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    const class DataArray * second; // offset 0x4, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x30
public:
    struct SongRanking _M_data; // offset 0x8, size 0x28
};
static class Symbol missing_song_data; // size: 0x4, address: 0x80A49E70
// Range: 0x8008E91C -> 0x8008EA68
void SongMgr::Init(class SongMgr * const this /* r30 */) {
    // References
    // -> static class Symbol missing_song_data;
    // -> class ContentMgr & TheContentMgr;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x8008EA68 -> 0x8008EB0C
void SongMgr::Terminate(class SongMgr * const this /* r31 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x8008EB0C -> 0x8008EB70
void SongMgr::ContentStarted(class SongMgr * const this /* r31 */) {}

// Range: 0x8008EB70 -> 0x8008EC24
void SongMgr::ContentLoaded(class SongMgr * const this /* r29 */, enum ContentLocT location /* r30 */) {
    // Local variables
    class DataLoader * d; // r31
    class DataArray * new_songs; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10DataLoader;
}

static class Symbol rank; // size: 0x4, address: 0x80A49E78
static class Symbol downloaded; // size: 0x4, address: 0x80A49E80
struct SongRankCmp {
    // total size: 0x8
    const class SongMgr & mSongMgr; // offset 0x0, size 0x4
    class Symbol mPart; // offset 0x4, size 0x4
};
struct pair {
    // total size: 0x8
    float first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
// Range: 0x8008EC24 -> 0x8008F410
void SongMgr::ContentDone(class SongMgr * const this /* r25 */) {
    // Local variables
    class vector all_ranked; // r1+0xE0
    int i; // r27
    class Symbol song_name; // r1+0xC4
    unsigned char is_ranked; // r0
    class Symbol instruments[5]; // r1+0xEC
    int i; // r28
    struct SongRanking r; // r1+0x100
    struct SongRankCmp cmp; // r1+0xD8
    class Symbol * s; // r26
    class Symbol song; // r1+0xC0
    class DataArray * rank_groups; // r0
    int num_groups; // r29
    int song; // r30
    int j; // r27
    int group_size; // r26
    class Symbol first_song; // r1+0xBC
    class Symbol last_song; // r1+0xB8
    struct pair range; // r1+0xD0

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std9pair<f,f>;
    // -> struct [anonymous] __RTTI__P6Symbol;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std35_List_node<Q27SongMgr11SongRanking>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> static class Symbol downloaded;
    // -> static class Symbol rank;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std9pair<f,f>; // size: 0x8, address: 0x80879AD8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std35_List_node<Q27SongMgr11SongRanking>; // size: 0x8, address: 0x80879B10
// Range: 0x8008F410 -> 0x8008F460
class Symbol SongMgr::Song() {}

static class Symbol tutorial; // size: 0x4, address: 0x80A49E88
// Range: 0x8008F460 -> 0x8008F51C
unsigned char SongMgr::IsTutorial(const class DataArray * data /* r30 */) {
    // Local variables
    class DataArray * t; // r30

    // References
    // -> static class Symbol tutorial;
}

static class Symbol fake; // size: 0x4, address: 0x80A49E90
// Range: 0x8008F51C -> 0x8008F5D8
unsigned char SongMgr::IsFake(const class DataArray * data /* r30 */) {
    // Local variables
    class DataArray * t; // r30

    // References
    // -> static class Symbol fake;
}

// Range: 0x8008F5D8 -> 0x8008F67C
unsigned char SongMgr::IsPrivate(const class SongMgr * const this /* r28 */, class Symbol & song /* r29 */, const class DataArray * data /* r30 */) {}

static class Symbol downloaded; // size: 0x4, address: 0x80A49E98
// Range: 0x8008F67C -> 0x8008F738
unsigned char SongMgr::IsDownload(const class DataArray * data /* r30 */) {
    // Local variables
    class DataArray * t; // r30

    // References
    // -> static class Symbol downloaded;
}

static class Symbol song_location; // size: 0x4, address: 0x80A49EA0
// Range: 0x8008F738 -> 0x8008F7E8
unsigned char SongMgr::IsOnDisc(const class DataArray * data /* r31 */) {
    // Local variables
    class DataArray * t; // r31
    enum ContentLocT loc; // r0

    // References
    // -> static class Symbol song_location;
}

static class Symbol rank; // size: 0x4, address: 0x80A49EA8
// Range: 0x8008F7E8 -> 0x8008F878
unsigned char SongMgr::IsRanked(const class DataArray * data /* r31 */) {
    // References
    // -> static class Symbol rank;
}

static class Symbol exported; // size: 0x4, address: 0x80A49EB0
// Range: 0x8008F878 -> 0x8008F978
unsigned char SongMgr::IsExported(const class SongMgr * const this /* r28 */, class Symbol & song /* r29 */, const class DataArray * data /* r30 */) {
    // Local variables
    unsigned char ret; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol exported;
}

// Range: 0x8008F978 -> 0x8008FA1C
unsigned char SongMgr::IsUnlockable(const class SongMgr * const this /* r28 */, class Symbol & song /* r29 */, const class DataArray * data /* r30 */) {}

static class Symbol version; // size: 0x4, address: 0x80A49EB8
// Range: 0x8008FA1C -> 0x8008FAA8
int SongMgr::GetVersion(const class DataArray * data /* r31 */) {
    // Local variables
    int ret; // r1+0x10

    // References
    // -> static class Symbol version;
}

// Range: 0x8008FAA8 -> 0x8008FAE8
unsigned char SongMgr::HasSong() {}

static class DataNode & force_song_block; // size: 0x4, address: 0x80A49EC0
static class Symbol song; // size: 0x4, address: 0x80A49EC8
static class Symbol song_vocals; // size: 0x4, address: 0x80A49ED0
static class Symbol vocals; // size: 0x4, address: 0x80A49ED8
// Range: 0x8008FAE8 -> 0x8008FCF8
class DataArray * SongMgr::SongAudioData(const class SongMgr * const this /* r29 */, class Symbol & song_name /* r28 */) {
    // Local variables
    const class DataArray * songData; // r28
    class DataArray * data; // r0

    // References
    // -> class GameMode * TheGameMode;
    // -> class GameConfig * TheGameConfig;
    // -> const char * gNullStr;
    // -> static class Symbol vocals;
    // -> static class Symbol song_vocals;
    // -> static class Symbol song;
    // -> static class DataNode & force_song_block;
}

static class Symbol preview; // size: 0x4, address: 0x80A49EE0
// Range: 0x8008FCF8 -> 0x8008FDC4
void SongMgr::SongPreviewTimes(float & start /* r29 */, float & end /* r30 */) {
    // Local variables
    const class DataArray * data; // r31
    class DataArray * p; // r31

    // References
    // -> static class Symbol preview;
}

static class Symbol name; // size: 0x4, address: 0x80A49EE8
// Range: 0x8008FDC4 -> 0x8008FE5C
char * SongMgr::SongName() {
    // Local variables
    const class DataArray * data; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol name;
}

static class Symbol artist; // size: 0x4, address: 0x80A49EF0
// Range: 0x8008FE5C -> 0x8008FEF4
char * SongMgr::SongArtist() {
    // Local variables
    const class DataArray * data; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol artist;
}

static class Symbol album_name; // size: 0x4, address: 0x80A49EF8
// Range: 0x8008FEF4 -> 0x8008FF94
char * SongMgr::SongAlbum() {
    // Local variables
    const class DataArray * data; // r31
    const class DataArray * a; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol album_name;
}

static class Symbol album_track_number; // size: 0x4, address: 0x80A49F00
// Range: 0x8008FF94 -> 0x80090020
int SongMgr::SongAlbumTrack() {
    // Local variables
    int ret; // r1+0x10
    const class DataArray * data; // r31

    // References
    // -> static class Symbol album_track_number;
}

static class Symbol pack_name; // size: 0x4, address: 0x80A49F08
// Range: 0x80090020 -> 0x800900C0
char * SongMgr::SongPack() {
    // Local variables
    const class DataArray * data; // r31
    const class DataArray * p; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol pack_name;
}

static class Symbol alternate_path; // size: 0x4, address: 0x80A49F10
// Range: 0x800900C0 -> 0x800901D8
char * SongMgr::SongFilePath(const class SongMgr * const this /* r27 */, class Symbol & song /* r29 */, const char * append /* r28 */) {
    // Local variables
    const class DataArray * data; // r30
    const class DataArray * pAltPath; // r30
    const char * songName; // r29

    // References
    // -> const char * gNullStr;
    // -> static class Symbol alternate_path;
}

static class Symbol album_art; // size: 0x4, address: 0x80A49F18
// Range: 0x800901D8 -> 0x800902CC
char * SongMgr::GetAlbumArtPath(const class SongMgr * const this /* r28 */, class Symbol & song /* r29 */) {
    // Local variables
    const class DataArray * data; // r30
    const class DataArray * pArt; // r30

    // References
    // -> const char * gNullStr;
    // -> static class Symbol album_art;
}

// Range: 0x800902CC -> 0x80090300
char * SongMgr::GetPanPath() {}

static class Symbol master; // size: 0x4, address: 0x80A49F20
// Range: 0x80090300 -> 0x80090390
unsigned char SongMgr::IsMaster() {
    // Local variables
    const class DataArray * data; // r31
    unsigned char is_master; // r1+0x8

    // References
    // -> static class Symbol master;
}

static class Symbol mtv_made_famous; // size: 0x4, address: 0x80A49F28
static class Symbol mtv_masters; // size: 0x4, address: 0x80A49F30
// Range: 0x80090390 -> 0x80090498
char * SongMgr::ByLine(const class SongMgr * const this /* r29 */, class Symbol & song /* r31 */) {
    // Local variables
    const class DataArray * data; // r0
    class Symbol token; // r1+0x18

    // References
    // -> const char * gNullStr;
    // -> static class Symbol mtv_masters;
    // -> static class Symbol mtv_made_famous;
}

static class Symbol anim_tempo; // size: 0x4, address: 0x80A49F38
// Range: 0x80090498 -> 0x80090530
int SongMgr::AnimTempo() {
    // Local variables
    const class DataArray * data; // r31

    // References
    // -> static class Symbol anim_tempo;
}

static class Symbol name; // size: 0x4, address: 0x80A49F40
// Range: 0x80090530 -> 0x800905CC
char * SongMgr::SongPath(const class SongMgr * const this /* r30 */, class Symbol & songName /* r31 */) {
    // References
    // -> static class Symbol name;
}

static class Symbol song_scroll_speed; // size: 0x4, address: 0x80A49F48
// Range: 0x800905CC -> 0x80090664
float SongMgr::SongScrollSpeed() {
    // Local variables
    const class DataArray * data; // r31

    // References
    // -> static class Symbol song_scroll_speed;
}

static class Symbol rank; // size: 0x4, address: 0x80A49F50
// Range: 0x80090664 -> 0x80090720
float SongMgr::SongPartRank(class Symbol & part /* r30 */, const class DataArray * data /* r31 */) {
    // Local variables
    class DataArray * rankings; // r0

    // References
    // -> static class Symbol rank;
}

static class Symbol bank; // size: 0x4, address: 0x80A49F58
// Range: 0x80090720 -> 0x800907B8
char * SongMgr::Bank() {
    // Local variables
    const class DataArray * data; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol bank;
}

// Range: 0x800907B8 -> 0x800908A4
int SongMgr::TrackNumOfInstrument(class Symbol & instrument /* r28 */) {
    // Local variables
    const class DataArray * song_array; // r31
    const class DataArray * tracks; // r30
    int i; // r29
}

// Range: 0x800908A4 -> 0x800908BC
unsigned char __eq() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x800908BC -> 0x80090990
class vector & SongMgr::RankedSongs(const class SongMgr * const this /* r29 */, class Symbol & instrument /* r30 */, enum SongType t /* r31 */) {
    // Local variables
    struct _List_iterator r; // r1+0x28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80090990 -> 0x800909EC
int SongMgr::RankTier(const class SongMgr * const this /* r31 */) {}

// Range: 0x800909EC -> 0x80090AF4
int SongMgr::RankTier(const class SongMgr * const this /* r31 */, float ranking /* f31 */) {
    // Local variables
    struct _List_iterator r; // r1+0x24
    int tier; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80090AF4 -> 0x80090BB0
int SongMgr::NumRankTiers(const class SongMgr * const this /* r31 */) {
    // Local variables
    struct _List_iterator r; // r1+0x24

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol song_groupings; // size: 0x4, address: 0x80A49F60
static class Symbol rank; // size: 0x4, address: 0x80A49F68
static class Symbol band; // size: 0x4, address: 0x80A49F70
// Range: 0x80090BB0 -> 0x80090CAC
class Symbol SongMgr::RankTierToken(int tier /* r30 */) {
    // References
    // -> static class Symbol band;
    // -> static class Symbol rank;
    // -> static class Symbol song_groupings;
}

// Range: 0x80090CAC -> 0x80090FA4
void SongMgr::ResetSharedSongs(class SongMgr * const this /* r31 */) {
    // Local variables
    class vector songs; // r1+0x60
    class Symbol * s; // r30
    class Symbol song; // r1+0x5C
}

// Range: 0x80090FA4 -> 0x80091218
void SongMgr::GetRankedSongs(const class SongMgr * const this /* r27 */, class vector & songs /* r28 */, unsigned char only_unlocked /* r29 */, class vector * allowed_parts /* r30 */) {
    // Local variables
    int i; // r31
    class Symbol song; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80091218 -> 0x800912B4
unsigned char SongMgr::HasAllowedPart(const class SongMgr * const this /* r28 */, class Symbol & song /* r29 */, class vector & parts /* r30 */) {
    // Local variables
    class Symbol * p; // r31
}

static class Symbol unlock_song_initial_num; // size: 0x4, address: 0x80A49F78
static class Symbol band; // size: 0x4, address: 0x80A49F80
// Range: 0x800912B4 -> 0x800914C4
unsigned char SongMgr::IsUnlocked(const class SongMgr * const this /* r29 */, class Symbol & song /* r30 */) {
    // Local variables
    int unlock_start_num; // r0

    // References
    // -> static class Symbol band;
    // -> static class Symbol unlock_song_initial_num;
    // -> class GameMode * TheGameMode;
    // -> class ProfileMgr TheProfileMgr;
    // -> unsigned char sUnlockAll;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800914C4 -> 0x8009156C
int SongMgr::Rank(class Symbol & song /* r31 */, class Symbol & instrument /* r4 */) {
    // Local variables
    const class vector & songs; // r0
    const class Symbol * pos; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8009156C -> 0x80091724
void SongMgr::ProcessRemoteSharedSongs(class SongMgr * const this /* r29 */, const class vector & remote_songs /* r30 */) {
    // Local variables
    class Symbol * s; // r31
    class Symbol song; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80091724 -> 0x800917A8
void SongMgr::SyncSharedSongs(class SongMgr * const this /* r30 */, const class vector & sharedSongs /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800917A8 -> 0x80091898
void SongMgr::AddSharedUnlocked(class SongMgr * const this /* r27 */, const class vector & songs /* r28 */) {
    // Local variables
    const class Symbol * s; // r29
    class Symbol song; // r1+0x14
}

// Range: 0x80091898 -> 0x80091930
unsigned char SongMgr::IsSongShared(const class SongMgr * const this /* r29 */, class Symbol & song /* r30 */) {}

static class Symbol none; // size: 0x4, address: 0x80A49F88
static class Symbol guitar; // size: 0x4, address: 0x80A49F90
static class Symbol bass; // size: 0x4, address: 0x80A49F98
// Range: 0x80091930 -> 0x80091EF0
unsigned char SongMgr::HasMissingParts(const class SongMgr * const this /* r25 */, class Symbol & song /* r26 */, enum MissingPartType t /* r27 */, const class MetaPerformer & mp /* r30 */, class BandUserMgr & user_mgr /* r29 */, const class DataArray * data /* r28 */) {
    // Local variables
    class Symbol part_required_by_set; // r1+0x7C
    int num_guitars; // r30
    class vector users; // r1+0x88
    class BandUser * * buIt; // r29
    class Symbol part; // r1+0x78
    class Symbol guitar_parts[2]; // r1+0x80
    int i; // r27

    // References
    // -> const char * gNullStr;
    // -> const char * kAssertStr;
    // -> static class Symbol bass;
    // -> static class Symbol guitar;
    // -> static class Symbol none;
    // -> class Debug TheDebug;
}

// Range: 0x80091EF0 -> 0x80092018
void SongMgr::FindMissingParts(const class SongMgr * const this /* r28 */, class Symbol & song /* r29 */, class DataArray * missing /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> static char * gPartSyms[4];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80092018 -> 0x800923C8
void SongMgr::SendSongsToLeader(class SongMgr * const this /* r29 */) {
    // Local variables
    class vector localPlayers; // r1+0x8C
    class vector unlocked; // r1+0x80
    class LocalSongsMsg msg; // r1+0x98

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class Net TheNet;
    // -> struct [anonymous] __RTTI__P6Symbol;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pi;
    // -> unsigned char gStlAllocNameLookup;
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol version; // size: 0x4, address: 0x80A49FA0
// Range: 0x800923C8 -> 0x80092494
unsigned char SongMgr::CheckVersion(const class DataArray * data /* r31 */) {
    // Local variables
    int v; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol version;
}

static class Symbol tuning_offset_cents; // size: 0x4, address: 0x80A49FA8
// Range: 0x80092494 -> 0x80092534
float SongMgr::TuningOffset() {
    // Local variables
    const class DataArray * data; // r31
    class DataArray * offset; // r31

    // References
    // -> static class Symbol tuning_offset_cents;
}

static class Symbol male; // size: 0x4, address: 0x80A49FB0
static class Symbol vocal_gender; // size: 0x4, address: 0x80A49FB8
// Range: 0x80092534 -> 0x800925F0
class Symbol SongMgr::VocalGender(const class SongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    class Symbol retVal; // r1+0x10
    const class DataArray * data; // r0

    // References
    // -> static class Symbol vocal_gender;
    // -> static class Symbol male;
}

static class Symbol rock; // size: 0x4, address: 0x80A49FC0
static class Symbol genre; // size: 0x4, address: 0x80A49FC8
// Range: 0x800925F0 -> 0x800926AC
class Symbol SongMgr::Genre(const class SongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    class Symbol retVal; // r1+0x10
    const class DataArray * data; // r0

    // References
    // -> static class Symbol genre;
    // -> static class Symbol rock;
}

static class Symbol the00s; // size: 0x4, address: 0x80A49FD0
static class Symbol decade; // size: 0x4, address: 0x80A49FD8
// Range: 0x800926AC -> 0x80092768
class Symbol SongMgr::Decade(const class SongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    class Symbol retVal; // r1+0x10
    const class DataArray * data; // r0

    // References
    // -> static class Symbol decade;
    // -> static class Symbol the00s;
}

static class Symbol year_released; // size: 0x4, address: 0x80A49FE0
// Range: 0x80092768 -> 0x80092800
int SongMgr::YearReleased(const class SongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    int year; // r1+0x10
    const class DataArray * data; // r0

    // References
    // -> static class Symbol year_released;
}

static class Symbol base_points; // size: 0x4, address: 0x80A49FE8
// Range: 0x80092800 -> 0x80092898
int SongMgr::BasePoints(const class SongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    int points; // r1+0x10
    const class DataArray * data; // r0

    // References
    // -> static class Symbol base_points;
}

static class Symbol video_venues; // size: 0x4, address: 0x80A49FF0
// Range: 0x80092898 -> 0x80092944
class DataArray * SongMgr::GetVideoVenues(const class SongMgr * const this /* r30 */, class Symbol & song /* r31 */) {
    // Local variables
    const class DataArray * data; // r0
    const class DataArray * videoVenues; // r31

    // References
    // -> static class Symbol video_venues;
}

static class Symbol name; // size: 0x4, address: 0x80A49FF8
static class Symbol midi_file; // size: 0x4, address: 0x80A4A000
// Range: 0x80092944 -> 0x80092B24
void SongMgr::AddPathInfo(class DataArray * song_data /* r31 */, const char * sPath /* r29 */) {
    // Local variables
    char sTmp[257]; // r1+0x20
    class DataArray * a; // r29
    const char * newName; // r0
    const char * newMidi; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol midi_file;
    // -> static class Symbol name;
}

// Range: 0x80092B24 -> 0x80092B94
void SongMgr::AddSongData(class SongMgr * const this /* r29 */, class DataArray * new_songs /* r30 */, enum ContentLocT location /* r31 */) {
    // Local variables
    const char * sPath; // r0
}

static class Symbol song; // size: 0x4, address: 0x80A4A008
static class Symbol song_vocals; // size: 0x4, address: 0x80A4A010
static class Symbol version; // size: 0x4, address: 0x80A4A018
static class Symbol tutorial; // size: 0x4, address: 0x80A4A020
static class Symbol fake; // size: 0x4, address: 0x80A4A028
static class Symbol format; // size: 0x4, address: 0x80A4A030
static class Symbol alternate_path; // size: 0x4, address: 0x80A4A038
static class Symbol format; // size: 0x4, address: 0x80A4A040
static class Symbol song_location; // size: 0x4, address: 0x80A4A048
static class Symbol exported; // size: 0x4, address: 0x80A4A050
static class Symbol fake; // size: 0x4, address: 0x80A4A058
static class Symbol downloaded; // size: 0x4, address: 0x80A4A060
// Range: 0x80092B94 -> 0x800937A4
void SongMgr::AddSongData(class SongMgr * const this /* r28 */, class DataArray * new_songs /* r29 */, const char * sPath /* r30 */, enum ContentLocT location /* r31 */) {
    // Local variables
    int first_song; // r22
    int newSize; // r21
    int songPos; // r20
    int i; // r19
    class DataArray * new_song; // r18
    class DataArray * tut; // r17
    class DataArray * f; // r23
    class DataArray * release_fmt; // r17
    class DataArray * missing_data; // r24
    class DataArray * newSongArray; // r17
    class DataArray * fmt; // r17
    class DataArray * song_loc_array; // r17
    class DataArray * new_song_data; // r23
    class DataArray * new_song_vocals_data; // r17
    unsigned char isExported; // r1+0x8
    unsigned char missing_part; // r17
    int i; // r23
    int finalSize; // r4

    // References
    // -> static class Symbol downloaded;
    // -> static class Symbol fake;
    // -> static char * gPartSyms[4];
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Symbol exported;
    // -> static class Symbol song_location;
    // -> static class Symbol format;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static const char * const OLD_DLC_DIR;
    // -> static class Symbol alternate_path;
    // -> static class Symbol format;
    // -> static class Symbol fake;
    // -> static class Symbol tutorial;
    // -> class Debug TheDebug;
    // -> static class Symbol version;
    // -> static class Symbol song_vocals;
    // -> static class Symbol song;
}

// Range: 0x800937A4 -> 0x800937EC
void SongMgr::AddSongs(class SongMgr * const this /* r31 */) {}

static class Symbol band; // size: 0x4, address: 0x80A4A068
// Range: 0x800937EC -> 0x80093B18
void SongMgr::GetValidSongs(const class SongMgr * const this /* r26 */, const class MetaPerformer & mp /* r27 */, class BandUserMgr & bum /* r28 */, enum MissingPartType mpt /* r29 */, class vector & valid_songs /* r30 */, float min_band_rank /* f30 */, float max_band_rank /* f31 */) {
    // Local variables
    class vector songs; // r1+0x5C
    class Symbol * s; // r31
    class Symbol song; // r1+0x58

    // References
    // -> static class Symbol band;
}

// Range: 0x80093B18 -> 0x80093D80
class Symbol SongMgr::GetRandomSong(const class SongMgr * const this /* r25 */, const class MetaPerformer & mp /* r26 */, class BandUserMgr & bum /* r27 */, enum MissingPartType mpt /* r28 */, unsigned char only_unlocked /* r29 */, float min_band /* f30 */, float max_band /* f31 */) {
    // Local variables
    class vector valid_songs; // r1+0x30
    class Symbol random; // r1+0x2C

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80093D80 -> 0x80093E3C
class TextStream & __ls(class TextStream & d /* r29 */, const class vector & c /* r30 */) {
    // Local variables
    const class Symbol * t; // r31
}

// Range: 0x80093E3C -> 0x80093E54
unsigned char SongMgr::ToggleRandomSongDebug() {}

// Range: 0x80093E54 -> 0x80093E84
void SongMgr::AddRecentSong() {}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x80093E84 -> 0x80093F34
class DataArray * SongMgr::Data() {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x1C
}

// Range: 0x80093F34 -> 0x80093F74
class DataArray * SongMgr::Data() {}

// Range: 0x80093F74 -> 0x8009401C
class DataNode SongMgr::OnHasMissingParts(class SongMgr * const this /* r29 */, class DataArray * a /* r30 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol missing_part_type; // size: 0x4, address: 0x80A4A070
// Range: 0x8009401C -> 0x80094130
class DataNode SongMgr::OnGetRandomSong() {
    // Local variables
    enum MissingPartType mpt; // r31

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SongMgr & TheSongMgr;
    // -> static class Symbol missing_part_type;
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameConfig * TheGameConfig;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A078
static class Symbol _s; // size: 0x4, address: 0x80A4A080
static class Symbol _s; // size: 0x4, address: 0x80A4A088
static class Symbol _s; // size: 0x4, address: 0x80A4A090
static class Symbol _s; // size: 0x4, address: 0x80A4A098
static class Symbol _s; // size: 0x4, address: 0x80A4A0A0
static class Symbol _s; // size: 0x4, address: 0x80A4A0A8
static class Symbol _s; // size: 0x4, address: 0x80A4A0B0
static class Symbol _s; // size: 0x4, address: 0x80A4A0B8
static class Symbol _s; // size: 0x4, address: 0x80A4A0C0
static class Symbol _s; // size: 0x4, address: 0x80A4A0C8
static class Symbol _s; // size: 0x4, address: 0x80A4A0D0
static class Symbol _s; // size: 0x4, address: 0x80A4A0D8
static class Symbol _s; // size: 0x4, address: 0x80A4A0E0
static class Symbol _s; // size: 0x4, address: 0x80A4A0E8
static class Symbol _s; // size: 0x4, address: 0x80A4A0F0
static class Symbol _s; // size: 0x4, address: 0x80A4A0F8
static class Symbol _s; // size: 0x4, address: 0x80A4A100
static class Symbol _s; // size: 0x4, address: 0x80A4A108
static class Symbol _s; // size: 0x4, address: 0x80A4A110
static class Symbol _s; // size: 0x4, address: 0x80A4A118
static class Symbol _s; // size: 0x4, address: 0x80A4A120
static class Symbol _s; // size: 0x4, address: 0x80A4A128
static class Symbol _s; // size: 0x4, address: 0x80A4A130
// Range: 0x80094130 -> 0x80094D68
class DataNode SongMgr::Handle(class SongMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x6C
    class MessageTimer _mt; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode _n; // r1+0x70

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xE8
} __vt__7SongMgr; // size: 0xE8, address: 0x8087A190
struct {
    // total size: 0x8
} __RTTI__7SongMgr; // size: 0x8, address: 0x8087A2A0
struct {
    // total size: 0x40
} __vt__Q210ContentMgr8Callback; // size: 0x40, address: 0x8087A2A8
struct {
    // total size: 0x8
} __RTTI__Q210ContentMgr8Callback; // size: 0x8, address: 0x8087A300
struct {
    // total size: 0x8
} __RTTI__10DataLoader; // size: 0x8, address: 0x8087A350
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std59_Rb_tree_node<Q211stlpmtx_std27pair<C6Symbol,PC9DataArray>>; // size: 0x8, address: 0x8087A3F0
// Range: 0x80094D68 -> 0x80094DB8
static void __sinit_\SongMgr_cpp() {
    // References
    // -> class SongMgr & TheSongMgr;
    // -> static class SongMgr gSongMgr;
}


