/*
    Compile unit: C:\rockband2\system\src\track\TrackWidgetImp.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803C7F5C -> 0x803C8694
*/
class Symbol name; // size: 0x4, address: 0x80A51864
class ImmediateWidgetImp : public TrackWidgetImp {
    // total size: 0x10
    class list mInstances; // offset 0x4, size 0x8
    unsigned char mAllowRotation; // offset 0xC, size 0x1
};
// Range: 0x803C7F5C -> 0x803C8490
void ImmediateWidgetImp::DrawInstances(class ImmediateWidgetImp * const this /* r27 */, int maxMeshes /* r28 */) {
    // Local variables
    class Transform retXform; // r1+0xC0
    int count; // r31
    class iterator mit; // r1+0x64
    class RndMesh * mesh; // r30
    struct _List_iterator inst; // r1+0x60
    class RndTransformable * bone; // r29
    class Vector3 bonePos; // r1+0x70
    class Transform t; // r1+0x80

    // References
    // -> class LoadMgr TheLoadMgr;
}

class MultiMeshWidgetImp : public TrackWidgetImp {
    // total size: 0x8
    class RndMultiMesh * mMulti; // offset 0x4, size 0x4
};
// Range: 0x803C8490 -> 0x803C8558
void * MultiMeshWidgetImp::MultiMeshWidgetImp(class MultiMeshWidgetImp * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndMultiMesh;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__18MultiMeshWidgetImp;
}

// Range: 0x803C8558 -> 0x803C85D8
void * MultiMeshWidgetImp::~MultiMeshWidgetImp(class MultiMeshWidgetImp * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__18MultiMeshWidgetImp;
}

// Range: 0x803C85D8 -> 0x803C85E4
class list & MultiMeshWidgetImp::Instances() {}

// Range: 0x803C85E4 -> 0x803C8694
void MultiMeshWidgetImp::DrawInstances(class MultiMeshWidgetImp * const this /* r29 */, int maxMeshes /* r30 */) {
    // Local variables
    int count; // r31
    class iterator mit; // r1+0x18
}

struct {
    // total size: 0x14
} __vt__18MultiMeshWidgetImp; // size: 0x14, address: 0x808E1828
struct {
    // total size: 0x8
} __RTTI__18MultiMeshWidgetImp; // size: 0x8, address: 0x808E1860
struct {
    // total size: 0x14
} __vt__18ImmediateWidgetImp; // size: 0x14, address: 0x808E1868
struct {
    // total size: 0x8
} __RTTI__18ImmediateWidgetImp; // size: 0x8, address: 0x808E18A0

