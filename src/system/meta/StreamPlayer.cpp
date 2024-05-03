#include "meta/StreamPlayer.h"
#include "synth/Stream.h"
#include "synth/Synth.h"
#include "utl/Symbols.h"

float StreamPlayer::kStreamEndMs = -1.1920929E-7f;
int StreamPlayer::kStreamEndSamples = -1;

StreamPlayer::StreamPlayer() : mMasterVol(1.0f), mStreamVol(1.0f), mLoop(0), mStarted(0), mPaused(0), mStream(0), mSongBuf(0) {

}

StreamPlayer::~StreamPlayer(){
    Delete();
}

void StreamPlayer::Delete(){
    if(mStream){
        mStream->Stop();
    }
    delete mStream;
    mStream = 0;
    if(mSongBuf){
        delete mSongBuf;
        mSongBuf = 0;
    }
}

void StreamPlayer::PlayFile(const char* cc, float f1, float f2, bool b){
    Delete();
    mStream = TheSynth->NewStream(cc, 0.0f, 0.0f, false);
    MILO_ASSERT(mStream, 0x34);
    mStarted = false;
    mLoop = b;
    mStreamVol = f1;
}

void StreamPlayer::Poll(){
    if(mStream && !mPaused && !mStream->IsPlaying()){
        if(mStream->IsReady()){
            if(!mStarted){
                Init();
                mStarted = true;
            }
            mStream->Play();
        }
        else {
            if(mStarted){
                mStarted = false;
                Delete();
            }
        }
    }
}

void StreamPlayer::Init(){
    mStream->SetVolume(mStreamVol * mMasterVol);
    int chanCount = mStream->GetNumChannels();
    if(chanCount == 2){
        mStream->SetPan(0, -1.0f);
        mStream->SetPan(1, 1.0f);
    }
    else mStream->SetPan(0, 0.0f);
    if(mLoop){
        mStream->SetJump(kStreamEndMs, 0.0f, 0);
    }
}

void StreamPlayer::StopPlaying(){ Delete(); }

void StreamPlayer::SetMasterVolume(float f){
    mMasterVol = f;
    if(!mStream) return;
    mStream->SetVolume(mStreamVol * mMasterVol);
}

BEGIN_HANDLERS(StreamPlayer)
    HANDLE_ACTION(set_volume, SetMasterVolume(_msg->Float(2)))
    HANDLE_CHECK(0xA9)
END_HANDLERS