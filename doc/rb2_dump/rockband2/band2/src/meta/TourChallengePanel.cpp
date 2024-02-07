/*
    Compile unit: C:\rockband2\band2\src\meta\TourChallengePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801C5ECC -> 0x801C8550
*/
class DataArray * types; // size: 0x4, address: 0x80A4DA58
class Symbol album; // size: 0x4, address: 0x80A4DA60
class Symbol newburst; // size: 0x4, address: 0x80A4DA68
class Symbol playerdiff; // size: 0x4, address: 0x80A4DA70
class Symbol name; // size: 0x4, address: 0x80A4DA78
class Symbol new_sym; // size: 0x4, address: 0x80A4DA80
class Symbol icon; // size: 0x4, address: 0x80A4DA88
class Symbol in_progress; // size: 0x4, address: 0x80A4DA90
class Symbol tour_new; // size: 0x4, address: 0x80A4DA98
class Symbol tour_challenge_in_progress; // size: 0x4, address: 0x80A4DAA0
// Range: 0x801C5ECC -> 0x801C5FA0
void * TourChallengePanel::TourChallengePanel(class TourChallengePanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18TourChallengePanel;
    // -> struct [anonymous] __vt__12TexLoadPanel;
    // -> struct [anonymous] __vt__Q210ContentMgr8Callback;
}

// Range: 0x801C5FA0 -> 0x801C60BC
void * TourChallengePanel::~TourChallengePanel(class TourChallengePanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__18TourChallengePanel;
}

static class Symbol new_challenges; // size: 0x4, address: 0x80A4DAA8
// Range: 0x801C6144 -> 0x801C658C
void TourChallengePanel::Load(class TourChallengePanel * const this /* r25 */) {
    // Local variables
    const char * path_fmt; // r26
    class DynamicTex * dlc; // r0
    class DynamicTex * loading; // r0
    class TourBand * tb; // r0
    const class vector & challenges; // r0
    class TourChallengeEvent * const * c; // r24
    class TourChallengeEvent * e; // r27
    const char * art; // r27
    class Symbol song; // r1+0x5C
    const char * path; // r0

    // References
    // -> const char * gNullStr;
    // -> class SongMgr & TheSongMgr;
    // -> struct [anonymous] __vt__17ChallengeProvider;
    // -> static class Symbol new_challenges;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
}

class _Temporary_buffer {
    // total size: 0xC
    long _M_original_len; // offset 0x0, size 0x4
    long _M_len; // offset 0x4, size 0x4
    class TourChallengeEvent * * _M_buffer; // offset 0x8, size 0x4
};
// Range: 0x801C658C -> 0x801C65C0
void TourChallengePanel::Enter(class TourChallengePanel * const this /* r31 */) {}

// Range: 0x801C65C0 -> 0x801C661C
void TourChallengePanel::Unload(class TourChallengePanel * const this /* r31 */) {}

// Range: 0x801C661C -> 0x801C6748
class TourChallengeEvent * TourChallengePanel::SelectedEvent(class TourChallengePanel * const this /* r28 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801C6748 -> 0x801C67DC
class DataNode TourChallengePanel::OnMsg(class TourChallengePanel * const this /* r30 */) {
    // Local variables
    class TourBandLocal * tb; // r31

    // References
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Tour * TheTour;
}

static class Symbol new_challenges; // size: 0x4, address: 0x80A4DAB0
static class Symbol tour_challenge_tier; // size: 0x4, address: 0x80A4DAB8
static class Message msg; // size: 0x8, address: 0x8097A088
// Range: 0x801C67DC -> 0x801C6DA4
void TourChallengePanel::Refresh(class TourChallengePanel * const this /* r26 */) {
    // Local variables
    unsigned char using_new; // r0
    class TourBand * tb; // r25
    class TourChallengeEvent * e; // r25

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol tour_challenge_tier;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Tour * TheTour;
    // -> static class Symbol new_challenges;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol cancel; // size: 0x4, address: 0x80A4DAC0
static class Symbol confirm; // size: 0x4, address: 0x80A4DAC8
static class Symbol helpbar_back; // size: 0x4, address: 0x80A4DAD0
static class Symbol helpbar_select; // size: 0x4, address: 0x80A4DAD8
// Range: 0x801C6DA4 -> 0x801C7518
void TourChallengePanel::UpdateHelpbar(class TourChallengePanel * const this /* r29 */) {
    // Local variables
    class UIList * l; // r30
    enum TourStatus s; // r0

    // References
    // -> class HelpBarPanel * sInstance;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol helpbar_select;
    // -> static class Symbol helpbar_back;
    // -> static class Symbol confirm;
    // -> static class Symbol cancel;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x801C7518 -> 0x801C7558
class DataNode TourChallengePanel::OnMsg() {}

static class Symbol _s; // size: 0x4, address: 0x80A4DAE0
static class Symbol _s; // size: 0x4, address: 0x80A4DAE8
// Range: 0x801C7558 -> 0x801C7D34
class DataNode TourChallengePanel::Handle(class TourChallengePanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__20UIComponentScrollMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__20UIComponentSelectMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class ChallengeProvider : public ListProvider {
    // total size: 0x2C
public:
    const class TourBand & mBand; // offset 0x4, size 0x4
    class vector mChallenges; // offset 0x8, size 0xC
    class RndDir * mResourceDir; // offset 0x14, size 0x4
    class RndMat * mGenericMat; // offset 0x18, size 0x4
    class RndMat * mLockedMat; // offset 0x1C, size 0x4
    class RndMat * mNewburstMat; // offset 0x20, size 0x4
    class RndMat * mDefaultDLCMat; // offset 0x24, size 0x4
    const class vector & mCovers; // offset 0x28, size 0x4
};
// Range: 0x801C7D34 -> 0x801C7D44
class Symbol ChallengeProvider::DataSymbol() {}

// Range: 0x801C7D44 -> 0x801C7D5C
int ChallengeProvider::NumData() {}

// Range: 0x801C7D5C -> 0x801C7F38
class RndMat * ChallengeProvider::Mat(const class ChallengeProvider * const this /* r31 */, int data /* r30 */, class Symbol & slot /* r29 */) {
    // Local variables
    class TourChallengeEvent * e; // r30
    class String name; // r1+0x10
    class DynamicTex * const * c; // r0

    // References
    // -> class Debug TheDebug;
    // -> class Symbol newburst;
    // -> class Symbol album;
}

// Range: 0x801C7F38 -> 0x801C809C
void ChallengeProvider::Custom(const class ChallengeProvider * const this /* r31 */, int data /* r30 */, class Symbol & slot /* r29 */, class Object * o /* r28 */) {
    // Local variables
    class PlayerDiffIcon * pdi; // r29
    class TourChallengeEvent * e; // r28
    enum TourStatus s; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14PlayerDiffIcon;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Symbol playerdiff;
}

// Range: 0x801C809C -> 0x801C8300
char * ChallengeProvider::Text(const class ChallengeProvider * const this /* r30 */, int data /* r28 */, class Symbol & slot /* r31 */) {
    // Local variables
    class TourChallengeEvent * e; // r28
    enum TourStatus s; // r0
    unsigned char incomplete; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Symbol tour_challenge_in_progress;
    // -> class Symbol tour_new;
    // -> const char * gNullStr;
    // -> class Symbol in_progress;
    // -> class Symbol icon;
    // -> class Symbol new_sym;
    // -> class Symbol name;
}

// Range: 0x801C8300 -> 0x801C8550
void ChallengeProvider::InitData(class ChallengeProvider * const this /* r29 */, class RndDir * dir /* r30 */) {
    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x44
} __vt__17ChallengeProvider; // size: 0x44, address: 0x808A2C58
struct {
    // total size: 0x8
} __RTTI__17ChallengeProvider; // size: 0x8, address: 0x808A2CC0
struct {
    // total size: 0xF4
} __vt__18TourChallengePanel; // size: 0xF4, address: 0x808A3118
struct {
    // total size: 0x8
} __RTTI__18TourChallengePanel; // size: 0x8, address: 0x808A3250

