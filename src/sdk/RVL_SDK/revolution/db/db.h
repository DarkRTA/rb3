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
void __DBExceptionDestinationAux(void);
void __DBExceptionDestination(void);
BOOL __DBIsExceptionMarked(u8 exc);
void DBPrintf(const char* msg, ...);

#ifdef __cplusplus
}
#endif
#endif
