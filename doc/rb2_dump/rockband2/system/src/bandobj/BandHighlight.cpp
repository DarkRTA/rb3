/*
    Compile unit: C:\rockband2\system\src\bandobj\BandHighlight.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8024D804 -> 0x8024EF9C
*/
class DataArray * types; // size: 0x4, address: 0x80A4EEF0
class Symbol name; // size: 0x4, address: 0x80A4EEF8
class BandHighlight : public UIComponent {
    // total size: 0x1D0
    class Vector3 mStartPos; // offset 0x130, size 0x10
    class Vector3 mTargetPos; // offset 0x140, size 0x10
    float mAnimTime; // offset 0x150, size 0x4
    float mAnimDuration; // offset 0x154, size 0x4
    class BandLabel * mHelpText; // offset 0x158, size 0x4
    class Vector3 mStartEdgePos; // offset 0x160, size 0x10
    class Vector3 mTargetEdgePos; // offset 0x170, size 0x10
    class RndTransformable * mTextEdge; // offset 0x180, size 0x4
    class vector mMirrorMats; // offset 0x184, size 0xC
    class UIComponent * mLimitGroup; // offset 0x190, size 0x4
    int mEnterCount; // offset 0x194, size 0x4
};
// Range: 0x8024D804 -> 0x8024D908
void * BandHighlight::BandHighlight(class BandHighlight * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13BandHighlight;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8024D908 -> 0x8024D9F0
void * BandHighlight::~BandHighlight(class BandHighlight * const this /* r30 */) {}

static int gRev; // size: 0x4, address: 0x80A4EEFC
// Range: 0x8024D9F0 -> 0x8024DA34
void BandHighlight::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8024DA34 -> 0x8024DA90
void BandHighlight::Load(class BandHighlight * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8024DA90 -> 0x8024DB54
void BandHighlight::PreLoad(class BandHighlight * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8024DB54 -> 0x8024DB94
void BandHighlight::PostLoad(class BandHighlight * const this /* r31 */) {}

// Range: 0x8024DB94 -> 0x8024DBC8
void BandHighlight::Enter(class BandHighlight * const this /* r31 */) {}

// Range: 0x8024DBC8 -> 0x8024DBFC
void BandHighlight::Exit(class BandHighlight * const this /* r31 */) {}

// Range: 0x8024DBFC -> 0x8024DF54
void BandHighlight::Poll(class BandHighlight * const this /* r31 */) {
    // Local variables
    class UIPanel * p; // r0
    float f; // f31
    class Vector3 new_pos; // r1+0x10
    class UILabel * asLabel; // r30
    int i; // r29

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class TaskMgr TheTaskMgr;
    // -> class UIManager TheUI;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8024DF54 -> 0x8024DFDC
void BandHighlight::DrawShowing(class BandHighlight * const this /* r31 */) {}

// Range: 0x8024DFDC -> 0x8024E064
class RndDrawable * BandHighlight::CollideShowing(class BandHighlight * const this /* r28 */, const class Segment & s /* r29 */, float & dist /* r30 */, class Plane & plane /* r31 */) {}

// Range: 0x8024E064 -> 0x8024E0B8
int BandHighlight::CollidePlane(class BandHighlight * const this /* r30 */, const class Plane & plane /* r31 */) {}

// Range: 0x8024E0B8 -> 0x8024E42C
void BandHighlight::Update(class BandHighlight * const this /* r31 */) {
    // Local variables
    class DataArray * sa; // r27
    class DataArray * sa; // r29
    int i; // r26
    class RndMat * mat; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9BandLabel;
}

// Range: 0x8024E42C -> 0x8024E5A8
void BandHighlight::SetTarget(class BandHighlight * const this /* r29 */, class UIComponent * target /* r30 */, unsigned char snap /* r31 */) {
    // Local variables
    class UIComponent * c; // r5
    unsigned char found; // r0
    class Vector3 zero; // r1+0x10

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8024E5A8 -> 0x8024E660
void BandHighlight::UpdateTargetEdge(class BandHighlight * const this /* r31 */) {
    // Local variables
    class UILabel * label; // r0
    class RndText * text; // r0
    float textWidth; // f0

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__7UILabel;
}

// Range: 0x8024E660 -> 0x8024E6B0
void BandHighlight::SyncDir(class BandHighlight * const this /* r31 */) {}

// Range: 0x8024E6B0 -> 0x8024E740
class DataNode BandHighlight::OnMsg(class BandHighlight * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x8024E740 -> 0x8024E840
void BandHighlight::OnRegisterFocus(class BandHighlight * const this /* r28 */) {
    // Local variables
    class UIComponent * initial_target; // r30
    class PanelDir * d; // r29

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__8PanelDir;
}

// Range: 0x8024E840 -> 0x8024E8E8
void BandHighlight::OnUnregisterFocus(class BandHighlight * const this /* r31 */) {
    // Local variables
    class MsgSource * d; // r3

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__8PanelDir;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EF04
static class Symbol _s; // size: 0x4, address: 0x80A4EF0C
// Range: 0x8024E8E8 -> 0x8024EF1C
class DataNode BandHighlight::Handle(class BandHighlight * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__25UIComponentFocusChangeMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

// Range: 0x8024EF1C -> 0x8024EF9C
unsigned char BandHighlight::SyncProperty(class BandHighlight * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0x14C
} __vt__13BandHighlight; // size: 0x14C, address: 0x808B2DA8

