/*
    Compile unit: C:\rockband2\system\src\rndobj\Anim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8046A854 -> 0x8046CB44
*/
class DataArray * types; // size: 0x4, address: 0x80A528B0
class Symbol name; // size: 0x4, address: 0x80A528B8
static int ANIMATABLE_REV; // size: 0x4, address: 0x80A470E0
class Symbol name; // size: 0x4, address: 0x80A528C0
static enum TaskUnits gRateUnits[5]; // size: 0x14, address: 0x808F1108
static float gRateFpu[5]; // size: 0x14, address: 0x808F111C
// Range: 0x8046A854 -> 0x8046A86C
enum TaskUnits RndAnimatable::Units() {
    // References
    // -> static enum TaskUnits gRateUnits[5];
}

// Range: 0x8046A86C -> 0x8046A884
float RndAnimatable::FramesPerUnit() {
    // References
    // -> static float gRateFpu[5];
}

// Range: 0x8046A884 -> 0x8046A8E4
unsigned char RndAnimatable::ConvertFrames(class RndAnimatable * const this /* r30 */, float & frames /* r31 */) {}

// Range: 0x8046A8E4 -> 0x8046A960
void * RndAnimatable::RndAnimatable(class RndAnimatable * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13RndAnimatable;
}

// Range: 0x8046A960 -> 0x8046A9A4
void RndAnimatable::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8046A9A4 -> 0x8046AAF4
void RndAnimatable::Load(class RndAnimatable * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static int ANIMATABLE_REV;
}

// Range: 0x8046AAF4 -> 0x8046AB54
void RndAnimatable::Copy(class RndAnimatable * const this /* r31 */) {
    // Local variables
    const class RndAnimatable * m; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
}

// Range: 0x8046AB54 -> 0x8046AC04
unsigned char RndAnimatable::IsAnimating(class RndAnimatable * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8AnimTask;
}

// Range: 0x8046AC04 -> 0x8046ACDC
void RndAnimatable::StopAnimation(class RndAnimatable * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x28
    class AnimTask * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8AnimTask;
}

// Range: 0x8046ACDC -> 0x8046AE38
class Task * RndAnimatable::Animate(class RndAnimatable * const this /* r28 */, float blend /* f28 */, unsigned char wait /* r29 */, float delay /* f29 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol dest; // size: 0x4, address: 0x80A528C8
static class Symbol loop; // size: 0x4, address: 0x80A528D0
// Range: 0x8046AE38 -> 0x8046B008
class Task * RndAnimatable::Animate(class RndAnimatable * const this /* r26 */, float blend /* f26 */, unsigned char wait /* r29 */, float delay /* f27 */, enum Rate rate /* r30 */, float start /* f28 */, float end /* f29 */, float period /* f30 */, float scale /* f31 */, class Symbol & type /* r27 */) {
    // Local variables
    float fpu; // f31

    // References
    // -> static enum TaskUnits gRateUnits[5];
    // -> class TaskMgr TheTaskMgr;
    // -> static float gRateFpu[5];
    // -> static class Symbol loop;
    // -> static class Symbol dest;
}

// Range: 0x8046B008 -> 0x8046B134
class Task * RndAnimatable::Animate(class RndAnimatable * const this /* r29 */, float start /* f28 */, float end /* f29 */, enum TaskUnits units /* r30 */, float blend /* f30 */) {
    // Local variables
    float fpu; // f31
    float fpus[3]; // r1+0x8

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A528D8
static class Symbol _s; // size: 0x4, address: 0x80A528E0
static class Symbol _s; // size: 0x4, address: 0x80A528E8
static class Symbol _s; // size: 0x4, address: 0x80A528F0
static class Symbol _s; // size: 0x4, address: 0x80A528F8
static class Symbol _s; // size: 0x4, address: 0x80A52900
static class Symbol _s; // size: 0x4, address: 0x80A52908
// Range: 0x8046B134 -> 0x8046B9FC
class DataNode RndAnimatable::Handle(class RndAnimatable * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40

    // References
    // -> class Debug TheDebug;
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

static class Symbol blend; // size: 0x4, address: 0x80A52910
static class Symbol range; // size: 0x4, address: 0x80A52918
static class Symbol loop; // size: 0x4, address: 0x80A52920
static class Symbol dest; // size: 0x4, address: 0x80A52928
static class Symbol period; // size: 0x4, address: 0x80A52930
static class Symbol delay; // size: 0x4, address: 0x80A52938
static class Symbol units; // size: 0x4, address: 0x80A52940
static class Symbol name; // size: 0x4, address: 0x80A52948
static class Symbol wait; // size: 0x4, address: 0x80A52950
// Range: 0x8046B9FC -> 0x8046BF6C
class DataNode RndAnimatable::OnAnimate(class RndAnimatable * const this /* r28 */, class DataArray * data /* r29 */) {
    // Local variables
    float b; // r1+0x3C
    float start; // f30
    float end; // f29
    unsigned char l; // r30
    float fpu; // f31
    enum TaskUnits u; // r1+0x38
    float d; // r1+0x34
    const char * n; // r1+0x30
    unsigned char w; // r1+0x8
    class DataArray * r; // r26
    class DataArray * r; // r26
    class DataArray * r; // r26
    class DataArray * r; // r26
    float p; // f0

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol wait;
    // -> static class Symbol name;
    // -> static class Symbol units;
    // -> static class Symbol delay;
    // -> static class Symbol period;
    // -> static class Symbol dest;
    // -> static class Symbol loop;
    // -> static class Symbol range;
    // -> static class Symbol blend;
}

// Range: 0x8046BF6C -> 0x8046C040
class DataNode RndAnimatable::OnConvertFrames(class RndAnimatable * const this /* r30 */, class DataArray * data /* r29 */) {
    // Local variables
    float frames; // r1+0x8
    unsigned char seconds; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A52958
// Range: 0x8046C040 -> 0x8046C1AC
unsigned char RndAnimatable::SyncProperty(class RndAnimatable * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

class AnimTask : public Task {
    // total size: 0x6C
protected:
    class ObjOwnerPtr mAnim; // offset 0x28, size 0xC
    class ObjPtr mAnimTarget; // offset 0x34, size 0xC
    class ObjPtr mBlendTask; // offset 0x40, size 0xC
    unsigned char mBlending; // offset 0x4C, size 0x1
    float mBlendTime; // offset 0x50, size 0x4
    float mBlendPeriod; // offset 0x54, size 0x4
    float mMin; // offset 0x58, size 0x4
    float mMax; // offset 0x5C, size 0x4
    float mScale; // offset 0x60, size 0x4
    float mOffset; // offset 0x64, size 0x4
    unsigned char mLoop; // offset 0x68, size 0x1
};
// Range: 0x8046C1AC -> 0x8046C56C
void * AnimTask::AnimTask(class AnimTask * const this /* r30 */, class RndAnimatable * anim /* r31 */, float start /* r1+0x8 */, float end /* r1+0xC */, float fpu /* f30 */, unsigned char loop /* r28 */, float blend /* f31 */) {
    // Local variables
    class Object * target; // r0
    struct _List_iterator i; // r1+0x28
    class Object * o; // r28

    // References
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__28ObjPtr<8AnimTask,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__39ObjOwnerPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__8AnimTask;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndAnimatable * mPtr; // offset 0x8, size 0x4
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class AnimTask * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8046C56C -> 0x8046C6D8
float AnimTask::TimeUntilEnd(class AnimTask * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8046C6D8 -> 0x8046C7E8
void * AnimTask::~AnimTask(class AnimTask * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__39ObjOwnerPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8AnimTask,9ObjectDir>;
    // -> struct [anonymous] __vt__8AnimTask;
}

// Range: 0x8046C7E8 -> 0x8046C898
void AnimTask::Replace(class AnimTask * const this /* r31 */) {}

// Range: 0x8046C898 -> 0x8046CB00
void AnimTask::Poll(class AnimTask * const this /* r31 */, float time /* f28 */) {
    // Local variables
    float blend; // f29
    float preFrame; // f28
    float frame; // f30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8046CB00 -> 0x8046CB44
class Symbol AnimTask::ClassName() {
    // References
    // -> class Symbol name;
}

struct {
    // total size: 0x58
} __vt__8AnimTask; // size: 0x58, address: 0x808F1298
struct {
    // total size: 0x8
} __RTTI__8AnimTask; // size: 0x8, address: 0x808F1318
struct {
    // total size: 0x18
} __vt__28ObjPtr<8AnimTask,9ObjectDir>; // size: 0x18, address: 0x808F1320
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8AnimTask,9ObjectDir>; // size: 0x8, address: 0x808F1360
struct {
    // total size: 0x18
} __vt__39ObjOwnerPtr<13RndAnimatable,9ObjectDir>; // size: 0x18, address: 0x808F13B8
struct {
    // total size: 0x8
} __RTTI__39ObjOwnerPtr<13RndAnimatable,9ObjectDir>; // size: 0x8, address: 0x808F1408
struct {
    // total size: 0xA0
} __vt__13RndAnimatable; // size: 0xA0, address: 0x808F1410
struct {
    // total size: 0x58
} __vt__4Task; // size: 0x58, address: 0x808F14E0

