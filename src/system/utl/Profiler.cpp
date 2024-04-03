#include "Profiler.h"
#include "os/Debug.h"
#include "utl/MakeString.h"

Profiler::Profiler(const char* name, int countMax) : mName(name), mMin(3.4028235E+38f), mMax(0), mSum(0), mCount(0), mCountMax(countMax) {}

void Profiler::Start() {
    mTimer.Start();
}

extern char* FormatTime(float);

void Profiler::Stop() {
    if (mCountMax == 1) {

    } else {
        TheDebug << MakeString("%s: min %s max %s mean %s\n", mName, FormatTime(mMin), FormatTime(mMax), FormatTime(mSum));
    }
    mTimer.Reset();
}
