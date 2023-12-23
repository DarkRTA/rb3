#include "asynctask.hpp"
#include "arkfile.hpp"

AsyncTask::AsyncTask(ArkFile *ark, void *v, int i1, int i2, int i3, int i4, const char *cc)
    : unk0(i1), unk4(i2), unk8(i3), unkc(i4), unk10(v), unk14((char *)cc), unk18(ark) {
}