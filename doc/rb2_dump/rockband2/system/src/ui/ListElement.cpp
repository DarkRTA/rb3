/*
    Compile unit: C:\rockband2\system\src\ui\ListElement.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803D560C -> 0x803D6D9C
*/
static class Symbol object; // size: 0x4, address: 0x80A51B74
static class Symbol highlight_only; // size: 0x4, address: 0x80A51B7C
static class Symbol text; // size: 0x4, address: 0x80A51B84
static class Symbol mesh; // size: 0x4, address: 0x80A51B8C
static class Symbol list; // size: 0x4, address: 0x80A51B94
static class Symbol custom; // size: 0x4, address: 0x80A51B9C
// Range: 0x803D560C -> 0x803D5F34
void * ListElement::ListElement(class ListElement * const this /* r24 */, class UIList * parent /* r25 */, class ObjectDir * resourceDir /* r26 */, class DataArray * slots /* r27 */) {
    // Local variables
    int i; // r28
    class Symbol name; // r1+0x60
    class DataArray * o; // r22
    class Symbol type; // r1+0x5C
    unsigned char ho; // r1+0xC
    class ListSlot * slot; // r1+0x58

    // References
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __vt__14CustomListSlot;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> struct [anonymous] __vt__11SubListSlot;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__8MeshSlot;
    // -> const char * gNullStr;
    // -> const char * kNotObjectMsg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__8TextSlot;
    // -> struct [anonymous] __vt__8ListSlot;
    // -> static class Symbol custom;
    // -> static class Symbol list;
    // -> static class Symbol mesh;
    // -> static class Symbol text;
    // -> static class Symbol highlight_only;
    // -> static class Symbol object;
    // -> struct [anonymous] __vt__11ListElement;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class ListSlot {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned char mHighlightOnly; // offset 0x4, size 0x1
    class Symbol mName; // offset 0x8, size 0x4
};
// Range: 0x803D5F34 -> 0x803D5F74
void * ListSlot::~ListSlot(class ListSlot * const this /* r31 */) {}

// Range: 0x803D5F74 -> 0x803D6118
void * ListElement::~ListElement(class ListElement * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11ListElement;
}

class list : public _List_base {
    // total size: 0x8
};
// Range: 0x803D6118 -> 0x803D61D4
unsigned char ListElement::Collide(class ListElement * const this /* r27 */, const class Segment & s /* r28 */, float & dist /* r29 */, class Plane & plane /* r30 */) {
    // Local variables
    class list colls; // r1+0x18
    class ListSlot * * it; // r31
}

struct Collision {
    // total size: 0x20
    class RndDrawable * object; // offset 0x0, size 0x4
    float distance; // offset 0x4, size 0x4
    class Plane plane; // offset 0x10, size 0x10
};
class _List_node : public _List_node_base {
    // total size: 0x30
public:
    struct Collision _M_data; // offset 0x10, size 0x20
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
// Range: 0x803D61D4 -> 0x803D62A0
int ListElement::CollidePlane(class ListElement * const this /* r28 */, const class Plane & plane /* r29 */) {
    // Local variables
    class list colls; // r1+0x18
    class ListSlot * * it; // r31
    int collide; // r30
}

// Range: 0x803D62A0 -> 0x803D6348
void ListElement::BoundingBox(class ListElement * const this /* r29 */, class Box & b /* r30 */) {
    // Local variables
    class Box slotBox; // r1+0x10
    class ListSlot * * it; // r31
}

// Range: 0x803D6348 -> 0x803D63C4
class UIList * ListElement::ChildList(class ListElement * const this /* r30 */) {
    // Local variables
    class ListSlot * * it; // r31
    class SubListSlot * sls; // r0

    // References
    // -> struct [anonymous] __RTTI__8ListSlot;
    // -> struct [anonymous] __RTTI__11SubListSlot;
}

// Range: 0x803D63C4 -> 0x803D644C
void ListElement::Fill(class ListElement * const this /* r27 */, const class ListProvider & provider /* r28 */, int showing /* r29 */, int data /* r30 */) {
    // Local variables
    class ListSlot * * it; // r31
}

static class Symbol highlight; // size: 0x4, address: 0x80A51BA4
// Range: 0x803D644C -> 0x803D661C
void ListElement::Draw(class ListElement * const this /* r25 */, const class ListProvider & provider /* r26 */, int showing /* r27 */, int data /* r28 */, class Symbol & compState /* r29 */, class Symbol & eleState /* r30 */, class DataArray * colors /* r31 */) {
    // Local variables
    class ListSlot * * it; // r23
    class ListSlot * s; // r22
    class RndMat * mat; // r0
    float old_alpha; // f31
    class Color old_color; // r1+0x30
    class Color c; // r1+0x20

    // References
    // -> static class Symbol highlight;
}

// Range: 0x803D661C -> 0x803D6624
unsigned char ListSlot::HightlightOnly() {}

// Range: 0x803D6624 -> 0x803D662C
void ListElement::SetFade() {}

// Range: 0x803D662C -> 0x803D6688
void ListElement::Poll(class ListElement * const this /* r30 */) {
    // Local variables
    class ListSlot * * s; // r31
}

// Range: 0x803D6688 -> 0x803D668C
void ListSlot::Poll() {}

class CustomListSlot : public ListSlot {
    // total size: 0x10
    class Object * mCustom; // offset 0xC, size 0x4
};
// Range: 0x803D668C -> 0x803D66D8
void CustomListSlot::Fill(class CustomListSlot * const this /* r8 */) {}

// Range: 0x803D66D8 -> 0x803D673C
void CustomListSlot::SetColorAlpha(float alpha /* f31 */) {
    // Local variables
    class ListAlphable * a; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12ListAlphable;
}

// Range: 0x803D673C -> 0x803D6740
void CustomListSlot::BoundingBox() {}

// Range: 0x803D6740 -> 0x803D6748
class RndMat * CustomListSlot::Mat() {}

// Range: 0x803D6748 -> 0x803D6768
class RndDrawable * CustomListSlot::Drawable() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

// Range: 0x803D6768 -> 0x803D6788
class RndTransformable * CustomListSlot::Trans() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x803D6788 -> 0x803D6808
void * CustomListSlot::~CustomListSlot(class CustomListSlot * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__14CustomListSlot;
}

struct {
    // total size: 0x2C
} __vt__14CustomListSlot; // size: 0x2C, address: 0x808E3604
struct {
    // total size: 0x8
} __RTTI__14CustomListSlot; // size: 0x8, address: 0x808E3650
class SubListSlot : public ListSlot {
    // total size: 0x10
    class UIList * mList; // offset 0xC, size 0x4
};
// Range: 0x803D6808 -> 0x803D681C
void SubListSlot::Poll() {}

// Range: 0x803D681C -> 0x803D6820
void SubListSlot::SetColorAlpha() {}

// Range: 0x803D6820 -> 0x803D695C
void SubListSlot::Fill(class SubListSlot * const this /* r26 */, const class ListProvider & p /* r27 */, int showing /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    const class ListProvider * old_provider; // r0
    class Symbol old_selected; // r1+0x14
    class ListProvider * sub_provider; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
    // -> const char * gNullStr;
}

// Range: 0x803D695C -> 0x803D6964
void SubListSlot::BoundingBox() {}

// Range: 0x803D6964 -> 0x803D696C
class RndMat * SubListSlot::Mat() {}

// Range: 0x803D696C -> 0x803D6974
class RndDrawable * SubListSlot::Drawable() {}

// Range: 0x803D6974 -> 0x803D6988
class RndTransformable * SubListSlot::Trans() {}

// Range: 0x803D6988 -> 0x803D6A08
void * SubListSlot::~SubListSlot(class SubListSlot * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11SubListSlot;
}

struct {
    // total size: 0x2C
} __vt__11SubListSlot; // size: 0x2C, address: 0x808E3658
struct {
    // total size: 0x8
} __RTTI__11SubListSlot; // size: 0x8, address: 0x808E36A0
class MeshSlot : public ListSlot {
    // total size: 0x10
    class RndMesh * mMesh; // offset 0xC, size 0x4
};
// Range: 0x803D6A08 -> 0x803D6A84
void MeshSlot::Fill(class MeshSlot * const this /* r30 */) {
    // Local variables
    class RndMat * mat; // r31
}

// Range: 0x803D6A84 -> 0x803D6B00
void MeshSlot::SetColorAlpha(const class Color & c /* r31 */, float alpha /* f31 */) {
    // Local variables
    class RndMat * mat; // r0
}

// Range: 0x803D6B00 -> 0x803D6B0C
class RndMat * MeshSlot::Mat() {}

// Range: 0x803D6B0C -> 0x803D6B14
void MeshSlot::BoundingBox() {}

// Range: 0x803D6B14 -> 0x803D6B1C
class RndDrawable * MeshSlot::Drawable() {}

// Range: 0x803D6B1C -> 0x803D6B30
class RndTransformable * MeshSlot::Trans() {}

// Range: 0x803D6B30 -> 0x803D6BB0
void * MeshSlot::~MeshSlot(class MeshSlot * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8MeshSlot;
}

struct {
    // total size: 0x2C
} __vt__8MeshSlot; // size: 0x2C, address: 0x808E36A8
struct {
    // total size: 0x8
} __RTTI__8MeshSlot; // size: 0x8, address: 0x808E36F0
class TextSlot : public ListSlot {
    // total size: 0x10
    class UILabel * mLabel; // offset 0xC, size 0x4
};
// Range: 0x803D6BB0 -> 0x803D6C0C
void TextSlot::Fill(class TextSlot * const this /* r31 */) {}

// Range: 0x803D6C0C -> 0x803D6C98
void TextSlot::SetColorAlpha(class TextSlot * const this /* r30 */, const class Color & c /* r31 */, float alpha /* f31 */) {
    // Local variables
    class RndMat * mat; // r0
}

// Range: 0x803D6C98 -> 0x803D6CC4
class RndMat * TextSlot::Mat() {}

// Range: 0x803D6CC4 -> 0x803D6D00
void TextSlot::BoundingBox(class Box & b /* r31 */) {}

// Range: 0x803D6D00 -> 0x803D6D08
class RndDrawable * TextSlot::Drawable() {}

// Range: 0x803D6D08 -> 0x803D6D1C
class RndTransformable * TextSlot::Trans() {}

// Range: 0x803D6D1C -> 0x803D6D9C
void * TextSlot::~TextSlot(class TextSlot * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__8TextSlot;
}

struct {
    // total size: 0x2C
} __vt__8TextSlot; // size: 0x2C, address: 0x808E36F8
struct {
    // total size: 0x8
} __RTTI__8TextSlot; // size: 0x8, address: 0x808E3740
struct {
    // total size: 0x2C
} __vt__8ListSlot; // size: 0x2C, address: 0x808E3748
struct {
    // total size: 0x8
} __RTTI__8ListSlot; // size: 0x8, address: 0x808E3780
struct {
    // total size: 0x9C
} __vt__11ListElement; // size: 0x9C, address: 0x808E3948
struct {
    // total size: 0x8
} __RTTI__11ListElement; // size: 0x8, address: 0x808E3A18
struct {
    // total size: 0x8
} __RTTI__PP8ListSlot; // size: 0x8, address: 0x808E3B48

