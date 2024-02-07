/*
    Compile unit: C:\rockband2\band2\src\meta\SongOffer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80169BBC -> 0x8016B064
*/
class Symbol song; // size: 0x4, address: 0x80A4C61C
static class Symbol missing_part_type; // size: 0x4, address: 0x80A4C624
// Range: 0x80169BBC -> 0x80169D7C
void * SongOffer::SongOffer(class SongOffer * const this /* r30 */) {
    // Local variables
    enum MissingPartType mpt; // r31

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol missing_part_type;
    // -> class SongMgr & TheSongMgr;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9SongOffer;
}

static class Symbol name; // size: 0x4, address: 0x80A4C62C
static class Symbol song; // size: 0x4, address: 0x80A4C634
// Range: 0x80169D7C -> 0x80169E98
char * SongOffer::OfferName(const class SongOffer * const this /* r29 */) {
    // References
    // -> static class Symbol song;
    // -> static class Symbol name;
}

static class Symbol master; // size: 0x4, address: 0x80A4C63C
// Range: 0x80169E98 -> 0x80169F40
unsigned char SongOffer::IsCover(const class SongOffer * const this /* r31 */) {
    // References
    // -> static class Symbol master;
}

static class Symbol download; // size: 0x4, address: 0x80A4C644
static class Symbol rb1_icon; // size: 0x4, address: 0x80A4C64C
static class Symbol rb2_icon; // size: 0x4, address: 0x80A4C654
// Range: 0x80169F40 -> 0x8016A010
class Symbol SongOffer::GetIcon(const class SongOffer * const this /* r30 */) {
    // References
    // -> static class Symbol rb2_icon;
    // -> static class Symbol rb1_icon;
    // -> static class Symbol download;
}

static class Symbol genre; // size: 0x4, address: 0x80A4C65C
// Range: 0x8016A010 -> 0x8016A08C
class Symbol SongOffer::Genre(const class SongOffer * const this /* r31 */) {
    // References
    // -> static class Symbol genre;
}

static class Symbol decade; // size: 0x4, address: 0x80A4C664
// Range: 0x8016A08C -> 0x8016A108
class Symbol SongOffer::Decade(const class SongOffer * const this /* r31 */) {
    // References
    // -> static class Symbol decade;
}

static class Symbol artist; // size: 0x4, address: 0x80A4C66C
// Range: 0x8016A108 -> 0x8016A180
char * SongOffer::Artist(const class SongOffer * const this /* r31 */) {
    // References
    // -> static class Symbol artist;
}

static class Symbol year_released; // size: 0x4, address: 0x80A4C674
// Range: 0x8016A180 -> 0x8016A1F8
int SongOffer::YearReleased(const class SongOffer * const this /* r31 */) {
    // References
    // -> static class Symbol year_released;
}

static class Symbol album_track_number; // size: 0x4, address: 0x80A4C67C
// Range: 0x8016A1F8 -> 0x8016A2D0
int SongOffer::AlbumTrackNum(const class SongOffer * const this /* r31 */) {
    // Local variables
    class DataArray * atn; // r0

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol album_track_number;
}

static class Symbol album_name; // size: 0x4, address: 0x80A4C684
// Range: 0x8016A2D0 -> 0x8016A370
char * SongOffer::AlbumName(const class SongOffer * const this /* r31 */) {
    // References
    // -> static class Symbol album_name;
}

// Range: 0x8016A370 -> 0x8016A3C8
class String SongOffer::AlbumArtPath() {
    // References
    // -> class SongMgr & TheSongMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4C68C
static class Symbol _s; // size: 0x4, address: 0x80A4C694
static class Symbol _s; // size: 0x4, address: 0x80A4C69C
static class Symbol _s; // size: 0x4, address: 0x80A4C6A4
static class Symbol _s; // size: 0x4, address: 0x80A4C6AC
static class Symbol _s; // size: 0x4, address: 0x80A4C6B4
static class Symbol _s; // size: 0x4, address: 0x80A4C6BC
static class Symbol _s; // size: 0x4, address: 0x80A4C6C4
static class Symbol _s; // size: 0x4, address: 0x80A4C6CC
static class Symbol _s; // size: 0x4, address: 0x80A4C6D4
static class Symbol _s; // size: 0x4, address: 0x80A4C6DC
// Range: 0x8016A3C8 -> 0x8016B064
class DataNode SongOffer::Handle(class SongOffer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x60
    class MessageTimer _mt; // r1+0x80
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x68
} __vt__9SongOffer; // size: 0x68, address: 0x808987C0
struct {
    // total size: 0x8
} __RTTI__9SongOffer; // size: 0x8, address: 0x80898850

