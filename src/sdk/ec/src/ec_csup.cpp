#include <ec/csup.h>

int EC_GetCustomerSupportCode(int p1) {
    int code;
    if (p1 >= 0) {
        code = 0;
    } else {
        code = 200000;
        if (-p1 <= 9999) {
            code = code - p1;
        }
    }
    return code;
}

namespace ec {
    unsigned long getExternalErrCode(ECProgress *progress) {
        ECResult status = progress->status;
        long errCode = progress->errCode;
        if (ECResult_WebServiceResError < status) {
            if (status != ECResult_WebServiceError) {
                if (status < ECResult_WebServiceError) {
                    if (status == ECResult_InvalidECard) goto label1;
                } else if (status == ECResult_NotDone || (-4010 < status && ECResult_Failure < status)) {
                    errCode = 0;
                    goto label3;
                }
                goto label2;
            }
            goto label1;
        }
        if (status == ECResult_TitleOwned) goto label1;
        if (status < ECResult_TitleOwned) {
            if (status == ECResult_InsufficientFunds) goto label1;
        } else if (status == ECResult_AgeRestricted) goto label1;
        if (status == ECResult_NotRegistered) {
            if (errCode <= 0) goto label2;
label1:
            if (errCode <= 0) goto someLabel;
            errCode = errCode + 205000;
            if (206999 < errCode) errCode = 205000;
            goto label3;
        }
label2:
        if ((status == ECResult_ContentRecvErr || status == ECResult_ECFail || status == ECResult_RecvWSErr) && errCode < 0) {
            errCode = 200000 - errCode;
            if (204999 < errCode) errCode = 200000;
            goto label3;
        }
someLabel:
        if (status < ECResult_Success && (errCode = 200000 - status, 204999 < errCode)) {
            errCode = 200000;
        }
label3:
        if (errCode == 0) return 0;
        if (9998 >= errCode - 200001U) return -(errCode - 200000);
        return -10000;
    };
}