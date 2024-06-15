#include "BudgetScreen.h"

#include "system/os/Debug.h"
#include "system/os/Debug.h"
#include "system/utl/Option.h"
#include "system/synth/StandardStream.h"

#include "decomp.h"

bool gUseSsv;

DECOMP_FORCEACTIVE(BudgetScreen,
    " ",
    "\n"
)

Distribution::Distribution(float res) : mRes(res) {
    MILO_ASSERT(mRes > 0.0f, 70);
    Reset();
}

void Distribution::Reset() {
    mCount = 0;
    mTotal = 0;
    mDist.clear();
    mDist.resize((int)(10 / mRes));
}

float Distribution::Pctile(float pct) {
    MILO_ASSERT(pct >= 0.f && pct <= 1.f, 84);

    float fCount = mCount;
    int total = 0;
    for (int i = 0; i < mDist.size(); i++) {
        total += mDist[i];

        float tmp = fCount * pct;
        if (total >= tmp) {
            return mRes * (i + 1);
        }

        if (total == mCount) {
            return mRes * (i + 1);
        }
    }

    MILO_NOTIFY_ONCE("something went wrong in pctile calculation\n");
    return 0.0f;
}

inline void Distribution::asdkjf(TextStream& stream, float min, float defaultMean, float max, const char* fmt) {
    float mean = mCount != 0 ? mTotal / mCount : defaultMean;
    stream << MakeString(fmt, min, mean, max);
}

void Distribution::Report(TextStream& stream, const char* tag) {
    MILO_ASSERT(tag || !gUseSsv, 103);

    if (!gUseSsv) {
        // this is stupid lol
        asdkjf(stream, mMin, 0.f, mMax, "Min/Mean/Max: %.2f/%.2f/%.2f\n");
        // float mean = mCount != 0 ? mTotal / mCount : 0.f;
        // stream << MakeString("Min/Mean/Max: %.2f/%.2f/%.2f\n", mMin, mean, mMax);
    }
    if (!gUseSsv) {
        stream << "Distribution:\n";
    }

    int acc = mCount;
    float start = mRes * (mDist.size() - 1);
    for (int i = mDist.size() - 1; i >= 0; i--, start -= mRes) {
        int hitCount = mDist[i];
        if (hitCount == 0)
            continue;

        float res = mRes;
        if (gUseSsv) {
            stream << MakeString("%s;[%.1f,%.1f);%d;%3.1f\n", tag, start, start + res, hitCount, (float)(acc * 100) / mCount);
        } else {
            stream << MakeString(" [%.1f, %.1f): %5d (%3.1f%%)\n", start, start + res, hitCount, (float)(acc * 100) / mCount);
        }

        acc -= mDist[i];
        if (acc == 0) {
            break;
        }

        MILO_ASSERT(acc > 0, 136);
    }
}

void Distribution::operator<<(float value) {
    if (value < 0) {
        return;
    }

    if (mCount == 0) {
        mMax = value;
        mMin = value;
    } else {
        if (value < mMin) {
            mMin = value;
        }
        if (mMax < value) {
            mMax = value;
        }
    }

    int pos = value / mRes;
    if (pos >= mDist.size()) {
        mDist.resize(pos * 2);
    }

    mDist[pos] += 1;
    mCount++;
    mTotal += value;
}

BudgetScreen::BudgetScreen() :
    mTestPanel(nullptr), mFrameInc(0.0), mLastCpu(0.0),
    mPollDist(0.1), mCpuDist(0.1), mGsDist(0.1), mUnk2(0.1),
    mRecordStartTick(0), mRecordEndTick(1000000),
    mTests(SystemConfig("tests")), mTestIdx(0),
    mWorstOnly(OptionBool("worst_only", false)),
    mWorstCpuPctile(0.0),
    mWorstGsPctile(0.0),
    mUnk3(0)
{
    // TheSongMgr.AddSongs(SystemConfig("songs"))
    // TheContentMgr.UnregisterCallback(TheSongMgr.field7_0x1c, false);

    const char* logFile = OptionStr("budget_log", SystemConfig("log_file")->Str(1));
    mLog = new TextFileStream(logFile, false);

    std::list<int> list(1000);
    if (!list.empty())
        list.clear();

    int useSsv = SystemConfig("dump_csv")->Int(1);
    StandardStream::sReportLargeTimerErrors = false;
    gUseSsv = useSsv;
}
