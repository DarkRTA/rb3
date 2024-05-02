#ifndef META_STREAMPLAYER_H
#define META_STREAMPLAYER_H
#include "obj/Object.h"

class Stream;

class StreamPlayer : public Hmx::Object {
public:
    StreamPlayer();
    virtual ~StreamPlayer();
    virtual DataNode Handle(DataArray*, bool);

    void Delete();
    void PlayFile(const char*, float, float, bool);
    void Poll();
    void Init();
    void StopPlaying();
    void SetMasterVolume(float);

    static float kStreamEndMs;
    static int kStreamEndSamples;

    float mMasterVol;
    float mStreamVol;
    bool mLoop;
    bool mStarted;
    bool mPaused;
    Stream* mStream;
    void* mSongBuf;
};

#endif
