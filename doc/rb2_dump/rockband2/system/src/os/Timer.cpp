/*
    Compile unit: C:\rockband2\system\src\os\Timer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CA394 -> 0x805CAC4C
*/
static float kWorstResetFrames; // size: 0x4, address: 0x80A57DF8
class list sTimers; // size: 0x8, address: 0x80988BD0
float sLowCycles2Ms; // size: 0x4, address: 0x80A54D90
float sHighCycles2Ms; // size: 0x4, address: 0x80A54D94
double sDoubleCycles2Ms; // size: 0x8, address: 0x80988BD8
// Range: 0x805CA394 -> 0x805CA3DC
void * Timer::Timer() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x805CA3DC -> 0x805CA4C4
void * Timer::Timer(class Timer * const this /* r29 */, class DataArray * config /* r30 */) {}

// Range: 0x805CA4C4 -> 0x805CA504
void Timer::Sleep() {}

// Range: 0x805CA504 -> 0x805CA60C
void Timer::Reset(class Timer * const this /* r29 */) {
    // References
    // -> static float kWorstResetFrames;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x805CA60C -> 0x805CA684
void Timer::Restart(class Timer * const this /* r30 */) {}

// Range: 0x805CA684 -> 0x805CA6B0
void Timer::SetLastMs() {}

// Range: 0x805CA6B0 -> 0x805CA720
class Timer * AutoTimer::GetTimer() {
    // Local variables
    struct _List_iterator t; // r1+0x18

    // References
    // -> class list sTimers;
}

// Range: 0x805CA720 -> 0x805CA784
void Timer::Init() {
    // References
    // -> float sHighCycles2Ms;
    // -> float sLowCycles2Ms;
    // -> double sDoubleCycles2Ms;
}

// Range: 0x805CA784 -> 0x805CA7E8
static class DataNode OnPrintTimers(class DataArray * a /* r31 */) {}

// Range: 0x805CA7E8 -> 0x805CA8D0
void AutoTimer::PrintTimers(unsigned char worst /* r30 */) {
    // Local variables
    struct _List_iterator t; // r1+0x18
    float ms; // f0

    // References
    // -> class list sTimers;
    // -> class Debug TheDebug;
}

// Range: 0x805CA8D0 -> 0x805CA964
static class DataNode SetTimerMs(class DataArray * d /* r30 */) {
    // Local variables
    class Timer * t; // r31
}

// Range: 0x805CA964 -> 0x805CA9E4
static class DataNode TimerMs(class DataArray * d /* r31 */) {
    // Local variables
    class Timer * t; // r0
}

// Range: 0x805CA9E4 -> 0x805CABAC
void AutoTimer::Init() {
    // Local variables
    class DataArray * config; // r30
    int i; // r29
    unsigned char enable; // r1+0x8

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<5Timer>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sTimers;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std18_List_node<5Timer>; // size: 0x8, address: 0x80926680
static class list sConditionalTimersEnabled; // size: 0x8, address: 0x80988BF0
// Range: 0x805CABAC -> 0x805CAC4C
static void __sinit_\Timer_cpp() {
    // References
    // -> static class list sConditionalTimersEnabled;
    // -> class list sTimers;
}


