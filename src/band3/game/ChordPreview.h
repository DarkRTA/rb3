#pragma once
#include "obj/Object.h"
#include "os/ContentMgr.h"
#include "synth/Faders.h"
#include "synth/Stream.h"
#include "utl/Symbol.h"

class ChordPreview : public ContentMgr::Callback, public Hmx::Object {
public:
    class StreamData {
    public:
        void Reset(bool);

        Stream *stream;
        int state;
        Fader *fader;
        bool needReset;
        float startMs;
        float endMs;
    };
    void Start(Symbol);

    StreamData mStreamData[3]; // 0x20
    Fader *mGuitarFader; // 0x68
    Fader *mSilenceFader; // 0x6c
    int mNumChannels; // 0x70
    float mFadeMs; // 0x74
    Symbol mSong; // 0x78
    Symbol mSongContent; // 0x7c
    float mStartMs; // 0x80
    float mEndMs; // 0x84
    bool mRegisteredWithCM; // 0x88
};