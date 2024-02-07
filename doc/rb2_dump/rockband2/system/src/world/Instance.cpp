/*
    Compile unit: C:\rockband2\system\src\world\Instance.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804633F8 -> 0x80465FE0
*/
class DataArray * types; // size: 0x4, address: 0x80A52828
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<P11SharedGroup>; // size: 0x8, address: 0x808F02D8
class list : public _List_base {
    // total size: 0x8
};
class list sGroups; // size: 0x8, address: 0x8097F0F8
// Range: 0x804633F8 -> 0x8046351C
void * WorldInstance::WorldInstance(class WorldInstance * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18ObjDirPtr<6RndDir>;
    // -> struct [anonymous] __vt__13WorldInstance;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8046351C -> 0x80463AA8
void * WorldInstance::~WorldInstance(class WorldInstance * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__18ObjDirPtr<6RndDir>;
}

// Range: 0x80463AA8 -> 0x80463B90
void WorldInstance::DrawShowing(class WorldInstance * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80463B90 -> 0x80463CD4
class RndDrawable * WorldInstance::CollideShowing(class WorldInstance * const this /* r26 */, const class Segment & s /* r27 */, float & dist /* r28 */, class Plane & p /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80463CD4 -> 0x80463E90
unsigned char WorldInstance::MakeWorldSphere(class WorldInstance * const this /* r31 */, class Sphere & s /* r29 */) {
    // Local variables
    class Sphere s2; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80463E90 -> 0x80463ED4
void WorldInstance::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80463ED4 -> 0x80463EEC
void WorldInstance::PreSave() {}

// Range: 0x80463EEC -> 0x80463EF0
void WorldInstance::PostSave() {}

// Range: 0x80463EF0 -> 0x80463EF4
void WorldInstance::Copy() {}

// Range: 0x80463EF4 -> 0x80463F50
void WorldInstance::Load(class WorldInstance * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x80463F50 -> 0x80463FE0
void WorldInstance::PreLoad(class WorldInstance * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80463FE0 -> 0x8046416C
void WorldInstance::PostLoad(class WorldInstance * const this /* r26 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8046416C -> 0x80464638
void WorldInstance::SetProxyFile(class WorldInstance * const this /* r30 */, const class FilePath & file /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol Group; // size: 0x4, address: 0x80A52830
static class Symbol Tex; // size: 0x4, address: 0x80A52838
static class Symbol CubeTex; // size: 0x4, address: 0x80A52840
static class Symbol Movie; // size: 0x4, address: 0x80A52848
static class Symbol SynthSample; // size: 0x4, address: 0x80A52850
class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80464638 -> 0x804654E0
void WorldInstance::SyncDir(class WorldInstance * const this /* r27 */) {
    // Local variables
    class list pairs; // r1+0x128
    class ObjDirItr i; // r1+0x130
    class EventTrigger * e; // r0
    class Object * o; // r24
    struct _List_iterator p; // r1+0xEC
    class list refs; // r1+0x120
    struct _List_iterator r; // r1+0xE8

    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6ObjRef>;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<7ObjPair>;
    // -> static class Symbol SynthSample;
    // -> static class Symbol Movie;
    // -> static class Symbol CubeTex;
    // -> static class Symbol Tex;
    // -> static class Symbol Group;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9MsgSource;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>;
    // -> struct [anonymous] __RTTI__11RndPollable;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11SharedGroup>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__11SharedGroup;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> class list sGroups;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndGroup * mPtr; // offset 0x8, size 0x4
};
class SharedGroup : public RndPollable {
    // total size: 0x4C
    class ObjOwnerPtr mGroup; // offset 0x8, size 0xC
    class list mPolls; // offset 0x14, size 0x8
    class ObjectDir * mDir; // offset 0x1C, size 0x4
};
// Range: 0x804654E0 -> 0x80465748
void SharedGroup::AddPolls(class SharedGroup * const this /* r31 */) {
    // Local variables
    class iterator i; // r1+0x4C
    class RndPollable * p; // r0
    class RndGroup * cg; // r0

    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPollable;
}

struct ObjPair {
    // total size: 0x8
    class Object * from; // offset 0x0, size 0x4
    class Object * to; // offset 0x4, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct ObjPair _M_data; // offset 0x8, size 0x8
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
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std20_List_node<7ObjPair>; // size: 0x8, address: 0x808F03C0
static class Symbol _s; // size: 0x4, address: 0x80A52858
// Range: 0x80465748 -> 0x80465D30
unsigned char WorldInstance::SyncProperty(class WorldInstance * const this /* r30 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r26 */, int _i /* r25 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class FilePath sNull;
    // -> static class Symbol _s;
}

// Range: 0x80465D30 -> 0x80465DFC
void * SharedGroup::~SharedGroup(class SharedGroup * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8RndGroup,9ObjectDir>;
}

// Range: 0x80465DFC -> 0x80465F14
void SharedGroup::Replace(class SharedGroup * const this /* r31 */) {
    // References
    // -> class list sGroups;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80465F14 -> 0x80465F84
void SharedGroup::Poll(class SharedGroup * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

struct {
    // total size: 0x80
} __vt__11SharedGroup; // size: 0x80, address: 0x808F0420
struct {
    // total size: 0x8
} __RTTI__11SharedGroup; // size: 0x8, address: 0x808F04C8
struct {
    // total size: 0x18
} __vt__33ObjOwnerPtr<8RndGroup,9ObjectDir>; // size: 0x18, address: 0x808F04D0
struct {
    // total size: 0x8
} __RTTI__33ObjOwnerPtr<8RndGroup,9ObjectDir>; // size: 0x8, address: 0x808F0518
struct {
    // total size: 0x21C
} __vt__13WorldInstance; // size: 0x21C, address: 0x808F0550
struct {
    // total size: 0x8
} __RTTI__13WorldInstance; // size: 0x8, address: 0x808F07D0
// Range: 0x80465F84 -> 0x80465FE0
static void __sinit_\Instance_cpp() {
    // References
    // -> class list sGroups;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class SharedGroup * _M_data; // offset 0x8, size 0x4
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

