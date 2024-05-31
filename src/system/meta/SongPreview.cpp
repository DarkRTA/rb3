#include "meta/SongPreview.h"
#include "os/System.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

SongPreview::SongPreview(const SongMgr& mgr) : mSongMgr((SongMgr&)mgr), mStream(0), mFader(0), mMusicFader(0), mCrowdSingFader(0), unk34(0), mAttenuation(0.0f), unk44(0),
    unk50(0.0f), unk54(0.0f), unk58(0.0f), unk5c(0.0f), unk64(0), unk68(0.0f), unk70(0), unk71(0), unk72(0), unk73(0) {

}

SongPreview::~SongPreview(){
    Terminate();
}

void SongPreview::Init(){
    unk48 = Symbol(0);
    unk4c = Symbol(0);
    delete mStream;
    mStream = 0;
    unk44 = 0;
    unk40 = true;
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
    unk48 = Symbol(0);
    unk4c = Symbol(0);
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
        unk68 = 0.0f;
    }
    if(!sym.Null()){
        if(!mSongMgr.HasSong(sym, true)) return;
        mSongMgr.Data(mSongMgr.GetSongIDFromShortName(sym, true)); // this part is what needs fixing
        if(!unk72){
            TheContentMgr->RegisterCallback(this, false);
            unk72 = true;
        }
        TheDebug << MakeString("Preview: Requesting %s...\n", sym.Str());
    }
    unk68 = TheTaskMgr.UISeconds();
    if(unk64){
        unk6c = sym;
        unk70 = true;
        if(unk64){
            mMusicFader->SetVal(0.0f);
            mCrowdSingFader->SetVal(-96.0f);
            switch(unk44){
                case 0:
                case 1:
                    delete mStream;
                    mStream = 0;
                    unk44 = 0;
                    break;
                case 2:
                    unk44 = 3;
                    break;
                case 4:
                    mFader->DoFade(-48.0f, mFadeTime);
                    unk44 = 5;
                    break;
                default: break;
            }
            unk64 = false;
        }
    }
    else {
        unk70 = false;
        unk64 = true;
        unk48 = sym;
        unk40 = true;
        mMusicFader->SetVal(0.0f);
        mCrowdSingFader->SetVal(-96.0f);
        switch(unk44){
            case 0:
            case 1:
                delete mStream;
                mStream = 0;
                unk44 = 0;
                break;
            case 2:
                unk44 = 3;
                break;
            case 4:
                mFader->DoFade(-48.0f, mFadeTime);
                unk44 = 5;
                break;
            default: break;
        }
    }
}

void SongPreview::ContentMounted(const char* contentName, const char* cc2){
    MILO_ASSERT(contentName, 0xE9);
    Symbol sym = Symbol(contentName);
    if(sym == unk4c){
        unk4c = Symbol(0);
    }
}

void SongPreview::ContentFailed(const char* contentName){
    MILO_ASSERT(contentName, 0xF5);
    Symbol sym = Symbol(contentName);
    if(sym == unk4c){
        unk48 = Symbol(0);
        unk4c = Symbol(0);
        unk44 = 0;
    }
}

DataNode SongPreview::OnStart(DataArray* arr){
    unk73 = 0;
    if(arr->Size() == 3){
        unk58 = 0.0f;
        unk5c = 0.0f;
        Start(arr->ForceSym(2));
    }
    else {
        unk58 = arr->Float(3);
        unk5c = arr->Float(4);
        if(arr->Size() >= 6){
            unk73 = arr->Int(5);
        }
        unk48 = Symbol(gNullStr);
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