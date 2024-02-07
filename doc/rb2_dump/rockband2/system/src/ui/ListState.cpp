/*
    Compile unit: C:\rockband2\system\src\ui\ListState.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803D70E8 -> 0x803D8CD8
*/
// Range: 0x803D70E8 -> 0x803D7220
void * ListState::ListState(class ListState * const this /* r30 */, class ListProvider * provider /* r31 */) {
    // References
    // -> struct [anonymous] __vt__9ListState;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x803D7220 -> 0x803D7258
int ListState::Selected(const class ListState * const this /* r31 */) {}

// Range: 0x803D7258 -> 0x803D72D4
int ListState::SelectedNoWrap(const class ListState * const this /* r30 */) {
    // Local variables
    int showing; // r31
}

// Range: 0x803D72D4 -> 0x803D730C
int ListState::SelectedData(const class ListState * const this /* r31 */) {}

// Range: 0x803D730C -> 0x803D7334
int ListState::SelectedDisplay() {}

// Range: 0x803D7334 -> 0x803D7350
unsigned char ListState::IsScrolling() {}

// Range: 0x803D7350 -> 0x803D73A0
int ListState::NumShowing() {}

// Range: 0x803D73A0 -> 0x803D73A8
int ListState::MinDisplay() {}

// Range: 0x803D73A8 -> 0x803D73B0
int ListState::MaxDisplay() {}

// Range: 0x803D73B0 -> 0x803D73B8
float ListState::Speed() {}

// Range: 0x803D73B8 -> 0x803D73C0
unsigned char ListState::ScrollPastMinDisplay() {}

// Range: 0x803D73C0 -> 0x803D73C8
unsigned char ListState::ScrollPastMaxDisplay() {}

// Range: 0x803D73C8 -> 0x803D7468
unsigned char ListState::CanScrollBack(const class ListState * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x803D7468 -> 0x803D7534
unsigned char ListState::CanScrollNext(const class ListState * const this /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x803D7534 -> 0x803D753C
float ListState::StepPercent() {}

// Range: 0x803D753C -> 0x803D7544
class ListProvider * ListState::Provider() {}

// Range: 0x803D7544 -> 0x803D754C
class ListProvider * ListState::Provider() {}

// Range: 0x803D754C -> 0x803D75B4
int ListState::WrapShowing(const class ListState * const this /* r30 */, int showing /* r31 */) {}

// Range: 0x803D75B4 -> 0x803D75FC
int ListState::Display2Data(const class ListState * const this /* r31 */) {
    // Local variables
    int showing; // r4
}

// Range: 0x803D75FC -> 0x803D7678
int ListState::Display2Showing(const class ListState * const this /* r30 */) {
    // Local variables
    int showing; // r31
}

// Range: 0x803D7678 -> 0x803D76CC
int ListState::Showing2Data(const class ListState * const this /* r31 */) {
    // Local variables
    int data; // r3
    const int * it; // r4
}

// Range: 0x803D76CC -> 0x803D77F8
int ListState::MaxFirstShowing(const class ListState * const this /* r31 */) {
    // Local variables
    int num_showing; // r1+0x10
    int max; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D77F8 -> 0x803D78C4
int ListState::ScrollMaxDisplay(const class ListState * const this /* r31 */) {
    // Local variables
    int max_display; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D78C4 -> 0x803D78CC
int ListState::CurrentScroll() {}

// Range: 0x803D78CC -> 0x803D7A50
void ListState::SetProvider(class ListState * const this /* r29 */, class ListProvider * provider /* r30 */, class RndDir * dir /* r31 */) {
    // Local variables
    int i; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D7A50 -> 0x803D7AE0
void ListState::SetNumDisplay(class ListState * const this /* r29 */, int num /* r30 */, unsigned char reset /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D7AE0 -> 0x803D7B4C
void ListState::SetMinDisplay(class ListState * const this /* r30 */, int min /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D7B4C -> 0x803D7BF4
void ListState::SetMaxDisplay(class ListState * const this /* r30 */, int max /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D7BF4 -> 0x803D7C10
void ListState::SetCircular() {}

// Range: 0x803D7C10 -> 0x803D7C8C
void ListState::SetSpeed(class ListState * const this /* r31 */, float speed /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D7C8C -> 0x803D7CC0
void ListState::SetScrollPastMinDisplay() {}

// Range: 0x803D7CC0 -> 0x803D7CC8
void ListState::SetScrollPastMaxDisplay() {}

// Range: 0x803D7CC8 -> 0x803D7DF4
void ListState::SetSelected(class ListState * const this /* r31 */, int showing /* r29 */, int first_showing /* r30 */) {}

// Range: 0x803D7DF4 -> 0x803D8064
void ListState::SetSelectedSimulateScroll(class ListState * const this /* r31 */) {
    // Local variables
    int amount; // r28

    // References
    // -> struct [anonymous] __vt__13ListScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D8064 -> 0x803D83B0
void ListState::Scroll(class ListState * const this /* r31 */, int amount /* r27 */, unsigned char simulate /* r28 */) {
    // Local variables
    struct ScrollState state; // r1+0x28
    unsigned char scroll; // r30
    unsigned char atEnd; // r29

    // References
    // -> struct [anonymous] __vt__13ListScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D83B0 -> 0x803D8434
void ListState::PageScroll() {}

unsigned char gCreditsPanelLoaded; // size: 0x1, address: 0x80A51BB0
// Range: 0x803D8434 -> 0x803D8944
void ListState::Poll(class ListState * const this /* r31 */, float time /* f31 */) {
    // Local variables
    float calculatedTime; // f1
    float overshot; // f0

    // References
    // -> struct [anonymous] __vt__13ListScrollMsg;
    // -> class Symbol t;
    // -> unsigned char gCreditsPanelLoaded;
    // -> struct [anonymous] __vt__18ListScrollStartMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

// Range: 0x803D8944 -> 0x803D8BDC
unsigned char ListState::BuildScroll(const class ListState * const this /* r28 */, int amount /* r26 */, int targetShowing /* r29 */, int selectedDisplay /* r30 */, struct ScrollState & state /* r31 */) {
    // Local variables
    int newTarget; // r26
    int current; // r0
    int maxDisplay; // r1+0xC
}

// Range: 0x803D8BDC -> 0x803D8C3C
int ListState::State2Data(const class ListState * const this /* r30 */, const struct ScrollState & state /* r31 */) {}

// Range: 0x803D8C3C -> 0x803D8CD8
int ListState::ScrollToTarget() {
    // Local variables
    int direct; // r29
    int wrap; // r0
}

struct {
    // total size: 0x6C
} __vt__9ListState; // size: 0x6C, address: 0x808E3D74
struct {
    // total size: 0x8
} __RTTI__9ListState; // size: 0x8, address: 0x808E3E08

