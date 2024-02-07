/*
    Compile unit: C:\rockband2\system\src\obj\DataArray.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CFD00 -> 0x805D26BC
*/
static int gIndent; // size: 0x4, address: 0x80A54E28
static class Symbol gFile; // size: 0x4, address: 0x80A54E2C
class list : public _List_base {
    // total size: 0x8
};
static class list gConditional; // size: 0x8, address: 0x80988CB8
class DataNode (* sDefaultHandler)(class DataArray *); // size: 0x4, address: 0x80A54E30
class DataNode (* gPreExecuteFunc)(class DataArray *); // size: 0x4, address: 0x80A54E34
int gPreExecuteLevel; // size: 0x4, address: 0x80A54E38
class DataArray * gCallStack[100]; // size: 0x190, address: 0x80988CC0
class DataArray * * gCallStackPtr; // size: 0x4, address: 0x80A478F8
class DataNode * (* gNodeAllocFunc)(int); // size: 0x4, address: 0x80A478FC
void (* gNodeFreeFunc)(int, class DataNode *); // size: 0x4, address: 0x80A47900
// Range: 0x805CFD00 -> 0x805CFD7C
unsigned char strncat_tofit(char * dest /* r27 */, int & dest_len /* r28 */, const char * src /* r29 */, int max_size /* r30 */) {
    // Local variables
    int src_len; // r0
}

// Range: 0x805CFD7C -> 0x805CFFA0
void DataAppendStackTrace(char * msg /* r28 */) {
    // Local variables
    unsigned char msg_full; // r31
    int msg_len; // r1+0x8
    class DataArray * * ptr; // r30
    class DataArray * a; // r29
    class String s; // r1+0x1C
    char visualStudioFmt[14]; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> class DataArray * gCallStack[100];
    // -> class DataArray * * gCallStackPtr;
}

// Range: 0x805CFFA0 -> 0x805D002C
class DataNode & DataArray::Node(const class DataArray * const this /* r30 */, int i /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D002C -> 0x805D00B8
class DataNode & DataArray::Node(class DataArray * const this /* r30 */, int i /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D00B8 -> 0x805D029C
void DataArray::Print(const class DataArray * const this /* r30 */, class TextStream & s /* r31 */, enum DataType type /* r24 */, unsigned char compact /* r25 */) {
    // Local variables
    class DataNode * i; // r29
    class DataNode * end; // r28
    char open; // r27
    char close; // r26

    // References
    // -> static int gIndent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D029C -> 0x805D030C
static class DataNode * NodesAlloc(int bytes /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class DataNode * (* gNodeAllocFunc)(int);
}

// Range: 0x805D030C -> 0x805D038C
static void NodesFree(int bytes /* r30 */, class DataNode * mem /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> void (* gNodeFreeFunc)(int, class DataNode *);
}

// Range: 0x805D038C -> 0x805D0398
static class DataNode * NodesAllocDefault() {}

// Range: 0x805D0398 -> 0x805D039C
static void NodesFreeDefault() {}

// Range: 0x805D039C -> 0x805D04D8
void DataArray::Insert(class DataArray * const this /* r28 */, int index /* r26 */, const class DataNode & node /* r27 */) {
    // Local variables
    int i; // r31
    int size; // r30
    class DataNode * old; // r29
}

// Range: 0x805D04D8 -> 0x805D063C
void DataArray::InsertNodes(class DataArray * const this /* r28 */, int index /* r24 */, const class DataArray * array /* r25 */) {
    // Local variables
    int i; // r31
    int arraySize; // r0
    int size; // r30
    class DataNode * old; // r29
}

// Range: 0x805D063C -> 0x805D0788
void DataArray::Resize(class DataArray * const this /* r29 */, int size /* r1+0x8 */) {
    // Local variables
    class DataNode * old; // r31
    int min; // r28
    int i; // r30
}

// Range: 0x805D0788 -> 0x805D08CC
void DataArray::Remove(class DataArray * const this /* r29 */, int index /* r27 */) {
    // Local variables
    class DataNode * old; // r31
    int size; // r30
    int i; // r28
    int i; // [invalid]
    int i; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805D08CC -> 0x805D0904
void DataArray::Remove() {
    // Local variables
    int value; // r6
    int i; // r4
}

// Range: 0x805D0904 -> 0x805D0944
unsigned char DataArray::Contains() {
    // Local variables
    int value; // r5
    int i; // r6
}

// Range: 0x805D0944 -> 0x805D0A00
class DataArray * DataArray::FindArray(const class DataArray * const this /* r26 */, int tag /* r27 */, unsigned char fail /* r28 */) {
    // Local variables
    class DataNode * i; // r31
    class DataNode * end; // r30
    class DataArray * a; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D0A00 -> 0x805D0A94
class DataArray * DataArray::FindArray(const class DataArray * const this /* r28 */, class Symbol & tag /* r29 */, unsigned char fail /* r30 */) {
    // Local variables
    class DataArray * r; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D0A94 -> 0x805D0AD8
class DataArray * DataArray::FindArray() {}

// Range: 0x805D0AD8 -> 0x805D0B30
class DataArray * DataArray::FindArray() {}

// Range: 0x805D0B30 -> 0x805D0B9C
class DataArray * DataArray::FindArray() {}

// Range: 0x805D0B9C -> 0x805D0BFC
class DataArray * DataArray::FindArray(const class DataArray * const this /* r30 */, class Symbol & s1 /* r31 */) {}

// Range: 0x805D0BFC -> 0x805D0C6C
unsigned char DataArray::FindData(const char * & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0C6C -> 0x805D0CE4
unsigned char DataArray::FindData(class Symbol & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0CE4 -> 0x805D0D40
unsigned char DataArray::FindData(class String & ret /* r31 */) {
    // Local variables
    const char * str; // r1+0xC
}

// Range: 0x805D0D40 -> 0x805D0DB0
unsigned char DataArray::FindData(int & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0DB0 -> 0x805D0E20
unsigned char DataArray::FindData(float & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0E20 -> 0x805D0E9C
unsigned char DataArray::FindData(unsigned char & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0E9C -> 0x805D0F24
unsigned char DataArray::FindData(class Vector2 & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0F24 -> 0x805D0FC4
unsigned char DataArray::FindData(class Vector3 & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D0FC4 -> 0x805D107C
unsigned char DataArray::FindData(class Plane & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D107C -> 0x805D114C
unsigned char DataArray::FindData(class Color & ret /* r30 */) {
    // Local variables
    class DataArray * array; // r31
}

// Range: 0x805D114C -> 0x805D12B0
class DataArray * DataArray::Clone(class DataArray * const this /* r27 */, unsigned char deep /* r28 */, unsigned char eval /* r29 */) {
    // Local variables
    class DataArray * array; // r0
    int i; // r30
    class DataArray * a; // r25
}

// Range: 0x805D12B0 -> 0x805D1344
void * DataArray::DataArray(class DataArray * const this /* r30 */, int size /* r31 */) {
    // Local variables
    int i; // r4

    // References
    // -> const char * gNullStr;
}

// Range: 0x805D1344 -> 0x805D13C4
void * DataArray::DataArray(class DataArray * const this /* r29 */, void * glob /* r30 */, int size /* r31 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x805D13C4 -> 0x805D14A0
void * DataArray::~DataArray(class DataArray * const this /* r29 */) {
    // Local variables
    int i; // r31
}

// Range: 0x805D14A0 -> 0x805D14B0
void DataArray::SetFileLine() {}

// Range: 0x805D14B0 -> 0x805D1640
static int NodeCmp() {
    // Local variables
    const class DataNode * anode; // r30
    const class DataNode * bnode; // r29
    float a; // f0
    float b; // f0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805D1640 -> 0x805D1664
void DataArray::SortNodes() {}

static class Timer * _t; // size: 0x4, address: 0x80A54E3C
struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    class DataNode (* second)(class DataArray *); // offset 0x4, size 0x4
};
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x805D1664 -> 0x805D1DDC
class DataNode DataArray::Execute(class DataArray * const this /* r28 */) {
    // Local variables
    class AutoTimer _at; // r1+0x24
    class Object * object; // r4
    struct _Rb_tree_iterator func; // r1+0x20
    class Object * object; // r4
    class DataNode n; // r1+0x38
    class String s; // r1+0x4C
    class String sn; // r1+0x40

    // References
    // -> class DataNode (* sDefaultHandler)(class DataArray *);
    // -> class map gDataFuncs;
    // -> class ObjectDir * gDataDir;
    // -> static class Timer * _t;
    // -> int gPreExecuteLevel;
    // -> class DataNode (* gPreExecuteFunc)(class DataArray *);
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class DataArray * * gCallStackPtr;
    // -> class DataArray * gCallStack[100];
}

// Range: 0x805D1DDC -> 0x805D1E8C
void DataArray::Save(const class DataArray * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int i; // r31
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805D1E8C -> 0x805D1EEC
static unsigned char Defined() {
    // Local variables
    struct _List_iterator i; // r1+0x10

    // References
    // -> static class list gConditional;
}

// Range: 0x805D1EEC -> 0x805D24A8
void DataArray::Load(class DataArray * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    signed short size; // r1+0xC
    int i; // r31
    class DataNode & n; // r26
    class DataArray * array; // r30
    int j; // r26
    class DataNode array; // r1+0x50
    class DataNode array; // r1+0x48
    const char * path; // r27
    int j; // r26
    int left; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<b>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list gConditional;
    // -> static class Symbol gFile;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std13_List_node<b>; // size: 0x8, address: 0x809273E8
// Range: 0x805D24A8 -> 0x805D2548
void DataArray::SaveGlob(const class DataArray * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    unsigned int size; // r31
}

// Range: 0x805D2548 -> 0x805D2554
void DataArray::SetFile() {
    // References
    // -> static class Symbol gFile;
}

// Range: 0x805D2554 -> 0x805D25E0
class BinStream & __rs(class BinStream & s /* r30 */, class DataArray * & n /* r31 */) {}

// Range: 0x805D25E0 -> 0x805D2658
class BinStream & __ls(class BinStream & s /* r30 */, const class DataArray * n /* r31 */) {}

// Range: 0x805D2658 -> 0x805D26BC
static void __sinit_\DataArray_cpp() {
    // References
    // -> static class list gConditional;
    // -> static class Symbol gFile;
    // -> const char * gNullStr;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    unsigned char _M_data; // offset 0x8, size 0x1
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
class StlNodeAlloc {
    // total size: 0x1
};
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
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};

