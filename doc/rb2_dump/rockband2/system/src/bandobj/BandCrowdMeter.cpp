/*
    Compile unit: C:\rockband2\system\src\bandobj\BandCrowdMeter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8024423C -> 0x802483CC
*/
class DataArray * types; // size: 0x4, address: 0x80A4EDD8
// Range: 0x8024423C -> 0x802448AC
void * BandCrowdMeter::BandCrowdMeter(class BandCrowdMeter * const this /* r29 */) {
    // Local variables
    int i; // r30
    int ii; // r25

    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndMatAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtrList<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__14BandCrowdMeter;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

struct Node {
    // total size: 0xC
    class RndGroup * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
// Range: 0x802448AC -> 0x80245108
void * BandCrowdMeter::~BandCrowdMeter(class BandCrowdMeter * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__32ObjPtrList<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndMatAnim,9ObjectDir>;
}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x80245108 -> 0x80245648
void BandCrowdMeter::Poll(class BandCrowdMeter * const this /* r24 */) {
    // Local variables
    float peakValue; // f0
    int i; // r25
    int j; // r25
    class iterator i; // r1+0x34
    float desiredFrame; // r1+0x30
    float add; // f1
    float add; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80245648 -> 0x80245700
class DataNode BandCrowdMeter::OnSetVal(class BandCrowdMeter * const this /* r30 */, class DataArray * args /* r31 */) {
    // Local variables
    class Symbol name; // r1+0x14
    float value; // f31
}

// Range: 0x80245700 -> 0x8024574C
float BandCrowdMeter::GetPeakValue() {
    // Local variables
    float peakValue; // f1
    int i; // r5
}

static class Symbol guitar; // size: 0x4, address: 0x80A4EDE0
static class Symbol drum; // size: 0x4, address: 0x80A4EDE8
static class Symbol bass; // size: 0x4, address: 0x80A4EDF0
static class Symbol vocals; // size: 0x4, address: 0x80A4EDF8
static class DebugWarner _dw; // size: 0x100, address: 0x8097CD78
// Range: 0x8024574C -> 0x8024589C
enum TrackInstrument GetTrackInstrument(class Symbol & name /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> static class Symbol vocals;
    // -> static class Symbol bass;
    // -> static class Symbol drum;
    // -> static class Symbol guitar;
}

// Range: 0x8024589C -> 0x802458AC
void BandCrowdMeter::SetVal() {}

// Range: 0x802458AC -> 0x802458C0
void BandCrowdMeter::Disable() {}

// Range: 0x802458C0 -> 0x80245908
void BandCrowdMeter::SetCrowd(class BandCrowdMeter * const this /* r31 */) {}

// Range: 0x80245908 -> 0x802459BC
void BandCrowdMeter::UpdateExcitement(class BandCrowdMeter * const this /* r31 */) {
    // Local variables
    unsigned char maxed; // r4
}

// Range: 0x802459BC -> 0x802459D8
void BandCrowdMeter::SetPlayerIconState(enum TrackInstrument instrument /* r0 */) {}

// Range: 0x802459D8 -> 0x80245A00
void BandCrowdMeter::SetMaxed() {}

// Range: 0x80245A00 -> 0x80245A7C
void BandCrowdMeter::Deploy(class BandCrowdMeter * const this /* r30 */, enum TrackInstrument instrument /* r31 */) {}

// Range: 0x80245A7C -> 0x80245B34
void BandCrowdMeter::StopDeploy(class BandCrowdMeter * const this /* r30 */, enum TrackInstrument instrument /* r31 */) {}

// Range: 0x80245B34 -> 0x80245BB8
void BandCrowdMeter::EnablePlayer(class BandCrowdMeter * const this /* r31 */) {}

// Range: 0x80245BB8 -> 0x80245C3C
void BandCrowdMeter::DisablePlayer() {}

// Range: 0x80245C3C -> 0x80245C6C
void BandCrowdMeter::ShowPeakArrow() {}

// Range: 0x80245C6C -> 0x80245F80
void BandCrowdMeter::OnShowWorstCase(class BandCrowdMeter * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EE00
static class Symbol _s; // size: 0x4, address: 0x80A4EE08
static class Symbol _s; // size: 0x4, address: 0x80A4EE10
static class Symbol _s; // size: 0x4, address: 0x80A4EE18
static class Symbol _s; // size: 0x4, address: 0x80A4EE20
static class Symbol _s; // size: 0x4, address: 0x80A4EE28
static class Symbol _s; // size: 0x4, address: 0x80A4EE30
static class Symbol _s; // size: 0x4, address: 0x80A4EE38
static class Symbol _s; // size: 0x4, address: 0x80A4EE40
static class Symbol _s; // size: 0x4, address: 0x80A4EE48
static class Symbol _s; // size: 0x4, address: 0x80A4EE50
static class Symbol _s; // size: 0x4, address: 0x80A4EE58
static class Symbol _s; // size: 0x4, address: 0x80A4EE60
static class Symbol _s; // size: 0x4, address: 0x80A4EE68
// Range: 0x80245F80 -> 0x80246978
unsigned char BandCrowdMeter::SyncProperty(class BandCrowdMeter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80246978 -> 0x80246CCC
unsigned char PropSync(class vector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r27 */, enum PropOp op /* r28 */) {
    // Local variables
    class Symbol * it; // r31
    class Symbol tmp; // r1+0x24

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80246CCC -> 0x80246E28
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4EE70
static class Symbol _s; // size: 0x4, address: 0x80A4EE78
static class Symbol _s; // size: 0x4, address: 0x80A4EE80
static class Symbol _s; // size: 0x4, address: 0x80A4EE88
static class Symbol _s; // size: 0x4, address: 0x80A4EE90
static class Symbol _s; // size: 0x4, address: 0x80A4EE98
static class Symbol _s; // size: 0x4, address: 0x80A4EEA0
static class Symbol _s; // size: 0x4, address: 0x80A4EEA8
static class Symbol _s; // size: 0x4, address: 0x80A4EEB0
static class Symbol _s; // size: 0x4, address: 0x80A4EEB8
static class Symbol _s; // size: 0x4, address: 0x80A4EEC0
static class Symbol _s; // size: 0x4, address: 0x80A4EEC8
static class Symbol _s; // size: 0x4, address: 0x80A4EED0
static class Symbol _s; // size: 0x4, address: 0x80A4EED8
static class Symbol _s; // size: 0x4, address: 0x80A4EEE0
static class Symbol _s; // size: 0x4, address: 0x80A4EEE8
// Range: 0x80246E28 -> 0x80248054
class DataNode BandCrowdMeter::Handle(class BandCrowdMeter * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x88
    class MessageTimer _mt; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode _n; // r1+0x90

    // References
    // -> class Debug TheDebug;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80248054 -> 0x80248098
void BandCrowdMeter::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80248098 -> 0x802481A8
void BandCrowdMeter::PreLoad(class BandCrowdMeter * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

// Range: 0x802481A8 -> 0x802481AC
void BandCrowdMeter::PostLoad() {}

// Range: 0x802481AC -> 0x802483CC
void BandCrowdMeter::Copy(class BandCrowdMeter * const this /* r29 */, const class Object * o /* r26 */, enum CopyType ct /* r25 */) {
    // Local variables
    const class BandCrowdMeter * bcm; // r0

    // References
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14BandCrowdMeter;
}

struct {
    // total size: 0x18
} __vt__28ObjPtr<8RndGroup,9ObjectDir>; // size: 0x18, address: 0x808B2010
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8RndGroup,9ObjectDir>; // size: 0x8, address: 0x808B2050
struct {
    // total size: 0x18
} __vt__35ObjPtr<14CrowdMeterIcon,9ObjectDir>; // size: 0x18, address: 0x808B2058
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14CrowdMeterIcon,9ObjectDir>; // size: 0x8, address: 0x808B20A0
struct {
    // total size: 0x21C
} __vt__14BandCrowdMeter; // size: 0x21C, address: 0x808B20A8
struct {
    // total size: 0x8
} __RTTI__14BandCrowdMeter; // size: 0x8, address: 0x808B2328
struct {
    // total size: 0x18
} __vt__31ObjPtr<10RndMatAnim,9ObjectDir>; // size: 0x18, address: 0x808B2330
struct {
    // total size: 0x8
} __RTTI__31ObjPtr<10RndMatAnim,9ObjectDir>; // size: 0x8, address: 0x808B2378
struct {
    // total size: 0x18
} __vt__32ObjPtrList<8RndGroup,9ObjectDir>; // size: 0x18, address: 0x808B2380
struct {
    // total size: 0x8
} __RTTI__32ObjPtrList<8RndGroup,9ObjectDir>; // size: 0x8, address: 0x808B23C8
struct {
    // total size: 0x18
} __vt__26ObjPtr<6RndDir,9ObjectDir>; // size: 0x18, address: 0x808B23D0
struct {
    // total size: 0x8
} __RTTI__26ObjPtr<6RndDir,9ObjectDir>; // size: 0x8, address: 0x808B2410
struct {
    // total size: 0x18
} __vt__26ObjPtr<6RndMat,9ObjectDir>; // size: 0x18, address: 0x808B2470
struct {
    // total size: 0x8
} __RTTI__26ObjPtr<6RndMat,9ObjectDir>; // size: 0x8, address: 0x808B24B0
struct {
    // total size: 0x8
} __RTTI__14CrowdMeterIcon; // size: 0x8, address: 0x808B25E8
struct {
    // total size: 0x18
} __vt__36ObjPtrList<11RndPollable,9ObjectDir>; // size: 0x18, address: 0x808B26A0
struct {
    // total size: 0x8
} __RTTI__36ObjPtrList<11RndPollable,9ObjectDir>; // size: 0x8, address: 0x808B26E8
struct {
    // total size: 0x8
} __RTTI__PQ23Hmx5Color; // size: 0x8, address: 0x808B28F0
struct {
    // total size: 0x8
} __RTTI__P28ObjPtr<8RndGroup,9ObjectDir>; // size: 0x8, address: 0x808B2918
struct {
    // total size: 0x8
} __RTTI__P35ObjPtr<14CrowdMeterIcon,9ObjectDir>; // size: 0x8, address: 0x808B2970

