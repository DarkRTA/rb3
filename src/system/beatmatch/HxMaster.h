#ifndef BEATMATCH_HXMASTER_H
#define BEATMATCH_HXMASTER_H

class HxMaster {
public:
    HxMaster(){}
    virtual ~HxMaster(){}
    virtual void Poll(float) = 0;
    virtual void Jump(float) = 0;
    virtual void Reset() = 0;
    virtual class HxAudio* GetHxAudio() = 0;
    virtual float SongDurationMs() = 0;
};

#endif