#include "meta/SongPreview.h"
#include "os/System.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

SongPreview::SongPreview(const SongMgr& mgr) : mSongMgr(mgr), mStream(0), mFader(0), mMusicFader(0), mCrowdSingFader(0),
    unk34(0), mAttenuation(0.0f), mState(kIdle), mStartMs(0.0f), mEndMs(0.0f), mStartPreviewMs(0.0f), mEndPreviewMs(0.0f),
    unk64(0), mPreviewRequestedMs(0.0f), unk70(0), unk71(0), unk72(0), mSecurePreview(0) {

}

SongPreview::~SongPreview(){
    Terminate();
}

void SongPreview::Init(){
    mSong = Symbol(0);
    mSongContent = Symbol(0);
    delete mStream;
    mStream = 0;
    mState = kIdle;
    mRestart = true;
    DataArray* cfg = SystemConfig("sound", "song_select");
    cfg->FindData("loop_forever", mLoopForever, true);
    cfg->FindData("fade_time", mFadeTime, true);
    cfg->FindData("attenuation", mAttenuation, true);
    mFadeTime *= 1000.0f;
    mFader = Hmx::Object::New<Fader>();
    mMusicFader = Hmx::Object::New<Fader>();
    mCrowdSingFader = Hmx::Object::New<Fader>();
    mCrowdSingFader->SetVal(-96.0f);
}

void SongPreview::Terminate(){
    DetachFaders();
    mSong = Symbol(0);
    mSongContent = Symbol(0);
    delete mStream;
    mStream = 0;
    delete mFader;
    mFader = 0;
    delete mMusicFader;
    mMusicFader = 0;
    delete mCrowdSingFader;
    mCrowdSingFader = 0;
    if(unk72){
        TheContentMgr->UnregisterCallback(this, true);
        unk72 = 0;
    }
}

void SongPreview::Start(Symbol sym){
    MILO_ASSERT(mFader && mMusicFader && mCrowdSingFader, 0x65);
    if(sym.Null()){
        unk70 = false;
        unk64 = false;
        mPreviewRequestedMs = 0.0f;
    }
    if(!sym.Null()){
        if(!mSongMgr.HasSong(sym, true)) return;
        SongMetadata* data = mSongMgr.Data(mSongMgr.GetSongIDFromShortName(sym, true));
        if(data && !data->IsVersionOK()){
            sym = gNullStr;
        }
        if(!unk72){
            TheContentMgr->RegisterCallback(this, false);
            unk72 = true;
        }
        TheDebug << MakeString("Preview: Requesting %s...\n", sym.Str());
    }
    mPreviewRequestedMs = TheTaskMgr.UISeconds();
    if(unk64){
        unk6c = sym;
        unk70 = true;
        if(unk64){
            mMusicFader->SetVal(0.0f);
            mCrowdSingFader->SetVal(-96.0f);
            switch(mState){
                case kIdle:
                case kMountingSong:
                    delete mStream;
                    mStream = 0;
                    mState = kIdle;
                    break;
                case kPreparingSong:
                    mState = kDeletingSong;
                    break;
                case kPlayingSong:
                    mFader->DoFade(-48.0f, mFadeTime);
                    mState = kFadingOutSong;
                    break;
                default: break;
            }
            unk64 = false;
        }
    }
    else {
        unk70 = false;
        unk64 = true;
        mSong = sym;
        mRestart = true;
        mMusicFader->SetVal(0.0f);
        mCrowdSingFader->SetVal(-96.0f);
        switch(mState){
            case kIdle:
            case kMountingSong:
                delete mStream;
                mStream = 0;
                mState = kIdle;
                break;
            case kPreparingSong:
                mState = kDeletingSong;
                break;
            case kPlayingSong:
                mFader->DoFade(-48.0f, mFadeTime);
                mState = kFadingOutSong;
                break;
            default: break;
        }
    }
}

void SongPreview::ContentMounted(const char* contentName, const char* cc2){
    MILO_ASSERT(contentName, 0xE9);
    Symbol sym = Symbol(contentName);
    if(sym == mSongContent){
        mSongContent = Symbol(0);
    }
}

void SongPreview::ContentFailed(const char* contentName){
    MILO_ASSERT(contentName, 0xF5);
    Symbol sym = Symbol(contentName);
    if(sym == mSongContent){
        mSong = Symbol(0);
        mSongContent = Symbol(0);
        mState = kIdle;
    }
}

void SongPreview::PreparePreview(){
    if(TheTaskMgr.UISeconds() - mPreviewRequestedMs < 1.0f) return;
    TheDebug << MakeString("Preview: Preparing %s\n", mSong.Str());
    float previewstart = 0.0f;
    float previewend = 15000.0f;
    if(mStartPreviewMs || mEndPreviewMs){
        previewend = mEndPreviewMs;
        previewstart = mStartPreviewMs;
    }
    else {
        int songid = mSongMgr.GetSongIDFromShortName(mSong, true);
        mSongMgr.Data(songid)->PreviewTimes(previewstart, previewend);
    }
    mStartMs = previewstart;
    mEndMs = previewend;
    PrepareSong(mSong);
    if(!mLoopForever) mRestart = false;
}

void SongPreview::Poll(){
    if(unk70) Start(unk6c);
    switch(mState){
        case kIdle:
            break;
        case kMountingSong:
            bool b = true;
            if(!mSong.Null()){
                // fix: needs to call TheContentMgr
                if(ContentDiscovered(mSong))
                b = false;
            }
            if(b) PreparePreview();
            break;
        case kPreparingSong:
            if(mStream->IsReady()){
                mFader->SetVal(-48.0f);
                mFader->DoFade(0.0f, mFadeTime);
                mStream->Play();
                mState = kPlayingSong;
            }
            break;
        case kDeletingSong:
            delete mStream;
            mStream = 0;
            mState = kIdle;
            break;
        case kPlayingSong:
            if(mStream->GetTime() >= mEndMs){
                mState = kFadingOutSong;
                mFader->DoFade(-48.0f, mFadeTime);
            }
            break;
        case kFadingOutSong:
            if(!mFader->IsFading()){
                delete mStream;
                mStream = 0;
                mState = kIdle;
            }
            break;
        default: break;
    }
}

DataNode SongPreview::OnStart(DataArray* arr){
    mSecurePreview = false;
    if(arr->Size() == 3){
        mStartPreviewMs = 0.0f;
        mEndPreviewMs = 0.0f;
        Start(arr->ForceSym(2));
    }
    else {
        mStartPreviewMs = arr->Float(3);
        mEndPreviewMs = arr->Float(4);
        if(arr->Size() >= 6){
            mSecurePreview = arr->Int(5);
        }
        mSong = Symbol(gNullStr);
        Start(arr->ForceSym(2));
    }
    return DataNode(1);
}

void SongPreview::SetMusicVol(float f){
    if(f < mMusicFader->GetTargetDb()){
        mMusicFader->DoFade(f, 250.0f);
    }
    else mMusicFader->DoFade(f, 1000.0f);
}

void SongPreview::SetCrowdSingVol(float f){
    mCrowdSingFader->DoFade(f, 0.0f);
}

void SongPreview::DetachFader(Fader* fader){
    if(mStream && fader){
        for(int i = 0; i < unk34; i++){
            mStream->ChannelFaders(i)->Remove(fader);
        }
    }
}

void SongPreview::DetachFaders(){
    DetachFader(mMusicFader);
    DetachFader(mCrowdSingFader);
}

BEGIN_HANDLERS(SongPreview)
    HANDLE(start, OnStart)
    HANDLE_ACTION(set_music_vol, SetMusicVol(_msg->Float(2)))
    HANDLE_ACTION(set_crowd_sing_vol, SetCrowdSingVol(_msg->Float(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x246)
END_HANDLERS