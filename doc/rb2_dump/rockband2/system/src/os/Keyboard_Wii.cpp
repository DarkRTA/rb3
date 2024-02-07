/*
    Compile unit: C:\rockband2\system\src\os\Keyboard_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BEA4C -> 0x805BED24
*/
static unsigned char __kbd_mem[3264]; // size: 0xCC0, address: 0x80985968
// Range: 0x805BEA4C -> 0x805BEB2C
static int TranslateKey() {
    // Local variables
    int key; // r4
}

struct _KBDDevEvent {
    // total size: 0x1
    unsigned char channel; // offset 0x0, size 0x1
};
// Range: 0x805BEB2C -> 0x805BEB78
static void kbdAppAttach(struct _KBDDevEvent * kde /* r31 */) {}

// Range: 0x805BEB78 -> 0x805BEB7C
static void kbdAppDetach() {}

enum _KBDModState {
    KBD_MS_CTRL = 1,
    KBD_MS_SHIFT = 2,
    KBD_MS_ALT = 4,
    KBD_MS_GUI = 8,
    KBD_MS_EXTRA = 16,
    KBD_MS_ALTGR = 32,
    KBD_MS_LANG1 = 64,
    KBD_MS_LANG2 = 128,
    KBD_MS_NUM_LOCK = 256,
    KBD_MS_CAPS_LOCK = 512,
    KBD_MS_SCROLL_LOCK = 1024,
    KBD_MS_SHIFTED_KEY = 2048,
    KBD_MS_SET_ALL = 4096,
    KBD_MS_NULL = 0,
};
// Range: 0x805BEB7C -> 0x805BEC50
static void kbdAppKeyEvent(struct _KBDKeyEvent * kke /* r28 */) {
    // Local variables
    enum _KBDModState ms; // r1+0x8
    unsigned char sh; // r31
    unsigned char ctl; // r30
    unsigned char alt; // r29
    int key; // r0
}

// Range: 0x805BEC50 -> 0x805BEC98
void KeyboardInit() {
    // References
    // -> static unsigned char __kbd_mem[3264];
}

// Range: 0x805BEC98 -> 0x805BEC9C
void KeyboardTerminate() {}

enum _KBDKeyMode {
    KBD_KM_DOWN = 1,
    KBD_KM_REPEAT = 2,
    KBD_KM_NULL = 0,
};
struct _KBDKeyEvent {
    // total size: 0x10
    unsigned char channel; // offset 0x0, size 0x1
    unsigned char hid; // offset 0x1, size 0x1
    enum _KBDKeyMode mode; // offset 0x4, size 0x4
    enum _KBDModState modState; // offset 0x8, size 0x4
    unsigned short unicode; // offset 0xC, size 0x2
};
enum _KBDChanStatus {
    KBD_CS_OK = 0,
    KBD_CS_DISCONNECTED = 1,
    KBD_CS_ROLL_OVER = 2,
    KBD_CS_ERROR = 4,
};
enum _KBDEc {
    KBD_SUCCESS = 0,
    KBD_ERR_OTHER = 1,
    KBD_ERR_NOT_INITIALIZED = 2,
    KBD_ERR_ALREADY_INITIALIZED = 3,
    KBD_ERR_BAD_VALUE = 4,
    KBD_ERR_BAD_STATUS = 5,
    KBD_ERR_BUSY = 7,
};
// Range: 0x805BEC9C -> 0x805BED24
void KeyboardPoll() {
    // Local variables
    struct _KBDKeyEvent kevent; // r1+0x10
    unsigned char ch; // r31
    enum _KBDChanStatus cstat; // r1+0x8
    enum _KBDEc rc; // r0
}


