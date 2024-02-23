#ifndef RVL_SDK_AI_H
#define RVL_SDK_AI_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct OSContext;

typedef void (*AIDMACallback)(void);

typedef enum {
    AI_DSP_32KHZ,
    AI_DSP_48KHZ,
} AIDSPSampleRate;

AIDMACallback AIRegisterDMACallback(AIDMACallback callback);
void AIInitDMA(void* buffer, u32 length);
void AIStartDMA(void);
void AIStopDMA(void);
u32 AIGetDMABytesLeft(void);
void AISetDSPSampleRate(u32 rate);
u32 AIGetDSPSampleRate(void);
u32 AIGetDMAStartAddr(void);
u32 AIGetDMALength(void);
BOOL AICheckInit(void);
void AIInit(void* stack);
void __AIDHandler(s32 intr, struct OSContext* ctx);

#ifdef __cplusplus
}
#endif
#endif
