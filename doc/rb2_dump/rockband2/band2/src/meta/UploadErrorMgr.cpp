/*
    Compile unit: C:\rockband2\band2\src\meta\UploadErrorMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802138FC -> 0x80214038
*/
class UploadErrorMgr * TheUploadErrorMgr; // size: 0x4, address: 0x80A4EA60
static class Symbol session_ready; // size: 0x4, address: 0x80A4EA68
// Range: 0x802138FC -> 0x802139C0
void UploadErrorMgr::Init() {
    // References
    // -> class NetSession * TheNetSession;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UploadErrorMgr * TheUploadErrorMgr;
    // -> static class Symbol session_ready;
}

// Range: 0x802139C0 -> 0x80213A3C
void * UploadErrorMgr::UploadErrorMgr(class UploadErrorMgr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14UploadErrorMgr;
}

// Range: 0x80213A3C -> 0x80213AD8
void * UploadErrorMgr::~UploadErrorMgr(class UploadErrorMgr * const this /* r30 */) {}

// Range: 0x80213AD8 -> 0x80213C3C
unsigned char UploadErrorMgr::ShouldDisplayUploadError(class UploadErrorMgr * const this /* r29 */, int iErrorCode /* r31 */, const char * iString /* r30 */) {
    // Local variables
    class String key; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80213C3C -> 0x80213C50
unsigned char UploadErrorMgr::AlwaysShowError() {}

// Range: 0x80213C50 -> 0x80213C98
class String UploadErrorMgr::MakeErrorKey() {}

// Range: 0x80213C98 -> 0x80213D0C
class DataNode UploadErrorMgr::OnMsg(class UploadErrorMgr * const this /* r31 */) {}

// Range: 0x80213D0C -> 0x80214038
class DataNode UploadErrorMgr::Handle(class UploadErrorMgr * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__15SessionReadyMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__14UploadErrorMgr; // size: 0x54, address: 0x808AD958
struct {
    // total size: 0x8
} __RTTI__14UploadErrorMgr; // size: 0x8, address: 0x808AD9D0
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_Rb_tree_node<6String>; // size: 0x8, address: 0x808ADA30

