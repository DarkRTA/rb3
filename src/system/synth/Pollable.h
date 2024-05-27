#ifndef SYNTH_POLLABLE_H
#define SYNTH_POLLABLE_H
#include <list>

class SynthPollable {
public:
    SynthPollable();
    virtual ~SynthPollable();
    virtual const char* GetSoundDisplayName(){ return ""; }
    virtual void SynthPoll() = 0;

    void StartPolling();
    void CancelPolling();
    void PollAll();

    std::list<SynthPollable*>::iterator mItr;

    static std::list<SynthPollable*> sPollables;
    bool mIsActive;
};

#endif
