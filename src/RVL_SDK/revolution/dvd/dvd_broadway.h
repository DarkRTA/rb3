#ifndef RVL_SDK_DVD_BROADWAY_H
#define RVL_SDK_DVD_BROADWAY_H
#include "types.h"
#include "revolution/ESP.h"
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct DVDDiskID;
typedef struct DVDDriveInfo;
typedef struct OSAlarm;

/**
 * https://wiibrew.org/wiki//dev/di
 * Names adjusted to be closer to those seen in assertions
 */
typedef enum {
    DVD_INTTYPE_TC = (1 << 0),   //!< Transaction callback?
    DVD_INTTYPE_DE = (1 << 1),   //!< Drive error
    DVD_INTTYPE_CVR = (1 << 2),  //!< Something with DVD cover
    DVD_INTTYPE_BR = (1 << 3),   //!< Break requested
    DVD_INTTYPE_TIME = (1 << 4), //!< Time out
    DVD_INTTYPE_SERR = (1 << 5), //!< Security error
    DVD_INTTYPE_VERR = (1 << 6), //!< Verify error
    DVD_INTTYPE_ARGS = (1 << 7), //!< Bad arguments
} DVDLowIntType;

typedef struct DVDVideoReportKey {
    u8 data[32];
} DVDVideoReportKey;

typedef void (*DVDLowCallback)(u32 intType);

bool32 DVDLowInit(void);
bool32 DVDLowReadDiskID(struct DVDDiskID* out, DVDLowCallback callback);
bool32 DVDLowOpenPartition(const u32 offset, const ESTicket* const ticket,
u32 certsSize, const u8* const certs, ESTitleMeta* tmd, DVDLowCallback callback);
bool32 DVDLowClosePartition(DVDLowCallback callback);
bool32 DVDLowUnencryptedRead(void* dst, u32 size, u32 offset, DVDLowCallback callback);
bool32 DVDLowStopMotor(bool32 eject, bool32 kill, DVDLowCallback callback);
bool32 DVDLowInquiry(struct DVDDriveInfo* out, DVDLowCallback callback);
bool32 DVDLowRequestError(DVDLowCallback callback);
bool32 DVDLowSetSpinupFlag(bool32 enable);
bool32 DVDLowReset(DVDLowCallback callback);
bool32 DVDLowAudioBufferConfig(bool32 enable, u32 size, DVDLowCallback callback);
bool32 DVDLowSetMaximumRotation(u32 speed, DVDLowCallback callback);
bool32 DVDLowRead(void* dst, u32 size, u32 offset, DVDLowCallback callback);
bool32 DVDLowSeek(u32 offset, DVDLowCallback callback);
u32 DVDLowGetCoverRegister(void);
u32 DVDLowGetStatusRegister(void);
u32 DVDLowGetControlRegister(void);
bool32 DVDLowPrepareCoverRegister(DVDLowCallback callback);
bool32 DVDLowPrepareStatusRegister(DVDLowCallback callback);
bool32 DVDLowPrepareControlRegister(DVDLowCallback callback);
u32 DVDLowGetImmBufferReg(void);
bool32 DVDLowUnmaskStatusInterrupts(void);
bool32 DVDLowMaskCoverInterrupt(void);
bool32 DVDLowClearCoverInterrupt(DVDLowCallback callback);
bool32 __DVDLowTestAlarm(const struct OSAlarm* alarm);

#ifdef __cplusplus
}
#endif
#endif
