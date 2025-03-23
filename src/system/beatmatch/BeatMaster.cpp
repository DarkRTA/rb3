#include "beatmatch/BeatMaster.h"
#include "beatmatch/SongData.h"
#include "beatmatch/Output.h"
#include "beatmatch/Playback.h"
#include "beatmatch/MasterAudio.h"
#include "midi/DataEvent.h"
#include "midi/MidiParserMgr.h"
#include "os/System.h"
#include "utl/BeatMap.h"
#include "utl/SongInfoCopy.h"
#include "synth/Synth.h"
#include "utl/TickedInfo.h"

BeatMaster::BeatMaster(SongData *data, int num_players)
    : mSongData(data), mRecording(0), mAudio(0), mMidiParserMgr(0), mSongInfo(0),
      mPtCfg(0), mLoader(0), mLoaded(0), unk2d(0), mHandlers(0) {
    mSongData->AddSink(this);
    DataArray *cfg = SystemConfig("beatmatcher");
    cfg->FindData("recording", mRecording, false);
    mHandlers = cfg->FindArray("callbacks", false);
    TheBeatMatchOutput.SetActive(mRecording);
    String str;
    if (cfg->FindData("playback", str, false)) {
        TheBeatMatchPlayback.LoadFile(str);
    }
    Reset();
    mAudio = new MasterAudio(cfg->FindArray("audio"), num_players, this, mSongData);
}

BeatMaster::~BeatMaster() {
    delete mMidiParserMgr;
    delete mAudio;
    delete mLoader;
}

void BeatMaster::RegisterSink(BeatMasterSink &sink) { mSinks.push_back(&sink); }

// fn_80457BB8
void BeatMaster::Load(
    SongInfo *info,
    int i,
    PlayerTrackConfigList *plist,
    bool b,
    SongDataValidate validate,
    std::vector<MidiReceiver *> *vec
) {
    mSongInfo = info;
    mPtCfg = plist;
    mMidiParserMgr = new MidiParserMgr(mSongData, info->GetName());
    std::vector<MidiReceiver *> midi_receivers;
    if (vec) {
        midi_receivers.insert(midi_receivers.begin(), vec->begin(), vec->end());
    }
    midi_receivers.push_back(mMidiParserMgr);
    mSongData->Load(info, i, plist, midi_receivers, b, validate);
    MILO_ASSERT(!mLoader, 0x82);
    mLoader = new BeatMasterLoader(this);
    mLoaded = false;
    unk2d = false;
    if (b)
        TheLoadMgr.PollUntilLoaded(mLoader, 0);
}

void BeatMaster::LoaderPoll() {
    if (!mLoaded && mSongData->Poll()) {
        mLoaded = true;
        mMidiParserMgr->FinishLoad();
    } else if (mLoaded && !unk2d) {
        unk2d = true;
        mAudio->Load(mSongInfo, mPtCfg);
        mSongInfo = 0;
    } else if (unk2d) {
        TheSynth->Poll();
        bool b1 = false;
        if (unk2d && mAudio->IsLoaded())
            b1 = true;
        if (b1)
            RELEASE(mLoader);
    }
}

bool BeatMaster::IsLoaded() {
    bool b = false;
    if (unk2d && mAudio->IsLoaded())
        b = true;
    return b;
}

void BeatMaster::AddTrack(
    int i, Symbol s, SongInfoAudioType atype, TrackType ttype, bool b
) {
    mSubmixIdxs.push_back(0);
}

void BeatMaster::Poll(float f) {
    if (TheBeatMatchPlayback.mCommands)
        TheBeatMatchPlayback.Poll(f);
    mSongPos = mSongData->CalcSongPos(f);
    for (int i = 0; i < mSinks.size(); i++) {
        mSinks[i]->UpdateSongPos(mSongPos);
    }
    mMidiParserMgr->Poll();
    float tick = mSongPos.mTotalTick;
    CheckBeat();
    CheckSubmixes(tick);
    mAudio->Poll();
}

float BeatMaster::SongDurationMs() {
    DataEventList *events = mMidiParserMgr->GetEventsList();
    for (int i = 0; i < events->Size(); i++) {
        const DataEvent &curEvent = events->Event(i);
        Symbol msgSym = curEvent.Msg()->Sym(1);
        if (msgSym == end) {
            float ftick = mSongData->GetBeatMap()->BeatToTick(curEvent.start);
            return mSongData->GetTempoMap()->TickToTime(ftick);
        }
    }
    return 0;
}

// fn_80458830
void BeatMaster::Jump(float f) {
    mSongPos = mSongData->CalcSongPos(f);
    mLastSongPos = mSongPos;
    mMidiParserMgr->Reset(mSongPos.mTotalTick);
    TheBeatMatchPlayback.Jump(f);
    float timeinloop = mSongData->GetTempoMap()->GetTimeInLoop(f);
    mAudio->Jump(timeinloop);
    mAudio->SetTimeOffset(f - timeinloop);
}

void BeatMaster::Reset() {
    mLastSongPos = SongPos();
    for (int i = 0; i < mSubmixIdxs.size(); i++) {
        mSubmixIdxs[i] = 0;
    }
    ExportInitialSubmixes();
    if (mMidiParserMgr)
        mMidiParserMgr->Reset();
    if (mRecording)
        TheBeatMatchOutput.Reset();
    TheBeatMatchPlayback.Jump(0);
    HandleBeatCallback("reset");
    ResetAudio();
}

void BeatMaster::ResetAudio() {
    if (mAudio) {
        if (mAudio->GetTime() != 0)
            mAudio->Jump(0);
    }
}

void BeatMaster::CheckBeat() {
    int curTotalBeat = mSongPos.GetTotalBeat();
    int lastTotalBeat = mLastSongPos.GetTotalBeat();
    if (lastTotalBeat != curTotalBeat) {
        static DataNode &beat = DataVariable("beat");
        beat = curTotalBeat;
        HandleBeatCallback("beat");
        for (int i = 0; i < mSinks.size(); i++) {
            mSinks[i]->Beat(mSongPos.GetMeasure(), mSongPos.GetBeat());
        }
    }
    if (mLastSongPos.GetMeasure() != mSongPos.GetMeasure()) {
        static DataNode &measure = DataVariable("measure");
        measure = mSongPos.GetMeasure();
        HandleBeatCallback("downbeat");
    }
    if ((mLastSongPos.GetTick() / 240) != (mSongPos.GetTick() / 240)) {
        HandleBeatCallback("eighth_note");
    }
    if ((mLastSongPos.GetTick() / 120) != (mSongPos.GetTick() / 120)) {
        HandleBeatCallback("sixteenth_note");
    }
    mLastSongPos = mSongPos;
}

void BeatMaster::ExportInitialSubmixes() {
    for (int i = 0; i < mSubmixIdxs.size(); i++) {
        TickedInfoCollection<String> &submixes = mSongData->GetSubmixes(i);
        if (submixes.Size() > 0) {
            const char *str = submixes.mInfos[0].mInfo.c_str();
            for (int j = 0; j < mSinks.size(); j++) {
                mSinks[j]->HandleSubmix(i, str);
            }
        }
    }
}

void BeatMaster::CheckSubmixes(int iii) {
    for (int i = 0; i < mSubmixIdxs.size(); i++) {
        TickedInfoCollection<String> &submixes = mSongData->GetSubmixes(i);
        while (true) {
            int curIdx = mSubmixIdxs[i];
            if (curIdx >= submixes.Size() || submixes.mInfos[curIdx].mTick > iii)
                break;
            const char *str = submixes.mInfos[curIdx].mInfo.c_str();
            for (int j = 0; j < mSinks.size(); j++) {
                mSinks[j]->HandleSubmix(i, str);
            }
            mSubmixIdxs[i]++;
        }
    }
}

void BeatMaster::HandleBeatCallback(Symbol s) {
    if (mHandlers) {
        DataArray *arr = mHandlers->FindArray(s, false);
        if (arr)
            arr->ExecuteScript(1, 0, 0, 1);
    }
}