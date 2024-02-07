/*
    Compile unit: C:\rockband2\system\src\world\LightPresetManager.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80441464 -> 0x80444AA0
*/
class _Slist_node : public _Slist_node_base {
    // total size: 0x14
public:
    struct pair _M_data; // offset 0x4, size 0x10
};
// Range: 0x80441464 -> 0x80441728
void * LightPresetManager::~LightPresetManager(class LightPresetManager * const this /* r30 */) {}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class LightPreset * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80441728 -> 0x80441CE4
void LightPresetManager::SyncObjects(class LightPresetManager * const this /* r29 */) {
    // Local variables
    class ObjDirItr i; // r1+0x88

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP11LightPreset;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11LightPreset;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP11LightPreset; // size: 0x8, address: 0x808ED9B8
// Range: 0x80441CE4 -> 0x80441E78
void LightPresetManager::Enter(class LightPresetManager * const this /* r31 */) {}

// Range: 0x80441E78 -> 0x8044207C
void LightPresetManager::Poll(class LightPresetManager * const this /* r30 */) {
    // Local variables
    class LightPreset * presetToStart; // r31
    float time; // f0
    float time; // f0
    float frame; // f29
    float fade; // f28
    float oldTime; // f0
    float oldFrame; // f31
    float blend; // f28

    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Message end; // size: 0x8, address: 0x8097EFF0
// Range: 0x8044207C -> 0x804423DC
void LightPresetManager::StartPreset(class LightPresetManager * const this /* r30 */, class LightPreset * preset /* r31 */, float delay /* f31 */) {
    // Local variables
    float scheduledTime; // f2

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message end;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804423DC -> 0x80442448
void LightPresetManager::ForcePreset(class LightPresetManager * const this /* r30 */, class LightPreset * preset /* r31 */) {}

// Range: 0x80442448 -> 0x80442468
class DataNode LightPresetManager::OnToggleLightingEvents() {}

// Range: 0x80442468 -> 0x804424D8
class DataNode LightPresetManager::OnIgnoreLightingEvents(class LightPresetManager * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x804424D8 -> 0x804425D8
class DataNode LightPresetManager::OnNextLighting(class LightPresetManager * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804425D8 -> 0x804426B4
void LightPresetManager::SelectPreset(class LightPresetManager * const this /* r31 */) {
    // Local variables
    float delay; // r1+0x8

    // References
    // -> class LoadMgr TheLoadMgr;
}

static class Message msg; // size: 0x8, address: 0x8097F008
// Range: 0x804426B4 -> 0x80442CCC
void LightPresetManager::SetCategoriesAndAdjectives(class LightPresetManager * const this /* r29 */, class DataArray * args /* r30 */) {
    // Local variables
    class DataNode adj; // r1+0xA8
    class DataArray * adjs; // r28
    unsigned int i; // r27
    class DataNode cat; // r1+0xA0
    class DataArray * cats; // r30
    unsigned int i; // r27
    char buf[256]; // r1+0xB0

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
}

// Range: 0x80442CCC -> 0x80442D84
class DataNode LightPresetManager::OnCycleLighting(class LightPresetManager * const this /* r30 */, class DataArray * args /* r31 */) {
    // Local variables
    unsigned char doDelay; // r4
}

// Range: 0x80442D84 -> 0x80442E38
class DataNode LightPresetManager::OnSetLighting(class LightPresetManager * const this /* r30 */, class DataArray * args /* r31 */) {
    // Local variables
    unsigned char doDelay; // r4
}

// Range: 0x80442E38 -> 0x80442EB8
class DataNode LightPresetManager::OnNextKeyframe(class LightPresetManager * const this /* r31 */) {}

// Range: 0x80442EB8 -> 0x80442F38
class DataNode LightPresetManager::OnPrevKeyframe(class LightPresetManager * const this /* r31 */) {}

// Range: 0x80442F38 -> 0x80442FB8
class DataNode LightPresetManager::OnFirstKeyframe(class LightPresetManager * const this /* r31 */) {}

// Range: 0x80442FB8 -> 0x8044308C
class DataNode LightPresetManager::OnExcitementChange(class LightPresetManager * const this /* r30 */, class DataArray * args /* r31 */) {}

// Range: 0x8044308C -> 0x80443214
static int CalculateScore(class LightPreset * preset /* r27 */, const class vector & categories /* r28 */, const class vector & adjs /* r29 */) {
    // Local variables
    int score; // r31
    unsigned int i; // r6
    unsigned int i; // r30
    unsigned int i; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80443214 -> 0x80443604
void LightPresetManager::FillPool(class LightPresetManager * const this /* r27 */, unsigned char useExcitement /* r28 */) {
    // Local variables
    unsigned int cat; // r29
    unsigned int i; // r30
    class LightPreset * test; // r1+0x68

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP11LightPreset;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80443604 -> 0x8044394C
void LightPresetManager::RebuildLightPool(class LightPresetManager * const this /* r31 */) {
    // Local variables
    int score; // r0
    unsigned int i; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P6Symbol;
    // -> unsigned char gStlAllocNameLookup;
}

struct _OKToSwap {
    // total size: 0x1
};
struct PoolSorter {
    // total size: 0x18
    class vector mAdjs; // offset 0x0, size 0xC
    class vector mCats; // offset 0xC, size 0xC
};
// Range: 0x8044394C -> 0x804439D4
class DataNode LightPresetManager::OnForcePreset(class LightPresetManager * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11LightPreset;
}

static class Symbol _s; // size: 0x4, address: 0x80A52514
static class Symbol _s; // size: 0x4, address: 0x80A5251C
static class Symbol _s; // size: 0x4, address: 0x80A52524
static class Symbol _s; // size: 0x4, address: 0x80A5252C
static class Symbol _s; // size: 0x4, address: 0x80A52534
static class Symbol _s; // size: 0x4, address: 0x80A5253C
static class Symbol _s; // size: 0x4, address: 0x80A52544
static class Symbol _s; // size: 0x4, address: 0x80A5254C
static class Symbol _s; // size: 0x4, address: 0x80A52554
static class Symbol _s; // size: 0x4, address: 0x80A5255C
static class Symbol _s; // size: 0x4, address: 0x80A52564
static class Symbol _s; // size: 0x4, address: 0x80A5256C
// Range: 0x804439D4 -> 0x80444AA0
class DataNode LightPresetManager::Handle(class LightPresetManager * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__18LightPresetManager;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x10
} __vt__18LightPresetManager; // size: 0x10, address: 0x808EDBF0
struct {
    // total size: 0x8
} __RTTI__18LightPresetManager; // size: 0x8, address: 0x808EDC18
struct {
    // total size: 0x8
} __RTTI__PPQ211stlpmtx_std22pair<P11LightPreset,f>; // size: 0x8, address: 0x808EDCE8
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22pair<P11LightPreset,f>; // size: 0x8, address: 0x808EDD20
struct _OKToMemCpy {
    // total size: 0x1
};
struct pair {
    // total size: 0x8
    struct _Ht_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
class _Slist_iterator : public _Slist_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ29stlp_priv131_Slist_node<Q211stlpmtx_std100pair<C6Symbol,Q211stlpmtx_std68vector<P11LightPreset,Q211stlpmtx_std28StlNodeAlloc<P11LightPreset>>>>; // size: 0x8, address: 0x808EDDD8
struct _Ht_iterator {
    // total size: 0x4
    class _Slist_iterator _M_ite; // offset 0x0, size 0x4
};

