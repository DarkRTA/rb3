/*
    Compile unit: C:\rockband2\system\src\bandobj\CrowdMeterIcon.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802C8554 -> 0x802C937C
*/
class DataArray * types; // size: 0x4, address: 0x80A50420
// Range: 0x802C8554 -> 0x802C8690
void * CrowdMeterIcon::CrowdMeterIcon(class CrowdMeterIcon * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14CrowdMeterIcon;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802C8690 -> 0x802C86F4
void CrowdMeterIcon::SetState() {}

// Range: 0x802C86F4 -> 0x802C8724
void CrowdMeterIcon::SetGlowing() {}

// Range: 0x802C8724 -> 0x802C872C
void CrowdMeterIcon::SetIcon() {}

// Range: 0x802C872C -> 0x802C87B0
void CrowdMeterIcon::ArrowShow(class CrowdMeterIcon * const this /* r31 */) {}

// Range: 0x802C87B0 -> 0x802C87C4
void CrowdMeterIcon::Deploy() {}

// Range: 0x802C87C4 -> 0x802C87D8
void CrowdMeterIcon::StopDeploy() {}

// Range: 0x802C87D8 -> 0x802C87EC
void CrowdMeterIcon::Reset() {}

// Range: 0x802C87EC -> 0x802C886C
unsigned char CrowdMeterIcon::SyncProperty(class CrowdMeterIcon * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A50428
static class Symbol _s; // size: 0x4, address: 0x80A50430
static class Symbol _s; // size: 0x4, address: 0x80A50438
static class Symbol _s; // size: 0x4, address: 0x80A50440
static class Symbol _s; // size: 0x4, address: 0x80A50448
static class Symbol _s; // size: 0x4, address: 0x80A50450
static class Symbol _s; // size: 0x4, address: 0x80A50458
static class Symbol _s; // size: 0x4, address: 0x80A50460
// Range: 0x802C886C -> 0x802C9270
class DataNode CrowdMeterIcon::Handle(class CrowdMeterIcon * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
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

// Range: 0x802C9270 -> 0x802C92B4
void CrowdMeterIcon::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802C92B4 -> 0x802C9374
void CrowdMeterIcon::PreLoad(class CrowdMeterIcon * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

// Range: 0x802C9374 -> 0x802C9378
void CrowdMeterIcon::PostLoad() {}

// Range: 0x802C9378 -> 0x802C937C
void CrowdMeterIcon::Copy() {}

struct {
    // total size: 0x21C
} __vt__14CrowdMeterIcon; // size: 0x21C, address: 0x808C8050

