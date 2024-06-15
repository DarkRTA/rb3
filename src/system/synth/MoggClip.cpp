#include "synth/MoggClip.h"
#include "synth/StandardStream.h"
#include "synth/Synth.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"

MoggClip::PanInfo::PanInfo(int i, float f) : channel(i), panning(f) {}

MoggClip::MoggClip() : mFilePath(), mVolume(0.0f), mLoop(0), mControllerVolume(0.0f), mStream(0), unk44(0.0f), unk48(0), unk4c(0), mFileLoader(0), mFaders(), mPanInfos() {
    Fader* f = Hmx::Object::New<Fader>();
    unk69 = 0;
    unk6a = 0;
    mLoopStart = 0;
    mLoopEnd = -1;
    mFader = f;
    mFaders.push_back(mFader);
    StartPolling();
}

MoggClip::~MoggClip(){
    delete mFileLoader;
    mFileLoader = 0;
    delete mFader;
    mFader = 0;
    KillStream();
    UnloadData();
}

const char* MoggClip::GetSoundDisplayName(){
    if(unk6a){
        return MakeString("MoggClip: %s", FileGetName(mFilePath.c_str()));
    }
    return gNullStr;
}

void MoggClip::SynthPoll(){
    if(unk6a && mStream){
        mStream->PollStream();
        if(!mStream->IsPlaying() && mStream->IsReady()){
            if(mPanInfos.size() == 0){
                int chans = mStream->GetNumChannels();
                if(chans == 1){
                    mStream->SetPan(0, 0.0f);
                }
                else if(chans == 2){
                    mStream->SetPan(0, -1.0f);
                    mStream->SetPan(1, 1.0f);
                }
            }
            mStream->Play();
        }
        else {
            if(mStream->IsFinished() || mFader->mVal == -96.0f) Stop();
        }
    }
}

SAVE_OBJ(MoggClip, 0x82)

BEGIN_COPYS(MoggClip)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(MoggClip)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFilePath)
        COPY_MEMBER(mVolume)
        COPY_MEMBER(mLoop)
        COPY_MEMBER(mLoopStart)
        COPY_MEMBER(mLoopEnd)
    END_COPYING_MEMBERS
END_COPYS

void MoggClip::Load(BinStream& bs){
    PreLoad(bs);
    PostLoad(bs);
    MILO_WARN("%s:  Ogg files are not supported in RB3_Wii.", (const char*)FindPathName());
}

void MoggClip::PreLoad(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 2) MILO_WARN("Can't load new MoggClip");
    else {
        Hmx::Object::Load(bs);
        char buf[0x100];
        bs.ReadString(buf, 0x100);
        mFilePath.SetRoot(buf);
        bs >> mVolume >> mLoop;
        if(rev > 1) bs >> mLoopStart >> mLoopEnd;
        LoadFile(rev > 0 ? &bs : 0);
    }
}

void MoggClip::PostLoad(BinStream& bs){ EnsureLoaded(); }

void MoggClip::Play(){
    if(EnsureLoaded()){
        KillStream();
        mStream = dynamic_cast<StandardStream*>(TheSynth->NewBufStream(unk48, unk4c, "mogg", 0.0f, 0));
        mFader->SetVal(0.0f);
        SetLoop(mLoop);
        SetVolume(mVolume);
        UpdateFaders();
        UpdatePanInfo();
        unk6a = true;
    }
    else MILO_WARN("Mogg file not loaded: '%s'", mFilePath.c_str());
}

void MoggClip::Pause(bool b){
    unk6a = b == 0;
    if(mStream && !unk6a){
        mStream->Stop();
    }
}

void MoggClip::Stop(){
    KillStream();
    if(unk69) UnloadData();
}

void MoggClip::SetFile(const char* file){
    MILO_ASSERT(file != NULL, 0x120);
    mFilePath.SetRoot(file);
    LoadFile(0);
}

void MoggClip::SetVolume(float f){
    mVolume = f;
    if(mStream){
        Stream* strm = mStream;
        strm->SetVolume(mVolume + mControllerVolume);
    }
}

void MoggClip::SetControllerVolume(float ff){
    mControllerVolume = ff;
    if(mStream){
        Stream* strm = mStream;
        strm->SetVolume(mVolume + mControllerVolume);
    }
}

void MoggClip::SetLoop(bool b){
    mLoop = b;
    if(mStream){
        mStream->ClearJump();
        if(mLoop){
            mStream->SetJumpSamples(mLoopEnd, mLoopStart, 0);
        }
    }
}

void MoggClip::SetLoopStart(int i){ mLoopStart = i; }
void MoggClip::SetLoopEnd(int i){ mLoopEnd = i; }

void MoggClip::SetPan(int chan, float pan){
    PanInfo pinfo(chan, pan);
    bool here = false;
    for(std::vector<PanInfo>::iterator it = mPanInfos.begin(); it != mPanInfos.end(); it++){
        if(it->channel == pinfo.channel){
            here = true;
            *it = pinfo;
            break;
        }
    }
    if(!here) mPanInfos.push_back(pinfo);
    if(mStream) mStream->SetPan(pinfo.channel, pinfo.panning);
}

void MoggClip::LoadFile(BinStream* bs){
    delete mFileLoader;
    mFileLoader = 0;
    KillStream();
    UnloadData();
    if(*mFilePath.c_str() != '\0'){
        BinStream* bsToUse = (bs && bs->Cached()) ? bs : 0;
        mFileLoader = new FileLoader(mFilePath, FileLocalize(mFilePath.c_str(), 0), kLoadFront, 0, false, true, bsToUse);
        if(!mFileLoader) MILO_WARN("Could not load mogg file '%s'", mFilePath.c_str());
    }
}

bool MoggClip::EnsureLoaded(){
    if(mFileLoader){
        if(!mFileLoader->IsLoaded()){
            MILO_WARN("MoggClip blocked while loading '%s'", mFilePath.c_str());
            TheLoadMgr.PollUntilLoaded(mFileLoader, 0);
        }
        unk48 = (void*)mFileLoader->GetBuffer(&unk4c);
        delete mFileLoader;
        mFileLoader = 0;
    }
    bool ret = false;
    if(unk48 != 0 && 0 < unk4c) ret = true;
    return ret;
}

void MoggClip::UpdateFaders(){
    if(mStream){
        for(std::vector<Fader*>::iterator it = mFaders.begin(); it != mFaders.end(); it++){
            mStream->mFaders->Add(*it);
        }
    }
}

void MoggClip::UpdatePanInfo(){
    if(mStream){
        for(std::vector<PanInfo>::iterator it = mPanInfos.begin(); it != mPanInfos.end(); it++){
            mStream->SetPan(it->channel, it->panning);
        }
    }
}

void MoggClip::KillStream(){
    unk6a = false;
    delete mStream;
    mStream = 0;
}

void MoggClip::UnloadData(){
    if(unk48){
        _MemFree(unk48);
        unk48 = 0;
        unk4c = 0;
    }
}

void MoggClip::SetupPanInfo(float f1, float f2, bool b){
    if(b){
        SetPan(0, -f2 / 2.0f + f1);
        SetPan(1, f2 / 2.0f + f1);
    }
    else SetPan(0, f1);
}

BEGIN_PROPSYNCS(MoggClip)
    SYNC_PROP_SET(file, mFilePath, SetFile(_val.Str(0)))
    SYNC_PROP_SET(volume, mVolume, SetVolume(_val.Float(0)))
    SYNC_PROP_SET(loop, mLoop, SetLoop(_val.Int(0) != 0))
    SYNC_PROP_SET(loop_start_sample, mLoopStart, SetLoopStart(_val.Int(0)))
    SYNC_PROP_SET(loop_end_sample, mLoopEnd, SetLoopEnd(_val.Int(0)))
END_PROPSYNCS

BEGIN_HANDLERS(MoggClip)
    HANDLE_ACTION(play, Play())
    HANDLE_ACTION(stop, Stop())
    HANDLE_ACTION(set_pan, SetPan(_msg->Int(2), _msg->Float(3)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x27F)
END_HANDLERS