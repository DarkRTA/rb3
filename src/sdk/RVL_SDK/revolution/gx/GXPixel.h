#ifndef RVL_SDK_GX_PIXEL_H
#define RVL_SDK_GX_PIXEL_H
#include "revolution/gx/GXTypes.h"
#include "revolution/MTX.h"
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXFogAdjTable {
    u16 r[10]; // at 0x0
} GXFogAdjTable;

void GXSetFog(GXFogType type, GXColor color, float start, float end, float near,
              float far);
void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, const Mtx44 proj);
void GXSetFogRangeAdj(GXBool enable, u16 center, const GXFogAdjTable* table);
void GXSetBlendMode(GXBlendMode mode, GXBlendFactor src, GXBlendFactor dst,
                    GXLogicOp op);
void GXSetColorUpdate(GXBool enable);
void GXSetAlphaUpdate(GXBool enable);
void GXSetZMode(GXBool enableTest, GXCompare func, GXBool enableUpdate);
void GXSetZCompLoc(GXBool beforeTex);
void GXSetPixelFmt(GXPixelFmt pixelFmt, GXZFmt16 zFmt);
void GXSetDither(GXBool enable);
void GXSetDstAlpha(GXBool enable, u8 alpha);
void GXSetFieldMask(GXBool enableEven, GXBool enableOdd);
void GXSetFieldMode(GXBool texLOD, GXBool adjustAR);


#ifdef __cplusplus
}
#endif
#endif
