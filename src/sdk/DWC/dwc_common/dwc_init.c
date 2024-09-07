#include "dwc_init.h"
#include "revolution/os/OS.h"
#include "dwc_common/dwc_memfunc.h"
#include "dwc_common/dwc_report.h"
#include "dwc_nonport/dwc_nonport.h"
#include "dwcsec_auth/dwc_auth_interface.h"
#include "types.h"
#include <string.h>

static u32 dwci_gamecode = 0;
static BOOL s_initialized = FALSE;

BOOL DWC_Init(int id, const char* name, int gamecode, DWCAllocExFunc alloc, DWCFreeFunc free) {
    #ifdef MILO_DEBUG
    OSRegisterVersion("<< RVL_SDK - DWCDL \trelease build: Apr 22 2010 18:57:59 (0x4302_162) >>");
    #else
    OSRegisterVersion("<< RVL_SDK - DWCDL \trelease build: Apr 22 2010 18:58:19 (0x4302_162) >>");
    #endif
    DWCi_SetMemFunc(alloc, free);
    #ifdef MILO_DEBUG
    DWC_SetReportLevel(-1);
    DWC_Printf(8, "================================\n");
    DWC_Printf(8, "- %s\n", "2_1_14");
    DWC_Printf(8, "--------------------------------\n");

    if (id != 1) {
        DWC_Printf(8, "\n");
        DWC_Printf(8, "********************************\n");
        DWC_Printf(8, "*YOU ARE USING THE DEBUG SERVER*\n");
        DWC_Printf(8, "********************************\n");
        DWC_Printf(8, "*\n");
        DWC_Printf(8, "* Please note that you need to\n");
        DWC_Printf(8, "*   switch it to the RELEASE\n");
        DWC_Printf(8, "*  server with your FINALROM!\n");
        DWC_Printf(8, "*\n");
        DWC_Printf(8, "*******************************\n");
        DWC_Printf(8, "\n");
    }

    if (gamecode == 0x4E54524A) { // NTRJ
        DWC_Printf(8, "\n");
        DWC_Printf(8, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        DWC_Printf(8, "x        IS THIS DEMO?         x\n");
        DWC_Printf(8, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        DWC_Printf(8, "x\n");
        DWC_Printf(8, "x You are using the gameCode for\n");
        DWC_Printf(8, "x   demos. It is not allowed\n");
        DWC_Printf(8, "x  using this gameCode except\n");
        DWC_Printf(8, "x     in demos and testing.\n");
        DWC_Printf(8, "x\n");
        DWC_Printf(8, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        DWC_Printf(8, "\n");
    }

    if (name != NULL && !strcmp(name, "dwctest")) {
        DWC_Printf(8, "\n");
        DWC_Printf(8, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        DWC_Printf(8, "x        IS THIS DEMO?         x\n");
        DWC_Printf(8, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        DWC_Printf(8, "x\n");
        DWC_Printf(8, "x You are using the gameName for\n");
        DWC_Printf(8, "x   demos. It is not allowed\n");
        DWC_Printf(8, "x  using this gameName except\n");
        DWC_Printf(8, "x     in demos and testing.\n");
        DWC_Printf(8, "x\n");
        DWC_Printf(8, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
        DWC_Printf(8, "\n");
    }
    #endif

    if (!DWCi_Auth_InitInterface(id)) {
        DWC_Printf(8, "Failed to initialize auth interface.\n");
        return -1;
    } else {
        dwci_gamecode = gamecode;
        s_initialized = TRUE;
        DWCi_Np_GetConsoleId();
        return FALSE;
    }
}

void DWC_Shutdown(void) {
    s_initialized = FALSE;
}
