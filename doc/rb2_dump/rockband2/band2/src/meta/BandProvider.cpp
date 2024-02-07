/*
    Compile unit: C:\rockband2\band2\src\meta\BandProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800B7DA8 -> 0x800BB584
*/
class Symbol name; // size: 0x4, address: 0x80A4A65C
class Symbol name; // size: 0x4, address: 0x80A4A664
class DataArray * types; // size: 0x4, address: 0x80A4A668
class Symbol name; // size: 0x4, address: 0x80A4A670
class BandProvider * sBandProvider; // size: 0x4, address: 0x80A4A674
enum BandEntryType {
    kMetaBandCreate = 0,
    kMetaBandJoin = 1,
    kMetaBandProfileNotConnected = 2,
    kMetaBandProfileNotSignedIn = 3,
    kMetaBandProfileNotActive = 4,
    kMetaBandProfileActive = 5,
    kMetaBandInstructionSignIn = 6,
    kMetaBandInstructionNotActive = 7,
    kMetaBandName = 8,
};
struct BandEntry {
    // total size: 0x18
    enum BandEntryType mType; // offset 0x0, size 0x4
    class BandUser * mBandUser; // offset 0x4, size 0x4
    class BandData * mBandData; // offset 0x8, size 0x4
    class RndTex * mLogoTex; // offset 0xC, size 0x4
    class RndMat * mLogoMat; // offset 0x10, size 0x4
    class RndTexRenderer * mLogoRnd; // offset 0x14, size 0x4
};
// Range: 0x800B7DA8 -> 0x800B7DC4
void * BandEntry::BandEntry() {}

// Range: 0x800B7DC4 -> 0x800B7E80
void * BandEntry::~BandEntry(struct BandEntry * const this /* r30 */) {}

// Range: 0x800B7E80 -> 0x800B7EF4
static unsigned char ListHasOnlineID(const class vector & list /* r29 */, const class OnlineID * element /* r30 */) {
    // Local variables
    const class OnlineID * const * it; // r31
}

class BandProvider : public ListProvider, public Object {
    // total size: 0x50
    class RndTex * mTemplateTex; // offset 0x2C, size 0x4
    class RndMat * mTemplateMat; // offset 0x30, size 0x4
    int mSelected; // offset 0x34, size 0x4
    class vector mBands; // offset 0x38, size 0xC
    class list mPresenceResults; // offset 0x44, size 0x8
    class PresenceResultList * mPresenceRequest; // offset 0x4C, size 0x4
};
// Range: 0x800B7EF4 -> 0x800B7F80
void * BandProvider::BandProvider(class BandProvider * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12BandProvider;
    // -> struct [anonymous] __vt__12ListProvider;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BandEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BandEntry * _M_start; // offset 0x0, size 0x4
    struct BandEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _List_node : public _List_node_base {
    // total size: 0x28
public:
    class PresenceResultRow _M_data; // offset 0x8, size 0x20
};
// Range: 0x800B7F80 -> 0x800B80A8
void * BandProvider::~BandProvider(class BandProvider * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12BandProvider;
}

// Range: 0x800B80A8 -> 0x800B80F8
void BandProvider::Init() {
    // References
    // -> class BandProvider * sBandProvider;
}

// Range: 0x800B80F8 -> 0x800B8118
class DataNode BandProvider::OnGetBandProvider() {
    // References
    // -> class BandProvider * sBandProvider;
}

// Range: 0x800B8118 -> 0x800B8170
class BandProvider * BandProvider::GetInstance() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandProvider * sBandProvider;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800B8170 -> 0x800B8E40
void BandProvider::Reload(class BandProvider * const this /* r27 */) {
    // Local variables
    struct BandEntry simpleEntry; // r1+0xE8
    class vector unsortedProfiles; // r1+0xC0
    class vector profiles; // r1+0xB4
    int n; // r30
    int n; // r30
    int size; // r0
    class Profile * * it; // r30
    struct BandEntry be; // r1+0xD0
    class Profile * pProfile; // r29
    int iBand; // r26
    int i; // r28
    class vector remoteOwners; // r1+0xA8
    struct BandEntry * it; // r28
    class BandData * band; // r26
    int n; // r28
    class FilePath bitmap_path; // r1+0x9C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PPC8OnlineID;
    // -> unsigned char gStlAllocNameLookup;
    // -> class RockCentralGateway RockCentral;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
    // -> class GameMode * TheGameMode;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    const class OnlineID * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    const class OnlineID * * _M_start; // offset 0x0, size 0x4
    const class OnlineID * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PPC8OnlineID; // size: 0x8, address: 0x8087EBB0
// Range: 0x800B8E40 -> 0x800B8F98
void BandProvider::Clear(class BandProvider * const this /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x800B8F98 -> 0x800B907C
unsigned char BandProvider::ContainsLocalBand(class BandProvider * const this /* r28 */, const class HxGuid & guid /* r29 */) {
    // Local variables
    int n; // r30
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x800B907C -> 0x800B9140
class PresenceResultRow * BandProvider::GetPresenceInfo(const class BandProvider * const this /* r28 */, const class OnlineID * id /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0x18
}

// Range: 0x800B9140 -> 0x800B9220
void BandProvider::UpdateOwnerName(class BandProvider * const this /* r28 */, const class OnlineID * id /* r29 */, const char * name /* r30 */) {
    // Local variables
    int n; // r31
    class RemoteBandData * bandData; // r0

    // References
    // -> struct [anonymous] __RTTI__8BandData;
    // -> struct [anonymous] __RTTI__14RemoteBandData;
}

static class Message uiMsg; // size: 0x8, address: 0x80977E00
// Range: 0x800B9220 -> 0x800B94BC
class DataNode BandProvider::OnMsg(class BandProvider * const this /* r30 */) {
    // Local variables
    const class list * newResults; // r31
    struct _List_iterator it; // r1+0x24
    class OnlineID id; // r1+0x38

    // References
    // -> class UIManager TheUI;
    // -> static class Message uiMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std31_List_node<17PresenceResultRow>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std31_List_node<17PresenceResultRow>; // size: 0x8, address: 0x8087EC00
// Range: 0x800B94BC -> 0x800B9548
unsigned char BandProvider::IsBandLocal(const class BandProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B9548 -> 0x800B9608
unsigned char BandProvider::IsPosJoinBand(const class BandProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B9608 -> 0x800B96C8
unsigned char BandProvider::IsPosBand(const class BandProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B96C8 -> 0x800B9788
unsigned char BandProvider::IsPosSignInInstruction(const class BandProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B9788 -> 0x800B9848
unsigned char BandProvider::IsPosNotActiveInstruction(const class BandProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B9848 -> 0x800B98E0
void BandProvider::SetDefaultBandPos(class BandProvider * const this /* r30 */, int pos /* r31 */) {
    // References
    // -> class Tour * TheTour;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B98E0 -> 0x800B9990
enum ShowGamercardResult BandProvider::ShowGamercard(class BandProvider * const this /* r29 */, int pos /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol start; // size: 0x4, address: 0x80A4A67C
static class Symbol start_desc; // size: 0x4, address: 0x80A4A684
static class Symbol instrument; // size: 0x4, address: 0x80A4A68C
static class Symbol padnum; // size: 0x4, address: 0x80A4A694
static class Symbol gamertag; // size: 0x4, address: 0x80A4A69C
static class Symbol instruction; // size: 0x4, address: 0x80A4A6A4
static class Symbol instruction_desc; // size: 0x4, address: 0x80A4A6AC
static class Symbol name; // size: 0x4, address: 0x80A4A6B4
static class Symbol owner_name; // size: 0x4, address: 0x80A4A6BC
static class Symbol owner_online; // size: 0x4, address: 0x80A4A6C4
static class Symbol rating_stars; // size: 0x4, address: 0x80A4A6CC
static class Symbol rating_diff; // size: 0x4, address: 0x80A4A6D4
static class Symbol band_chooser_create; // size: 0x4, address: 0x80A4A6DC
static class Symbol band_chooser_create_desc; // size: 0x4, address: 0x80A4A6E4
static class Symbol band_chooser_join; // size: 0x4, address: 0x80A4A6EC
static class Symbol band_chooser_join_desc; // size: 0x4, address: 0x80A4A6F4
static class Symbol band_chooser_not_connected; // size: 0x4, address: 0x80A4A6FC
static class Symbol band_chooser_not_signed_in; // size: 0x4, address: 0x80A4A704
static class Symbol band_chooser_not_signed_in_desc; // size: 0x4, address: 0x80A4A70C
static class Symbol band_chooser_not_active; // size: 0x4, address: 0x80A4A714
static class Symbol band_chooser_not_active_desc; // size: 0x4, address: 0x80A4A71C
// Range: 0x800B9990 -> 0x800BA120
char * BandProvider::Text(const class BandProvider * const this /* r28 */, int data /* r30 */, class Symbol & slot /* r29 */) {
    // Local variables
    const char * bands; // r3
    const class PresenceResultRow * presence; // r0

    // References
    // -> const char * gNullStr;
    // -> static class Symbol band_chooser_not_active_desc;
    // -> static class Symbol band_chooser_not_active;
    // -> static class Symbol band_chooser_not_signed_in_desc;
    // -> static class Symbol band_chooser_not_signed_in;
    // -> static class Symbol band_chooser_not_connected;
    // -> static class Symbol band_chooser_join_desc;
    // -> static class Symbol band_chooser_join;
    // -> static class Symbol band_chooser_create_desc;
    // -> static class Symbol band_chooser_create;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol rating_diff;
    // -> static class Symbol rating_stars;
    // -> static class Symbol owner_online;
    // -> static class Symbol owner_name;
    // -> static class Symbol name;
    // -> static class Symbol instruction_desc;
    // -> static class Symbol instruction;
    // -> static class Symbol gamertag;
    // -> static class Symbol padnum;
    // -> static class Symbol instrument;
    // -> static class Symbol start_desc;
    // -> static class Symbol start;
}

static class Symbol logo; // size: 0x4, address: 0x80A4A724
// Range: 0x800BA120 -> 0x800BA220
class RndMat * BandProvider::Mat(const class BandProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol logo;
}

static class Symbol rating; // size: 0x4, address: 0x80A4A72C
class ListAlphable {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class PlayerDiffIcon : public UIComponent, public ListAlphable {
    // total size: 0x1A0
    class vector mPlayerMeshes; // offset 0x134, size 0xC
    class RndMat * mPlayerMat; // offset 0x140, size 0x4
    class RndMat * mNoPlayerMat; // offset 0x144, size 0x4
    class vector mDiffLabels; // offset 0x148, size 0xC
    int mNumPlayers; // offset 0x154, size 0x4
    int mDiff; // offset 0x158, size 0x4
    float mAlpha; // offset 0x15C, size 0x4
};
// Range: 0x800BA220 -> 0x800BA368
void BandProvider::Custom(const class BandProvider * const this /* r27 */, int data /* r28 */, class Symbol & slot /* r30 */, class Object * o /* r29 */) {
    // Local variables
    class PlayerDiffIcon * pdi; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14PlayerDiffIcon;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol rating;
}

// Range: 0x800BA368 -> 0x800BA390
int BandProvider::NumData() {}

// Range: 0x800BA390 -> 0x800BA428
unsigned char BandProvider::IsActive() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800BA428 -> 0x800BA454
void BandProvider::PreDraw() {
    // Local variables
    class RndTexRenderer * r; // r3
}

static class Symbol _s; // size: 0x4, address: 0x80A4A734
static class Symbol _s; // size: 0x4, address: 0x80A4A73C
static class Symbol _s; // size: 0x4, address: 0x80A4A744
static class Symbol _s; // size: 0x4, address: 0x80A4A74C
static class Symbol _s; // size: 0x4, address: 0x80A4A754
static class Symbol _s; // size: 0x4, address: 0x80A4A75C
static class Symbol _s; // size: 0x4, address: 0x80A4A764
static class Symbol _s; // size: 0x4, address: 0x80A4A76C
static class Symbol _s; // size: 0x4, address: 0x80A4A774
static class Symbol _s; // size: 0x4, address: 0x80A4A77C
static class Symbol _s; // size: 0x4, address: 0x80A4A784
static class Symbol _s; // size: 0x4, address: 0x80A4A78C
// Range: 0x800BA454 -> 0x800BB45C
class DataNode BandProvider::Handle(class BandProvider * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x58
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__24RockCentralOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class BandSelectPanel : public UIPanel {
    // total size: 0x5C
};
// Range: 0x800BB45C -> 0x800BB54C
void BandSelectPanel::Draw(class BandSelectPanel * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x800BB54C -> 0x800BB584
void BandSelectPanel::Unload(class BandSelectPanel * const this /* r31 */) {}

struct {
    // total size: 0x8
} __RTTI__14RemoteBandData; // size: 0x8, address: 0x8087F118
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ListSlot * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ListSlot * * _M_start; // offset 0x0, size 0x4
    class ListSlot * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ListElement : public RndTransformable {
    // total size: 0x100
    class vector mSlots; // offset 0xB8, size 0xC
    float mFade; // offset 0xC4, size 0x4
};
struct {
    // total size: 0xAC
} __vt__15BandSelectPanel; // size: 0xAC, address: 0x8087F160
struct {
    // total size: 0x8
} __RTTI__15BandSelectPanel; // size: 0x8, address: 0x8087F240
struct {
    // total size: 0x9C
} __vt__12BandProvider; // size: 0x9C, address: 0x8087F248
struct {
    // total size: 0x8
} __RTTI__12BandProvider; // size: 0x8, address: 0x8087F310
struct {
    // total size: 0x8
} __RTTI__6RndTex; // size: 0x8, address: 0x8087F3C8
struct {
    // total size: 0x8
} __RTTI__14PlayerDiffIcon; // size: 0x8, address: 0x8087F4A0
struct {
    // total size: 0x8
} __RTTI__12ListAlphable; // size: 0x8, address: 0x8087F4B8
struct {
    // total size: 0x8
} __RTTI__PP7Profile; // size: 0x8, address: 0x8087F6B0
struct {
    // total size: 0x8
} __RTTI__PQ212BandProvider9BandEntry; // size: 0x8, address: 0x8087F6D8

