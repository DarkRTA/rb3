/*
    Compile unit: C:\rockband2\band2\src\meta\OutfitPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80131DE0 -> 0x80136BF0
*/
class DataArray * types; // size: 0x4, address: 0x80A4BD40
// Range: 0x80131DE0 -> 0x80131E38
unsigned char OutfitChar::HasMultipleCameras() {}

static class Symbol _s; // size: 0x4, address: 0x80A4BD48
static class Symbol _s; // size: 0x4, address: 0x80A4BD50
static class Symbol _s; // size: 0x4, address: 0x80A4BD58
// Range: 0x80131E38 -> 0x801323AC
class DataNode OutfitChar::Handle(class OutfitChar * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x801323AC -> 0x80132440
void * OutfitPanel::OutfitPanel(class OutfitPanel * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__11OutfitPanel;
}

static class Symbol bandanas; // size: 0x4, address: 0x80A4BD60
static class Symbol facehair; // size: 0x4, address: 0x80A4BD68
// Range: 0x80132440 -> 0x801324CC
class Symbol ComponentToCharCategory(class Symbol & cat /* r31 */) {
    // References
    // -> static class Symbol facehair;
    // -> static class Symbol bandanas;
}

// Range: 0x801324CC -> 0x80132530
class Symbol OutfitPanel::FocusCategory(class OutfitPanel * const this /* r31 */) {
    // Local variables
    class UIComponent * c; // r4

    // References
    // -> const char * gNullStr;
}

static class Symbol female; // size: 0x4, address: 0x80A4BD70
static class Symbol head_10; // size: 0x4, address: 0x80A4BD78
// Range: 0x80132530 -> 0x8013265C
class Symbol OutfitPanel::FocusOutfit(class OutfitPanel * const this /* r30 */) {
    // Local variables
    class UIList * l; // r31

    // References
    // -> static class Symbol head_10;
    // -> static class Symbol female;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> const char * gNullStr;
}

// Range: 0x8013265C -> 0x801326F8
class OutfitProvider * OutfitPanel::FocusProvider(class OutfitPanel * const this /* r31 */) {
    // References
    // -> class Shop * TheShop;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801326F8 -> 0x80132744
class OutfitConfig * OutfitPanel::FindOutfitConfig(class OutfitPanel * const this /* r31 */) {}

// Range: 0x80132744 -> 0x80132774
class CompositeCharacter * OutfitPanel::GetChar() {}

// Range: 0x80132774 -> 0x801327A4
class TourCharLocal * OutfitPanel::GetTourChar() {}

static class Symbol outfit_char; // size: 0x4, address: 0x80A4BD80
// Range: 0x801327A4 -> 0x8013282C
class OutfitChar * OutfitPanel::GetOutfitChar(class OutfitPanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10OutfitChar;
    // -> static class Symbol outfit_char;
}

// Range: 0x8013282C -> 0x80132888
unsigned char OutfitPanel::InShop() {
    // Local variables
    unsigned char in_shop; // r1+0x8
}

// Range: 0x80132888 -> 0x80132890
class Symbol OutfitPanel::SelectedOutfit() {}

// Range: 0x80132890 -> 0x801328D4
char * OutfitPanel::CamBaseName() {
    // Local variables
    class OutfitProvider * p; // r0

    // References
    // -> class Shop * TheShop;
}

// Range: 0x801328D4 -> 0x8013293C
unsigned char OutfitPanel::IsLoaded(class OutfitPanel * const this /* r30 */) {}

// Range: 0x8013293C -> 0x80132B1C
void OutfitPanel::FinishLoad(class OutfitPanel * const this /* r31 */) {
    // Local variables
    class ObjDirItr ol; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12OutfitLoader;
}

static class Symbol outfit; // size: 0x4, address: 0x80A4BD88
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UIList * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80132B1C -> 0x80132FBC
void OutfitPanel::RefreshLists(class OutfitPanel * const this /* r28 */) {
    // Local variables
    class TourCharLocal * tc; // r30
    unsigned char show_outfit_text; // r1+0x8
    class Symbol genre; // r1+0x44
    const class DataNode * g; // r0
    unsigned char is_closet; // r29
    unsigned char in_shop; // r0
    class ObjDirItr l; // r1+0x48
    class Symbol category; // r1+0x40
    class OutfitProvider * p; // r27

    // References
    // -> unsigned char sUnlockAll;
    // -> class Shop * TheShop;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> static class Symbol outfit;
    // -> const char * gNullStr;
}

// Range: 0x80132FBC -> 0x80132FF0
void OutfitPanel::Enter(class OutfitPanel * const this /* r31 */) {}

// Range: 0x80132FF0 -> 0x8013308C
void OutfitPanel::Exit(class OutfitPanel * const this /* r31 */) {
    // Local variables
    class Symbol category; // r1+0x18

    // References
    // -> const char * gNullStr;
}

// Range: 0x8013308C -> 0x801331D0
void OutfitPanel::StoreOutfit(class OutfitPanel * const this /* r30 */) {
    // Local variables
    class Symbol category; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Message msg; // size: 0x8, address: 0x80979230
// Range: 0x801331D0 -> 0x80133428
void OutfitPanel::ConfirmOutfit(class OutfitPanel * const this /* r30 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

static class Message msg; // size: 0x8, address: 0x80979248
// Range: 0x80133428 -> 0x80133650
class DataNode OutfitPanel::UndoOutfit(class OutfitPanel * const this /* r31 */) {
    // Local variables
    class Symbol category; // r1+0x24

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x80133650 -> 0x8013374C
void OutfitPanel::ManualSetCategory(class OutfitPanel * const this /* r30 */, class Symbol & category /* r31 */) {}

// Range: 0x8013374C -> 0x80133B44
class DataNode OutfitPanel::SetCategory(class DataNode * ret /* r24 */, class OutfitPanel * const this /* r25 */, class Symbol & category /* r26 */, unsigned char selected /* r27 */, unsigned char undo /* r28 */) {
    // Local variables
    class Symbol char_category; // r1+0x38
    unsigned char select_cam; // r1+0x9
    unsigned char skip_buttons; // r1+0x8
    const char * name; // r23
    class UIComponent * c; // r4

    // References
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x80133B44 -> 0x80133BE0
class Symbol OutfitPanel::SelectedOutfit(class OutfitPanel * const this /* r31 */, class Symbol & category /* r30 */) {
    // Local variables
    class TourCharLocal * tc; // r31
}

// Range: 0x80133BE0 -> 0x80133E30
void OutfitPanel::SelectOutfit(class OutfitPanel * const this /* r27 */, class Symbol & category /* r28 */, class Symbol & outfit /* r29 */) {
    // Local variables
    class TourCharLocal * tc; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x80133E30 -> 0x80133F34
class DataNode OutfitPanel::OnMsg(class OutfitPanel * const this /* r30 */) {
    // Local variables
    enum JoypadAction action; // r0
    class UIList * l; // r3

    // References
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x80133F34 -> 0x80133FB8
class DataNode OutfitPanel::OnMsg(class OutfitPanel * const this /* r31 */) {
    // Local variables
    class Symbol category; // r1+0x14

    // References
    // -> const char * gNullStr;
}

// Range: 0x80133FB8 -> 0x80133FF8
unsigned char __eq(class Symbol & rhs /* r31 */) {}

// Range: 0x80133FF8 -> 0x801340C8
class Symbol OutfitPanel::ComponentCategory(class OutfitPanel * const this /* r30 */, class UIComponent * c /* r31 */) {
    // Local variables
    class Symbol category; // r1+0x18
    class Symbol char_cat; // r1+0x14

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol cancel; // size: 0x4, address: 0x80A4BD90
static class Symbol helpbar_back; // size: 0x4, address: 0x80A4BD98
static class Symbol confirm; // size: 0x4, address: 0x80A4BDA0
static class Symbol shop_hb_category; // size: 0x4, address: 0x80A4BDA8
static class Symbol view_modify; // size: 0x4, address: 0x80A4BDB0
static class Symbol shop_hb_change_camera; // size: 0x4, address: 0x80A4BDB8
static class Symbol shop_hb_choosegroup; // size: 0x4, address: 0x80A4BDC0
static class Symbol shop_hb_choosecolor; // size: 0x4, address: 0x80A4BDC8
static class Symbol shop_hb_select; // size: 0x4, address: 0x80A4BDD0
static class Symbol shop_hb_purchase; // size: 0x4, address: 0x80A4BDD8
static class Symbol waiting; // size: 0x4, address: 0x80A4BDE0
static class Symbol shop_unlock_all; // size: 0x4, address: 0x80A4BDE8
static class Symbol shop_cant_afford_text; // size: 0x4, address: 0x80A4BDF0
class UIButton : public UILabel {
    // total size: 0x1E0
};
struct AnimPlayer {
    // total size: 0x18
    class String mName; // offset 0x0, size 0xC
    float mStartTime; // offset 0xC, size 0x4
    unsigned char mLoop; // offset 0x10, size 0x1
    unsigned char mPlaying; // offset 0x11, size 0x1
    class RndAnimatable * mAnim; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct AnimPlayer * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct AnimPlayer * _M_start; // offset 0x0, size 0x4
    struct AnimPlayer * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BandButton : public UIButton, public BandTextComp {
    // total size: 0x230
    float mAnimTime; // offset 0x1C4, size 0x4
    float mLastJitterTime; // offset 0x1C8, size 0x4
    class ObjPtr mTextMesh; // offset 0x1CC, size 0xC
    class RndTransAnim * mSelectingAnim; // offset 0x1D8, size 0x4
    class RndEnviron * mTextEnv; // offset 0x1DC, size 0x4
    class vector mAnims; // offset 0x1E0, size 0xC
    unsigned char mIsSelected; // offset 0x1EC, size 0x1
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class BandButton * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x801340C8 -> 0x801356E4
void OutfitPanel::Update(class OutfitPanel * const this /* r20 */) {
    // Local variables
    class Symbol selected; // r1+0x98
    class ObjDirItr b; // r1+0x184
    class Symbol category; // r1+0x94
    class TourCharLocal * tcl; // r24
    unsigned char has_outfit; // r0
    class OutfitProvider * focus_provider; // r23
    int cost; // r22
    unsigned char can_afford; // r21
    class DataArrayPtr helpbar; // r1+0x168
    class Symbol confirm_sym; // r1+0x90
    class ObjDirItr b; // r1+0x170
    class Symbol token; // r1+0x8C
    unsigned char disabled; // r3

    // References
    // -> static class Symbol shop_cant_afford_text;
    // -> static class Symbol shop_unlock_all;
    // -> static class Symbol waiting;
    // -> static class Symbol shop_hb_purchase;
    // -> static class Symbol shop_hb_select;
    // -> static class Symbol shop_hb_choosecolor;
    // -> static class Symbol shop_hb_choosegroup;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__9BandLabel;
    // -> static class Symbol shop_hb_change_camera;
    // -> static class Symbol view_modify;
    // -> class HelpBarPanel * sInstance;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> struct [anonymous] __RTTI__10BandButton;
    // -> static class Symbol shop_hb_category;
    // -> const char * gNullStr;
    // -> static class Symbol confirm;
    // -> static class Symbol helpbar_back;
    // -> static class Symbol cancel;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

static class Symbol closet; // size: 0x4, address: 0x80A4BDF8
// Range: 0x801356E4 -> 0x80135758
unsigned char OutfitPanel::IsCloset(class OutfitPanel * const this /* r31 */) {
    // Local variables
    unsigned char is_closet; // r1+0x8

    // References
    // -> static class Symbol closet;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BE00
static class Symbol _s; // size: 0x4, address: 0x80A4BE08
static class Symbol _s; // size: 0x4, address: 0x80A4BE10
static class Symbol _s; // size: 0x4, address: 0x80A4BE18
static class Symbol _s; // size: 0x4, address: 0x80A4BE20
static class Symbol _s; // size: 0x4, address: 0x80A4BE28
static class Symbol _s; // size: 0x4, address: 0x80A4BE30
static class Symbol _s; // size: 0x4, address: 0x80A4BE38
static class Symbol _s; // size: 0x4, address: 0x80A4BE40
static class Symbol _s; // size: 0x4, address: 0x80A4BE48
static class Symbol _s; // size: 0x4, address: 0x80A4BE50
static class Symbol _s; // size: 0x4, address: 0x80A4BE58
static class Symbol _s; // size: 0x4, address: 0x80A4BE60
static class Symbol _s; // size: 0x4, address: 0x80A4BE68
static class Symbol _s; // size: 0x4, address: 0x80A4BE70
static class Symbol _s; // size: 0x4, address: 0x80A4BE78
// Range: 0x80135758 -> 0x80136BF0
class DataNode OutfitPanel::Handle(class OutfitPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x90
    class MessageTimer _mt; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode _n; // r1+0xA8

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__20UIComponentScrollMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> const char * gNullStr;
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

struct {
    // total size: 0x8
} __RTTI__10BandButton; // size: 0x8, address: 0x80891498
struct {
    // total size: 0x8
} __RTTI__8UIButton; // size: 0x8, address: 0x808914F0
struct {
    // total size: 0xAC
} __vt__11OutfitPanel; // size: 0xAC, address: 0x80891578
struct {
    // total size: 0xBC
} __vt__10OutfitChar; // size: 0xBC, address: 0x80891658

