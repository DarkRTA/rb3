/*
    Compile unit: C:\rockband2\system\src\os\ContentMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A5F70 -> 0x805A688C
*/
// Range: 0x805A5F70 -> 0x805A5F84
void ContentMgr::RecurseCallback(const char * dir /* r0 */) {
    // References
    // -> class ContentMgr & TheContentMgr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std40_List_node<Q210ContentMgr12CallbackFile>; // size: 0x8, address: 0x80921FD8
// Range: 0x805A5F84 -> 0x805A5F94
unsigned char ContentMgr::RefreshDone() {}

// Range: 0x805A5F94 -> 0x805A5FB8
unsigned char ContentMgr::RefreshInProgress() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std36_List_node<PQ210ContentMgr8Callback>; // size: 0x8, address: 0x80922098
// Range: 0x805A5FB8 -> 0x805A6090
void ContentMgr::UnregisterCallback(class ContentMgr * const this /* r30 */, class Callback * c /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805A6090 -> 0x805A619C
class DataNode ContentMgr::OnAddContent(class ContentMgr * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6String>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x805A619C -> 0x805A629C
class DataNode ContentMgr::OnRemoveContent(class ContentMgr * const this /* r27 */, class DataArray * msg /* r28 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C
}

static class Symbol _s; // size: 0x4, address: 0x80A5489C
static class Symbol _s; // size: 0x4, address: 0x80A548A4
static class Symbol _s; // size: 0x4, address: 0x80A548AC
static class Symbol _s; // size: 0x4, address: 0x80A548B4
// Range: 0x805A629C -> 0x805A688C
class DataNode ContentMgr::Handle(class ContentMgr * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xB8
} __vt__10ContentMgr; // size: 0xB8, address: 0x80922128
struct {
    // total size: 0x8
} __RTTI__10ContentMgr; // size: 0x8, address: 0x80922200
class _List_node : public _List_node_base {
    // total size: 0x28
public:
    struct CallbackFile _M_data; // offset 0x8, size 0x20
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Content * _M_data; // offset 0x8, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Callback * _M_data; // offset 0x8, size 0x4
};

