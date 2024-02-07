/*
    Compile unit: C:\rockband2\band2\src\meta\StorePreviewMgrWii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801F89E4 -> 0x801F96C8
*/
static class PreviewDownloadCompleteMsg msg; // size: 0x8, address: 0x8097C7E0
// Range: 0x801F89E4 -> 0x801F8BAC
void StorePreviewMgrWii::ClearCurrentPreview(class StorePreviewMgrWii * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26PreviewDownloadCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class PreviewDownloadCompleteMsg msg;
    // -> const char * gNullStr;
}

// Range: 0x801F8BAC -> 0x801F8C04
void StorePreviewMgrWii::SetCurrentPreviewFile(class StorePreviewMgrWii * const this /* r30 */, const class String & strRemotePath /* r31 */) {}

// Range: 0x801F8C04 -> 0x801F8CD8
void StorePreviewMgrWii::DownloadPreviewFile(class StorePreviewMgrWii * const this /* r30 */, const class String & strRemotePath /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

static class PreviewDownloadCompleteMsg msg; // size: 0x8, address: 0x8097C7F8
// Range: 0x801F8CD8 -> 0x801F8F30
void StorePreviewMgrWii::Poll(class StorePreviewMgrWii * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26PreviewDownloadCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class PreviewDownloadCompleteMsg msg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801F8F30 -> 0x801F8F5C
unsigned char StorePreviewMgrWii::AllowPreviewDownload() {}

// Range: 0x801F8F5C -> 0x801F9044
void StorePreviewMgrWii::PlayCurrentPreview(class StorePreviewMgrWii * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4E46C
static class Symbol _s; // size: 0x4, address: 0x80A4E474
static class Symbol _s; // size: 0x4, address: 0x80A4E47C
static class Symbol _s; // size: 0x4, address: 0x80A4E484
static class Symbol _s; // size: 0x4, address: 0x80A4E48C
// Range: 0x801F9044 -> 0x801F96C8
class DataNode StorePreviewMgrWii::Handle(class StorePreviewMgrWii * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x58

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x6C
} __vt__18StorePreviewMgrWii; // size: 0x6C, address: 0x808A8DEC
struct {
    // total size: 0x8
} __RTTI__18StorePreviewMgrWii; // size: 0x8, address: 0x808A8E88

