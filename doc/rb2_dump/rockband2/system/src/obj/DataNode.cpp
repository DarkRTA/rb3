/*
    Compile unit: C:\rockband2\system\src\obj\DataNode.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805DD140 -> 0x805DF108
*/
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
static class map gDataVars; // size: 0x18, address: 0x80988ED0
// Range: 0x805DD140 -> 0x805DD298
class DataNode & DataVariable() {
    // References
    // -> static class map gDataVars;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x805DD298 -> 0x805DD320
char * DataVarName(const class DataNode * var /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator i; // r1+0x14

    // References
    // -> static class map gDataVars;
}

// Range: 0x805DD320 -> 0x805DD3A4
unsigned char DataNode::CompatibleType() {}

static class DataNode gEvalNode[8]; // size: 0x40, address: 0x80988EF8
static int gEvalIndex; // size: 0x4, address: 0x80A54E78
// Range: 0x805DD3A4 -> 0x805DD4F8
class DataNode & DataNode::Evaluate(const class DataNode * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Object * gDataThis;
    // -> static class DataNode gEvalNode[8];
    // -> static int gEvalIndex;
}

// Range: 0x805DD4F8 -> 0x805DD5D8
int DataNode::Int(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DD5D8 -> 0x805DD6B4
int DataNode::LiteralInt(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DD6B4 -> 0x805DD794
class Symbol DataNode::Sym(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DD794 -> 0x805DD870
class Symbol DataNode::LiteralSym(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DD870 -> 0x805DD970
class Symbol DataNode::ForceSym(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x18

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DD970 -> 0x805DDA64
char * DataNode::Str(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DDA64 -> 0x805DDB54
char * DataNode::LiteralStr(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DDB54 -> 0x805DDC5C
void * DataNode::Glob(int * size /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DDC5C -> 0x805DDD6C
float DataNode::Float(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DDD6C -> 0x805DDE78
float DataNode::LiteralFloat(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DDE78 -> 0x805DDF54
class DataNode (* DataNode::Func(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */))(class DataArray *) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DDF54 -> 0x805DE034
class Object * DataNode::GetObj(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r0
    const char * name; // r31
    class Object * o; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * gDataDir;
}

// Range: 0x805DE034 -> 0x805DE114
class DataArray * DataNode::Array(const class DataArray * a /* r30 */) {
    // Local variables
    const class DataNode & n; // r31
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DE114 -> 0x805DE1F0
class DataArray * DataNode::LiteralArray(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DE1F0 -> 0x805DE2CC
class DataArray * DataNode::Command(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DE2CC -> 0x805DE3A8
class DataNode * DataNode::Var(const class DataNode * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class String s; // r1+0x14

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805DE3A8 -> 0x805DE3D0
void * DataNode::DataNode() {}

// Range: 0x805DE3D0 -> 0x805DE45C
void * DataNode::DataNode(class DataNode * const this /* r29 */, const char * string /* r30 */) {}

// Range: 0x805DE45C -> 0x805DE4EC
void * DataNode::DataNode(class DataNode * const this /* r29 */, const class String & string /* r30 */) {}

// Range: 0x805DE4EC -> 0x805DE564
void * DataNode::DataNode(class DataNode * const this /* r29 */, void * glob /* r30 */, int size /* r31 */) {}

// Range: 0x805DE564 -> 0x805DE584
void * DataNode::DataNode() {}

// Range: 0x805DE584 -> 0x805DE644
void * DataNode::DataNode(class DataNode * const this /* r28 */, class DataArray * array /* r29 */, enum DataType type /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805DE644 -> 0x805DE7D8
unsigned char DataNode::__eq(const class DataNode * const this /* r29 */, const class DataNode & n /* r30 */) {
    // Local variables
    const char * a; // r31
    const char * b; // r4
}

// Range: 0x805DE7D8 -> 0x805DE800
unsigned char DataNode::__ne() {}

// Range: 0x805DE800 -> 0x805DE8A4
unsigned char DataNode::NotNull() {
    // Local variables
    const class DataNode & n; // r0
    enum DataType t; // r0
}

// Range: 0x805DE8A4 -> 0x805DE938
class DataNode & DataNode::__as(class DataNode * const this /* r30 */, const class DataNode & n /* r31 */) {}

// Range: 0x805DE938 -> 0x805DEC2C
void DataNode::Print(const class DataNode * const this /* r31 */, class TextStream & s /* r30 */) {
    // Local variables
    char * str; // r31
}

// Range: 0x805DEC2C -> 0x805DED94
void DataNode::Save(const class DataNode * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

static char buf[128]; // size: 0x80, address: 0x80988F38
// Range: 0x805DED94 -> 0x805DF04C
void DataNode::Load(class DataNode * const this /* r30 */, class BinStream & d /* r29 */) {
    // Local variables
    class Symbol sym; // r1+0x24
    struct _Rb_tree_iterator func; // r1+0x20
    class Symbol sym; // r1+0x1C
    class Symbol name; // r1+0x18

    // References
    // -> class ObjectDir * gDataDir;
    // -> static char buf[128];
    // -> class Debug TheDebug;
    // -> class map gDataFuncs;
    // -> const char * gNullStr;
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std56_Rb_tree_node<Q211stlpmtx_std24pair<C6Symbol,8DataNode>>; // size: 0x8, address: 0x809286E0
// Range: 0x805DF04C -> 0x805DF108
static void __sinit_\DataNode_cpp() {
    // References
    // -> static class DataNode gEvalNode[8];
    // -> static class map gDataVars;
}

struct pair {
    // total size: 0xC
    class Symbol first; // offset 0x0, size 0x4
    class DataNode second; // offset 0x4, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};

