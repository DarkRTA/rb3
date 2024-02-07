/*
    Compile unit: C:\rockband2\system\src\os\HomeMenu_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805B4A18 -> 0x805B5A6C
*/
static long op[4]; // size: 0x10, address: 0x8084E6B0
// Range: 0x805B4A18 -> 0x805B4A20
static int HomeMenuSoundCallback() {}

// Range: 0x805B4A20 -> 0x805B4A5C
void * HomeMenu::HomeMenu() {}

// Range: 0x805B4A5C -> 0x805B4AB0
void * HomeMenu::~HomeMenu(class HomeMenu * const this /* r30 */) {}

// Range: 0x805B4AB0 -> 0x805B4B48
void HomeMenu::Terminate(class HomeMenu * const this /* r31 */) {}

// Range: 0x805B4B48 -> 0x805B4B68
void HomeMenu::AllowHomeMenu() {}

// Range: 0x805B4B68 -> 0x805B4B90
void HomeMenu::ActivateBanIcon() {}

// Range: 0x805B4B90 -> 0x805B4BB8
void HomeMenu::SetHomeMenuActive() {}

// Range: 0x805B4BB8 -> 0x805B4BD0
void HomeMenu::UnlockHomeMenu() {}

// Range: 0x805B4BD0 -> 0x805B4DA0
void HomeMenu::ShowBannedIcon(class HomeMenu * const this /* r30 */) {
    // Local variables
    unsigned char wasActive; // r31
    unsigned long currTime; // r0
    float elapse; // f3
}

// Range: 0x805B4DA0 -> 0x805B4EB8
void HomeMenu::Poll(class HomeMenu * const this /* r30 */) {
    // Local variables
    int i; // r31
    long probeResult; // r0
    unsigned long type; // r1+0x8
    int input_classic; // r0
}

// Range: 0x805B4EB8 -> 0x805B4F3C
void HomeMenu::ActivateHomeMenu() {
    // References
    // -> class UIManager TheUI;
}

// Range: 0x805B4F3C -> 0x805B5000
void HomeMenu::InitHomeMenu(class HomeMenu * const this /* r31 */) {
    // Local variables
    int i; // r31

    // References
    // -> class SynthWii * TheWiiSynth;
}

// Range: 0x805B5000 -> 0x805B5078
void HomeMenu::SetAdjustValue(struct HBMDataInfo * pHomeMenuInfo /* r31 */) {}

static int _x; // size: 0x4, address: 0x80A549D0
// Range: 0x805B5078 -> 0x805B5340
void HomeMenu::InitHomeMenuButtonInfo(class HomeMenu * const this /* r29 */, struct HBMDataInfo * pHomeMenuInfo /* r30 */) {
    // References
    // -> static int _x;
}

// Range: 0x805B5340 -> 0x805B5374
void HomeMenu::InitControllerData() {
    // Local variables
    int i; // r5
}

// Range: 0x805B5374 -> 0x805B56F8
void HomeMenu::DrawBannedIcon(class HomeMenu * const this /* r28 */, unsigned char alpha /* r29 */) {
    // Local variables
    struct _GXTexObj texObj; // r1+0x10
    signed short offset; // r3
    signed short x1; // r31
    signed short x2; // r30

    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805B56F8 -> 0x805B57F0
void * HomeMenu::ReadDvdFile(unsigned long * fileSize /* r29 */) {
    // Local variables
    void * readBuf; // r31
    int readBytes; // r0
    class File * file; // r30
}

// Range: 0x805B57F0 -> 0x805B58C8
int HomeMenu::CalculateAnalogCursorPos() {
    // Local variables
    float x; // f3
    float y; // f0
}

// Range: 0x805B58C8 -> 0x805B5A6C
int HomeMenu::CalculateDigitalCursorPos() {}


