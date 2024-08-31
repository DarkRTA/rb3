#include "dwc_naslogin.h"
#include "dwc_common/dwc_error.h"
#include "dwcsec_auth/dwc_auth_interface.h"

s32 s_nasstate;

void DWC_NasLoginAsync(void) {
    s_nasstate = 4;
    DWCi_Auth_StartAuthentication("\0", "", 0, DWC_Alloc, DWC_Free);
}

int DWC_NasLoginProcess() {
    switch (s_nasstate) {
        case 1: return 3;
        case 2: return 5;
        case 3: return 4;
        case 4:
            DWCi_Auth_ProcessAuthentication();
            if (DWCi_Auth_IsFinished()) {
                if (DWCi_Auth_IsSucceeded()) {
                    s_nasstate = 1;
                    return 3;
                } else {
                    s_nasstate = 3;
                    DWCi_SetError(2, DWCi_Auth_GetErrorCode());
                    return 4;
                }
            } else return 2;
        default:
        return 4;
    }
}

void DWC_NasLoginAbort(void) {
    DWCi_Auth_AbortAuthentication();
    s_nasstate = 2;
}
