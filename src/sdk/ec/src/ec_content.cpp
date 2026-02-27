/*#include <ec/content.h>


ECResult ec::downloadUcsFule(const ECAsyncOpEnv &env, const ECString &str, char *param3, unsigned char *param4, unsigned long &param5) {
    char *pcVar5;
    unsigned long uVar6;
    unsigned long locala8;
    AsyncOpThread *localb0;
    unsigned long locala4;
    ECResult status;
    locala8 = param5;
    localb0 = env.opThread + 0x2c;
    locala4 = 0;
    status = ECResult_Success;
    if (!param4 || locala8 == 0) {
        status = ECResult_InvalidBufHeap;
    }
    pcVar5 = (char *)status;
    if (status == ECResult_Success) {

    }
    return status;
}


ec::Buffer::~Buffer() {}

ec::Content<ec::Buffer>::~Content() {}


void ECAsyncOp::setErrInfo(long param1, const char *msg) {
    char buffer [32];
    if (param1 != 0) {
        snprintf(buffer, 0x20, "%d", param1);
        setErrInfo(buffer, msg);
    } else {
        setErrMsg(msg);
        
    }
    return;
}

ec::ImportBuf::~ImportBuf() { close(); }

ec::Content<ec::ImportBuf>::~Content() {}

ECResult ec::getTmd(const ECAsyncOpEnv &env, const ECString &str, unsigned short *param3, unsigned char *&param4, unsigned long &param5, unsigned char *&param6, unsigned long &param7) {
    char *buffer;
    if (param3) {
        snprintf(buffer, 0xd, ".%u", param3);
    }
}








*/
