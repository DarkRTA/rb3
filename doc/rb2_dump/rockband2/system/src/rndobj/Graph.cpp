/*
    Compile unit: C:\rockband2\system\src\rndobj\Graph.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805204BC -> 0x80520EEC
*/
static class RndGraph * sOneFrame; // size: 0x4, address: 0x80A53C58
class list : public _List_base {
    // total size: 0x8
};
static class list sGraphs; // size: 0x8, address: 0x80981A70
class list : public _List_base {
    // total size: 0x8
};
static class list sFakes; // size: 0x8, address: 0x80981A88
static class ObjPtr sCam; // size: 0xC, address: 0x80981A9C
// Range: 0x805204BC -> 0x8052052C
void RndGraph::SetCamera(class RndCam * cam /* r31 */) {
    // References
    // -> static class ObjPtr sCam;
}

// Range: 0x8052052C -> 0x80520574
class RndGraph * RndGraph::GetOneFrame() {
    // References
    // -> static class RndGraph * sOneFrame;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80520574 -> 0x80520690
void RndGraph::DrawAll() {
    // Local variables
    struct _List_iterator it; // r1+0x24
    struct _List_iterator jt; // r1+0x20

    // References
    // -> static class list sFakes;
    // -> static class RndGraph * sOneFrame;
    // -> static class list sGraphs;
    // -> static class ObjPtr sCam;
}

// Range: 0x80520690 -> 0x80520790
class RndGraph * RndGraph::Get(void * id /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x18

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8RndGraph>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list sGraphs;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8RndGraph>; // size: 0x8, address: 0x80904878
struct FakeGraph {
    // total size: 0x8
    void * mId; // offset 0x0, size 0x4
    void (* mDrawCallback)(); // offset 0x4, size 0x4
};
// Range: 0x80520790 -> 0x805207BC
void * RndGraph::RndGraph() {}

// Range: 0x805207BC -> 0x80520850
void * RndGraph::~RndGraph(class RndGraph * const this /* r30 */) {}

// Range: 0x80520850 -> 0x805208EC
void RndGraph::Draw(class RndGraph * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805208EC -> 0x805209B0
void RndGraph::Reset(class RndGraph * const this /* r30 */) {
    // Local variables
    int i; // r31
}

class Drawable {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
// Range: 0x805209B0 -> 0x80520AC4
void RndGraph::AddLine(class RndGraph * const this /* r28 */, const class Vector3 & a /* r29 */, const class Vector3 & b /* r30 */, const class Color & col /* r31 */) {
    // References
    // -> struct [anonymous] __vt__4Line;
}

// Range: 0x80520AC4 -> 0x80520BDC
void RndGraph::AddSphere(class RndGraph * const this /* r28 */, const class Vector3 & center /* r29 */, float radius /* f31 */, const class Color & col /* r30 */, int numLats /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10DrawSphere;
}

// Range: 0x80520BDC -> 0x80520CD8
void RndGraph::AddString3D(class RndGraph * const this /* r27 */, const char * text /* r28 */, const class Vector3 & worldPos /* r29 */, const class Color & col /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12DrawString3D;
}

class DrawString3D : public Drawable {
    // total size: 0x40
public:
    class Vector3 mPos; // offset 0x10, size 0x10
    class String mText; // offset 0x20, size 0xC
    class Color mCol; // offset 0x30, size 0x10
};
// Range: 0x80520CD8 -> 0x80520CE8
void DrawString3D::DrawFixedZ() {}

// Range: 0x80520CE8 -> 0x80520CFC
void DrawString3D::Draw(class DrawString3D * const this /* r5 */) {}

struct {
    // total size: 0x14
} __vt__12DrawString3D; // size: 0x14, address: 0x809048A8
struct {
    // total size: 0x8
} __RTTI__12DrawString3D; // size: 0x8, address: 0x809048D8
class DrawSphere : public Drawable {
    // total size: 0x50
public:
    class Vector3 mCenter; // offset 0x10, size 0x10
    float mRadius; // offset 0x20, size 0x4
    class Color mCol; // offset 0x30, size 0x10
    int mNumLats; // offset 0x40, size 0x4
};
// Range: 0x80520CFC -> 0x80520D54
void DrawSphere::DrawFixedZ(class DrawSphere * const this /* r5 */) {}

// Range: 0x80520D54 -> 0x80520D68
void DrawSphere::Draw() {}

struct {
    // total size: 0x14
} __vt__10DrawSphere; // size: 0x14, address: 0x809048E0
struct {
    // total size: 0x8
} __RTTI__10DrawSphere; // size: 0x8, address: 0x80904910
class Line : public Drawable {
    // total size: 0x40
public:
    class Vector3 mA; // offset 0x10, size 0x10
    class Vector3 mB; // offset 0x20, size 0x10
    class Color mCol; // offset 0x30, size 0x10
};
// Range: 0x80520D68 -> 0x80520DE4
void Line::DrawFixedZ(class Line * const this /* r6 */) {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80520DE4 -> 0x80520E0C
void Line::Draw(class Line * const this /* r6 */) {
    // References
    // -> class Rnd & TheRnd;
}

struct {
    // total size: 0x14
} __vt__4Line; // size: 0x14, address: 0x80904918
struct {
    // total size: 0x8
} __RTTI__4Line; // size: 0x8, address: 0x80904940
struct {
    // total size: 0x8
} __RTTI__8Drawable; // size: 0x8, address: 0x80904958
struct {
    // total size: 0x8
} __RTTI__PP8Drawable; // size: 0x8, address: 0x80904970
// Range: 0x80520E0C -> 0x80520EEC
static void __sinit_\Graph_cpp() {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> static class ObjPtr sCam;
    // -> static class list sFakes;
    // -> static class list sGraphs;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndGraph * _M_data; // offset 0x8, size 0x4
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
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct FakeGraph _M_data; // offset 0x8, size 0x8
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

