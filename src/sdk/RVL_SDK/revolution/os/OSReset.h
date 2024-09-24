#ifndef RVL_SDK_OS_RESET_H
#define RVL_SDK_OS_RESET_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif


typedef int OSShutdownPass;
enum OSShutdownPass_et {
    OS_SHUTDOWN_PASS_FIRST,
    OS_SHUTDOWN_PASS_SECOND
};

typedef u32 OSShutdownEvent;
enum OSShutdownEvent_et {
    OS_SHUTDOWN_EVENT_FATAL,
    OS_SHUTDOWN_EVENT_1,
    OS_SHUTDOWN_EVENT_SHUTDOWN,
    OS_SHUTDOWN_EVENT_3,
    OS_SHUTDOWN_EVENT_RESTART,
    OS_SHUTDOWN_EVENT_RETURN_TO_MENU,
    OS_SHUTDOWN_EVENT_LAUNCH_APP,
};

typedef BOOL (*OSShutdownFunction)(OSShutdownPass pass, OSShutdownEvent event);

typedef struct OSShutdownFunctionInfo {
    OSShutdownFunction func;             // at 0x0
    u32 prio;                            // at 0x4
    struct OSShutdownFunctionInfo* next; // at 0x8
    struct OSShutdownFunctionInfo* prev; // at 0xC
} OSShutdownFunctionInfo;

typedef struct OSShutdownFunctionQueue {
    OSShutdownFunctionInfo* head; // at 0x0
    OSShutdownFunctionInfo* tail; // at 0x4
} OSShutdownFunctionQueue;

extern BOOL __OSIsReturnToIdle;

void OSRegisterShutdownFunction(OSShutdownFunctionInfo* info);
BOOL __OSCallShutdownFunctions(OSShutdownPass pass, OSShutdownEvent event);
void __OSShutdownDevices(OSShutdownEvent event);
void __OSGetDiscState(u8* out);
void OSShutdownSystem(void);
void OSReturnToMenu(void);
u32 OSGetResetCode(void);
void OSResetSystem(u32 arg0, u32 arg1, u32 arg2);

#ifdef __cplusplus
}
#endif
#endif
