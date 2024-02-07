/*
    Compile unit: C:\rockband2\system\src\synth\Faders.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8056E6AC -> 0x80570D30
*/
class DataArray * types; // size: 0x4, address: 0x80A541F0
// Range: 0x8056E6AC -> 0x8056E73C
void * Fader::Fader(class Fader * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__5Fader;
}

// Range: 0x8056E73C -> 0x8056E7E4
void * Fader::~Fader(class Fader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__5Fader;
}

// Range: 0x8056E7E4 -> 0x8056E828
void Fader::SetVal(class Fader * const this /* r31 */, float valDb /* f31 */) {}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std23_List_node<P9FaderTask>; // size: 0x8, address: 0x8091B690
// Range: 0x8056E828 -> 0x8056E83C
unsigned char Fader::IsFading() {}

// Range: 0x8056E83C -> 0x8056E870
void Fader::AddClient(class Fader * const this /* r5 */, class FaderGroup * fg /* r1+0x8 */) {}

// Range: 0x8056E870 -> 0x8056E934
void Fader::RemoveClient(class Fader * const this /* r31 */) {}

// Range: 0x8056E934 -> 0x8056E954
void Fader::CancelFade() {}

// Range: 0x8056E954 -> 0x8056E9E4
void Fader::UpdateValue() {}

// Range: 0x8056E9E4 -> 0x8056EA54
void Fader::Copy(class Fader * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class Fader * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
}

static class Symbol _s; // size: 0x4, address: 0x80A541F8
// Range: 0x8056EA54 -> 0x8056EBE4
unsigned char Fader::SyncProperty(class Fader * const this /* r31 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r30 */, enum PropOp _op /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A54200
static class Symbol _s; // size: 0x4, address: 0x80A54208
// Range: 0x8056EBE4 -> 0x8056F09C
class DataNode Fader::Handle(class Fader * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8056F09C -> 0x8056F0C8
void * FaderGroup::FaderGroup() {
    // References
    // -> struct [anonymous] __vt__29ObjPtrList<5Fader,9ObjectDir>;
}

// Range: 0x8056F0C8 -> 0x8056F434
void * FaderGroup::~FaderGroup(class FaderGroup * const this /* r28 */) {
    // References
    // -> struct [anonymous] __vt__29ObjPtrList<5Fader,9ObjectDir>;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056F434 -> 0x8056F6AC
class Fader * FaderGroup::AddLocal(class FaderGroup * const this /* r30 */, class Symbol & name /* r29 */) {
    // Local variables
    class iterator itr; // r1+0x30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x8056F6AC -> 0x8056F83C
void FaderGroup::Add(class FaderGroup * const this /* r31 */, class Fader * fader /* r29 */) {
    // Local variables
    class iterator itr; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056F83C -> 0x8056F9B0
void FaderGroup::Remove(class FaderGroup * const this /* r31 */) {
    // Local variables
    class iterator itr; // r1+0x1C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056F9B0 -> 0x8056FA04
float FaderGroup::GetVal() {
    // Local variables
    float ret; // f1
    class iterator itr; // r1+0x18
}

// Range: 0x8056FA04 -> 0x8056FA0C
unsigned char FaderGroup::Dirty() {}

// Range: 0x8056FA0C -> 0x8056FA18
void FaderGroup::SetDirty() {}

// Range: 0x8056FA18 -> 0x8056FA24
void FaderGroup::ClearDirty() {}

// Range: 0x8056FA24 -> 0x8056FAD8
class Fader * FaderGroup::FindLocal() {
    // Local variables
    class iterator itr; // r1+0x24

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x8056FAD8 -> 0x8056FC48
void FaderGroup::Print(class FaderGroup * const this /* r29 */, class TextStream & ts /* r31 */) {
    // Local variables
    class iterator itr; // r1+0x20
    class String nm; // r1+0x24
}

// Range: 0x8056FC48 -> 0x8056FF04
void FaderGroup::Load(class FaderGroup * const this /* r31 */, class BinStream & s /* r30 */) {
    // Local variables
    int rev; // r1+0x38
    class ObjPtrList l; // r1+0x3C
    class iterator itr; // r1+0x34

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__29ObjPtrList<5Fader,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056FF04 -> 0x8057045C
unsigned char PropSync(class FaderGroup & g /* r24 */, class DataNode & n /* r25 */, class DataArray * prop /* r26 */, int i /* r27 */, enum PropOp op /* r28 */) {
    // Local variables
    class ObjPtrList l; // r1+0x68
    class iterator itr; // r1+0x64
    unsigned char ret; // r29
    class iterator itr; // r1+0x60

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__29ObjPtrList<5Fader,9ObjectDir>;
}

// Range: 0x8057045C -> 0x80570AE8
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class Fader * obj; // r31
    class Fader * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class list : public _List_base {
    // total size: 0x8
};
class list sTasks; // size: 0x8, address: 0x80983400
struct FaderTask {
    // total size: 0x60
    class Timer mTimer; // offset 0x0, size 0x38
    class LinearInterpolator mInterp; // offset 0x38, size 0x1C
    class Fader * mFader; // offset 0x54, size 0x4
    unsigned char mDone; // offset 0x58, size 0x1
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80570AE8 -> 0x80570B9C
void FaderTask::PollAll() {
    // Local variables
    struct _List_iterator itr; // r1+0x1C

    // References
    // -> class list sTasks;
}

// Range: 0x80570B9C -> 0x80570CD4
void FaderTask::Poll(struct FaderTask * const this /* r30 */) {
    // Local variables
    float t; // f0

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x18
} __vt__29ObjPtrList<5Fader,9ObjectDir>; // size: 0x18, address: 0x8091B7C0
struct {
    // total size: 0x8
} __RTTI__29ObjPtrList<5Fader,9ObjectDir>; // size: 0x8, address: 0x8091B808
struct {
    // total size: 0x54
} __vt__5Fader; // size: 0x54, address: 0x8091B810
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
} __RTTI__PQ211stlpmtx_std28_Rb_tree_node<P10FaderGroup>; // size: 0x8, address: 0x8091B900
// Range: 0x80570CD4 -> 0x80570D30
static void __sinit_\Faders_cpp() {
    // References
    // -> class list sTasks;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    struct FaderTask * _M_data; // offset 0x8, size 0x4
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

