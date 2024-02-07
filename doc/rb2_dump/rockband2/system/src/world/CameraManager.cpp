/*
    Compile unit: C:\rockband2\system\src\world\CameraManager.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803FBF70 -> 0x803FFF3C
*/
static class Rand sRand; // size: 0x410, address: 0x8097E580
static int sSeed; // size: 0x4, address: 0x80A51F50
class FreeCamera {
    // total size: 0x80
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class RndTransformable * mParent; // offset 0x4, size 0x4
    class Vector3 mRot; // offset 0x10, size 0x10
    class Transform mXfm; // offset 0x20, size 0x40
    float mFov; // offset 0x60, size 0x4
    unsigned char mFrozen; // offset 0x64, size 0x1
    unsigned char mActive; // offset 0x65, size 0x1
    int mController; // offset 0x68, size 0x4
    float mRotateRate; // offset 0x6C, size 0x4
    float mSlewRate; // offset 0x70, size 0x4
    float mFocalPlane; // offset 0x74, size 0x4
    unsigned char mUseParentRotateX; // offset 0x78, size 0x1
    unsigned char mUseParentRotateY; // offset 0x79, size 0x1
    unsigned char mUseParentRotateZ; // offset 0x7A, size 0x1
    int mStateNum; // offset 0x7C, size 0x4
};
// Range: 0x803FBF70 -> 0x803FC0C4
void * CameraManager::CameraManager(class CameraManager * const this /* r28 */, class WorldDir * parent /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__27ObjPtr<7CamShot,9ObjectDir>;
    // -> struct [anonymous] __vt__13CameraManager;
}

class _Slist_node : public _Slist_node_base {
    // total size: 0x10
public:
    struct pair _M_data; // offset 0x4, size 0xC
};
// Range: 0x803FC0C4 -> 0x803FC21C
void * CameraManager::~CameraManager(class CameraManager * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7CamShot,9ObjectDir>;
    // -> struct [anonymous] __vt__13CameraManager;
}

struct _Ht_iterator {
    // total size: 0x4
    class _Slist_iterator _M_ite; // offset 0x0, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803FC21C -> 0x803FC8F8
void CameraManager::SyncObjects(class CameraManager * const this /* r30 */) {
    // Local variables
    class ObjDirItr shotItr; // r1+0xD4
    struct _Ht_iterator it; // r1+0x98
    int count; // r31
    class CamShot * shots[1000]; // r1+0xE8
    class list & cams; // r30
    struct _List_iterator cam; // r1+0x94
    int i; // r27
    int which; // r0
    int i; // r27

    // References
    // -> static int sSeed;
    // -> static class Rand sRand;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7CamShot>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7CamShot;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class CamShot * _M_data; // offset 0x8, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std21_List_node<P7CamShot>; // size: 0x8, address: 0x808E88A8
static class Symbol flags_exact; // size: 0x4, address: 0x80A51F58
static class Symbol flags_any; // size: 0x4, address: 0x80A51F60
// Range: 0x803FC8F8 -> 0x803FCBEC
unsigned char CameraManager::ShotMatches(class CamShot * shot /* r28 */, const class vector & filters /* r29 */) {
    // Local variables
    const struct PropertyFilter * it; // r30
    class DataNode val; // r1+0x28
    class Symbol p; // r1+0x10
    class DataArray * matches; // r27
    unsigned int j; // r26

    // References
    // -> static class Symbol flags_any;
    // -> static class Symbol flags_exact;
}

static class Symbol flags_exact; // size: 0x4, address: 0x80A51F68
static class Symbol flags_any; // size: 0x4, address: 0x80A51F70
// Range: 0x803FCBEC -> 0x803FCEA0
class CamShot * CameraManager::PickCameraShot(class CameraManager * const this /* r29 */, class Symbol & category /* r27 */, const class vector & filters /* r28 */) {
    // Local variables
    class CamShot * shot; // r26
    class String note; // r1+0x28
    const struct PropertyFilter * it; // r29

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol flags_any;
    // -> static class Symbol flags_exact;
}

static class Message first_shot_ok; // size: 0x8, address: 0x8097E9A0
// Range: 0x803FCEA0 -> 0x803FD2A8
class CamShot * CameraManager::FindCameraShot(class CameraManager * const this /* r28 */, class Symbol & category /* r29 */, const class vector & filters /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x7C
    class CamShot * cam; // r27

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std21_List_node<P7CamShot>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class WorldDir * TheWorld;
    // -> static class Message first_shot_ok;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol flags_exact; // size: 0x4, address: 0x80A51F78
static class Symbol flags_any; // size: 0x4, address: 0x80A51F80
struct PropertyFilter {
    // total size: 0x14
    class DataNode prop; // offset 0x0, size 0x8
    class DataNode match; // offset 0x8, size 0x8
    int mask; // offset 0x10, size 0x4
};
// Range: 0x803FD2A8 -> 0x803FD618
class Symbol CameraManager::MakeCategoryAndFilters(class DataArray * args /* r27 */, class vector & filterList /* r29 */) {
    // Local variables
    class Symbol cat; // r1+0x20
    unsigned int i; // r30
    struct PropertyFilter filt; // r1+0x38

    // References
    // -> static class Symbol flags_any;
    // -> static class Symbol flags_exact;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x803FD618 -> 0x803FD7A8
class DataNode CameraManager::OnPickCameraShot(class CameraManager * const this /* r31 */, class DataArray * args /* r30 */) {
    // Local variables
    class vector filterList; // r1+0x28
    class Symbol cat; // r1+0x24
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct PropertyFilter * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct PropertyFilter * _M_start; // offset 0x0, size 0x4
    struct PropertyFilter * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x803FD7A8 -> 0x803FD938
class DataNode CameraManager::OnFindCameraShot(class CameraManager * const this /* r31 */, class DataArray * args /* r30 */) {
    // Local variables
    class vector filterList; // r1+0x28
    class Symbol category; // r1+0x24
}

// Range: 0x803FD938 -> 0x803FD9E4
void CameraManager::ForceCameraShot(class CameraManager * const this /* r30 */, class CamShot * shot /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803FD9E4 -> 0x803FDAA4
void CameraManager::StartShot_(class CameraManager * const this /* r30 */, class CamShot * shot /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803FDAA4 -> 0x803FE27C
class DataNode CameraManager::OnCycleShot(class CameraManager * const this /* r31 */) {
    // Local variables
    class ObjDirItr shot; // r1+0x58
    class ObjDirItr shot; // r1+0x44
    class ObjDirItr first; // r1+0x30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7CamShot;
}

// Range: 0x803FE27C -> 0x803FE2F8
unsigned char CameraManager::ToggleFreeCam(class CameraManager * const this /* r30 */, int controller /* r31 */) {}

// Range: 0x803FE2F8 -> 0x803FE340
unsigned char CameraManager::FreeCamActive() {}

// Range: 0x803FE340 -> 0x803FE388
void CameraManager::SetFreeCamParent(class CameraManager * const this /* r30 */, class RndTransformable * parent /* r31 */) {}

// Range: 0x803FE388 -> 0x803FE3E4
void CameraManager::SetFreeCamPos(class CameraManager * const this /* r30 */, const class Vector3 & pos /* r31 */) {}

// Range: 0x803FE3E4 -> 0x803FE440
void CameraManager::SetFreeCamRot(class CameraManager * const this /* r30 */, const class Vector3 & rot /* r31 */) {}

// Range: 0x803FE440 -> 0x803FE4C4
void CameraManager::SetFreeCamParentDof(class CameraManager * const this /* r28 */, int x /* r29 */, int y /* r30 */, int z /* r31 */) {}

// Range: 0x803FE4C4 -> 0x803FE528
void CameraManager::StartNextShot(class CameraManager * const this /* r31 */) {}

static class Symbol shot; // size: 0x4, address: 0x80A51F88
static class Symbol category; // size: 0x4, address: 0x80A51F90
// Range: 0x803FE528 -> 0x803FE614
void CameraManager::Poll(class CameraManager * const this /* r31 */) {
    // Local variables
    float time; // f0
    float dur; // f31

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol category;
    // -> static class Symbol shot;
}

static class Symbol _s; // size: 0x4, address: 0x80A51F98
static class Symbol _s; // size: 0x4, address: 0x80A51FA0
static class Symbol _s; // size: 0x4, address: 0x80A51FA8
static class Symbol _s; // size: 0x4, address: 0x80A51FB0
static class Symbol _s; // size: 0x4, address: 0x80A51FB8
static class Symbol _s; // size: 0x4, address: 0x80A51FC0
static class Symbol _s; // size: 0x4, address: 0x80A51FC8
static class Symbol _s; // size: 0x4, address: 0x80A51FD0
static class Symbol _s; // size: 0x4, address: 0x80A51FD8
static class Symbol _s; // size: 0x4, address: 0x80A51FE0
static class Symbol _s; // size: 0x4, address: 0x80A51FE8
static class Symbol _s; // size: 0x4, address: 0x80A51FF0
static class Symbol _s; // size: 0x4, address: 0x80A51FF8
static class Symbol _s; // size: 0x4, address: 0x80A52000
static class Symbol _s; // size: 0x4, address: 0x80A52008
static class Symbol _s; // size: 0x4, address: 0x80A52010
static class Symbol _s; // size: 0x4, address: 0x80A52018
// Range: 0x803FE614 -> 0x803FFC08
class DataNode CameraManager::Handle(class CameraManager * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x68
    class MessageTimer _mt; // r1+0xD0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__7CamShot;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__13CameraManager;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> unsigned char sActive;
}

// Range: 0x803FFC08 -> 0x803FFC80
class DataNode CameraManager::OnGetFreeCamState(class CameraManager * const this /* r31 */) {}

// Range: 0x803FFC80 -> 0x803FFCC4
class DataNode CameraManager::OnNextFreeCamState() {}

// Range: 0x803FFCC4 -> 0x803FFD00
class DataNode CameraManager::OnResyncCategories() {}

// Range: 0x803FFD00 -> 0x803FFD58
class DataNode CameraManager::OnRandomSeed(class DataArray * msg /* r31 */) {
    // References
    // -> static int sSeed;
}

// Range: 0x803FFD58 -> 0x803FFF2C
class DataNode CameraManager::OnIterateShot(class CameraManager * const this /* r27 */, class DataArray * msg /* r29 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode val; // r1+0x40
    struct _Ht_iterator it; // r1+0x28
    class list & cams; // r30
    struct _List_iterator cam; // r1+0x24
    class CamShot * shot; // r3
    int j; // r27
}

struct {
    // total size: 0x10
} __vt__13CameraManager; // size: 0x10, address: 0x808E8A58
struct {
    // total size: 0x8
} __RTTI__13CameraManager; // size: 0x8, address: 0x808E8A78
struct {
    // total size: 0x18
} __vt__27ObjPtr<7CamShot,9ObjectDir>; // size: 0x18, address: 0x808E8A80
struct {
    // total size: 0x8
} __RTTI__27ObjPtr<7CamShot,9ObjectDir>; // size: 0x8, address: 0x808E8AC0
unsigned long _list[28]; // size: 0x70, address: 0x80848F38
class _Stl_prime {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PPQ29stlp_priv16_Slist_node_base; // size: 0x8, address: 0x808E8C20
struct {
    // total size: 0x8
} __RTTI__PQ213CameraManager14PropertyFilter; // size: 0x8, address: 0x808E8C48
struct _OKToMemCpy {
    // total size: 0x1
};
struct pair {
    // total size: 0x8
    struct _Ht_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct _Slist_iterator_base {
    // total size: 0x4
    struct _Slist_node_base * _M_node; // offset 0x0, size 0x4
};
class _Slist_iterator : public _Slist_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ29stlp_priv118_Slist_node<Q211stlpmtx_std88pair<C6Symbol,Q211stlpmtx_std56list<P7CamShot,Q211stlpmtx_std23StlNodeAlloc<P7CamShot>>>>; // size: 0x8, address: 0x808E8CD0
class _Sl_global {
    // total size: 0x1
};
// Range: 0x803FFF2C -> 0x803FFF3C
static void __sinit_\CameraManager_cpp() {
    // References
    // -> static class Rand sRand;
}


