#include "dwc_report.h"
#include "types.h"
#include <revolution/os/OSError.h>
#include <stdarg.h>

static u32 sReportLevel = 0;

void DWC_SetReportLevel(int level) {
    sReportLevel = level;
}

void DWC_Printf(int id, const char* format, ...) {
    va_list args;
    if ((id & sReportLevel) == 0) return;
    switch (id) {
        case 0x1:   OSReport("DWC_INFO     :"); break;
        case 0x2:   OSReport("++DWC_ERROR  :"); break;
        case 0x4:   OSReport("DWC_DEBUG    :"); break;
        case 0x8:   OSReport("DWC_WARN     :"); break;
        case 0x10:  OSReport("DWC_ACHECK   :"); break;
        case 0x20:  OSReport("DWC_LOGIN    :"); break;
        case 0x40:  OSReport("DWC_MATCH_NN :"); break;
        case 0x80:  OSReport("DWC_MATCH_GT2:"); break;
        case 0x100: OSReport("DWC_TRANSPORT:"); break;
        case 0x200: OSReport("DWC_QR2_REQ  :"); break;
        case 0x400: OSReport("DWC_SB_UPDATE:"); break;
        case 0x8000:OSReport("DWC_SEND     :"); break;
        case 0x10000:   OSReport("DWC_RECV     :"); break;
        case 0x20000:   OSReport("DWC_UPDATE_SV:"); break;
        case 0x40000:   OSReport("DWC_CONNECTINET:"); break;
        case 0x1000000: OSReport("DWC_AUTH     :"); break;
        case 0x2000000: OSReport("DWC_AC       :"); break;
        case 0x4000000: OSReport("DWC_BM       :"); break;
        case 0x8000000: OSReport("DWC_UTIL     :"); break;
        case 0x10000000:OSReport("DWC_OPTION_CF:"); break;
        case 0x20000000:OSReport("DWC_OPTION_CONNTEST:"); break;
        case 0x80000000:OSReport("DWC_GAMESPY  :"); break;

        default: OSReport("DWC_UNKNOWN  :"); break;
    }
    va_start(args, format);
    OSVReport(format, args);
}
