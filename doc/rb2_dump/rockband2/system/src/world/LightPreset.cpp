/*
    Compile unit: C:\rockband2\system\src\world\LightPreset.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80429FF8 -> 0x804372B8
*/
class DataArray * types; // size: 0x4, address: 0x80A52418
class Symbol name; // size: 0x4, address: 0x80A52420
class deque : protected _Deque_base {
    // total size: 0x28
};
class deque sManualEvents; // size: 0x28, address: 0x8097EF58
struct _SpotlightEntryCompressedInternal SpotlightOff; // size: 0x20, address: 0x8097EF90
class SpotlightEntryCompressed SpotlightEntryOff; // size: 0x4, address: 0x80A52424
// Range: 0x80429FF8 -> 0x8042A1F0
void * LightPreset::LightPreset(class LightPreset * const this /* r31 */) {
    // Local variables
    int i; // r5

    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__11LightPreset;
}

// Range: 0x8042A1F0 -> 0x8042A240
unsigned char LightPreset::PlatformOk() {
    // Local variables
    enum Platform p; // r3

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8042A240 -> 0x8042A7C4
void * LightPreset::~LightPreset(class LightPreset * const this /* r30 */) {
    // Local variables
    int i; // r29

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__11LightPreset;
}

// Range: 0x8042A7C4 -> 0x8042A7D0
void LightPreset::ResetEvents() {
    // References
    // -> class deque sManualEvents;
}

// Range: 0x8042A7D0 -> 0x8042AAFC
void LightPreset::Clear(class LightPreset * const this /* r31 */) {
    // Local variables
    unsigned int i; // r28
    unsigned int i; // r28
    unsigned int i; // r28
    unsigned int i; // r28
}

// Range: 0x8042AAFC -> 0x8042B3AC
void LightPreset::Copy(class LightPreset * const this /* r27 */, const class Object * o /* r26 */, enum CopyType type /* r25 */) {
    // Local variables
    const class LightPreset * f; // r0
    unsigned int i; // r25
    unsigned int i; // r25
    unsigned int i; // r25
    unsigned int i; // r25

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11LightPreset;
}

static int REV; // size: 0x4, address: 0x80A47060
// Range: 0x8042B3AC -> 0x8042B3F0
void LightPreset::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A52428
static unsigned char sLoading; // size: 0x1, address: 0x80A5242C
static class Symbol target_animator; // size: 0x4, address: 0x80A52430
// Range: 0x8042B3F0 -> 0x8042D334
void LightPreset::Load(class LightPreset * const this /* r27 */, class BinStream & d /* r28 */) {
    // Local variables
    int size; // r1+0x1E4
    int storageSize; // r1+0x1E0
    int storageIndex; // r25
    int i; // r26
    int i; // r25
    char buf[128]; // r1+0x2B0
    int sz; // r1+0x1DC
    unsigned int i; // r25
    unsigned int i; // r25
    unsigned int i; // r25
    struct Keyframe pulseFrame; // r1+0x470
    class String selectionScriptStr; // r1+0x20C
    class String pulseScriptStr; // r1+0x200
    unsigned int i; // r25
    int i; // r1+0x1D8
    unsigned int i; // r25
    unsigned int i; // r25
    unsigned int i; // r25
    unsigned int i; // r25
    class RndDir * backlightDir; // r25
    const class DataNode * backlight; // r0
    const class DataNode * backlightEvent; // r0
    const class DataNode * target1; // r25
    const class DataNode * target2; // r25
    const class DataNode * target3; // r25
    const class DataNode * target4; // r25
    const class DataNode * target5; // r25
    const class DataNode * target6; // r25

    // References
    // -> struct [anonymous] __RTTI__9Character;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> const char * gNullStr;
    // -> static class Symbol target_animator;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__15SpotlightDrawer;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
    // -> class Debug TheDebug;
    // -> static int REV;
    // -> static int gRev;
    // -> static unsigned char sLoading;
}

// Range: 0x8042D334 -> 0x8042D668
void LightPreset::Replace(class LightPreset * const this /* r30 */, class Object * to /* r31 */) {
    // Local variables
    unsigned int i; // r7
    unsigned int i; // r7
    unsigned int i; // r7
    unsigned int i; // r7

    // References
    // -> struct [anonymous] __RTTI__15SpotlightDrawer;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
}

// Range: 0x8042D668 -> 0x8042D8E4
void LightPreset::RemoveSpotlight(class LightPreset * const this /* r28 */, int index /* r29 */) {
    // Local variables
    unsigned int i; // r5

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x8042D8E4 -> 0x8042DB5C
void LightPreset::RemoveEnvironment(class LightPreset * const this /* r30 */, int index /* r31 */) {
    // Local variables
    unsigned int i; // r6
}

// Range: 0x8042DB5C -> 0x8042DDDC
void LightPreset::RemoveLight(class LightPreset * const this /* r30 */, int index /* r31 */) {
    // Local variables
    unsigned int i; // r6
}

// Range: 0x8042DDDC -> 0x8042DFDC
void LightPreset::RemoveSpotlightDrawer(class LightPreset * const this /* r30 */, int index /* r31 */) {
    // Local variables
    unsigned int i; // r5
}

static class Message play_anim; // size: 0x8, address: 0x8097EFC0
// Range: 0x8042DFDC -> 0x8042E758
void LightPreset::StartAnim(class LightPreset * const this /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> static class Message play_anim;
    // -> struct [anonymous] __vt__7Message;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8042E758 -> 0x8042E760
void LightPreset::SetFrame() {}

static class Timer * _t; // size: 0x4, address: 0x80A52438
static class Message start; // size: 0x8, address: 0x8097EFD8
// Range: 0x8042E760 -> 0x8042EC50
void LightPreset::SetFrameEx(class LightPreset * const this /* r27 */, float frame /* f28 */, float blend /* f31 */, unsigned char same /* r28 */) {
    // Local variables
    class AutoTimer _at; // r1+0x2C
    const struct Keyframe * curFrame; // r30
    const struct Keyframe * prevFrame; // r29
    float curBlend; // r1+0x28
    float nextEvent; // f30
    float fadeBeats; // f29
    float timePassed; // f1
    int prevFrameI; // r1+0x24
    int curFrameI; // r1+0x20

    // References
    // -> static class Message start;
    // -> struct [anonymous] __vt__7Message;
    // -> class TaskMgr TheTaskMgr;
    // -> class deque sManualEvents;
    // -> class LoadMgr TheLoadMgr;
    // -> static class Timer * _t;
}

// Range: 0x8042EC50 -> 0x8042ECDC
void LightPreset::OnNext() {
    // References
    // -> class deque sManualEvents;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8042ECDC -> 0x8042ED68
void LightPreset::OnPrev() {
    // References
    // -> class deque sManualEvents;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8042ED68 -> 0x8042EDF4
void LightPreset::OnFirst() {
    // References
    // -> class deque sManualEvents;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8042EDF4 -> 0x8042EF54
void LightPreset::AdvanceManual(class LightPreset * const this /* r31 */, int advance /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8042EF54 -> 0x8042F30C
void LightPreset::GetKey(class LightPreset * const this /* r25 */, float frame /* f30 */, int & prev /* r26 */, int & next /* r27 */, float & alpha /* r28 */) {
    // Local variables
    float fadeStart; // f31
    int before; // r30
    int after; // r29
    int between; // r4
    float f; // f0
    float fadeStart; // f31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8042F30C -> 0x8042F370
void LightPreset::ApplyState(class LightPreset * const this /* r30 */, const struct Keyframe & frame /* r31 */) {}

// Range: 0x8042F370 -> 0x8042F5E8
void LightPreset::DecompressSpotEntryVec(class ObjVector & destination /* r28 */, const class ObjVector & source /* r29 */) {
    // Local variables
    int i; // r26

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x8042F5E8 -> 0x8042FA0C
void LightPreset::AnimateState(class LightPreset * const this /* r28 */, const struct Keyframe & frame /* r29 */, const struct Keyframe & nextFrame /* r30 */, float blend /* f31 */) {
    // Local variables
    unsigned int i; // r31
    unsigned int i; // r31
    unsigned int i; // r31
    unsigned int i; // r31
}

// Range: 0x8042FA0C -> 0x8042FD80
void LightPreset::Animate(class LightPreset * const this /* r30 */, float blend /* f31 */) {
    // Local variables
    unsigned int i; // r29
    unsigned int i; // r29
    unsigned int i; // r29
    unsigned int i; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8042FD80 -> 0x8042FEFC
void LightPreset::SetKeyframe(class LightPreset * const this /* r30 */, struct Keyframe & frame /* r31 */) {
    // Local variables
    unsigned int i; // r29
    unsigned int i; // r29
    unsigned int i; // r29
    unsigned int i; // r29
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class Spotlight * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8042FEFC -> 0x80430244
void LightPreset::SyncNewSpotlights(class LightPreset * const this /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x1C
    class Spotlight & test; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndEnviron * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class SpotlightDrawer * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80430244 -> 0x80430C24
void LightPreset::SyncKeyframeTargets(class LightPreset * const this /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x84
    class Spotlight & test; // r1+0x58
    class ObjDirItr i; // r1+0x70
    class RndEnviron & test; // r1+0x54
    class iterator i; // r1+0x50
    class RndLight * light; // r1+0x4C
    class ObjDirItr i; // r1+0x5C
    class SpotlightDrawer & test; // r1+0x48

    // References
    // -> struct [anonymous] __RTTI__15SpotlightDrawer;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9Spotlight;
}

// Range: 0x80430C24 -> 0x80431120
void LightPreset::AddSpotlight(class LightPreset * const this /* r28 */, class Spotlight * light /* r1+0x10 */, unsigned char initToBlack /* r26 */) {
    // Local variables
    struct SpotlightEntry entry; // r1+0x70
    unsigned int i; // r30

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SpotlightEntryCompressed SpotlightEntryOff;
}

// Range: 0x80431120 -> 0x804313E4
void LightPreset::AddEnvironment(class LightPreset * const this /* r30 */, class RndEnviron * env /* r1+0x10 */) {
    // Local variables
    struct EnvironmentEntry entry; // r1+0x30
    unsigned int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804313E4 -> 0x804316A0
void LightPreset::AddLight(class LightPreset * const this /* r30 */, class RndLight * light /* r1+0x10 */) {
    // Local variables
    struct EnvLightEntry entry; // r1+0x30
    unsigned int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804316A0 -> 0x804318DC
void LightPreset::AddSpotlightDrawer(class LightPreset * const this /* r30 */, class SpotlightDrawer * sd /* r1+0x8 */) {
    // Local variables
    struct SpotlightDrawerEntry entry; // r1+0x20
    unsigned int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804318DC -> 0x80431BC0
void LightPreset::CacheFrames(class LightPreset * const this /* r26 */) {
    // Local variables
    float frame; // f31
    unsigned int i; // r28
    struct Keyframe & key; // r0
    struct Keyframe & lastKey; // r0
    unsigned int j; // r27
    unsigned int j; // r27
    unsigned int j; // r27
    unsigned int j; // r27
}

// Range: 0x80431BC0 -> 0x80431BF4
void LightPreset::TranslateColor() {}

// Range: 0x80431BF4 -> 0x80431E08
void LightPreset::FillSpotPresetData(class Spotlight * spot /* r29 */, struct SpotlightEntry & entry /* r30 */, int propogateType /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80431E08 -> 0x80432214
void LightPreset::FillSpotPresetData(class Spotlight * spot /* r29 */, class SpotlightEntryCompressed & entry /* r30 */, int propogateType /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80432214 -> 0x804325C0
void LightPreset::AnimateSpotFromPreset(class LightPreset * const this /* r29 */, class Spotlight * spot /* r30 */, const struct SpotlightEntry & entry /* r31 */, float blend /* f30 */) {
    // Local variables
    class Color newColor; // r1+0x50
    float newIntensity; // f1
    class Color entryColor; // r1+0x40
    class Quat ZeroQuat; // r1+0x30
    class Quat to; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804325C0 -> 0x8043270C
void LightPreset::FillLightPresetData(class RndLight * l /* r30 */, struct EnvLightEntry & entry /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8043270C -> 0x804329C8
void LightPreset::AnimateLightFromPreset(class RndLight * l /* r30 */, const struct EnvLightEntry & entry /* r31 */, float blend /* f31 */) {
    // Local variables
    class Color color; // r1+0x20
    float range; // f30
    class Matrix3 m; // r1+0x70
    class Transform xfm; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804329C8 -> 0x80432B80
void LightPreset::FillEnvPresetData(class RndEnviron * e /* r30 */, struct EnvironmentEntry & entry /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80432B80 -> 0x8043301C
void LightPreset::AnimateEnvFromPreset(class LightPreset * const this /* r29 */, class RndEnviron * e /* r30 */, const struct EnvironmentEntry & entry /* r31 */, float blend /* f31 */) {
    // Local variables
    class Color ambientColor; // r1+0x20
    float fogStart; // f29
    float fogEnd; // f28
    class Color fogColor; // r1+0x10
    float farPlane; // f0

    // References
    // -> class RndCam * sCurrent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8043301C -> 0x80433038
void LightPreset::FillSpotlightDrawerPresetData() {}

// Range: 0x80433038 -> 0x80433078
void LightPreset::AnimateSpotlightDrawerFromPreset() {
    // Local variables
    float res; // f0
}

// Range: 0x80433078 -> 0x8043315C
void LightPreset::SetSpotlight(class LightPreset * const this /* r27 */, class Spotlight * spot /* r28 */, int propogateFlags /* r29 */) {
    // Local variables
    unsigned int i; // r31
    unsigned int k; // r30
}

// Range: 0x8043315C -> 0x8043322C
class DataNode LightPreset::OnSetKeyframe(class LightPreset * const this /* r29 */, class DataArray * args /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8043322C -> 0x804332B0
class DataNode LightPreset::OnViewKeyframe(class LightPreset * const this /* r30 */, class DataArray * args /* r31 */) {}

// Range: 0x804332B0 -> 0x80433830
void * Keyframe::Keyframe(struct Keyframe * const this /* r30 */, class Object * owner /* r28 */) {
    // Local variables
    class LightPreset * preset; // r31

    // References
    // -> static unsigned char sLoading;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11LightPreset;
}

// Range: 0x80433830 -> 0x80433B64
void * Keyframe::~Keyframe(struct Keyframe * const this /* r30 */) {}

// Range: 0x80433B64 -> 0x80433B68
void Keyframe::Load() {}

// Range: 0x80433B68 -> 0x80433E04
int Keyframe::Load(struct Keyframe * const this /* r27 */, class BinStream & d /* r28 */, struct _SpotlightEntryCompressedInternal * dst /* r29 */, unsigned char dropDead /* r30 */) {
    // Local variables
    int size; // r1+0x20
    int storageIndex; // r26
    int i; // r31
    int dummy; // r1+0x1C

    // References
    // -> static int gRev;
}

// Range: 0x80433E04 -> 0x80433E50
void * SpotlightEntry::SpotlightEntry() {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80433E50 -> 0x80433FC8
void SpotlightEntry::CalculateDirection(const struct SpotlightEntry * const this /* r27 */, class Spotlight * slight /* r28 */, class Quat & out /* r29 */) {
    // Local variables
    class RndTransformable * target; // r30
    class ObjectDir * dir; // r0
    class Matrix3 m; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> const char * gNullStr;
}

// Range: 0x80433FC8 -> 0x80434340
void SpotlightEntry::Animate(struct SpotlightEntry * const this /* r29 */, class Spotlight * slight /* r30 */, const class SpotlightEntryCompressed & other /* r31 */, float blend /* f31 */) {
    // Local variables
    float i; // f4
    float oi; // f0
    class Color c; // r1+0x50
    class Color oc; // r1+0x40
    class Quat from; // r1+0x30
    class Quat to; // r1+0x20

    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
}

// Range: 0x80434340 -> 0x8043458C
struct SpotlightEntry & SpotlightEntry::__as(struct SpotlightEntry * const this /* r30 */, const class SpotlightEntryCompressed & compressed /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
}

// Range: 0x8043458C -> 0x8043459C
void * SpotlightEntryCompressed::SpotlightEntryCompressed() {
    // References
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
}

static class Symbol bone_pelvis; // size: 0x4, address: 0x80A52440
// Range: 0x8043459C -> 0x80434D58
unsigned char SpotlightEntryCompressed::Load(class SpotlightEntryCompressed * const this /* r30 */, class BinStream & d /* r31 */, struct _SpotlightEntryCompressedInternal * dst /* r29 */, unsigned char dropDead /* r28 */) {
    // Local variables
    float intensity; // r1+0x1C
    class Quat q; // r1+0x60
    class Color c; // r1+0x50
    class ObjPtr target; // r1+0x40
    int flareSteps; // r1+0x18
    class Quat q; // r1+0x30
    class Color c; // r1+0x20
    int flareSteps; // r1+0x14
    class Character * dude; // r0

    // References
    // -> struct [anonymous] __RTTI__9Character;
    // -> static class Symbol bone_pelvis;
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
    // -> static int gRev;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

struct Node {
    // total size: 0xC
    class RndLight * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x80434D58 -> 0x80434F54
void SpotlightEntryCompressed::CalculateDirection(const class SpotlightEntryCompressed * const this /* r29 */, class Spotlight * slight /* r30 */, class Quat & out /* r31 */) {
    // Local variables
    class RndTransformable * target; // r27
    class ObjectDir * dir; // r0
    class Matrix3 m; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> const char * gNullStr;
}

// Range: 0x80434F54 -> 0x804351AC
unsigned char SpotlightEntryCompressed::__ne(const class SpotlightEntryCompressed * const this /* r30 */, const class SpotlightEntryCompressed & other /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
}

// Range: 0x804351AC -> 0x80435210
void * _SpotlightEntryCompressedInternal::_SpotlightEntryCompressedInternal() {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
}

// Range: 0x80435210 -> 0x80435308
void EnvironmentEntry::Load(struct EnvironmentEntry * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80435308 -> 0x80435430
void EnvironmentEntry::Animate() {
    // Local variables
    float farPlane; // f0

    // References
    // -> class RndCam * sCurrent;
}

// Range: 0x80435430 -> 0x80435520
unsigned char EnvironmentEntry::__ne() {}

// Range: 0x80435520 -> 0x8043568C
void EnvLightEntry::Load(struct EnvLightEntry * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class Color color; // r1+0x10
}

// Range: 0x8043568C -> 0x804358E4
void EnvLightEntry::Animate(struct EnvLightEntry * const this /* r30 */, const struct EnvLightEntry & other /* r31 */, float blend /* f31 */) {
    // Local variables
    class Color a; // r1+0x20
    class Color b; // r1+0x10
}

// Range: 0x804358E4 -> 0x804359D0
unsigned char EnvLightEntry::__ne() {}

// Range: 0x804359D0 -> 0x80435A34
void SpotlightDrawerEntry::Load(struct SpotlightDrawerEntry * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80435A34 -> 0x80435A74
void SpotlightDrawerEntry::Animate() {}

// Range: 0x80435A74 -> 0x80435AC0
unsigned char SpotlightDrawerEntry::__ne() {}

static class Symbol _s; // size: 0x4, address: 0x80A52448
static class Symbol _s; // size: 0x4, address: 0x80A52450
static class Symbol _s; // size: 0x4, address: 0x80A52458
// Range: 0x80435AC0 -> 0x80435D68
unsigned char PropSync(struct Keyframe & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A52460
static class Symbol _s; // size: 0x4, address: 0x80A52468
static class Symbol _s; // size: 0x4, address: 0x80A52470
static class Symbol _s; // size: 0x4, address: 0x80A52478
static class Symbol _s; // size: 0x4, address: 0x80A52480
static class Symbol _s; // size: 0x4, address: 0x80A52488
// Range: 0x80435D68 -> 0x8043676C
class DataNode LightPreset::Handle(class LightPreset * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
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

static class Symbol _s; // size: 0x4, address: 0x80A52490
static class Symbol _s; // size: 0x4, address: 0x80A52498
static class Symbol _s; // size: 0x4, address: 0x80A524A0
static class Symbol _s; // size: 0x4, address: 0x80A524A8
static class Symbol _s; // size: 0x4, address: 0x80A524B0
static class Symbol _s; // size: 0x4, address: 0x80A524B8
static class Symbol _s; // size: 0x4, address: 0x80A524C0
static class Symbol _s; // size: 0x4, address: 0x80A524C8
static class Symbol _s; // size: 0x4, address: 0x80A524D0
static class Symbol _s; // size: 0x4, address: 0x80A524D8
static class Symbol _s; // size: 0x4, address: 0x80A524E0
static class Symbol _s; // size: 0x4, address: 0x80A524E8
// Range: 0x8043676C -> 0x80437210
unsigned char LightPreset::SyncProperty(class LightPreset * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8LightHue;
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
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__15SpotlightDrawer; // size: 0x8, address: 0x808ECFF0
struct {
    // total size: 0xA4
} __vt__11LightPreset; // size: 0xA4, address: 0x808ED038
struct {
    // total size: 0x8
} __RTTI__8RndLight; // size: 0x8, address: 0x808ED368
struct {
    // total size: 0x8
} __RTTI__PPQ211stlpmtx_std9pair<i,f>; // size: 0x8, address: 0x808ED520
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std9pair<i,f>; // size: 0x8, address: 0x808ED548
struct {
    // total size: 0x8
} __RTTI__PP15SpotlightDrawer; // size: 0x8, address: 0x808ED568
struct {
    // total size: 0x8
} __RTTI__PP8RndLight; // size: 0x8, address: 0x808ED580
struct {
    // total size: 0x8
} __RTTI__PP10RndEnviron; // size: 0x8, address: 0x808ED598
struct {
    // total size: 0x8
} __RTTI__PP9Spotlight; // size: 0x8, address: 0x808ED5B0
struct {
    // total size: 0x8
} __RTTI__PQ211LightPreset20SpotlightDrawerEntry; // size: 0x8, address: 0x808ED5E0
struct {
    // total size: 0x8
} __RTTI__PQ211LightPreset13EnvLightEntry; // size: 0x8, address: 0x808ED608
struct {
    // total size: 0x8
} __RTTI__PQ211LightPreset16EnvironmentEntry; // size: 0x8, address: 0x808ED630
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211LightPreset24SpotlightEntryCompressed; // size: 0x8, address: 0x808ED660
struct {
    // total size: 0x8
} __RTTI__PQ211LightPreset8Keyframe; // size: 0x8, address: 0x808ED680
struct {
    // total size: 0x8
} __RTTI__PQ211LightPreset14SpotlightEntry; // size: 0x8, address: 0x808ED6C0
// Range: 0x80437210 -> 0x804372B8
static void __sinit_\LightPreset_cpp() {
    // References
    // -> class SpotlightEntryCompressed SpotlightEntryOff;
    // -> struct _SpotlightEntryCompressedInternal SpotlightOff;
    // -> class deque sManualEvents;
}

class StlNodeAlloc {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
struct pair {
    // total size: 0x8
    int first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
struct _Deque_iterator_base {
    // total size: 0x10
    struct pair * _M_cur; // offset 0x0, size 0x4
    struct pair * _M_first; // offset 0x4, size 0x4
    struct pair * _M_last; // offset 0x8, size 0x4
    struct pair * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * * _M_data; // offset 0x0, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};

