/*
    Compile unit: C:\rockband2\band2\src\meta\CharLoadingPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800D8484 -> 0x800D84BC
*/
class DataArray * types; // size: 0x4, address: 0x80A4AC50
class Symbol name; // size: 0x4, address: 0x80A4AC58
class CharLoadingPanel : public UIPanel {
    // total size: 0x5C
};
// Range: 0x800D8484 -> 0x800D84BC
void CharLoadingPanel::Enter(class CharLoadingPanel * const this /* r31 */) {
    // References
    // -> class CharSelectPanel * sInstance;
}

struct {
    // total size: 0xAC
} __vt__16CharLoadingPanel; // size: 0xAC, address: 0x80882FE0
struct {
    // total size: 0x8
} __RTTI__16CharLoadingPanel; // size: 0x8, address: 0x808830C0
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class UIProxy * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class UIProxy * * _M_start; // offset 0x0, size 0x4
    class UIProxy * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class CharSelectPanel : public UIPanel {
    // total size: 0x88
    class BandUser * mCreatorUser; // offset 0x30, size 0x4
    class UIProxy * mCreatorProxy; // offset 0x34, size 0x4
    class vector mProxies; // offset 0x38, size 0xC
    int mPreviousAttitude; // offset 0x44, size 0x4
    class CharLoadingPanel * mLoadingPanel; // offset 0x48, size 0x4
    class String mShotRoot; // offset 0x4C, size 0xC
    int mShotNumber; // offset 0x58, size 0x4
};

