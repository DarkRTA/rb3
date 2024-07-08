#include "meta/CreditsPanel.h"
#include "ui/UIList.h"
#include "synth/Faders.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "utl/Messages.h"

CreditsPanel::CreditsPanel() : mLoader(0), mNames(0), mStream(0), mAutoScroll(1), mSavedSpeed(-1.0f), mPaused(0) {

}

CreditsPanel::~CreditsPanel(){

}

void CreditsPanel::Load(){
    UIPanel::Load();
    mLoader = new DataLoader(FilePath(SystemConfig("credits_file")->Str(1)), kLoadFront, true);
}

bool CreditsPanel::IsLoaded() const {
    return UIPanel::IsLoaded() && mLoader->IsLoaded();
}

void CreditsPanel::FinishLoad(){
    UIPanel::FinishLoad();
    mNames = mLoader->Data();
    MILO_ASSERT(mNames, 0x35);
    mNames->AddRef();
    mList = mDir->Find<UIList>("credits.lst", true);
    mList->SetProvider(this);
    delete mLoader;
    mLoader = 0;
}

void CreditsPanel::Exit(){
    if(mStream && !mPaused){
        mStream->Faders()->FindLocal("fade", true)->DoFade(-96.0f, 2000.0f);
    }
    UIPanel::Exit();
}

bool CreditsPanel::Exiting() const {
    bool ret = true;
    bool b = false;
    if(mStream){
        if(mStream->Faders()->FindLocal("fade", true)->IsFading()) b = true;
    }
    if(!b && !UIPanel::Exiting()) ret = false;
    return ret;
}

void CreditsPanel::Unload(){
    UIPanel::Unload();
    if(mNames){
        mNames->Release();
        mNames = 0;
    }
    delete mStream;
    mStream = 0;
}

void CreditsPanel::Enter(){
    UIPanel::Enter();
    mCheatOn = false;
    mPaused = false;
    mList->SetSelected(0, -1);
    mAutoScroll = true;
    mList->AutoScroll();
}

void CreditsPanel::Poll(){
    UIPanel::Poll();
    if(!mStream){
        // virtual Stream* NewStream(const char*, float, float, bool);
        mStream = TheSynth->NewStream("sfx/streams/credits",0,0,0);
        MILO_ASSERT_FMT(mStream, "sfx/streams/credits.foo missing");
        mStream->SetJump(Stream::kStreamEndMs,0,0);
        mStream->SetPan(0, -1.0f);
        mStream->SetPan(1, 1.0f);
        mStream->SetVolume(-4.0f);
        mStream->Faders()->AddLocal("fade");
    }
    else {
        if(!mStream->IsPlaying() && mStream->IsReady() && !mPaused){
            mStream->Play();
        }
    }
    if(mAutoScroll && TheUI->GetTransitionState() == kTransitionNone){
        if(!mList->IsScrolling()){
            HandleType(credits_done_msg);
            SetAutoScroll(false);
        }
    }
}

void CreditsPanel::SetAutoScroll(bool b){
    if(b == mAutoScroll) return;
    mAutoScroll = b;
    if(mAutoScroll) mList->AutoScroll();
    else mList->StopAutoScroll();
}