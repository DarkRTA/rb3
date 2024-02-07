/*
    Compile unit: C:\rockband2\band2\src\meta\StoreEnumeration.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801F78B4 -> 0x801F7F34
*/
// Range: 0x801F78B4 -> 0x801F78F0
void * StoreEnumeration::StoreEnumeration() {
    // References
    // -> struct [anonymous] __vt__16StoreEnumeration;
}

// Range: 0x801F78F0 -> 0x801F7944
unsigned char __eq() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
enum State {
    kEnumWaiting = 0,
    kEnumProcessing = 1,
    kPreSuccess = 2,
    kPreFail = 3,
    kSuccess = 4,
    kFail = 5,
};
class WiiEnumeration : public StoreEnumeration, public Object {
    // total size: 0x70
protected:
    unsigned char mSuccess; // offset 0x38, size 0x1
private:
    unsigned short mCurrentPos; // offset 0x3A, size 0x2
    class String mCurrentTitle; // offset 0x3C, size 0xC
    class vector mTitleIds; // offset 0x48, size 0xC
    class map mContentList; // offset 0x54, size 0x18
    enum State mState; // offset 0x6C, size 0x4
};
// Range: 0x801F7944 -> 0x801F79EC
void * WiiEnumeration::WiiEnumeration(class WiiEnumeration * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14WiiEnumeration;
}

struct pair {
    // total size: 0x8
    unsigned long first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
static class Symbol store; // size: 0x4, address: 0x80A4E45C
static class Symbol titles; // size: 0x4, address: 0x80A4E464
// Range: 0x801F79EC -> 0x801F7C00
void WiiEnumeration::Start(class WiiEnumeration * const this /* r30 */) {
    // Local variables
    class DataArray * store_titles; // r26
    int i; // r27

    // References
    // -> static class Symbol titles;
    // -> static class Symbol store;
    // -> class Debug TheDebug;
}

// Range: 0x801F7C00 -> 0x801F7C18
unsigned char WiiEnumeration::IsSuccess() {}

// Range: 0x801F7C18 -> 0x801F7C3C
unsigned char WiiEnumeration::IsEnumerating() {}

// Range: 0x801F7C3C -> 0x801F7D64
void WiiEnumeration::Poll(class WiiEnumeration * const this /* r31 */) {
    // Local variables
    unsigned char ret; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x801F7D64 -> 0x801F7F34
class DataNode WiiEnumeration::OnMsg(class WiiEnumeration * const this /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x18
    struct EnumProduct p; // r1+0x28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std45_List_node<Q216StoreEnumeration11EnumProduct>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class ContentMgr & TheContentMgr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std45_List_node<Q216StoreEnumeration11EnumProduct>; // size: 0x8, address: 0x808A8AD8
struct {
    // total size: 0x74
} __vt__14WiiEnumeration; // size: 0x74, address: 0x808A8AF8
struct {
    // total size: 0x8
} __RTTI__14WiiEnumeration; // size: 0x8, address: 0x808A8B98
struct {
    // total size: 0x1C
} __vt__16StoreEnumeration; // size: 0x1C, address: 0x808A8C00
struct {
    // total size: 0x8
} __RTTI__16StoreEnumeration; // size: 0x8, address: 0x808A8C30
struct {
    // total size: 0x8
} __RTTI__P6String; // size: 0x8, address: 0x808A8C78

