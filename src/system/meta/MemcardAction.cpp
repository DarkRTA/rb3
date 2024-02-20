#include "MemcardAction.h"

MemcardAction::MemcardAction(Profile* p) : unk_04(12), mBuf(0), mBufLen(-1), unk_10(p), unk_14(0), unk_18(-1), unk_1c(-1), unk_20(0) {}

void MemcardAction::SetBuffer(char* c, int i) {
    mBuf = c;
    mBufLen = i;
}
