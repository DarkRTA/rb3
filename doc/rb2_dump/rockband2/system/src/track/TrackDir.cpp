/*
    Compile unit: C:\rockband2\system\src\track\TrackDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803C1608 -> 0x803C3A00
*/
class DataArray * types; // size: 0x4, address: 0x80A517A0
class TrackTest {
    // total size: 0x14
    class TrackDir * mTrack; // offset 0x0, size 0x4
    class ObjPtr mWidget; // offset 0x4, size 0xC
    int mSlot; // offset 0x10, size 0x4
};
// Range: 0x803C1608 -> 0x803C17C8
void * TrackDir::TrackDir(class TrackDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__8TrackDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803C17C8 -> 0x803C19D0
void * TrackDir::~TrackDir(class TrackDir * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11TrackWidget,9ObjectDir>;
    // -> struct [anonymous] __vt__8TrackDir;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class TrackWidget * mPtr; // offset 0x8, size 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class TrackWidget * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x803C19D0 -> 0x803C1CE4
void TrackDir::SyncObjects(class TrackDir * const this /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
}

// Range: 0x803C1CE4 -> 0x803C1E5C
void TrackDir::Copy(class TrackDir * const this /* r28 */, const class Object * o /* r29 */) {
    // Local variables
    const class TrackDir * d; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8TrackDir;
}

// Range: 0x803C1E5C -> 0x803C1EB8
void TrackDir::Load(class TrackDir * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803C1EB8 -> 0x803C2004
void TrackDir::PostLoad(class TrackDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class list sRevs;
}

// Range: 0x803C2004 -> 0x803C20F4
void TrackDir::DrawShowing(class TrackDir * const this /* r30 */) {
    // Local variables
    class RndCam * oldcam; // r31

    // References
    // -> class RndCam * sCurrent;
}

// Range: 0x803C20F4 -> 0x803C218C
void TrackDir::Poll(class TrackDir * const this /* r31 */) {
    // Local variables
    class Timer tm; // r1+0x8
    float nowY; // f1

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803C218C -> 0x803C219C
float TrackDir::TopSeconds() {}

// Range: 0x803C219C -> 0x803C21AC
float TrackDir::BottomSeconds() {}

// Range: 0x803C21AC -> 0x803C21B8
float TrackDir::SecondsToY() {}

// Range: 0x803C21B8 -> 0x803C21C4
float TrackDir::YToSeconds() {}

// Range: 0x803C21C4 -> 0x803C220C
float TrackDir::CutOffY(const class TrackDir * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803C220C -> 0x803C22E8
void TrackDir::SetSlotPosition(class TrackDir * const this /* r29 */, int index /* r30 */, struct SlotPosition & pos /* r31 */) {}

// Range: 0x803C22E8 -> 0x803C2350
void TrackDir::MakeSecondsXfm(class Transform & t /* r31 */) {}

// Range: 0x803C2350 -> 0x803C23A4
void TrackDir::MakeWidgetXfm(const class TrackDir * const this /* r30 */, float seconds /* f31 */, class Transform & t /* r31 */) {}

// Range: 0x803C23A4 -> 0x803C23AC
void TrackDir::SetYPerSecond() {}

// Range: 0x803C23AC -> 0x803C23C8
void TrackDir::SetScrollSpeed() {}

// Range: 0x803C23C8 -> 0x803C26C8
void TrackDir::ClearAllWidgets() {
    // Local variables
    class ObjDirItr i; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
}

// Range: 0x803C26C8 -> 0x803C2A0C
void TrackDir::ClearWidgets(float seconds /* f31 */, const class Symbol & except /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
}

// Range: 0x803C2A0C -> 0x803C2A74
void TrackDir::ToggleRunning(class TrackDir * const this /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A517A8
static class Symbol _s; // size: 0x4, address: 0x80A517B0
static class Symbol _s; // size: 0x4, address: 0x80A517B8
// Range: 0x803C2A74 -> 0x803C3020
class DataNode TrackDir::Handle(class TrackDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A517C0
static class Symbol _s; // size: 0x4, address: 0x80A517C8
// Range: 0x803C3020 -> 0x803C3274
unsigned char PropSync(struct SlotPosition & _me /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A517D0
static class Symbol _s; // size: 0x4, address: 0x80A517D8
static class Symbol _s; // size: 0x4, address: 0x80A517E0
static class Symbol _s; // size: 0x4, address: 0x80A517E8
static class Symbol _s; // size: 0x4, address: 0x80A517F0
static class Symbol _s; // size: 0x4, address: 0x80A517F8
static class Symbol _s; // size: 0x4, address: 0x80A51800
static class Symbol _s; // size: 0x4, address: 0x80A51808
// Range: 0x803C3274 -> 0x803C3804
unsigned char TrackDir::SyncProperty(class TrackDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
}

// Range: 0x803C3804 -> 0x803C3A00
unsigned char PropSync(class vector & v /* r31 */, class DataNode & n /* r26 */, class DataArray * prop /* r27 */, int i /* r28 */, enum PropOp op /* r29 */) {
    // Local variables
    struct SlotPosition * it; // r30
    struct SlotPosition tmp; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x18
} __vt__32ObjPtr<11TrackWidget,9ObjectDir>; // size: 0x18, address: 0x808E0678
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11TrackWidget,9ObjectDir>; // size: 0x8, address: 0x808E06C0
struct {
    // total size: 0x23C
} __vt__8TrackDir; // size: 0x23C, address: 0x808E06C8
struct {
    // total size: 0x8
} __RTTI__P12SlotPosition; // size: 0x8, address: 0x808E0CD0

