#include "dwc_error.h"
#include "dwc_common/dwc_report.h"

int stDwcLastError = 0;
u32 stDwcErrorCode = 0;

u32 DWC_GetLastErrorEx(int* errCode, int* r4) {
    if (errCode != NULL) {
        *errCode = stDwcErrorCode;
    }
    if (r4 != NULL) {
        switch(stDwcLastError) {
            case 2:
            case 3:
            case 4:
            case 5:
            case 8:
            case 0xe:
            case 0x10:
            case 0x12:
            case 0x15:
                *r4 = 6; break;
            case 6:
                *r4 = 3; break;
            case 7:
                *r4 = 4; break;
            case 0xd:
                *r4 = 5; break;
            case 0x16:
                *r4 = 8; break;
            case 10:
            case 0xb:
            case 0xc:
            case 0x18:
                *r4 = 1; break;
            case 0xf:
            case 0x11:
            case 0x13:
            case 0x14:
            case 0x17:
            case 0x19:
                *r4 = 2; break;
            case 1:
            case 9:
                *r4 = 7; break;
            default:
                *r4 = 0; break;
        }
    }
    return stDwcLastError;
}

void DWC_ClearError(void) {
    if (stDwcLastError == 9) return;
    stDwcLastError = 0;
    stDwcErrorCode = 0;
}

void DWCi_SetError(int lastErr, int errCode) {
    if (stDwcLastError != 9) {
        stDwcLastError = lastErr;
        stDwcErrorCode = errCode;
    }
    if (lastErr != 9) return;
    DWC_Printf(-1, "FATALERROR_SET\n");
}
