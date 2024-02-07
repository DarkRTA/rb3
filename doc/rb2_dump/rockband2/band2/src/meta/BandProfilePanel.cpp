/*
    Compile unit: C:\rockband2\band2\src\meta\BandProfilePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801F99AC -> 0x802008F8
*/
class DataArray * types; // size: 0x4, address: 0x80A4E490
class MemberStatusChangeMsg : public NetMessage {
    // total size: 0x14
    class String mCharName; // offset 0x4, size 0xC
    unsigned char mPromoted; // offset 0x10, size 0x1
};
// Range: 0x801F99AC -> 0x801F99FC
static class NetMessage * MemberStatusChangeMsg::NewNetMessage() {
    // References
    // -> static struct [anonymous] __vt__Q230@unnamed@BandProfilePanel_cpp@21MemberStatusChangeMsg;
}

// Range: 0x801F99FC -> 0x801F9A54
static void MemberStatusChangeMsg::Save(const class MemberStatusChangeMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x801F9A54 -> 0x801F9AB8
static void MemberStatusChangeMsg::Load(class MemberStatusChangeMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

static class Symbol passive_message_promoted; // size: 0x4, address: 0x80A4E498
static class Symbol passive_message_demoted; // size: 0x4, address: 0x80A4E4A0
// Range: 0x801F9AB8 -> 0x801F9C3C
static void MemberStatusChangeMsg::Dispatch(class MemberStatusChangeMsg * const this /* r28 */) {
    // Local variables
    class Symbol token; // r1+0xC
    const char * msg; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__20PassiveMessagesPanel;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol passive_message_demoted;
    // -> static class Symbol passive_message_promoted;
}

static class Symbol tour_profile_user_not_present; // size: 0x4, address: 0x80A4E4A8
// Range: 0x801F9C3C -> 0x801FA2AC
void LineupProvider::InitFromBand(class LineupProvider * const this /* r26 */, class BandData * bandData /* r27 */, unsigned char display_band_data /* r28 */) {
    // Local variables
    class vector participants; // r1+0x50
    int n; // r29
    struct LineupMember member; // r1+0x90
    class TourCharLocal * localChar; // r0
    class vector roster; // r1+0x44
    int n; // r29
    struct LineupMember * existingMember; // r0
    struct LineupMember member; // r1+0x5C

    // References
    // -> const char * gNullStr;
    // -> static class Symbol tour_profile_user_not_present;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> class Debug TheDebug;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Tour * TheTour;
}

// Range: 0x801FA2AC -> 0x801FA354
struct LineupMember * LineupProvider::HasCharInLineup(class LineupProvider * const this /* r28 */, const class HxGuid & guid /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x801FA354 -> 0x801FA408
unsigned char LineupProvider::IsBandMember(class LineupProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FA408 -> 0x801FA4BC
char * LineupProvider::GetCharName(class LineupProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FA4BC -> 0x801FA578
unsigned char LineupProvider::IsAbsent(class LineupProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FA578 -> 0x801FA628
struct LineupMember * LineupProvider::GetLineupMember(class LineupProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FA628 -> 0x801FA73C
void LineupProvider::InitData(class LineupProvider * const this /* r28 */, class RndDir * dir /* r29 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol char_name; // size: 0x4, address: 0x80A4E4B0
static class Symbol icon; // size: 0x4, address: 0x80A4E4B8
static class Symbol status; // size: 0x4, address: 0x80A4E4C0
static class Symbol user_name; // size: 0x4, address: 0x80A4E4C8
// Range: 0x801FA73C -> 0x801FA948
char * LineupProvider::Text(const class LineupProvider * const this /* r29 */, int data /* r30 */, class Symbol & slot /* r28 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> static class Symbol user_name;
    // -> static class Symbol status;
    // -> static class Symbol icon;
    // -> static class Symbol char_name;
}

static class Symbol black_bar; // size: 0x4, address: 0x80A4E4D0
// Range: 0x801FA948 -> 0x801FAA10
class RndMat * LineupProvider::Mat(const class LineupProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol black_bar;
}

// Range: 0x801FAA10 -> 0x801FAA38
int LineupProvider::NumData() {}

// Range: 0x801FAA38 -> 0x801FAAC8
enum ShowGamercardResult LineupProvider::ShowGamercard() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4E4D8
static class Symbol _s; // size: 0x4, address: 0x80A4E4E0
static class Symbol _s; // size: 0x4, address: 0x80A4E4E8
static class Symbol _s; // size: 0x4, address: 0x80A4E4F0
static class Symbol _s; // size: 0x4, address: 0x80A4E4F8
static class Symbol _s; // size: 0x4, address: 0x80A4E500
// Range: 0x801FAAC8 -> 0x801FB39C
class DataNode LineupProvider::Handle(class LineupProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandData;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol band_profile_choose_standin; // size: 0x4, address: 0x80A4E508
static class Symbol tour_standin_unavailable; // size: 0x4, address: 0x80A4E510
// Range: 0x801FB39C -> 0x801FB90C
void StandInProvider::InitFromBand(class StandInProvider * const this /* r27 */, class TourBandLocal * tbl /* r28 */) {
    // Local variables
    int num_controllers[3]; // r1+0x68
    int i; // r5
    class vector users; // r1+0x5C
    class vector active_guids; // r1+0x50
    class BandUser * * u; // r29
    enum ControllerType ct; // r0
    class CharData * cd; // r0
    int i; // r29
    struct StandIn stand_in; // r1+0x74
    enum TrackType tt; // r0
    class CharData * c; // r30
    enum ControllerType ct; // r0

    // References
    // -> static class Symbol tour_standin_unavailable;
    // -> class ProfileMgr TheProfileMgr;
    // -> static class Symbol band_profile_choose_standin;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct StandInCmp {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
static class Symbol char_name; // size: 0x4, address: 0x80A4E518
static class Symbol icon; // size: 0x4, address: 0x80A4E520
// Range: 0x801FB90C -> 0x801FBA00
char * StandInProvider::Text(const class StandInProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Symbol icon;
    // -> static class Symbol char_name;
}

// Range: 0x801FBA00 -> 0x801FBA4C
class RndMat * StandInProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FBA4C -> 0x801FBA74
int StandInProvider::NumData() {}

static class Symbol disabled; // size: 0x4, address: 0x80A4E528
// Range: 0x801FBA74 -> 0x801FBAFC
class Symbol StandInProvider::State(const class StandInProvider * const this /* r29 */, int data /* r30 */, class Symbol & component_state /* r31 */) {
    // References
    // -> static class Symbol disabled;
}

static class Symbol _s; // size: 0x4, address: 0x80A4E530
static class Symbol _s; // size: 0x4, address: 0x80A4E538
// Range: 0x801FBAFC -> 0x801FBFC8
class DataNode StandInProvider::Handle(class StandInProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801FBFC8 -> 0x801FBFD0
unsigned char __eq() {}

static class Symbol tour_standin_unavailable; // size: 0x4, address: 0x80A4E540
// Range: 0x801FBFD0 -> 0x801FC498
int StandInCharProvider::InitFromBand(class StandInCharProvider * const this /* r28 */, class TourBandLocal * b /* r29 */, enum TrackType tt /* r30 */) {
    // Local variables
    class vector profiles; // r1+0x50
    class Profile * * p; // r31
    class vector chars; // r1+0x44
    class TourCharLocal * * c; // r25
    unsigned char skip; // r26
    int t; // r24
    class TourCharLocal * const * c; // r24
    const class HxGuid & guid; // r24
    struct Entry * e; // r0
    struct Entry unavailable; // r1+0x60

    // References
    // -> static class Symbol tour_standin_unavailable;
    // -> class PlatformMgr ThePlatformMgr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP13TourCharLocal;
    // -> unsigned char gStlAllocNameLookup;
    // -> class ProfileMgr TheProfileMgr;
    // -> const char * gNullStr;
}

// Range: 0x801FC498 -> 0x801FC4B8
void StandInCharProvider::SetStandIn(class StandInCharProvider * const this /* r7 */) {}

// Range: 0x801FC4B8 -> 0x801FC4D0
unsigned char StandInCharProvider::IsActive() {}

static class Symbol character; // size: 0x4, address: 0x80A4E548
static class Symbol option; // size: 0x4, address: 0x80A4E550
static class Symbol heading; // size: 0x4, address: 0x80A4E558
static class Symbol tour_standin_none; // size: 0x4, address: 0x80A4E560
// Range: 0x801FC4D0 -> 0x801FC680
char * StandInCharProvider::Text(const class StandInCharProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Symbol tour_standin_none;
    // -> const char * gNullStr;
    // -> static class Symbol heading;
    // -> static class Symbol option;
    // -> static class Symbol character;
}

// Range: 0x801FC680 -> 0x801FC6CC
class RndMat * StandInCharProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FC6CC -> 0x801FC6E4
int StandInCharProvider::NumData() {}

// Range: 0x801FC6E4 -> 0x801FC7E0
class HxGuid & StandInCharProvider::AddEntry(class StandInCharProvider * const this /* r29 */, unsigned char header /* r30 */, const char * name /* r31 */) {
    // Local variables
    struct Entry entry; // r1+0x10
}

static class Symbol _s; // size: 0x4, address: 0x80A4E568
static class Symbol _s; // size: 0x4, address: 0x80A4E570
// Range: 0x801FC7E0 -> 0x801FCD1C
class DataNode StandInCharProvider::Handle(class StandInCharProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801FCD1C -> 0x801FCD3C
void TopSongsProvider::InitFromBand(class TopSongsProvider * const this /* r5 */) {}

static class Symbol name; // size: 0x4, address: 0x80A4E578
static class Symbol score; // size: 0x4, address: 0x80A4E580
// Range: 0x801FCD3C -> 0x801FCEE4
char * TopSongsProvider::Text(const class TopSongsProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> class SongMgr & TheSongMgr;
    // -> static class Symbol score;
    // -> static class Symbol name;
}

// Range: 0x801FCEE4 -> 0x801FCF30
class RndMat * TopSongsProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FCF30 -> 0x801FCF68
int TopSongsProvider::NumData() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E588
// Range: 0x801FCF68 -> 0x801FD340
class DataNode TopSongsProvider::Handle(class TopSongsProvider * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandData;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class _List_node : public _List_node_base {
    // total size: 0x30
public:
    class BotbBattlesParticipatedInRow _M_data; // offset 0x8, size 0x28
};
// Range: 0x801FD340 -> 0x801FD43C
void BattleHistoryProvider::InitData(class BattleHistoryProvider * const this /* r29 */, class RndDir * dir /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
}

// Range: 0x801FD43C -> 0x801FD444
class BotbBattlesParticipatedInList & BattleHistoryProvider::GetBattlesList() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801FD444 -> 0x801FD59C
int BattleHistoryProvider::GetBattleID(const class BattleHistoryProvider * const this /* r28 */, int pos /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0x28
    int n; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FD59C -> 0x801FD654
int BattleHistoryProvider::GetBattleIDPos(const class BattleHistoryProvider * const this /* r29 */, int battleid /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x10
    int n; // r31
}

static class Symbol name; // size: 0x4, address: 0x80A4E590
static class Symbol score; // size: 0x4, address: 0x80A4E598
static class Symbol botb_hist_unranked; // size: 0x4, address: 0x80A4E5A0
static class Symbol botb_hist_rank; // size: 0x4, address: 0x80A4E5A8
static class Symbol band_profile_no_battles; // size: 0x4, address: 0x80A4E5B0
// Range: 0x801FD654 -> 0x801FD918
char * BattleHistoryProvider::Text(const class BattleHistoryProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x4C
    int n; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol band_profile_no_battles;
    // -> static class Symbol botb_hist_rank;
    // -> static class Symbol botb_hist_unranked;
    // -> static class Symbol score;
    // -> static class Symbol name;
}

// Range: 0x801FD918 -> 0x801FDB58
class RndMat * BattleHistoryProvider::Mat(const class BattleHistoryProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x40
    int n; // r4
    class DynamicTex * const * c; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801FDB58 -> 0x801FDBE4
int BattleHistoryProvider::NumData() {
    // Local variables
    int numBattles; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A4E5B8
static class Symbol _s; // size: 0x4, address: 0x80A4E5C0
// Range: 0x801FDBE4 -> 0x801FE094
class DataNode BattleHistoryProvider::Handle(class BattleHistoryProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol summary; // size: 0x4, address: 0x80A4E5C8
// Range: 0x801FE094 -> 0x801FE248
void * BandProfilePanel::BandProfilePanel(class BandProfilePanel * const this /* r31 */) {
    // References
    // -> static class Symbol summary;
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__21BattleHistoryProvider;
    // -> struct [anonymous] __vt__16TopSongsProvider;
    // -> struct [anonymous] __vt__14LineupProvider;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> struct [anonymous] __vt__16BandProfilePanel;
}

// Range: 0x801FE248 -> 0x801FE550
void * BandProfilePanel::~BandProfilePanel(class BandProfilePanel * const this /* r30 */) {}

// Range: 0x801FE550 -> 0x801FE57C
void BandProfilePanel::SetBandData() {}

// Range: 0x801FE57C -> 0x801FE584
class BandData * BandProfilePanel::GetBandData() {}

// Range: 0x801FE584 -> 0x801FE5C4
unsigned char BandProfilePanel::DisplayingTourBand(class BandProfilePanel * const this /* r31 */) {
    // References
    // -> class Tour * TheTour;
}

// Range: 0x801FE5C4 -> 0x801FE5CC
class LineupProvider * BandProfilePanel::GetLineupProvider() {}

// Range: 0x801FE5CC -> 0x801FE7C8
unsigned char BandProfilePanel::CanToggleMemberStatus(class BandProfilePanel * const this /* r29 */, int pos /* r30 */) {
    // Local variables
    struct LineupMember * member; // r0
    class vector roster; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FE7C8 -> 0x801FE9D0
void BandProfilePanel::ToggleMemberStatus(class BandProfilePanel * const this /* r31 */, int pos /* r29 */) {
    // Local variables
    class TourBandLocal * band; // r28
    struct LineupMember * member; // r0
    unsigned char promote; // r0
    struct BandMember newMember; // r1+0x28
    class String censoredName; // r1+0x8
    class MemberStatusChangeMsg passiveMsg; // r1+0x14

    // References
    // -> class NetSession * TheNetSession;
    // -> static struct [anonymous] __vt__Q230@unnamed@BandProfilePanel_cpp@21MemberStatusChangeMsg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
}

// Range: 0x801FEA30 -> 0x801FEB20
void BandProfilePanel::SetToggleCandidate(class BandProfilePanel * const this /* r29 */, int pos /* r30 */) {
    // Local variables
    class TourBandLocal * band; // r0
    struct LineupMember * member; // r0

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FEB20 -> 0x801FEB28
class TopSongsProvider * BandProfilePanel::GetTopSongsProvider() {}

// Range: 0x801FEB28 -> 0x801FEC18
void BandProfilePanel::SetBandLogo(class BandProfilePanel * const this /* r30 */, class String & band_logo /* r29 */) {
    // Local variables
    class TourBandLocal * pBand; // r30

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FEC18 -> 0x801FECEC
void BandProfilePanel::SetBandLogoPos(class BandProfilePanel * const this /* r30 */, int band_logo_pos /* r29 */) {
    // Local variables
    class TourBandLocal * pBand; // r30

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FECEC -> 0x801FEDC0
void BandProfilePanel::SetMotto(class BandProfilePanel * const this /* r30 */, const char * motto /* r29 */) {
    // Local variables
    class TourBandLocal * pBand; // r30

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FEDC0 -> 0x801FEEA0
void BandProfilePanel::SetBandName(class BandProfilePanel * const this /* r30 */, const char * strName /* r29 */) {
    // Local variables
    class TourBandLocal * pBand; // r30

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FEEA0 -> 0x801FEEF8
enum ShowGamercardResult BandProfilePanel::ShowOwnerGamercard() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FEEF8 -> 0x801FEF00
class BattleHistoryProvider * BandProfilePanel::GetBattleHistoryProvider() {}

// Range: 0x801FEF00 -> 0x801FEF28
unsigned char BandProfilePanel::HasBattleData() {}

// Range: 0x801FEF28 -> 0x801FEFF4
unsigned char BandProfilePanel::HasSelectableBattleData(class BandProfilePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801FEFF4 -> 0x801FF120
void BandProfilePanel::RequestBattleData(class BandProfilePanel * const this /* r29 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol botb_error; // size: 0x4, address: 0x80A4E5D0
static class Message init; // size: 0x8, address: 0x8097C810
// Range: 0x801FF120 -> 0x801FF3B8
class DataNode BandProfilePanel::OnMsg(class BandProfilePanel * const this /* r27 */) {
    // Local variables
    const class list * list; // r28
    struct _List_iterator it; // r1+0x24
    const char * path; // r0

    // References
    // -> class Debug TheDebug;
    // -> class BandUI * TheBandUI;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol botb_error;
}

static class Message update; // size: 0x8, address: 0x8097C828
// Range: 0x801FF3B8 -> 0x801FF53C
void BandProfilePanel::Poll(class BandProfilePanel * const this /* r31 */) {
    // References
    // -> static class Message update;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x801FF53C -> 0x801FF594
void BandProfilePanel::Exit(class BandProfilePanel * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x801FF594 -> 0x801FF66C
void BandProfilePanel::Enter(class BandProfilePanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__19StandInCharProvider;
    // -> struct [anonymous] __vt__15StandInProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

static class Symbol summary; // size: 0x4, address: 0x80A4E5D8
// Range: 0x801FF66C -> 0x801FF868
void BandProfilePanel::UpdateTabFocus(class BandProfilePanel * const this /* r28 */) {
    // Local variables
    class ObjectDir * dir; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> static class Symbol summary;
}

// Range: 0x801FF868 -> 0x801FF8EC
void BandProfilePanel::Unload(class BandProfilePanel * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4E5E0
static class Symbol _s; // size: 0x4, address: 0x80A4E5E8
static class Symbol _s; // size: 0x4, address: 0x80A4E5F0
static class Symbol _s; // size: 0x4, address: 0x80A4E5F8
static class Symbol _s; // size: 0x4, address: 0x80A4E600
static class Symbol _s; // size: 0x4, address: 0x80A4E608
static class Symbol _s; // size: 0x4, address: 0x80A4E610
static class Symbol _s; // size: 0x4, address: 0x80A4E618
static class Symbol _s; // size: 0x4, address: 0x80A4E620
static class Symbol _s; // size: 0x4, address: 0x80A4E628
static class Symbol _s; // size: 0x4, address: 0x80A4E630
static class Symbol _s; // size: 0x4, address: 0x80A4E638
static class Symbol _s; // size: 0x4, address: 0x80A4E640
static class Symbol _s; // size: 0x4, address: 0x80A4E648
static class Symbol _s; // size: 0x4, address: 0x80A4E650
static class Symbol _s; // size: 0x4, address: 0x80A4E658
static class Symbol _s; // size: 0x4, address: 0x80A4E660
static class Symbol _s; // size: 0x4, address: 0x80A4E668
static class Symbol _s; // size: 0x4, address: 0x80A4E670
static class Symbol _s; // size: 0x4, address: 0x80A4E678
// Range: 0x801FFAEC -> 0x802004E8
class DataNode BandProfilePanel::Handle(class BandProfilePanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

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
}

static class Symbol _s; // size: 0x4, address: 0x80A4E680
static class Symbol _s; // size: 0x4, address: 0x80A4E688
static class Symbol _s; // size: 0x4, address: 0x80A4E690
// Range: 0x802004E8 -> 0x80200868
unsigned char BandProfilePanel::SyncProperty(class BandProfilePanel * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x80200868 -> 0x8020089C
static char * MemberStatusChangeMsg::Name() {}

// Range: 0x8020089C -> 0x802008F8
static unsigned char MemberStatusChangeMsg::ByteCode() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
}

static struct {
    // total size: 0x28
} __vt__Q230@unnamed@BandProfilePanel_cpp@21MemberStatusChangeMsg; // size: 0x28, address: 0x808A9758
struct {
    // total size: 0x8
} __RTTI__Q230@unnamed@BandProfilePanel_cpp@21MemberStatusChangeMsg; // size: 0x8, address: 0x808A97C8
struct {
    // total size: 0xF8
} __vt__16BandProfilePanel; // size: 0xF8, address: 0x808A9B98
struct {
    // total size: 0x9C
} __vt__21BattleHistoryProvider; // size: 0x9C, address: 0x808A9CE0
struct {
    // total size: 0x8
} __RTTI__21BattleHistoryProvider; // size: 0x8, address: 0x808A9DB0
struct {
    // total size: 0x9C
} __vt__16TopSongsProvider; // size: 0x9C, address: 0x808A9DB8
struct {
    // total size: 0x8
} __RTTI__16TopSongsProvider; // size: 0x8, address: 0x808A9E88
struct {
    // total size: 0x9C
} __vt__19StandInCharProvider; // size: 0x9C, address: 0x808A9E90
struct {
    // total size: 0x8
} __RTTI__19StandInCharProvider; // size: 0x8, address: 0x808A9F60
struct {
    // total size: 0x9C
} __vt__15StandInProvider; // size: 0x9C, address: 0x808A9F68
struct {
    // total size: 0x8
} __RTTI__15StandInProvider; // size: 0x8, address: 0x808AA038
struct {
    // total size: 0x9C
} __vt__14LineupProvider; // size: 0x9C, address: 0x808AA040
struct {
    // total size: 0x8
} __RTTI__14LineupProvider; // size: 0x8, address: 0x808AA108
struct {
    // total size: 0x8
} __RTTI__PQ219StandInCharProvider5Entry; // size: 0x8, address: 0x808AA268
struct {
    // total size: 0x8
} __RTTI__PQ215StandInProvider7StandIn; // size: 0x8, address: 0x808AA290
struct {
    // total size: 0x8
} __RTTI__P12LineupMember; // size: 0x8, address: 0x808AA2A8

