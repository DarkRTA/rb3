/*
    Compile unit: C:\rockband2\band2\src\meta\CharSelectPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800DE46C -> 0x800DFDF4
*/
class DataArray * types; // size: 0x4, address: 0x80A4AD68
class Symbol name; // size: 0x4, address: 0x80A4AD70
class CharSelectPanel * sInstance; // size: 0x4, address: 0x80A4AD74
// Range: 0x800DE46C -> 0x800DE54C
void * CharSelectPanel::CharSelectPanel(class CharSelectPanel * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class CharSelectPanel * sInstance;
    // -> struct [anonymous] __vt__15CharSelectPanel;
}

// Range: 0x800DE54C -> 0x800DE680
void CharSelectPanel::SelectCam(class CharSelectPanel * const this /* r28 */, const char * name /* r29 */) {
    // Local variables
    class WorldDir * dir; // r30
    const char * shot_name; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7CamShot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> struct [anonymous] __RTTI__8WorldDir;
}

// Range: 0x800DE680 -> 0x800DE990
void CharSelectPanel::SelectNextCam(class CharSelectPanel * const this /* r24 */) {
    // Local variables
    class WorldDir * dir; // r27
    const char * shot_name; // r26
    class CamShot * s; // r25
    const char * shot_name; // r25

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7CamShot;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> struct [anonymous] __RTTI__8WorldDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x800DE990 -> 0x800DE998
void CharSelectPanel::SetCreatorUser() {}

// Range: 0x800DE998 -> 0x800DEAE0
void CharSelectPanel::PlayAttitudeGroup(class CharSelectPanel * const this /* r28 */) {
    // Local variables
    class CompositeCharacter * c; // r29

    // References
    // -> const char * gNullStr;
    // -> class CharCache * TheCharCache;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800DEAE0 -> 0x800DEAE8
void CharSelectPanel::SetLoadingPanel() {}

// Range: 0x800DEAE8 -> 0x800DEB28
void CharSelectPanel::Enter(class CharSelectPanel * const this /* r31 */) {}

static class Symbol show_char; // size: 0x4, address: 0x80A4AD7C
static class Message msg; // size: 0x8, address: 0x809786C0
// Range: 0x800DEB28 -> 0x800DF030
void CharSelectPanel::Poll(class CharSelectPanel * const this /* r23 */) {
    // Local variables
    int slot; // r29
    class UIProxy * proxy; // r28
    int player_num; // r27
    unsigned char is_showing; // r26
    class CompositeCharacter * c; // r25
    class UIScreen * s; // r30
    class DataNode n; // r1+0x38
    class vector & cats; // r0
    int cat_index; // r24

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol show_char;
    // -> class UIManager TheUI;
    // -> class CharCache * TheCharCache;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x800DF030 -> 0x800DF29C
void CharSelectPanel::FinishLoad(class CharSelectPanel * const this /* r31 */) {
    // Local variables
    class Symbol mode; // r1+0x28
    int max_players; // r0
    int i; // r25

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIProxy;
    // -> class GameMode * TheGameMode;
}

// Range: 0x800DF29C -> 0x800DF35C
class Symbol CharSelectPanel::Mode() {
    // Local variables
    int max_players; // r0

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UIProxy * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x800DF35C -> 0x800DF69C
void CharSelectPanel::HookupProxy(class UIProxy * p /* r30 */, class CompositeCharacter * c /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIProxy;
}

static class Symbol _s; // size: 0x4, address: 0x80A4AD84
static class Symbol _s; // size: 0x4, address: 0x80A4AD8C
static class Symbol _s; // size: 0x4, address: 0x80A4AD94
static class Symbol _s; // size: 0x4, address: 0x80A4AD9C
static class Symbol _s; // size: 0x4, address: 0x80A4ADA4
// Range: 0x800DF69C -> 0x800DFDF4
class DataNode CharSelectPanel::Handle(class CharSelectPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8BandUser;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x8
} __RTTI__8WorldDir; // size: 0x8, address: 0x80883EF8
struct {
    // total size: 0x8
} __RTTI__7UIProxy; // size: 0x8, address: 0x80884038
class ObjDirPtr : public ObjRef {
    // total size: 0xC
protected:
    class RndDir * mDir; // offset 0x4, size 0x4
    class DirLoader * mLoader; // offset 0x8, size 0x4
};
class UIProxy : public UIComponent {
    // total size: 0x1D0
    class ObjDirPtr mDir; // offset 0x130, size 0xC
    class ObjPtr mEnv; // offset 0x13C, size 0xC
    class RndTransformable * mMainTrans; // offset 0x148, size 0x4
    class Transform mOldXfm; // offset 0x150, size 0x40
    unsigned char mSyncOnMove; // offset 0x190, size 0x1
    unsigned char mPolled; // offset 0x191, size 0x1
};
struct {
    // total size: 0xAC
} __vt__15CharSelectPanel; // size: 0xAC, address: 0x80884268
struct {
    // total size: 0x8
} __RTTI__15CharSelectPanel; // size: 0x8, address: 0x80884348
struct {
    // total size: 0x8
} __RTTI__PP7UIProxy; // size: 0x8, address: 0x808843E0

