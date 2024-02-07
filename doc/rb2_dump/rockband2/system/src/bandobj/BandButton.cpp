/*
    Compile unit: C:\rockband2\system\src\bandobj\BandButton.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8023676C -> 0x802391F8
*/
class DataArray * types; // size: 0x4, address: 0x80A4EC00
class Symbol name; // size: 0x4, address: 0x80A4EC08
float sAnimDuration; // size: 0x4, address: 0x80A46A50
// Range: 0x8023676C -> 0x8023685C
void BandButton::Init() {
    // Local variables
    class DataArray * a; // r31

    // References
    // -> float sAnimDuration;
    // -> class Symbol name;
    // -> class UIManager TheUI;
}

// Range: 0x8023685C -> 0x80236860
void BandButton::Terminate() {}

// Range: 0x80236860 -> 0x802369B4
void * BandButton::BandButton(class BandButton * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__10BandButton;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802369B4 -> 0x802369EC
void BandButton::Enter(class BandButton * const this /* r31 */) {}

// Range: 0x802369EC -> 0x80236AC8
void BandButton::Copy(class BandButton * const this /* r28 */, const class Object * o /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class BandButton * b; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10BandButton;
}

static int BUTTON_REV; // size: 0x4, address: 0x80A46A54
// Range: 0x80236AC8 -> 0x80236B0C
void BandButton::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A4EC0C
// Range: 0x80236B0C -> 0x80236B68
void BandButton::Load(class BandButton * const this /* r30 */, class BinStream & d /* r31 */) {}

static class Symbol default_colors; // size: 0x4, address: 0x80A4EC14
// Range: 0x80236B68 -> 0x80237168
void BandButton::PreLoad(class BandButton * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    unsigned char all_caps; // r29
    int seed; // r1+0x5C
    float delta_x; // r1+0x58
    float delta_z; // r1+0x54
    float delta_rot; // r1+0x50
    class Symbol style; // r1+0x4C
    class Matrix3 m; // r1+0x70
    int fitText; // r1+0x48
    int seed; // r1+0x44
    float delta_x; // r1+0x40
    float delta_z; // r1+0x3C
    float delta_rot; // r1+0x38
    class Color c; // r1+0x60
    int fitText; // r1+0x34
    int seed; // r1+0x30
    float delta_x; // r1+0x2C
    float delta_z; // r1+0x28
    float delta_rot; // r1+0x24
    float wrap_width; // r1+0x20

    // References
    // -> static class Symbol default_colors;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> static int BUTTON_REV;
    // -> static int gRev;
}

// Range: 0x80237168 -> 0x80237268
void BandButton::PostLoad(class BandButton * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class ObjectDir * dir; // r4
    class ObjPtr text_mesh; // r1+0x8

    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> static int gRev;
}

static class Symbol text; // size: 0x4, address: 0x80A4EC1C
class RndEnvironTracker {
    // total size: 0x8
protected:
    class RndEnviron * mOld; // offset 0x0, size 0x4
    const class Vector3 * mOldPos; // offset 0x4, size 0x4
};
// Range: 0x80237268 -> 0x802375DC
void BandButton::DrawShowing(class BandButton * const this /* r31 */) {
    // Local variables
    float min_scale; // f31
    float max_scale; // f30
    const class DataNode * fs; // r0
    int i; // r30
    float tmp; // f0
    float r; // f1
    float s; // f0
    class Transform xfm; // r1+0x30
    class RndText * t; // r3
    class RndEnvironTracker _rndEnvironTracker; // r1+0x20

    // References
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
    // -> static class Symbol text;
    // -> float sAnimDuration;
    // -> class TaskMgr TheTaskMgr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802375DC -> 0x8023767C
void BandButton::Highlight(class BandButton * const this /* r31 */) {
    // Local variables
    struct _List_iterator m; // r1+0x10
}

// Range: 0x8023767C -> 0x80237780
class RndDrawable * BandButton::CollideShowing(class BandButton * const this /* r27 */, const class Segment & s /* r28 */, float & dist /* r29 */, class Plane & plane /* r30 */) {
    // Local variables
    class RndDrawable * c; // r31
    struct _List_iterator m; // r1+0x10
}

// Range: 0x80237780 -> 0x80237860
int BandButton::CollidePlane(class BandButton * const this /* r29 */, const class Plane & plane /* r30 */) {
    // Local variables
    int collide; // r31
    struct _List_iterator m; // r1+0x10
}

// Range: 0x80237860 -> 0x802379AC
void BandButton::SetState(class BandButton * const this /* r30 */) {
    // Local variables
    enum State oldState; // r0

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x802379AC -> 0x802379C4
void BandButton::SetSelected() {}

// Range: 0x802379C4 -> 0x80237A68
void BandButton::PlayAnim(class BandButton * const this /* r28 */, const class String & animName /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80237A68 -> 0x80237B0C
void BandButton::StopAnim(class BandButton * const this /* r28 */, const class String & animName /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80237B0C -> 0x80237BB4
unsigned char BandButton::IsAnimPlaying(class BandButton * const this /* r28 */, const class String & animName /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80237BB4 -> 0x80237C1C
void * AnimPlayer::AnimPlayer(struct AnimPlayer * const this /* r29 */, class RndAnimatable * anim /* r30 */, float startFrame /* f31 */, unsigned char loop /* r31 */) {}

// Range: 0x80237C1C -> 0x80237C68
void AnimPlayer::Play(struct AnimPlayer * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80237C68 -> 0x80237C74
void AnimPlayer::Stop() {}

// Range: 0x80237C74 -> 0x80237DD4
void AnimPlayer::Poll(struct AnimPlayer * const this /* r31 */) {
    // Local variables
    float frame; // f30

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol text; // size: 0x4, address: 0x80A4EC24
// Range: 0x80237DD4 -> 0x802386D0
void BandButton::Update(class BandButton * const this /* r30 */) {
    // Local variables
    class DataArray * sa; // r27
    class DataArray * sa; // r27
    class DataArray * sa; // r27
    class DataArray * sa; // r27
    class DataArray * sa; // r27
    class DataArray * sa; // r27
    class RndText * t; // r3

    // References
    // -> static class Symbol text;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x802386D0 -> 0x80238744
void BandButton::UpdateMat(class RndMat * mat /* r31 */) {
    // Local variables
    class Color c; // r1+0x10
}

// Range: 0x80238744 -> 0x802388CC
void BandButton::SyncMeshes(class BandButton * const this /* r30 */) {
    // Local variables
    class Transform mesh_xfm; // r1+0x50
    class Transform anim_xfm; // r1+0x10
    float frame; // f1

    // References
    // -> int sSelectFrames;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EC2C
static class Symbol _s; // size: 0x4, address: 0x80A4EC34
static class Symbol _s; // size: 0x4, address: 0x80A4EC3C
// Range: 0x802388CC -> 0x80238EF0
class DataNode BandButton::Handle(class BandButton * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x60
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

static class Symbol _s; // size: 0x4, address: 0x80A4EC44
static class Symbol _s; // size: 0x4, address: 0x80A4EC4C
// Range: 0x80238EF0 -> 0x80239090
unsigned char BandButton::SyncProperty(class BandButton * const this /* r27 */, class DataNode & _val /* r31 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80239090 -> 0x802391F8
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct UIMat {
    // total size: 0x8
    class Symbol mState; // offset 0x0, size 0x4
    class RndMat * mMat; // offset 0x4, size 0x4
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
struct UIMesh {
    // total size: 0xC
    class RndMesh * mMesh; // offset 0x0, size 0x4
    class list mMats; // offset 0x4, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct UIMesh _M_data; // offset 0x8, size 0xC
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
struct UIFont {
    // total size: 0x8
    class Symbol mState; // offset 0x0, size 0x4
    class RndFont * mFont; // offset 0x4, size 0x4
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
struct UIText {
    // total size: 0x10
    class Symbol mTextName; // offset 0x0, size 0x4
    class RndText * mText; // offset 0x4, size 0x4
    class list mFonts; // offset 0x8, size 0x8
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
class UIResource {
    // total size: 0x38
    class DataArray * mData; // offset 0x0, size 0x4
    const class UIResource * mClassResource; // offset 0x4, size 0x4
    int mRefCount; // offset 0x8, size 0x4
    class FilePath mResourcePath; // offset 0xC, size 0xC
    class ObjDirPtr mDir; // offset 0x18, size 0xC
    class Symbol mID; // offset 0x24, size 0x4
    class list mMeshes; // offset 0x28, size 0x8
    class list mTexts; // offset 0x30, size 0x8
};
struct {
    // total size: 0x174
} __vt__10BandButton; // size: 0x174, address: 0x808B0A38
struct {
    // total size: 0x18
} __vt__27ObjPtr<7RndMesh,9ObjectDir>; // size: 0x18, address: 0x808B0C18
struct {
    // total size: 0x8
} __RTTI__27ObjPtr<7RndMesh,9ObjectDir>; // size: 0x8, address: 0x808B0C58
struct {
    // total size: 0x64
} __vt__16RndHighlightable; // size: 0x64, address: 0x808B0E38
struct {
    // total size: 0x8
} __RTTI__PQ210BandButton10AnimPlayer; // size: 0x8, address: 0x808B0F38

