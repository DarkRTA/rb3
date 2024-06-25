#include "BudgetScreen.h"

#include "system/os/Debug.h"
#include "system/os/Timer.h"
#include "system/ui/UI.h"
#include "system/utl/Option.h"
#include "system/rndobj/Rnd.h"
#include "system/synth/StandardStream.h"

#include "band3/game/SongDB.h"
#include "band3/meta_band/BandSongMgr.h"

#include <algorithm>
#include "decomp.h"

extern int gMainFree;
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
    float res;
    int i;
    for (i = mDist.size() - 1, res = mRes; i >= 0; i--, res = mRes, start -= mRes) {
        int hitCount = mDist[i];
        if (hitCount == 0)
            continue;

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

float Average(std::vector<float>& items, bool partial) {
    std::sort(items.begin(), items.end());

    // for whatever reason this needs to be up here to match?
    std::vector<float>::iterator it;

    int size = items.size();
    int endOffset = partial ? (int)(size * 0.3f) : 0;

    float total = 0;
    for (it = items.begin(); it != items.end() - endOffset; ++it) {
        total += *it;
    }

    return total / (size - endOffset);
}

BudgetScreen::BudgetScreen() :
    mTestPanel(nullptr), mLastCpu(0.0), mLastGpu(0.0),
    mCpuDist(0.1), mGsDist(0.1), mHudDist(0.1), mEtcDist(0.1),
    mRecordStartTick(0), mRecordEndTick(1000000),
    mTests(SystemConfig("tests")), mTestIdx(0),
    mWorstOnly(OptionBool("worst_only", false)),
    mWorstCpuPctile(0.0),
    mWorstGsPctile(0.0),
    mSampleCount(0)
{
    TheSongMgr->AddSongs(SystemConfig("songs"));
    TheContentMgr->UnregisterCallback(TheSongMgr, false);

    const char* logFile = OptionStr("budget_log", SystemConfig("log_file")->Str(1));
    mLog = new TextFileStream(logFile, false);

    // yes there's just a random list here lol
    { std::list<int> list(10000); }

    int useSsv = SystemConfig("dump_scsv")->Int(1);
    StandardStream::sReportLargeTimerErrors = false;
    gUseSsv = useSsv;
}

void BudgetScreen::Enter(UIScreen* screen) {
    mCpuDist.Reset();
    mGsDist.Reset();
    mHudDist.Reset();
    mEtcDist.Reset();
    TheTaskMgr.ClearTasks();

    mTestPanel = nullptr;
    UIScreen::Enter(screen);
    mTestPanel = mTypeDef->FindArray("test_panel", true)->Obj<UIPanel>(1);

    TheRnd->SetGSTiming(true);
    TheRnd->BeginDrawing();
    TheRnd->EndDrawing();

    std::vector<float> cpuTimes;
    std::vector<float> gsTimes;

    for (int i = 0; i < 100; i++) {
        TheRnd->BeginDrawing();
        TheRnd->EndDrawing();

        TheRnd->BeginDrawing();
        cpuTimes.push_back(AutoTimer::GetTimer("cpu")->GetLastMs());
        gsTimes.push_back(AutoTimer::GetTimer("gs")->GetLastMs());
        TheRnd->EndDrawing();
    }

    mNullCpu = Average(cpuTimes, false);
    mNullGs = Average(gsTimes, true);

    TheTaskMgr.SetSeconds(0, false);

    TheRnd->BeginDrawing();
    mTestPanel->Draw();
    TheRnd->EndDrawing();

    // TODO: This doesn't seem quite right...
    // Should probably be mEndTime and mFrameInc
    mTime = TheSongDB->GetSongDurationMs() / 1000.0f;
    mEndTime = Property("frame_inc", true)->Float(nullptr);

    mLastGpu = 0;
    mLastCpu = 0;
    mSampleCount = 0;

    DataArray* test = mTests->Array(mTestIdx)->FindArray("init", false);
    if (test != nullptr) {
        test->ExecuteScript(1, nullptr, nullptr, 1);
    }
}
inline float GetLastTimerMs(const char* name) {
    return AutoTimer::GetTimer(name)->GetLastMs();
}

void BudgetScreen::Poll() {
    UIScreen::Poll();
    START_AUTO_TIMER("budget_screen_poll");

    static DataArray* timerScript = SystemConfig("rnd")->FindArray("timer_script", false);
    if (timerScript)
        timerScript->ExecuteScript(1, nullptr, nullptr, 1);

    float tick = TheSongDB->GetSongData()->GetTempoMap()->TimeToTick(TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f);

    // needs to be used as a local variable
    Timer* slowFrameTimer = &Timer::sSlowFrameTimer;
    float slowFrameTime = slowFrameTimer->SplitMs();

    bool b = slowFrameTime > 0;
    b |= tick < mRecordStartTick || tick >= mRecordEndTick;

    float cpuMs = GetLastTimerMs("cpu") - mNullCpu;
    float animMs = GetLastTimerMs("anim");
    float worldMs = GetLastTimerMs("world");
    float pollMs = GetLastTimerMs("budget_screen_poll");
    float cpuDist = animMs + (cpuMs - worldMs - pollMs);

    float gsMs = GetLastTimerMs("gs") - mNullGs;

    float hudTrackMs = GetLastTimerMs("hud_track");
    float hudDist = animMs + hudTrackMs;

    float gameEtcMs = GetLastTimerMs("game_etc");

    if (!b) {
        if (mSampleCount > 0) {
            mCpuDist << (cpuDist + mLastCpu) / 2;
            mGsDist << (gsMs + mLastGpu) / 2;
            mHudDist << (hudDist + mLastHud) / 2;
            mEtcDist << (gameEtcMs + mLastEtc) / 2;
        } else {
            mCpuDist << cpuDist;
            mGsDist << gsMs;
            mHudDist << hudDist;
            mEtcDist << gameEtcMs;
        }

        mLastCpu = cpuDist;
        mLastGpu = gsMs;
        mLastHud = hudDist;
        mLastEtc = gameEtcMs;
        mSampleCount++;
    }

    if (tick >= mRecordEndTick) {
        if (!gUseSsv) {
            const char* testName = mTests->Array(mTestIdx)->Str(0);
            *mLog << "START TEST: " << testName;

            float gpuPctile = mGsDist.Pctile(0.99f);
            float cpuPctile = mCpuDist.Pctile(0.99f);
            *mLog << " [cpu " << cpuPctile << "] [gpu " << gpuPctile << "]\n";

            *mLog << "Cpu overhead: " << mNullCpu << "\n";
            *mLog << "Gs overhead: " << mNullGs << "\n";

            mLog->mFile.Flush();

            *mLog << "\nCpu "; mCpuDist.Report(*mLog, nullptr);
            *mLog << "\nGpu "; mGsDist.Report(*mLog, nullptr);
            *mLog << "\nHUD/Track "; mHudDist.Report(*mLog, nullptr);
            *mLog << "\nGame Etc. "; mEtcDist.Report(*mLog, nullptr);
        }

        gMainFree = HeapFreeSize("main");

        float cpuPctile = mCpuDist.Pctile(0.99f);
        if (cpuPctile > mWorstCpuPctile) {
            mWorstCpuPctile = cpuPctile;
            mWorstCpuName = mTests->Array(mTestIdx)->Str(0);
        }

        float gsPctile = mGsDist.Pctile(0.99f);
        if (gsPctile > mWorstGsPctile) {
            mWorstGsPctile = gsPctile;
            mWorstGsName = mTests->Array(mTestIdx)->Str(0);
        }

        UIScreen* stopScreen = ObjectDir::Main()->Find<UIScreen>("stop_budget", true);
        TheUI->GotoScreen(stopScreen, false, false);
    }
}

// Must be down here to avoid data pooling in Poll
int gMainFree;
