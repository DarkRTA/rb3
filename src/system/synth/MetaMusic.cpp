#include "synth/MetaMusic.h"
#include "synth/Synth.h"
#include "synth/FxSendEQ.h"
#include "os/PlatformMgr.h"
#include "utl/Symbols.h"

void MetaMusicLoader::DoneLoading() {}

inline MetaMusicLoader::MetaMusicLoader(File *f, int &bytes, unsigned char *buf, int size)
    : Loader(FilePath(""), kLoadFront), mFile(f), mBytesRead(bytes), mBuf(buf),
      mBufSize(size) {
    MILO_ASSERT(mFile, 0x2A);
    mState = OpenFile;
}

MetaMusic::MetaMusic(const char *cc)
    : mStream(0), mLoop(0), mFadeTime(1.0f), mVolume(0), mPlayFromBuffer(1), mRndHeap(0),
      mBufferH(0), mBuf(0), mFile(0), mBufSize(0), mBytesRead(0), mExtraFaders(this),
      mLoader(0), unk78(0), unk88(cc), unk8c(1) {
    mFader = Hmx::Object::New<Fader>();
    mFaderMute = Hmx::Object::New<Fader>();
}

MetaMusic::~MetaMusic() {
    RELEASE(mStream);
    UnloadStreamFx();
    RELEASE(mFile);
    RELEASE(mLoader);
    if (mRndHeap) {
        if (mBufferH) {
            mBufferH->Unlock();
            MemFreeH(mBufferH);
            mBufferH = 0;
        }
        mBuf = 0;
    } else if (mBuf) {
        _MemFree(mBuf);
        mBuf = 0;
    }
    delete mFader;
    delete mFaderMute;
}

void MetaMusic::Load(const char *cc, float f, bool b1, bool b2) {
    mLoop = b2;
    unk8c = b1;
    DataArray *cfg = SystemConfig("synth", "metamusic");
    cfg->FindData("fade_time", mFadeTime, true);
    cfg->FindData("volume", mVolume, true);
    mVolume += f;
    cfg->FindData("play_from_memory", mPlayFromBuffer, true);
    mStartTimes.clear();
    DataArray *startPtsArr = cfg->FindArray("start_points_ms", false);
    if (startPtsArr) {
        for (int i = 1; i < startPtsArr->Size(); i++) {
            mStartTimes.push_back(startPtsArr->Int(i));
        }
    }
    if (mPlayFromBuffer) {
        MILO_ASSERT(!mBuf, 0xB2);
        TheSynth->NewStreamFile(cc, mFile, mExt);
        mBytesRead = 0;
        if (!mFile) {
            MILO_FAIL("\nMetagame music not found:\n%s\n", cc);
        }
        mBufSize = mFile->Size();
        if (!mRndHeap) {
            mBuf = (unsigned char *)_MemAlloc(mBufSize, 0);
            MILO_ASSERT(!mLoader, 0xC2);
            mLoader = new MetaMusicLoader(mFile, mBytesRead, mBuf, mBufSize);
        }
    } else
        mFilename = cc;
}

void MetaMusicLoader::OpenFile() {
    mFile->ReadAsync(mBuf, mBufSize);
    mState = LoadFile;
}

void MetaMusicLoader::LoadFile() {
    if (mFile->ReadDone(mBytesRead)) {
        mState = DoneLoading;
    }
}

#pragma push
#pragma force_active on
inline bool MetaMusic::Loaded() {
    bool isLoaded = 0;
    if (mPlayFromBuffer == 0 || (mBuf != 0 && mFile == 0)) {
        isLoaded = 1;
    }
    return isLoaded;
}
#pragma pop

void MetaMusic::Poll() {
    if (mRndHeap && !mBuf) {
        int i18, i1c, i20, i24;
        MemFreeBlockStats(MemFindHeap("rnd"), i18, i1c, i20, i24);
        if (i24 <= mBufSize + 0x20)
            return;
        static int _x = MemFindHeap("rnd");
        MemTempHeap tmp(_x);
        mBufferH = _MemAllocH(mBufSize);
        mBuf = (unsigned char *)mBufferH->Lock();
        MILO_ASSERT(!mLoader, 0xE9);
        mLoader = new MetaMusicLoader(mFile, mBytesRead, mBuf, mBufSize);
    }
    if (mLoader && mBytesRead == mBufSize) {
        RELEASE(mLoader);
        RELEASE(mFile);
    }
    if (mStream && !mStream->IsPlaying() && mStream->IsReady()
        && !ThePlatformMgr.HomeMenuActive()) {
        mFader->SetVal(-96.0f);
        mFader->DoFade(mVolume, mFadeTime * 1000.0f);
        mStream->Play();
    }
    if (mStream && mStream->IsPlaying()) {
        if (!mFader->IsFading() && mFader->mVal == -96.0f) {
            RELEASE(mStream);
            UnloadStreamFx();
        } else
            UpdateMix();
    }
}

void MetaMusic::Start() {
    if (!mPlayFromBuffer || mBuf) {
        if (mStream && mStream->IsPlaying()) {
            mFader->DoFade(mVolume, mFadeTime * 1000.0f);
        } else {
            MILO_ASSERT(Loaded(), 0x122);
            RELEASE(mStream);
            UnloadStreamFx();
            if (mPlayFromBuffer) {
                MILO_ASSERT(mBuf, 0x128);
                mStream =
                    TheSynth->NewBufStream(mBuf, mBufSize, mExt, ChooseStartMs(), true);
            } else {
                MILO_ASSERT(!mFilename.empty(), 0x12D);
                mStream =
                    TheSynth->NewStream(mFilename.c_str(), ChooseStartMs(), 0, false);
            }
            mStream->Faders()->Add(mFaderMute);
            mStream->Faders()->Add(mFader);
            for (ObjPtrList<Fader>::iterator it = mExtraFaders.begin();
                 it != mExtraFaders.end();
                 ++it) {
                mStream->Faders()->Add(*it);
            }
            if (mLoop) {
                mStream->SetJump(Stream::kStreamEndMs, 0, 0);
            }
            if (unk88) {
                LoadStreamFx();
                for (int i = 0; i < 6; i++) {
                    mStream->SetFXSend(i, unk70[i]->Find<FxSendEQ>("eq.send", true));
                }
            }
            unk78 = true;
        }
    }
}

// matches in retail
void MetaMusic::UpdateMix() {
    if (!unk88) {
        if (mStream && mStream->GetNumChannels() == 2) {
            if (unk8c) {
                mStream->SetPan(0, -2.0f);
                mStream->SetPan(1, 2.0f);
            } else {
                mStream->SetPan(0, -1.0f);
                mStream->SetPan(1, 1.0f);
            }
        }
    } else {
        MILO_ASSERT(m_CurrentFxConfig, 0x16F);
        DataArray *volsArr = m_CurrentFxConfig->FindArray(vols, true);
        DataArray *pansArr = m_CurrentFxConfig->FindArray(pans, true);
        float f15 = SomeMinusFunc();
        float f16 = SomePlusFunc();
        int numChannels = Min(mStream->GetNumChannels(), 6);
        if (unk80 && unk84 <= 90) {
            DataArray *volsArr80 = unk80->FindArray(vols, true);
            DataArray *pansArr80 = unk80->FindArray(pans, true);
            for (int i = 0; i < numChannels; i++) {
                char buf[16];
                sprintf(buf, "channel_%d", i + 1);
                DataArray *chanArr7c = m_CurrentFxConfig->FindArray(buf, false);
                DataArray *chanArr80 = unk80->FindArray(buf, false);
                if (chanArr7c && chanArr80) {
                    for (ObjDirItr<FxSend> it(unk70[i], true); it != nullptr; ++it) {
                        it->EnableUpdates(false);
                        DataArray *thisFxConfigPost =
                            chanArr7c->FindArray(it->Name(), false);
                        DataArray *thisFxConfigPre =
                            chanArr80->FindArray(it->Name(), false);
                        MILO_ASSERT(thisFxConfigPost, 0x18C);
                        MILO_ASSERT(thisFxConfigPre, 0x18D);
                        MILO_ASSERT(thisFxConfigPre->Size() == thisFxConfigPost->Size(), 0x18E);
                        for (int j = 1; j < thisFxConfigPre->Size(); j++) {
                            DataArray *yetAnotherArr80 = thisFxConfigPre->Array(j);
                            DataArray *yetAnotherArr7c = thisFxConfigPost->Array(j);
                            it->SetProperty(
                                yetAnotherArr80->Sym(0),
                                f15 * yetAnotherArr80->Float(1)
                                    + f16 * yetAnotherArr7c->Float(1)
                            );
                        }
                        it->EnableUpdates(true);
                    }
                }
                mStream->SetVolume(
                    i, f15 * volsArr80->Float(i + 1) + f16 * volsArr->Float(i + 1)
                );
                mStream->SetPan(
                    i, f15 * pansArr80->Float(i + 1) + f16 * pansArr->Float(i + 1)
                );
            }

        } else if (unk84 == 0) {
            for (int i = 0; i < numChannels; i++) {
                char buf[16];
                sprintf(buf, "channel_%d", i + 1);
                DataArray *chanArr = m_CurrentFxConfig->FindArray(buf, false);
                if (chanArr) {
                    for (ObjDirItr<FxSend> it(unk70[i], true); it != nullptr; ++it) {
                        it->EnableUpdates(false);
                        DataArray *fxArr = chanArr->FindArray(it->Name(), false);
                        for (int j = 1; j < fxArr->Size(); j++) {
                            DataArray *propArr = fxArr->Array(j);
                            it->SetProperty(propArr->Sym(0), propArr->Node(1));
                        }
                        it->EnableUpdates(true);
                    }
                }
                mStream->SetVolume(i, volsArr->Float(i + 1));
                mStream->SetPan(i, pansArr->Float(i + 1));
            }
        }
        unk84++;
    }
}

DECOMP_FORCEACTIVE(MetaMusic, "mStream")

bool MetaMusic::IsPlaying() const { return mStream; }

bool MetaMusic::IsFading() const { return mFader->IsFading(); }

void MetaMusic::Stop() {
    if (mStream) {
        if (!mStream->IsPlaying()) {
            RELEASE(mStream);
            UnloadStreamFx();
        } else
            mFader->DoFade(-96.0f, mFadeTime * 1000.0f);
        unk78 = false;
    }
}

void MetaMusic::Mute() { mFaderMute->DoFade(-96.0f, 1000.0); }

void MetaMusic::UnMute() { mFaderMute->DoFade(0.0f, 1000.0); }

void MetaMusic::AddFader(Fader *fader) {
    if (fader)
        mExtraFaders.push_back(fader);
    else
        MILO_WARN("trying to add null fader");
}

void MetaMusic::SetScene(MetaMusicScene *scene) {
    if (scene) {
        DataArray *mix = scene->GetMix();
        if (mix) {
            if (!mStream || !mStream->IsPlaying()) {
                Start();
                unk80 = nullptr;
            } else
                unk80 = m_CurrentFxConfig;
            m_CurrentFxConfig = mix;
            if (m_CurrentFxConfig != unk80) {
                unk84 = 0;
            }
        }
    } else
        Stop();
}

void MetaMusic::LoadStreamFx() {
    unk70.reserve(6);
    unk70.resize(6);
    FilePath fp(".", unk88);
    for (int i = 0; i < 6; i++) {
        unk70[i].LoadFile(fp, true, false, kLoadFront, false);
        unk70[i].PostLoad(nullptr);
    }
}

void MetaMusic::UnloadStreamFx() {
    if (mStream) {
        for (int i = 0; i < 6; i++) {
            mStream->SetFXSend(i, nullptr);
        }
    }
    unk70.clear();
}

int MetaMusic::ChooseStartMs() const {
    int startMs = 0;

    if (mStartTimes.size() != 0) {
        // pick a random element
        int randomInt = RandomInt(0, mStartTimes.size());
        startMs = mStartTimes[randomInt];
    }

    return startMs;
}

BEGIN_HANDLERS(MetaMusic)
    HANDLE_ACTION(stop, Stop())
    HANDLE_ACTION(start, Start())
    HANDLE_ACTION(mute, Mute())
    HANDLE_ACTION(unmute, UnMute())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x252)
END_HANDLERS