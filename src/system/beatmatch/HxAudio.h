#ifndef BEATMATCH_HXAUDIO_H
#define BEATMATCH_HXAUDIO_H

class HxAudio {
public:
    HxAudio(){}
    virtual ~HxAudio(){}
    virtual bool IsReady() = 0;
    virtual bool Paused() const = 0;
    virtual void SetPaused(bool) = 0;
    virtual void Poll() = 0;
    virtual float GetTime() const = 0;
    virtual int GetSongStream() = 0; // fix ret type
    virtual void SetMasterVolume(float) = 0;
};

#endif