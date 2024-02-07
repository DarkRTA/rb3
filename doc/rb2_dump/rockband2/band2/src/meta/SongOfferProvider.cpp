/*
    Compile unit: C:\rockband2\band2\src\meta\SongOfferProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8016B118 -> 0x80172444
*/
// Range: 0x8016B118 -> 0x8016B158
void * Element::Element(class Element * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8016B158 -> 0x8016B1C8
void * Element::Element(class Element * const this /* r29 */, class SongOffer * o /* r30 */, unsigned char is_cover /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8016B1C8 -> 0x8016B23C
void Element::Clear(class Element * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x8016B23C -> 0x8016B268
void Element::__as() {}

// Range: 0x8016B268 -> 0x8016B2B8
unsigned char Element::__eq() {}

// Range: 0x8016B2B8 -> 0x8016B460
class DataArrayPtr Element::ToDataArray(class DataArrayPtr * result /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x8016B460 -> 0x8016B584
void Element::FromDataArray(class Element * const this /* r29 */, class DataArray * a /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongOfferProvider * TheSongOfferProvider;
}

class SongOfferProvider * TheSongOfferProvider; // size: 0x4, address: 0x80A4C6E0
static class Symbol song_select; // size: 0x4, address: 0x80A4C6E8
static class Symbol sorts; // size: 0x4, address: 0x80A4C6F0
// Range: 0x8016B584 -> 0x8016B67C
void SongOfferProvider::Init() {
    // Local variables
    class DataArray * cfg; // r30

    // References
    // -> static class Symbol sorts;
    // -> static class Symbol song_select;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongOfferProvider * TheSongOfferProvider;
}

// Range: 0x8016B67C -> 0x8016B84C
void * SongOfferProvider::SongOfferProvider(class SongOfferProvider * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12SortProvider;
    // -> struct [anonymous] __vt__13GroupProvider;
    // -> struct [anonymous] __vt__15SetlistProvider;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__17SongOfferProvider;
}

// Range: 0x8016B84C -> 0x8016BB64
void * SongOfferProvider::~SongOfferProvider(class SongOfferProvider * const this /* r30 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
    // -> struct [anonymous] __vt__17SongOfferProvider;
}

// Range: 0x8016BC98 -> 0x8016BD34
void SongOfferProvider::OnUnload(class SongOfferProvider * const this /* r29 */) {}

// Range: 0x8016BD34 -> 0x8016BDB8
class SongOffer * SongOfferProvider::GetSongOffer(class SongOfferProvider * const this /* r29 */, class Symbol & shortname /* r30 */) {
    // Local variables
    class SongOffer * it; // r31
}

// Range: 0x8016BDB8 -> 0x8016BF1C
void SongOfferProvider::GetRepresentedShortcuts(const class SongOfferProvider * const this /* r30 */, class vector & rep /* r31 */) {
    // Local variables
    int i; // r28
    class Symbol shortcut; // r1+0x24
}

// Range: 0x8016BF1C -> 0x8016C018
unsigned char SongOfferProvider::AllowActiveShortcut(const class SongOfferProvider * const this /* r30 */, class Symbol & shortcut /* r31 */) {
    // Local variables
    int i; // r28
}

// Range: 0x8016C018 -> 0x8016C0F8
void SongOfferProvider::getSorts(const class vector & all /* r29 */, class vector & available /* r30 */) {
    // Local variables
    class StoreSort * const * it; // r31
}

static class Symbol bass; // size: 0x4, address: 0x80A4C6F8
static class Symbol career; // size: 0x4, address: 0x80A4C700
static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C708
static class Symbol song_select_tour; // size: 0x4, address: 0x80A4C710
static class Symbol random_song; // size: 0x4, address: 0x80A4C718
static class Symbol make_a_setlist; // size: 0x4, address: 0x80A4C720
static class Symbol play_setlist; // size: 0x4, address: 0x80A4C728
static class Symbol browser_group; // size: 0x4, address: 0x80A4C730
static class Symbol browser_cover; // size: 0x4, address: 0x80A4C738
static class Symbol browser_subgroup; // size: 0x4, address: 0x80A4C740
struct SortCmp {
    // total size: 0x4
    class StoreSort * mSort; // offset 0x0, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8016C0F8 -> 0x8016CF20
void SongOfferProvider::applySort(class SongOfferProvider * const this /* r22 */) {
    // Local variables
    struct SortCmp cmp; // r1+0xDC
    class Element * elem; // r1+0xD8
    class Element * elem; // r1+0xD4
    class Element * e; // r1+0xD0
    class Element * e; // r1+0xCC
    class vector subgroups; // r1+0x120
    class DataArray * groupScript; // r30
    class DataArray * subgroup_script; // r29
    class DataArray * coverScript; // r28
    int HdrSongCount; // r27
    int HdrDiscSongCount; // r26
    int HdrDownloadSongCount; // r25
    int ixCurrentGroup; // r24
    class SongOffer * s; // r23
    class Element * offer_element; // r1+0xC8
    class DataArrayPtr args; // r1+0x100
    class Symbol group; // r1+0xC4
    unsigned char cover; // r31
    class Element * group_element; // r1+0xC0
    class vector * insert; // r31
    class vector newAlbum; // r1+0x114

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP7Element;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> const char * kAssertStr;
    // -> static class Symbol browser_subgroup;
    // -> static class Symbol browser_cover;
    // -> static class Symbol browser_group;
    // -> static class Symbol play_setlist;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol make_a_setlist;
    // -> static class Symbol random_song;
    // -> static class Symbol song_select_tour;
    // -> static class Symbol song_select_mode;
    // -> static class Symbol career;
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> static class Symbol bass;
    // -> class Debug TheDebug;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class vector * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class vector * _M_start; // offset 0x0, size 0x4
    class vector * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP7Element; // size: 0x8, address: 0x80898A88
// Range: 0x8016CF20 -> 0x8016D3F0
void SongOfferProvider::AddSubs(class SongOfferProvider * const this /* r31 */, class vector & subgroups /* r28 */) {
    // Local variables
    class vector * vit; // r30
    class Element * pElem; // r1+0x94
    class Element * * eit; // r27
    class Symbol subHeader; // r1+0x90
    class Element * pSub; // r1+0x8C
}

struct _OKToSwap {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct _IsPOD {
    // total size: 0x1
};
static class Symbol song_select_gap; // size: 0x4, address: 0x80A4C748
static class Symbol bass; // size: 0x4, address: 0x80A4C750
static class Symbol guitar; // size: 0x4, address: 0x80A4C758
static class Symbol band; // size: 0x4, address: 0x80A4C760
// Range: 0x8016D3F0 -> 0x8016DC8C
void SongOfferProvider::InitData(class SongOfferProvider * const this /* r29 */, class RndDir * dir /* r27 */) {
    // Local variables
    class vector allowed_parts; // r1+0xB4
    class Symbol part; // r1+0x90
    class vector songs; // r1+0xA8
    class Symbol * songIt; // r31
    const class DataArray * pSongData; // r4

    // References
    // -> struct [anonymous] __vt__9SongOffer;
    // -> struct [anonymous] __vt__5Offer;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6ObjRef>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__9TypeProps;
    // -> struct [anonymous] __vt__Q23Hmx6Object;
    // -> class SongMgr & TheSongMgr;
    // -> static class Symbol band;
    // -> static class Symbol guitar;
    // -> static class Symbol bass;
    // -> static class Symbol song_select_gap;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x8016DC8C -> 0x8016DD08
int SongOfferProvider::GetHeadingSongCount(const class SongOfferProvider * const this /* r30 */, int data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016DD08 -> 0x8016DD84
int SongOfferProvider::GetHeadingDiscSongCount(const class SongOfferProvider * const this /* r30 */, int data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016DD84 -> 0x8016DE00
int SongOfferProvider::GetHeadingDownloadSongCount(const class SongOfferProvider * const this /* r30 */, int data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol group; // size: 0x4, address: 0x80A4C768
static class Symbol store_famous_by; // size: 0x4, address: 0x80A4C770
static class Symbol famousby; // size: 0x4, address: 0x80A4C778
static class Symbol famousby_group; // size: 0x4, address: 0x80A4C780
static class Symbol album; // size: 0x4, address: 0x80A4C788
static class Symbol rb1_icon; // size: 0x4, address: 0x80A4C790
static class Symbol rb2_icon; // size: 0x4, address: 0x80A4C798
static class Symbol song_count; // size: 0x4, address: 0x80A4C7A0
static class Symbol song; // size: 0x4, address: 0x80A4C7A8
static class Symbol score; // size: 0x4, address: 0x80A4C7B0
static class Symbol details; // size: 0x4, address: 0x80A4C7B8
static class Symbol bonus; // size: 0x4, address: 0x80A4C7C0
static class Symbol random_song; // size: 0x4, address: 0x80A4C7C8
static class Symbol career; // size: 0x4, address: 0x80A4C7D0
static class Symbol song_select_play_all; // size: 0x4, address: 0x80A4C7D8
static class Symbol song_select_song; // size: 0x4, address: 0x80A4C7E0
static class Symbol song_select_songs; // size: 0x4, address: 0x80A4C7E8
static class Symbol song_select_practice; // size: 0x4, address: 0x80A4C7F0
static class Symbol song_select_jukebox; // size: 0x4, address: 0x80A4C7F8
static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C800
static class Symbol is_tour; // size: 0x4, address: 0x80A4C808
// Range: 0x8016DE00 -> 0x8016E5F0
char * SongOfferProvider::Text(const class SongOfferProvider * const this /* r26 */, int data /* r27 */, class Symbol & slot /* r28 */) {
    // Local variables
    const class Element * e; // r29
    const class SongOffer * offer; // r3
    int songCount; // r26
    class Symbol heading; // r1+0x7C
    class Symbol song; // r1+0x78
    int score; // r29
    class TourBand * band; // r0
    class list users; // r1+0x90
    struct _List_iterator it; // r1+0x74
    class Profile * profile; // r0
    int temp; // r3
    class BandUser * user; // r26
    enum ControllerType ct; // r0
    enum TrackType tt; // r27
    class Profile * profile; // r0

    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class NetSession * TheNetSession;
    // -> class Tour * TheTour;
    // -> const char * gNullStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_tour;
    // -> static class Symbol song_select_mode;
    // -> static class Symbol song_select_jukebox;
    // -> static class Symbol song_select_practice;
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol song_select_songs;
    // -> static class Symbol song_select_song;
    // -> static class Symbol song_select_play_all;
    // -> static class Symbol career;
    // -> static class Symbol random_song;
    // -> static class Symbol bonus;
    // -> static class Symbol details;
    // -> static class Symbol score;
    // -> static class Symbol song;
    // -> static class Symbol song_count;
    // -> static class Symbol rb2_icon;
    // -> static class Symbol rb1_icon;
    // -> static class Symbol album;
    // -> static class Symbol famousby_group;
    // -> static class Symbol famousby;
    // -> static class Symbol store_famous_by;
    // -> static class Symbol group;
}

static class Symbol group_bg; // size: 0x4, address: 0x80A4C810
static class Symbol album_bg; // size: 0x4, address: 0x80A4C818
static class Symbol song_bg; // size: 0x4, address: 0x80A4C820
static class Symbol download; // size: 0x4, address: 0x80A4C828
// Range: 0x8016E5F0 -> 0x8016E76C
class RndMat * SongOfferProvider::Mat(const class SongOfferProvider * const this /* r29 */, int data /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    class Element * e; // r4

    // References
    // -> static class Symbol download;
    // -> static class Symbol song_bg;
    // -> static class Symbol album_bg;
    // -> static class Symbol group_bg;
}

static class Symbol download; // size: 0x4, address: 0x80A4C830
static class Symbol rb1_icon; // size: 0x4, address: 0x80A4C838
static class Symbol rb2_icon; // size: 0x4, address: 0x80A4C840
// Range: 0x8016E76C -> 0x8016E84C
class Symbol SongOfferProvider::getIcon(const class SongOfferProvider * const this /* r29 */, int ixData /* r30 */) {
    // Local variables
    class Element * e; // r3

    // References
    // -> const char * gNullStr;
    // -> static class Symbol rb2_icon;
    // -> static class Symbol rb1_icon;
    // -> static class Symbol download;
}

// Range: 0x8016E84C -> 0x8016E8D8
class Symbol SongOfferProvider::DataSymbol(const class SongOfferProvider * const this /* r30 */, int data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016E8D8 -> 0x8016E8F0
int SongOfferProvider::NumData() {}

static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C848
static class Symbol song_select_practice; // size: 0x4, address: 0x80A4C850
// Range: 0x8016E8F0 -> 0x8016EBE0
unsigned char SongOfferProvider::IsActive(const class SongOfferProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    class MetaPerformer * mp; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol song_select_practice;
    // -> static class Symbol song_select_mode;
}

static class Symbol song_data_mounted; // size: 0x4, address: 0x80A4C858
static class Message msg; // size: 0x8, address: 0x80979DA8
// Range: 0x8016EBE0 -> 0x8016EF1C
void SongOfferProvider::ContentMounted(class SongOfferProvider * const this /* r29 */, const char * contentName /* r30 */) {
    // Local variables
    class Element & preview; // r31
    int ix; // r0
    const char * selectedContentName; // r4

    // References
    // -> class UIManager TheUI;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
    // -> class SongMgr & TheSongMgr;
    // -> class ContentMgr & TheContentMgr;
    // -> static class Symbol song_data_mounted;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol random_song; // size: 0x4, address: 0x80A4C860
static class Symbol career; // size: 0x4, address: 0x80A4C868
static class Symbol song_select_practice; // size: 0x4, address: 0x80A4C870
static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C878
static class Symbol missing_part_type; // size: 0x4, address: 0x80A4C880
// Range: 0x8016EF1C -> 0x8016F388
unsigned char SongOfferProvider::IsDisabled(const class SongOfferProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    const class SongOffer * offer; // r30
    class Symbol song; // r1+0x44
    const class SongOffer * offer; // r26
    class Symbol song; // r1+0x40
    const class SongOffer * offer; // r26
    class Symbol song; // r1+0x3C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol missing_part_type;
    // -> static class Symbol song_select_mode;
    // -> static class Symbol song_select_practice;
    // -> static class Symbol career;
    // -> static class Symbol random_song;
}

static class Symbol disabled; // size: 0x4, address: 0x80A4C888
// Range: 0x8016F388 -> 0x8016F40C
class Symbol SongOfferProvider::State(const class SongOfferProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> static class Symbol disabled;
}

// Range: 0x8016F40C -> 0x8016F518
unsigned char SongOfferProvider::OnIsSong(const class SongOfferProvider * const this /* r31 */) {
    // Local variables
    class DataNode n; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016F518 -> 0x8016F5D4
unsigned char SongOfferProvider::IsHeader(const class SongOfferProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016F5D4 -> 0x8016F688
unsigned char SongOfferProvider::IsSubHeader(const class SongOfferProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016F688 -> 0x8016F73C
unsigned char SongOfferProvider::IsFunction(const class SongOfferProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol browser_shortcut; // size: 0x4, address: 0x80A4C890
static class Symbol browser_group; // size: 0x4, address: 0x80A4C898
// Range: 0x8016F73C -> 0x8016F994
class Symbol SongOfferProvider::PosToShortcut(const class SongOfferProvider * const this /* r30 */, int pos /* r28 */) {
    // Local variables
    class DataArray * c; // r28
    class DataArrayPtr args; // r1+0x28

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol browser_group;
    // -> static class Symbol browser_shortcut;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016F994 -> 0x8016FA4C
class Symbol SongOfferProvider::GetCurrentShortcut(const class SongOfferProvider * const this /* r30 */, int pos /* r31 */) {
    // Local variables
    class Symbol shortcut; // r1+0x10

    // References
    // -> const char * gNullStr;
}

static class Symbol browser_shortcut; // size: 0x4, address: 0x80A4C8A0
// Range: 0x8016FA4C -> 0x8016FCF0
int SongOfferProvider::ShortcutToPos(const class SongOfferProvider * const this /* r27 */, class Symbol & shortcut /* r28 */) {
    // Local variables
    class DataArray * c; // r30
    int num_data; // r0
    int i; // r29
    int x; // r5
    class DataArrayPtr args; // r1+0x28

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol browser_shortcut;
}

// Range: 0x8016FCF0 -> 0x8016FD70
int SongOfferProvider::ShortcutToSelectablePos(const class SongOfferProvider * const this /* r31 */) {
    // Local variables
    int pos; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016FD70 -> 0x8016FF0C
int SongOfferProvider::GetNextHeader(const class SongOfferProvider * const this /* r28 */, int data /* r29 */) {
    // Local variables
    int max; // r25
    int ix; // r30
    enum ElementType type; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8016FF0C -> 0x8016FFD8
int SongOfferProvider::PosToSelectablePos(const class SongOfferProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    int ix; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol random_song; // size: 0x4, address: 0x80A4C8A8
static class Symbol career; // size: 0x4, address: 0x80A4C8B0
static class Symbol missing_part_type; // size: 0x4, address: 0x80A4C8B8
// Range: 0x8016FFD8 -> 0x80170150
class Symbol SongOfferProvider::GetSelectedSong(class SongOfferProvider * const this /* r30 */) {
    // Local variables
    enum MissingPartType mpt; // r29

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SongMgr & TheSongMgr;
    // -> static class Symbol missing_part_type;
    // -> static class Symbol career;
    // -> static class Symbol random_song;
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol missing_part_type; // size: 0x4, address: 0x80A4C8C0
// Range: 0x80170150 -> 0x8017040C
int SongOfferProvider::OnSelectHeader(class SongOfferProvider * const this /* r26 */, int ixData /* r27 */) {
    // Local variables
    class QuickplayPerformer * qpp; // r31
    enum MissingPartType mpt; // r30
    unsigned char bSkipSubs; // r29
    int result; // r28
    const class SongOffer * offer; // r22
    class Symbol song; // r1+0x18

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SongMgr & TheSongMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol missing_part_type;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C8C8
static class Symbol song_select_tour; // size: 0x4, address: 0x80A4C8D0
// Range: 0x8017040C -> 0x80170480
unsigned char SongOfferProvider::IsSetlistMode(const class SongOfferProvider * const this /* r31 */) {
    // References
    // -> static class Symbol song_select_tour;
    // -> static class Symbol song_select_mode;
}

static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C8D8
static class Symbol song_select_tour; // size: 0x4, address: 0x80A4C8E0
static class Symbol any; // size: 0x4, address: 0x80A4C8E8
static class Symbol missing_part_type; // size: 0x4, address: 0x80A4C8F0
// Range: 0x80170480 -> 0x8017072C
void SongOfferProvider::SetSetlistMode(class SongOfferProvider * const this /* r29 */, unsigned char bSet /* r30 */) {
    // Local variables
    enum MissingPartType mpt; // r28
    class vector valid_songs; // r1+0x30
    int i; // r28
    int valid_size; // r1+0x2C

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SongMgr & TheSongMgr;
    // -> static class Symbol missing_part_type;
    // -> class GameMode * TheGameMode;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol any;
    // -> static class Symbol song_select_tour;
    // -> static class Symbol song_select_mode;
}

static class Symbol band; // size: 0x4, address: 0x80A4C8F8
static class Symbol none; // size: 0x4, address: 0x80A4C900
// Range: 0x8017072C -> 0x801709A0
class Symbol SongOfferProvider::findRelevantPart(class SongOfferProvider * const this /* r28 */) {
    // Local variables
    unsigned char coop; // r0
    unsigned char solo; // r0
    class list configs; // r1+0x48
    class BandUser * pUser; // r28
    class Symbol part; // r1+0x34

    // References
    // -> static class Symbol none;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> static class Symbol band;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
}

static class Symbol song_select_mode; // size: 0x4, address: 0x80A4C908
static class Symbol song_select_tour; // size: 0x4, address: 0x80A4C910
static class Symbol song_select_practice; // size: 0x4, address: 0x80A4C918
static class Symbol player_arrangement; // size: 0x4, address: 0x80A4C920
// Range: 0x801709A0 -> 0x80170B54
unsigned char SongOfferProvider::HeadersSelectable(const class SongOfferProvider * const this /* r31 */) {
    // References
    // -> class GameMode * TheGameMode;
    // -> static class Symbol player_arrangement;
    // -> static class Symbol song_select_practice;
    // -> static class Symbol song_select_tour;
    // -> static class Symbol song_select_mode;
}

// Range: 0x80170B54 -> 0x80170C3C
void SongOfferProvider::PlayPreview(class SongOfferProvider * const this /* r30 */, int ix /* r31 */) {
    // Local variables
    class Symbol song_name; // r1+0x14

    // References
    // -> const char * gNullStr;
    // -> class ContentMgr & TheContentMgr;
    // -> class SongPreview TheSongPreview;
}

// Range: 0x80170C3C -> 0x80170C98
void SongOfferProvider::SetHighlighted(class SongOfferProvider * const this /* r5 */) {
    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x80170C98 -> 0x80170D40
int SongOfferProvider::GetHighlightedIx(class SongOfferProvider * const this /* r29 */) {
    // Local variables
    class Element & highlight; // r31
    int i; // r30

    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x80170D40 -> 0x80170DB0
class DataNode SongOfferProvider::GetRemoteHighlight() {
    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x80170DB0 -> 0x80170E38
class DataNode SongOfferProvider::SetRemoteHighlight(class SongOfferProvider * const this /* r30 */, class DataArray * d /* r31 */) {}

// Range: 0x80170E38 -> 0x80170EB8
int SongOfferProvider::InitHighlight(class SongOfferProvider * const this /* r30 */) {
    // Local variables
    int ix; // r31

    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
}

static class Symbol _s; // size: 0x4, address: 0x80A4C928
static class Symbol _s; // size: 0x4, address: 0x80A4C930
static class Symbol _s; // size: 0x4, address: 0x80A4C938
static class Symbol _s; // size: 0x4, address: 0x80A4C940
static class Symbol _s; // size: 0x4, address: 0x80A4C948
static class Symbol _s; // size: 0x4, address: 0x80A4C950
static class Symbol _s; // size: 0x4, address: 0x80A4C958
static class Symbol _s; // size: 0x4, address: 0x80A4C960
static class Symbol _s; // size: 0x4, address: 0x80A4C968
static class Symbol _s; // size: 0x4, address: 0x80A4C970
static class Symbol _s; // size: 0x4, address: 0x80A4C978
static class Symbol _s; // size: 0x4, address: 0x80A4C980
static class Symbol _s; // size: 0x4, address: 0x80A4C988
static class Symbol _s; // size: 0x4, address: 0x80A4C990
static class Symbol _s; // size: 0x4, address: 0x80A4C998
static class Symbol _s; // size: 0x4, address: 0x80A4C9A0
static class Symbol _s; // size: 0x4, address: 0x80A4C9A8
static class Symbol _s; // size: 0x4, address: 0x80A4C9B0
static class Symbol _s; // size: 0x4, address: 0x80A4C9B8
static class Symbol _s; // size: 0x4, address: 0x80A4C9C0
static class Symbol _s; // size: 0x4, address: 0x80A4C9C8
static class Symbol _s; // size: 0x4, address: 0x80A4C9D0
static class Symbol _s; // size: 0x4, address: 0x80A4C9D8
static class Symbol _s; // size: 0x4, address: 0x80A4C9E0
static class Symbol _s; // size: 0x4, address: 0x80A4C9E8
static class Symbol _s; // size: 0x4, address: 0x80A4C9F0
static class Symbol _s; // size: 0x4, address: 0x80A4C9F8
static class Symbol _s; // size: 0x4, address: 0x80A4CA00
static class Symbol _s; // size: 0x4, address: 0x80A4CA08
static class Symbol _s; // size: 0x4, address: 0x80A4CA10
// Range: 0x80170EB8 -> 0x80171CB0
class DataNode SongOfferProvider::Handle(class SongOfferProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4CA18
static class Symbol _s; // size: 0x4, address: 0x80A4CA20
static class Symbol _s; // size: 0x4, address: 0x80A4CA28
static class Symbol _s; // size: 0x4, address: 0x80A4CA30
// Range: 0x80171CB0 -> 0x80172180
unsigned char SongOfferProvider::SyncProperty(class SongOfferProvider * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__12SortProvider;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__13GroupProvider;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__15SetlistProvider;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

static class Symbol song; // size: 0x4, address: 0x80A4CA38
static class Symbol any; // size: 0x4, address: 0x80A4CA40
static class Symbol random; // size: 0x4, address: 0x80A4CA48
static class Symbol choosing; // size: 0x4, address: 0x80A4CA50
static class Symbol tour_random_song; // size: 0x4, address: 0x80A4CA58
// Range: 0x80172180 -> 0x801723BC
char * SetlistProvider::Text(int data /* r30 */, class Symbol & slot /* r29 */) {
    // Local variables
    class String strResult; // r1+0x30
    class Symbol songSym; // r1+0x20

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongMgr & TheSongMgr;
    // -> static class Symbol tour_random_song;
    // -> static class Symbol choosing;
    // -> static class Symbol random;
    // -> static class Symbol any;
    // -> static class Symbol song;
}

// Range: 0x801723BC -> 0x801723F4
class Symbol SetlistProvider::DataSymbol(int data /* r31 */) {}

// Range: 0x801723F4 -> 0x80172418
int SetlistProvider::NumData() {}

struct {
    // total size: 0x98
} __vt__15SetlistProvider; // size: 0x98, address: 0x80899188
struct {
    // total size: 0x8
} __RTTI__15SetlistProvider; // size: 0x8, address: 0x80899250
struct {
    // total size: 0x10C
} __vt__17SongOfferProvider; // size: 0x10C, address: 0x80899258
struct {
    // total size: 0x8
} __RTTI__17SongOfferProvider; // size: 0x8, address: 0x808993A8
struct {
    // total size: 0x98
} __vt__12SortProvider; // size: 0x98, address: 0x80899410
struct {
    // total size: 0x8
} __RTTI__12SortProvider; // size: 0x8, address: 0x808994D8
// Range: 0x80172418 -> 0x80172444
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std58vector<P7Element,Q211stlpmtx_std23StlNodeAlloc<P7Element>>; // size: 0x8, address: 0x80899628
struct {
    // total size: 0x8
} __RTTI__P9SongOffer; // size: 0x8, address: 0x80899640

