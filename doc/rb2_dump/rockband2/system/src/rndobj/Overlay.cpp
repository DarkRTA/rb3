/*
    Compile unit: C:\rockband2\system\src\rndobj\Overlay.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804D5438 -> 0x804D5A9C
*/
class list : public _List_base {
    // total size: 0x8
};
class list sOverlays; // size: 0x8, address: 0x809803F8
// Range: 0x804D5438 -> 0x804D5548
void RndOverlay::Init() {
    // Local variables
    class DataArray * cfg; // r30
    int i; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std25_List_node<P10RndOverlay>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sOverlays;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std25_List_node<P10RndOverlay>; // size: 0x8, address: 0x808FC7A8
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x804D5548 -> 0x804D55F4
void RndOverlay::Terminate() {
    // Local variables
    struct _List_iterator i; // r1+0x20

    // References
    // -> class list sOverlays;
}

// Range: 0x804D5654 -> 0x804D56BC
void RndOverlay::DrawAll() {
    // Local variables
    struct _List_iterator i; // r1+0x14
    float y; // f1

    // References
    // -> class list sOverlays;
}

// Range: 0x804D56BC -> 0x804D5728
void RndOverlay::SetTimeout(class RndOverlay * const this /* r31 */, float seconds /* f31 */) {}

// Range: 0x804D5728 -> 0x804D5854
class String & RndOverlay::CurrentLine(class RndOverlay * const this /* r30 */) {
    // Local variables
    class String s; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6String>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804D5854 -> 0x804D58D0
void RndOverlay::Clear(class RndOverlay * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
}

// Range: 0x804D58D0 -> 0x804D5A40
void RndOverlay::Print(class RndOverlay * const this /* r30 */) {
    // Local variables
    const char * c; // r31
    class String s; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6String>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x10
} __vt__10RndOverlay; // size: 0x10, address: 0x808FC830
struct {
    // total size: 0x8
} __RTTI__10RndOverlay; // size: 0x8, address: 0x808FC858
// Range: 0x804D5A40 -> 0x804D5A9C
static void __sinit_\Overlay_cpp() {
    // References
    // -> class list sOverlays;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndOverlay * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};

