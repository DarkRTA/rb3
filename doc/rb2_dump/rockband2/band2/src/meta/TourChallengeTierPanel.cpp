/*
    Compile unit: C:\rockband2\band2\src\meta\TourChallengeTierPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801C18BC -> 0x801C424C
*/
class DataArray * types; // size: 0x4, address: 0x80A4D9C8
class Symbol disabled; // size: 0x4, address: 0x80A4D9D0
class Symbol album; // size: 0x4, address: 0x80A4D9D8
class Symbol newburst; // size: 0x4, address: 0x80A4D9E0
class Symbol tier_name; // size: 0x4, address: 0x80A4D9E8
class Symbol available; // size: 0x4, address: 0x80A4D9F0
class Symbol new_sym; // size: 0x4, address: 0x80A4D9F8
class Symbol tour_challenge_tier_locked; // size: 0x4, address: 0x80A4DA00
class Symbol tour_challenge_completed; // size: 0x4, address: 0x80A4DA08
class Symbol tour_challenge_tier_locked_desc; // size: 0x4, address: 0x80A4DA10
class Symbol tour_new; // size: 0x4, address: 0x80A4DA18
class TourChallengeTierPanel * sInstance; // size: 0x4, address: 0x80A4DA1C
// Range: 0x801C18BC -> 0x801C1948
void * TourChallengeTierPanel::TourChallengeTierPanel(class TourChallengeTierPanel * const this /* r30 */) {
    // References
    // -> class TourChallengeTierPanel * sInstance;
    // -> struct [anonymous] __vt__22TourChallengeTierPanel;
}

// Range: 0x801C1948 -> 0x801C1A18
void * TourChallengeTierPanel::~TourChallengeTierPanel(class TourChallengeTierPanel * const this /* r29 */) {
    // References
    // -> class TourChallengeTierPanel * sInstance;
    // -> struct [anonymous] __vt__22TourChallengeTierPanel;
}

class vector : protected _Vector_base {
    // total size: 0xC
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
class StlNodeAlloc {
    // total size: 0x1
};
// Range: 0x801C1B64 -> 0x801C1C44
void TourChallengeTierPanel::Enter(class TourChallengeTierPanel * const this /* r29 */) {
    // Local variables
    class TourChallenge & tc; // r30
    class TourBand * tb; // r0

    // References
    // -> struct [anonymous] __vt__21ChallengeTierProvider;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
}

// Range: 0x801C1C44 -> 0x801C1C9C
void TourChallengeTierPanel::Unload(class TourChallengeTierPanel * const this /* r31 */) {}

// Range: 0x801C1C9C -> 0x801C25C0
void TourChallengeTierPanel::Refresh(class TourChallengeTierPanel * const this /* r25 */) {
    // Local variables
    class TourBand * tb; // r21
    int diff_tier; // r27
    enum ChallengeFocus cf; // r0
    class TourChallengeEvent * e; // r0
    class vector & tiers; // r0
    int data; // r26
    int data; // r26
    class vector tier; // r1+0xD8

    // References
    // -> class Tour * TheTour;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP18TourChallengeEvent;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _IsPOD {
    // total size: 0x1
};
struct TierLessThan {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801C25C0 -> 0x801C27EC
class DataNode TourChallengeTierPanel::OnMsg(class TourChallengeTierPanel * const this /* r26 */, const class UIComponentSelectMsg & msg /* r27 */) {
    // Local variables
    class TourBandLocal * tbl; // r28
    class UIList * l; // r29
    class vector & tier; // r0
    int selected_tier; // r0
    class TourChallengeEvent * e; // r30
    class TourChallengeEvent * * c; // r27

    // References
    // -> struct [anonymous] __RTTI__6UIList;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Tour * TheTour;
}

static class Symbol cancel; // size: 0x4, address: 0x80A4DA24
static class Symbol confirm; // size: 0x4, address: 0x80A4DA2C
static class Symbol helpbar_back; // size: 0x4, address: 0x80A4DA34
static class Symbol helpbar_select; // size: 0x4, address: 0x80A4DA3C
// Range: 0x801C27EC -> 0x801C2F90
void TourChallengeTierPanel::UpdateHelpbar(class TourChallengeTierPanel * const this /* r30 */) {
    // Local variables
    class UIList * l; // r29

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

// Range: 0x801C2F90 -> 0x801C2FD0
class DataNode TourChallengeTierPanel::OnMsg() {}

static class Symbol _s; // size: 0x4, address: 0x80A4DA44
static class Symbol _s; // size: 0x4, address: 0x80A4DA4C
static class Symbol _s; // size: 0x4, address: 0x80A4DA54
// Range: 0x801C2FD0 -> 0x801C38DC
class DataNode TourChallengeTierPanel::Handle(class TourChallengeTierPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
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
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class ChallengeTierProvider : public ListProvider {
    // total size: 0x2C
public:
    const class TourBand & mBand; // offset 0x4, size 0x4
    const class TourChallenge & mTourChallenge; // offset 0x8, size 0x4
    class vector mTiers; // offset 0xC, size 0xC
    class RndMat * mLockedMat; // offset 0x18, size 0x4
    class RndMat * mBurstMat; // offset 0x1C, size 0x4
    class vector mTierMats; // offset 0x20, size 0xC
};
// Range: 0x801C38DC -> 0x801C39A0
class Symbol ChallengeTierProvider::State(const class ChallengeTierProvider * const this /* r28 */, class Symbol & component_state /* r29 */) {
    // References
    // -> class Symbol disabled;
}

// Range: 0x801C39A0 -> 0x801C3A18
class Symbol ChallengeTierProvider::DataSymbol() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801C3A18 -> 0x801C3A40
int ChallengeTierProvider::NumData() {}

// Range: 0x801C3A40 -> 0x801C3BF0
class RndMat * ChallengeTierProvider::Mat(const class ChallengeTierProvider * const this /* r31 */, int data /* r29 */, class Symbol & slot /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> class Symbol newburst;
    // -> class Symbol album;
}

// Range: 0x801C3BF0 -> 0x801C3FBC
char * ChallengeTierProvider::Text(const class ChallengeTierProvider * const this /* r30 */, int data /* r28 */, class Symbol & slot /* r29 */) {
    // References
    // -> class Symbol tour_new;
    // -> class Symbol tour_challenge_tier_locked_desc;
    // -> class Symbol tour_challenge_completed;
    // -> const char * gNullStr;
    // -> class Symbol tour_challenge_tier_locked;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Symbol new_sym;
    // -> class Symbol available;
    // -> class Symbol tier_name;
}

// Range: 0x801C3FBC -> 0x801C424C
void ChallengeTierProvider::InitData(class ChallengeTierProvider * const this /* r29 */, class RndDir * dir /* r30 */) {
    // Local variables
    int i; // r31
    const char * name; // r0

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x44
} __vt__21ChallengeTierProvider; // size: 0x44, address: 0x808A2360
struct {
    // total size: 0x8
} __RTTI__21ChallengeTierProvider; // size: 0x8, address: 0x808A23C8
struct {
    // total size: 0xAC
} __vt__22TourChallengeTierPanel; // size: 0xAC, address: 0x808A2758
struct {
    // total size: 0x8
} __RTTI__22TourChallengeTierPanel; // size: 0x8, address: 0x808A2838
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std82vector<P18TourChallengeEvent,Q211stlpmtx_std35StlNodeAlloc<P18TourChallengeEvent>>; // size: 0x8, address: 0x808A2920
struct {
    // total size: 0x8
} __RTTI__PP6RndMat; // size: 0x8, address: 0x808A2938

