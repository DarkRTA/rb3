/*
    Compile unit: C:\rockband2\system\src\beatmatch\BarPhraseCapturer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D0E94 -> 0x802D0F80
*/
class BarPhraseCapturer : public PhraseCapturer {
    // total size: 0xC
protected:
    class SongData * mSongData; // offset 0x4, size 0x4
    class BarFinder * mBarFinder; // offset 0x8, size 0x4
};
// Range: 0x802D0E94 -> 0x802D0EAC
void * BarPhraseCapturer::BarPhraseCapturer() {
    // References
    // -> struct [anonymous] __vt__17BarPhraseCapturer;
}

struct PhraseInfo {
    // total size: 0x18
    int start_gem; // offset 0x0, size 0x4
    int end_gem; // offset 0x4, size 0x4
    float start_ms; // offset 0x8, size 0x4
    float end_ms; // offset 0xC, size 0x4
    int start_bar; // offset 0x10, size 0x4
    int end_bar; // offset 0x14, size 0x4
};
class PhraseCapturer {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class StandardBarPhraseCapturer : public BarPhraseCapturer {
    // total size: 0x10
protected:
    int mNumBarsToCapture; // offset 0xC, size 0x4
};
// Range: 0x802D0EAC -> 0x802D0F0C
void * StandardBarPhraseCapturer::StandardBarPhraseCapturer(class StandardBarPhraseCapturer * const this /* r30 */, class DataArray * cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__25StandardBarPhraseCapturer;
}

// Range: 0x802D0F4C -> 0x802D0F80
int StandardBarPhraseCapturer::LastCapturedBar() {}

struct {
    // total size: 0x14
} __vt__25StandardBarPhraseCapturer; // size: 0x14, address: 0x808C9F0C
struct {
    // total size: 0x8
} __RTTI__25StandardBarPhraseCapturer; // size: 0x8, address: 0x808C9F50
struct {
    // total size: 0x14
} __vt__17BarPhraseCapturer; // size: 0x14, address: 0x808C9F58
struct {
    // total size: 0x8
} __RTTI__17BarPhraseCapturer; // size: 0x8, address: 0x808C9F90
struct {
    // total size: 0x8
} __RTTI__14PhraseCapturer; // size: 0x8, address: 0x808C9FA8

