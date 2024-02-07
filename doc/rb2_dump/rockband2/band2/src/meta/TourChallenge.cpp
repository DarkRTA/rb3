/*
    Compile unit: C:\rockband2\band2\src\meta\TourChallenge.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801B791C -> 0x801BAC34
*/
class Symbol band; // size: 0x4, address: 0x80A4D7C4
// Range: 0x801B791C -> 0x801B79C4
void * TourChallengeEvent::TourChallengeEvent(class TourChallengeEvent * const this /* r30 */, class Symbol & event_name /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__18TourChallengeEvent;
}

static class Symbol diff_tier; // size: 0x4, address: 0x80A4D7CC
static class Symbol prereqs; // size: 0x4, address: 0x80A4D7D4
static class Symbol any; // size: 0x4, address: 0x80A4D7DC
static class Symbol all; // size: 0x4, address: 0x80A4D7E4
static class Symbol min_players; // size: 0x4, address: 0x80A4D7EC
static class Symbol required_part; // size: 0x4, address: 0x80A4D7F4
static class Symbol guitar; // size: 0x4, address: 0x80A4D7FC
static class Symbol bass; // size: 0x4, address: 0x80A4D804
static class Symbol drum; // size: 0x4, address: 0x80A4D80C
static class Symbol vocals; // size: 0x4, address: 0x80A4D814
static class Symbol venues; // size: 0x4, address: 0x80A4D81C
static class Symbol cover_art; // size: 0x4, address: 0x80A4D824
static class Symbol back_art; // size: 0x4, address: 0x80A4D82C
static class Symbol show_list_name; // size: 0x4, address: 0x80A4D834
static class Symbol auto_genre; // size: 0x4, address: 0x80A4D83C
static class Symbol auto_decade; // size: 0x4, address: 0x80A4D844
static class Symbol achievement; // size: 0x4, address: 0x80A4D84C
// Range: 0x801B79C4 -> 0x801B8384
void * TourChallengeEvent::TourChallengeEvent(class TourChallengeEvent * const this /* r26 */, class DataArray * d /* r27 */) {
    // Local variables
    class DataArray * p; // r29
    int i; // r28
    struct ChallengePrereq cp; // r1+0xD8
    int j; // r25
    class DataArray * v; // r25
    int i; // r28
    class DataArray * gen; // r25
    class DataArray * dec; // r25

    // References
    // -> static class Symbol achievement;
    // -> static class Symbol auto_decade;
    // -> static class Symbol auto_genre;
    // -> static class Symbol show_list_name;
    // -> static class Symbol back_art;
    // -> static class Symbol cover_art;
    // -> static class Symbol venues;
    // -> static class Symbol vocals;
    // -> static class Symbol drum;
    // -> static class Symbol bass;
    // -> static class Symbol guitar;
    // -> static class Symbol required_part;
    // -> static class Symbol min_players;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<15ChallengePrereq>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class Symbol all;
    // -> static class Symbol any;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol prereqs;
    // -> static class Symbol diff_tier;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__18TourChallengeEvent;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std29_List_node<15ChallengePrereq>; // size: 0x8, address: 0x808A0FA8
// Range: 0x801B8384 -> 0x801B83E0
char * TourChallengeEvent::DisplayName(const class TourChallengeEvent * const this /* r31 */) {}

static class Symbol tour_challenge_description; // size: 0x4, address: 0x80A4D854
static class Symbol tour_challenge_description_singular; // size: 0x4, address: 0x80A4D85C
// Range: 0x801B83E0 -> 0x801B8518
char * TourChallengeEvent::Description(const class TourChallengeEvent * const this /* r30 */) {
    // References
    // -> static class Symbol tour_challenge_description_singular;
    // -> static class Symbol tour_challenge_description;
}

static class Symbol band; // size: 0x4, address: 0x80A4D864
// Range: 0x801B8518 -> 0x801B8624
int TourChallengeEvent::DiffTier(const class TourChallengeEvent * const this /* r30 */) {
    // Local variables
    int max_tier; // r1+0x14
    int i; // r31

    // References
    // -> static class Symbol band;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol band; // size: 0x4, address: 0x80A4D86C
static class Symbol tour_challenge_botb_tier; // size: 0x4, address: 0x80A4D874
// Range: 0x801B8624 -> 0x801B8700
class Symbol TourChallengeEvent::TierName(const class TourChallengeEvent * const this /* r29 */) {
    // Local variables
    int diff_tier; // r30

    // References
    // -> static class Symbol tour_challenge_botb_tier;
    // -> static class Symbol band;
}

// Range: 0x801B8700 -> 0x801B8708
class list & TourChallengeEvent::Prereqs() {}

// Range: 0x801B8708 -> 0x801B8710
int TourChallengeEvent::MinPlayers() {}

// Range: 0x801B8710 -> 0x801B8770
class Symbol TourChallengeEvent::VenueVariant(const class TourChallengeEvent * const this /* r31 */) {}

// Range: 0x801B8770 -> 0x801B8778
char * TourChallengeEvent::CoverArt() {}

// Range: 0x801B8778 -> 0x801B8780
char * TourChallengeEvent::BackArt() {}

// Range: 0x801B8780 -> 0x801B8788
unsigned char TourChallengeEvent::ShowListName() {}

// Range: 0x801B8788 -> 0x801B8790
enum ChallengeEventType TourChallengeEvent::ChallengeType() {}

// Range: 0x801B8790 -> 0x801B87BC
unsigned char TourChallengeEvent::AutoSongs() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801B87BC -> 0x801B87C4
void TourChallengeEvent::SetDiffTier() {}

// Range: 0x801B87C4 -> 0x801B87CC
void TourChallengeEvent::SetShowListName() {}

// Range: 0x801B87CC -> 0x801B87D4
void TourChallengeEvent::SetChallengeType() {}

// Range: 0x801B87D4 -> 0x801B8D28
void TourChallengeEvent::RefreshAutoSongs(class TourChallengeEvent * const this /* r28 */, const class vector & all_songs /* r29 */, int max_set_size /* r30 */) {
    // Local variables
    const class Symbol * s; // r31
    unsigned char missing; // r26
    int i; // r27
    const class Symbol * s; // r31
    unsigned char missing; // r26
    int i; // r27
    int year_released; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801B8D28 -> 0x801B8E3C
void TourChallengeEvent::SortAndLimitSongs(class TourChallengeEvent * const this /* r30 */, int max_set_size /* r31 */) {}

struct AutoSongCmp {
    // total size: 0x8
    const class SongMgr & mSongMgr; // offset 0x0, size 0x4
    enum ChallengeEventType mChallengeType; // offset 0x4, size 0x4
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801B8E3C -> 0x801B8FCC
void TourChallengeEvent::AddPrereq(class TourChallengeEvent * const this /* r30 */, unsigned char all /* r6 */) {
    // Local variables
    struct ChallengePrereq cp; // r1+0x58

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std29_List_node<15ChallengePrereq>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x801B8FCC -> 0x801B8FD0
void TourChallengeEvent::Validate() {}

static class Symbol _s; // size: 0x4, address: 0x80A4D87C
static class Symbol _s; // size: 0x4, address: 0x80A4D884
// Range: 0x801B8FD0 -> 0x801B943C
class DataNode TourChallengeEvent::Handle(class TourChallengeEvent * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol auto_min_songs; // size: 0x4, address: 0x80A4D88C
static class Symbol challenges; // size: 0x4, address: 0x80A4D894
// Range: 0x801B943C -> 0x801B9578
void * TourChallenge::TourChallenge(class TourChallenge * const this /* r27 */, const class SongMgr & sm /* r28 */, class DataArray * cfg /* r29 */) {
    // Local variables
    class DataArray * c; // r30
    int i; // r29

    // References
    // -> static class Symbol challenges;
    // -> static class Symbol auto_min_songs;
}

// Range: 0x801B9578 -> 0x801B963C
void * TourChallenge::~TourChallenge(class TourChallenge * const this /* r30 */) {}

// Range: 0x801B963C -> 0x801B9740
void TourChallenge::TierChallenges(const class TourChallenge * const this /* r28 */, class vector & tier /* r29 */, int diff_tier /* r30 */) {
    // Local variables
    class TourChallengeEvent * const * c; // r31
    class TourChallengeEvent * e; // r1+0x18
}

// Range: 0x801B9740 -> 0x801B9780
unsigned char __eq(class Symbol & rhs /* r31 */) {}

// Range: 0x801B9780 -> 0x801B97D0
class TourChallengeEvent * TourChallenge::FindChallenge(const class TourChallenge * const this /* r31 */) {
    // Local variables
    class TourChallengeEvent * const * c; // r0
}

// Range: 0x801B97D0 -> 0x801B97D8
class vector & TourChallenge::AllChallenges() {}

static class Symbol band; // size: 0x4, address: 0x80A4D89C
// Range: 0x801B97D8 -> 0x801B9838
int TourChallenge::NumChallengeTiers(const class TourChallenge * const this /* r31 */) {
    // References
    // -> static class Symbol band;
}

// Range: 0x801B9838 -> 0x801B9908
void TourChallenge::GetLiveBattles(const class TourChallenge * const this /* r29 */, class list & battles /* r30 */) {
    // Local variables
    class TourChallengeEvent * const * c; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x801B9908 -> 0x801B99D4
void TourChallenge::AddChallenge(class TourChallenge * const this /* r31 */, class TourChallengeEvent * tce /* r1+0x8 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x801B99D4 -> 0x801B9BD8
void TourChallenge::DisableBattles(class TourChallenge * const this /* r29 */, const class list * shared /* r30 */) {
    // Local variables
    class TourChallengeEvent * * c; // r28
    class TourChallengeEvent * * c; // r31
}

// Range: 0x801B9BD8 -> 0x801B9D10
void TourChallenge::ClearBattles(class TourChallenge * const this /* r30 */) {
    // Local variables
    class TourChallengeEvent * * c; // r31
    class TourChallengeEvent * * c; // r31
}

// Range: 0x801B9E18 -> 0x801B9F50
void TourChallenge::Clear(class TourChallenge * const this /* r29 */) {}

// Range: 0x801B9F50 -> 0x801B9F7C
static unsigned char __eq() {}

// Range: 0x801B9F7C -> 0x801B9FA8
static unsigned char __eq() {}

// Range: 0x801B9FA8 -> 0x801B9FD4
static unsigned char __eq() {}

// Range: 0x801B9FD4 -> 0x801BA02C
static void Tokenize(const char * in /* r0 */, class String & out /* r31 */) {}

static class Symbol tour_challenge_auto_album; // size: 0x4, address: 0x80A4D8A4
static class Symbol tour_challenge_auto_artist; // size: 0x4, address: 0x80A4D8AC
static class Symbol tour_challenge_auto_pack; // size: 0x4, address: 0x80A4D8B4
class list : public _List_base {
    // total size: 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct Artist {
    // total size: 0x24
    const char * mArtist; // offset 0x0, size 0x4
    class String mArtistToken; // offset 0x4, size 0xC
    class vector mSongs; // offset 0x10, size 0xC
    class list mAlbums; // offset 0x1C, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct Album {
    // total size: 0x10
    const char * mAlbum; // offset 0x0, size 0x4
    class vector mSongs; // offset 0x4, size 0xC
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct Pack {
    // total size: 0x14
    const char * mPack; // offset 0x0, size 0x4
    const char * mArtist; // offset 0x4, size 0x4
    class vector mSongs; // offset 0x8, size 0xC
};
// Range: 0x801BA02C -> 0x801BAA48
void TourChallenge::RefreshAutos(class TourChallenge * const this /* r28 */, int max_set_size /* r29 */) {
    // Local variables
    class vector songs; // r1+0x168
    class TourChallengeEvent * * c; // r27
    class list artists; // r1+0xE0
    class list packs; // r1+0xD8
    const class Symbol * s; // r30
    unsigned char missing; // r27
    int i; // r26
    const char * artist; // r1+0xD0
    struct _List_iterator ait; // r1+0xCC
    struct Artist new_artist; // r1+0x188
    const char * album; // r1+0xC8
    struct _List_iterator a; // r1+0xC4
    struct Album new_album; // r1+0x158
    const char * pack; // r1+0xC0
    struct _List_iterator p; // r1+0xBC
    struct Pack new_pack; // r1+0x174
    struct _List_iterator a; // r1+0xB8
    struct _List_iterator al; // r1+0xB4
    class String album_token; // r1+0x148
    class Symbol event_name; // r1+0xB0
    class String display_name; // r1+0x13C
    class Symbol * s; // r26
    struct _List_iterator a; // r1+0xAC
    class Symbol event_name; // r1+0xA8
    class String display_name; // r1+0x130
    struct _List_iterator p; // r1+0xA4
    class String pack_token; // r1+0x124
    class Symbol event_name; // r1+0xA0
    class String display_name; // r1+0x118

    // References
    // -> static class Symbol tour_challenge_auto_pack;
    // -> static class Symbol tour_challenge_auto_artist;
    // -> static class Symbol tour_challenge_auto_album;
    // -> const char * gNullStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x2C
public:
    struct Artist _M_data; // offset 0x8, size 0x24
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    struct Pack _M_data; // offset 0x8, size 0x14
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct Album _M_data; // offset 0x8, size 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std49_List_node<Q227@unnamed@TourChallenge_cpp@5Album>; // size: 0x8, address: 0x808A1200
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std50_List_node<Q227@unnamed@TourChallenge_cpp@6Artist>; // size: 0x8, address: 0x808A1248
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std48_List_node<Q227@unnamed@TourChallenge_cpp@4Pack>; // size: 0x8, address: 0x808A1290
static class Symbol screen; // size: 0x4, address: 0x80A4D8BC
// Range: 0x801BAA48 -> 0x801BAC34
void TourChallenge::Validate(const class TourChallenge * const this /* r27 */) {
    // Local variables
    class TourChallengeEvent * const * c; // r31
    class TourChallengeEvent * ce; // r28
    class DataArray * hints; // r28
    int i; // r27
    class DataArray * s; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol screen;
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x68
} __vt__18TourChallengeEvent; // size: 0x68, address: 0x808A1330
struct {
    // total size: 0x8
} __RTTI__P9EventSong; // size: 0x8, address: 0x808A1438
struct {
    // total size: 0x8
} __RTTI__PP18TourChallengeEvent; // size: 0x8, address: 0x808A1458

