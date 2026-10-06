#include <ec/asyncOp.h>

class ECList : public ECAsyncOp {
private:
    char padding[0xc4];
    long unkc4;
    long unkc8;
    long *unkcc;
    long unkd0;
public:
    int init(long, ECAsyncOpArg *);
};

class ECListArg {
    ECListArg(unsigned long, unsigned long *, unsigned long *);

    unsigned long unk0; // 0
    unsigned long *unk4; // 4
    unsigned long *unk8; // 8
    ECResult status; // c
};