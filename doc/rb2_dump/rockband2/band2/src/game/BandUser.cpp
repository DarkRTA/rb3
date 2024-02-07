/*
    Compile unit: C:\rockband2\band2\src\game\BandUser.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80044370 -> 0x80046984
*/
static class Symbol none; // size: 0x4, address: 0x80A49214
// Range: 0x80044370 -> 0x80044434
void * BandUser::BandUser(class BandUser * const this /* r29 */) {
    // References
    // -> static class Symbol none;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__8BandUser;
}

// Range: 0x80044434 -> 0x80044500
void * BandUser::~BandUser(class BandUser * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8BandUser;
}

// Range: 0x80044500 -> 0x80044540
class BandUser * BandUser::NewBandUser(int playerNum /* r31 */) {}

static class Symbol none; // size: 0x4, address: 0x80A4921C
// Range: 0x80044540 -> 0x80044604
void BandUser::Reset(class BandUser * const this /* r31 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class CharCache * TheCharCache;
    // -> static class Symbol none;
}

// Range: 0x80044604 -> 0x8004460C
enum Difficulty BandUser::GetDifficulty() {}

// Range: 0x8004460C -> 0x80044614
class Symbol BandUser::GetDifficultySym() {}

// Range: 0x80044614 -> 0x800446EC
void BandUser::SetDifficulty(class BandUser * const this /* r29 */, enum Difficulty d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800446EC -> 0x80044730
void BandUser::SetDifficulty(class BandUser * const this /* r31 */) {}

// Range: 0x80044730 -> 0x80044738
enum TrackType BandUser::GetTrackType() {}

// Range: 0x80044738 -> 0x80044740
class Symbol BandUser::GetTrackSym() {}

// Range: 0x80044740 -> 0x800447CC
void BandUser::SetTrackType(class BandUser * const this /* r30 */, enum TrackType t /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800447CC -> 0x80044810
void BandUser::SetTrackType(class BandUser * const this /* r31 */) {}

// Range: 0x80044810 -> 0x80044818
enum ControllerType BandUser::GetControllerType() {}

// Range: 0x80044818 -> 0x80044820
class Symbol BandUser::GetControllerSym() {}

// Range: 0x80044820 -> 0x800448AC
void BandUser::SetControllerType(class BandUser * const this /* r30 */, enum ControllerType ControllerType /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800448AC -> 0x800448F0
void BandUser::SetControllerType(class BandUser * const this /* r31 */) {}

// Range: 0x800448F0 -> 0x80044904
unsigned char BandUser::HasChar() {}

// Range: 0x80044904 -> 0x8004490C
class CharData * BandUser::GetChar() {}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct OutfitPref {
    // total size: 0x18
    class Symbol mCategory; // offset 0x0, size 0x4
    class Symbol mOutfit; // offset 0x4, size 0x4
    class vector mColorPrefs; // offset 0x8, size 0xC
    int mPatchIdx; // offset 0x14, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct ClosetOutfit {
    // total size: 0x8
    class Symbol mCategory; // offset 0x0, size 0x4
    class Symbol mOutfit; // offset 0x4, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    class Symbol second; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    int second; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct OutfitGroup {
    // total size: 0x14
    class Symbol mCategory; // offset 0x0, size 0x4
    class list mSelectedVariants; // offset 0x4, size 0x8
    class list mSelectedPatches; // offset 0xC, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class TourCharLocal : public CharData, public TourSavable {
    // total size: 0xA0
protected:
    class list mOutfitPrefs; // offset 0x40, size 0x8
private:
    class String mCharName; // offset 0x48, size 0xC
    class Symbol mHometown; // offset 0x54, size 0x4
    int mMoney; // offset 0x58, size 0x4
    class list mCloset; // offset 0x5C, size 0x8
    int mMoneySpentOnOutfits; // offset 0x64, size 0x4
    class list mOutfitGroups; // offset 0x68, size 0x8
    unsigned char mEyebrowsMatchHair; // offset 0x70, size 0x1
};
// Range: 0x8004490C -> 0x8004499C
class TourCharLocal * BandUser::GetCharLocal(class BandUser * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004499C -> 0x80044A80
void BandUser::SetChar(class BandUser * const this /* r29 */, class CharData * char_data /* r30 */, unsigned char update_data /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80044A80 -> 0x80044B3C
void BandUser::UpdateRemoteChar(class BandUser * const this /* r30 */, class DataArray * char_data /* r31 */) {
    // References
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80044B3C -> 0x80044B4C
int BandUser::GetSlot(const class BandUser * const this /* r4 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80044B4C -> 0x80044BA4
class GameplayOptions * BandUser::GetGameplayOptions(class BandUser * const this /* r31 */) {
    // Local variables
    class GameplayOptions * result; // r3

    // References
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x80044BA4 -> 0x80044BB4
unsigned char BandUser::IsParticipating(const class BandUser * const this /* r4 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x80044BB4 -> 0x80044C20
char * BandUser::IntroName(const class BandUser * const this /* r31 */) {
    // Local variables
    class TourCharLocal * tc; // r0

    // References
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x80044C20 -> 0x80044CAC
char * BandUser::CharacterName(const class BandUser * const this /* r31 */) {
    // Local variables
    class TourCharLocal * tc; // r0

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
}

// Range: 0x80044CAC -> 0x80044CB4
char * BandUser::GetUserName() {}

// Range: 0x80044CB4 -> 0x80044CD4
void BandUser::SetNetUIState() {
    // Local variables
    enum NetUIState oldState; // r0
}

// Range: 0x80044CD4 -> 0x80044CDC
enum NetUIState BandUser::GetNetUIState() {}

// Range: 0x80044CDC -> 0x80044CF4
unsigned char BandUser::NetSynchronized() {}

// Range: 0x80044CF4 -> 0x80044D9C
unsigned char BandUser::CanSaveData(class BandUser * const this /* r29 */) {
    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80044D9C -> 0x80044DA0
unsigned char BandUser::CanGetAchievements() {}

// Range: 0x80044DA0 -> 0x80044E58
unsigned char BandUser::IsLocalPlayer(const class BandUser * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x80044E58 -> 0x80044ECC
unsigned char BandUser::IsJoypadConnected(const class BandUser * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol joypad; // size: 0x4, address: 0x80A49224
static class Symbol instrument_mapping; // size: 0x4, address: 0x80A4922C
// Range: 0x80044ECC -> 0x80045068
enum ControllerType BandUser::ConnectedControllerType(const class BandUser * const this /* r30 */) {
    // Local variables
    enum ControllerType ctOverride; // r0
    class Symbol controller; // r1+0x18
    class DataArray * cfg; // r0
    class DataArray * data; // r30
    enum ControllerType ct; // r30

    // References
    // -> static class Symbol instrument_mapping;
    // -> static class Symbol joypad;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80045068 -> 0x80045380
void BandUser::SyncSave(const class BandUser * const this /* r30 */, class BinStream & dest /* r31 */, unsigned int dirtyMask /* r28 */) {
    // Local variables
    class String charName; // r1+0x1C
    class TourCharLocal * localChar; // r0
    enum Difficulty diff; // r0

    // References
    // -> struct [anonymous] __RTTI__14TourCharRemote;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__13TourCharLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PrefabChar * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PrefabChar * * _M_start; // offset 0x0, size 0x4
    class PrefabChar * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PrefabChar : public CharData {
    // total size: 0x58
};
class TourCharRemote : public PrefabChar {
    // total size: 0x58
};
// Range: 0x80045380 -> 0x800456F8
void BandUser::SyncLoad(class BandUser * const this /* r27 */, class BinStream & src /* r28 */, unsigned int dirtyMask /* r29 */) {
    // Local variables
    unsigned char diff; // r1+0xC
    unsigned char trackType; // r1+0xB
    unsigned char ct; // r1+0xA
    unsigned char uiState; // r1+0x9
    class String charName; // r1+0x20
    class TourCharRemote * remoteChar; // r26
    int diff; // r1+0x1C
    class TourCharRemote * remoteChar; // r26
    class DataArray * char_data; // r1+0x18
    class Symbol prefab; // r1+0x14

    // References
    // -> const char * gNullStr;
    // -> class CharCache * TheCharCache;
    // -> class ProfileMgr TheProfileMgr;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__14TourCharRemote;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Net TheNet;
}

// Range: 0x800456F8 -> 0x80045760
void BandUser::UpdateData(class BandUser * const this /* r29 */, unsigned int dirtyMask /* r30 */) {
    // References
    // -> class Net TheNet;
}

// Range: 0x80045760 -> 0x80045768
void BandUser::UpdateCharWinDiff() {}

// Range: 0x80045768 -> 0x80045850
class DataNode BandUser::OnSetDifficulty(class BandUser * const this /* r31 */) {
    // Local variables
    const class DataNode & arg; // r0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80045850 -> 0x8004591C
class DataNode BandUser::OnSetTrackType(class BandUser * const this /* r31 */) {
    // Local variables
    const class DataNode & arg; // r3

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8004591C -> 0x80045A30
class DataNode BandUser::OnSetControllerType(class BandUser * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & arg; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80045A30 -> 0x80045B0C
class DataNode BandUser::OnSetChar(class BandUser * const this /* r31 */) {
    // Local variables
    const class DataNode & arg; // r0

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharData;
}

// Range: 0x80045B0C -> 0x80045B14
unsigned char BandUser::HasAsFriend() {}

static class Symbol _s; // size: 0x4, address: 0x80A49234
static class Symbol _s; // size: 0x4, address: 0x80A4923C
static class Symbol _s; // size: 0x4, address: 0x80A49244
static class Symbol _s; // size: 0x4, address: 0x80A4924C
static class Symbol _s; // size: 0x4, address: 0x80A49254
static class Symbol _s; // size: 0x4, address: 0x80A4925C
static class Symbol _s; // size: 0x4, address: 0x80A49264
static class Symbol _s; // size: 0x4, address: 0x80A4926C
static class Symbol _s; // size: 0x4, address: 0x80A49274
static class Symbol _s; // size: 0x4, address: 0x80A4927C
static class Symbol _s; // size: 0x4, address: 0x80A49284
static class Symbol _s; // size: 0x4, address: 0x80A4928C
static class Symbol _s; // size: 0x4, address: 0x80A49294
static class Symbol _s; // size: 0x4, address: 0x80A4929C
static class Symbol _s; // size: 0x4, address: 0x80A492A4
static class Symbol _s; // size: 0x4, address: 0x80A492AC
static class Symbol _s; // size: 0x4, address: 0x80A492B4
static class Symbol _s; // size: 0x4, address: 0x80A492BC
static class Symbol _s; // size: 0x4, address: 0x80A492C4
static class Symbol _s; // size: 0x4, address: 0x80A492CC
static class Symbol _s; // size: 0x4, address: 0x80A492D4
static class Symbol _s; // size: 0x4, address: 0x80A492DC
static class Symbol _s; // size: 0x4, address: 0x80A492E4
static class Symbol _s; // size: 0x4, address: 0x80A492EC
static class Symbol _s; // size: 0x4, address: 0x80A492F4
static class Symbol _s; // size: 0x4, address: 0x80A492FC
// Range: 0x80045B14 -> 0x800466EC
class DataNode BandUser::Handle(class BandUser * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

class DebugNotifier {
    // total size: 0x1
};
static class Symbol _s; // size: 0x4, address: 0x80A49304
static class Symbol _s; // size: 0x4, address: 0x80A4930C
// Range: 0x800466EC -> 0x80046984
unsigned char BandUser::SyncProperty(class BandUser * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__14TourCharRemote; // size: 0x8, address: 0x80872638
struct {
    // total size: 0x8
} __RTTI__13TourCharLocal; // size: 0x8, address: 0x80872680
struct {
    // total size: 0x8
} __RTTI__11TourSavable; // size: 0x8, address: 0x808726A8
struct {
    // total size: 0x8
} __RTTI__10PrefabChar; // size: 0x8, address: 0x808726E0
struct {
    // total size: 0x8
} __RTTI__8CharData; // size: 0x8, address: 0x80872710
struct {
    // total size: 0x8
} __RTTI__8CharDesc; // size: 0x8, address: 0x80872738
struct {
    // total size: 0x70
} __vt__8BandUser; // size: 0x70, address: 0x80872740
struct {
    // total size: 0x8
} __RTTI__8BandUser; // size: 0x8, address: 0x808727D8
struct {
    // total size: 0x8
} __RTTI__4User; // size: 0x8, address: 0x80872800

