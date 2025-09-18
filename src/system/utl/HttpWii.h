#pragma once
#include "obj/Data.h"
#include "os/Timer.h"

#define NUM_HTTPWII_HANDLES 10

extern "C" {
void *CommerceEcAlloc(int, int);
void *CommerceEcFree(void *);
}

enum NHTTPError {
    NHTTP_NUM_ERRORS = 0x10,
    NHTTP_ERROR_SYSTEM = -1
};

class HttpWii {
public:
    HttpWii();
    ~HttpWii();

    void Init();
    void Start();
    void Stop();
    int GetStatus();
    int GetFileAsync(const char *, void *, int);
    int CompleteAsync(int, unsigned long &);
    int CancelAsync(int task);
    int CancelAsyncAll();

    static void CleanupCallback();
    static const char *GetNHTTPErrorString(NHTTPError err);

    bool mServerVerifySSL;
    bool mUseSSL;
    bool mUseFileLoad;
    char *mRootCA;
    unsigned long mCertSize;
    DataArray *mServerInfo;
    void *mDataBuffer;
    int mDataBufferSize;
    void *mHandles[NUM_HTTPWII_HANDLES];
    unsigned int mLastReceived[NUM_HTTPWII_HANDLES];
    Timer mTimeout[NUM_HTTPWII_HANDLES];
    int mStatus; // ??
};

extern HttpWii TheHttpWii;
