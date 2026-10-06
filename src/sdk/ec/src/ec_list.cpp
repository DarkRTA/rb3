#include <ec/list.h>

ECListArg::ECListArg(unsigned long p1, unsigned long *p2, unsigned long *p3) {
    unk0 = p1;
    unk4 = p2;
    unk8 = p3;
    status = ECResult_Success;
    if (p2)
        return;
    status = ECResult_InvalidBufHeap;
}

int ECList::init(long p1, ECAsyncOpArg *arg) {
    int ret = ECList::ECAsyncOp::init(p1, arg);
    if (ret == 0) {
        unkc4 = arg->unk0;
        unkc8 = *arg->unk4;
        unkcc = arg->unk4;
        *unkcc = 0;
        unkd0 = arg->unk8;
    }
    return ret;
}
