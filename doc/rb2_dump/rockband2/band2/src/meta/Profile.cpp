/*
    Compile unit: C:\rockband2\band2\src\meta\Profile.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80140114 -> 0x801457F0
*/
class Symbol t; // size: 0x4, address: 0x80A4BFCC
// Range: 0x80140114 -> 0x80140328
void * Profile::Profile(class Profile * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7Profile;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x80140328 -> 0x801407A8
void * Profile::~Profile(class Profile * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7Profile;
}

// Range: 0x80140818 -> 0x80140820
class vector & Profile::GetAllChars() {}

// Range: 0x80140820 -> 0x801408AC
class TourCharLocal * Profile::GetCharFromGuid(class Profile * const this /* r27 */, const class HxGuid & guid /* r28 */) {
    // Local variables
    int size; // r30
    int i; // r29
}

// Range: 0x801408AC -> 0x801408C4
int Profile::NumChars() {}

// Range: 0x801408C4 -> 0x801408F8
unsigned char Profile::HasChar() {
    // Local variables
    class TourCharLocal * const * it; // r5
}

static char buf1[100]; // size: 0x64, address: 0x80979280
// Range: 0x801408F8 -> 0x80140A74
unsigned char Profile::IsCharNameUnique(class Profile * const this /* r31 */, const char * charName /* r28 */) {
    // Local variables
    int len1; // r0
    int i; // r6
    class TourCharLocal * const * it; // r29
    const char * charName2; // r28
    int len2; // r0
    char buf2[100]; // r1+0x8

    // References
    // -> static char buf1[100];
    // -> struct __locale _current_locale;
}

// Range: 0x80140A74 -> 0x80140AF8
unsigned char Profile::IsBandNameUnique(class Profile * const this /* r29 */, const char * bandName /* r30 */) {
    // Local variables
    class TourBandLocal * const * it; // r31
}

// Range: 0x80140AF8 -> 0x80140DB4
void Profile::DeleteChar(class Profile * const this /* r30 */, const class HxGuid & charGuid /* r31 */) {
    // Local variables
    class TourBandLocal * * bandIter; // r28
    class TourBandLocal * localBand; // r27
    class vector remoteBandsToDelete; // r1+0x20
    class RemoteBandData * * remoteIter; // r27
    class RemoteBandData * remoteBand; // r1+0x1C
    class RemoteBandData * * remoteIter; // r27
    class TourCharLocal * * charIter; // r27
    class TourCharLocal * tourChar; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80140DB4 -> 0x80140F88
void Profile::FindAllBandsForCharacterGuid(const class Profile * const this /* r28 */, const class HxGuid & charGuid /* r29 */, class vector & bands /* r30 */) {
    // Local variables
    class TourBandLocal * const * bandIter; // r27
    class TourBandLocal * localBand; // r1+0x14
    class RemoteBandData * const * remoteIter; // r27
    class RemoteBandData * remoteBand; // r1+0x10

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80140F88 -> 0x8014111C
void Profile::RemoveCharFromBand(class Profile * const this /* r26 */, const class HxGuid & charGuid /* r27 */, const class HxGuid & bandGuid /* r28 */) {
    // Local variables
    class TourBandLocal * const * bandIter; // r30
    class TourBandLocal * localBand; // r29
    class RemoteBandData * const * remoteIter; // r29
    class RemoteBandData * remoteBand; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8014111C -> 0x801412E8
unsigned char Profile::HasAdditionalMembersFromProfile(class Profile * const this /* r29 */, const class HxGuid & charGuid /* r30 */) {
    // Local variables
    class vector remoteRoster; // r1+0x40
    const struct BandMember * rosterIter; // r31
    class HxGuid remoteBandMemberGuid; // r1+0x30
}

// Range: 0x801412E8 -> 0x80141408
void Profile::AddNewBand(class Profile * const this /* r29 */, class TourBandLocal * pBand /* r1+0x8 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80141408 -> 0x80141420
int Profile::NumBands() {}

// Range: 0x80141420 -> 0x80141430
class TourBandLocal * Profile::GetBand() {}

// Range: 0x80141430 -> 0x80141624
void Profile::DeleteBand(class Profile * const this /* r31 */, const class HxGuid & bandGuid /* r27 */) {
    // Local variables
    class TourBandLocal * * bandIter; // r29
    class TourBandLocal * localBand; // r28
    class RemoteBandData * * remoteIter; // r28
    class RemoteBandData * remoteBand; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80141624 -> 0x80141658
unsigned char Profile::OwnsBand() {
    // Local variables
    class TourBandLocal * const * it; // r5
}

// Range: 0x80141658 -> 0x80141810
void Profile::FindAllBands(const class Profile * const this /* r29 */, class vector & bands /* r30 */) {
    // Local variables
    class TourBandLocal * const * bandIter; // r28
    class TourBandLocal * localBand; // r1+0x14
    class RemoteBandData * const * remoteIter; // r28
    class RemoteBandData * remoteBand; // r1+0x10

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

// Range: 0x80141810 -> 0x80141964
void Profile::AddNewRemoteBand(class Profile * const this /* r30 */, class RemoteBandData * pRemoteBand /* r1+0x8 */) {
    // Local variables
    int maxRemoteBands; // r0

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80141964 -> 0x80141B04
void Profile::DeleteRemoteBand(class Profile * const this /* r29 */, class RemoteBandData * pRemoteBand /* r1+0x8 */) {
    // Local variables
    class RemoteBandData * * it; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80141B04 -> 0x80141B88
class RemoteBandData * Profile::GetRemoteBand(class Profile * const this /* r29 */, const class HxGuid & guid /* r30 */) {
    // Local variables
    class RemoteBandData * * it; // r31
}

// Range: 0x80141B88 -> 0x80141C28
class RemoteBandData * Profile::GetRemoteBand(class Profile * const this /* r30 */, int i /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80141C28 -> 0x80141C9C
void Profile::SetComebackTarget(class Profile * const this /* r31 */, class User * target /* r30 */) {}

// Range: 0x80141C9C -> 0x80141CB8
unsigned char Profile::IsComebackTarget() {}

// Range: 0x80141CB8 -> 0x80141D0C
void Profile::UpdateSoloScore(class Profile * const this /* r31 */) {}

// Range: 0x80141D0C -> 0x80141D4C
void Profile::SetPendingBattleScore(class Profile * const this /* r31 */) {}

// Range: 0x80141D4C -> 0x80141DAC
void Profile::UpdateLeaderboards(class Profile * const this /* r30 */) {
    // Local variables
    class TourBandLocal * * it; // r31
}

static class Symbol career; // size: 0x4, address: 0x80A4BFD4
// Range: 0x80141DAC -> 0x80141EAC
int Profile::GetSongHighScore(const class Profile * const this /* r29 */, class Symbol & songName /* r30 */, enum TrackType type /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol career;
}

// Range: 0x80141EAC -> 0x80141EF8
void Profile::RecordHighScore(class Profile * const this /* r31 */) {}

// Range: 0x80141EF8 -> 0x80141F40
unsigned char Profile::IsSongUnlocked() {}

// Range: 0x80141F40 -> 0x80142040
void Profile::UnlockSong(class Profile * const this /* r29 */, class Symbol & song /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x80142040 -> 0x8014212C
void Profile::ResyncBandName(class Profile * const this /* r27 */, class TourBandLocal * pBand /* r28 */) {
    // Local variables
    class RemoteBandData * * remoteIter; // r30
    class RemoteBandData * remoteBand; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8014212C -> 0x80142240
void Profile::ResyncCharName(class Profile * const this /* r29 */, class CharData * pChar /* r28 */, unsigned char charNameUnchecked /* r27 */) {
    // Local variables
    const class HxGuid & charGuid; // r31
    const char * charName; // r30
    class vector bands; // r1+0xC
    class BandData * * it; // r29
    class BandData * pBand; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80142240 -> 0x801422C4
unsigned char Profile::IsModifierUnlocked() {}

// Range: 0x801422C4 -> 0x80142310
void Profile::UnlockModifier(class Profile * const this /* r31 */) {
    // Local variables
    struct pair result; // r1+0x8
}

// Range: 0x80142310 -> 0x8014239C
void Profile::Init(class Profile * const this /* r30 */, int padNum /* r31 */) {
    // References
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x8014239C -> 0x801423C0
unsigned char Profile::HasValidSaveData() {}

// Range: 0x801423C0 -> 0x801423C8
unsigned char Profile::HasCheated() {}

// Range: 0x801423C8 -> 0x801423D4
void Profile::MarkSaveDataAsCheated() {}

// Range: 0x801423D4 -> 0x8014248C
void Profile::SortDirtyRemoteBandsToFront(class Profile * const this /* r24 */) {
    // Local variables
    int countMinusOne; // r29
    int i; // r28
    int j; // r27
    class RemoteBandData * pBandA; // r26
    class RemoteBandData * pBandB; // r25
}

// Range: 0x8014248C -> 0x80142494
int Profile::GetPadNum() {}

// Range: 0x80142494 -> 0x8014249C
int Profile::GetPlayerNum() {}

// Range: 0x8014249C -> 0x801424A4
enum ProfileSaveState Profile::GetSaveState() {}

// Range: 0x801424A4 -> 0x801425BC
void Profile::SetSaveState(class Profile * const this /* r29 */, enum ProfileSaveState state /* r30 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801425BC -> 0x801425C4
unsigned char Profile::IsActive() {}

static struct DateTime defaultTimestamp; // size: 0x6, address: 0x809792E4
// Range: 0x801425C4 -> 0x80142674
struct DateTime & Profile::GetBotbNewsTimestamp(const class Profile * const this /* r28 */, class HxGuid & bandId /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> static struct DateTime defaultTimestamp;
}

static class String defaultCookies; // size: 0xC, address: 0x809792F8
// Range: 0x80142674 -> 0x80142734
class String & Profile::GetBotbNewsCookies(const class Profile * const this /* r28 */, class HxGuid & bandId /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> static class String defaultCookies;
}

// Range: 0x80142734 -> 0x801428F8
void Profile::SetBotbNewsCreds(class Profile * const this /* r27 */, class HxGuid & bandId /* r28 */, struct DateTime & t /* r29 */, class String & newCookies /* r30 */) {
    // Local variables
    int earlyIdx; // r25
    struct DateTime earliest; // r1+0x8
    int i; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x801428F8 -> 0x8014297C
void Profile::SetBotbNewsCredsCookiesOnly(class Profile * const this /* r27 */, class HxGuid & bandId /* r28 */, class String & newCookies /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x8014297C -> 0x80142984
int Profile::GetUploadFriendsToken() {}

// Range: 0x80142984 -> 0x8014298C
void Profile::SetUploadFriendsToken() {}

// Range: 0x8014298C -> 0x80142D78
void Profile::Save(class Profile * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int count; // r28
    int i; // r27
    struct _Rb_tree_iterator iter; // r1+0x40
    class Symbol sym; // r1+0x3C
    unsigned char hasComebackTarget; // r27
    int i; // r27
    int i; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4BFDC
// Range: 0x80142D78 -> 0x8014344C
void Profile::Load(class Profile * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int version; // r1+0x4C
    int count; // r1+0x48
    int i; // r31
    class TourBandLocal * band; // r1+0x44
    class RemoteBandData * remoteBand; // r1+0x40
    class Symbol lesson; // r1+0x3C
    int ignore; // r1+0x38
    struct BeatData bd; // r1+0x60
    class Symbol sym; // r1+0x34
    struct DateTime t; // r1+0x58
    int i; // r28
    int i; // r28
    int i; // r27

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_saving_feature;
    // -> const char * gNullStr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SongMgr & TheSongMgr;
    // -> class Tour * TheTour;
}

// Range: 0x8014344C -> 0x80143598
unsigned char Profile::IsUnsaved(const class Profile * const this /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class ProfileMgr TheProfileMgr;
}

static class ProfileChangedMsg msg; // size: 0x8, address: 0x80979310
// Range: 0x80143598 -> 0x801438B8
void Profile::SaveLoadComplete(class Profile * const this /* r30 */, enum ProfileSaveState saveState /* r31 */) {
    // Local variables
    int count; // r29
    int i; // r28

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> struct [anonymous] __vt__17ProfileChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ProfileChangedMsg msg;
}

// Range: 0x801438B8 -> 0x801439D0
unsigned char Profile::HasSomethingToUpload(class Profile * const this /* r31 */) {
    // Local variables
    int count; // r29
    int i; // r28
    int padNum; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4BFE4
// Range: 0x801439D0 -> 0x80143DA0
void Profile::DeleteAll(class Profile * const this /* r31 */) {
    // Local variables
    class TourCharLocal * * it; // r30
    class TourBandLocal * * it; // r30
    class RemoteBandData * * it; // r30

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_saving_feature;
}

// Range: 0x80143DA0 -> 0x80143E2C
class DataNode Profile::IsLessonComplete(class Profile * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x80143E2C -> 0x80143EEC
class DataNode Profile::SetLessonComplete(class Profile * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x80143EEC -> 0x80143F1C
unsigned char __eq() {}

// Range: 0x80143F1C -> 0x80143F78
unsigned char Profile::IsBeatComplete() {
    // Local variables
    struct BeatData bd; // r1+0x8
    unsigned char complete; // r0

    // References
    // -> const char * gNullStr;
}

// Range: 0x80143F78 -> 0x8014403C
void Profile::SetBeatComplete(class Profile * const this /* r30 */) {
    // Local variables
    struct BeatData bd; // r1+0x10

    // References
    // -> const char * gNullStr;
}

static class ProfileActivatedMsg msgActivated; // size: 0x8, address: 0x80979328
// Range: 0x8014403C -> 0x8014454C
class DataNode Profile::OnButtonDownMsg(class Profile * const this /* r31 */, const class ButtonDownMsg & msg /* r30 */) {
    // Local variables
    class DataNode ret; // r1+0x58

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__19ProfileActivatedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ProfileActivatedMsg msgActivated;
}

static class ProfileActivatedMsg msgActivated; // size: 0x8, address: 0x80979340
// Range: 0x8014454C -> 0x80144868
void Profile::Activate(class Profile * const this /* r30 */) {
    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__19ProfileActivatedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ProfileActivatedMsg msgActivated;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BFEC
static class Symbol _s; // size: 0x4, address: 0x80A4BFF4
static class Symbol _s; // size: 0x4, address: 0x80A4BFFC
static class Symbol _s; // size: 0x4, address: 0x80A4C004
static class Symbol _s; // size: 0x4, address: 0x80A4C00C
static class Symbol _s; // size: 0x4, address: 0x80A4C014
static class Symbol _s; // size: 0x4, address: 0x80A4C01C
static class Symbol _s; // size: 0x4, address: 0x80A4C024
static class Symbol _s; // size: 0x4, address: 0x80A4C02C
static class Symbol _s; // size: 0x4, address: 0x80A4C034
static class Symbol _s; // size: 0x4, address: 0x80A4C03C
// Range: 0x80144868 -> 0x801457F0
class DataNode Profile::Handle(class Profile * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x60
    class MessageTimer _mt; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode _n; // r1+0x70
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
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xC
} __vt__17ProfileChangedMsg; // size: 0xC, address: 0x80893984
struct {
    // total size: 0x8
} __RTTI__17ProfileChangedMsg; // size: 0x8, address: 0x808939B0
struct {
    // total size: 0x84
} __vt__7Profile; // size: 0x84, address: 0x808939F0
class _List_node : public _List_node_base {
    // total size: 0x30
public:
    struct SoloSongStatus _M_data; // offset 0x8, size 0x28
};
struct {
    // total size: 0x8
} __RTTI__P8BeatData; // size: 0x8, address: 0x80893B58
struct {
    // total size: 0x8
} __RTTI__PP14RemoteBandData; // size: 0x8, address: 0x80893B78
struct {
    // total size: 0x8
} __RTTI__PP13TourBandLocal; // size: 0x8, address: 0x80893B98
struct {
    // total size: 0x8
} __RTTI__PP8BandData; // size: 0x8, address: 0x80893BB0

