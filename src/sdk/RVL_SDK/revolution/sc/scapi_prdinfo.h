#ifndef RVL_SDK_SC_SCAPI_PRDINFO_H
#define RVL_SDK_SC_SCAPI_PRDINFO_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

#define SC_PRDINFO_SIZE 0x100

typedef s8 SCProductArea;
enum SCProductArea_et {
    SC_AREA_JPN,
    SC_AREA_USA,
    SC_AREA_EUR,
    SC_AREA_AUS,
    SC_AREA_BRA,
    SC_AREA_TWN,
    SC_AREA_KOR,
    SC_AREA_HKG,
    SC_AREA_ASI,
    SC_AREA_LTN,
    SC_AREA_SAF,
    SC_AREA_CHN
};

typedef s8 SCProductGameRegion;
enum SCProductGameRegion_et {
    SC_PRD_GAME_REG_JP,
    SC_PRD_GAME_REG_US,
    SC_PRD_GAME_REG_EU,
    SC_PRD_GAME_REG_DEBUG,

    SC_PRD_GAME_REG_KR,
    SC_PRD_GAME_REG_CN,

    SC_PRD_GAME_REG_MAX,
    SC_PRD_GAME_REG_NULL	= -1
};


typedef struct SCArea {
    SCProductArea area; // at 0x0
    char name[4];       // at 0x1
} SCArea;

typedef struct SCRegion {
    SCProductGameRegion region; // at 0x0
    char name[3];               // at 0x1
} SCRegion;

BOOL __SCF1(const char* type, char* buf, u32 sz);
BOOL SCGetProductAreaString(char* buf, u32 sz);
BOOL SCGetProductGameRegionString(char* buf, u32 sz);
SCProductGameRegion SCGetProductGameRegion(void);
SCProductArea SCGetProductArea(void);

#ifdef __cplusplus
}
#endif
#endif
