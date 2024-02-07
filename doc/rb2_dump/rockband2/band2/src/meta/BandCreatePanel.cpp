/*
    Compile unit: C:\rockband2\band2\src\meta\BandCreatePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800B1B74 -> 0x800B2500
*/
class DataArray * types; // size: 0x4, address: 0x80A4A520
class Symbol name; // size: 0x4, address: 0x80A4A528
class BandCreatePanel : public UIPanel {
    // total size: 0x68
    class DataArray * mNames; // offset 0x30, size 0x4
    class DataLoader * mLoader; // offset 0x34, size 0x4
    unsigned char mRandomNames; // offset 0x38, size 0x1
};
// Range: 0x800B1B74 -> 0x800B1C08
void * BandCreatePanel::BandCreatePanel(class BandCreatePanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15BandCreatePanel;
}

static class Symbol tour; // size: 0x4, address: 0x80A4A530
static class Symbol band_names; // size: 0x4, address: 0x80A4A538
// Range: 0x800B1C08 -> 0x800B1D58
void BandCreatePanel::Load(class BandCreatePanel * const this /* r28 */) {
    // Local variables
    class DataArray * names; // r31
    const char * path; // r29

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol band_names;
    // -> static class Symbol tour;
}

// Range: 0x800B1D58 -> 0x800B1DBC
unsigned char BandCreatePanel::IsLoaded(class BandCreatePanel * const this /* r30 */) {}

// Range: 0x800B1DBC -> 0x800B1E64
void BandCreatePanel::FinishLoad(class BandCreatePanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800B1E64 -> 0x800B1EC4
void BandCreatePanel::Unload(class BandCreatePanel * const this /* r31 */) {}

// Range: 0x800B1EC4 -> 0x800B1FCC
char * BandCreatePanel::CreateRandomBandName(class BandCreatePanel * const this /* r28 */) {
    // Local variables
    class DataArray * first; // r29
    class DataArray * second; // r28
    const char * name; // r30
}

static class Symbol _s; // size: 0x4, address: 0x80A4A540
// Range: 0x800B1FCC -> 0x800B2374
class DataNode BandCreatePanel::Handle(class BandCreatePanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A4A548
// Range: 0x800B2374 -> 0x800B2500
unsigned char BandCreatePanel::SyncProperty(class BandCreatePanel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB0
} __vt__15BandCreatePanel; // size: 0xB0, address: 0x8087DF48
struct {
    // total size: 0x8
} __RTTI__15BandCreatePanel; // size: 0x8, address: 0x8087E028

