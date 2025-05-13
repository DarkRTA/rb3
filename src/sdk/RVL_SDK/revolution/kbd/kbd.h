#ifndef RVL_SDK_KBD_H
#define RVL_SDK_KBD_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

enum _KBDModState {
    KBD_MS_CTRL = 0x1,
    KBD_MS_SHIFT = 0x2,
    KBD_MS_ALT = 0x4,
    KBD_MS_GUI = 0x8,
    KBD_MS_EXTRA = 0x10,
    KBD_MS_ALTGR = 0x20,
    KBD_MS_LANG1 = 0x40,
    KBD_MS_LANG2 = 0x80,
    KBD_MS_NUM_LOCK = 0x100,
    KBD_MS_CAPS_LOCK = 0x200,
    KBD_MS_SCROLL_LOCK = 0x400,
    KBD_MS_SHIFTED_KEY = 0x800,
    KBD_MS_SET_ALL = 0x1000,
    KBD_MS_NULL = 0,
};

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
struct _KBDDevEvent {
    // total size: 0x1
    unsigned char channel; // offset 0x0, size 0x1
};

typedef void (*kbdAttachCallback)(_KBDDevEvent *event);
typedef void (*kbdDetachCallback)(_KBDDevEvent *event);
void KBDInit(
    void *kbdBuf, kbdAttachCallback attachCb, kbdDetachCallback detachCb, int unk
);
void KBDInitRegionUS();
void KBDInitRegionEU();
void KBDInitRegionJP();

void KBDSetCountry(unsigned char channel, int val);
void KBDSetModState(unsigned char channel, int val);
void KBDSetLedsRetry(unsigned char channel, int val);

void KBDGetModState(unsigned char channel, int *val);
void KBDGetChannelStatus(unsigned char channel, int *val);
int KBDGetKey(unsigned char channel, _KBDKeyEvent *event);

#ifdef __cplusplus
}
#endif

#endif // RVL_SDK_KBD_H
