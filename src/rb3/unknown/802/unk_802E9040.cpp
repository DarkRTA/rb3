#include "AsyncTask.h"

AsyncTask::AsyncTask(ArkFile *ark, void *v, int i1, int i2, int i3, int i4, const char *cc)
    : mArkfileNum(i1), mBlockNum(i2), mOffsetStart(i3), mOffsetEnd(i4), mBuffer(v), unk14((char *)cc), mOwner(ark) {
}
