/*
    Compile unit: C:\rockband2\system\src\bandobj\BandCamShot.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80239FB4 -> 0x80240214
*/
class DataArray * types; // size: 0x4, address: 0x80A4EC50
unsigned char mShotLOD; // size: 0x1, address: 0x80A4EC55
// Range: 0x80239FB4 -> 0x8023A148
void * BandCamShot::BandCamShot(class BandCamShot * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11BandCamShot,9ObjectDir>;
    // -> struct [anonymous] __vt__11BandCamShot;
}

class _List_node : public _List_node_base {
    // total size: 0x120
public:
    struct Target _M_data; // offset 0x10, size 0x110
};
static int gRev; // size: 0x4, address: 0x80A4EC58
// Range: 0x8023A148 -> 0x8023A72C
class BinStream & __rs(class BinStream & d /* r30 */, struct Target & e /* r31 */) {
    // Local variables
    class Transform a; // r1+0x20
    float freezeTime; // r1+0x18

    // References
    // -> const char * gNullStr;
    // -> static int gRev;
    // -> struct [anonymous] __RTTI__9Character;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8023A72C -> 0x8023A84C
void BandCamShot::Replace(class BandCamShot * const this /* r27 */, class Object * from /* r28 */, class Object * to /* r29 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> struct [anonymous] __RTTI__9Character;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x8023A84C -> 0x8023A890
void BandCamShot::Save() {
    // References
    // -> class Debug TheDebug;
}

static class Symbol event_start; // size: 0x4, address: 0x80A4EC60
static class Symbol event_end; // size: 0x4, address: 0x80A4EC68
static class Symbol min_time; // size: 0x4, address: 0x80A4EC70
static class Symbol max_time; // size: 0x4, address: 0x80A4EC78
// Range: 0x8023A890 -> 0x8023AD44
void BandCamShot::Load(class BandCamShot * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    const class DataNode * startNode; // r0
    const class DataNode * endNode; // r0
    const class DataNode * val; // r0

    // References
    // -> static class Symbol max_time;
    // -> static class Symbol min_time;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> static class Symbol event_end;
    // -> static class Symbol event_start;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8023AD44 -> 0x8023B1E4
void BandCamShot::Copy(class BandCamShot * const this /* r28 */, const class Object * o /* r26 */) {
    // Local variables
    const class BandCamShot * c; // r0

    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11BandCamShot;
}

static class Message msg; // size: 0x8, address: 0x8097CD58
// Range: 0x8023B1E4 -> 0x8023B4B8
void BandCamShot::TeleportTarget(class BandCamShot * const this /* r30 */, class RndTransformable * target /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__9Character;
}

static class Message msg; // size: 0x8, address: 0x8097CD70
static class Symbol hands; // size: 0x4, address: 0x80A4EC80
// Range: 0x8023B4B8 -> 0x8023BDC0
void BandCamShot::StartAnim(class BandCamShot * const this /* r25 */) {
    // Local variables
    struct _List_iterator i; // r1+0x20
    class CompositeCharacter * cc; // r27
    class vector & cats; // r0
    int cat_index; // r26
    unsigned char hide; // r0
    class UIProxy * p; // r0

    // References
    // -> unsigned char mShotLOD;
    // -> class WiiRnd TheWiiRnd;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__7UIProxy;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> static class Symbol hands;
    // -> struct [anonymous] __RTTI__9Character;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8023BDC0 -> 0x8023BFFC
void BandCamShot::SetFrame(class BandCamShot * const this /* r30 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8023BFFC -> 0x8023C04C
void BandCamShot::SortTriggers(class BandCamShot * const this /* r31 */) {}

class TriggerCompare {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x8023C04C -> 0x8023C09C
void BandCamShot::ResetCurTrigger() {}

// Range: 0x8023C09C -> 0x8023C3F4
void BandCamShot::AdjustIK(class RndTransformable * target /* r30 */, class RndTransformable * bone /* r29 */, class RndTransformable * world /* r31 */) {
    // Local variables
    class Transform bli; // r1+0xF0
    class Transform bi; // r1+0xB0
    class Transform tw; // r1+0x70
    class Transform inv; // r1+0x30
}

// Range: 0x8023C3F4 -> 0x8023C594
void BandCamShot::EndAnim(class BandCamShot * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
    class UIProxy * p; // r0

    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__7UIProxy;
}

// Range: 0x8023C594 -> 0x8023C5F8
void BandCamShot::Store(class BandCamShot * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x8023C5F8 -> 0x8023C75C
void BandCamShot::View(class BandCamShot * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8023C75C -> 0x8023C7B4
void BandCamShot::FreezeChar(unsigned char freeze /* r31 */) {
    // Local variables
    class CompositeCharacter * cc; // r0

    // References
    // -> struct [anonymous] __RTTI__9Character;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
}

// Range: 0x8023C7B4 -> 0x8023C87C
void BandCamShot::ViewFreeze(class BandCamShot * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8023C87C -> 0x8023C8F0
void BandCamShot::Stop(class BandCamShot * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x8023C8F0 -> 0x8023D254
class DataNode BandCamShot::AddTarget(class BandCamShot * const this /* r28 */, class DataArray * target /* r30 */) {
    // Local variables
    struct Target t; // r1+0x140

    // References
    // -> struct [anonymous] __RTTI__9Character;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8023D254 -> 0x8023D29C
float BandCamShot::GetTotalDuration() {
    // Local variables
    float dur; // f31
}

// Range: 0x8023D29C -> 0x8023D2BC
int BandCamShot::GetNumShots() {
    // Local variables
    int count; // r4
    const class BandCamShot * shot; // r3
}

// Range: 0x8023D2BC -> 0x8023D318
float BandCamShot::GetTotalDurationSeconds(class BandCamShot * const this /* r31 */) {
    // Local variables
    float dur; // f31
}

// Range: 0x8023D318 -> 0x8023D3C4
void BandCamShot::CheckNextShot(class BandCamShot * const this /* r30 */) {
    // Local variables
    class BandCamShot * cam; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8023D3C4 -> 0x8023D4E0
class BandCamShot * BandCamShot::InitialShot(class BandCamShot * const this /* r29 */) {
    // Local variables
    class BandCamShot * cur; // r31
    struct _List_iterator i; // r1+0x20
    class BandCamShot * prev; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11BandCamShot;
}

// Range: 0x8023D4E0 -> 0x8023D52C
class BinStream & __rs(class BinStream & d /* r30 */, class TimedTrigger & t /* r31 */) {}

// Range: 0x8023D52C -> 0x8023D558
void * TimedTrigger::TimedTrigger() {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
}

// Range: 0x8023D558 -> 0x8023D5BC
void * TimedTrigger::TimedTrigger(class TimedTrigger * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
}

// Range: 0x8023D5BC -> 0x8023D630
class TimedTrigger & TimedTrigger::__as(class TimedTrigger * const this /* r30 */) {}

static class BandCamShot * gOwner; // size: 0x4, address: 0x80A4EC84
// Range: 0x8023D630 -> 0x8023D638
static void SyncFrames() {
    // References
    // -> static class BandCamShot * gOwner;
}

// Range: 0x8023D638 -> 0x8023D790
void Target::Store(struct Target * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__9Character;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8023D790 -> 0x8023D824
void Target::UpdateTarget(struct Target * const this /* r30 */, class RndTransformable * target /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A4EC8C
static class Symbol _s; // size: 0x4, address: 0x80A4EC94
// Range: 0x8023D824 -> 0x8023D9E8
unsigned char PropSync(class TimedTrigger & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8023D9E8 -> 0x8023DB38
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EC9C
static class Symbol _s; // size: 0x4, address: 0x80A4ECA4
static class Symbol _s; // size: 0x4, address: 0x80A4ECAC
static class Symbol _s; // size: 0x4, address: 0x80A4ECB4
static class Symbol _s; // size: 0x4, address: 0x80A4ECBC
static class Symbol _s; // size: 0x4, address: 0x80A4ECC4
static class Symbol _s; // size: 0x4, address: 0x80A4ECCC
static class Symbol _s; // size: 0x4, address: 0x80A4ECD4
static class Symbol _s; // size: 0x4, address: 0x80A4ECDC
static class Symbol _s; // size: 0x4, address: 0x80A4ECE4
static class Symbol _s; // size: 0x4, address: 0x80A4ECEC
static class Symbol _s; // size: 0x4, address: 0x80A4ECF4
static class Symbol _s; // size: 0x4, address: 0x80A4ECFC
static class Symbol _s; // size: 0x4, address: 0x80A4ED04
static class Symbol _s; // size: 0x4, address: 0x80A4ED0C
static class Symbol _s; // size: 0x4, address: 0x80A4ED14
static class Symbol _s; // size: 0x4, address: 0x80A4ED1C
static class Symbol _s; // size: 0x4, address: 0x80A4ED24
static class Symbol _s; // size: 0x4, address: 0x80A4ED2C
static class Symbol _s; // size: 0x4, address: 0x80A4ED34
// Range: 0x8023DB38 -> 0x8023EAA8
unsigned char PropSync(struct Target & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class BandCamShot * gOwner;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4ED3C
static class Symbol _s; // size: 0x4, address: 0x80A4ED44
static class Symbol _s; // size: 0x4, address: 0x80A4ED4C
static class Symbol _s; // size: 0x4, address: 0x80A4ED54
static class Symbol _s; // size: 0x4, address: 0x80A4ED5C
static class Symbol _s; // size: 0x4, address: 0x80A4ED64
static class Symbol _s; // size: 0x4, address: 0x80A4ED6C
static class Symbol _s; // size: 0x4, address: 0x80A4ED74
static class Symbol _s; // size: 0x4, address: 0x80A4ED7C
// Range: 0x8023EAA8 -> 0x8023F0D4
unsigned char BandCamShot::SyncProperty(class BandCamShot * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class BandCamShot * gOwner;
}

// Range: 0x8023F0D4 -> 0x8023F334
unsigned char PropSync(class ObjVector & v /* r31 */, class DataNode & n /* r26 */, class DataArray * prop /* r27 */, int i /* r30 */, enum PropOp op /* r29 */) {
    // Local variables
    class TimedTrigger * it; // r28
    class TimedTrigger tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std34_List_node<Q211BandCamShot6Target>; // size: 0x8, address: 0x808B1328
static class Symbol _s; // size: 0x4, address: 0x80A4ED84
static class Symbol _s; // size: 0x4, address: 0x80A4ED8C
static class Symbol _s; // size: 0x4, address: 0x80A4ED94
static class Symbol _s; // size: 0x4, address: 0x80A4ED9C
static class Symbol _s; // size: 0x4, address: 0x80A4EDA4
static class Symbol _s; // size: 0x4, address: 0x80A4EDAC
static class Symbol _s; // size: 0x4, address: 0x80A4EDB4
static class Symbol _s; // size: 0x4, address: 0x80A4EDBC
static class Symbol _s; // size: 0x4, address: 0x80A4EDC4
static class Symbol _s; // size: 0x4, address: 0x80A4EDCC
static class Symbol _s; // size: 0x4, address: 0x80A4EDD4
// Range: 0x8023F334 -> 0x8024010C
class DataNode BandCamShot::Handle(class BandCamShot * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
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

// Range: 0x8024010C -> 0x80240214
class DataNode BandCamShot::OnTestDelta(class BandCamShot * const this /* r30 */, class DataArray * arr /* r31 */) {
    // Local variables
    float delta30fps; // f0
}

struct {
    // total size: 0xA4
} __vt__11BandCamShot; // size: 0xA4, address: 0x808B14E0
struct {
    // total size: 0x18
} __vt__33ObjPtr<12EventTrigger,9ObjectDir>; // size: 0x18, address: 0x808B1640
struct {
    // total size: 0x8
} __RTTI__33ObjPtr<12EventTrigger,9ObjectDir>; // size: 0x8, address: 0x808B1688
struct {
    // total size: 0x18
} __vt__37ObjPtr<16RndTransformable,9ObjectDir>; // size: 0x18, address: 0x808B1948
struct {
    // total size: 0x8
} __RTTI__37ObjPtr<16RndTransformable,9ObjectDir>; // size: 0x8, address: 0x808B1990
struct {
    // total size: 0x18
} __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>; // size: 0x18, address: 0x808B1998
struct {
    // total size: 0x8
} __RTTI__42ObjOwnerPtr<16RndTransformable,9ObjectDir>; // size: 0x8, address: 0x808B19E8
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211BandCamShot12TimedTrigger; // size: 0x8, address: 0x808B1AB0

