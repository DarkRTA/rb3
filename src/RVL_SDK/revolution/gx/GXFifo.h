#ifndef RVL_SDK_GX_FIFO_H
#define RVL_SDK_GX_FIFO_H
#include "revolution/gx/GXInternal.h"
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

GX_DECL_PUBLIC_STRUCT(GXFifoObj, 128);

void GXSetCPUFifo(GXFifoObj*);
bool32 GXGetCPUFifo(GXFifoObj*);

u32 GXGetFifoCount(GXFifoObj*);
u8 GXGetFifoWrap(GXFifoObj*);

#ifdef __cplusplus
}
#endif
#endif
