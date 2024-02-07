/*
    Compile unit: C:\rockband2\band2\src\meta\GameTimePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800EC5B4 -> 0x800EC874
*/
class DataArray * types; // size: 0x4, address: 0x80A4B068
class Symbol name; // size: 0x4, address: 0x80A4B070
class GameTimePanel : public UIPanel {
    // total size: 0x98
    class Timer mTimer; // offset 0x30, size 0x38
    float mTempo; // offset 0x68, size 0x4
};
// Range: 0x800EC5B4 -> 0x800EC640
void * GameTimePanel::GameTimePanel(class GameTimePanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13GameTimePanel;
}

// Range: 0x800EC640 -> 0x800EC670
void GameTimePanel::Load() {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x800EC670 -> 0x800EC6AC
void GameTimePanel::Unload() {
    // References
    // -> class GamePanel * TheGamePanel;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x800EC6AC -> 0x800EC6B0
void GameTimePanel::Exit() {}

// Range: 0x800EC6B0 -> 0x800EC728
void GameTimePanel::Enter(class GameTimePanel * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x800EC728 -> 0x800EC874
void GameTimePanel::Poll(class GameTimePanel * const this /* r31 */) {
    // Local variables
    float dt; // f31
    float newSeconds; // f30
    float beat; // f2

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class GamePanel * TheGamePanel;
}

struct {
    // total size: 0xAC
} __vt__13GameTimePanel; // size: 0xAC, address: 0x808869A0
struct {
    // total size: 0x8
} __RTTI__13GameTimePanel; // size: 0x8, address: 0x80886A78

