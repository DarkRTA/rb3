#ifndef RVL_SDK_SC_SCAPI_H
#define RVL_SDK_SC_SCAPI_H

#include "types.h"

#include <revolution/bte/context_bte.h>
#include <revolution/wpad/WUD.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * SC/SYSCONF documentation from:
 * https://wiibrew.org/wiki//shared2/sys/SYSCONF
 */

typedef enum {
    SC_ASPECT_STD,
    SC_ASPECT_WIDE
} SCAspectRatio;

typedef enum {
    SC_EURGB_50_HZ,
    SC_EURGB_60_HZ
} SCEuRgb60Mode;

typedef enum {
    SC_LANG_JP,
    SC_LANG_EN,
    SC_LANG_DE,
    SC_LANG_FR,
    SC_LANG_SP,
    SC_LANG_IT,
    SC_LANG_NL,
    SC_LANG_ZH_S,
    SC_LANG_ZH_T,
    SC_LANG_KR,
} SCLanguage;

typedef enum {
    SC_SND_MONO,
    SC_SND_STEREO,
    SC_SND_SURROUND
} SCSoundMode;

typedef enum {
    SC_SENSOR_BAR_BOTTOM,
    SC_SENSOR_BAR_TOP
} SCSensorBarPos;

typedef struct SCIdleMode {
    u8 wc24; // at 0x0
    u8 slotLight; // at 0x1
} SCIdleMode;

typedef struct SCBtDeviceInfo {
    BD_ADDR devAddr; // size 0x06, offset 0x00
    struct small_dev_info small; // size 0x40, offset 0x06
} SCBtDeviceInfo;

typedef struct SCBtDeviceInfoArray {
    u8 num; // size 0x001, offset 0x000 // name known from asserts
    union {
        struct {
            SCBtDeviceInfo registered[WUD_MAX_DEV_ENTRY_FOR_STD]; // at 0x1
            SCBtDeviceInfo active[WUD_MAX_CHANNELS]; // at 0x2BD
        };
        struct {
            /* NOTE: functions in WUD act as if the above is only one buffer
             * (see __wudSecurityEventStackCallback, case BTA_DM_LINK_DOWN_EVT)
             */
            SCBtDeviceInfo devices[14]; // size 0x3d4, offset 0x001
            SCBtDeviceInfo wbc; // size 0x046, offset 0x3d5
            SCBtDeviceInfo at_0x41b; // size 0x046, offset 0x41b
        };
    };
} SCBtDeviceInfoArray; // size 0x461

typedef struct SCBtCmpDevInfo {
    BD_ADDR devAddr; // size 0x06, offset 0x00
    struct small_dev_info small; // size 0x40, offset 0x06
    LINK_KEY linkKey; // size 0x10, offset 0x30 // ? or just a buffer
} SCBtCmpDevInfo; // size 0x56

typedef struct SCBtCmpDevInfoArray {
    u8 num; // size 0x001, offset 0x000 // name known from asserts
    SCBtCmpDevInfo devices[6]; // size 0x204, offset 0x001
} SCBtCmpDevInfoArray; // size 0x205

BOOL SCCheckPCMessageRestriction(void);

u8 SCGetAspectRatio(void);
s8 SCGetDisplayOffsetH(void);
u8 SCGetEuRgb60Mode(void);
void SCGetIdleMode(SCIdleMode *mode);
u8 SCGetLanguage(void);
u8 SCGetProgressiveMode(void);
u8 SCGetScreenSaverMode(void);
u8 SCGetSoundMode(void);
u32 SCGetCounterBias(void);
u32 SCGetSimpleAddressID(int);
u32 SCGetSimpleAddressRegionIdHi(unsigned char *);

void SCGetBtDeviceInfoArray(SCBtDeviceInfoArray *array);
BOOL SCSetBtDeviceInfoArray(const SCBtDeviceInfoArray *array);
void SCGetBtCmpDevInfoArray(SCBtCmpDevInfoArray *array);
BOOL SCSetBtCmpDevInfoArray(const SCBtCmpDevInfoArray *array);
u32 SCGetBtDpdSensibility(void);
u8 SCGetWpadMotorMode(void);
BOOL SCSetWpadMotorMode(u8 mode);
u8 SCGetWpadSensorBarPosition(void);
u8 SCGetWpadSpeakerVolume(void);
BOOL SCSetWpadSpeakerVolume(u8 vol);

#ifdef __cplusplus
}
#endif

#endif
