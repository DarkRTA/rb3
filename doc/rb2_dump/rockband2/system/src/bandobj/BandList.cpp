/*
    Compile unit: C:\rockband2\system\src\bandobj\BandList.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802536E4 -> 0x80254910
*/
class Symbol name; // size: 0x4, address: 0x80A4EFAC
class DataArray * types; // size: 0x4, address: 0x80A4EFB0
class Symbol name; // size: 0x4, address: 0x80A4EFB8
// Range: 0x802536E4 -> 0x80253804
void * BandList::BandList(class BandList * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8BandList;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80253804 -> 0x802538EC
void * BandList::~BandList(class BandList * const this /* r30 */) {}

static class Symbol anim_delay_frac; // size: 0x4, address: 0x80A4EFC0
// Range: 0x802538EC -> 0x80253960
void BandList::SetTypeDef(class BandList * const this /* r31 */) {
    // References
    // -> static class Symbol anim_delay_frac;
}

static class Symbol enter_anim; // size: 0x4, address: 0x80A4EFC8
// Range: 0x80253960 -> 0x802539E4
void BandList::Enter(class BandList * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol enter_anim;
}

static class Symbol exit_anim; // size: 0x4, address: 0x80A4EFD0
// Range: 0x802539E4 -> 0x80253A68
void BandList::Exit(class BandList * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol exit_anim;
}

static class Symbol exit_anim; // size: 0x4, address: 0x80A4EFD8
// Range: 0x80253A68 -> 0x80253B40
unsigned char BandList::Exiting(class BandList * const this /* r29 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol exit_anim;
}

static class Symbol enter_anim; // size: 0x4, address: 0x80A4EFE0
static class Symbol exit_anim; // size: 0x4, address: 0x80A4EFE8
static class Symbol element_anim; // size: 0x4, address: 0x80A4EFF0
// Range: 0x80253B40 -> 0x80253C80
void BandList::AdjustTrans(class BandList * const this /* r30 */, class RndTransformable * element /* r31 */, int display /* r1+0x8 */) {
    // Local variables
    class Symbol anim_name; // r1+0x14
    float start_time; // f1

    // References
    // -> static class Symbol element_anim;
    // -> static class Symbol exit_anim;
    // -> static class Symbol enter_anim;
}

static class Symbol element_anim; // size: 0x4, address: 0x80A4EFF8
// Range: 0x80253C80 -> 0x80253D34
unsigned char BandList::IsAnimatingElements(const class BandList * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol element_anim;
}

// Range: 0x80253D34 -> 0x80253E6C
void BandList::AnimateElements(class BandList * const this /* r29 */, unsigned char only_disabled /* r30 */) {
    // Local variables
    int i; // r1+0x18
    int data; // r31

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80253E6C -> 0x80253E78
void BandList::SkipAnimateElements() {}

// Range: 0x80253E78 -> 0x80253F98
class RndTransAnim * BandList::FindAnim(const class BandList * const this /* r31 */) {
    // Local variables
    class DataArray * a; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x80253F98 -> 0x80254070
float BandList::AnimDuration(const class BandList * const this /* r30 */) {
    // Local variables
    class RndAnimatable * anim; // r31
}

static class Symbol anim_delay_frac; // size: 0x4, address: 0x80A4F000
// Range: 0x80254070 -> 0x8025415C
float BandList::ElementAnimDuration(const class BandList * const this /* r29 */, class Symbol & anim /* r30 */) {
    // Local variables
    float delay_frac; // f0
    float duration; // f0

    // References
    // -> static class Symbol anim_delay_frac;
}

static class Symbol anim_fps; // size: 0x4, address: 0x80A4F008
// Range: 0x8025415C -> 0x802541DC
float BandList::AnimFps(const class BandList * const this /* r31 */) {
    // References
    // -> static class Symbol anim_fps;
}

// Range: 0x802541DC -> 0x80254540
void BandList::AdjustElement(class BandList * const this /* r27 */, class RndTransformable * element /* r30 */, class Symbol & anim_name /* r28 */, int display /* r29 */, float start_time /* f30 */) {
    // Local variables
    class RndTransAnim * anim; // r31
    float duration; // f0
    float frame; // f30
    class Transform anim_xfm; // r1+0x60
    class Transform ele_xfm; // r1+0x20

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F010
// Range: 0x80254540 -> 0x80254910
class DataNode BandList::Handle(class BandList * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x1C8
} __vt__8BandList; // size: 0x1C8, address: 0x808B4340

