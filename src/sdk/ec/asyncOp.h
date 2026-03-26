#ifndef RVL_EC_ASYNCOP_H
#define RVL_EC_ASYNCOP_H

#include <ec/result.h>
#include <ec/string.h>
#include <ec/internal/shr.h>

class ECAsyncOpEnv;
class ECAsyncOp;

class ECAsyncOpEnv {
public:
    _SHRThread *opThread; //offset 0x4, size 0x4
    int unk0x4c; //offset 0x4c, size 0x4. maybe cached balance?
    bool unk0x50; //offset 0x50, size 0x1
    ECString unk0xc0; //offset 0xc0, size 0x4
    bool unk0x174; //offset 0x174, size 0x1
    ECString m_AppId; //offset 0x178, size 0x4
    ECString m_TIN; //offset 0x184, size 0x4
    int unk0x190; //offset 0x190, size 0x4 (need to check this)
    ECResult init();
    ~ECAsyncOpEnv();
    ECResult checkParentalControlPassword(char const *, long *);
    void lock();
    void unlock();
    void lockProgress();
    void unlockProgress();
    ECResult shutDown();
};

namespace ec {
    ECAsyncOpEnv *op;
}

#endif