#include "dwc_svl.h"
#include "dwc_common/dwc_memfunc.h"
#include "dwcsec_auth/dwc_auth_interface.h"

int* s_svlresult;

void DWC_SvlGetTokenAsync(int i, int* j) {
    s_svlresult = j;
    DWCi_Auth_Svl_StartAuthentication(i, DWC_Alloc, DWC_Free);
}

int DWC_SvlProcess(void) {
    if (DWCi_Auth_IsFinished()) {
        if (DWCi_Auth_IsSucceeded()) {
            if (s_svlresult != NULL) {
                DWCi_Auth_GetSvlResult();
            }
        } else {
            if (DWCi_Auth_GetErrorCode() + 20110 < 10) {

            }
        }
    } else {
        DWCi_Auth_ProcessAuthentication();
        return 2;
    }
}

void DWC_SvlAbort(void) { DWCi_Auth_AbortAuthentication(); }
