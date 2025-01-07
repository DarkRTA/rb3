#pragma once
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "synth/MoggClip.h"

class MoggClipMap : public Hmx::Object {
public:
    MoggClipMap(Hmx::Object*);
    virtual ~MoggClipMap(){}
    void myLoad(BinStream&);

    MoggClip* GetMoggClip() const { return mMoggClip; }

    static int sRev;

    /** "Which moggclip to play" */
    ObjPtr<MoggClip> mMoggClip; // 0x1c
    /** "Surround pan, between -4 and 4" */
    float mPan; // 0x28
    /** "Surround pan width, between 0 and 4" */
    float mPanWidth; // 0x2c
    /** "Volume in dB (0 is full volume, -96 is silence)" */
    float mVolume; // 0x30
    /** "Is the mogg clip stereo?" */
    bool mIsStereo; // 0x34
};

BinStream& operator>>(BinStream&, MoggClipMap&);
