/*
    Compile unit: C:\rockband2\system\src\ui\Splash_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803FA664 -> 0x803FBF70
*/
static float ANIM_FRAME_TIME_MS; // size: 0x4, address: 0x80A571A8
// Range: 0x803FA664 -> 0x803FA698
void * AllocateDiscErrorImage(int size /* r1+0x8 */) {
    // References
    // -> struct TPLPalette * gEjectErrorImg;
}

// Range: 0x803FA698 -> 0x803FA6CC
void * AllocateDiscRetryImage(int size /* r1+0x8 */) {
    // References
    // -> struct TPLPalette * gRetryErrorImg;
}

// Range: 0x803FA6CC -> 0x803FA6FC
void * AllocateMEM2(int size /* r1+0x8 */) {}

// Range: 0x803FA6FC -> 0x803FA7C0
void * SplasherDiscErrorThread() {
    // Local variables
    class SplashWii * splasher; // r31
    int retryCount; // r30
    unsigned char discError; // r29
    long status; // r28

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x803FA7C0 -> 0x803FA824
void * SplashWii::SplashWii(class SplashWii * const this /* r31 */) {
    // References
    // -> static float ANIM_FRAME_TIME_MS;
}

// Range: 0x803FA824 -> 0x803FA890
void * SplashWii::~SplashWii(class SplashWii * const this /* r30 */) {}

// Range: 0x803FA890 -> 0x803FA91C
void SplashWii::Init(class SplashWii * const this /* r30 */) {
    // Local variables
    unsigned int size; // r1+0x8

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x803FA91C -> 0x803FAAD0
void SplashWii::Show(class SplashWii * const this /* r31 */) {
    // Local variables
    unsigned char alpha; // r29

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x803FAAD0 -> 0x803FAC70
void SplashWii::EndShow(class SplashWii * const this /* r31 */) {
    // Local variables
    unsigned char alpha; // r29

    // References
    // -> class WiiRnd TheWiiRnd;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x803FAC70 -> 0x803FACB4
void SplashWii::ShowLoading(class SplashWii * const this /* r31 */) {}

// Range: 0x803FACB4 -> 0x803FADB4
void SplashWii::EndShowLoading(class SplashWii * const this /* r30 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x803FADB4 -> 0x803FAEAC
int SplashWii::PollWPAD(class SplashWii * const this /* r30 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x803FAEAC -> 0x803FAF0C
void SplashWii::PollWPADThread() {
    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> enum quitType gPowerCallback;
}

// Range: 0x803FAF0C -> 0x803FAF8C
void SplashWii::Draw(class SplashWii * const this /* r30 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x803FAF8C -> 0x803FB018
void SplashWii::DrawLoading(class SplashWii * const this /* r30 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x803FB018 -> 0x803FB080
void SplashWii::SuspendMainThread(class SplashWii * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803FB080 -> 0x803FB0BC
void SplashWii::InitPAD() {}

// Range: 0x803FB0BC -> 0x803FB2C0
void SplashWii::InitSplasher(class SplashWii * const this /* r30 */) {
    // Local variables
    unsigned int size; // r1+0x8
    unsigned char langType; // r0
}

// Range: 0x803FB2C0 -> 0x803FB3C8
void SplashWii::InitDiscError(class SplashWii * const this /* r31 */) {
    // Local variables
    unsigned int size; // r1+0x8
    char discErrorFileName[1024]; // r1+0x410
    char discRetryFileName[1024]; // r1+0x10

    // References
    // -> struct TPLPalette * gRetryErrorImg;
    // -> struct TPLPalette * gEjectErrorImg;
}

// Range: 0x803FB3C8 -> 0x803FB44C
void SplashWii::LoadLoadingImage(class SplashWii * const this /* r31 */) {
    // Local variables
    unsigned int size; // r1+0x8
}

// Range: 0x803FB44C -> 0x803FB71C
void SplashWii::DrawSplasher(class SplashWii * const this /* r31 */, unsigned char alpha /* r29 */) {
    // Local variables
    struct _GXColor matColor; // r1+0x14
    struct _GXColor ambColor; // r1+0x10

    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x803FB71C -> 0x803FBC04
void SplashWii::DrawLoadingAnimation(class SplashWii * const this /* r30 */) {
    // Local variables
    struct _GXColor matColor; // r1+0x14
    struct _GXColor ambColor; // r1+0x10
    struct TPLPalette * pal; // r0
    int width; // r30
    int height; // r28
    struct TPLDescriptor * desc; // r0
    float x; // f31
    float y; // f30

    // References
    // -> static float ANIM_FRAME_TIME_MS;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x803FBC04 -> 0x803FBD50
void SplashWii::PollUntilScreenCanEnd(class SplashWii * const this /* r31 */) {
    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x803FBD50 -> 0x803FBDC4
void SplashWii::StartDiscErrorThread(class SplashWii * const this /* r31 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x803FBDC4 -> 0x803FBE10
void SplashWii::EndDiscErrorThread() {
    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x803FBE10 -> 0x803FBF70
void * SplashWii::LoadFile(class SplashWii * const this /* r28 */, unsigned int & size /* r30 */, void * (* memoryAlloc)(int) /* r29 */) {
    // Local variables
    struct DVDFileInfo fileInfo; // r1+0x8
    void * buffer; // r31
    long status; // r30
    int retryCount; // r29

    // References
    // -> class PlatformMgr ThePlatformMgr;
}


