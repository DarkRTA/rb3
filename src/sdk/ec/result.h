#ifndef EC_RESULT_H
#define EC_RESULT_H

enum ECResult {
    ECResult_Success = 0,

    ECResult_Failure = -1,

    ECResult_InvalidBufHeap = -4004,
};

#define EC_SUCCESS(expr) ((expr) >= 0)
#define EC_FAIL(expr) ((expr) < 0)

#endif
