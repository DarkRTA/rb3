/*
    Compile unit: C:\rockband2\band2\src\meta\LoadingPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800FBCD8 -> 0x800FBD34
*/
class DataArray * types; // size: 0x4, address: 0x80A4B290
class Symbol name; // size: 0x4, address: 0x80A4B298
class LoadingPanel : public UIPanel {
    // total size: 0x5C
};
// Range: 0x800FBCD8 -> 0x800FBCEC
void LoadingPanel::Poll() {}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class CamShot * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x800FBCEC -> 0x800FBD34
void LoadingPanel::Unload(class LoadingPanel * const this /* r31 */) {
    // References
    // -> class Rnd & TheRnd;
}

struct {
    // total size: 0xAC
} __vt__12LoadingPanel; // size: 0xAC, address: 0x808890B8
struct {
    // total size: 0x8
} __RTTI__12LoadingPanel; // size: 0x8, address: 0x80889190

