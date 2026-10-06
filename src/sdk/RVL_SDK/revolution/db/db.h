#ifndef RVL_SDK_DB_H
#define RVL_SDK_DB_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct OSDebugInterface;

extern struct OSDebugInterface* __DBInterface;
extern BOOL DBVerbose;

void DBInit(void);
void DBInitComm(void * ,int *);
u32 DBQueryData(void);
BOOL DBRead(void *dst, u32 size);
BOOL DBWrite(const void *src, u32 size);
void DBClose(void);
void DBOpen(void);
void DBInitInterrupts(void);
void __DBExceptionDestinationAux(void);
void __DBExceptionDestination(void);
BOOL __DBIsExceptionMarked(u8 exc);
void DBPrintf(const char* msg, ...);

#ifdef __cplusplus
}
#endif
#endif
