#ifndef EC_ASYNCOP_H
#define EC_ASYNCOP_H

#include <ec/string.h>
#include <ec/internal/shr.h>
#include <ec/vector.h>
#include <ec/mem.h>

void *asyncOpThreadFunc(void *arg);

namespace ec {
    class ECNamValStr : public ECString {
    public:
        ECString field0xc;
        ECNamValStr();
        ~ECNamValStr();
    };
}

struct ECAsyncOpArg {
    int field0x0;
    int *field0x4;
    ECString *field0x8;
    unsigned long field0xc;
    int field0x10;
    int field0x14;
    int field0x18;
    int field0x1c;
    int field0x20;
    int field0x24;
    int field0x28;
    int field0x2c;
    int field0x30;
    ec::ECBufHeapMeta *bufHeap; //0x34
    void *field0x38;
};

struct AsyncOpThread : public _SHRThread {
    int field0x2c;
};

class ECObj {
    public:
    void operator delete(void *);
};

class ECAsyncOp : public ECObj {
public:
    //ECAsyncOpEnv *env;
    long field0x4; //0x4
    ECString method; //0x8
    long field0x14; //0x14
    int field0x18; //0x18
    int field0x1c;
    ECResult status; //0x20
    int field0x24;
    int field0x28; //0x28
    u8 pad5[0x4];
    unsigned long field0x30;
    unsigned long downloadSize;
    int field0x38;
    u8 pad6[0x4];
    char field0x3c;
    u8 pad7[0x77];
    char field0xbb;
    int field0xbc;
    char &__vt;
    u8 padf[0x3];
    int field0xc4;
    int field0xc8;
    int *field0xcc;
    ECString *field0xd0;
    int field0xd4;
    int field0xd8;
    int field0xdc;
    int field0xe0;
    int field0xe4;
    int field0xe8;
    int field0xec;
    int field0xf0;
    int field0xf4;
    ec::ECBufHeapMeta *field0xf8;
    void *pvVar; //0xfc
    ec::ECBufHeapMeta field0x100;
    const char *field0x108;
    unsigned long field0x10c;
    int field0x110;
    int field0x114;
    int field0x118;
    int field0x11c;
    const char *field0x120;
    void setErrMsg(const char* msg);
    void setErrInfo(const char*, const char*);
    void setErrInfo(long, const char*);
    void setTotalSize(unsigned long);
    void incDownloadedSize(unsigned long);
    ECResult init(long param1, ECAsyncOpArg *asyncOpArg);
    void setFinalStatus(long param1);
    void dump();
    ~ECAsyncOp();
};

class ECAsyncOpEnv {
    public:
    int field0x0;
    AsyncOpThread *opThread;
    _SHRThread *opThread1;
    int field0xc;
    ECString ecsUrl;
    ECString iasUrl;
    ECString casUrl;
    ECString ccsUrl;
    ECString ucsUrl;
    unsigned int points;
    bool field0x50; //got points?
    u8 pad1[0x14];
    ECString field0x68;
    ECString field0x74;
    int field0x80;
    int field0x84;
    int field0x88;
    int field0x8c;
    int field0x90;
    int field0xbc;
    u8 pad2[0x28];
    ECString field0xc0;
    ECString field0xcc;
    ECString field0xd8;
    ECString field0xe4;
    ECString field0xf0;
    ECString field0xfc;
    ECString field0x108;
    ECString field0x114;
    ECString field0x120;
    ECString field0x12c;
    ECString field0x138;
    ECString field0x144;
    u8 pad3[0x28];
    int field0x150;
    int field0x154;
    int field0x158;
    int field0x15c;
    int field0x160;
    u8 pad4[0x4];
    int field0x164;
    u8 padd[0xc];
    bool field0x170;
    bool field0x171;
    bool field0x172;
    bool field0x173;
    int field0x174;
    ECString field0x184;
    u8 pad5[0xc];
    ECVector<ec::ECNamValStr> *vector1;
    u8 currTitleId[0x8];
    ECString field0x1b0;
    ECString field0x1bc;
    u8 pad7[0x8];
    ECString field0x1d0;
    u8 pad8[0x48];
    ECString field0x224;
    ECString field0x230;
    ECString field0x23c;
    bool field0x25a;
    bool field0x25b;
    u8 pad9[0x10];
    ECString field0x260;
    ECAsyncOpEnv();
    ~ECAsyncOpEnv();
    ECResult init();
    ECResult shutDown();
    void lock();
    void unlock();
    void lockProgress();
    void unlockProgress();
    void dispatchOp(ECAsyncOp *op);
    void post(ECAsyncOp *op);
    void start(ECAsyncOp *op, ECAsyncOpArg *arg);
    void clearOpCaches();
    void getDeviceInfo();
    void getKeyPairStatus();
    void setDeviceToken(const char *token);
    void setDeviceToken(ECString &token);
    void setNamedValue(const char *name, const char *value);
    int saveConfig();
    void getConfig();
    void getDevId();
    void getDevCert();
    void getCRL(bool unk);
    bool checkParentalControlPassword(const char *unk1, long code);
    void getParentalControlInfo();
    void getCountry();
    void getRegion();
    void getLanguage();
    void getSerialNumber();
    void getFileSystemStatus();
    void getWifiMac(char *unk);
    void getBluetoothMac(char *unk);
    int getFreeChannelAppCount();
    int setWebSvcUrls(const char* ecsUrl, const char* iasUrl, const char* casUrl);
    int setContentUrls(const char* ccsUrl, const char* ucsUrl);
    void setErrInfo(const char*, const char*);
};

namespace ec {
    ECAsyncOpEnv op;
}



#endif // EC_ASYNCOP_H
