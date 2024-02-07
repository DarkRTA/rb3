/*
    Compile unit: C:\rockband2\band2\src\meta\DrumTutorialPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800E3368 -> 0x800E4108
*/
class DataArray * types; // size: 0x4, address: 0x80A4AE90
class Symbol name; // size: 0x4, address: 0x80A4AE98
class DrumTutorialPanel * TheDrumTutorialPanel; // size: 0x4, address: 0x80A4AE9C
struct FileData {
    // total size: 0x4
    const char * file; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct FileData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct FileData * _M_start; // offset 0x0, size 0x4
    struct FileData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct EventData {
    // total size: 0x14
    class Symbol name; // offset 0x0, size 0x4
    int next; // offset 0x4, size 0x4
    class vector files; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EventData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EventData * _M_start; // offset 0x0, size 0x4
    struct EventData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class VoiceMgr {
    // total size: 0x18
    class vector mEventList; // offset 0x0, size 0xC
    float mVolume; // offset 0xC, size 0x4
    const char * mDirectory; // offset 0x10, size 0x4
    class StreamPlayer * mStreamPlayer; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct Flasher {
    // total size: 0x8
    class RndDrawable * mDrawable; // offset 0x0, size 0x4
    int mFrames; // offset 0x4, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class TutorialPanel : public UIPanel, public BeatMatchControllerSink {
    // total size: 0xF0
protected:
    class VoiceMgr * mVoiceMgr; // offset 0x34, size 0x4
    const char * mPanelName; // offset 0x38, size 0x4
private:
    float mTutorialSeconds; // offset 0x3C, size 0x4
    int mTutorialPlayer; // offset 0x40, size 0x4
    int mTotalAutoplayBRE; // offset 0x44, size 0x4
    unsigned char mAutoplayingBRE; // offset 0x48, size 0x1
    unsigned char mAutoplayingDrumsBRE; // offset 0x49, size 0x1
    float mAutoplayBREWindow; // offset 0x4C, size 0x4
    float mAutoplayBRETimes[5]; // offset 0x50, size 0x14
    class GemPlayer * mGemAutoplayerBRE; // offset 0x64, size 0x4
    class MasterAudio * mAudioAutoplayerBRE; // offset 0x68, size 0x4
    unsigned char mAmbientLoopStarted; // offset 0x6C, size 0x1
    class Sfx * mAmbientLoop; // offset 0x70, size 0x4
    class list mFlashList; // offset 0x74, size 0x8
    class Timer mTimer; // offset 0x80, size 0x38
    class BeatMatchController * mController; // offset 0xB8, size 0x4
    class Fader * mFader; // offset 0xBC, size 0x4
};
class DrumTutorialPanel : public TutorialPanel {
    // total size: 0xF8
    class list mCallbackList; // offset 0xC0, size 0x8
};
// Range: 0x800E3368 -> 0x800E3420
void * DrumTutorialPanel::DrumTutorialPanel(class DrumTutorialPanel * const this /* r30 */) {
    // References
    // -> class DrumTutorialPanel * TheDrumTutorialPanel;
    // -> struct [anonymous] __vt__17DrumTutorialPanel;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Object * _M_data; // offset 0x8, size 0x4
};
// Range: 0x800E3420 -> 0x800E34C4
void * DrumTutorialPanel::~DrumTutorialPanel(class DrumTutorialPanel * const this /* r29 */) {
    // References
    // -> class DrumTutorialPanel * TheDrumTutorialPanel;
}

// Range: 0x800E34C4 -> 0x800E34FC
void DrumTutorialPanel::Enter(class DrumTutorialPanel * const this /* r31 */) {}

// Range: 0x800E34FC -> 0x800E353C
void DrumTutorialPanel::Exit(class DrumTutorialPanel * const this /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x800E353C -> 0x800E3728
unsigned char DrumTutorialPanel::Swing(class DrumTutorialPanel * const this /* r31 */) {
    // Local variables
    class Message msgOut; // r1+0x38
    struct _List_iterator j; // r1+0x18

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800E3728 -> 0x800E37FC
class DataNode DrumTutorialPanel::OnAddDrumHitCallback(class DrumTutorialPanel * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    class Object * callback; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>; // size: 0x8, address: 0x80884F18
// Range: 0x800E37FC -> 0x800E38EC
class DataNode DrumTutorialPanel::OnRemoveDrumHitCallback(class DrumTutorialPanel * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    class Object * callback; // r31
}

// Range: 0x800E38EC -> 0x800E3958
int DrumTutorialPanel::Get16th() {
    // Local variables
    struct MBT mbt; // r1+0x8

    // References
    // -> class SongDB * TheSongDB;
    // -> class TaskMgr TheTaskMgr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4AEA4
static class Symbol _s; // size: 0x4, address: 0x80A4AEAC
static class Symbol _s; // size: 0x4, address: 0x80A4AEB4
// Range: 0x800E3958 -> 0x800E4108
class DataNode DrumTutorialPanel::Handle(class DrumTutorialPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xE8
} __vt__17DrumTutorialPanel; // size: 0xE8, address: 0x80884F98
struct {
    // total size: 0x8
} __RTTI__17DrumTutorialPanel; // size: 0x8, address: 0x808850C0
struct {
    // total size: 0x8
} __RTTI__13TutorialPanel; // size: 0x8, address: 0x80885100
struct {
    // total size: 0x8
} __RTTI__23BeatMatchControllerSink; // size: 0x8, address: 0x80885120

