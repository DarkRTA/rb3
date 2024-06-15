#include "synth/SlipTrack.h"
#include "synth/Stream.h"

#include "decomp.h"

SlipTrack::SlipTrack(Stream* stream, int i){
    mChannels.push_back(i);
    Init(stream);
}

// Force SetStereoPair to generate here
DECOMP_FORCEFUNC(SlipTrack, Stream, SetStereoPair(0, 0))

void SlipTrack::Init(Stream* stream){
    mStream = stream;
    mOffMs = 0.0f;
    mOn = false;
    mMaxSlip = SystemConfig("synth", "iop")->FindFloat("max_slip");
    for(std::vector<int>::iterator it = mChannels.begin(); it != mChannels.end(); it++){
        mStream->EnableSlipStreaming(*it);
    }
}

void SlipTrack::ForceOn(){
    mOffMs = 0.0f;
    VolumeOn(mStream->GetTime());
}

void SlipTrack::Poll(){
    if(mOffMs != 0.0f && mStream->GetTime() > mOffMs){
        VolumeOff();
        mOffMs = 0.0f;
    }
}

void SlipTrack::VolumeOn(float f){
    SetOffset(f - mStream->GetTime());
    mOn = true;
}

void SlipTrack::VolumeOff(){
    mOn = false;
    for(std::vector<int>::iterator it = mChannels.begin(); it != mChannels.end(); it++){
        mStream->SlipStop(*it);
    }
}

void SlipTrack::SetSpeed(float f){
    for(std::vector<int>::iterator it = mChannels.begin(); it != mChannels.end(); it++){
        mStream->SetSlipSpeed(*it, f);
    }
}

void SlipTrack::SetOffset(float f){
    for(std::vector<int>::iterator it = mChannels.begin(); it != mChannels.end(); it++){
        mStream->SetSlipOffset(*it, f);
    }
}

float SlipTrack::GetCurrentOffset(){
    return mStream->GetSlipOffset(mChannels.front());
}
