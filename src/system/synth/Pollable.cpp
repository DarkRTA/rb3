#include "synth/Pollable.h"

std::list<SynthPollable*> SynthPollable::sPollables;

SynthPollable::SynthPollable() : mItr(sPollables.begin()), mIsActive(0) {

}

SynthPollable::~SynthPollable(){
    CancelPolling();
}

void SynthPollable::StartPolling(){
    if(mItr == sPollables.begin()){
        sPollables.push_back(0);
        mItr = sPollables.begin();
        mIsActive = true;
    }
}

void SynthPollable::CancelPolling(){
    if(mIsActive){
        std::list<SynthPollable*>::iterator beginning = sPollables.begin();
        if(mItr != beginning){
            sPollables.erase(mItr);
            mItr = beginning;
            mIsActive = false;
        }
    }
}

void SynthPollable::PollAll(){
    for(std::list<SynthPollable*>::iterator it = sPollables.begin(); it != sPollables.end(); it++){
        (*it)->SynthPoll();
    }
}