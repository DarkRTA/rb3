#include "synth/BinkClip.h"
#include "synth/Synth.h"
#include "utl/Symbols.h"

BinkClip::PanInfo::PanInfo(int i, float f) : chan(i), pan(f) {}

BinkClip::BinkClip() : mVolume(0), mLoop(0), mPreload(0), mStream(0), mPlaybackVolumeOffset(0), mData(0), mSize(0), mLoader(0),
    mFadeOutFader(Hmx::Object::New<Fader>()), mUnloadWhenFinishedPlaying(0), mPlaying(0), mStreamLoader(0) {
    mFaders.push_back(mFadeOutFader);
    StartPolling();
}

BinkClip::~BinkClip(){
    delete mLoader;
    mLoader = 0;
    delete mFadeOutFader;
    mFadeOutFader = 0;
    KillStream();
    UnloadData();
}

void BinkClip::SynthPoll(){
    if(mPlaying && mStream){
        if(!mStream->IsPlaying() && mStream->IsReady()){
            mStream->Play();
        }
        else {
            if(mStream->IsFinished() || mFadeOutFader->mVal == -96.0f){
                Stop();
            }
        }
    }
}

SAVE_OBJ(BinkClip, 0x5D)

BEGIN_COPYS(BinkClip)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(BinkClip)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFile)
        COPY_MEMBER(mVolume)
        COPY_MEMBER(mLoop)
        COPY_MEMBER(mPreload)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_LOADS(BinkClip)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BinkClip::PreLoad(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 1) MILO_WARN("Can't load new BinkClip");
    else {
        LOAD_SUPERCLASS(Hmx::Object);
        bs >> mFile >> mVolume >> mLoop >> mPreload;
        if(!mFile.empty()){
            LoadFile(rev > 0 ? &bs : 0);
        }
    }
}

void BinkClip::PostLoad(BinStream&){ EnsureLoaded(); }

void BinkClip::Play(){
    if(!mPreload){
        String str(mFile.c_str());
        str = str.substr(0, str.length() - 4);
        mStream = dynamic_cast<StandardStream*>(TheSynth->NewStream(str.c_str(), 0, 0, false));
        mFadeOutFader->SetVal(0);
        SetLoop(mLoop);
        UpdateVolume();
        UpdateFaders();
        UpdatePanInfo();
        mPlaying = true;
    }
    else {
        if(EnsureLoaded()){
            KillStream();
            mStream = dynamic_cast<StandardStream*>(TheSynth->NewBufStream(mData, mSize, "bik", 0, true));
            mFadeOutFader->SetVal(0);
            SetLoop(mLoop);
            UpdateVolume();
            UpdateFaders();
            UpdatePanInfo();
            mPlaying = true;
        }
        else MILO_WARN("bik file not loaded: '%s'", mFile.c_str());
    }
}

void BinkClip::Pause(bool b){
    mPlaying = !b;
    if(mStream && !mPlaying) mStream->Stop();
}

void BinkClip::Stop(){
    KillStream();
    if(mUnloadWhenFinishedPlaying) UnloadData();
}

bool BinkClip::IsStreaming() const {
    return mStream && mStream->IsPlaying();
}

void BinkClip::SetFile(const char* file){
    MILO_ASSERT(file != NULL, 0xFE);
    mFile.SetRoot(file);
    LoadFile(0);
}

void BinkClip::SetVolume(float f){
    mVolume = f;
    UpdateVolume();
}

void BinkClip::SetLoop(bool b){
    mLoop = b;
    if(mStream){
        mStream->ClearJump();
        if(mLoop) mStream->SetJump(Stream::kStreamEndMs, 0, 0);
    }
}

void BinkClip::AddFader(Fader* fader){
    if(fader){
        bool found = false;
        for(std::vector<Fader*>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
            if(*it == fader){
                found = true;
                break;
            }
        }
        if(!found) mFaders.push_back(fader);
        if(mStream) mStream->Faders()->Add(fader);
    }
}

void BinkClip::RemoveFader(Fader* fader){
    if(fader){
        for(std::vector<Fader*>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
            if(*it == fader){
                mFaders.erase(it);
                break;
            }
        }
        if(mStream) mStream->Faders()->Remove(fader);
    }
}

void BinkClip::SetPan(int chan, float pan){
    PanInfo info(chan, pan);
    bool found = false;
    for(std::vector<PanInfo>::iterator it = mPanInfo.begin(); it != mPanInfo.end(); ++it){
        if((*it).chan == chan){
            *it = info;
            found = true;
            break;
        }
    }
    if(!found) mPanInfo.push_back(info);
    if(mStream) mStream->SetPan(info.chan, info.pan);
}

void BinkClip::FadeOut(float f){
    mFadeOutFader->DoFade(-96.0f, f);
}

void BinkClip::UnloadWhenFinishedPlaying(bool b){ mUnloadWhenFinishedPlaying = b; }

void BinkClip::LoadFile(BinStream* bs){
    delete mLoader;
    mLoader = 0;
    KillStream();
    UnloadData();
    if(mPreload){
        BinStream* toUse = bs && bs->Cached() ? bs : 0;
        mLoader = new FileLoader(mFile, FileLocalize(mFile.c_str(), 0), kLoadFront, 0, false, true, toUse);
        if(!mLoader) MILO_WARN("Could not load bik file '%s'", mFile.c_str());
    }
}

bool BinkClip::IsReadyToPlay() const {
    if(!mPreload) return true;
    if(mLoader) return mLoader->IsLoaded();
    return mData && mSize > 0;
}

bool BinkClip::EnsureLoaded(){
    if(mLoader){
        if(!mLoader->IsLoaded()){
            MILO_WARN("BinkClip blocked while loading '%s'", mFile.c_str());
            TheLoadMgr.PollUntilLoaded(mLoader, 0);
        }
        mData = (void*)mLoader->GetBuffer(&mSize);
        delete mLoader;
        mLoader = 0;
    }
    return mData && mSize > 0;
}

void BinkClip::UpdateVolume(){
    if(mStream) mStream->Stream::SetVolume(mVolume + mPlaybackVolumeOffset);
}

void BinkClip::UpdateFaders(){
    if(mStream){
        for(std::vector<Fader*>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
            mStream->Faders()->Add(*it);
        }
    }
}

void BinkClip::UpdatePanInfo(){
    if(mStream){
        for(std::vector<PanInfo>::iterator it = mPanInfo.begin(); it != mPanInfo.end(); ++it){
            mStream->SetPan((*it).chan, (*it).pan);
        }
    }
}

void BinkClip::KillStream(){
    mPlaying = false;
    delete mStream;
    mStream = 0;
}

void BinkClip::UnloadData(){
    if(mData){
        _MemFree(mData);
        mData = 0;
        mSize = 0;
    }
}

BEGIN_PROPSYNCS(BinkClip)
    SYNC_PROP_SET(file, mFile, SetFile(_val.Str()))
    SYNC_PROP_SET(volume, mVolume, SetVolume(_val.Float()))
    SYNC_PROP_SET(loop, mLoop, SetLoop(_val.Int()))
    SYNC_PROP_SET(preload, mPreload, mPreload = _val.Int())
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS

BEGIN_HANDLERS(BinkClip)
    HANDLE_ACTION(play, Play())
    HANDLE_ACTION(stop, Stop())
    HANDLE_ACTION(set_pan, SetPan(_msg->Int(2), _msg->Float(3)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x24A)
END_HANDLERS
