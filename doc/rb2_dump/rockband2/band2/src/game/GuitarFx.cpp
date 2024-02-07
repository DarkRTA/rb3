/*
    Compile unit: C:\rockband2\band2\src\game\GuitarFx.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80070DE0 -> 0x800718C8
*/
// Range: 0x80070DE0 -> 0x80070E8C
void * GuitarFx::GuitarFx(class GuitarFx * const this /* r30 */, enum TrackType inst /* r31 */) {
    // References
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__8GuitarFx;
}

// Range: 0x80070E8C -> 0x800710C0
void * GuitarFx::~GuitarFx(class GuitarFx * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class FxSend * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class FxParamAutoLock {
    // total size: 0x1
};
// Range: 0x800710C0 -> 0x800713FC
class FxSend * GuitarFx::GetFxSend() {
    // Local variables
    class ObjDirItr itr; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
}

// Range: 0x800713FC -> 0x800714C8
class DataNode GuitarFx::OnMidiParser(class GuitarFx * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A49B24
// Range: 0x800714C8 -> 0x800718C8
class DataNode GuitarFx::Handle(class GuitarFx * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__8GuitarFx; // size: 0x54, address: 0x808772D8
struct {
    // total size: 0x8
} __RTTI__8GuitarFx; // size: 0x8, address: 0x80877350

